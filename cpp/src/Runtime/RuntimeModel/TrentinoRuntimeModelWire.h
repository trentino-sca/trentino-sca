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

#ifndef TretninoRuntimeModelWireH
#define TretninoRuntimeModelWireH

//specific
#include "TrentinoRuntimeModel.h"
#include "../Invocation/TrentinoInvocation.h"

//baseclasses
#include <boost/enable_shared_from_this.hpp>
#include "TrentinoRuntimeModelWireBase.h"

namespace Trentino{
namespace RuntimeModel
{
   //class declaration
   //**********************************************************************************************
   //                                           Wire
   //**********************************************************************************************
   //! \ingroup RuntimeModel
   //! \brief A wire connects a reference and service and stores the proxy that is used to 
   //!        execute calls over this wire.
   //! A proxy associated with a wire is supposed to store a pointer to its wire in order to 
   //! retrieve necessary information (such as the invocation context and the target service) for
   //! the execution of a service call. 
   //**********************************************************************************************   
   class RUNTIMEMODEL_IMPORT_EXPORT Wire : public boost::enable_shared_from_this<Wire>, public WireBase
   {
      //construction
   public:
      //*******************************************************************************************
      //                                       ~Wire()
      //*******************************************************************************************
      //! Destructor.
      //*******************************************************************************************
      virtual ~Wire();
   private:
      //*******************************************************************************************
      //                                        Wire()
      //*******************************************************************************************
      //! Parameter constructor.
      //! Wire must be constructed by this constructor.
      //! \param[in] Shared pointer of a reference.
      //! \param[in] Shared pointer of a service.
      //*******************************************************************************************
      Wire(const ReferenceBasePtr& reference, const ServiceBasePtr& service);

      //*******************************************************************************************
      //                                        Wire()
      //*******************************************************************************************
      //! Copy constructor.
      //! \param[in] Wire source reference to copy from.
      //*******************************************************************************************
      Wire(const Wire&);

      //operators
   private:
      //*******************************************************************************************
      //                                     operator=()
      //*******************************************************************************************
      //! Assignment operator.
      //! \param[in] Wire source reference to copy from.
      //*******************************************************************************************
      void operator=(const Wire& wire);

      //services
   public:
      //*******************************************************************************************
      //                                        create()
      //*******************************************************************************************
      //! \brief In order to ceate a wire you must call this method.
      //! You have to set an existing reference and service.
      //! \param[in] Shared pointer of an existing reference.
      //! \param[in] Shared pointer of an existing service.
      //! \return Returns a new wire with given reference and service.
      //*******************************************************************************************
      static WirePtr create(const ReferenceBasePtr& reference, const ServiceBasePtr& service);

      //*******************************************************************************************
      //                                        wire()
      //*******************************************************************************************
      //! \brief Does an wire with existing and already stored reference and service.
      //*******************************************************************************************
      virtual void wire();

      //*******************************************************************************************
      //                                        rewire()
      //*******************************************************************************************
      //! \brief Does an rewire with existing and already stored reference and a a new given
      //! \brief service.
      //! \param[in] Shared_ptr of an existing service to rewire.
      //*******************************************************************************************
      //void rewire(const ServiceBasePtr& service);

      //*******************************************************************************************
      //                                        unwire()
      //*******************************************************************************************
      //! \brief Unwires an existing service and reference.
      //*******************************************************************************************
      virtual void unwire();

      //*******************************************************************************************
      //                                     unwireService()
      //*******************************************************************************************
      //! \brief Unwires an existing service only.
      //*******************************************************************************************
      virtual void unwireService();      

      //*******************************************************************************************
      //                                        reference()
      //*******************************************************************************************
      //! \brief Returns the original reference for this wire.
      //! \return Returns a weak_ptr of \sa Reference.
      //*******************************************************************************************
      virtual ReferenceBaseWeakPtr reference() const;

      //*******************************************************************************************
      //                                        service()
      //*******************************************************************************************
      //! \brief Returns the final service for this wire. 
      //!
      //! The final service is the most promoted service, i.e. service that is not implemented by 
      //! a component with <implementation.composite>. For example given the following situation:
      //! ServiceA is promoted to ServiceB is promoted to ServiceC, service() will return ServiceC.
      //! \attention A valid value is returned only after wire() is called.
      //! \return Returns a weak_ptr to the final service. 
      //! \sa originalService(), wire()
      //*******************************************************************************************
      virtual const std::string& service() const;

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
      virtual ServiceBaseWeakPtr originalService() const;

      //*******************************************************************************************
      //                                  invocationContext()
      //*******************************************************************************************
      //! \brief Returns the stored invocationContext of this wire.
      //! \return Returns a shared_ptr of \sa InvocationContext.
      //*******************************************************************************************
      virtual Trentino::Invocation::InvocationContextPtr invocationContext() const;

      //*******************************************************************************************
      //                                  setInvocationContext()
      //*******************************************************************************************
      //! \brief Sets the \sa InvocationContext
      //! \param[in] Shared_ptr of an existing \sa InvocationContext to set.
      //*******************************************************************************************
      virtual void setInvocationContext(
         const Trentino::Invocation::InvocationContextPtr& invocationContext);

      //*******************************************************************************************
      //                                     setProxy()
      //*******************************************************************************************
      //! \brief Sets the Proxy.
      //! \param[in] Shared_ptr of an proxy with unspecified pointer.
      //! \sa proxy()
      //*******************************************************************************************
      virtual void setProxy(const ProxyPtr& proxy);  

      //*******************************************************************************************
      //                                      proxy()
      //*******************************************************************************************
      //! \brief Returns the proxy
      //! \return A shared pointer to the proxy.
      //! \sa setProxy
      //*******************************************************************************************
      virtual ProxyPtr proxy() const;
      
      //data
   private:
      //! Weak pointer to the original reference for this wire\sa Reference.
      ReferenceBaseWeakPtr mOriginalReference;
      //! Weak pointer to the original service for this wire \sa originalService().
      ServiceBaseWeakPtr mOriginalService;
      //! Weak pointer to the final service for this wire. \sa service()
      std::string mFinalService;
      //! Shared pointer of a \sa InvocationContext.
      Trentino::Invocation::InvocationContextPtr mInvocationContext;      
      
      bool mWired;
      //! \brief Proxy to store with an unspecified pointer.      
      ProxyPtr mProxy;

   }; //class Wire

} //namespace RuntimeModel
} //namespace Trentino

#endif //TretninoRuntimeModelWireH