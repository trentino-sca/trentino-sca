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

template<typename LIST> 
void ListWrapper<LIST>::deleterListType(ListType* listType)
{
   assert(listType != nullptr);
   ListType::deallocateListType(*listType);
}

template<typename LIST>
inline void expandToList(LIST& list, const ListType& listType)
{
   ListWrapper<LIST>::expandToList(list, listType);
}


template<typename LIST> 
inline const ListType ListWrapper<LIST>::extractFromList(const LIST& list)
{
   ListType listType = {
      static_cast<int>(list.size()),
      sizeof(typename LIST::value_type),
      malloc(list.size() * sizeof(typename LIST::value_type)),
      false,
      false,
   };

   int index = 0;
   if(listType.arrayOfInnerType != nullptr)
   {
      BOOST_FOREACH(const typename LIST::value_type& iter, list)
      {
         static_cast<typename LIST::value_type*>(listType.arrayOfInnerType)[index++] = iter;
      }
   }

   return listType;
}

template<> 
inline const ListType ListWrapper< std::list<std::string> >::extractFromList(
   const std::list<std::string>& list)
{
   ListType listType = {
      static_cast<int>(list.size()),
      sizeof(const char*),
      malloc(list.size() * sizeof(const char*)),
      true,
      false,
   };

   int index = 0;
   BOOST_FOREACH(const std::string& iter, list)
   {
      char** ptr = static_cast<char**>(listType.arrayOfInnerType);
      ptr[index] = static_cast<char*>(malloc(sizeof(std::string::value_type) * iter.size() + 1));
      strcpy_s(ptr[index], sizeof(std::string::value_type) * iter.size() + 1, iter.c_str());
      index++;
   }

   return listType;
}

template<> 
inline const ListType ListWrapper< std::list< std::list< std::string > > >::extractFromList(
   const std::list< std::list<std::string> >& list)
{
   ListType listType = {
      static_cast<int>(list.size()),
      sizeof(ListType),
      malloc(list.size() * sizeof(ListType)),
      false,
      true,
   };

   int index = 0;
   BOOST_FOREACH(const std::list<std::string>& iter, list)
   {
      ListType* ptr = static_cast<ListType*>(listType.arrayOfInnerType);
      ptr[index] = ListWrapper< std::list<std::string> >::extractFromList(iter);

      index++;
   }

   return listType;
}

template<typename LIST> 
inline void ListWrapper<LIST>::expandToList(LIST& list, const ListType& listType)
{
   assert(sizeof(typename LIST::value_type) == listType.sizeOfElement);
   assert(listType.arrayOfInnerType != nullptr);

   for(int i = 0; i < listType.count; ++i)
   {
      list.push_back(static_cast<typename LIST::value_type*>(listType.arrayOfInnerType)[i]);
   }
}

template<> 
inline void ListWrapper< std::list<std::string> >::expandToList(
    std::list<std::string>& list
   ,const ListType& listType)
{
   assert(sizeof(const char*) == listType.sizeOfElement);
   assert(listType.arrayOfInnerType != nullptr);

   for(int i = 0; i < listType.count; ++i)
   {
      list.push_back(std::string(static_cast<char**>(listType.arrayOfInnerType)[i]));
   }
}

template<> 
inline 
void ListWrapper< std::list< std::list<std::string> > >::expandToList(
    std::list< std::list< std::string> >& list
   ,const ListType& listType)
{
   assert(sizeof(ListType) == listType.sizeOfElement);

   assert(listType.arrayOfInnerType != nullptr);

   for(int i = 0; i < listType.count; ++i)
   {
      //! \todo Optimize insertion if necessary: Insert first and take reference to fill
      std::list<std::string> listToInsert;
      ListType* ptr = static_cast<ListType*>(listType.arrayOfInnerType);
      ListWrapper< std::list<std::string> >::expandToList(listToInsert, ptr[i]);
      list.push_back(listToInsert);
   }
}


template<typename LIST> 
inline ListWrapper<LIST>::ListWrapper(const LIST& list) : 
   mListType(new ListType(extractFromList(list)), deleterListType)
{
}

template<typename LIST> 
inline ListWrapper<LIST>::ListWrapper(const ListTypePtr& listType) : mListType(listType)
{
}

template<typename LIST> 
inline ListWrapper<LIST>::~ListWrapper()
{
}

template<typename LIST> 
const ListTypePtr& ListWrapper<LIST>::listType() const
{
   return mListType;
}

