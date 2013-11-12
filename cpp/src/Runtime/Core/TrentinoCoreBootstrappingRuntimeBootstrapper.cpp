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
#include "TrentinoCoreBootstrappingRuntimeBootstrapper.h"

//standard
#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include <boost/foreach.hpp>
#include <boost/smart_ptr.hpp>

//specific 
#include "TrentinoCoreBootstrappingRuntimeConfiguration.h"

#ifdef TRENTINO_LOGGING
   #include "./../../Utils/TrentinoUtilsLoggingLog4CPlus.h"
#endif//TRENTINO_LOGGING

#include "./../../Utils/TrentinoUtilsLogging.h"
#include "./../../Runtime/Invocation/TrentinoInvocationInvoker.h"
#include "./../ReflectionRuntime/TrentinoReflectionRegistration.h"
#include "./../RuntimeModel/TrentinoRuntimeModel.h"
#include "../Binding/Impl/TrentinoBindingImplBindingManager.h"
#include "../Discovery/TrentinoDiscoveryFactory.h"
#include "../Discovery/TrentinoDiscoveryActivator.h"


using namespace std;
using namespace Trentino::Utils;
using namespace Trentino::Utils::Logging;
using namespace Trentino::Core::Bootstrapping;
using namespace Trentino::Invocation;
using namespace Trentino::Core;
using namespace Trentino::Core::Bootstrapping;
namespace RuntimeModel = Trentino::RuntimeModel;

//global functions
void deleterInvoker(InvokerBase* /*ptr*/)
{
   // we don?t delete any invoker here, Bootstrapper is responsible to destroy invoker here
}

void deleterComponentImplementationManager(ComponentImplementationManagerBase* /*ptr*/)
{
   // we don?t delete any ComponentImplementationManager here, 
   // Bootstrapper is responsible to destroy ComponentImplementationManager here
}

void deleterBindingManager(Trentino::Binding::BindingManagerBase* /*ptr*/)
   {
   // we don?t delete any BindingManagerBase here, 
   // Bootstrapper is responsible to destroy BindingManagerBase here
   }

void deleterServiceRegistry(Trentino::ServiceRegistry::ServiceRegistryBase* /*ptr*/)
{
// We dont delete the Service registry. The Bootstrapper will delete it 
}

void deleterContributionLoader(ContributionLoading::ContributionLoader* /*ptr*/)
{
   // we don?t delete ContributionLoader here, 
   // Bootstrapper is responsible to destroy ContributionLoader here
}

void deleterManagementInterface(Trentino::ManagementInterface* /*ptr*/)
{
   // we don?t delete any ManagementInterface here, 
   // Bootstrapper is responsible to destroy the ManagementInterface 
}

//globals
RuntimeBootstrapper* RuntimeBootstrapper::mBootstapper = nullptr;


//class definition

//construction
RuntimeBootstrapper::RuntimeBootstrapper()
{
   assert(false); //must not be called!
}

RuntimeBootstrapper::RuntimeBootstrapper(
   const RuntimeBootstrapper::RuntimeConfigurationConstPtr& configuration) 
: mConfiguration(configuration)
{
   Trentino::Reflection::Registration::create();

   //order sensitive !
   //mLogger.reset(new LoggerStaticClassPtr);
   //mComponentPropertyManager.reset(new ComponentPropertyManagerStaticClassPtr);
   mComponentImplementationManager.reset(new ComponentCPPImplementationManager);
   mInvoker.reset(new Invoker);
   //mContributionLoader.reset(new ContributionLoaderStaticClassPtr);
   //mRuntime.reset(new RuntimeStaticClassPtr);
   //mDomain.reset(new DomainStaticClassPtr);
   mBootstapper = this;
   mBindingManager.reset(new Trentino::Binding::Impl::BindingManager);
   mServiceRegistry.reset(new Trentino::ServiceRegistry::ServiceRegistry);
   mDiscoveryActivator = Trentino::Discovery::DiscoveryActivator::instance();
   mDiscoveryActivator->startDiscoveryActivator();
}

RuntimeBootstrapper::~RuntimeBootstrapper()
{
   //!\todo unique_ptr order...
   mBindingManager.reset();
   //mDomain.reset();
   //mContributionLoader.reset();
   mInvoker.reset();
   mComponentImplementationManager.reset();
   //mComponentPropertyManager.reset();
   mServiceRegistry.reset();
}

//service
InvokerPtr RuntimeBootstrapper::invoker() const
{
   //return InvokerPtr((*mInvoker).get(), deleterInvoker);
   return mInvoker;
}

ComponentImplementationManagerBasePtr RuntimeBootstrapper::componentImplementationManager() const
{
 return mComponentImplementationManager;
}

Trentino::Core::ComponentPropertyManager& RuntimeBootstrapper::componentPropertyManager()
{
  return mComponentPropertyManager;
}

Trentino::Discovery::DiscoveryActivator* RuntimeBootstrapper::discoveryActivator() const
{
   return mDiscoveryActivator;
}

BOOTSTRAPPER_IMPORT_EXPORT Trentino::Binding::BindingManagerBasePtr RuntimeBootstrapper::bindingManagerBasePtr() const
   {
    // return Trentino::Binding::BindingManagerBasePtr((*mBindingManager).get(), deleterBindingManager);
     return mBindingManager;
   }

BOOTSTRAPPER_IMPORT_EXPORT Trentino::ServiceRegistry::ServiceRegistryPtr RuntimeBootstrapper::serviceRegistry() const
   {
      //return Trentino::ServiceRegistry::ServiceRegistryPtr ((*mServiceRegistry).get(), deleterServiceRegistry);
      return mServiceRegistry;
   }

BOOTSTRAPPER_IMPORT_EXPORT RuntimeBootstrapper::RuntimeConfigurationConstPtr RuntimeBootstrapper::configuration() const
   {
    return mConfiguration;
   }


RuntimeBootstrapper& RuntimeBootstrapper::instance()
{
   return *mBootstapper;
}

Trentino::Core::ContributionLoading::ContributionLoader& RuntimeBootstrapper::contributionLoader()
{
   //return ContributionLoading::ContributionLoaderPtr((*mContributionLoader).get(), deleterContributionLoader);
   return mContributionLoader;
}


Trentino::Core::Domain& RuntimeBootstrapper::domain()
{
   return mDomain;
}

Trentino::ManagementInterface& RuntimeBootstrapper::managementInterface()
{
   //return ManagementInterfacePtr(&(*(*mDomain)).managementInterface(), deleterManagementInterface);
   return mDomain.managementInterface();
}


//service
void RuntimeBootstrapper::onStartUp()
{
   //default logger with basic configuration and no! namespace
   //\todo Add appropriate namespace for loggers
   std::string str = mConfiguration->log4cplusConfigFilePath();
   Logger::ConfigDesc config = 
      { nullptr, str.c_str(), nullptr };
   Logger::setup(Logger::SetupLogger, &config);
   logInfo("Starting logger...");

   mDomain.setup(mConfiguration->domainURI());
}

void RuntimeBootstrapper::onShutdown()
{
}

void RuntimeBootstrapper::onInitialize()
{  
   //(*(*mDomain)).registerLocalRuntime(*(*mRuntime.get()));
    mDomain.registerLocalRuntime(mRuntime);
   //(*(*mInvoker)).setComponentImplementationManager(componentImplementationManager());
   Trentino::Invocation::Invoker* val= static_cast<Trentino::Invocation::Invoker*>(mInvoker.get());
   val->setComponentImplementationManager(componentImplementationManager());


   std::map <std::string, std::string> cntrb = mConfiguration->autoLoadContributions();
   if( !cntrb.empty()  )
    {
       logInfo("Autoloading contributions:");
       for(std::map<std::string, std::string>::iterator iter = cntrb.begin(); iter != cntrb.end(); ++iter )
       {
          std::string uri = iter->first;
          std::string path = iter->second;
         // uri = cntrb[i].substr(0, cntrb[i].find_first_of("|"));
         // path = cntrb[i].substr( cntrb[i].find_first_of("|")+1, cntrb[i].length());
          
          logInfo("%s as %s", path.c_str(), uri.c_str());
          std::string error = mDomain.managementInterface().install(path, uri);
          if (error.empty())
          {
             error = mDomain.managementInterface().deploy(uri);
          }
          
          if(!error.empty()){ logInfo("Contribution loading %s FAILED",uri.c_str() ) }
       }
    }
}

void RuntimeBootstrapper::onDeinitialize()
{   
   mBindingManager->stop();
   //propertly remove all the contributions from the runtime
   BOOST_FOREACH(const RuntimeModel::ContributionPtr contribution, mRuntime.contributions())
   {
      try 
      {
         mContributionLoader.remove(contribution);
      }
      catch(exception& e)
      {
         logError(e.what());
      }
      catch(...)
      {
         logError("Unexpected exception thrown by ContributionLoader::remove()");
      }
   }
   
   mDomain.unregisterLocalRuntime();   
}
