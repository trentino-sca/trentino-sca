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
 
#ifndef Oasis_sca_RefCountingPointerH
#define Oasis_sca_RefCountingPointerH

//standard
#include <cstddef>

//specific
//CAUTION. since this code is public, using releative paths break some working applications
#include <Global/TrentinoGlobal.h>

namespace oasis{
namespace sca 
{

   //class declaration
   //**********************************************************************************************
   //                             RefCountingPointer                          
   //**********************************************************************************************
   //! \brief A smart pointer that uses intrusive reference counting.
   //! Relies on unqualified calls to 
   //! void TrentinoFuncPtrAddRef(TYPE* pPointer);
   //! and
   //! void TrentinoFuncPtrReleaseRef(TYPE* pPointer);
   //! (pPointer != 0).
   //! The object is responsible for destroying itself.
   //! The RefCountingPointer class template stores a pointer to an object with an embedded 
   //! reference count.
   //! Every new intrusive_ptr instance increments the reference count by using an unqualified call 
   //! to the function TrentinoFuncPtrAddRef,
   //! passing it the pointer as an argument. Similarly, when an RefCountingPointer is destroyed,
   //! it calls TrentinoFuncPtrReleaseRef; 
   //! this function is responsible for destroying the object when its reference count drops to zero.
   //! The user is expected to provide suitable definitions of these two functions.
   //! On compilers that support argument-dependent lookup, 
   //! TrentinoFuncPtrAddRef and TrentinoFuncPtrReleaseRef should be defined in the namespace 
   //! that corresponds to their parameter.
   //**********************************************************************************************
   template <typename TYPE>
   class RefCountingPointer
   {
      //additional
   private:
      //! Own type of template
      typedef RefCountingPointer ThisType;
   public:
      //! Element type: TYPE
      typedef TYPE ElementType;

      //construction
   public:
      //*******************************************************************************************
      //                                     RefCountingPointer()                               
      //*******************************************************************************************
      //! Default constructor.
      //*******************************************************************************************
      RefCountingPointer();

      //*******************************************************************************************
      //                                     RefCountingPointer()                               
      //*******************************************************************************************
      //! Assignment constructor.
      //*******************************************************************************************
	   RefCountingPointer(TYPE* ptr);

      //*******************************************************************************************
      //                                     RefCountingPointer()                               
      //*******************************************************************************************
      //! Assignment constructor.
      //*******************************************************************************************
		RefCountingPointer(const RefCountingPointer& refPtr);

      //*******************************************************************************************
      //                                     ~RefCountingPointer()                               
      //*******************************************************************************************
      //! Destructor.
      //*******************************************************************************************
	   ~RefCountingPointer();
   
      //operators
   public:
      //! Indirection operator.
      TYPE& operator* () const;
      //! Access operator.
      TYPE* operator-> () const;
      //! void operator
      operator void*() const;
      //! Negate operator.
      bool operator! () const;
      //! void* operator

		//! Assignment operator.
		RefCountingPointer& operator= (const RefCountingPointer& refPtr);

      //! Assignment operator.
		RefCountingPointer& operator= (TYPE* ptr);

      //services
   public:
      //*******************************************************************************************
      //                                     reset()                               
      //*******************************************************************************************
		//! Resets (clears) the intrusive pointer.
      //*******************************************************************************************
      void reset();

      //*******************************************************************************************
      //                                     reset()                               
      //*******************************************************************************************
		//! Resets the intrusive pointer with specified pointer.
      //! \param  pointer to reset with.
      //*******************************************************************************************
		void reset(TYPE* ptr);

      //*******************************************************************************************
      //                                     get()                               
      //*******************************************************************************************
		//! Returns the pointer contained by the RefCountingPointer.
      //! \Return Internal raw pointer.
      //*******************************************************************************************
		TYPE* get() const;

      //*******************************************************************************************
      //                                     swap()                               
      //*******************************************************************************************
		//! Swaps the contained pointers of both intrusive pointers (this and specified one).
      //*******************************************************************************************
		void swap(RefCountingPointer& refPtr);

      //data
   private:
      TYPE* mPointer;
   }; //class RefCountingPointer


   //! Comparison operator.
	template< class TYPE, class OTHERTYPE > inline bool operator== 
      (const RefCountingPointer<TYPE>& refPtrA, const RefCountingPointer<OTHERTYPE>& refPtrB)
   {
	   return refPtrA.get() == refPtrB.get();
   }

   //! Comparison operator.
	template< class TYPE, class OTHERTYPE > inline bool operator!= 
      (const RefCountingPointer<TYPE>& refPtrA, const RefCountingPointer<OTHERTYPE>& refPtrB)
   {
	   return refPtrA.get() != refPtrB.get();
   }

   //! Comparison operator.
   template< class TYPE, class OTHERTYPE > inline bool operator== 
      (const RefCountingPointer< TYPE >& refPtrA, OTHERTYPE* ptrB)
   {
	   return refPtrA.get() == ptrB;
   }

   //! Comparison operator.
   template< class TYPE, class OTHERTYPE > inline bool operator!= 
      (const RefCountingPointer<TYPE>& refPtrA, OTHERTYPE* ptrB)
   {
	   return refPtrA.get() != ptrB;
   }

   //! Comparison operator.
   template< class TYPE, class OTHERTYPE > inline bool operator== 
      (TYPE* ptrA, const RefCountingPointer<OTHERTYPE>& refPtrB)
   {
	   return ptrA == refPtrB.get();
   }

   //! Comparison operator.
	template< class TYPE, class OTHERTYPE > inline bool operator!= 
      (TYPE* ptrA, const RefCountingPointer<OTHERTYPE>& refPtrB)
   {
	   return ptrA != refPtrB.get();
   }

	//! Swaps the contained pointers of both specified intrusive pointers.
   template< class TYPE > void swap
      (RefCountingPointer<TYPE>& refPtrA, RefCountingPointer<TYPE>& refPtrB)
   {
	   refPtrA.swap(refPtrB);
   }


   //! RefCountingPointer const cast
   //! \todo: why does SCA CPP Spec use copy by value?
   template <typename TYPE, typename OTHERTYPE>
   RefCountingPointer<TYPE> constCast(/*const*/ RefCountingPointer<OTHERTYPE>/*&*/ other)
   {
      return const_cast<TYPE*>(other.get());
   }

   //! RefCountingPointer dynamic cast
   //! \todo: why does SCA CPP Spec use copy by value?
   template <typename TYPE, typename OTHERTYPE>
   RefCountingPointer<TYPE> dynamicCast(/*const*/ RefCountingPointer<OTHERTYPE>/*&*/ other)
   {
      return dynamic_cast<TYPE*>(other.get());
   }

   template <typename TYPE, typename OTHERTYPE>
   RefCountingPointer<TYPE> reinterpretCast(/*const*/ RefCountingPointer<OTHERTYPE>/*&*/ other)
   {
      return reinterpret_cast<TYPE*>(other.get());
   }

   template <typename TYPE, typename OTHERTYPE>
   RefCountingPointer<TYPE> staticCast(/*const*/ RefCountingPointer<OTHERTYPE>/*&*/ other)
   {
      return static_cast<TYPE*>(other.get());
   }

   #include "RefCountingPointer.inl"

} // namespace sca
} // namespace oasis
 
 #endif /* _oasis_sca_RefCountingPointer_h_ */
