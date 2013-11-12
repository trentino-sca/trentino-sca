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
 
#ifndef Oasis_sca_ServiceProxyH
#define Oasis_sca_ServiceProxyH
 
#include "RefCountingPointer.h"
 
namespace oasis {
namespace sca 
{
   //class declaration
   //**********************************************************************************************
   //                             ServiceProxy                          
   //**********************************************************************************************
   //! \brief This class is only used as marker base class and to work with service proxies.
   //**********************************************************************************************
   class ServiceProxy 
   {
   //construction
   public:
      //*******************************************************************************************
      //                                     ~ServiceProxy()                               
      //*******************************************************************************************
      //! Destructor.
      //*******************************************************************************************
      virtual ~ServiceProxy() {}

      //*******************************************************************************************
      //                                     addRef()              
      //*******************************************************************************************
      //! \brief  Adds internal reference of object by one.
      //! \return Returns number of used references. 
      //*******************************************************************************************
      virtual uint32_t addRef() = 0;

      //*******************************************************************************************
      //                                     releaseRef()              
      //*******************************************************************************************
      //! \brief  Reduces internal reference of object by one.
      //!         If object reference is 0, object will be deleted by releaseRef().
      //! \return Returns number of used references. Returns 0 if object is destroyed.
      //*******************************************************************************************
      virtual uint32_t releaseRef() = 0;

   }; //class ServiceProxy
 
   //! Typedef for using with RefCountingPointer
   typedef RefCountingPointer<ServiceProxy> ServiceProxyPtr;

   //! Support function for \sa RefCountingPointer, increments internal object reference by one.
   void TrentinoFuncPtrAddRef(ServiceProxy* svxProxy);

   //! Support function for \sa RefCountingPointer, decrements internal object reference by one.
   void TrentinoFuncPtrReleaseRef(ServiceProxy* svxProxy);

   #include "ServiceProxy.inl"
} // namespace sca
} // namespace oasis
 
#endif //Oasis_sca_ServiceProxyH

