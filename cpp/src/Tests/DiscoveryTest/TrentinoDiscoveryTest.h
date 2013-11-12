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

#ifndef TrentinoDiscoveryTestH
#define TrentinoDiscoveryTestH

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
#include "./../../Runtime/Discovery/TrentinoDiscovery.h"
// test specific
#include "MocksFakes/TrentinoDiscoveryDiscoveryMethodFake.h"

using namespace Trentino::Discovery;
using ::testing::Return;
using ::testing::_;

namespace Trentino{
namespace Tests{
namespace Discovery
{
   
   class TrentinoDiscoveryTest : public ::testing::Test
   {
   public:
	  typedef boost::shared_ptr<Metadata> MetadataSharedPtr;
      TrentinoDiscoveryTest();

      static void frameworkCallback(DiscoveryTask::DiscoveryTaskSharedPtr& ptr);
      static void runtimeCallback(bool f, std::string retVal);
	  static void callBack(int nID, bool f, std::string retVal);
      static void startRelatedCB();
      void SetUp();

   public:
      static bool mIsRuntimeCallbackTriggered;

   protected:
	   static listFoundServices mFoundServices;
	   typedef boost::shared_ptr<DiscoveryTaskFindSrv> DiscoveryTaskFindSrvSharedPtr;
	   typedef boost::shared_ptr<DiscoveryTaskStart> DiscoveryTaskStartSharedPtr;
	   typedef boost::shared_ptr<DiscoveryTaskRegister> DiscoveryTaskRegisterSharedPtr;
	   typedef boost::shared_ptr<DiscoveryTaskDeregister> DiscoveryTaskDeregisterSharedPtr;
   };
   
} // namespace Discovery
} // namespace Tests
} // namespace Trentino
#endif //TrentinoDiscoveryTestH