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


//global functions
inline unsigned long crc32(const std::string& name)
{
   boost::crc_32_type result;
   result.process_bytes(name.data(), name.length());
   return result.checksum();   
}

template <typename TYPE>
inline unsigned long classId( void )
{			
   static unsigned long classId = crc32(std::string(typeid(TYPE).name()));
   return classId;
}

template <typename TYPE, class CONSTRUCTION>
inline bool StaticClass< TYPE, CONSTRUCTION >::mustAllocateMemory() const
{
   return static_cast<bool>(CONSTRUCTION::allocateMemory);
}


//construction
template <typename TYPE, class CONSTRUCTION>
inline StaticClass< TYPE, CONSTRUCTION >::StaticClass() : mHashIndex(classId<TYPE>())
{
   void* memPtr = StaticMap::retainNamedMemory(mHashIndex);
   if (memPtr == nullptr && mustAllocateMemory() == true)
   {
      memPtr = malloc(sizeof(typename CONSTRUCTION::Type));

      //calling ::new(dataPtr) TYPE(); if correct CONSTRUCTION
      CONSTRUCTION::callCTor(static_cast<typename CONSTRUCTION::Type*>(memPtr));

      StaticMap::registerNamedMemory(mHashIndex, memPtr);
   }
   
   mData = static_cast<TYPE*>(memPtr);
}

template <typename TYPE, class CONSTRUCTION>
inline StaticClass< TYPE, CONSTRUCTION >::~StaticClass()
{
   //returns only a valid ptr if refcount == 0
   void* memPtr = StaticMap::releaseNamedMemory(mHashIndex);

   if (memPtr != nullptr)
   {
      // Simulating a "delete" here to allow private destructors by setting
      // friend to typename CONSTRUCTION class. 
      CONSTRUCTION::callDTor(static_cast<typename CONSTRUCTION::Type*>(memPtr));

      free(memPtr);
   }
}

//operators
template <typename TYPE, class CONSTRUCTION>
inline TYPE* StaticClass< TYPE, CONSTRUCTION >::operator-> () const
{
   return mData;      
}

template <typename TYPE, class CONSTRUCTION>
inline TYPE& StaticClass< TYPE, CONSTRUCTION >::operator* () const
{
   return *mData;
}

//service
template <typename TYPE, class CONSTRUCTION>
inline bool StaticClass< TYPE, CONSTRUCTION >::hasReference()
{
   unsigned long hashIndex = classId<TYPE>();
   return StaticMap::isNamedMemoryRegistered(hashIndex);
}

template <typename TYPE, class CONSTRUCTION>
inline TYPE* StaticClass< TYPE, CONSTRUCTION >::get() const
{
   return mData;
}
