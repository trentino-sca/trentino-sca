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

template < typename TYPE >
inline 
   RefCountingPointer<TYPE>::RefCountingPointer() : mPointer(nullptr)
{
}

template < typename TYPE >
inline 
   RefCountingPointer<TYPE>::RefCountingPointer(TYPE* ptr) : mPointer(ptr)
{
   TrentinoFuncPtrAddRef(mPointer);
}

template < typename TYPE >
inline 
   RefCountingPointer<TYPE>::RefCountingPointer(const RefCountingPointer& refPtr) : 
mPointer(refPtr.mPointer)
{
   if(mPointer != nullptr)
   {
      TrentinoFuncPtrAddRef(mPointer);
   }
}

template < typename TYPE >
inline
   RefCountingPointer<TYPE>::~RefCountingPointer()
{
   if(mPointer != nullptr)
   {
      TrentinoFuncPtrReleaseRef(mPointer);
   }
}   

template < typename TYPE >
inline
   TYPE& RefCountingPointer<TYPE>::operator* () const
{
   return *mPointer;
}

template < typename TYPE >
inline
   TYPE* RefCountingPointer<TYPE>::operator-> () const
{
   return mPointer;
}

template < typename TYPE >
inline
   bool RefCountingPointer<TYPE>::operator! () const
{
   return (mPointer == nullptr);
}

template < typename TYPE >
inline
   RefCountingPointer<TYPE>::operator void*() const
{
   return mPointer;
}

template < typename TYPE >
inline
   void RefCountingPointer<TYPE>::reset()
{
   ThisType().swap(*this);
}

template < typename TYPE >
inline
   void RefCountingPointer<TYPE>::reset(TYPE* ptr)
{
   ThisType(ptr).swap(*this);
}

template < typename TYPE >
inline
   TYPE* RefCountingPointer<TYPE>::get() const
{
   return mPointer;
}

template < typename TYPE >
inline
void RefCountingPointer<TYPE>::swap(RefCountingPointer& refPtr)
{
   TYPE* tmpPointer = mPointer;
   mPointer = refPtr.mPointer;
   refPtr.mPointer = tmpPointer;
}

template < typename TYPE >
inline
   RefCountingPointer<TYPE>& RefCountingPointer<TYPE>::operator= 
   (const RefCountingPointer& refPtr)
{
   ThisType(refPtr).swap(*this);
   return *this;
}

template < typename TYPE >
inline
   RefCountingPointer<TYPE>& RefCountingPointer<TYPE>::operator= (TYPE* refPtr)
{
   ThisType(refPtr).swap(*this);
   return *this;
}
