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

//header
#include "TrentinoDiscoveryFactoryTest.h"
//standard
#include <gtest/gtest.h>
#include <string>

//specific
#include "./../../Runtime/Discovery/TrentinoDiscoveryFactory.h"
//standard
#pragma warning(push)
#pragma warning(disable:4273)
#include "./../../Runtime/Discovery/TrentinoDiscoveryInterface.h"
#include "./../../Runtime/SCAModel/TrentinoSCAModelMetadata.h"
#pragma warning(pop)


//test
#include "./MocksFakes/TrentinoDiscoveryFactoryMock.h"
#include "../../Runtime/Discovery/TrentinoDiscoveryImpl.h"

using namespace Trentino::Discovery;
using ::testing::Return; 

namespace Trentino{
namespace Tests{
namespace Discovery
{
   void DiscoveryFactoryTest::SetUp()
   {
      
   }

   void DiscoveryFactoryTest::callBack(bool f, std::string retVal)
   {
      f;
      retVal;
   }


   
  

} // namespace Discovery
} // namespace Tests
} // namespace Trentino