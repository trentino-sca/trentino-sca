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

#ifndef TrentinoUtilsH
#define TrentinoUtilsH

//standard
#include <boost/shared_ptr.hpp>

//specific
#include "../Global/TrentinoGlobal.h"

//#ifdef WIN32
   struct _CrtMemState;
//#endif//WIN32

namespace Trentino{
//! \defgroup Utils
namespace Utils
{
   //**********************************************************************************************
   //                                  constantExpression<TYPE>()                               
   //**********************************************************************************************
   //! Returns a constant expression which can be optimized/removed in release builds.
   //! Use it instead of defining special macros
   //! \par Example: 
   //! You should not write on compiling level4 if(true == true) ..., 
   //! because l-value/r-value are constant
   //! you get a warning, so you can write:
   //! if(constantExpression<bool>(true) == true) ....
   //! \param[in] value Expression which should be returned 
   //! \return Parameter you have delivered
   //**********************************************************************************************
   template<class TYPE>
   inline TYPE constantExpression(const TYPE& value)
   {
      return value;
   }

   class DynamicLibrary;

   typedef boost::shared_ptr<DynamicLibrary> DynamicLibraryPtr;
//#ifdef WIN32
   typedef boost::shared_ptr<_CrtMemState> CrtMemStatePtr;
//#endif//WIN32

} //namespace Utils
} //namespace Trentino

#endif //TrentinoUtilsH
