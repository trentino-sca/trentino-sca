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

#ifndef TrentinoUtilsPatternFullImplCTorDTorH
#define TrentinoUtilsPatternFullImplCTorDTorH

namespace Trentino{
namespace Utils{
namespace Pattern
{
   ////class declaration
   ////**********************************************************************************************
   ////                             FullImplCTorDTor
   ////**********************************************************************************************
   ////! \ingroup Pattern
   ////! \brief Simple class to reduce linkage dependency by calling constructor and destructor
   ////! \brief indirection.
   ////! This template class calls constructor or destructor. This class does a full implementation
   ////! of calling inplace new and destructor in order to create and destroy a object by given class.
   ////! See \sa Trentino::Utils::StaticMap for more details.
   ////**********************************************************************************************
   //template <typename TYPE>
   //class FullImplCTorDTor
   //{
   //   //additional
   //public:
   //   enum { allocateMemory = 1 };
   //public:
   //   typedef TYPE Type;
   //   //service
   //public:
   //   //*******************************************************************************************
   //   //                          callCTor()
   //   //*******************************************************************************************
   //   //! Calls constructor of new object by inplace new.  Memory must be still allocated.
   //   //! \param[in] Object to create by inplace new.
   //   //*******************************************************************************************
   //   static inline void callCTor(TYPE* classPtr);

   //   //*******************************************************************************************
   //   //                          callDTor()
   //   //*******************************************************************************************
   //   //! Calls destructor directly. Memory isn´t destroyed. Object is after this call in an 
   //   //! undefined state.
   //   //! \param[in] Object to destroy by calling destructor directly.
   //   //*******************************************************************************************
   //   static inline void callDTor(TYPE* classPtr);
   //}; //template <typename TYPE> class FullImplCTorDTor


   //#include "TrentinoUtilsPatternFullImplCTorDTor.inl"

} //namespace Pattern
} //namespace Utils
} //namespace Trentino


#endif //TrentinoUtilsPatternFullImplCTorDTorH

