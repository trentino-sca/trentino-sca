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

#ifndef TrentinoReflectionHelpersListTypeH
#define TrentinoReflectionHelpersListTypeH

//standard
#include <boost/shared_ptr.hpp>
#include <cstring>

//specific
#include "./../../Utils/TrentinoUtilsTypeName.h"



namespace Trentino{
namespace Reflection{      
namespace Helpers
{
   //forward declarations
   template<typename LIST> class ListWrapper;

   //! ListType converted from a std::list<TYPE>
   struct ListType
   {
      template<typename LIST> friend class ListWrapper;
      //! Number of elements in list
      int count;
      //! Size of each single element.
      size_t sizeOfElement;
      //! Pointer to array of elements.
      void* arrayOfInnerType;
      //! Indicates a string
      bool mStringList;
      //! Indicates a embedded list
      bool mStringStringList;

      //management
   private:
      static inline void deallocateListType(ListType& listType);
      static inline void deallocateStrings(ListType& listType);

   };//struct ListType

   typedef boost::shared_ptr<ListType> ListTypePtr;

   #include "TrentinoReflectionHelpersListType.inl"
} //namespace Helpers
} //namespace Reflection
} //namespace Helpers

#endif//TrentinoReflectionHelpersListTypeH
