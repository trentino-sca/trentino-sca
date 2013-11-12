// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
// http://trentino.sourceforge.net/
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, g (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
// **********************************************************************************

//header
#include "TrentinoDiscoveryImpl.h"

//standart
#include <boost/ref.hpp>
//#pragma warning(push)
//#pragma warning(disable:4996)
//#include <sys/timeb.h>
//#include <sstream>
//
//#include <boost/uuid/uuid.hpp>            // uuid class
//#include <boost/uuid/uuid_generators.hpp> // generators
//#include <boost/uuid/uuid_io.hpp>
//#pragma warning(pop)

//specific
#include "TrentinoDiscoveryTask.h"
#include "TrentinoDiscoveryUtil.h"
#include "TrentinoDiscoveryTaskStart.h"
#include "TrentinoDiscoveryTaskRegister.h"
#include "TrentinoDiscoveryTaskDeregister.h"
#include "TrentinoDiscoveryTaskFindSrv.h"
#include "TrentinoDiscoveryTaskStop.h"
#include "TrentinoDiscoveryFactory.h"


using namespace Trentino::Discovery;
using namespace std;

//static member variables
DiscoveryManager* DiscoveryManager::mInstance;
DiscoveryTaskQueue DiscoveryManager::mTaskQueue;
bool DiscoveryManager::mFlagDiscoveryTaskProcessingThread = true;
std::list< boost::shared_ptr<DiscoveryTask> > DiscoveryManager::mWaitingTaskList;
boost::mutex DiscoveryManager::mMutexWaitingList;
bool DiscoveryManager::mInstantiated = false;

boost::mutex DiscoveryManager::mMutexProcessTaskThread;
boost::thread_group DiscoveryManager::mThreads;
Trentino::Discovery::DiscoveryFactory* DiscoveryManager::mDiscoveryFactory;
DiscoveryManager::DISCOVERY_LAYER_STATES   DiscoveryManager::mDiscoveryLayerState= DISCOVERY_NOT_INITIATED;

DiscoveryManager::DiscoveryManager()
   :DiscoveryInterface(1, 1)
{

}

DiscoveryManager::~DiscoveryManager()
{

}

//boost::shared_ptr<DiscoveryInterface> DiscoveryImpl::getDiscoveryInterface() 
DiscoveryInterface* DiscoveryManager::getDiscoveryInterface() 
{ 
   return static_cast<DiscoveryInterface*>( (getInstance()));
} 

DiscoveryManager* DiscoveryManager::getInstance()
{
   if(mInstantiated ==  false)
   {
      mInstance = new DiscoveryManager();
      mInstantiated = true;
   }
   return mInstance;
}

void DiscoveryManager::start( bool isDA, 
   int retryCount, 
   int retryInterval, 
   onDiscoveryStartCBPtr discoveryTaskCB)
{
   if(mDiscoveryLayerState == DISCOVERY_NOT_INITIATED)
   {
      mRetryCount = retryCount;
      mRetryInterval = retryInterval;
      // TODO : pass this isDA info to the open slp lib
      isDA;

      mFlagDiscoveryTaskProcessingThread = true;
      mThreads.create_thread((boost::ref(*this)));
      mThreads.create_thread(&DiscoveryManager::checkWaitingList);
      mDiscoveryLayerState = DISCOVERY_INITIATED;
   }

   if(mDiscoveryLayerState == DISCOVERY_INITIATED)
   {
      if(!isDA)
      {
         discoveryTaskCB(true,"This runtime is not a DA so relies on that a running DA already exists");
         return;
      }
      DiscoveryTask::discoveryFrameWorkCBFuncPtr funcPtr = &DiscoveryManager::onTaskComplete;
      DiscoveryTaskStart::startRealtedCB onStartedFuncPtr = &DiscoveryManager::OnStarted;
      DiscoveryTaskStart::startRealtedCB onStartFailedFuncPtr =   &DiscoveryManager::OnStartFailed;
      DiscoveryTaskStart::startRealtedCB onStartingFuncPtr =   &DiscoveryManager::OnStarting;
      DiscoveryTaskSharedPtr taskPtr = DiscoveryTaskSharedPtr(new DiscoveryTaskStart(funcPtr,
         mRetryCount, 
         mRetryInterval,
         mDiscoveryMethodInterface, 
         discoveryTaskCB,
         onStartedFuncPtr,
         onStartFailedFuncPtr,
         onStartingFuncPtr));
      //mTaskQueue.enqueue(taskPtr);
      taskPtr->setSharedPtr(taskPtr);
      // converted the discovery starting to be syncronous
      for(int counter = 0; counter < mRetryCount  ; counter++)
      {
         taskPtr->execute();
         if(taskPtr->succeeded())
         {
            break;
         }
      }
   }
}

void DiscoveryManager::stop(Trentino::Discovery::DiscoveryFactory* factory, bool isDA)
{
   DiscoveryTask::discoveryFrameWorkCBFuncPtr funcPtr = &DiscoveryManager::onTaskComplete;
   //DiscoveryTaskStop::onStopFuncPtr funcPtrStop = &DiscoveryManager::onStop;
   mDiscoveryFactory = factory;
   
   mMutexProcessTaskThread.lock();
   mFlagDiscoveryTaskProcessingThread = false;
   mMutexProcessTaskThread.unlock();
   
   //mTaskQueue.clear();
   //mWaitingTaskList.clear();

   //mThreads.interrupt_all();

   mDiscoveryLayerState = DISCOVERY_NOT_INITIATED;
   if(!isDA)
   {
      return;
   }
   DiscoveryTaskSharedPtr taskPtr =  DiscoveryTaskSharedPtr(new DiscoveryTaskStop(funcPtr,
      mRetryCount, 
      mRetryInterval,
      mDiscoveryMethodInterface));
   taskPtr->setSharedPtr(taskPtr);
   if(!mTaskQueue.empty() || !mWaitingTaskList.empty() )
   {
      boost::this_thread::sleep(boost::posix_time::millisec(1500));
   }
   mTaskQueue.clear();
   mWaitingTaskList.clear();

   mThreads.interrupt_all();
   //try as long as retryTimes but at most 5 times
   for(int counter = 0; counter < mRetryCount  ; counter++)
   {
      taskPtr->execute();
      if(taskPtr->succeeded())
      {
         break;
      }
   }

   delete mInstance;
}

void DiscoveryManager::setDiscoveryMethodInterface(DiscoveryMethodInterface* methodInterface)
{
   mDiscoveryMethodInterface = methodInterface;
}

int DiscoveryManager::registerService(std::string serviceIdentifier, 
   ConstMetadataConstSharedPtr serviceAttributes, 
   onDiscoveryTaskRegsiterCB registerCB)
{
   discoveryFrameWorkCBFuncPtr funcPtr = &DiscoveryManager::onTaskComplete;
   DiscoveryTaskSharedPtr taskPtr = DiscoveryTaskSharedPtr(new DiscoveryTaskRegister(funcPtr,
      mRetryCount, 
      mRetryInterval, 
      mDiscoveryMethodInterface,
      DiscoveryManager::escapeServiceId(serviceIdentifier),
      serviceAttributes,
      registerCB));

   mTaskQueue.enqueue(taskPtr);
   taskPtr->setSharedPtr(taskPtr);

   //taskPtr->setSharedPtr(taskPtr);
   ////try as long as retryTimes but at most 5 times
   //for(int counter = 0; counter < mRetryCount  ; counter++)
   //{
   //   taskPtr->execute();
   //   if(taskPtr->succeeded())
   //   {
   //      break;
   //   }
   //}

   return taskPtr->getID();  
}

void DiscoveryManager::deregisterService(std::string serviceIdentifier)
{
   discoveryFrameWorkCBFuncPtr funcPtr = &DiscoveryManager::onTaskComplete;
   DiscoveryTaskSharedPtr taskPtr = DiscoveryTaskSharedPtr(new DiscoveryTaskDeregister(funcPtr,
      mRetryCount, 
      mRetryInterval, 
      mDiscoveryMethodInterface,
      DiscoveryManager::escapeServiceId(serviceIdentifier)));

   mTaskQueue.enqueue(taskPtr);
   taskPtr->setSharedPtr(taskPtr);

}

// asyncall for eager initialization
int DiscoveryManager::findService(std::string serviceIdentifier, 
   ConstMetadataConstSharedPtr const serviceAttributes, 
   //listFoundServices& foundServices, 
   listFoundServices& foundServices,
   onDiscoveryTaskFindSrvCB onServiceFoundFn)
{
   discoveryFrameWorkCBFuncPtr funcPtr = &DiscoveryManager::onTaskComplete;
   //boost::shared_ptr<listFoundServices> listFoundServicesPtr(&foundServices);
   DiscoveryTaskSharedPtr taskPtr = DiscoveryTaskSharedPtr(new DiscoveryTaskFindSrv(funcPtr,
      mRetryCount, 
      mRetryInterval, 
      mDiscoveryMethodInterface,
      DiscoveryManager::escapeServiceId(serviceIdentifier),
      serviceAttributes,
      onServiceFoundFn,
      //foundServices));
      // listFoundServicesPtr));
   &foundServices));

   //taskPtr->setSharedPtr(taskPtr);
   ////try as long as retryTimes but at most 5 times
   //for(int counter = 0; counter < mRetryCount  ; counter++)
   //{
   //   taskPtr->execute();
   //   if(taskPtr->succeeded())
   //   {
   //      break;
   //   }
   //}

   taskPtr->setSharedPtr(taskPtr);
   mTaskQueue.enqueue(taskPtr);
   return taskPtr->getID();   
}


void DiscoveryManager::processDiscoveryTasks()
{
   // Main thread loop
   while(mFlagDiscoveryTaskProcessingThread)
   {
      try
      {
         DiscoveryTaskSharedPtr  taskPtr = mTaskQueue.dequeue();
         taskPtr->setExecutionTickCount(DiscoveryUtil::GetMilliCount());
         //taskPtr->setSharedPtr(taskPtr);
         
         // lock to avoid the  thread flag changes(service dll is stopped) until the task executed
         mMutexProcessTaskThread.lock();
         if( mFlagDiscoveryTaskProcessingThread != true)
         {
            break;
         }
         if(mDiscoveryLayerState == DISCOVERY_STARTING)
         {
            // Acquire lock 
            mMutexWaitingList.lock();
            mWaitingTaskList.push_back(taskPtr);
            mMutexWaitingList.unlock();
         }
         else 
         {
            taskPtr->execute();
            if(!taskPtr->succeeded())
            {
               onTaskComplete(taskPtr);
            }
         }
         mMutexProcessTaskThread.unlock();
         
         boost::this_thread::interruption_point();
      }
      catch(const boost::thread_interrupted&)
      {
         // Thread interruption request received, break the loop
         break;
      }
   }
   mTaskQueue.clear();
}

void DiscoveryManager::checkWaitingList()
{
   while(mFlagDiscoveryTaskProcessingThread)
   {
      try
      {
         // lock to avaoid the  thread flag changes until
         mMutexProcessTaskThread.lock();
         if( mFlagDiscoveryTaskProcessingThread != true)
         {
            
            break;
         }
         mMutexProcessTaskThread.unlock();
         for (TaskListIterator it = mWaitingTaskList.begin(); it != mWaitingTaskList.end(); )
         {
            if(isTimeToRetry(*it))
            {
               mMutexProcessTaskThread.lock();
               // task queue is already thread safe
               mTaskQueue.enqueue(*it);
               mMutexProcessTaskThread.unlock();

               // lock the waiting list cause main thread can me inserting new task at the same time
               mMutexWaitingList.lock();
               it = mWaitingTaskList.erase(it);
               mMutexWaitingList.unlock();

               continue;
            }
            ++it;
         }

         boost::this_thread::sleep(boost::posix_time::millisec(1500));
         boost::this_thread::interruption_point();
      }
      catch(const boost::thread_interrupted&)
      {
         // Thread interruption request received, break the loop
         break;
      }
   }
   mWaitingTaskList.clear();
}

// Operator() called by the thread
void DiscoveryManager::operator () ()
{
   processDiscoveryTasks();
   boost::this_thread::yield(); 
}

void DiscoveryManager::onTaskComplete(DiscoveryTaskSharedPtr discoveryTaskPtr)
{
   // even tough retry count is 0 we should get here maybe to log the error message
   // log the error code and info of the task
   int retryCount = discoveryTaskPtr->getRetryCount();
   if(retryCount == 0)
   {
      discoveryTaskPtr->onTaskCancelled();
      return;
   }
   
   discoveryTaskPtr->setRetryCount(--retryCount);
   if(isTimeToRetry(discoveryTaskPtr))
   {
      mTaskQueue.enqueue(discoveryTaskPtr);
   }
   else
   {
      // Acquire lock 
      mMutexWaitingList.lock();
      mWaitingTaskList.push_back(discoveryTaskPtr);
      mMutexWaitingList.unlock();
   }
   
}

void DiscoveryManager::OnStartFailed()
{
   mDiscoveryLayerState = DISCOVERY_INITIATED;
}

void DiscoveryManager::OnStarted()
{
   mDiscoveryLayerState = DISCOVERY_STARTED;
}

void DiscoveryManager::OnStarting()
{
   mDiscoveryLayerState = DISCOVERY_STARTING;
}
//void DiscoveryManager::onStop()
//{
//   // clean up
//
//   mMutexProcessTaskThread.lock();
//   mFlagDiscoveryTaskProcessingThread = false;
//   mMutexProcessTaskThread.unlock();
//   
//   mDiscoveryFactory->onDiscoveryLayerStopped();
//   mTaskQueue.clear();
//
//   //mThreads.join_all();
//   //mThreads.interrupt_all();
//     
//}

bool DiscoveryManager::isTimeToRetry(DiscoveryTaskSharedPtr discoveryTaskPtr)
{
   int nExecutionTickCount = discoveryTaskPtr->getExecutionTickCount();
   int nSpan = DiscoveryUtil::GetMilliSpan(nExecutionTickCount);
   int nSeconds = nSpan /1000;
   if((nSpan%1000) > 0) // round to the ceiling
   {
      ++nSeconds;
   }

   if(nSeconds > discoveryTaskPtr->getRetryInterval())
   {
      return true;
   }
   return false;
}


std::string DiscoveryManager::escapeServiceId(std::string id)
{
      std::string retval;
      retval = id;
      size_t found;
      do
      {
         found = retval.find(":");
         if (found != std::string::npos)
         {
            retval.replace(found, 1, "_", 1);
         }
      }while(found != std::string::npos);

      return retval;
}
