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

#ifndef TrentinoReflectionHelpersDefaultValueH
#define TrentinoReflectionHelpersDefaultValueH

//standard
#include <memory>

//specific
#include "./../../Global/TrentinoGlobal.h"
#include "TrentinoReflectionHelpersListType.h"

namespace Trentino{
namespace Reflection{      
//! \defgroup ReflectionHelpers
namespace Helpers
{

   //**********************************************************************************************
   //                              DefaultValue                               
   //**********************************************************************************************
   //! \ingroup ReflectionHelpers
   //! Returns specializations for type default values.
   //**********************************************************************************************
   template <typename TYPE> class DefaultValue
   {
   public:
      //*******************************************************************************************
      //                                    value()                               
      //*******************************************************************************************
      //! \brief Returns default value of specified type.
      //!
      //! Currently following types are supported:
      //! - signed/unsigned char
      //! - signed/unsigned short
      //! - signed/unsigned int
      //! - signed/unsigned long
      //! - signed/unsigned long long
      //! - float
      //! - double
      //! - const char*
      //! - void*
      //! \return Default value of type.
      //*******************************************************************************************
      static inline TYPE value();
   };


   #include "TrentinoReflectionHelpersDefaultValue.inl"

} //namespace Helpers
} //namespace Reflection
} //namespace Trentino


#endif //TrentinoReflectionHelpersDefaultValueH
