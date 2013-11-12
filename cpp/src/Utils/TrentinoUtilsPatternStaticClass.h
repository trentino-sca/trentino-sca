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

#ifndef TrentinoUtilsPatternStaticClassH
#define TrentinoUtilsPatternStaticClassH

//standard
#pragma warning(push)
#pragma warning(disable:4245 4390 4244)
   #include <boost/crc.hpp>
#pragma warning(pop)

#include <string>
#include <malloc.h>
#include <typeinfo>

//specific
#include "../Global/TrentinoGlobal.h"
#include "TrentinoUtilsPatternEmptyImplCTorDTor.h"
#include "TrentinoUtilsStaticMap.h"

namespace Trentino{
namespace Utils{
//! \defgroup Pattern
namespace Pattern
{
//   //**********************************************************************************************
//   //                          crc32()
//   //**********************************************************************************************
//   //! \ingroup Pattern
//   //! Creates a crc32 checksum. Uses \sa boost::crc_optimal structure.
//   //! \param[in] String from which crc should be created.
//   //! \return Returns crc32 checksum. 
//   //**********************************************************************************************
//   static inline unsigned long crc32(const std::string& name);
//   
//   //**********************************************************************************************
//   //                          classId()
//   //**********************************************************************************************
//   //! \ingroup Pattern
//   //! Convenience method to create a crc32 checksum by given class type
//   //! Uses RTTI to generate a class name string.
//   //! \return Returns crc32 checksum.
//   //**********************************************************************************************
//   template <typename TYPE>
//   static inline unsigned long classId( void );
//
//
//   //class declaration
//   //**********************************************************************************************
//   //                             StaticClass
//   //**********************************************************************************************
//   //! \ingroup Pattern
//   //! \brief The StaticClass allows you to share data among boundaries if you like.
//   //! The object wrapped by StaticClass is put into named memory, where the name is generated
//   //! from the hash of the class name.
//   //! StaticClass objects will be destroyed at exit on default. 
//   //! Every call increments internal referencemap associated with this class
//   //! First call, preferred by bootstrapper should use as second parameter:
//   //! \sa FullImplCTorDTor<TYPE>. Default template parameter is \sa EmptyImplCTorDTor
//   //! in order to reduce linkage dependency of created object. No constructor or destructor
//   //! will be called.
//   //**********************************************************************************************
//   template < typename TYPE, class CONSTRUCTION = EmptyImplCTorDTor<TYPE> >
//   class StaticClass
//   {
//      //construction
//   public:
//      //*******************************************************************************************
//      //                            StaticClass()
//      //*******************************************************************************************
//      //! \brief Default constructor.
//      //! Your first call should be done by FullImplCTorDTor<TYPE> as second parameter to
//      //! construct your object properly. Each constructor call of a typed StaticClass will
//      //! increment internal refcounter of constructed object. 
//      //! You can call \sa StaticMap::refCount to determine current active refcount of
//      //! StaticClass which owns a specified type.
//      //*******************************************************************************************
//      StaticClass();
//      //*******************************************************************************************
//      //                            ~StaticClass()
//      //*******************************************************************************************
//      //! \brief Destructor.
//      //! Most of your destruction calls should be done by exiting a scope. 
//      //! But beware: StaticClass which owns the last reference of this specified type should
//      //! be still created by \sa FullImplCTorDTor<TYPE> as second template parameter and 
//      //! in optimal way done by bootstrapper.
//      //*******************************************************************************************
//      ~StaticClass();
//
//      //operators
//   public:
//      //*******************************************************************************************
//      //                                     operator->()                               
//      //*******************************************************************************************
//      //! Returns pointer of your object, created by StaticClass.
//      //! \return Pointer of object.
//      //*******************************************************************************************
//      TYPE* operator-> () const;
//
//      //*******************************************************************************************
//      //                                     operator*()                               
//      //*******************************************************************************************
//      //! Returns reference of your object, created by StaticClass.
//      //! \return Reference of object.
//      //*******************************************************************************************
//      TYPE& operator* () const;
//
//      //*******************************************************************************************
//      //                                     get()                               
//      //*******************************************************************************************
//      //! Returns pointer of your object, created by StaticClass.
//      //! \return Pointer of object.
//      //*******************************************************************************************
//      TYPE* get() const;
//
//      //service
//   public:
//      //*******************************************************************************************
//      //                                     hasReference()                               
//      //*******************************************************************************************
//      //! Determines if reference of object stored in StaticClass instance is valid
//      //! Uses HashIndex to determine a valid reference.
//      //! \return Indicates if a valid reference of created object exists.
//      //! \retval true, if reference of object exists.
//      //! \retval false, if reference of object doesn´t exist.
//      //*******************************************************************************************
//      static bool hasReference();
//      //management
//   private:
//      bool mustAllocateMemory() const;
//      
//      //data
//   private:
//      //! Data pointer of created object
//      TYPE* mData;
//      //! Hashindex corresponded with TYPE
//unsigned long mHashIndex;
//   }; //template <typename TYPE, class CONSTRUCTION> class StaticClass
//
//   #include "TrentinoUtilsPatternStaticClass.inl"

} //namespace Pattern
} //namespace Utils
} //namespace Trentino


#endif //TrentinoUtilsPatternStaticClassH
