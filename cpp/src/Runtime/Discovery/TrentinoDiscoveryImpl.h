// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
// http://trentino.sourceforge.net/
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
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

#ifndef TrentinoDiscoveryImplH
#define TrentinoDiscoveryImplH

//standart
#include <boost/shared_ptr.hpp>
#include <list>
#include <boost/thread.hpp>

//specific
#include "TrentinoDiscoveryInterface.h"
#include "TrentinoDiscoveryTaskQueue.h"


namespace Trentino{
namespace Discovery
{
   class DiscoveryMethodInterface;
   class DiscoveryFactory;
   //class declaration
   //**********************************************************************************************
   //                             DiscoveryManager
   //**********************************************************************************************
   //! \ingroup Discovery
   //! \brief Generic impl of DiscoveryInterface to manage Discovery method independent features.
   //! This class wraps the discovery method specific dll that implements the DiscoveryMethodInterface. 
   //
   //! Implemented as singleton 
   //**********************************************************************************************
   class DiscoveryManager : public Trentino::Discovery::DiscoveryInterface
   {
      //additional
   public:
      typedef boost::shared_ptr<DiscoveryTask> DiscoveryTaskSharedPtr;
      //typedef void (DiscoveryImpl::*discoveryFrameWorkCBFuncPtr)(DiscoveryTaskSharedPtr);
      typedef void (*discoveryFrameWorkCBFuncPtr)(DiscoveryTaskSharedPtr);
   
   private:
      enum DISCOVERY_LAYER_STATES
      {
         DISCOVERY_NOT_INITIATED,
         DISCOVERY_INITIATED,
         DISCOVERY_STARTING,
         DISCOVERY_STARTED
      };
      //construction
   private:

      //****************************************************************************************
      //                                DiscoveryManager()
      //****************************************************************************************
      //! \brief Disallow construction.  
      //****************************************************************************************
      DiscoveryManager(); 

   private: // TODO why to have copy constructor and destructor private for thread as this class is a singleton
      //****************************************************************************************
      //                                ~DiscoveryManager()
      //****************************************************************************************
      //! \brief Disallow destruction.  
      //****************************************************************************************
      ~DiscoveryManager();

   private:
      ////****************************************************************************************
      ////                                DiscoveryManager()
      ////****************************************************************************************
      ////! \brief Disallow copy construction.  
      ////****************************************************************************************
      DiscoveryManager(const DiscoveryManager &);

      //operators
   private:
      
      ////****************************************************************************************
      ////                                operator=()
      ////****************************************************************************************
      ////! \brief Disallow assignment
      ////****************************************************************************************
      DiscoveryManager &operator=(const DiscoveryManager&);

 
      //services
   public:
      //****************************************************************************************
      //                                getDiscoveryInterface()
      //****************************************************************************************
      //! \brief Return a pointer to the DiscoveryInterface
      //****************************************************************************************
      static DiscoveryInterface* getDiscoveryInterface();

      //****************************************************************************************
      //                                getInstance()
      //****************************************************************************************
      //! \brief Returns an instance to DiscoveryImpl
      //! Returned instance is used by DiscoveryFactory mostly to assist DiscoveryManagement work
      //****************************************************************************************
      static DiscoveryManager* getInstance(void);

      //****************************************************************************************
      //                                start()
      //****************************************************************************************
      //! \brief Starts and initiates discovery related resources once discovery framework is 
      //! started via DiscoveryManagement interface
      //****************************************************************************************
      void start( bool isDA, 
         int retryCount, 
         int retryInterval, 
         onDiscoveryStartCBPtr discoveryTaskCB);

      //****************************************************************************************
      //                                stop()
      //****************************************************************************************
      //! \brief Stops and cleans up when discovery framework is stopped via DiscoveryManagement
      //! interface. This function is implemented sync. First of all it stops threads
      //! Then it executes the stop task on discovery method dll at most 5 times or until given
      //! retry count. Afterwars it notifies the dicovery factory for unloading dll
      //****************************************************************************************
      void stop(DiscoveryFactory* factory, bool isDA);

      //****************************************************************************************
      //                                setDiscoveryMethodInterface()
      //****************************************************************************************
      //! \brief Used to set the DiscoveryMethod interface implemented by the specific dll of the 
      //! currently actibve discovery method
      //****************************************************************************************
      void setDiscoveryMethodInterface(DiscoveryMethodInterface* methodInterface);
      
      void operator () ();

      //****************************************************************************************
      //                                onTaskComplete()
      //****************************************************************************************
      //! \brief Callback function to be triggered once the discovery task is accomplished.
      //! If the task is accomplished successfully the callback at runtime side is triggered by 
      //! the task if not the retry mechanism takes place via this function
      //! It was implemented static to be able to pass it to tasks as callback function in case
      //! of failure to manage retries. But now calback mechanism is not used but still, code
      //! passing this callback persists, so this function and all members used by it are kept 
      //! static until the full integration and testing is done.
      //! I am not changing now to be more flexible in a case requiring the callback mechanism again.
      //****************************************************************************************
      static void onTaskComplete(DiscoveryTaskSharedPtr discoveryTask);

      static void OnStartFailed();
      static void OnStarted();
      static void OnStarting();

      //management
   private:
      // implementation functions of TrentinoDiscoveryInterface can be publicly acced only via base interface
      // (see documentation in DiscoveryInterface)
      int registerService(std::string serviceIdentifier, ConstMetadataConstSharedPtr serviceAttributes, onDiscoveryTaskRegsiterCB registerCB);
      void deregisterService(std::string serviceIdentifier);
      int findService(std::string serviceIdentifier, 
         ConstMetadataConstSharedPtr serviceAttributes, 
        // listFoundServices& foundServices, 
         listFoundServices& foundServices,
         onDiscoveryTaskFindSrvCB onServiceFoundFn);

      //internal management functions

      //****************************************************************************************
      //                                processDiscoveryTasks()
      //****************************************************************************************
      //! \brief used to process the discovery tasks inserted to the discovery task que by the 
      //! user of DiscoveryInterface (runtime core)
      //****************************************************************************************
      void processDiscoveryTasks();

      static void checkWaitingList();

      //****************************************************************************************
      //                                onStop()
      //****************************************************************************************
      //! \brief Callback function to be triggered once the stop task is finsihed
      //! This function cleans up the discovery layer
      //****************************************************************************************
      static void onStop();

      //****************************************************************************************
      //                                isTimeToRetry()
      //****************************************************************************************
      //! \brief Checks out if the task is mature (retry interval has elapsed) to be retried
      //****************************************************************************************
       static bool isTimeToRetry(DiscoveryTaskSharedPtr discoveryTaskPtr);

       //****************************************************************************************
       //                                escapeServiceId()
       //****************************************************************************************
       //! \brief escapes invalid symbols in a given service Id. As the id the fully qualified class
       //! name is used, so the symbols to escape are mainly ::
       //****************************************************************************************
        static std::string escapeServiceId(std::string id);

      //data
   private:

      //! Static single instance of DiscoveryImp singleton
      static DiscoveryManager* mInstance;
      static bool mInstantiated;

      //! Thread-safe discovery task queue that keeps the tasks to be executed
      static DiscoveryTaskQueue mTaskQueue;

      //! Thread-safe discovery task queue that keeps the tasks that are in waiting state
      static std::list< boost::shared_ptr<DiscoveryTask> > mWaitingTaskList;
      typedef std::list< boost::shared_ptr<DiscoveryTask> >::iterator TaskListIterator;

      static boost::mutex mMutexWaitingList;
      static boost::mutex mMutexProcessTaskThread;
      //static boost::mutex mMutexWaitingListThread;

      //! Flag used to stop the threaded while loop of processDiscoveryTasks
      static bool mFlagDiscoveryTaskProcessingThread;
      
      //interface to the active discovery method dll
      //(dicovery method dlls implement DiscoveryMethodInterface)
      DiscoveryMethodInterface* mDiscoveryMethodInterface;

      static boost::thread_group mThreads;

      static Trentino::Discovery::DiscoveryFactory* mDiscoveryFactory;
      //void (DiscoveryImpl::*mDiscoveryFrameworkCB)(DiscoveryTaskSharedPtr);

      static DISCOVERY_LAYER_STATES mDiscoveryLayerState;

   }; // class DiscoveryImpl

 

} // namespace Discovery
} // namespace Trentino
#endif //TrentinoDiscoveryImplH
