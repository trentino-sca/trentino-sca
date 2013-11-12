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

#ifndef TrentinoRuntimeModelWireBaseH
#define TrentinoRuntimeModelWireBaseH

//specific
#include "TrentinoRuntimeModel.h"
#include "../Invocation/TrentinoInvocation.h"

namespace Trentino{
namespace RuntimeModel
{
   //class declaration
   //**********************************************************************************************
   //                             WireBase
   //**********************************************************************************************
   //! \ingroup RuntimeModel
   //! \brief A wire connects a reference and service and stores the proxy that is used to 
   //!        execute calls over this wire.
   //! A proxy associated with a wire is supposed to store a pointer to its wire in order to 
   //! retrieve necessary information (such as the invocation context and the target service) for
   //! the execution of a service call. 
   //**********************************************************************************************   
   class WireBase
   {
      
   //services
   public:
      //*******************************************************************************************
      //                                        wire()
      //*******************************************************************************************
      //! \brief Does an wire with existing and already stored reference and service.
      //*******************************************************************************************
      virtual void wire() = 0;

      //*******************************************************************************************
      //                                        unwire()
      //*******************************************************************************************
      //! \brief Unwires an existing service and reference.
      //*******************************************************************************************
      virtual void unwire() = 0;

      //*******************************************************************************************
      //                                     unwireService()
      //*******************************************************************************************
      //! \brief Unwires an existing service only.
      //*******************************************************************************************
      virtual void unwireService() = 0;      

      //*******************************************************************************************
      //                                        reference()
      //*******************************************************************************************
      //! \brief Returns the source reference
      //! \return Returns a weak_ptr of \sa Reference.
      //*******************************************************************************************
      virtual ReferenceBaseWeakPtr reference() const = 0;

      //*******************************************************************************************
      //                                         service()
      //*******************************************************************************************
      //! \brief Returns the target Service
      //!
      //! The final service is the most promoted service, i.e. service that is not implemented by 
      //! a component with <implementation.composite>. For example given the following situation:
      //! ServiceA is promoted to ServiceB is promoted to ServiceC, service() will return ServiceC.
      //! \attention A valid value is returned only after wire() is called.
      //! \return Returns the fully qualified name of the target service in format <component name>/
      //! <service name>. 
      //! \sa originalService(), wire()
      //*******************************************************************************************
      virtual const std::string& service() const = 0;

      //*******************************************************************************************
      //                                     originalService()
      //*******************************************************************************************
      //! \brief Returns the original service for this wire. 
      //!
      //! The original service is the service which the wire was originally wired to. This might
      //! be a service implemented by a component with <implementation.composite> or any other
      //! implementation. This service is not supposed to be used in the invocation chain. 
      //! So for example given the following situation: ServiceA is promoted to ServiceB is 
      //! promoted to ServiceC, originalService() will return serviceA.
      //! \return Returns a weak_ptr to the original service of the wire.
      //! \sa service()
      //*******************************************************************************************
      virtual ServiceBaseWeakPtr originalService() const = 0;

      //*******************************************************************************************
      //                                     invocationContext()
      //*******************************************************************************************
      //! \brief Returns the stored invocationContext of this wire.
      //! \return Returns a shared_ptr of \sa InvocationContext.
      //*******************************************************************************************
      virtual Trentino::Invocation::InvocationContextPtr invocationContext() const = 0;

      //*******************************************************************************************
      //                                  setInvocationContext()
      //*******************************************************************************************
      //! \brief Sets the \sa InvocationContext
      //! \param[in] Shared_ptr of an existing \sa InvocationContext to set.
      //*******************************************************************************************
      virtual void setInvocationContext(
         const Trentino::Invocation::InvocationContextPtr& invocationContext) = 0;

      //*******************************************************************************************
      //                                      proxy()
      //*******************************************************************************************
      //! \brief Returns the proxy
      //! \return A shared pointer to the proxy.
      //! \sa setProxy
      //*******************************************************************************************
      virtual ProxyPtr proxy() const = 0;

      //*******************************************************************************************
      //                                     setProxy()
      //*******************************************************************************************
      //! \brief Sets the Proxy.
      //! \param[in] Shared_ptr of an proxy with unspecified pointer.
      //! \sa proxy()
      //*******************************************************************************************
      virtual void setProxy(const ProxyPtr& proxy) = 0;  

   }; //class WireBase
} //namespace RuntimeModel
} //namespace Trentino

#endif //TretninoRuntimeModelWireH