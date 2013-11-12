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

#ifndef TrentinoDiscoveryMethodFakeUnsucceedingH
#define TrentinoDiscoveryMethodFakeUnsucceedingH

//test
#include "gmock/gmock.h" 

//specific
#include "../../../Runtime/Discovery/TrentinoDiscoveryMethodInterface.h"

using namespace Trentino::Discovery;

namespace Trentino{
namespace Tests{
namespace Discovery
{
   // This class is imitating DiscoveryMetyhodInterface
   class DiscoveryMethodUnsucceedingFake : public DiscoveryMethodInterface 
   {
   public:
	   DiscoveryMethodUnsucceedingFake();
      void start(Trentino::Discovery::DiscoveryTask* taskStart);
      void stop(Trentino::Discovery::DiscoveryTask* taskStart);
      void registerSrv(Trentino::Discovery::DiscoveryTask* taskRegister);
      void deregisterSrv(Trentino::Discovery::DiscoveryTask* taskDeregister);
      void findSrv(Trentino::Discovery::DiscoveryTask* taskFindSrv);

   private:

   };
}
}
}

#endif //TrentinoDiscoveryMethodFakeUnsucceedingH