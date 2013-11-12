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

#ifndef TrentinoReflectionHelpersDefaultValueVariantH
#define TrentinoReflectionHelpersDefaultValueVariantH

//specific
#include "./../../Global/TrentinoGlobal.h"
#include "TrentinoReflectionHelpersDefaultValue.h"
#include "TrentinoReflectionHelpersVariant.h"

namespace Trentino{
namespace Reflection{      
namespace Helpers
{

   //class declaration
   //**********************************************************************************************
   //                          DefaultValueVariant                           
   //**********************************************************************************************
   //! Returns variant specializations for type default values
   //**********************************************************************************************
   template <typename TYPE> class DefaultValueVariant
   {
   public:
      //*******************************************************************************************
      //                                    value()                               
      //*******************************************************************************************
      //! \brief Returns default variant values of specified type.
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
      //! \return Variant of specific type.
      //*******************************************************************************************
      static inline Variant value();
   }; //template <typename TYPE> class DefaultValueVariant

   #include "TrentinoReflectionHelpersDefaultValueVariant.inl"

} //namespace Helpers
} //namespace Reflection
} //namespace Helpers


#endif //TrentinoReflectionHelpersDefaultValueVariantH
