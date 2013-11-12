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
#include "../../../Runtime/Discovery/TrentinoDiscoveryFactory.h"
#include "../../../Runtime/Discovery/TrentinoDiscoveryInterface.h"
#include "../../../Runtime/Discovery/TrentinoDiscoveryTaskStart.h"
#include "../../../Runtime/Discovery/TrentinoDiscoveryTaskRegister.h"
#include "../../../Runtime/Discovery/TrentinoDiscoveryTaskDeregister.h"
#include "../../../Runtime/Discovery/TrentinoDiscoveryTaskFindSrv.h"

// test specific
#include "TrentinoDiscoveryDiscoveryMethodFake.h"

using namespace Trentino::Discovery;
using ::testing::Return;
using ::testing::_;

namespace Trentino{
namespace Tests{
namespace Discovery
{
   
   DiscoveryMethodFake::DiscoveryMethodFake(bool startMethodExpectedResult)
      : mExpectedResult(startMethodExpectedResult) {}

   void DiscoveryMethodFake::start(DiscoveryTask*  taskStart) 
   {
      taskStart->setSucceeded(mExpectedResult);
   }

   void DiscoveryMethodFake::registerSrv(DiscoveryTask*  taskRegister) 
   {
      taskRegister->setSucceeded(mExpectedResult);
   }

   void DiscoveryMethodFake::deregisterSrv(DiscoveryTask*  taskDeregister) 
   {
      taskDeregister->setSucceeded(mExpectedResult);
   }

   void DiscoveryMethodFake::findSrv(DiscoveryTask*  taskFindSrv) 
   {
      taskFindSrv->setSucceeded(mExpectedResult);
   }

   
} // namespace Discovery
} // namespace Tests
} // namespace Trentino