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

#ifndef TrentinoCoreBootstrappingBootstrapperBaseH
#define TrentinoCoreBootstrappingBootstrapperBaseH

//standard
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <vector>

//specific
#include "../../Global/TrentinoGlobal.h"
#include "TrentinoCore.h"
#include "../../Utils/TrentinoUtilsPatternStaticClass.h"
#include "TrentinoCoreBootstrappingModuleBase.h"

#ifdef WIN32
   #ifdef CORE_EXPORTS
      #define BOOTSTRAPPER_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define BOOTSTRAPPER_IMPORT_EXPORT __declspec(dllimport)       
   #endif //CORE_EXPORTS
#else
   #define BOOTSTRAPPER_IMPORT_EXPORT
#endif //WIN32


//class declaration
namespace Trentino{
namespace Core{
namespace Bootstrapping
{
   //class declaration
   //**********************************************************************************************
   //                             BootstrapperBase
   //**********************************************************************************************
   //! \ingroup Bootstrapping
   //! \brief Central class to achieve bootstrapping to start/initialize and deinitialize/shutdown
   //!        corresponding modules.
   //! Modules can be registered directly in derived bootstrapper by using StaticClass 
   //! or to register/unregister dynamically by appropriate methods.
   //**********************************************************************************************
   class BootstrapperBase
   {
      //construction
   public:
      //*******************************************************************************************
      //                            BootstrapperBase()
      //*******************************************************************************************
      //! \brief Default constructor.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT BootstrapperBase();

      //*******************************************************************************************
      //                            ~BootstrapperBase()
      //*******************************************************************************************
      //! \brief Destructor.
      //! Destructor does still nothing here, because calling deinitialization and shutdown in
      //! constructor could cause exceptions, so we must call \sa shutdown() and
      //! deinitialize() manually.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT virtual ~BootstrapperBase();

      //service
   public:
      //*******************************************************************************************
      //                                     startUp()                               
      //*******************************************************************************************
      //! Calls startup for all modules and calls internal overridable 
      //! \sa onStartUp() method.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT void startUp();

      //*******************************************************************************************
      //                                     shutdown()                               
      //*******************************************************************************************
      //! Calls shutdown for all modules and calls internal overridable 
      //! \sa onShutdown() method.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT void shutdown();

      //*******************************************************************************************
      //                                     run()                               
      //*******************************************************************************************
      //! Calls run for all modules and calls internal overridable 
      //! \sa onRun() method.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT void run(); //mainloop etc

      //*******************************************************************************************
      //                                     initialize()                               
      //*******************************************************************************************
      //! Calls initialize for all modules and calls internal overridable 
      //! \sa onInitialize() method.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT void initialize();

      //*******************************************************************************************
      //                                     deinitialize()                               
      //*******************************************************************************************
      //! Calls deinitialize for all modules and calls internal overridable 
      //! \sa onDeinitialize() method.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT void deinitialize();

      //*******************************************************************************************
      //                                     registerNewModule()                               
      //*******************************************************************************************
      //! Registers a new dynamic module.
      //! \param[in] Module to register.
      //! \param[in] Indicates if new registered module should be automatically initialized.
      //! Default is false, user must do it outside.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT void registerNewModule( const ModulePtr& module,
                                                         bool automaticInitialization = false);

      //*******************************************************************************************
      //                                     unregisterNewModule()                               
      //*******************************************************************************************
      //! Unregisters a existing dynamic module.
      //! \param[in] Module to unregister.
      //! \param[in] Indicates if registered module should be automatically deinitialized.
      //! Default is false, user must do it outside.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT void unregisterNewModule( const ModulePtr& module,
                                                           bool automaticDeinitialization = false);

      //*******************************************************************************************
      //                                     isInitialized()                               
      //*******************************************************************************************
      //! Determines if bootstrapper has already called \sa initialize() method.
      //! \return Status of initialization.
      //! \retval true, if initialize is already executed.
      //! \retval false, if bootstrapper is in deinitialized state.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT bool isInitialized() const;

      //*******************************************************************************************
      //                                     isStartUp()                               
      //*******************************************************************************************
      //! Determines if bootstrapper has already called \sa startUp() method.
      //! \return Status of startup.
      //! \retval true, if startup is already executed.
      //! \retval false, if bootstrapper is in shutdown state.
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT bool isStartUp() const;


      //*******************************************************************************************
      //                                     module()
      //*******************************************************************************************
      //! Returns module of a specified type
      //! \return ModulePtr
      //*******************************************************************************************
      template< typename MODULE > ModulePtr module();

      //management
   protected:
      //*******************************************************************************************
      //                                     onStartUp()                               
      //*******************************************************************************************
      //! Can be overridden by derived class in order to startup custom structures. 
      //! Called by startUp().
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT virtual void onStartUp();

      //*******************************************************************************************
      //                                     onShutdown()                               
      //*******************************************************************************************
      //! Can be overridden by derived class in order to shutdown custom structures. 
      //! Called by shutdown().
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT virtual void onShutdown();

      //*******************************************************************************************
      //                                     onInitialize()                               
      //*******************************************************************************************
      //! Can be overridden by derived class in order to initialize custom structures. 
      //! Called by initialize().
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT virtual void onInitialize();

      //*******************************************************************************************
      //                                     onDeinitialize()                               
      //*******************************************************************************************
      //! Can be overridden by derived class in order to deinitialize custom structures. 
      //! Called by deinitialize().
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT virtual void onDeinitialize();

      //*******************************************************************************************
      //                                     onRun()                               
      //*******************************************************************************************
      //! Can be overridden by derived class in order to run custom structures. 
      //! Called by run().
      //*******************************************************************************************
      BOOTSTRAPPER_IMPORT_EXPORT virtual void onRun();

   private:
      //*******************************************************************************************
      //                                  initializeAllModules()                               
      //*******************************************************************************************
      //! Calls initialize() method from all modules
      //*******************************************************************************************
      void initializeAllModules();

      //*******************************************************************************************
      //                                  deinitializeAllModules()                               
      //*******************************************************************************************
      //! Calls deinitialize() method from all modules
      //*******************************************************************************************
      void deinitializeAllModules();

      //*******************************************************************************************
      //                                  startUpAllModules()                               
      //*******************************************************************************************
      //! Calls startUp() method from all modules
      //*******************************************************************************************
      void startUpAllModules();

      //*******************************************************************************************
      //                                  shutdownAllModules()                               
      //*******************************************************************************************
      //! Calls shutdown() method from all modules
      //*******************************************************************************************
      void shutdownAllModules();

      //data
   protected:
      //! Indicates that bootstrapper is initialized.
      bool mInitialized;

      //! Indicates that bootstrapper has done startup.
      bool mStartUp;
   private:
      //! Stored all registered  ModulePtr in a array/vector
      std::vector< ModulePtr > mModules; 
   }; //class BootstrapperBase

   #include "TrentinoCoreBootstrappingBootstrapperBase.inl"   

} //namespace Bootstrapping
} //namespace Core
} //namespace Trentino


#endif //TrentinoCoreBootstrappingBootstrapperBaseH
