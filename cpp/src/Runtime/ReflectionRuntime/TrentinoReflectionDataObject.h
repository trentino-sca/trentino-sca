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

#ifndef TrentinoReflectionDataObjectH
#define TrentinoReflectionDataObjectH

// specific
#include "./../../Global/TrentinoGlobal.h"
#include "TrentinoReflectionDataMethod.h"

namespace Trentino{
namespace Reflection{
namespace Data{
namespace Object
{
   //! Function prototype/callback to call internal cast to get correct interface if you use
   //! multiple inheritance.
   typedef void* (TRENTINO_STDCALL *CastCallPtr) (void* thisPtr, const char* castInto);

   //**********************************************************************************************
   //                             MetaData
   //**********************************************************************************************
   //! \ingroup ReflectionRuntime
   //! \brief MetaData structure is used to hold all relevant information about
   //! an object. 
   //! This is the internal POD data structure.
   //**********************************************************************************************
   struct MetaData
   {
      //! Name of reflected class.
      const char* className;     
      //! Special cast call to convert into a specified interface
      CastCallPtr castCall;
      //! Method array, which contains all invocable methods in this class.
      Data::Method::MetaData* methods;
      //! Number of registered invocable methods.
      int methodCount;
   }; //struct MetaData

} //namespace Object
} //namespace Data
} //namespace Reflection
} //namespace Trentino


#endif //TrentinoReflectionDataObjectH


