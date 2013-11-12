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

#ifndef TrentinoCoreContributionLoadingDeployerH
#define TrentinoCoreContributionLoadingDeployerH

//baseclasse
#include "TrentinoCoreContributionLoadingErrorReporter.h"

//standard
#include <set>

//specific
#include "../RuntimeModel/TrentinoRuntimeModel.h"
#include "../SCAModel/TrentinoSCAModel.h"
#include "../XML/TrentinoXMLSchema.h"

namespace Trentino{
namespace Core{
namespace ContributionLoading
{
   class WiringException;

   //**********************************************************************************************
   //                                       Deployer
   //**********************************************************************************************
   //! \ingroup ContributionLoading
   //! \brief Responsible for putting a contribution into the 
   //!        RuntimeModel::Contribution::Deployed state. 
   //!
   //! For clients, it's not necessary no use the Deployer class directly, instead its  
   //! functionality is provided through the facade class ContributionLoader.  
   //**********************************************************************************************
   class Deployer : public ErrorReporter
   {
      //additional
   private:
      typedef std::set<Trentino::SCA::Model::WirePtr> SCAWiresSet;
      typedef std::set<Trentino::RuntimeModel::ComponentPtr> ComponentsSet;
      enum DeployCompositeResult {NoUnresolvedComponents, HasUnresolvedComponents};
      //construction
   public:
      //*******************************************************************************************
      //                                      Deployer()
      //*******************************************************************************************
      //! \brief Empty constructor.      
      //*******************************************************************************************
      Deployer();

      //*******************************************************************************************
      //                                      ~Deployer()
      //*******************************************************************************************
      //! \brief Empty destructor.      
      //*******************************************************************************************
      ~Deployer();
   private:
      //*******************************************************************************************
      //                               Deployer(const Deployer&)
      //*******************************************************************************************
      //! \brief Disallow inadvertent copying.      
      //*******************************************************************************************
      Deployer(const Deployer&);

      //operators
   private:
      //*******************************************************************************************
      //                                      operator=()
      //*******************************************************************************************
      //! \brief Disallow inadvertent assignment.      
      //*******************************************************************************************
      void operator=(const Deployer&);

      //services
   public:
      //*******************************************************************************************
      //                                         deploy()
      //*******************************************************************************************
      //! \brief Performs several steps necessary to transfer a contribution from the 
      //!        RuntimeModel::Contribution::Installed to the RuntimeModel::Contribution::Deployed 
      //!        state.
      //!      
      //! During the deployment process, following steps are performed:
      //! -# The RuntimeModel representation is created for the whole contribution (with the 
      //!    exception for the RuntimeModel::Contribution object itself that is already created
      //!    during the installation step (see ContributionLoading::Installer)).
      //! -# For each deployable composite attempts are made to deploy it:
      //!   -# Wiring is performed for each component (RuntimeModel::Wire objects are created).
      //!      As a consequence, each component and each of its references are assigned one of the 
      //!      following states: RuntimeModel::Component::Resolved, 
      //!      RuntimeModel::Component::Unresolved or RuntimeModel::Component::OptionalUnresolved
      //!      (for the component itself) and RuntimeModel::Reference::Resolved, 
      //!      RuntimeModel::Reference::Unresolved or RuntimeModel::Reference::OptionalUnresolved
      //!      (for the references).
      //!   -# Composites serving as component implementations are deployed recursively .
      //!   -# Component property values are getting assigned (e.g read from files).      
      //!   -# If no critical errors occurred:
      //!     - All the components in the deployed composite are added to the virtual domain level 
      //!       composite, i.e. become visible domain-wide. 
      //!     - The composite is assigned the RuntimeModel::Composite::Deployed state (the same
      //!       holds also for non-deployable composites indirectly referenced as component
      //!       implementations).
      //! -# If <em>et least</em> one composite could be deployed successfully, the contribution
      //!    is assigned the RuntimeModel::Contribution::Deployed state.
      //!
      //! \param[in] contribution A shared pointer to the contribution to deploy.
      //! \throw std::invalid_argument In case the contribution is not in the 
      //!        RuntimeModel::Contribution::Installed state.
      //! \throw std::runtime_error In case the contribution contains no deployable composites
      //! \throw std::runtime_error In case none of the deployable composites in the contribution
      //!        could be deployed. 
      //! \throw std::runtime_error In case there was an error in cofiguring bindings.
      //!
      //! \note Component implementations are \b not instantiated during the deployment process.
      //!       Consequently, all the performed actions (such as wiring or property value 
      //!       assignment) are not reflected to the business logic (through injection etc.) but
      //!       only inside of in-memory runtime structures (such as RuntimeModel or Core::Domain)
      //!       The instantiation happens when the contribution is put into the 
      //!       RuntimeModel::Contribution::Running state (see ContributionLoading::Runner). 
      //! \sa deployComposite(), deployComponent(), deployWire(), wireComponent(), wireReference(),
      //!     wireReferenceToTarget()
      //*******************************************************************************************
      void deploy(const Trentino::RuntimeModel::ContributionPtr& contribution);

      //*******************************************************************************************
      //                                         undeploy()
      //*******************************************************************************************
      //! \brief Performs several steps necessary to transfer a contribution from the 
      //!        RuntimeModel::Contribution::Deployed to the RuntimeModel::Contribution::Installed
      //!        state.
      //!      
      //! During the undeployment process, following steps are performed:
      //! -# For each deployable composite:
      //!    -# Components are removed from the virtual domain level composite, thus becoming
      //!       invisible domain wide. 
      //!    -# All the components are getting unwired with the consequence that the components 
      //!       theirselves and all of their reference is assigned the 
      //!       RuntimeModel::Component::Initial and RuntimeModel::Reference::Initial state, 
      //!       respectively. 
      //!    -# The composite is assigned the RuntimeModel::Composite::Installed state.
      //! -# The complete in-memory RuntimeModel created during deployment is destroyed (with the 
      //!    exception for the RuntimeModel::Contribution object itself, it's needed to further 
      //!    represent the contribution in the RuntimeModel::Contribution::Installed state).
      //! -# The contribution is assigned the RuntimeModel::Contribution::Installed state.       
      //! 
      //! \param[in] contribution A shared pointer to the contribution to undeploy.
      //! \throw std::invalid_argument In case the contribution is not in the 
      //!        RuntimeModel::Contribution::Deployed state.
      //!
      //! \note Component implementations are \b not destroyed during the undeployment process.
      //!       Consequently, all the performed actions are not reflected to the business logic but
      //!       only inside of in-memory runtime structures (such as RuntimeModel or Core::Domain).
      //!       The destruction happens before the undeployment during the sopping process, when
      //!       the contribution is transfered from the RuntimeModel::Contribution::Running to
      //!       the RuntimeModel::Contribution::Deployed state (see ContributionLoading::Runner).
      //! \todo During undeployment \c \<wire\> elements that have beend deploy by deployWire()
      //!       must also be undeployed (see also deployComposite()).
      //*******************************************************************************************
      void undeploy(const Trentino::RuntimeModel::ContributionPtr& contribution);

      //management
   private:      
      //*******************************************************************************************
      //                                      deployComposite()
      //*******************************************************************************************
      //! \brief Performs actions necessary to deploy a single composite. 
      //!
      //! The following steps are performed by deployComposite()
      //! -# deployComponent() is called for each component contained in the given composite
      //! -# deployWire() is called for all the left \c \<wire\> elements that have not been 
      //!    processed in the first step (by calls to deployComponent()). Such left \c \<wire\> 
      //!    elements are either erroneous or they reference source components that are not 
      //!    contained in the deploying composite but somewhere in the domain. See documentation
      //!    for wireReference() for the reason for why such \c \<wire\> elements are not 
      //!    processed "automatically".
      //! -# If no error (exception) occurred, the composite is assigned the 
      //!    RuntimeModel::Composite::Deployed state.
      //!
      //! \param[in] composite Shared pointer to the composite to deploy.
      //! \return HasUnresolvedComponents if there is <em>at least</em> one component in the 
      //!         composite that was assigned the RuntimeModel::Component::Unresolved state, 
      //!         otherwise NoUnresolvedComponents. 
      //*******************************************************************************************
      DeployCompositeResult deployComposite(const Trentino::RuntimeModel::CompositePtr& composite);

      //*******************************************************************************************
      //                                      deployComponent()
      //*******************************************************************************************
      //! \brief Performs actions necessary to deploy a single component. 
      //!
      //! The following steps are performed by deployComponent()
      //! -# Core::ComponentPropertyManager::assignValuesFromSCAModel() is called for each
      //!    property contained in the given component.
      //! -# wireComponent() is called to further delegate the deployment process by performing
      //!    wiring and eventually deploying composites used as component implementations. All
      //!    the arguments of the method are further passed to wireComponent() without any change. 
      //!
      //! \param[in] component Shared pointer to the component to deploy.
      //! \param[in, out] leftComponentsToDeploy A collection of components that haven't been 
      //!                 deployed so far. When deployComponent() is called by deployComposite() 
      //!                 for the first time, the passed collection contains all the components  
      //!                 contained in the deploying composite except for the one component that is  
      //!                 passed to deployComposite() as the first argument. When deployComponent()
      //!                 returns \c leftComponentsToDeploy will contain the still undeployed
      //!                 components. Thus, it's possible that a single call to deployComponent()
      //!                 actually results in more than one component being deployed. In order to
      //!                 understand this behavior, see the following example
      //! \param[in, out] availableSCAWires A collection of SCA::Model::WirePtr instances, 
      //!                 representing all the \c \<wire\> elements in a composite that haven't
      //!                 been processed so far. When deployComponent() is called by 
      //!                 deployComposite() for the first time, the passed collection contains
      //!                 all the \c \<wire\> elements contained in the deploying composite. When
      //!                 deployComponent() returns \c availableSCAWires will contain all the still
      //!                 unprocessed <wire\> elements. 
      //!                 For more details on \c \<wire\> elements processing see the documentation 
      //!                 for wireReference(). 
      //! \par Example
      //! Given the following exemplary composite: \n
      //! \verbatim
      //! <composite>
      //!   <component name="C1"><reference name="R1" target="C2"/></component>
      //!   <component name="C2"/>
      //!   <component name="C3"/>
      //! </composite>
      //! \endverbatim \n
      //! The following pseudo code snippets illustrate the sequence of necessary 
      //! deployComponent() calls along with the passed arguments.  \n
      //! \code
      //! //initial call 
      //! leftComponentsToDeploy = {"C1", "C2", "C3"};
      //! leftComponentsToDeploy.erase("C1");
      //! deployComponent("C1", leftComponentsToDeploy, ...);  //first call (top level)
      //!
      //! //In the course of the execution of deployComponent() further sub routines will be called
      //! //the last of which (wireRefenceToTarget()) will determine that C1 needs C2 as the
      //! //target of one of its reference. Because  C2 is not deployed so far 
      //! //wireReferenceToTarget() will recursively call deployComponent() as follows:
      //! leftComponentsToDeploy.erase("C2");
      //! deployComponent("C2", leftComponentstoDeploy, ...); //second call (recursively)
      //!
      //! //since C2 has no further targets, deployComponent() won't be call recursively anymore
      //! //so that when the first call of deployComponent() returns, C1 and C2 will be deployed
      //! //and leftComponentsToDeploy will contain only C3. In order to finish the deployment
      //! //of the composite, only one last call to deployCoponent() is neccessary:
      //! leftComponentsToDeploy.erase("C3"); // now it's empty
      //! deployComponent("C3", leftComponentsToDeploy, ...); //third call (top level)
      //! \endcode    
      //*******************************************************************************************
      void deployComponent( const Trentino::RuntimeModel::ComponentPtr& component
                          , ComponentsSet& leftComponentsToDeploy
                          , SCAWiresSet& availableSCAWires);

      //*******************************************************************************************
      //                                      deployWire()
      //*******************************************************************************************
      //! \brief Processes a \c \<wire\> element that have not been processed "automatically"
      //!        by previous calls to wireReference().
      //!
      //! Such left \c \<wire\> elements are either erroneous or they reference source components 
      //! that are not contained in the deploying composite but somewhere in the domain. See 
      //! documentation for wireReference() for the reason for why such \c \<wire\> elements are 
      //! not processed "automatically".
      //!
      //! deployWire() evaluates the \c \@source and \c \@target attributes and calls 
      //! wireReferenceToTarget() in order to perfrom the wiring or issues an error in case the
      //! given \c \<wire\> element is erroneous. 
      //!
      //! \param[in] composite A shared pointer to the composite in which the \c \<wire\> element
      //!            is contained.
      //! \param[in] wire A shared pointer to the \c \<wire\> element to process. 
      //*******************************************************************************************
      void deployWire( const Trentino::RuntimeModel::ConstCompositePtr& composite
                     , const Trentino::SCA::Model::WirePtr& wire );

      //*******************************************************************************************
      //                                     wireComponent()
      //*******************************************************************************************
      //! \brief Tries to wire all of the component's unresolved references.
      //!
      //! The following steps are performed by wireComponent()
      //! -# The given component is assigned the (temporary) RuntimeModel::Component::Resolving 
      //!    state.
      //! -# wireReference() is called for all the component's references that are not already in
      //!    RuntimeModel::Reference::Resolved state. The \c leftComponentsToDeploy and 
      //!    \c availableSCAWires arguments are further passed to wireReference() without any 
      //!    change. 
      //! -# For components implemented by composites, the implementing composite is deployed 
      //!    by a call to deployComposite(). 
      //! -# Finally the component is assigned one of the following states: 
      //!    RuntimeModel::Component::Resolved, RuntimeModel::Component::Unresolved or 
      //!    RuntimeModel::Component::OptionalUnresolved
      //!
      //! In case the implementing composite (if any) of the given component contains at least one 
      //! component in the RuntimeModel::Component::Unresolved state after deployement, the 
      //! implementation is considered inconsistent with the consequence that the implementing 
      //! composite is undeployed, the references of the given component (wired in step 2) are 
      //! getting unwired and the component is assigned the RuntimeModel::Component::Unresolved 
      //! state. 
      //!      
      //! \param[in] component A shared pointer to the component to wire.
      //! \param[in, out] leftComponentsToDeploy see deployComponent()
      //! \param[in, out] availableSCAWires see deployComponent()
      //*******************************************************************************************
      void wireComponent( const Trentino::RuntimeModel::ComponentPtr& component
                        , ComponentsSet& leftComponentsToDeploy
                        , SCAWiresSet& availableSCAWires);

      //*******************************************************************************************
      //                                      wireReference()
      //*******************************************************************************************
      //! \brief Searches for all the targets specified for the given reference and tries to
      //!        wire the reference to those targets.
      //!
      //! The following steps are performed by wireReference()
      //! -# In case all of the following conditions are met:
      //!    -# the given reference belongs to a component that is contained in a composite which
      //!       is used as implementation
      //!    -# the reference is <em>already wired through promotion</em> (targets are specified by 
      //!       the parent component of the composite used as implementation)
      //!    -# \c \@nonOverridable="false" is specified for the reference
      //!    .
      //!    the reference is assigned the RuntimeModel::Reference::Resolved state and 
      //!    wireReference() returns wihtout considering possible further targets specified for
      //!    the reference in it's own composite. This behavior corresponds to what is specified
      //!    for the \c \@nonOverridable attribute (see Assembly Spec, line 886 ff.)
      //! -# The reference itself as well as all of the references the reference is promoted to
      //!    is assigned the temporary RuntimeModel::Reference::Resolving state. 
      //!    See RuntimeModel::Reference for more information on promotion.
      //! -# All the targets specified for the reference are collected. These can be either targets
      //!    specified via the reference's \c \@target attribute or those specified in \c \<wire\>
      //!    elements. 
      //! -# wireReferenceToTarget() is called for each found target in order to perform the actual
      //!    wiring.
      //! -# Finally the reference is assigned one of the following states: 
      //!    RuntimeModel::Reference::Resolved, RuntimeModel::Reference::Unresolved or 
      //!    RuntimeModel::Reference::OptionalUnresolved
      //!      
      //! \param[in] reference A shared pointer to the reference to wire.
      //! \param[in, out] leftComponentsToDeploy see deployComponent()
      //! \param[in, out] availableSCAWires A collection of SCA::Model::WirePtr instances, 
      //!                 representing all the \c \<wire\> elements in the composite that haven't
      //!                 been processed so far. When collecting the targets for the given 
      //!                 reference (see step 3), wireReference() pics the \c \<wire\> elements
      //!                 specifying the current reference in their \c \@source attributes and
      //!                 erases those elements from the collection. See the bottom example
      //!                 for more details.
      //! \par Example
      //! Given the following exemplary composite: \n
      //! \verbatim 
      //! <composite>
      //!   <component name="C1"><reference name="R1"/></component>
      //!
      //!   <wire source="C1/R1" target="Something"/> <!--1-->
      //!   <wire source="C1/R2" target="Something"/> <!--2-->
      //!   <wire source="C2/SomeRef" target="Something/> <!--3-->
      //! </composite>
      //! \endverbatim \n
      //! At some point wireReference() would be called with all the three \c \<wire\> elements
      //! contained in the \c availableSCAWires parameter. In would only pick the first 
      //! \c \<wire\> element and erase if from the collection. The second \c \<wire\> element
      //! would not be touched because \c C1 doesn't have a reference named \c R2 (hence it's not
      //! possible that wireReference() is ever called for this reference). The last 
      //! \c \<wire\> element would also not be touched because the composite doesn't even contain
      //! a component named \c C2 (hence it's not possible that wireComponent() is called for that
      //! component and consequently no wireReference() call will ever take place that could pick
      //! the \c \<wire\> element). \n
      //! Consequently, at some point, when the last call to deployComponent() returns and all the
      //! components in a composite have been processed, the both last \c \<wire\> elements will be
      //! still left untouched. They must therefore be explicitly processed by deployWire().
      //*******************************************************************************************
      void wireReference( const Trentino::RuntimeModel::ReferenceBasePtr& reference
                        , ComponentsSet& leftComponentsToDeploy
                        , SCAWiresSet& availableSCAWires);

      //*******************************************************************************************
      //                                     wireReferenceToTarget()
      //*******************************************************************************************
      //! \brief Wires the given reference to the specified target by creating a corresponding
      //!        RuntimeModel::Wire object. 
      //!
      //! If the \c target references a component that is in RuntimeModel::Component::Initial 
      //! state, the component is deployed via deployComponent().
      //!
      //! \param[in] reference A shared pointer to the reference to wire.
      //! \param[in] target A \b wire-target-URI as specified in Assembly Spec, line 1847 ff. with
      //!            the exception that the \c \<binding-name\> part is currently not supported. 
      //!            Consequently, the expected URI format is as follows: 
      //!            <tt>\<comonent-name\>[/\<service-name\>]?</tt>.
      //! \param[in, out] leftComponentsToDeploy see deployComponent()
      //! \throw ConributionLoading::WiringException with \c data() set to
      //!        ContributionLoading::ComponentNotFoundError in case the specified target component
      //!        could not be found (see also Assembly Spec, [ASM60047]).
      //! \throw ConributionLoading::WiringException with \c data() set to
      //!        ContributionLoading::ServiceNotFoundError in case the specified target service
      //!        could not be found (see also Assembly Spec, [ASM60047]).
      //! \throw ConributionLoading::WiringException with \c data() set to
      //!        ContributionLoading::ServiceIncombatibleError in case the interface of the 
      //!        specified target service is not compatible with the reference's interface.
      //! \throw ConributionLoading::WiringException with \c data() set to
      //!        ContributionLoading::AmbigousServicesError in case the given \c target doesn't
      //!        specify a service name but the target component has more that one compatible
      //!        service (see also Assembly Spec, [ASM60048]). 
      //! \throw ConributionLoading::WiringException with \c data() set to
      //!        ContributionLoading::NoCompatibleServicesError in case the given \c target doesn't
      //!        specify a service name but the target component has not compatible services at all
      //!        (see also Assembly Spec, [ASM60048]). 
      //! \throw ConributionLoading::WiringException with \c data() set to
      //!        ContributionLoading::ComponentUnresolvedError in case the target component is in
      //!        RuntimeModel::Component::Unresolved state. 
      //! \throw ConributionLoading::WiringException with \c data() set to
      //!        ContributionLoading::CyclicDependencyError in case a cyclic dependency between
      //!        components occurred. See RuntimeModel::Component::Resolving for more information.
      //! \throw ConributionLoading::ErrorException with \c data() set to
      //!        ContributionLoading::ProxyInstanceNotCreatedError in case a proxy object needed
      //!        to establish a wire could not be created for some reasons.
      //! 
      //! \remark Cyclic dependencies are \b not disallowed by the spec and should be supported in
      //!         future. 
      //*******************************************************************************************
      void wireReferenceToTarget( const Trentino::RuntimeModel::ReferenceBasePtr& reference
                                , const Trentino::XML::Schema::AnyURI& target
                                , ComponentsSet& leftComponentsToDeploy
                                , SCAWiresSet& availableSCAWires);

      //*******************************************************************************************
      //                                 processWiringException()
      //*******************************************************************************************
      //! \brief Creates an appropriate error message for the given exception and reports it over
      //!        the associated error handler. 
      //!
      //! \param[in] e %Exception to be processed.
      //! \param[in] referencedIn A string containing a description about the source that caused
      //!            the exception to occur. For example the \c \@target attribute of a 
      //!            \c \<reference\> or a \c \<wire\> element.
      //! \sa ErrorReporter::errorHandler(), ErrorReporter::setErrorHandler()
      //*******************************************************************************************
      void processWiringException( const WiringException& e
                                 , const std::string& referencedIn);

   }; //class Deployer

} //namespace ContributionLoading
} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreContributionLoadingDeployerH