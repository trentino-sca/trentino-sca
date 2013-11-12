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

#ifndef TrentinoDiscoveryTaskH
#define TrentinoDiscoveryTaskH

// standart
#include <boost/thread.hpp>
#include <queue>
#include <string>

// specific
//#include "../../DiscoverySLP/TrentinoDiscoverySlp.h"
#include "../SCAModel/TrentinoSCAModelMetadata.h"


namespace Trentino{
namespace Discovery
{
   class DiscoveryManager;
   class DiscoveryMethodInterface;
   //class declaration
   //**********************************************************************************************
   //                             DiscoveryTask
   //**********************************************************************************************
   //! \ingroup Discovery
   //! \brief Discovery tasks are implemented here
   //
   //**********************************************************************************************
   class DiscoveryTask
   {
      //additional
   public:
      typedef boost::shared_ptr<Trentino::SCA::Model::Metadata> MetadataSharedPtr;
      typedef boost::shared_ptr<DiscoveryTask> DiscoveryTaskSharedPtr;
     // typedef void (DiscoveryImpl::*discoveryFrameWorkCBFuncPtr)(int);
      typedef void (*discoveryFrameWorkCBFuncPtr)(DiscoveryTaskSharedPtr);

      // friend becuase DiscoverySLP will be capable of using the member callbacks of the task
      //friend class Trentino::Discovery::SLP::OpenSLP::TrentinoDiscoverySlp;

      //construction
   public:
      DiscoveryTask(DiscoveryTask::discoveryFrameWorkCBFuncPtr funcPtr, 
                     int retryCount,
                     int retryInterval,
                     DiscoveryMethodInterface* methodInterface);

   protected: 

      //****************************************************************************************
      //                               ~DiscoveryTask()
      //****************************************************************************************
      //! \brief Virtual destructor of base class
      //****************************************************************************************
      virtual ~DiscoveryTask();

      // services
   public:

      //****************************************************************************************
      //                                ~execute()
      //****************************************************************************************
      //! \brief Execute method needs to be implemented by each derived class
      //****************************************************************************************
      virtual bool execute() = 0;

      void setRetryCount(int retrycount)
      {
         mRetryCount = retrycount;
      }

      int getRetryCount()
      {
         return mRetryCount;
      }
      
      void setRetryInterval(int retryInterval)
      {
         mRetryInterval = retryInterval;
      }

      int getRetryInterval()
      {
         return mRetryInterval;
      }
      
      void setExecutionTickCount(int executionTickCount)
      {
         mExecutionTickCount = executionTickCount;
      }

      int getExecutionTickCount()
      {
         return mExecutionTickCount;
      }

      void setSucceeded(bool stat)
      {
         mStatus = mStatus || stat;
      }

      bool succeeded()
      {
         return mStatus;
      }

      void setReturnVal(std::wstring returnVal)
      {
         //if task has succeeded at least once keep the returnval of success
         if(!mStatus)
         {
            mReturnValue.assign(returnVal.begin(),returnVal.end());
         }
      }

      void setReturnVal(std::string returnVal)
      {
         mReturnValue = returnVal;
      }

      std::string getReturnVal()
      {
         return mReturnValue;
      }

      void setSharedPtr (DiscoveryTaskSharedPtr taskSharedPtr)
      {
         mTaskPtr = taskSharedPtr.get();
      }

      int createID()
      {
         return mID++;
      }

      int getID()
      {
         return mTaskID;
      }



      //****************************************************************************************
      //                               onTaskCancelled()
      //****************************************************************************************
      //! \brief Once all the retries fail to call the runtimeCB with the last error
      //****************************************************************************************
      virtual void onTaskCancelled()
      {

      }

      static int mID;
      //data
   protected:
      //! Member that keeps teh left retry count for each task
      int mRetryCount;

      //! Member that keeps the retry interval bw retries
      int mRetryInterval;

      //! Keeps the recentExecution Tick Count
      int mExecutionTickCount;

      //! Keeps the return code of the task
      bool mStatus;

      std::string mReturnValue;

      //! Callback of DircoveryFramework to be triggered once the task is finished
      discoveryFrameWorkCBFuncPtr mDiscoveryFrameworkCB;

      //! Interface of the specific discovery method impl to be used for executing the task
      DiscoveryMethodInterface* mDiscoveryMethodInterface;

      //! Member to keep the shared pointer of the task to be able to pass the task to CB
      // needs to be a raw pointe since it is keeping a pointe to itself to be used by the
      // used Discovery dll
      DiscoveryTask* mTaskPtr;

      int mTaskID;

      
   }; // class DiscoveryTask


} // namespace Discovery
} // namespace Trentino
#endif //TrentinoDiscoveryTaskH
