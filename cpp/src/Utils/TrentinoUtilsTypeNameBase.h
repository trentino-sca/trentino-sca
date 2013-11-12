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

#ifndef TrentinoUtilsTypeNameBaseH
#define TrentinoUtilsTypeNameBaseH

//standard
#include <string>
#ifdef __GNUG__
   #include <cxxabi.h>
#endif

//specific
#include "./../Global/TrentinoGlobal.h"

namespace Trentino{
namespace Utils
{
   //class declaration
   //**********************************************************************************************
   //                              TypeNameBase                               
   //**********************************************************************************************
   //! \ingroup Utils
   //! \brief Baseclass for unmangling type by RTTI.
   //**********************************************************************************************
   class TypeNameBase
	{
	   //services
   public:
      //*******************************************************************************************
      //                                       unmangle()                               
      //*******************************************************************************************
      //! \brief Unmangles string if necessary from typeinfo
      //! \todo Unmangling is currently really neccessary, we don´t have any prefix-/suffix
      //! \todo in classes to unmangle.
      //!
      //! \param[in] Name of type to unmangle.
      //! \return Unmangled typename.
      //*******************************************************************************************
      static const char* unMangle(const char* nameFromTypeInfo);
	}; //class TypeNameBase

   #include "TrentinoUtilsTypeNameBase.inl"

} //namespace Utils
} //namespace Trentino


#endif //TrentinoUtilsTypeNameBaseH
