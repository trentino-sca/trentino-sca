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

#ifndef TrentinoCoreBootstrappingRuntimeBootstrapperH
#define TrentinoCoreBootstrappingRuntimeBootstrapperH

//base class
#include "TrentinoCoreBootstrappingBootstrapperBase.h"

//standard
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

//specific
#include "TrentinoCore.h"
#include "TrentinoCoreDomain.h"
#include "TrentinoCoreRuntime.h"
#include "TrentinoCoreComponentCPPImplementationManager.h"
#include "TrentinoCoreContributionLoadingContributionLoader.h"
#include "TrentinoCoreComponentPropertyManager.h"
#include "./../../Utils/TrentinoUtilsPatternStaticClass.h"
#include "./../../Utils/TrentinoUtilsPatternFullImplCTorDTor.h"
#include "./../../Utils/TrentinoUtilsLoggingLogger.h"
#include "./../../Runtime/Invocation/TrentinoInvocationInvoker.h"
#include "../Binding/Impl/TrentinoBindingImplBindingManager.h"
#include "../ServiceRegistry/TrentinoServiceRegistryServiceRegistry.h"
#include "../Discovery/TrentinoDiscoveryActivator.h"
#include "../Discovery/TrentinoDiscoveryInterface.h"
#include "TrentinoCoreBootstrappingRuntimeBootstrapper.h"

namespace Trentino{
namespace Core{
namespace Bootstrapping
{
   class RuntimeConfiguration;
   //class declaration
   //**********************************************************************************************
   //                             RuntimeBootstrapper
   //**********************************************************************************************
   //! \ingroup Bootstrapping
   //! \brief Central class to achieve runtime bootstrapping to start/initialize and 
   //! deinitialize/shutdown corresponding modules.
   //! Modules can be registered directly in derived bootstrapper by using StaticClass 
   //! or to register/unregister dynamically by appropriate methods.
   //**********************************************************************************************
   class RuntimeBootstrapper : public BootstrapperBase
   {   
      //additional
   public:
      typedef boost::shared_ptr<const RuntimeConfiguration> RuntimeConfigurationConstPtr;
      typedef boost::shared_ptr<RuntimeConfiguration> RuntimeConfigurationPtr;
//      typedef boost::shared_ptr<Trentino::Discovery::DiscoveryActivator> DiscoveryActivatorPtr;
      typedef Trentino::Discovery::DiscoveryActivator* DiscoveryActivatorPtr;
      //! Full ctor/dtor construction type
      

      //construction
   public:
      //*******************************************************************************************
      //                            RuntimeBootstrapper()
      //*******************************************************************************************
      //! \brief Parameter configuration constructor.
      //! \param[in] Specific configuration to set
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT RuntimeBootstrapper(const RuntimeConfigurationConstPtr& configuration);

      //*******************************************************************************************
      //                            ~RuntimeBootstrapper()
      //*******************************************************************************************
      //! \brief Destructor.
      //! Destructor does still nothing here, because calling deinitialization and shutdown in
      //! constructor could cause exceptions, so we must call \sa shutdown() and
      //! deinitialize() manually.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT virtual ~RuntimeBootstrapper();

   private:
      //*******************************************************************************************
      //                            RuntimeBootstrapper()
      //*******************************************************************************************
      //! \brief Default constructor.
      //*******************************************************************************************
      RuntimeBootstrapper();

      //*******************************************************************************************
      //                RuntimeBootstrapper(const RuntimeBootstrapper&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copy construction.      
      //*******************************************************************************************
      RuntimeBootstrapper(const RuntimeBootstrapper&);

      //operators
   private:
      //*******************************************************************************************
      //                                     operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.      
      //*******************************************************************************************
      void operator=(const RuntimeBootstrapper&);

      //service
   public:
      //*******************************************************************************************
      //                                     invoker() 
      //*******************************************************************************************
      //! Returns an invoker instance, but beware: this instance is special and constructed
      //! with a specialized deleter.
      //! \return Shared pointer of an invoker.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT Trentino::Invocation::InvokerPtr invoker() const;

      //*******************************************************************************************
      //                           componentImplementationManager() 
      //*******************************************************************************************
      //! Returns a componentImplementationManager instance, but beware: 
      //! this instance is special and constructed with a specialized deleter.
      //! \return Shared pointer of a ComponentCPPImplementationManager.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT Trentino::Core::ComponentImplementationManagerBasePtr 
                                    componentImplementationManager() const;

      BOOTSTRAPPER_IMPORT_EXPORT Trentino::Core::ComponentPropertyManager& componentPropertyManager();

      //****************************************************************************************************
      //                                         bindingManagerBasePtr()
      //****************************************************************************************************
      //! \brief return the runtime wide Binding implementation manager
      //! \return BOOTSTRAPPER_IMPORT_EXPORT Trentino::Binding::BindingManagerBasePtr
      //****************************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT Trentino::Binding::BindingManagerBasePtr
                                    bindingManagerBasePtr() const;

      BOOTSTRAPPER_IMPORT_EXPORT Trentino::ServiceRegistry::ServiceRegistryPtr serviceRegistry() const;


      //*******************************************************************************************
      //                                     contributionLoader() 
      //*******************************************************************************************
      //! Returns a contributionLoader instance, but beware: 
      //! this instance is special and constructed with a specialized deleter.
      //! \return Shared pointer of a contributionLoader.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT 
         Trentino::Core::ContributionLoading::ContributionLoader& contributionLoader();

      //*******************************************************************************************
      //                             managementInterface() 
      //*******************************************************************************************
      //! Returns a an instance implementing the ManagementInterface, but beware: 
      //! this instance is special and constructed with a specialized deleter.
      //! \return Shared pointer to a RuntimeManagementInteface.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT Trentino::ManagementInterface&  
         managementInterface();
                           
      BOOTSTRAPPER_IMPORT_EXPORT Trentino::Core::Domain& domain();
                           

      BOOTSTRAPPER_IMPORT_EXPORT Trentino::Discovery::DiscoveryActivator* discoveryActivator() const;

      //*******************************************************************************************
      //                                        instance() 
      //*******************************************************************************************
      //! Returns instance of RuntimeBootstrapper
      //! \return Shared pointer of a ComponentCPPImplementationManager.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT static RuntimeBootstrapper& instance();

      //*******************************************************************************************
      //                                        configuration() 
      //*******************************************************************************************
      //! \return Shared pointer of Runtime configuration
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT RuntimeConfigurationConstPtr configuration() const;

      //management
   private:
      //*******************************************************************************************
      //                                     onStartUp()                               
      //*******************************************************************************************
      // override from BootstrapperBase (see documentation in BootstrapperBase)
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT virtual void onStartUp();

      //*******************************************************************************************
      //                                     onShutdown()                               
      //*******************************************************************************************
      // override from BootstrapperBase (see documentation in BootstrapperBase)
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT virtual void onShutdown();

      //*******************************************************************************************
      //                                     onInitialize()                               
      //*******************************************************************************************
      // override from BootstrapperBase (see documentation in BootstrapperBase)
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT virtual void onInitialize();

      //*******************************************************************************************
      //                                     onDeinitialize()                               
      //*******************************************************************************************
      // override from BootstrapperBase (see documentation in BootstrapperBase)
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT virtual void onDeinitialize();

      //data
   private:
      //! Central logger structure, to access by static class pattern.
      Trentino::Utils::Logging::Logger mLogger;

      //! Domain
      Trentino::Core::Domain mDomain;

      //! ComponentCPPImplementationManager
      boost::shared_ptr<Trentino::Core::ComponentImplementationManagerBase> mComponentImplementationManager;

      //! Invoker
      Trentino::Invocation::InvokerPtr mInvoker;

      //! ContributionLoader
      Trentino::Core::ContributionLoading::ContributionLoader mContributionLoader;

      //! ComponentPropertyManager
      Trentino::Core::ComponentPropertyManager mComponentPropertyManager;

      //! Runtime
      Trentino::Core::Runtime mRuntime;

      //! Singleton instance pointer
      static RuntimeBootstrapper* mBootstapper;

      //! Common configuration settings
      RuntimeConfigurationConstPtr mConfiguration;

      //! The BindingManager
      Trentino::Binding::BindingManagerBasePtr mBindingManager;

      //! The Service Registry
      Trentino::ServiceRegistry::ServiceRegistryPtr mServiceRegistry;

      //! Service discovery framework
//      Trentino::Discovery::DiscoveryInterface* mDiscoveryInterface;

      DiscoveryActivatorPtr mDiscoveryActivator;

   }; // class RuntimeBootstrapper

} //Bootstrapping
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreBootstrappingBootstrapperH
