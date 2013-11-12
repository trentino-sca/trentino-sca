// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2013
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


//standard
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>

//specific
#include "./../../Runtime/Discovery/TrentinoDiscoveryFactory.h"
#include "./../../Runtime/Discovery/TrentinoDiscoveryInterface.h"
#include "./../../Runtime/Discovery/TrentinoDiscoveryTaskStart.h"
#include "./../../Runtime/Discovery/TrentinoDiscoveryTaskRegister.h"
#include "./../../Runtime/Discovery/TrentinoDiscoveryTaskDeregister.h"
#include "./../../Runtime/Discovery/TrentinoDiscoveryTaskFindSrv.h"
#include "./../../Runtime/Discovery/TrentinoDiscoveryTaskQueue.h"

// test specific
#include "MocksFakes/TrentinoDiscoveryDiscoveryMethodFake.h"
#include "TrentinoDiscoveryTest.h"

using namespace Trentino::Discovery;
using ::testing::Return;
using ::testing::_;

namespace Trentino{
namespace Tests{
namespace Discovery
{
   
   listFoundServices TrentinoDiscoveryTest::mFoundServices;
   bool TrentinoDiscoveryTest::mIsRuntimeCallbackTriggered = false;
   TrentinoDiscoveryTest::TrentinoDiscoveryTest() {}

   void TrentinoDiscoveryTest::callBack(int nID, bool f, std::string retVal)
   {
      nID;
      f;
      retVal;
	  mIsRuntimeCallbackTriggered = true;
      //TODO write the asserts here
   }

   void TrentinoDiscoveryTest::frameworkCallback(DiscoveryTask::DiscoveryTaskSharedPtr& ptr)
   {
      ptr;
   }

   void TrentinoDiscoveryTest::runtimeCallback(bool f, std::string retVal)
   {
      f; 
	  retVal;
      mIsRuntimeCallbackTriggered = true;
   }

   void TrentinoDiscoveryTest::startRelatedCB()
   {
      
   }

   void TrentinoDiscoveryTest::SetUp()
   {
	  mFoundServices.clear();
      mIsRuntimeCallbackTriggered = false;
   }

   //===============================================

   TEST_F(TrentinoDiscoveryTest, discovery_task_start_execute_results_true_runtime_callback_expected)
   {
      DiscoveryMethodFake discoveryMethodFake(true);
      DiscoveryTaskStart::startRealtedCB startRealtedFuncPtr =   &TrentinoDiscoveryTest::startRelatedCB;
      DiscoveryTaskStartSharedPtr discoveryTaskStart(new DiscoveryTaskStart((DiscoveryTask::discoveryFrameWorkCBFuncPtr)&frameworkCallback,
         0,
         0,
         &discoveryMethodFake,
         &runtimeCallback,
         startRealtedFuncPtr,
         startRealtedFuncPtr,
         startRealtedFuncPtr));
      discoveryTaskStart->setSharedPtr(discoveryTaskStart);
      discoveryTaskStart->execute();
      
      EXPECT_TRUE(discoveryTaskStart->succeeded());
   }

   //===============================================

   TEST_F(TrentinoDiscoveryTest, discovery_task_register_execute_results_true_no_callback_expected)
   {
      DiscoveryMethodFake discoveryMethodFake(true);
      MetadataSharedPtr serviceData (new Metadata());
      //DiscoveryTaskRegister discoveryTaskRegister((DiscoveryTask::discoveryFrameWorkCBFuncPtr)&frameworkCallback, 0, 0, &discoveryMethodFake, "", serviceData, &callBack);
      DiscoveryTaskRegisterSharedPtr discoveryTaskRegister(new DiscoveryTaskRegister((DiscoveryTask::discoveryFrameWorkCBFuncPtr)&frameworkCallback, 0, 0, &discoveryMethodFake, "", serviceData, &callBack));
      discoveryTaskRegister->setSharedPtr(discoveryTaskRegister);
      discoveryTaskRegister->execute();
      
	  EXPECT_TRUE(discoveryTaskRegister->succeeded());
   }

   //===============================================

   TEST_F(TrentinoDiscoveryTest, discovery_task_deregister_execute_results_true_no_callback_expected)
   {
      DiscoveryMethodFake discoveryMethodFake(true);
      //DiscoveryTaskDeregister discoveryTaskDeregister((DiscoveryTask::discoveryFrameWorkCBFuncPtr)&frameworkCallback, 0, 0, &discoveryMethodFake, "");
      DiscoveryTaskDeregisterSharedPtr discoveryTaskDeregister(new DiscoveryTaskDeregister((DiscoveryTask::discoveryFrameWorkCBFuncPtr)&frameworkCallback, 0, 0, &discoveryMethodFake, ""));
      discoveryTaskDeregister->setSharedPtr(discoveryTaskDeregister);
      discoveryTaskDeregister->execute();
      
      EXPECT_TRUE(discoveryTaskDeregister->succeeded());
   }

   //===============================================

   TEST_F(TrentinoDiscoveryTest, discovery_task_findsrv_execute_results_true_runtime_callback_expected)
   {
      DiscoveryMethodFake discoveryMethodFake(true);
      MetadataSharedPtr serviceData (new Metadata());
      //DiscoveryTaskFindSrv discoveryTaskFindSrv((DiscoveryTask::discoveryFrameWorkCBFuncPtr)&frameworkCallback, 0, 0, &discoveryMethodFake, "", serviceData, &callBack, mFoundServices);
	  DiscoveryTaskFindSrvSharedPtr discoveryTaskFindSrv(new DiscoveryTaskFindSrv((DiscoveryTask::discoveryFrameWorkCBFuncPtr)&frameworkCallback,
        0,
        0,
        &discoveryMethodFake,
        "",
        serviceData,
        &callBack,
        &mFoundServices) );
	  discoveryTaskFindSrv->setSharedPtr(discoveryTaskFindSrv);
      discoveryTaskFindSrv->execute();
      
      EXPECT_TRUE(discoveryTaskFindSrv->succeeded());
   }

   TEST_F(TrentinoDiscoveryTest, discovery_task_queue_enqueue_nonempty_queue_expected)
   {
      DiscoveryMethodFake discoveryMethodFake(true);
      DiscoveryTaskQueue discoveryTaskQueue;
      DiscoveryTaskStart::startRealtedCB startRealtedFuncPtr =   &TrentinoDiscoveryTest::startRelatedCB;
      discoveryTaskQueue.enqueue((DiscoveryTask::DiscoveryTaskSharedPtr)(new DiscoveryTaskStart((DiscoveryTask::discoveryFrameWorkCBFuncPtr)&frameworkCallback,
         0,
         0,
         &discoveryMethodFake,
         &runtimeCallback,
         startRealtedFuncPtr,
         startRealtedFuncPtr,
         startRealtedFuncPtr)));

      EXPECT_FALSE(discoveryTaskQueue.empty());
   }

   TEST_F(TrentinoDiscoveryTest, discovery_task_queue_clear_empty_queue_expected)
   {
      DiscoveryMethodFake discoveryMethodFake(true);
      DiscoveryTaskQueue discoveryTaskQueue;
     DiscoveryTaskStart::startRealtedCB startRealtedFuncPtr =   &TrentinoDiscoveryTest::startRelatedCB;
      discoveryTaskQueue.enqueue((DiscoveryTask::DiscoveryTaskSharedPtr)(new DiscoveryTaskStart((DiscoveryTask::discoveryFrameWorkCBFuncPtr)&frameworkCallback,
         0,
         0,
         &discoveryMethodFake,
         &runtimeCallback,
         startRealtedFuncPtr,
         startRealtedFuncPtr,
         startRealtedFuncPtr)));
      discoveryTaskQueue.clear();

      EXPECT_TRUE(discoveryTaskQueue.empty());
   }


} // namespace Discovery
} // namespace Tests
} // namespace Trentino