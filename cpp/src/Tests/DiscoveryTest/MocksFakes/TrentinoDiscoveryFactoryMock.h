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

#ifndef TrentinoDiscoveryFactoryMockH
#define TrentinoDiscoveryFactoryMockH

//test
#include "gmock/gmock.h" 

// specific 
#include "../../../Runtime/Discovery/TrentinoDiscoveryFactory.h"


// test specific
#include "TrentinoDiscoveryMethodInterfaceFake.h"

using namespace Trentino::Discovery;
using ::testing::_; 
using ::testing::Invoke; 
using ::testing::AtLeast;

namespace Trentino{
namespace Tests{
namespace Discovery
{
      

    //**********************************************************************************************
   //                             DiscoveryFactoryMock
   //**********************************************************************************************
   //! \ingroup Test::Discovery
   //! \brief 
   //**********************************************************************************************
   class DiscoveryFactoryMock :public DiscoveryManagementInterface
   { 
   public:   
      DiscoveryFactoryMock() 
      {     
         //// By default, all calls are delegated to the real object.     
         //ON_CALL(*this, stop())         
         //   .WillByDefault(Invoke(&DiscoveryFactory::getInstance(), &Foo::DoThis));     
         //ON_CALL(*this, DoThat(_))         .WillByDefault(Invoke(&real_, &Foo::DoThat));     ...   } 
      }
   public:
      MOCK_METHOD4(start,void(bool,int,int,onDiscoveryStartCBPtr));
      MOCK_METHOD0(stop,void());
      MOCK_METHOD0(getDiscoveryInterface, Trentino::Discovery::DiscoveryInterfacePtr());
         
   }; // class DiscoveryFactoryMock



    
}
}
}

#endif //TrentinoDiscoveryFactoryMockH