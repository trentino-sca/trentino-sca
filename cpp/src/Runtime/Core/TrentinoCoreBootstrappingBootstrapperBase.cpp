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
#include "TrentinoCoreBootstrappingBootstrapperBase.h"

//standard
#include <assert.h>

//specific
#include "../../Utils/TrentinoUtilsLogging.h"
#include "../Discovery/TrentinoDiscoveryActivator.h"

using namespace std;
using namespace Trentino::Utils;
using namespace Trentino::Core::Bootstrapping;


//class definition

//construction
BootstrapperBase::BootstrapperBase() : mInitialized(false), mStartUp(false)
{
   //does nothing here
}

BootstrapperBase::~BootstrapperBase()
{
   //safety only
   //assert(isInitialized() == false);
   //assert(isStartUp() == false);
}

   //services
void BootstrapperBase::startUp()
{
   if(mStartUp == false)
   {
      try
      {
         //calls only startup for now
         //we couldn´t call here trace log function, because logger will be initialized in
         //onStartup method
         //logTrace(__FUNCTION__": calling onStartup()");
         onStartUp();
         logTrace("%s: onStartup() called", __FUNCTION__);

         logInfo("Do a startup on all registered modules...");
         startUpAllModules();
      }
      catch (...)
      {
         logError("Error on startup occurred! One or more modules can´t be fully initialized");
         throw;
      }

      mStartUp = true;
   }
}
void BootstrapperBase::shutdown()
{
   if(mStartUp == true && mInitialized == false)
   {
      try
      {
         logInfo("Calling shutdown on all registered modules...");
         shutdownAllModules();
         
         logTrace("%s: Calling onShutdown()", __FUNCTION__);
         onShutdown();
      }
      catch (...)
      {
         logError
            ("Error during shutdown procedure occurred! One ore more modules can´t be shutdown properly");
         throw;
      }

      mStartUp = false;
   }
   else
   {
      logError("Can´t call shutdown(). State: startUp:%d, initialize:%d", mStartUp, mInitialized);
   }

}

void BootstrapperBase::run()
{
   if(mStartUp == true && mInitialized == true)
   {
      try
      {
         logTrace("%s: Calling onRun()", __FUNCTION__);
         onRun();
      }
      catch (...)
      {
         logError("Error calling onRun!");
         throw;
      }
   }
}

void BootstrapperBase::initialize()
{
   if(mInitialized == false && mStartUp == true)
   {
      try
      {
         logTrace("%s: calling onInitialize()", __FUNCTION__);
         onInitialize();

         logInfo("Initializing all modules...");
         initializeAllModules();
      }
      catch(...)
      {
         logError("Can´t initialize bootstrapper properly!");
         throw;
      }

      mInitialized = true;
   }
   else
   {
      logError("Can´t call intialize(). State: startUp:%d, initialize:%d", mStartUp, mInitialized);
   }
}

void BootstrapperBase::deinitialize()
{
   if(mInitialized == true)
   {
      try
      {
         logInfo("Deinitializing all modules...");
         deinitializeAllModules();

         logTrace("%s: Calling onDeinitialize()", __FUNCTION__);
         onDeinitialize();
         // stop discovery layer 
         Trentino::Discovery::DiscoveryActivator::instance()->stopDiscoveryActivator();
      }
      catch(...)
      {
         logError("Can´t deinitialize bootstrapper properly!");
         throw;
      }


      mInitialized = false;
   }
}

void BootstrapperBase::registerNewModule(const ModulePtr& module, bool automaticInitialization)
{

   //take to same level like the other modules
   if(automaticInitialization == true && isStartUp() == true)
   {
      try
      {
         if(false == module->isStartUp())
         {
            module->startUp();
            logInfo("Module: %s has done startup call.", module->name());
         }
      }
      catch(...)
      {
         logError("Can´t startup module: %s", module->name());
      }
   }

   if(automaticInitialization == true && isInitialized() == true)
   {
      try
      {
         if(false == module->isInitialized())
         {
            module->initialize();
            logInfo("Module: %s has done initialize call.", module->name());
         }
      }
      catch(...)
      {
         logError("Can´t initialize module: %s", module->name());
      }
   }

   mModules.push_back(module);
}

void BootstrapperBase::unregisterNewModule(const ModulePtr& module, bool automaticDeinitialization)
{
   //take to same level like the other modules
   if(automaticDeinitialization == true && isInitialized() == true)
   {
      try
      {
         module->deinitialize();
         logInfo("Module: %s was deinitialized.", module->name());
      }
      catch (...)
      {
         logError("Can´t deinitialize module: %s", module->name());
      }
   }

   if(automaticDeinitialization == true && isStartUp() == true)
   {
      try
      {
         module->shutdown();
         logInfo("Module: %s was shutdown.", module->name());
      }
      catch (...)
      {
         logError("Can´t shutdown module: %s", module->name());
      }
   }

   const std::vector< ModulePtr >::const_iterator listEnd = mModules.end();
   std::vector< ModulePtr >::iterator iter = mModules.begin();
   bool moduleFound = false;
   while(iter != listEnd)
   {
      if(iter->get() == module.get())
      {
         mModules.erase(iter);
         moduleFound = true;
         logInfo("Module: %s unregistered.", module->name());
         break;
      }
      ++iter;
   }

   if(moduleFound == false)
   {
      logWarn("Can´t find module: %s in modulelist!", module->name());
   }
}

bool BootstrapperBase::isInitialized() const
{
   return mInitialized;
}

bool BootstrapperBase::isStartUp() const
{
   return mStartUp;
}

void BootstrapperBase::onStartUp()
{
   //does nothing here
}

void BootstrapperBase::onShutdown()
{
   //does nothing here
}

void BootstrapperBase::onInitialize()
{
   //does nothing here
}

void BootstrapperBase::onDeinitialize()
{
   //does nothing here
}

void BootstrapperBase::onRun()
{
   //does nothing here
}


//management
void BootstrapperBase::deinitializeAllModules()
{
   const std::vector<ModulePtr>::const_iterator listEnd = mModules.end();
   std::vector<ModulePtr>::iterator iter = mModules.begin();

   // deinitialize all modules for safety
   while(iter != listEnd)
   {
      if((*iter)->isInitialized() == true)
      {
         (*iter)->deinitialize();
         assert((*iter)->isInitialized() == false);
      }
      ++iter;
   }
}

void BootstrapperBase::initializeAllModules()
{
   const std::vector<ModulePtr>::const_iterator listEnd = mModules.end();
   std::vector<ModulePtr>::iterator iter = mModules.begin();

   // deinitialize all modules for safety
   while(iter != listEnd)
   {
      if((*iter)->isInitialized() == false)
      {
         (*iter)->initialize();
         assert((*iter)->isInitialized() == true);
      }
      ++iter;
   }

}

void BootstrapperBase::startUpAllModules()
{
   const std::vector<ModulePtr>::const_iterator listEnd = mModules.end();
   std::vector<ModulePtr>::iterator iter = mModules.begin();

   // deinitialize all modules for safety
   while(iter != listEnd)
   {
      if((*iter)->isStartUp() == false)
      {
         (*iter)->startUp();
         assert((*iter)->isStartUp() == true);
      }
      ++iter;
   }
}

void BootstrapperBase::shutdownAllModules()
{
   const std::vector<ModulePtr>::const_iterator listEnd = mModules.end();
   std::vector<ModulePtr>::iterator iter = mModules.begin();

   // deinitialize all modules for safety
   while(iter != listEnd)
   {
      if((*iter)->isStartUp() == true)
      {
         (*iter)->shutdown();
         assert((*iter)->isStartUp() == false);
      }
      ++iter;
   }
}
