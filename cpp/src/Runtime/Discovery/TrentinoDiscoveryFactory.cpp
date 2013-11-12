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
#include "TrentinoDiscoveryFactory.h"

//specific
#include "TrentinoDiscoveryImpl.h"
#include "TrentinoDiscoveryInterface.h"

using namespace Trentino::Discovery;
using Trentino::Utils::DynamicLibraryPtr;
using Trentino::Utils::DynamicLibrary;

//DiscoveryFactory DiscoveryFactory::mInstance;
DiscoveryFactory::DiscoveryMethod DiscoveryFactory::mDiscoveryMethod = SLP;
DiscoveryFactory* DiscoveryFactory::mInstance;
bool DiscoveryFactory::mInstantiated = false;

//functions
//**********************************************************************************************
//                           deleterDynamicLibraryUnloader()
//**********************************************************************************************
//! \brief Custom deleter used by boost::shared_pointer in order to automatically unload a 
//!        dynamic library as soons as the corresponding Trentino::Utils::DynamicLibrary object
//!        is destructed. 
//! \param[in] ptr Raw pointer to the Trentino::Utils::DynamicLibrary object.
//**********************************************************************************************
void deleterDynamicLibraryUnloader(DynamicLibrary* ptr)
{
   // HLOGGER();   
   assert(ptr != nullptr);

   if(ptr->isLoaded())
   {
      // once should be sufficient
      ptr->unload(DynamicLibrary::Once);
   }

   delete ptr;
}

/* Discovery Method factory constructor. 
Private, called by the singleton accessor on first call. 
Register the types of discovery methods here */
DiscoveryFactory::DiscoveryFactory()
   :mDiscoveryFrameworkState(NOT_STARTED)
{ 
   //Initially null will be filled up after the start method
   mDiscoveryInterface = nullptr;

   // Further Discovery methods will be registered here
   mDiscoveryMethodDllNames[SLP] = "DiscoverySlp";
} 

Trentino::Discovery::DiscoveryManagementInterface* DiscoveryFactory::getDiscoveryManagementInterface(
   DiscoveryFactory::DiscoveryMethod chosenDiscoveryMethod) 
{ 
   mDiscoveryMethod =  chosenDiscoveryMethod;
  
   if(mInstantiated == false)
   {
      mInstance = new DiscoveryFactory();
      mInstantiated = true;
   }
   return static_cast<DiscoveryManagementInterface*>(mInstance); 
} 


void DiscoveryFactory::start( bool isDA, 
   int retryCount, 
   int retryInterval, 
   onDiscoveryStartCBPtr discoveryLayerStartCB)
{ 
   // Altough the state of factory is STARTED probably the Start task returned 
   // negative to the runtime callback so runtime core is retrying to start it
   if(mDiscoveryFrameworkState == STARTED)
   {
      mDiscoveryDll.reset();
      mDiscoveryInterface = nullptr;
      mDiscoveryFrameworkState = NOT_STARTED;
   }

   DynamicLibraryPtr dll(new DynamicLibrary(mDiscoveryMethodDllNames[mDiscoveryMethod]), deleterDynamicLibraryUnloader);
   //DynamicLibraryPtr dll(new DynamicLibrary("DiscoverySlp"),deleterDynamicLibraryUnloader);
   dll->load();
   assert(dll->isLoaded()); 
   setDynamicLibrary(dll);

   // get the interface getter function from the dll
   const getDiscoveryMethodInterfaceFunc getDiscoveryMethodInterface =  
      mDiscoveryDll->functionAddress<getDiscoveryMethodInterfaceFunc>(GetDiscoveryMethodInterfaceFuncName);
   assert(getDiscoveryMethodInterface != nullptr);

   mDiscoveryInterface = DiscoveryManager::getDiscoveryInterface();

   mDiscoveryFrameworkState = STARTED;

   // pass the appropriate dll and initiate the impl
   DiscoveryManager::getInstance()->setDiscoveryMethodInterface(getDiscoveryMethodInterface());
   DiscoveryManager::getInstance()->start(isDA, retryCount, retryInterval, discoveryLayerStartCB);

}

void DiscoveryFactory::stop(bool isDA)
{ 
   // this call is sync for details check out the documentation of stop@DiscoveryManager
   DiscoveryManager::getInstance()->stop(mInstance, isDA);

   mDiscoveryDll->unload();
   mDiscoveryDll.reset();
   mDiscoveryInterface = nullptr;
   mDiscoveryFrameworkState = NOT_STARTED;
   delete mInstance;
}

void DiscoveryFactory::onDiscoveryLayerStopped()
{
   mDiscoveryDll->unload();
   mDiscoveryDll.reset();
   mDiscoveryInterface = nullptr;
   mDiscoveryFrameworkState = NOT_STARTED;
}

Trentino::Discovery::DiscoveryInterfacePtr DiscoveryFactory::getDiscoveryInterface() 
{
   if(mDiscoveryFrameworkState != STARTED)
   {
      assert(false);
   }

   return mDiscoveryInterface;
} 
