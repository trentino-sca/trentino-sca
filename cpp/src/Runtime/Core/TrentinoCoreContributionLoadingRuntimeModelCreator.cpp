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

//header
#include "TrentinoCoreContributionLoadingRuntimeModelCreator.h"

//standard
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>

//specific
#include "TrentinoCoreContributionLoading.h"
#include "TrentinoCoreContributionInfo.h"
#include "../RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "../RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "../RuntimeModel/TrentinoRuntimeModelComponent.h"
#include "../RuntimeModel/TrentinoRuntimeModelCPPImplementation.h"
#include "../RuntimeModel/TrentinoRuntimeModelService.h"
#include "../RuntimeModel/TrentinoRuntimeModelReference.h"
#include "../RuntimeModel/TrentinoRuntimeModelProperty.h"
#include "../RuntimeModel/TrentinoRuntimeModelCommonFuncs.h"
#include "../SCAModel/TrentinoSCAModelComposite.h"
#include "../SCAModel/TrentinoSCAModelComponent.h"
#include "../SCAModel/TrentinoSCAModelComponentService.h"
#include "../SCAModel/TrentinoSCAModelComponentType.h"
#include "../SCAModel/TrentinoSCAModelSCAImplementation.h"
#include "../SCAModel/TrentinoSCAModelCPPImplementation.h"
#include "../SCAModel/TrentinoSCAModelComponentTypeReference.h"
#include "../SCAModel/TrentinoSCAModelComponentReference.h"
#include "../SCAModel/TrentinoSCAModelReference.h"
#include "../SCAModel/TrentinoSCAModelProperty.h"
#include "../SCAModel/TrentinoSCAModelCPPInterface.h"
#include "../SCAModel/TrentinoSCAModelModelDescriptor.h"
#include "../Invocation/TrentinoInvocation.h"
#include "../ReflectionRuntime/TrentinoReflectionDataRegistry.h"
#include "../XML/TrentinoXMLSchema.h"
#include "../XML/TrentinoXMLSchemaQName.h"
#include "../../Utils/TrentinoUtilsDynamicLibrary.h"
#include "../../Utils/TrentinoUtilsPerformanceHierarchyLogger.h"

using namespace std;
using namespace Trentino;
using Trentino::Core::ContributionLoading::RuntimeModelCreator;
namespace ContributionLoading = Trentino::Core::ContributionLoading;
namespace SCAModel = Trentino::SCA::Model;

namespace
{
   //forward declarations
   RuntimeModel::ImplementationPtr createImplementation(
      const RuntimeModel::ConstCompositePtr& parentComposite,
      const SCAModel::ComponentPtr& scaComponent);
   void resolvePromotion(const RuntimeModel::ConstComponentPtr& component);

   //**********************************************************************************************
   //                                     createComponent()
   //**********************************************************************************************
   //! \brief Creates a Trentino::RuntimeModel::Component object based on the given 
   //!        Trentino::SCA::Model::Component object.
   //!      
   //! \param[in] parentComposite A shared pointer to the parent composite (i.e. composite 
   //!            containing the component) of the to be created component. 
   //! \param[in] scaComponent A shared pointer to an Trentino::SCA::Model::Component object that 
   //!            will be used as "information source" for creating the 
   //!            Trentino::RuntimeModel::Component. 
   //! \throw ContributionLoading::ErrorException with \c data() set to 
   //!        Trentino::Core::ContributionLoading::ComponentTypeNotFoundError in case a componen  
   //!        type (Trentino::SCA::Model::ComponentType) for a component could not be found in the
   //!         %SCA Model.
   //! \throw ContributionLoading::ErrorException with \c data() set to 
   //!        Trentino::Core::ContributionLoading::ReflectObjectNotFoundError in case a needed  
   //!        proxy reflect object  could not be found.
   //! \throw everything thrown by createImplementation()
   //! \return A shared pointer to the newly created Trentino::RuntimeModel::Component object.
   //!        
   //! Apart from creating the Trentino::RuntimeModel::Component instance itself, createComponent() 
   //! is also responsible for the creation of RuntimeModel representations for the following SCDL 
   //! elements contained in a \c \<component\> element: \n
   //! - \c \<implementation.composite\> represented by Trentino::RuntimeModel::Composite
   //! - \c \<implementation.cpp\> represented by Trentino::RuntimeModel::CPPImplementation
   //! - \c \<service\> represened by Trentino::RuntimeModel::Service
   //! - \c \<reference\> represented by Trentino::RuntimeModel::Reference
   //! - \c \<property\> represented by Trentino::RuntimeModel::Property
   //!
   //! Further responsibilities of createComponent() are:
   //! - associating each created Trentino::RuntimeModel::Service object with its corresponding,  
   //!   generated ServiceInvocationWrapper 
   //!  (instance of Trentino::Invocaton::ServiceInvocationWrapperBase) 
   //! - associating each created Trentino::RuntimeModel::Reference object with the generated Proxy 
   //!   object used to perform service calls through the reference.
   //! \sa createImplementation()
   //**********************************************************************************************
   RuntimeModel::ComponentPtr createComponent( const RuntimeModel::CompositePtr& parentComposite
                                             , const SCAModel::ComponentPtr& scaComponent)
   {
      HLOGGER();   
      HLOGGER_INFO(scaComponent->name().c_str());

      //implementation
      const RuntimeModel::ImplementationPtr implementation = 
         createImplementation(parentComposite, scaComponent);
                                                     
      const RuntimeModel::ComponentPtr component = 
         boost::make_shared<RuntimeModel::Component>( scaComponent                                                 
                                                    , parentComposite
                                                    , implementation);   
      implementation->setComponent(component);
   
      //needed for the creation of runtime services, references and properties
      const RuntimeModel::ConstContributionPtr contribution = 
         parentComposite->contribution().lock();
      assert(contribution);
      const SCAModel::ComponentTypePtr scaComponentType = 
         contribution->scaModelDescriptor()->findComponentType(scaComponent);

      //services 
      if(!scaComponentType)
      {
         ostringstream errorMsg;
         errorMsg << "Cannot find component type for <component> with @name' " << scaComponent->name()
                  << "' in <composite> with @name '" << parentComposite->scaComposite()->name() << "'.";               
         
         throw ContributionLoading::ErrorException(
            ContributionLoading::ComponentTypeNotFoundError, errorMsg.str());      
      }

      const vector<SCAModel::ComponentServicePtr>& scaServiceTypes =
                                                               scaComponentType->serviceElements();
      const vector<SCAModel::ComponentServicePtr>& scaServices =
                                                               scaComponent->serviceElements();



      BOOST_FOREACH(const SCAModel::ComponentServicePtr& scaServiceType, scaServiceTypes)
      {
         /* SCA Assembly Model Specification Version 1.1
          * Committee Specification Draft 08 / Public Review Draft 03
          * 31 May 2011
          * Section 4 Component
          * Subsection 4.2 Service
          * Page 27
          * Lines 771 - 776
          *  The component service element has the attributes:
          *  • name : NCName (1..1) - the name of the service. The @name attribute of a service element of a
          *    <component/> MUST be unique amongst the service elements of that <component/> [ASM50002]
          *    The @name attribute of a service element of a <component/> MUST match the @name attribute of a
          *    service element of the componentType of the <implementation/> child element of the component.
          *    [ASM50003]
          *
          * So, find matching service element SCAService by name (if exists):
          */
         SCAModel::ComponentServicePtr matchedService;
         BOOST_FOREACH(const SCAModel::ComponentServicePtr& scaService, scaServices)
         {
           if(scaService->name() == scaServiceType->name())
              {
              matchedService = scaService;
              break;
              }
         }

         // And now construct the Runtime Model Service
         const boost::shared_ptr<RuntimeModel::Service> service = 
            boost::make_shared<RuntimeModel::Service>(scaServiceType, matchedService , component);
         XML::Schema::Name wrapperClassName = service->cPPInterfaceClassName();
         const RuntimeModel::ConstContributionPtr contribution = 
            parentComposite->contribution().lock();
         assert(contribution);
         const Core::TrentinoContributionInfoPtr contributionInfo = 
            contribution->contributionInfo();
         component->addService(service);
      }
   
      //references
      const vector<SCAModel::ComponentTypeReferencePtr>& scaReferenceTypes = 
         scaComponentType->referenceElements();
      BOOST_FOREACH(const SCAModel::ComponentTypeReferencePtr& scaReferenceType, scaReferenceTypes)
      {
         const boost::shared_ptr<RuntimeModel::Reference> reference =
            boost::make_shared<RuntimeModel::Reference>(scaReferenceType, component); 

         const vector<SCAModel::ComponentReferencePtr>::const_iterator it =
            find_if( scaComponent->referenceElements().begin()
                   , scaComponent->referenceElements().end()
                   , boost::bind(&SCAModel::ComponentReference::name, _1) == scaReferenceType->name() ); 
         if(it != scaComponent->referenceElements().end())
         {
            reference->setSCAReference(*it);
         }

         reference->setSetterMethod( implementation->querySetterMethod(reference) );

         //get the proxy reflect object
         const SCAModel::CPPInterfacePtr scaCPPInterface =                                       
            boost::static_pointer_cast<SCAModel::CPPInterface>(
               reference->scaReferenceType()->interfaceElement());
         assert(scaCPPInterface);
      
         const string proxyClassName = 
            RuntimeModel::CommonFuncs::proxyName(scaCPPInterface->clazz());

         const Reflection::ReflectObjectPtr proxyReflectObject = 
               component->dataRegistry().queryReflectObject(proxyClassName);

         if(!proxyReflectObject)
         {            
            throw ContributionLoading::ErrorException( 
               ContributionLoading::ReflectObjectNotFoundError,
               "Reflect object for class '" + proxyClassName + "' not found!"); 
         }

         reference->setProxyReflectObject(proxyReflectObject);

         component->addReference(reference);
      } //BOOST_FOREACH(const SCAModel::ComponentTypeReferencePtr& scaReferenceType, scaReferenceTypes)

   
      //properties
      const vector<SCAModel::PropertyPtr>& scaPropertyTypes = 
         scaComponentType->propertyElements();
      BOOST_FOREACH(const SCAModel::PropertyPtr& scaPropertyType, scaPropertyTypes)
      {
         const RuntimeModel::PropertyPtr property = 
            boost::make_shared<RuntimeModel::Property>(scaPropertyType, component);

         const vector<SCAModel::PropertyValuePtr>::const_iterator it =
            find_if( scaComponent->propertyElements().begin()
                   , scaComponent->propertyElements().end()
                   , boost::bind(&SCAModel::PropertyValue::name, _1) == scaPropertyType->name() ); 
         if(it != scaComponent->propertyElements().end())
         {
            property->setSCAProperty(*it);
         }

         property->setSetterMethod( implementation->queryPropertySetterMethod(property) );
      
         component->addProperty(property);
      } //BOOST_FOREACH(const SCAModel::PropertyPtr& scaPropertyType, scaPropertyTypes)

      return component;
   }

   //**********************************************************************************************
   //                                     createImplementation()
   //**********************************************************************************************
   //! \brief Creates a Trentino::RuntimeModel::Implementation instance for the given 
   //!        Trentino::SCA::Model::Component.
   //!
   //! \param[in] parentComposite A shared pointer to the parent composite (i.e. composite 
   //!            containing the component for which the implementation is to be created).
   //! \param[in] scaComponent A shared pointer to a Trentino::SCA::Model::Component object that 
   //!            will be used as "information source" for creating the appropriate implementation
   //!            object. 
   //! 
   //! \throw ContributionLoading::ErrorException with \c data() set to 
   //!        Trentino::Core::ContributionLoading::CompositeNotFoundError in case the given 
   //!        component is implemented by a composite but the composite referenced in the
   //!        \c \<implementation.composite\> element could not be found.
   //! \throw std::runtime_error in case the implementation type associated with the given 
   //!        component is not supported by the runtime. 
   //!
   //! \return Depending on the implementation type of the component, an instance of either
   //!         Trentino::RuntimeModel::Composite (for \c \<implementation.composite\>) or
   //!         Trentino::RuntimeModel::CPPImplementation (for \c \<implementation.cpp\>).
   //**********************************************************************************************
   RuntimeModel::ImplementationPtr createImplementation(
      const RuntimeModel::ConstCompositePtr& parentComposite,
      const SCAModel::ComponentPtr& scaComponent)
   {   
      HLOGGER();   
      HLOGGER_INFO(scaComponent->name().c_str());

      const SCAModel::ImplementationPtr scaImplementation = 
         scaComponent->implementationElement();
      if(scaImplementation->xsdType() == ContributionLoading::XSDTypeImplementationComposite)
      {
         //SCAImplementation represents <implementation.composite>
         //ATTENTION: We must use a static cast here, even though SCAModel::Implementation
         //_is_ a base class of SCAModel::SCAImplementation and considering type safety a 
         //dynamic cast would be more appropriate. Unfortunately the SCAModel isn't allowed 
         //to contain polymorphic types because of binary compatibility issues. 
         const SCAModel::SCAImplementationPtr scaSCAImplementation = 
            boost::static_pointer_cast<SCAModel::SCAImplementation>(scaImplementation);      

         const SCAModel::CompositePtr scaImplComposite = 
            parentComposite->contribution().lock()->scaModelDescriptor()->findCompositeByQName(
               *scaSCAImplementation->name() );

         if(!scaImplComposite)
         {
            ostringstream errorMsg;
            errorMsg << "composite with QName '" << scaSCAImplementation->name() << "' not found! " 
                     << "Specified in <implementation.composite>/@name in <component> with @name = '"
                     << scaComponent->name() << "' in <composite> with @name = '"
                     << parentComposite->scaComposite()->name() << "'";
         
            throw ContributionLoading::ErrorException(
               ContributionLoading::CompositeNotFoundError, errorMsg.str().c_str());         
         }
      
         return RuntimeModelCreator::createComposite(
            scaImplComposite, parentComposite->contribution().lock());      
      
      }
      //! \todo support through extensions
      else if(scaImplementation->xsdType() == ContributionLoading::XSDTypeImplementationCPP) 
      {
         //ATTENTION: We must use a static cast here, even though SCAModel::Implementation
         //_is_ a base class of SCAModel::CPPImplementation and considering type safety a 
         //dynamic cast would be more appropriate. Unfortunately the SCAModel isn't allowed 
         //to contain polymorphic types because of binary compatibility issues. 
         const SCAModel::CPPImplementationPtr scaCPPImplementation = 
            boost::static_pointer_cast<SCAModel::CPPImplementation>(scaImplementation);      
         RuntimeModel::ConstContributionPtr cont = parentComposite->contribution().lock();
         return boost::make_shared<RuntimeModel::CPPImplementation>(cont->contributionInfo()->dataRegistry(),scaCPPImplementation);      
      }
      else
      {
         throw runtime_error
            ("Implementation type '" + scaImplementation->xsdType().toString() + "' not supported");
      }
   }

   //**********************************************************************************************
   //                                      resolvePromotion()
   //**********************************************************************************************
   //! \brief Constructs the promotion graphs for all the component's services and references.
   //!
   //! For more information on \a promotion see the corresponding documentation in 
   //! Trentino::RuntimeModel::Reference and Trentino::RuntimeModel::Service.
   //! \param[in] component A shared pointer to the component for whose services and references
   //!            the promotion graphs should be constructed.
   //! \attention This function must not be called before createComponent() is executed for
   //!            the given component, i.e. not before the the RuntimeModel object graph for the 
   //!            given component has been constructed. Otherwise, undefined behavior is the 
   //!            consequence. 
   //**********************************************************************************************
   void resolvePromotion(const RuntimeModel::ConstComponentPtr& component)
   {
      HLOGGER();   
      HLOGGER_INFO(component->uri().c_str());

      const RuntimeModel::ConstCompositePtr implComposite = 
         boost::dynamic_pointer_cast<RuntimeModel::Composite>(component->implementation());
      //resolvePromotion() must not be called for components not implemented by composites
      assert(implComposite);

      //process services
      BOOST_FOREACH(const RuntimeModel::ServiceBasePtr& service, component->services())
      {
         //1) find the composite service element with the same name as the given service
         const std::vector<SCAModel::ServicePtr>::const_iterator it =       
            find_if( implComposite->scaComposite()->serviceElements().begin()
                   , implComposite->scaComposite()->serviceElements().end()
                   , boost::bind(&SCAModel::Service::name, _1) == service->name());

         //this should have been validated at generation time 
         assert(it != implComposite->scaComposite()->serviceElements().end());

         //2) determine the service to which the given service is promoted 
         string promotedComponentName;
         string promotedServiceName;
         RuntimeModel::CommonFuncs::parseSCAWiringURI( 
            (*it)->promote(),  promotedComponentName, promotedServiceName );

         const RuntimeModel::ConstComponentPtr promotedComponent = 
            implComposite->findComponentByName(promotedComponentName);

         //this should have been validated at generation time 
         assert(promotedComponent);

         //"The service name can be omitted if the target component only has one service"
         //(Assembly Spec 1.1. line 1395 f.)
         RuntimeModel::ServiceBasePtr promotedService;
         if(promotedServiceName.empty())
         {
            assert(promotedComponent->services().size() == 1);
            promotedService = promotedComponent->services().front();            
         }
         else
         {
            promotedService = promotedComponent->findServiceByName(promotedServiceName);
         }

         //this should have been validated at generation time 
         assert(promotedService);
         service->setPromotedTo(promotedService);
         promotedService->addPromotedBy(service);
      } //BOOST_FOREACH(const RuntimeModel::ConstServiceBasePtr& service, component->services())
   
      //process references
      BOOST_FOREACH(const RuntimeModel::ReferenceBasePtr& reference, component->references())
      {
         //1) find the composite reference element with the same name as the given reference
         const vector<SCAModel::ReferencePtr>::const_iterator it = 
            find_if( implComposite->scaComposite()->referenceElements().begin()
                   , implComposite->scaComposite()->referenceElements().end()
                   , boost::bind(&SCAModel::Reference::name, _1) == reference->name());

         //this should have been validated at generation time 
         assert(it != implComposite->scaComposite()->referenceElements().end());

         //2) determine the references to which the given reference is promoted
         BOOST_FOREACH(const Trentino::XML::Schema::AnyURI& promoteTarget, (*it)->promotes())
         {
            string promotedComponentName;
            string promotedReferenceName;
            RuntimeModel::CommonFuncs::parseSCAWiringURI(
               promoteTarget, promotedComponentName, promotedReferenceName);

            const RuntimeModel::ConstComponentPtr promotedComponent = 
               implComposite->findComponentByName(promotedComponentName);

            //this should have been validated at generation time 
            assert(promotedComponent);

            //"The reference name can be omitted if the component has only one reference" 
            //(Assembly Spec 1.1. line 1506 f.)
            RuntimeModel::ReferenceBasePtr promotedReference;
            if(promotedReferenceName.empty())
            {
               assert(promotedComponent->references().size() == 1);
               promotedReference = promotedComponent->references().front();            
            }
            else
            {
               promotedReference = promotedComponent->findReferenceByName(promotedReferenceName);
            }

            //this should have been validated at generation time 
            assert(promotedReference);
            reference->addPromotedTo(promotedReference);
            promotedReference->addPromotedBy(reference);

         } //BOOST_FOREACH(const Trentino::XML::Schema::AnyURI& promoteTarget, (*it)->promotes())
      } //BOOST_FOREACH(const RuntimeModel::ReferenceBasePtr& reference, component->references())
   }

} //namespace 


//class RuntimeModelCreator
   //services
RuntimeModel::ContributionPtr RuntimeModelCreator::createContribution( 
   const SCAModel::ModelDescriptorPtr& scaModelDescriptor, 
   const Trentino::Utils::URI& baseURI, 
   const string& localPath,
   const Utils::DynamicLibraryPtr& contributionDLL,
   const DLLs businessDlls,
   Trentino::Core::TrentinoContributionInfo* contributionInfo )
{
   HLOGGER();   
   const RuntimeModel::ContributionPtr contribution = 
      boost::make_shared<RuntimeModel::Contribution>(scaModelDescriptor, baseURI);
   contribution->setLocalPath(localPath);
   contribution->setContributionLibrary(contributionDLL);
   contribution->setBusinessLibraries(businessDlls);      
   contribution->setContributionInfo(
      Trentino::Core::TrentinoContributionInfoPtr(contributionInfo));   

   return contribution;
}

RuntimeModel::CompositePtr RuntimeModelCreator::createComposite( 
   const SCAModel::CompositePtr& scaComposite, 
   const RuntimeModel::ContributionPtr& contribution )
{
   HLOGGER();   
   HLOGGER_INFO(scaComposite->name().c_str());

   const RuntimeModel::CompositePtr composite = 
      boost::make_shared<RuntimeModel::Composite>(scaComposite, contribution);

   //process <composite>/<component> elements
   const vector<SCAModel::ComponentPtr>& scaComponents = scaComposite->componentElements();
   
   BOOST_FOREACH(const SCAModel::ComponentPtr& scaComponent, scaComponents)
   {      
      const RuntimeModel::ComponentPtr component = 
         createComponent(composite, scaComponent); 
      assert(component.get() != nullptr);

      if( component->scaComponent()->implementationElement()->xsdType() 
         == Core::ContributionLoading::XSDTypeImplementationComposite)
      {
         resolvePromotion(component);
      }

      composite->addComponent(component);
   }
   
   contribution->addComposite(composite);
   return composite;
}
