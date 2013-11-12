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

#ifndef TrentinoReflectionRegistrationH
#define TrentinoReflectionRegistrationH

#ifdef WIN32
   #ifdef REFLECTIONRUNTIME_EXPORTS
      #define REGISTRATION_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define REGISTRATION_IMPORT_EXPORT __declspec(dllimport)       
   #endif //REFLECTIONRUNTIME_EXPORTS
   #else
      #define REGISTRATION_IMPORT_EXPORT
#endif //WIN32

//specific
#include "./../../Global/TrentinoGlobal.h"
#include "TrentinoReflectionIncludes.h"

namespace Trentino{
namespace Reflection
{
   //struct declaration
   //**********************************************************************************************
   //                             Registration
   //**********************************************************************************************
   //! \ingroup ReflectionRuntime
   //! \brief Supports (de)registration functions for generated c++ sourcecode
   //**********************************************************************************************
   struct Registration
   {
      REGISTRATION_IMPORT_EXPORT static void TRENTINO_STDCALL create();

      //*******************************************************************************************
      //                              registerMetaData()
      //*******************************************************************************************
      //! \brief Registers a new ReflectObject by using \sa Data::Object::MetaData POD structure.
      //! This is the external function which will be called by generated code.
      //*******************************************************************************************
      REGISTRATION_IMPORT_EXPORT static void TRENTINO_STDCALL 
         registerMetaData(Trentino::Reflection::DataRegistry& registry,Trentino::Reflection::Data::Object::MetaData& data);

      //*******************************************************************************************
      //                              unregisterMetaData()
      //*******************************************************************************************
      //! \brief Unregisters a new ReflectObject by using \sa Data::Object::MetaData POD structure.
      //! This is the external function which will be called by generated code.
      //*******************************************************************************************
      REGISTRATION_IMPORT_EXPORT static void TRENTINO_STDCALL 
         unregisterMetaData(Trentino::Reflection::DataRegistry& registry,Trentino::Reflection::Data::Object::MetaData& data);
   };

} //namespace Reflection
} //namespace Trentino


#endif //TrentinoReflectionRegistrationH