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

#ifndef TrentinoReflectionDataMethodH
#define TrentinoReflectionDataMethodH

// specific
#include "./../../Global/TrentinoGlobal.h"

namespace Trentino{
namespace Reflection{
namespace Data{
namespace Method
{

   //! Function prototype/callback to call a method in your generated sourcecode.
   typedef void (TRENTINO_STDCALL *InvokeFuncPtr) (void* thisPtr, void* retVal, void* params[]);

   //**********************************************************************************************
   //                             Params
   //**********************************************************************************************
   //! \ingroup ReflectionRuntime
   //! Parameters structure is used to store a single parameter info of 
   //! a method.
   //**********************************************************************************************
   struct Param
   {
      //! Type of a parameter in a method, must be supported by \sa TypeName template.
      const char* type;
   }; //struct Params

   //**********************************************************************************************
   //                             MetaData
   //**********************************************************************************************
   //! \ingroup ReflectionRuntime
   //! \brief MetaData structure is used to hold all relevant information about
   //! a method which can be called by Invoke().
   //! This is the public POD data structure.
   //**********************************************************************************************
   struct MetaData
   {
      //! Name of method.
      const char* methodName;
      //! Type of method, must be supported by \sa TypeName template.
      const char* returnType;
      //! Array of parameters, see \sa Params for more info.
      const Param* params;
      //! Number of parameters.
      int paramsCount;
      //! Callback method which is called if you use Invoke(),
      //! see \sa methodInvoke.
      InvokeFuncPtr invoke;
   }; //struct MetaData

} //namespace Method
} //namespace Data
} //namespace Reflection
} //namespace Trentino

#endif //TrentinoReflectionDataMethodH
