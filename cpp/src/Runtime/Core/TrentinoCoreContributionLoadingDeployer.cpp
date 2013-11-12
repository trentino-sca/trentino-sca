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
#include "TrentinoCoreContributionLoadingDeployer.h"

//standard
#include <vector>
#include <queue>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/foreach.hpp>

//specific
#include "TrentinoCoreContributionLoadingRuntimeModelCreator.h"
#include "TrentinoCoreContributionLoadingErrorHandlerBase.h"
#include "TrentinoCoreContributionLoadingWiringException.h"
#include "TrentinoCoreContributionLoadingErrorMessageHelpers.h"
#include "TrentinoCoreComponentPropertyManager.h"
#include "TrentinoCoreDomain.h"
#include "TrentinoCoreBootstrappingRuntimeBootstrapper.h"
#include "../Discovery/TrentinoDiscoveryActivator.h"
#include "../RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "../RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "../RuntimeModel/TrentinoRuntimeModelComponent.h"
#include "../RuntimeModel/TrentinoRuntimeModelReference.h"
#include "../RuntimeModel/TrentinoRuntimeModelWire.h"
#include "../RuntimeModel/TrentinoRuntimeModelCommonFuncs.h"
#include "../SCAModel/TrentinoSCAModelDeployableType.h"
#include "../SCAModel/TrentinoSCAModelContributionType.h"
#include "../SCAModel/TrentinoSCAModelComposite.h"
#include "../SCAModel/TrentinoSCAModelComponent.h"
#include "../SCAModel/TrentinoSCAModelImplementation.h"
#include "../SCAModel/TrentinoSCAModelComponentService.h"
#include "../SCAModel/TrentinoSCAModelComponentTypeReference.h"
#include "../SCAModel/TrentinoSCAModelComponentReference.h"
#include "../SCAModel/TrentinoSCAModelInterface.h"
#include "../SCAModel/TrentinoSCAModelCPPInterface.h"
#include "../SCAModel/TrentinoSCAModelWire.h"
#include "../SCAModel/TrentinoSCAModelModelDescriptor.h"
#include "../Binding/TrentinoBindingBindingManagerBase.h"
#include "../ReflectionRuntime/TrentinoReflectionReflectObject.h"
#include "../Invocation/TrentinoInvocationInvocationContext.h"
#include "../XML/TrentinoXMLSchemaQName.h"
#include "../../Utils/TrentinoUtilsPatternStaticClass.h"
#include "../../Utils/TrentinoUtilsLogging.h"
#include "../../Utils/TrentinoUtilsPerformanceHierarchyLogger.h"

using namespace std;
using namespace Trentino;
using namespace Trentino::Core::ContributionLoading;
using namespace Trentino::Core::Bootstrapping;
using namespace Trentino::Discovery;
using namespace Trentino::ServiceRegistry;

namespace SCAModel = Trentino::SCA::Model;

namespace
{
   //**********************************************************************************************
   //                                       deleterProxy()
   //**********************************************************************************************
   //! \brief Custom deleter used by boost::shared_pointer in order to appropriately delete a 
   //!        proxy object that was created by the means of the reflection runtime and therefore
   //!        must not be deleted in the usual manner.
   //!
   //! \param[in] ptr Raw pointer to a proxy object.
   //**********************************************************************************************
   void deleterProxy(void* ptr)
   {
      HLOGGER();   
      if (ptr != nullptr)
      {
         //Trentino::Reflection::ReflectObject::deleteRegisteredInstance(ptr);
      }
   }
   
   //**********************************************************************************************
   //                                       compatible()
   //**********************************************************************************************
   //! \brief Tests for the compatibility of a reference and a service (aswering the question 
   //!        whether or not a wire can be established between them).
   //!
   //! \param[in] reference A shared pointer to the reference to test.
   //! \param[in] service A shared pointer to the service to test.
   //! \return \c true in case the interfaces are compatible, otherwise \c false.
   //!
   //! \note This is a very rudimentary and incomplete compatibility check!
   //! \todo Implement compatibility checking as described in Assembly Spec 1.1, chapter 6.2.1
   //**********************************************************************************************
   bool compatible( const RuntimeModel::ConstReferenceBasePtr& reference 
                  , const RuntimeModel::ConstServiceBasePtr& service)
   {
      HLOGGER();   
      HLOGGER_INFO(reference->name().c_str());

      const SCAModel::InterfacePtr referenceInterface = 
         reference->interfaceElement();
      const SCAModel::InterfacePtr serviceInterface =
         service->scaServiceType()->interfaceElement();

      if(   referenceInterface->xsdType() == XSDTypeInterfaceCPP
         && serviceInterface->xsdType() == XSDTypeInterfaceCPP)
      {
         const SCAModel::CPPInterfacePtr referenceCPPInterface = 
            boost::static_pointer_cast<SCAModel::CPPInterface>(referenceInterface);
         const SCAModel::CPPInterfacePtr serviceCPPInterface = 
            boost::static_pointer_cast<SCAModel::CPPInterface>(serviceInterface);
      
         //the simplest compatibility check is just to check the equality of the
         //interface classes
         return referenceCPPInterface->clazz() == serviceCPPInterface->clazz();
      }
   
      return false;   
   }
   
    //forward declarations
   void unwireReference(const RuntimeModel::ReferenceBasePtr& reference);
   void makeUnresolving(const RuntimeModel::ReferenceBasePtr& reference);
   void undeployComponent(const RuntimeModel::ComponentPtr& component);
   
   //**********************************************************************************************
   //                                   undeployComposite()
   //**********************************************************************************************
   //! \brief Undeployes the given composite by calling undeployComponent() for each of the 
   //!        contained components. 
   //!
   //! The composite is assigned the Trentino::RuntimeModel::Composite::Installed state. 
   //!
   //! \param[in] composite A shared pointer to the composite to undeploy.
   //**********************************************************************************************
   void undeployComposite(const RuntimeModel::CompositePtr& composite)
   {
      for_each( composite->components().begin()
              , composite->components().end()
              , boost::bind(undeployComponent, _1) );
   
      composite->setState(RuntimeModel::Composite::Installed);
   }

   //**********************************************************************************************
   //                                   undeployComponent()
   //**********************************************************************************************
   //! \brief Undeploys the given component.
   //!
   //! The following steps are performed by undeployComponent()
   //! -# For each reference:
   //!    -# makeUnresolving() is called in order to assgin the reference and all the references 
   //!       the reference is promoted to the temporary 
   //!       Trentino::RuntimeModel::Reference::Unresolving state. 
   //!    -# The reference is getting unwired with the help of unwireReference().
   //!    -# The reference is assigned the final Trentino::RuntimeModel::Reference::Initial state.
   //! -# In case the given component is implemented by a composite, the implementing composite
   //!    is getting undeployed with the help of undeployComposite().
   //! -# The component is assgined the Trentino::RuntimeModel::Component::Initial state.
   //!
   //! \param[in] component A shared pointer to the component to undeploy.
   //**********************************************************************************************
   void undeployComponent(const RuntimeModel::ComponentPtr& component) 
   {
      assert(component);  

      BOOST_FOREACH(const RuntimeModel::ReferenceBasePtr& reference, component->references())
      {
         makeUnresolving(reference);
         //[3] Remove all wires from the reference
         unwireReference(reference);
         assert(reference->wireableSupport().wires().empty());

         reference->setState(RuntimeModel::Reference::Initial);
      }

      if( component->scaComponent()->implementationElement()->xsdType() == 
            XSDTypeImplementationComposite )
      {
         const RuntimeModel::CompositePtr implComposite = 
               boost::dynamic_pointer_cast<RuntimeModel::Composite>(component->implementation());
         assert(implComposite);
         undeployComposite(implComposite);     
      }
  
      component->setState(RuntimeModel::Component::Initial);
   }

   
   //**********************************************************************************************
   //                                   unwireReference()
   //**********************************************************************************************
   //! \brief Removes all the wires from the given reference.
   //!
   //! \param[in] reference A shared pointer to the reference to unwire.
   //**********************************************************************************************
   void unwireReference(const RuntimeModel::ReferenceBasePtr& reference)
   {
      HLOGGER();   
      HLOGGER_INFO(reference->name().c_str());

      RuntimeModel::WireBases::iterator it = reference->wireableSupport().wires().begin();
      while(it != reference->wireableSupport().wires().end())
      {
         //use post increment due to iterator invalidation issues:
         //unwire() will erase the wire from the collection
         const RuntimeModel::WireBasePtr wire = *(it++);      
         assert(wire);
         wire->unwire();
      }   
   }

   //**********************************************************************************************
   //                                   makeUnresolving()
   //**********************************************************************************************
   //! \brief Assigns the given reference and all the references the reference is promoted to the
   //!        Trentino::RuntimeModel::Reference::Unresolving state.
   //!
   //! For more information on promotion see Trentino::RuntimeModel::Reference.
   //!
   //! \param[in] reference A shared pointer to the reference to process.
   //**********************************************************************************************
   void makeUnresolving(const RuntimeModel::ReferenceBasePtr& reference)
   {
      queue<RuntimeModel::ReferenceBaseWeakPtr> toVisit;
      toVisit.push(reference);      
      do
      {  
         const RuntimeModel::ReferenceBasePtr ref = toVisit.front().lock();
         assert(ref);      
         ref->setState(RuntimeModel::Reference::Unresolving);
         toVisit.pop();           

         BOOST_FOREACH(const RuntimeModel::ReferenceBaseWeakPtr& promotedRef, ref->promotedTo() )
         {
            toVisit.push(promotedRef);
         }
      }while(!toVisit.empty());
   }


} //namespace

//class Deployer
   //construction
Deployer::Deployer()
{}

Deployer::~Deployer()
{}

//services

void Deployer::deploy( const RuntimeModel::ContributionPtr& contribution )
{
   logInfo("deploying contribution '%s'...", contribution->baseURI().c_str());
   HLOGGER();   
   HLOGGER_INFO(contribution->baseURI().c_str());
   if(contribution->state() != RuntimeModel::Contribution::Installed)
   {
      throw invalid_argument( 
         "Cannot deploy a contribution that is not in '" + 
         RuntimeModel::CommonFuncs::toString( RuntimeModel::Contribution::Installed ) + 
         "' state." );
   }

   const SCAModel::ModelDescriptorPtr modelDescriptor = 
      contribution->scaModelDescriptor();
   assert(modelDescriptor);

   const vector<SCAModel::DeployableTypePtr>& scaDeployableTypes =
      modelDescriptor->contribution()->deployableElements();

   if(scaDeployableTypes.empty())
   {
      //! \todo this should not be an error but just an information
      //! => error handling concept must be refactored
      throw runtime_error(
         "contribution '" + contribution->baseURI() + "' has no deployable composites");
   }

   RuntimeModel::Composites deployableComposites;
   BOOST_FOREACH(const SCAModel::DeployableTypePtr& scaDeployableType, scaDeployableTypes)
   {
      const SCAModel::CompositePtr scaComposite = 
         modelDescriptor->findCompositeByQName(*scaDeployableType->composite());

      if(!scaComposite)
      {
         const string warningMsg = 
            "composite with QName '" + scaDeployableType->composite()->toString() +
            "' specified as deployable not found in contribution '" + 
            contribution->baseURI() + "' ";
         
         assert(errorHandler());
         errorHandler()->issueWarning(CompositeNotFoundWarning, warningMsg);

         continue;      
      }
   
      try
      {
         const RuntimeModel::CompositePtr composite = 
            RuntimeModelCreator::createComposite(scaComposite, contribution);       
         composite->setDeployable(true);
         deployableComposites.push_back(composite);
      }
      catch(ErrorException& e)
      {  
         const string errorMsg = 
            "composite with QName '" + scaDeployableType->composite()->toString() + 
            "' could not be deployed due to the following error: " + e.what();
         
         assert(errorHandler());
         errorHandler()->issueError(e.data(), errorMsg);
         HLOGGER_EXCEPTION(e.what());
      }
      catch(exception& e)
      {
          const string errorMsg = 
            "composite with QName '" + scaDeployableType->composite()->toString() + 
            "' could not be deployed due to the following error: " + e.what();
         
         assert(errorHandler());
         errorHandler()->issueError(CompositeNotDeployedError, errorMsg);
         HLOGGER_EXCEPTION(e.what());
      }      
   } //BOOST_FOREACH(const SCAModel::DeployableTypePtr& scaDeployableType, scaDeployableTypes)
      
   Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();

   Domain& domain = booter.domain();

   BOOST_FOREACH(RuntimeModel::CompositePtr& composite, deployableComposites)
   {  
      try
      {
         domain.addToDomainLevelComposite(composite);
         deployComposite(composite);         
      }
      catch(ErrorException& e)
      {  
         const string errorMsg = 
            "composite with QName '" + composite->qName().toString() + 
            "' could not be deployed due to the following error: " + e.what();
         
         assert(errorHandler());
         errorHandler()->issueError(e.data(), errorMsg);
         HLOGGER_EXCEPTION(e.what());

         domain.removeFromDomainLevelComposite(composite);
         contribution->removeComposite(composite);    
         undeployComposite(composite);
      }
      catch(exception& e)
      {
         const string errorMsg = 
            "composite with QName '" + composite->qName().toString() + 
            "' could not be deployed due to the following error: " + e.what();

         assert(errorHandler());
         errorHandler()->issueError(CompositeNotDeployedError, errorMsg);
         HLOGGER_EXCEPTION(e.what());

         domain.removeFromDomainLevelComposite(composite);
         contribution->removeComposite(composite); 
         undeployComposite(composite);
      }
   } //BOOST_FOREACH(RuntimeModel::CompositePtr& composite, deployableComposites)

   const unsigned int deployedComposites = 
      count_if( deployableComposites.begin()
              , deployableComposites.end()
              , boost::bind(&RuntimeModel::Composite::state, _1) == 
                  RuntimeModel::Composite::Deployed);

   if(deployedComposites == 0)
   {      
      throw runtime_error(
         "None of the deployable composites in contribution '" + contribution->baseURI() +
         "' could be deployed");         
   }

   Trentino::Binding::BindingManagerBasePtr bindingManager = booter.bindingManagerBasePtr();
   //now tell the BindingManager to handle the new contribution.
   //the Binding manager returns true if the contribution was handled correctly
   const bool isHandlingOK = bindingManager->onDeploy(contribution);
   if(!isHandlingOK)
   {
      throw runtime_error(
         "Error when configuring biding for contribution '" + contribution->baseURI() +
         "'.\n See previous messages for more details");   
   }
   contribution->setState(RuntimeModel::Contribution::Deployed);
   logInfo("contribution '%s' deployed!", contribution->baseURI().c_str() );

   // now register remotable services
   ServiceRegistryPtr serviceRegistry = RuntimeBootstrapper::instance().serviceRegistry();
   DiscoveryActivator *da = RuntimeBootstrapper::instance().discoveryActivator();
   da->registerRemotableServices(serviceRegistry->findRemotableServices(contribution->baseURI()));

   // And now go and discover services
   da->discoverServices(serviceRegistry->findRemoteReferences(contribution->baseURI()));
}


void Deployer::undeploy( const RuntimeModel::ContributionPtr& contribution )
{
   if( contribution->state() != RuntimeModel::Contribution::Deployed )
   {
      throw invalid_argument( 
         "Cannot undeploy a contribution that is in '" + 
         RuntimeModel::CommonFuncs::toString( contribution->state() ) + "' state." );
   }
   Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
   Trentino::Core::Domain& domain = booter.domain() ;

   BOOST_FOREACH(const RuntimeModel::CompositePtr& composite, contribution->composites())
   {
      if(composite->isDeployable())
      {  
         domain.removeFromDomainLevelComposite(composite); 
         undeployComposite(composite);         
      }
   }

   contribution->disposeComposites();
   // now deregister remotable services
   ServiceRegistryPtr serviceRegistry = RuntimeBootstrapper::instance().serviceRegistry();
   DiscoveryActivator *da = RuntimeBootstrapper::instance().discoveryActivator();
   da->deregisterServices(serviceRegistry->findRemotableServices(contribution->baseURI()));

   contribution->setState(RuntimeModel::Contribution::Installed);
}

   //management
Deployer::DeployCompositeResult Deployer::deployComposite(
   const RuntimeModel::CompositePtr& composite)
{  
   HLOGGER();   
   HLOGGER_INFO(composite->qName().toString().c_str());

   SCAWiresSet availableSCAWires( composite->scaComposite()->wireElements().begin()
                                , composite->scaComposite()->wireElements().end() );   
   
   //1) try to deploy all the components in the composite
   ComponentsSet componentsToDeploy( composite->components().begin()
                                   , composite->components().end() );

   
   DeployCompositeResult result = NoUnresolvedComponents;
   while(!componentsToDeploy.empty())
   {
      const RuntimeModel::ComponentPtr component = *componentsToDeploy.begin();
      componentsToDeploy.erase(componentsToDeploy.begin());
      deployComponent( component
                     , componentsToDeploy
                     , availableSCAWires);     
      if(component->state() == RuntimeModel::Component::Unresolved)
      {
         result = HasUnresolvedComponents;
      }      
   }

   //2) try to deploy the left <wire> elements 
   //
   //After deployComponent() is executed, availableSCAWires may contain unprocced <wire> elements.
   //There may be three reasons for why they were not processed:
   //(1) The component mentioned in the @source attribute is not contained in the composite
   //    currently being deployed.
   //(2) The reference mentioned in the @source attribute doesn't exist.
   //(3) The @source attribute contains only a component name but the target component has no
   //    references at all.
   //Case (1) might still represent a valid wire whose @source attribute points to a component
   //not contained in the current composite but in the virtual domain level composite.
   //So process the left <wire> elements in order to perform wiring for domain-level components or
   //discover erroneous wires and issue the errors. 
   for_each( availableSCAWires.begin()
           , availableSCAWires.end()
           , boost::bind(&Deployer::deployWire, this, composite, _1) );

   composite->setState(RuntimeModel::Composite::Deployed);
   return result;
}

void Deployer::deployComponent( const RuntimeModel::ComponentPtr& component
                              , Deployer::ComponentsSet& leftComponentsToDeploy
                              , Deployer::SCAWiresSet& availableSCAWires)
{
   HLOGGER();   
   HLOGGER_INFO(component->uri().c_str());

   //DON'T CHANGE THE ORDER OF THE FOLLOWING METHOD CALLS!!!
   //assignValuesFromSCAModel() must be executed before wireComponent()!
   //For components implemented by composites, wireComponent() will trigger the deployment of 
   //the implementation composites that in turn will trigger the deployment of the contained
   //components. When assignValuesFromSCAModel() is executed for these components, it expects the
   //property values for the parent component (i.e. the current component in this method) 
   //to be set.

   // 1)
      Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
      Trentino::Core::ComponentPropertyManager& componentPropertyManager = booter.componentPropertyManager();


   BOOST_FOREACH(const RuntimeModel::PropertyPtr& property, component->properties())
   {
      componentPropertyManager.assignValuesFromSCAModel(property);
   }

   // 2)
   wireComponent(component, leftComponentsToDeploy, availableSCAWires);
}

void Deployer::deployWire( const RuntimeModel::ConstCompositePtr& composite
                         , const SCAModel::WirePtr& wireElement )
{ 
   //After deployComponent() is executed, there may still be some unprocessed  <wire> elements.
   //There may be three reasons for why they were not processed:
   //(1) The component mentioned in the @source attribute is not contained in the composite
   //    currently being deployed.
   //(2) The reference mentioned in the @source attribute doesn't exist.
   //(3) The @source attribute contains only a component name but the target component has no
   //    references at all.
   //Case (1) might still represent a valid wire whose @source attribute points to a component
   //not contained in the current composite but in the virtual domain level composite.  
   
   string sourceComponentName;
   string sourceReferenceName;
   RuntimeModel::CommonFuncs::parseSCAWiringURI( wireElement->source()
                                               , sourceComponentName
                                               , sourceReferenceName ); 

   const RuntimeModel::ConstComponentPtr sourceComponent = 
      composite->findComponentByName(sourceComponentName);
   if(sourceComponent) //case (2) or (3)
   {
      if(sourceReferenceName.empty())
      {
         //case (3): if sourceComponent would have any references, 
         //the given <wire> element would already have been processed.
         assert(sourceComponent->references().empty());
      }
      else
      {         
         //case (2): if sourceReferenceName would point to an existent reference, 
         //the given <wire> element would already have been processed.
         assert(!sourceComponent->findReferenceByName(sourceReferenceName));
      }
         
      const string errorMessage = 
            errorMessageComponent("reference not found", sourceComponentName) + " " +
            errorMessageReferencedInWire("@source", composite);
      assert(errorHandler());
      errorHandler()->issueError(ReferenceNotFoundError, errorMessage); 
   }
   else //case (1)
   {  
     Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();

      Trentino::Core::Domain& domain = booter.domain();
  
      const RuntimeModel::ConstComponentPtr sourceDomainLevelComponent = 
         domain.findDomainLevelComponentByName(sourceComponentName);

      if(sourceDomainLevelComponent)
      {
         RuntimeModel::ReferenceBasePtr sourceReference;
         if(sourceReferenceName.empty())
         {            
            //The reference name can be omitted if the source component only has one reference
            //Assembly Spec 1.1 line 1876 f.
            if(sourceDomainLevelComponent->references().size() == 1)
            {               
               sourceReference = sourceDomainLevelComponent->references().front(); 
               assert(sourceReference);
            }
            else if(sourceDomainLevelComponent->references().size() > 1)
            {
               const string errorMessage = 
                  errorMessageComponent("ambiguous references", sourceComponentName) + " " +
                  errorMessageReferencedInWire("@source", composite);
               assert(errorHandler());
               errorHandler()->issueError(AmbigousReferencesError, errorMessage); 
            } //else if(sourceDomainLevelComponent->references().size() > 1)              
         }
         else
         {
            sourceReference = 
               sourceDomainLevelComponent->findReferenceByName(sourceReferenceName);               
               
         } //if(sourceReferenceName.empty()){...}else{...}

         if(sourceReference)
         {            
            try
            {                  
               //in this case wireReferenceToTarget() will not deploy any components
               //so we can pass an empty component and wires set
               ComponentsSet emptyComponentsSet;
               SCAWiresSet emptySCAWiresSet;
               wireReferenceToTarget( sourceReference
                                    , wireElement->target()
                                    , emptyComponentsSet
                                    , emptySCAWiresSet );
            }
            catch(WiringException& e)
            {  
               processWiringException( 
                  e, errorMessageReferencedInWire("@target", composite) );
            }
         }
         else
         {
            const string errorMessage = 
               errorMessageComponent("reference not found", sourceComponentName) + " " +
               errorMessageReferencedInWire("@source", composite);
            assert(errorHandler());
            errorHandler()->issueError(ReferenceNotFoundError, errorMessage); 
         }
      }
      else
      {
         const string errorMessage = 
            errorMessageComponent("component not found", sourceComponentName) + " " +
            errorMessageReferencedInWire("@source", composite);
         assert(errorHandler());
         errorHandler()->issueError(ComponentNotFoundError, errorMessage); 
      } //if(sourceDomainLevelComponent){...}else{...}
   }//if(sourceComponent){...}else{...} 
}

void Deployer::wireComponent( const RuntimeModel::ComponentPtr& component
                            , ComponentsSet& leftComponentsToDeploy
                            , SCAWiresSet& availableSCAWires)
{
   HLOGGER();   
   HLOGGER_INFO(component->uri().c_str());

   //a component that is currently being resolved MUST NOT be resolved twice
   assert(component->state() != RuntimeModel::Component::Resolving);  
   //a component that is currently being resolved MUST NOT be in Stopping state 
   assert(component->state() != RuntimeModel::Component::Stopping);
   //For now we assume that resolved components must not be processed by deployComponent(). 
   //This might change in future. 
   assert(component->state() != RuntimeModel::Component::Resolved);
      
   //We start to resolve the component by trying to wire (=resolve) all of its references.
   component->setState(RuntimeModel::Component::Resolving);
   
   //assume that the component will be in Resolved state an the end
   RuntimeModel::Component::State finalComponentState = RuntimeModel::Component::Resolved;
   BOOST_FOREACH(const RuntimeModel::ReferenceBasePtr& reference, component->references())
   {  
      //For now assume that it will be never necessary to wire a reference that is already
      //resolved during the resolving process for a whole component. Yes, in case of rewiring
      //it might become necessary but in that cast wireReference() or its future 'rewire' 
      //counterpart won't be called from here. 
      if(reference->state() != RuntimeModel::Reference::Resolved)
      {
         //***************** TRY TO WIRE THE REFERENCE  *******************
         wireReference(reference, leftComponentsToDeploy, availableSCAWires);
         //****************************************************************
         
         //a reference should definitely have a stable state after wiring
         assert(reference->state() != RuntimeModel::Reference::Resolving);
         assert(reference->state() != RuntimeModel::Reference::Unresolving);
         assert(reference->state() != RuntimeModel::Reference::Initial);
         
         //If the component's final state has already been set to Unresolved because the wiring 
         //of one of the previously processed references didn't succeed, it cannot be changed 
         //anymore (see definition for Component::Unresolved)
         if(finalComponentState != RuntimeModel::Component::Unresolved)
         {  
            if(reference->state() == RuntimeModel::Reference::Unresolved)
            {
               finalComponentState = RuntimeModel::Component::Unresolved;
            }
            else if(reference->state() == RuntimeModel::Reference::OptionalUnresolved)
            {      
               finalComponentState = RuntimeModel::Component::OptionalUnresolved;
            }
         }         
      } //if(reference->state() != RuntimeModel::Reference::Resolved)            
   } //BOOST_FOREACH(const RuntimeModel::ReferenceBasePtr& reference, component->references())
      
   //For components implemented by composites, it's not only necessary to wire its references
   //(which actually are promoted to further references) but also to wire its implementing
   //composite to reach a valid state.
   if( component->scaComponent()->implementationElement()->xsdType() == 
      XSDTypeImplementationComposite )
   {
      //If the wiring of the references has not succeed (and thus the component is in Unresolved 
      //state) it's also not necessary to try to wire the implementing composite 
      if(finalComponentState != RuntimeModel::Component::Unresolved)
      {
         const RuntimeModel::CompositePtr implComposite = 
            boost::dynamic_pointer_cast<RuntimeModel::Composite>(component->implementation());
         assert(implComposite);
                  
         if(deployComposite(implComposite) == HasUnresolvedComponents)
         {
            //! remove created wires 
            BOOST_FOREACH(const RuntimeModel::ReferenceBasePtr& reference, component->references())
            {
               unwireReference(reference);
               reference->setState(RuntimeModel::Reference::Unresolved);
            }
                       
            undeployComposite(implComposite);
            finalComponentState = RuntimeModel::Component::Unresolved;
         }        
      }
   }

   component->setState(finalComponentState);        
}

void Deployer::wireReference( const RuntimeModel::ReferenceBasePtr& reference
                            , ComponentsSet& leftComponentsToDeploy
                            , SCAWiresSet& availableSCAWires)
{
   HLOGGER();
   HLOGGER_INFO(reference->name().c_str());

   //For now we assume that already resolved references can't be proccess by wireReference().
   //This might change in future once rewiring is supported.
   assert(reference->state() != RuntimeModel::Reference::Resolved);
   //A reference that is currently being resolved MUST NOT be in Unresolving state 
   assert(reference->state() != RuntimeModel::Reference::Unresolving);

   const RuntimeModel::ConstComponentPtr component = reference->component().lock();
   assert(component);
   const RuntimeModel::ConstCompositePtr composite = component->composite().lock();
   assert(composite); 
   //the given composite is used as implementation in case it has a parent component
   const bool isCompositeUsedAsImplementation = 
      (composite->component().lock().get() != nullptr);
   
   //In case of a domain-level composite a reference that is currently being resolved MUST NOT
   //be resolved twice. In case of a composite used as implementation a promoted reference might 
   //have been set to Resolving state by the parent component (because it configured own targets 
   //on it) but might still be in Resolving state because now the component contained in the
   //implementing composite has the chance to configure further targets on. Consequently:
   //If we are processing a domain-level composite it IS an error to reprocess a reference in 
   //Resolving state, in case of composites used as implementation it's NOT an error.   
   assert(!isCompositeUsedAsImplementation ? 
      reference->state() != RuntimeModel::Reference::Resolving : true);
   
   if(isCompositeUsedAsImplementation)
   {
      //Are there any wires already configured through promotion??
      if(!reference->wireableSupport().wires().empty())
      {          
         const bool isNonOverridable = reference->isNonOverridable();        
         if(isNonOverridable == false)
         {
            //Don't add own targets but take those configured through promotion
            reference->setState(RuntimeModel::Reference::Resolved);
            return;
         }
           
      } //if(reference->state() == RuntimeModel::Reference::Resolved)
   }
   
   //set the state of all the reference and all the promoted references to Resolving
   //! \todo encapsulate this algorithm in a "promotion iterator" class
   queue<RuntimeModel::ReferenceBaseWeakPtr> toVisit;
   toVisit.push(reference);      
   do
   {  
      const RuntimeModel::ReferenceBasePtr ref = toVisit.front().lock();
      assert(ref);      
      toVisit.pop();
      ref->setState(RuntimeModel::Reference::Resolving);      

      BOOST_FOREACH(const RuntimeModel::ReferenceBaseWeakPtr& promotedRef, ref->promotedTo())
      {
         toVisit.push(promotedRef);
      }
   }while(!toVisit.empty());
   
   //copy the wires having this reference as source from availabeSCAWires to myWires and remove
   //them from availableSCAWires
   vector<SCAModel::WirePtr> myWires;   
   SCAWiresSet::const_iterator it = availableSCAWires.begin();
   while(it != availableSCAWires.end())
   {
      string sourceComponentName;
      string sourceReferenceName ;
      RuntimeModel::CommonFuncs::parseSCAWiringURI( (*it)->source()
                                                  , sourceComponentName
                                                  , sourceReferenceName );      
      //Is this the reference's parent component?
      if(sourceComponentName == component->scaComponent()->name())
      {
         if(sourceReferenceName.empty())
         {
            //The reference name can be omitted if the source component only has one reference
            //Assembly Spec 1.1 line 1876 f.
            if(component->references().size() == 1)
            {               
               //If the parent component has only one reference, then this must be the reference
               //that is currently processed, so put it in myWires
               myWires.push_back(*it);                
            }
            else if(component->references().size() > 1)
            {
               const string errorMessage = 
                  errorMessageComponent("ambiguous references", sourceComponentName) + " " +
                  errorMessageReferencedInWire("@source", composite);
               assert(errorHandler());
               errorHandler()->issueError(AmbigousReferencesError, errorMessage); 
            }
            else
            {
               const string errorMessage = 
                  errorMessageComponent("reference not found", sourceComponentName) + " " +
                  errorMessageReferencedInWire("@source", composite);
               assert(errorHandler());
               errorHandler()->issueError(ReferenceNotFoundError, errorMessage); 
            }

            //In all cases the wire can be erased from the availabeSCAWires because it doesn't
            //have to be processed further outside of this function (either it's a erroneous wire
            //and the error has already been issued in the else-case or it will be processed as 
            //part of myWires 
            availableSCAWires.erase(it++);
         }
         else
         {
            //Is the current reference the source of the wire?
            if(sourceReferenceName == reference->name())  
            {
               myWires.push_back(*it);
               availableSCAWires.erase(it++);
            }
            else
            {
               ++it;               
            }   
         } //if(sourceReferenceName.empty()){...}else{...}                 
      } //if(componentName == component->scaComponent()->name())
      else
      {            
         //The wire was not copied to myWires, so no need for erasing it, 
         //just process the next one
         ++it;
      }
   } //while(it != availableSCAWires.end())   

      
   //Put all the targets from the <reference>/@target attribute ((Assembly Spec 1.1 line 939)
   //as well as from the @target attributes of all the <wire> elements pointing to the
   //current reference (Assembly Spec 1.1. lines 1876) in one container to be able to 
   //process them homogeneously (in one loop) without  duplicating code .   
   


   vector<string> targets;
      //First copy the targets from <reference>/@target
   const vector<string>& scaTargets =  reference->targets();
   for(vector<string>::const_iterator it2=scaTargets.begin(); it2!= scaTargets.end(); ++it2)
      {
      targets.push_back(*it2);
      }

      //now append the targets from <wire>/@target
   for(vector<SCAModel::WirePtr>::const_iterator wItr =myWires.begin(); wItr!=myWires.end(); ++wItr)
      {
      targets.push_back((*wItr)->target());
      }
      
   //In following we assume that there is no mismatch between <reference>/@multiplicity 
   //and the actual number of wires defined for this reference because this should have been
   //validated at generation time. Let's express this assumption through asserts.
   const string multiplicity = reference->multiplicity();
   
   //Iterate over all the targets for the reference and try to wire them.   
   for(unsigned int i = 0; i < targets.size(); i++) 
   {
      try
      {
         //this function MUST NOT change the state of the reference
         wireReferenceToTarget( reference
                              , targets[i] 
                              , leftComponentsToDeploy
                              , availableSCAWires ); 
      }
      catch(WiringException& e)
      {  
         //this assumes that all the targets from <reference>/@target are processed before
         //all the targets from <wire>/@target 
         const string referencedIn = i < reference->targets().size() ? 
              errorMessageReferencedInReference(reference, "@target")
            : errorMessageReferencedInWire("@target", composite);

         processWiringException(e, referencedIn);
      } //try{...}catch(){...}      
   } //for(unsigned int i = 0; i < targets.size(); i++)  
   

   if(!reference->wireableSupport().wires().empty())
   {
      reference->setState(RuntimeModel::Reference::Resolved);
   }
   else
   {
      //If the reference couldn't be resolved but is optional (i.e. multiplicity="0..1" or "0..n")
      //set the state to OptionalUnresolved.
      if(    multiplicity == SCAModel::ReferenceMultiplicity0to1  
          || multiplicity == SCAModel::ReferenceMultiplicity0toN ) 
      {
         reference->setState(RuntimeModel::Reference::OptionalUnresolved);
      }
      else
      {
         reference->setState(RuntimeModel::Reference::Unresolved);
      }
   }
}

void Deployer::wireReferenceToTarget( const RuntimeModel::ReferenceBasePtr& reference
                                    , const Trentino::XML::Schema::AnyURI& target
                                    , ComponentsSet& leftComponentsToDeploy
                                    , SCAWiresSet& availableSCAWires)
{
   HLOGGER();   
   HLOGGER_INFO(reference->name().c_str());

   const RuntimeModel::ConstComponentPtr component = reference->component().lock();
   assert(component);
   const RuntimeModel::ConstCompositePtr composite = component->composite().lock();
   assert(composite);
   //the given composite is used as implementation in case it has a parent component
   const bool isCompositeUsedAsImplementation = 
      (composite->component().lock().get() != nullptr);
     Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
     Trentino::Core::Domain& domain = booter.domain();

   string targetComponentName;
   string targetServiceName;

   RuntimeModel::CommonFuncs::parseSCAWiringURI(target, targetComponentName, targetServiceName );

   //find target component
   RuntimeModel::ComponentPtr targetComponent;
   if(isCompositeUsedAsImplementation)
   {
      //"For a composite used as a component implementation, wires can only link sources
      //and targets that are contained in the same composite" 
      //(Assembly Spec 1.1 lines 1890 ff. and 980 ff.)
      targetComponent = composite->findComponentByName(targetComponentName);   
   }
   else
   {
      //For a domain level composite, the search is performed domain-wide.
      //Here it's assumed that the components from the current composite already
      //have been added to the virtual domain level composite (before the wiring is
      //performed). So that we don't need to search additionally separately inside
      //the current composite. 
      targetComponent = domain.findDomainLevelComponentByName(targetComponentName);
   }

   if(!targetComponent)
   {  
      //implication of [ASM60047]
      throw WiringException( ComponentNotFoundError
                           , "component not found"
                           , targetComponentName);      
   }

   //find target service
   assert(targetComponent);
   RuntimeModel::ServiceBasePtr targetService;
   if(!targetServiceName.empty())
   {
      targetService = targetComponent->findServiceByName(targetServiceName);
      if(!targetService)
      {
         throw WiringException( ServiceNotFoundError
                              , "service not found"
                              , targetComponentName
                              , targetServiceName);         
      }

      if( !compatible(reference, targetService) )
      {
         throw WiringException( ServiceIncombatibleError
                              ,"service incompatible"
                              , targetComponentName
                              , targetServiceName);         
      }
   }
   else //if no service name specified
   {
      //find one compatible service implemented by the target component
      BOOST_FOREACH ( const RuntimeModel::ServiceBasePtr& service
         , targetComponent->services() )
      {
         if(compatible(reference, service))
         {
            //If the component has more than one compatible service, it's an error.
            //[ASM60048]
            if(targetService)
            {
               throw WiringException( AmbigousServicesError
                                    , "ambiguous services"
                                    , targetComponentName);
            }
            
            targetService = service;            
         }
      } // BOOST_FOREACH ( const RuntimeModel::ConstServiceBasePtr& service...

      //If the component has no compatible services, it's an error.
      //[ASM60048]
      if(!targetService)
      {
         throw WiringException( NoCompatibleServicesError
                              , "no compatible services"
                              , targetComponentName);         
      }
   } //if(!targetServiceName.empty()){...}else{...} 


   if(targetComponent->state() == RuntimeModel::Component::Initial)
   {      
      //the component can be in Initial state only if it's part of the current composite 
      //and has not been processed so far 
      const ComponentsSet::const_iterator it = 
         leftComponentsToDeploy.find(targetComponent);
      assert(it != leftComponentsToDeploy.end());
      
      //so let's try to resolve it 
      leftComponentsToDeploy.erase(it);
      deployComponent(targetComponent, leftComponentsToDeploy, availableSCAWires);
   }

   if(targetComponent->state() == RuntimeModel::Component::Unresolved)
   {
      //Now the component could be in unresolved state for the following reasons:
      //1) It's not part of the composite currently being deployed (i.e.has been deployed
      //   previously as part of another composite) and is left in Undeployed state due to
      //   some errors.
      //2) It is part of the current composite, has already been processed but left in 
      //   Unresolved state due to some errors
     
      //In any case, we cannot wire to an unresolved component
      throw WiringException( ComponentUnresolvedError
                           , "component unresolved"
                           , targetComponentName);      
   }
   else if(targetComponent->state() == RuntimeModel::Component::Resolving)
   {
      //We try to wire to a component that is currently being resolved, this 
      //is a cyclic dependency (see also RuntimeModel::Component::State::Resolving)
      throw WiringException( CyclicDependencyError
                           , "Component in 'Resolving' state. " 
                             "Cyclic dependencies currently not supported!"
                           , targetComponentName);
   }

   assert(targetComponent->state() != RuntimeModel::Component::Unresolved);
   assert(targetService);
   assert(targetService->state() == RuntimeModel::ServiceBase::Available);

   //********************************* ESTABLISH THE WIRE ***********************************
   const RuntimeModel::WireBasePtr theWire = RuntimeModel::Wire::create(reference, targetService);   
   assert(theWire);
   //create proxy instance 
   const Trentino::Reflection::ReflectObjectPtr proxyReflectObject = 
      reference->proxyReflectObject();
   assert(proxyReflectObject);
   void* theWireRaw = theWire.get();
   void* ctrParams[] = {&theWireRaw}; //wire is passed to the proxy instance 
   void* const proxyInstance = 
      proxyReflectObject->newInstance(component->dataRegistry(),
         vector<string>(1, "Trentino::RuntimeModel::Wire *"),
         ctrParams, 
         true );
   if(!proxyInstance)
   {
      const string errorMsg = 
         string("Could not create service proxy instance of class '")  + 
         proxyReflectObject->className() + "' for reference with @name='" + reference->name() + 
         "'in component with @name='" +  component->scaComponent()->name() + 
         "' in composite with @name='" + composite->scaComposite()->name();
      throw ErrorException(ProxyInstanceNotCreatedError, errorMsg);      
   }

   //! \todo sharing of proxy instances (proxy registry)?
   theWire->setProxy( RuntimeModel::ProxyPtr(proxyInstance, deleterProxy) );
   
   //create invocation context
   const Trentino::Invocation::InvocationContextPtr invocationContext =
      boost::make_shared<Trentino::Invocation::InvocationContext>();
   invocationContext->setCurrentInvoker(RuntimeBootstrapper::instance().invoker());
   theWire->setInvocationContext(invocationContext);
   
   //execute the wiring
   theWire->wire(); 
}

void Deployer::processWiringException( const WiringException& e
                                     , const string& referencedIn)
{
   string errorMessage = e.hasServiceInfo() ? 
         errorMessageService( e.targetComponentName(), e.targetServiceName(), e.what() )
      : errorMessageComponent( e.targetComponentName(), e.what() );
   errorMessage += " " + referencedIn;
   assert(errorHandler());
   errorHandler()->issueError(e.data(), errorMessage);
         
   HLOGGER_EXCEPTION(errorMessage.c_str());
}
