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
 
#ifndef Oasis_sca_ServiceReferenceH
#define Oasis_sca_ServiceReferenceH
 
#include "ServiceProxy.h"
#include "RefCountingPointer.h"
 
namespace oasis {
namespace sca 
{
   //class declaration
   //**********************************************************************************************
   //                             ServiceReference
   //**********************************************************************************************
   //! \brief This class is used to hold a service reference and it is used for asynchronous 
   //!        programming.
   //**********************************************************************************************
   class ServiceReference
   {
      //construction
   public:
      //*******************************************************************************************
      //                                     ~ServiceReference()                               
      //*******************************************************************************************
      //! Destructor.
      //*******************************************************************************************
      virtual ~ServiceReference() {};
      //services
   public:
      //*******************************************************************************************
      //                                     getService()                               
      //*******************************************************************************************
		//! \brief A C++ component implementation uses getService() to get a service proxy 
      //!        implementing the interface defined for a ServiceReference.
      //! \return Pointer to a \sa ServiceProxy implementing the interface of the ServiceReference.
      //*******************************************************************************************
      virtual ServiceProxyPtr getService() const = 0;

      //*******************************************************************************************
      //                                     getCallback()                               
      //*******************************************************************************************
		//! \brief A C++ component implementation uses getCallback() to get a service proxy 
      //!        implementing the callback interface defined for a ServiceReference.
      //! \return Pointer to a \sa ServiceProxy implementing the callback interface of the 
      //!         ServiceReference. This will be NULL if no callback interface is defined.
      //*******************************************************************************************
      virtual ServiceProxyPtr getCallback() const = 0;

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

   }; //class ServiceReference
  
   //! RefCountingPointer for ServiceReference
   typedef RefCountingPointer<ServiceReference> ServiceReferencePtr;

   //! Support function for \sa RefCountingPointer, increments internal object reference by one.
   void TrentinoFuncPtrAddRef(ServiceReference* svxRef);

   //! Support function for \sa RefCountingPointer, decrements internal object reference by one.
   void TrentinoFuncPtrReleaseRef(ServiceReference* svxRef);

   #include "ServiceReference.inl"

} // namespace sca
} // namespace oasis
 
#endif  //Oasis_sca_ServiceReferenceH
