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

#ifndef TrentinoRuntimeModelServiceBaseH
#define TrentinoRuntimeModelServiceBaseH

//standard
#include <boost/thread/recursive_mutex.hpp>

//specific
#include "TrentinoRuntimeModel.h"
#include "../SCAModel/TrentinoSCAModel.h"
#include "../Invocation/TrentinoInvocation.h"
#include "../Binding/TrentinoBindingBindingHelperBase.h"

namespace Trentino{
namespace RuntimeModel{

   class Wireable;

   //**********************************************************************************************
   //                                        ServiceBase
   //**********************************************************************************************
   //! \ingroup RuntimeModel
   //! \brief Interface for the RuntimeModel::Service class to make it easy mockable. 
   //!
   //! The RuntimeModel::ServiceBase class exist for only one real purpose: to facilitate testing
   //! by making the Runtime::Service class easily mockable.
   //**********************************************************************************************
   class RUNTIMEMODEL_IMPORT_EXPORT ServiceBase 
   {
      //additional
   public:
      
      //*******************************************************************************************
      //                                    State
      //*******************************************************************************************
      //! Describes the state of a Service. The service's state is dependent on the state of 
      //! the component the service is attached to. 
      //*******************************************************************************************
      enum State{

      //*******************************************************************************************
      //                                    Available 
      //*******************************************************************************************
      //! \brief Service is accessible and may be invoked.
      //! - The corresponding component is either in RuntimeModel::Component::Resolved or 
      //!   RuntimeModel::Component::OptionalUnresolved state.
      //! - further conditions:       
      //!   - communication and bindings initialized 
      //!   - allow remote connection (start servers)
      //*******************************************************************************************
      Available,

      //*******************************************************************************************
      //                                    Unavailable
      //*******************************************************************************************
      //! \brief Service is not accessible and may not be invoked.
      //! The service proxy will throw an std::runtime_error("service unavailable") exception if
      //! a service in Unavailable state is being accessed. 
      //*******************************************************************************************
      Unavailable};

      //construction
   public:
      virtual ~ServiceBase(){}

      //services
   public:
      //*******************************************************************************************
      //                                    scaServiceType()
      //*******************************************************************************************
      //! \brief Returns the SCA::Model::ComponentService associated with the service. The returned
      //!        SCA::Model::ComponentService represents the corresponding <service> element from 
      //!        the component type and not from the composite. 
      //! \return A shared pointer to the component type's SCA::Model::ComponentService instance  
      //!         the service is associated with.
      //*******************************************************************************************
      virtual Trentino::SCA::Model::ComponentServicePtr scaServiceType() const = 0;      

      //*******************************************************************************************
      //                                    scaService()
      //*******************************************************************************************
      //! \brief Returns the SCA::Model::ComponentService associated with the service. The returned
      //!        SCA::Model::ComponentService represents the corresponding <service> element from
      //!        the composite.
      //! \return A shared pointer to the component's SCA::Model::ComponentService instance
      //!         the service is associated with.
      //*******************************************************************************************
      virtual Trentino::SCA::Model::ComponentServicePtr scaService() const = 0;

      //*******************************************************************************************
      //                                       component()
      //*******************************************************************************************
      //! \brief Returns the service's parent component.
      //! \return A shared pointer to the service's parent component.      
      //*******************************************************************************************
      virtual ComponentWeakPtr component() const = 0;

      //*******************************************************************************************
      //                                        state()
      //*******************************************************************************************
      //! \brief Returns the service's state.
      //! The state is computed dependent on the state of the service's parent component. 
      //! This method is thread-safe. 
      //! \return The service's state.      
      //*******************************************************************************************
      virtual ServiceBase::State state() const = 0;

     
      //*******************************************************************************************
      //                                 bindingHelperByBindingId()
      //*******************************************************************************************
      //! \brief Returns the BindingHelper for the Binding with the given Id.
      //! \param[in] bindingId Id of the binding to return the BindingHelper for. 
      //! \return A shared pointer to the BindingHelper.
      //*******************************************************************************************
      virtual Trentino::Binding::BindingHelperBasePtr bindingHelperByBindingId(const std::string& bindingId) = 0;      
      
      //*******************************************************************************************
      //! \name Promotion      
      //! @{
      //! A service that is attached to a component which is implemented by a composite must be 
      //! promoted to a service contained in the implementing composite. A single service can be
      //! promoted only to exactly one target service. On the other hand, it is allowed for a
      //! service to be the target service of an arbitrary number of promotions (see also Assembly
      //! Spec 1.1, chapters 5.1 and 5.6).
      //!
      //! The admissible promotion relations are illustrated in the following graph.
      //! \image html ServicePromotionGraph.png
      //! The four methods in this group serve for accessing and modifying the promotion relations
      //! for the current service: for the given example graph promotedTo() will return ServiceC
      //! and promotedBy() will return ca collection containg ServiceA and ServiceB. 
      //*******************************************************************************************

      //*******************************************************************************************
      //                                 promotedTo()
      //*******************************************************************************************
      //! \brief Returns the service the current service is promoted to.
      //! \return A weak pointer to the the service the current service is promoted to. An empty
      //!         weak pointer (i.e. promotedTo().expired() == true) is returned in case the
      //!         current service is not promoted.      
      //! \sa setPromotedTo()
      //*******************************************************************************************
      virtual ServiceBaseWeakPtr promotedTo() const = 0;  

      //*******************************************************************************************
      //                                 setPromotedTo()
      //*******************************************************************************************
      //! \brief Sets the service the current service is promoted to.
      //! \param[in] service A shared pointer to the service the current service is promoted to.
      //! \sa setPromotedTo()
      //*******************************************************************************************
      virtual void setPromotedTo(const ServiceBasePtr& service) = 0;

      //*******************************************************************************************
      //                                 promotedBy()
      //*******************************************************************************************
      //! \brief Returns a collection of services that are promoted to the current service. 
      //! \return A collection of weak pointers to services that are promoted to the current 
      //!         service. An empty collection is returned in case the current service is not
      //!         promoted by any service. 
      //! \sa addPromotedBy()
      //*******************************************************************************************
      virtual const WeakServiceBases& promotedBy() const = 0;

      //*******************************************************************************************
      //                                 addPromotedBy()
      //*******************************************************************************************
      //! \brief Adds a service to the collection of services that are promoted the the current
      //!        service. 
      //! \param[in] service A shared pointer to the service that should be added to the collection
      //!            of services that are promoted to the current service.
      //! \sa promotedBy()
      //*******************************************************************************************
      virtual void addPromotedBy(const ServiceBasePtr& service) = 0;
      //! @}

      //*******************************************************************************************
      //                                 wireableSupport()
      //*******************************************************************************************
      //! \brief Returns the RuntimeModel::Wirable object associated with this service.
      //! \return Reference to the RuntimeModel::Wirable object associated with this service.      
      //*******************************************************************************************
      virtual Wireable& wireableSupport() = 0;

      //*******************************************************************************************
      //                                       mutex()
      //*******************************************************************************************
      //! \brief Returns a mutex that can be used to guard access to the service object. 
      //!
      //! Even though single methods of the class can be made thread safe by internally using this
      //! mutex and thus hiding the complexity from the client, in some situations this might be
      //! not enough to atomically execute several methods that affect the consistency of the 
      //! service's internal state. 
      //! For these special situations the client can take over the responsibility for thread 
      //! safety by using the mutex returned from this method. 
      //! \return A recursive mutex.    
      //*******************************************************************************************
      virtual boost::recursive_mutex& mutex() const = 0;
      
      //*******************************************************************************************
      //! \name convenience methods 
      //! @{
      //*******************************************************************************************
      
      //*******************************************************************************************
      //                                         name()
      //*******************************************************************************************
      //! \brief Convenience method to access SCA::Model service name. 
      //! \return The service's name. 
      //*******************************************************************************************
      virtual const Trentino::XML::Schema::NCName& name() const = 0;
      //! @}

      //****************************************************************************************************
      //                                         isRemotable()
      //****************************************************************************************************
      //! \brief return true if this service is a remotable service
      //! \return bool
      //****************************************************************************************************
      virtual bool isRemotable() const = 0;

      //****************************************************************************************************
      //                                         bindings()
      //****************************************************************************************************
      //! \brief get the list of bindings used by this service
      //! \return const std::set<std::string>
      //****************************************************************************************************
      virtual const std::set<std::string> bindings() const =0;


      //****************************************************************************************************
      //                                         metaData()
      //****************************************************************************************************
      //! \brief get the service metadata
      //! \return Trentino::SCA::Model::Metadata
      //****************************************************************************************************
      virtual const Trentino::SCA::Model::MetadataPtr metaData() const =0;

      //****************************************************************************************************
      //                                         discoveryId()
      //****************************************************************************************************
      //! \brief get the service discovery registration id
      //! \return unique string id obtained from discovery registration, empty string means the service is
      //! not registered
      //****************************************************************************************************
      virtual const std::string discoveryId() const = 0;
      
      //****************************************************************************************************
      //                                         discoveryId()
      //****************************************************************************************************
      //! \brief Set the service discovery registration id
      //****************************************************************************************************
      virtual void setDiscoveryId(const std::string id) = 0;

   }; //class ServiceBase

} //namespace RuntimeModel
} //namespace Trentino

#endif //TrentinoRuntimeModelServiceBaseH
