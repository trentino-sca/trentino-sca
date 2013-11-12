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



#include "TrentinoDiscoveryFactoryFake.h"
#include "../../../Runtime/Discovery/TrentinoDiscoveryImpl.h"

using namespace Trentino::Tests::Discovery;

DiscoveryFactoryFake::FakeDiscoveryMethod DiscoveryFactoryFake::mFakeDiscoveryMethod = DUMMY_SUCCEEDING;
/* Discovery Method factory constructor. 
Private, called by the singleton accessor on first call. 
Register the types of discovery methods here */

DiscoveryFactoryFake::DiscoveryFactoryFake() 
{ 
   //Initially null will be filled up after the start method
   mDiscoveryInterface = nullptr;

   //Register(discoveryMethod, &DiscoverySLP::getDiscoveryInterface); 

   // Further Discovery methods will be registered here
   mDiscoveryMethodDllNames[SLP] = "DiscoverySlp";
} 



//void DiscoveryFactory::registerDiscoveryMethod(DiscoveryMethod discoveryMethod, GetDiscoveryInterfaceFn pfnCreate)
//{ 
//   m_FactoryMap[discoveryMethod]  = pfnCreate; 
//} 


void DiscoveryFactoryFake::start( bool isDA, 
   int retryCount, 
   int retryInterval, 
   onDiscoveryStartCBPtr discoveryTaskCB)
{ 
   // FAKE-ADD: Instead of loading the dll pass the dummy interface
   //if(mDiscoveryMethodFake == DUMMY_SUCCEEDING)
   //{
   //   DiscoveryImpl::getInstance().setDiscoveryMethodInterface(&mDiscoveryMethodFake);
   //}
   //else
   {
      DiscoveryManager::getInstance()->setDiscoveryMethodInterface(&mDiscoveryMethodUnsucceedingFake);
   }
   DiscoveryManager::getInstance()->start(isDA, retryCount, retryInterval, discoveryTaskCB);

  // m_FactoryMap[discoveryMethod]  = getDiscoveryInterface(); 
   mDiscoveryInterface = DiscoveryManager::getDiscoveryInterface();
}

void DiscoveryFactoryFake::stop( )
{ 
   //DiscoveryImpl::getInstance().stop();
}

Trentino::Discovery::DiscoveryInterfacePtr DiscoveryFactoryFake::getDiscoveryInterface() 
{
   //return mDiscoveryInterface();
   return mDiscoveryInterface;
} 

