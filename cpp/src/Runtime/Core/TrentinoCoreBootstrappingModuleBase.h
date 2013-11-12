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

#ifndef TrentinoCoreBootstrappingModuleBaseH
#define TrentinoCoreBootstrappingModuleBaseH

//specific
#include "TrentinoCore.h"
#include "../../Global/TrentinoGlobal.h"

#ifdef WIN32
   #ifdef CORE_EXPORTS
      #define MODULE_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define MODULE_IMPORT_EXPORT __declspec(dllimport)       
   #endif //CORE_EXPORTS
#else
   #define MODULE_IMPORT_EXPORT
#endif //WIN32

namespace Trentino{
namespace Core{
namespace Bootstrapping
{
   //class declaration
   //**********************************************************************************************
   //                             ModuleBase
   //**********************************************************************************************
   //! \ingroup Bootstrapping
   //! \brief Represents a module that can be loaded and unloaded at runtime.
   //! ModuleBase can be used by boost::intrusive_ptr to monitor lifecycle of module.
   //! Modules can be also managed by StaticClass. In this case you don´t need any reference
   //! counting. 
   //**********************************************************************************************
   class ModuleBase
   {
      //construction
   public:
      //*******************************************************************************************
      //                            ModuleBase()
      //*******************************************************************************************
      //! \brief Default constructor.
      //*******************************************************************************************
      MODULE_IMPORT_EXPORT ModuleBase();

      //*******************************************************************************************
      //                            ~ModuleBase()
      //*******************************************************************************************
      //! \brief Destructor.
      //! Base destructor does nothing here. Lifecycle methods are called by bootstrapper and
      //! not by module itself.
      //*******************************************************************************************
      MODULE_IMPORT_EXPORT virtual ~ModuleBase();
      
      //service
   public:
      //*******************************************************************************************
      //                                     isStartUp()                               
      //*******************************************************************************************
      //! Determines if module has already called \sa startUp() method.
      //! \return Status of startup.
      //! \retval true, if startup is already executed.
      //! \retval false, if module is in shutdown state.
      //*******************************************************************************************
      virtual bool isStartUp() const = 0;


      //*******************************************************************************************
      //                                     moduleName()                               
      //*******************************************************************************************
      //! Returns specific modulename. Can be overridden.
      //! \return Name of module.
      //*******************************************************************************************
      MODULE_IMPORT_EXPORT  virtual const char* name() const;

      //*******************************************************************************************
      //                                     isInitialized()                               
      //*******************************************************************************************
      //! Determines if module has already called \sa initialize() method.
      //! \return Status of initialization.
      //! \retval true, if initialize is already executed.
      //! \retval false, if module is in deinitialized state.
      //*******************************************************************************************
      virtual bool isInitialized() const = 0;

      //*******************************************************************************************
      //                                     startUp()                               
      //*******************************************************************************************
      //! \brief Calls startup for the given module.
      //! Must be implemented by an override.
      //*******************************************************************************************
      virtual void startUp() = 0; 

      //*******************************************************************************************
      //                                     shutdown()                               
      //*******************************************************************************************
      //! \brief Calls shutdown for the given module.
      //! Must be implemented by an override.
      //*******************************************************************************************
      virtual void shutdown() = 0;

      //*******************************************************************************************
      //                                     initialize()                               
      //*******************************************************************************************
      //! \brief Calls initialize for the given module.
      //! Must be implemented by an override.
      //*******************************************************************************************
      virtual void initialize() = 0;

      //*******************************************************************************************
      //                                     deinitialize()                               
      //*******************************************************************************************
      //! \brief Calls deinitialize for the given module.
      //! Must be implemented by an override.
      //*******************************************************************************************
      virtual void deinitialize() = 0;

      //*******************************************************************************************
      //                                     addRef()                               
      //*******************************************************************************************
      //! Increments internal module reference.
      //! \return Number of references 
      //*******************************************************************************************
      MODULE_IMPORT_EXPORT unsigned long addRef();

      //*******************************************************************************************
      //                                     releaseRef()                               
      //*******************************************************************************************
      //! \brief Decrements internal module reference.
      //! Decrementing a module which has still no addref != 0 has no effect.
      //! If reference falls to 0, object will be destroyed and returned refcount is 0.
      //! \return Number of references 
      //*******************************************************************************************
      MODULE_IMPORT_EXPORT unsigned long releaseRef();

      //data
   private:
      //! Internal refcounter in order to achieve reference counting.
      unsigned long mRefCount;
   }; //class ModuleBase

} //namespace Bootstrapping
} //namespace Core
} //namespace Trentino

namespace
{
   //**********************************************************************************************
   //                               intrusive_ptr_add_ref()                               
   //**********************************************************************************************
   //! Increments internal module reference. Used by boost::intrusive_ptr.
   //**********************************************************************************************
   void intrusive_ptr_add_ref(Trentino::Core::Bootstrapping::ModuleBase* p);

   //**********************************************************************************************
   //                               intrusive_ptr_release()                               
   //**********************************************************************************************
   //! Decrements internal module reference. Used by boost::intrusive_ptr.
   //**********************************************************************************************
   void intrusive_ptr_release(Trentino::Core::Bootstrapping::ModuleBase* p);
   
   #include "TrentinoCoreBootstrappingModuleBase.inl"

} //namespace


#endif //TrentinoCoreBootstrappingModuleBaseH
