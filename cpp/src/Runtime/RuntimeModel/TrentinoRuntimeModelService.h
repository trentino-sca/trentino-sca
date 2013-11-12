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

#ifndef TrentinoRuntimeModelServiceH
#define TrentinoRuntimeModelServiceH

//baseclass 
#include "TrentinoRuntimeModelServiceBase.h"

//standard
#include <map>

//specific
#include "TrentinoRuntimeModel.h"
#include "TrentinoRuntimeModelWireable.h"
#include "../SCAModel/TrentinoSCAModel.h"
#include "../SCAModel/TrentinoSCAModelService.h"
#include "../../Utils/TrentinoUtilsURI.h"
#include "../Binding/TrentinoBinding.h"


namespace Trentino{
namespace RuntimeModel
{

   //**********************************************************************************************
   //                                        Service
   //**********************************************************************************************
   //! \ingroup RuntimeModel
   //! \brief Represents an SCA service at runtime.
   //!
   //! The RuntimeModel::Service class points to the corresponding information from the SCA Model
   //! representing an sca service and provides additional information associated with a service. 
   //! Examples for such additional information are: 
   //! - the service's state
   //! - the service's parent component
   //! - collection of wires connected to the service   
   //! - etc. 
   //! \todo specify exceptions thrown by all the methods/constructors
   //**********************************************************************************************
   class RUNTIMEMODEL_IMPORT_EXPORT Service : public ServiceBase
   {
      //construction
   public:
      //*******************************************************************************************
      //                                     Service()
      //*******************************************************************************************
      //! \brief Constructs a service with the given parent component and associates it with the
      //!        given SCA::Model::ComponentService representing the service element from the
      //!        component type. 
      //! \param[in] scaServiceType A shared pointer to the SCA::Model::ComponentService 
      //!            instance (representing the service from componentType) the service
      //!            should be associated with.
      //! \param[in] scaService A shared pointer to the SCA::Model::ComponentService
      //!            instance the service should be associated with.
      //! \param[in] A shared pointer to the services's parent component.      
      //*******************************************************************************************
      Service( const Trentino::SCA::Model::ComponentServicePtr& scaServiceType
             , const Trentino::SCA::Model::ComponentServicePtr& scaService
             , const ComponentPtr& component);
   private:
      //*******************************************************************************************
      //                              Service(const Service&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copy construction.      
      //*******************************************************************************************
      Service(const Service&);

      //operators
   private:            
      //*******************************************************************************************
      //                                       operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.
      //*******************************************************************************************
      void operator=(const Service&);

      //services
   public:                  
      //*******************************************************************************************
      //                                    scaServiceType()
      //*******************************************************************************************
      // override from ServiceBase (see documentation in ServiceBase)
      //! \copydoc RuntimeModel::ServiceBase::scaServiceType()
      //! \sa Service()
      //*******************************************************************************************
      virtual Trentino::SCA::Model::ComponentServicePtr scaServiceType() const;

      //*******************************************************************************************
      //                                    scaService()
      //*******************************************************************************************
      // override from ServiceBase (see documentation in ServiceBase)
      //! \copydoc RuntimeModel::ServiceBase::scaService()
      //! \sa Service()
      //*******************************************************************************************
      virtual Trentino::SCA::Model::ComponentServicePtr scaService() const;
      
      //*******************************************************************************************
      //                                       component()
      //*******************************************************************************************
      // override from ServiceBase (see documentation in ServiceBase)
      //! \copydoc RuntimeModel::ServiceBase::component()
      //! \sa Service()
      //*******************************************************************************************
      virtual ComponentWeakPtr component() const;

      //*******************************************************************************************
      //                                        state()
      //*******************************************************************************************
      // override from ServiceBase (see documentation in ServiceBase)      
      //*******************************************************************************************
      virtual State state() const;


      //*******************************************************************************************
      //                          bindingHelperByBindingId()      
      //*******************************************************************************************
      // override from ServiceBase (see documentation in ServiceBase)      
      //*******************************************************************************************
      virtual Trentino::Binding::BindingHelperBasePtr bindingHelperByBindingId(const std::string& bindingId); 

      
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
      //                                  promotedTo()      
      //*******************************************************************************************      
      // override from ServiceBase (see documentation in ServiceBase)      
      //*******************************************************************************************
      virtual ServiceBaseWeakPtr promotedTo() const; 

      //*******************************************************************************************
      //                                 setPromotedTo()      
      //*******************************************************************************************
      // override from ServiceBase (see documentation in ServiceBase)      
      //*******************************************************************************************
      virtual void setPromotedTo(const ServiceBasePtr& service);

      //*******************************************************************************************
      //                                  promotedBy()      
      //*******************************************************************************************
      // override from ServiceBase (see documentation in ServiceBase)      
      //*******************************************************************************************
      virtual const WeakServiceBases& promotedBy() const;

      //*******************************************************************************************
      //                                 setPromotedBy()      
      //*******************************************************************************************
      // override from ServiceBase (see documentation in ServiceBase)      
      //*******************************************************************************************
      virtual void addPromotedBy(const ServiceBasePtr& service);
      //! @}

      //*******************************************************************************************
      //                                 wireableSupport()      
      //*******************************************************************************************
      // override from ServiceBase (see documentation in ServiceBase)      
      //*******************************************************************************************
      virtual Wireable& wireableSupport();

      //*******************************************************************************************
      //                                       mutex()      
      //*******************************************************************************************
      // override from ServiceBase (see documentation in ServiceBase)      
      //*******************************************************************************************
      virtual boost::recursive_mutex& mutex() const;

      //*******************************************************************************************
      //! \name convenience methods 
      //! @{
      //*******************************************************************************************

      //*******************************************************************************************
      //                                         name()
      //*******************************************************************************************
      // override from ServiceBase (see documentation in ServiceBase) 
      //! \copydoc RuntimeModel::ServiceBase::name()
      //! \return scaServiceType()->name()
      //*******************************************************************************************
      virtual const Trentino::XML::Schema::NCName& name() const;
      //! @}

     //****************************************************************************************************
     //                                         cPPInterfaceClassName()
     //****************************************************************************************************
     //! \brief return the CPP interface classname for this service.
     //! \return Trentino::XML::Schema::Name
     //****************************************************************************************************
      Trentino::XML::Schema::Name cPPInterfaceClassName() const;

     //****************************************************************************************************
     //                                         isRemotable()
     //****************************************************************************************************
     //! \brief return true if the service is remotable
     //! \return bool
     //****************************************************************************************************
      virtual bool isRemotable() const;

     //****************************************************************************************************
     //                                         bindings()
     //****************************************************************************************************
     //! \brief see super class TrentinoRuntimeModelServiceBase
     //! \return const std::set<std::string>
     //****************************************************************************************************
      virtual const std::set<std::string> bindings() const;

      //****************************************************************************************************
      //                                         metaData()
      //****************************************************************************************************
      // override from ServiceBase (see documentation in ServiceBase)
      //! \copydoc RuntimeModel::ServiceBase::metaData()
      //****************************************************************************************************
      virtual const Trentino::SCA::Model::MetadataPtr metaData() const;

      //****************************************************************************************************
      //                                         discoveryId()
      //****************************************************************************************************
      //! \brief get the service discovery registration id
      //! \return unique string id obtained from discovery registration, empty string means the service is
      //! not registered
      //****************************************************************************************************
      virtual const std::string discoveryId() const;

      //****************************************************************************************************
      //                                         setDiscoveryId()
      //****************************************************************************************************
      //! \brief set the service discovery registration id
      //! \param discovery id
      //****************************************************************************************************
      virtual void setDiscoveryId(const std::string id);

      //data
   private:      
      //! the component type's SCA::Model::ComponentService associated with the service
      const Trentino::SCA::Model::ComponentServicePtr mSCAServiceType;
      //! the component's SCA::Model::ComponentService associated with the service
      const Trentino::SCA::Model::ComponentServicePtr mSCAService;
      //! the service's parent component
      const ComponentWeakPtr mComponent;
      //! the service state
      State mState;
      //! the invocation wrapper associated with the service
      Trentino::Invocation::ServiceInvocationWrapperBasePtr mServiceInvocationWrapper;
      //! service the current service is promoted to 
      ServiceBaseWeakPtr mPromotedTo;
      //! collection of services that are promoted to the current service       
      WeakServiceBases mPromotedBy;
      //! object managing the wire handling for the service  
      Wireable mWireableSupport;
      
      std::map<std::string,Trentino::Binding::BindingHelperBasePtr> mHelpers;
      //! Discovery ID obtained from discovery layer. Used for service de-registration
      std::string mDiscoveryId;
      //! Metadata member: joined from scaService and scaServiceType
      Trentino::SCA::Model::MetadataPtr mMetaData;

   }; //class Service  

} //namespace RuntimeModel
} //namespace Trentino

#endif //TrentinoRuntimeModelServiceH
