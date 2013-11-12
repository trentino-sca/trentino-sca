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

#ifndef TrentinoReflectionHelpersListWrapperH
#define TrentinoReflectionHelpersListWrapperH

//standard
#include <memory>
#include <list>
#include <boost/foreach.hpp>


//specific
#include "TrentinoReflectionHelpersListType.h"
#include "./../../Utils/TrentinoUtilsTypeName.h"

namespace Trentino{
namespace Reflection{      
namespace Helpers
{

   //class declaration
   //**********************************************************************************************
   //                              ListWrapper    
   //**********************************************************************************************
   //! \ingroup ReflectionHelpers.
   //! \brief Resolves a std::list
   //**********************************************************************************************
   template<typename LIST>
   class ListWrapper
   {
      //construction
   public:
      //*******************************************************************************************
      //                              ListWrapper
      //*******************************************************************************************
      //! Constructs ListWrapper by given std::list template.
      //! \param[in] List to extract.
      //*******************************************************************************************
      ListWrapper(const LIST& list);

      //*******************************************************************************************
      //                              ListWrapper
      //*******************************************************************************************
      //! Constructs ListWrapper by given existing listtype.
      //! \param[in] ListType shared pointer to set
      //*******************************************************************************************
      explicit ListWrapper(const ListTypePtr& listType);

      //*******************************************************************************************
      //                              ~ListWrapper
      //*******************************************************************************************
      //! Destructor, destroys stored ListType structure recursively 
      //*******************************************************************************************
      ~ListWrapper();
      //services
   public:
      //*******************************************************************************************
      //                              extractFromList()
      //*******************************************************************************************
      //! Extract list into ListType Format
      //! Currently it is only one depth possible, except std::list<std::list<std::string>>
      //! \param[in] List to extract.
      //*******************************************************************************************
      static inline const ListType extractFromList(const LIST& list);

      //*******************************************************************************************
      //                              expandToList()
      //*******************************************************************************************
      //! Expands given ListType to list.
      //! You have to set given ListType as template parameter.
      //! \param[in] List to expand.
      //! \param[in] ListType to read from.
      //*******************************************************************************************
      static inline void expandToList(LIST& list, const ListType& listType);

      //*******************************************************************************************
      //                              listType()
      //*******************************************************************************************
      //! Returns stored ListType shared pointer member.
      //*******************************************************************************************
      const ListTypePtr& listType() const;
      //management
   private: 
      //*******************************************************************************************
      //                              deallocateStrings()
      //*******************************************************************************************
      //! Deallocates all strings in a given ListType parameter.
      //! \param[in] ListType which must be freed.
      //*******************************************************************************************
      static inline void deallocateStrings(ListType& listType);

      //*******************************************************************************************
      //                              deallocateListType()
      //*******************************************************************************************
      //! Deallocates all given ListTypes, works recursively with std::list<std::list<std::string>>
      //! \param[in] ListType which must be freed.
      //*******************************************************************************************
      static inline void deallocateListType(ListType& listType);

      static void TRENTINO_CDECL deleterListType(ListType* listType);
      //data
   private:
      //! Stored ListType shared pointer member
      ListTypePtr mListType;
   };//class ListWrapper

   //*******************************************************************************************
   //                              expandToList()
   //*******************************************************************************************
   //! Expands to a \sa std::list by a given \sa ListType.
   //! \param[in] List to fill.
   //! \param[in] ListType to extract from.
   //*******************************************************************************************
   template<typename LIST>
   static inline void expandToList(LIST& list, const ListType& listType);


   #include "TrentinoReflectionHelpersListWrapper.inl"

} //namespace Helpers
} //namespace Reflection
} //namespace Helpers

#endif//TrentinoReflectionHelpersListWrapperH
