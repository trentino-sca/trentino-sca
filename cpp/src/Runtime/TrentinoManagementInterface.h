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

#ifndef ManagementInterfaceH
#define ManagementInterfaceH

//standard
#include <map>
#include <string>
#include <vector>

//specific
#include "../Utils/TrentinoUtilsDataObject.h"

namespace Trentino
{
   //**********************************************************************************************
   //                            ManagementInterface
   //**********************************************************************************************
   //! \class ManagementInterface
   //! \brief A class representing the interface to communicate with the runtime
   //!
   //! Trentino runtime is controlled by a set of commands executed by a user. The implementation
   //! of these commands should perform requests to the main runtime part to communicate the
   //! information gathered from the user. The following class represents an
   //! abstract interface which defines a list of methods to be used for data exchanging
   //! between user and runtime parts.
   //!
   //! As an example of possible application, this interface should be used by Trentino console.
   //!
   //! This interface was designed to be as simple as possible. No processing of the return
   //! values should be performed. Instead, if return value contains some text, it should
   //! printed as it is.
   //!
   //! The following methods can be classified in two groups
   //!  - informationRetrieval: contains commands intended to retrieve information from the runtime 
   //!  - runtimeManagement: contains commands to perform operations on the runtime 
   //**********************************************************************************************
   class ManagementInterface
   {
       // additional
   public:
      //! \brief This type represents identifier for the installed contribution
      typedef Trentino::Utils::DataObject ContributionData;
      //! \brief Collection of contribution base URIs
      typedef std::vector<ContributionData> ContributionDatas;                 
      //! \brief Error message returned from runtime (empty string if no errors occured)
      typedef std::string ErrorMessage;
      //! \brief SCDL Attributes represented in a map format: name -> value
      typedef std::map< std::string, std::string > Attributes;
      //! \brief A collection of the service names
      typedef std::vector<std::string> Services;
      //! \brief A collection of the component structural URIs
      typedef std::vector<std::string> Components;
      //! \brief A collection of the reference names
      typedef std::vector<std::string> References;
      //! \brief A collection  of property names, it's assumed that each property could be 
      //! definitely identified by its name in component context
      typedef std::vector<std::string> PropertiesNames;
      //! \brief A type of implementation (such as composite, java, cpp...)
      typedef std::string ImplementationType;
      //! \brief Values for a property, simple types are currently supported only
      //! \todo Add support for a complex XML types
      typedef std::vector<std::string> PropertyValues;

      //! \todo Maybe merge references and services to decrease amount of data types?

  
      //! \brief Represents a component state
      typedef std::string ComponentState;      
      //! \brief A service state type
      typedef std::string ServiceState;
      //! \brief A collection of states for several services in a map format: service name -> 
      //!        state
      typedef std::map< std::string, ServiceState > ServicesStates;
      //! \brief A reference state
      typedef std::string ReferenceState;
      //! \brief A collection of states for several references in a map format: 
      //! /biref reference name -> state
      typedef std::map< std::string, ReferenceState > ReferencesStates;
      //! \brief A collection of a target service to which specified reference is wired
      typedef std::vector<std::string> ReferenceTargets;
      
      typedef void (*ownerProcessExceptionHandlerPtr)();

      //construction
   public:
      virtual ~ManagementInterface() {};

       //services
   public:
      //! \name Operations on the runtime
      //! @{

      //*******************************************************************************************
      //                                  install()
      //*******************************************************************************************
      //! \brief An install command interface
      //! \param[in] contrinutionDirectoryPath physical path to contribution to be installed
      //! \param[in] contributionBaseURI Base URI to be assigned to the contribution.
      //! \return unique identifier or empty string is case of error
      //*******************************************************************************************
      virtual ErrorMessage install(const std::string& contributionDirectoryPath,
                                   const std::string& contributionBaseURI) = 0;

      //*******************************************************************************************
      //                                  update()
      //*******************************************************************************************
      //! \brief An update command interface
      //! \param[in] contrinutionDirectoryPath physical path to new contribution
      //! \param[in] contributionBaseURI Base URI of the contribution to be updated.
      //! \return update message
      //*******************************************************************************************
      virtual void update(const std::string& contributionDirectoryPath,
                           const std::string& contributionBaseURI,
                           Trentino::Utils::DataObject& res) = 0;

      //*******************************************************************************************
      //                                  deploy()
      //*******************************************************************************************
      //! \brief A deploy command interface
      //! \param contrinutionIdentifier unique identifier for the installed contribution
      //! \return empty string if command completed successfully or an error message
      //*******************************************************************************************
      virtual ErrorMessage deploy(const std::string& contributionBaseURI) = 0;

      //*******************************************************************************************
      //                                  remove()
      //*******************************************************************************************
      //! \brief A remove command interface
      //! \param contributionIdentifier a value to definitely identify contribution
      //! \return empty string or an error message if command failed
      //*******************************************************************************************
      virtual ErrorMessage remove(const std::string& contributionBaseURI) = 0;

      //*******************************************************************************************
      //                               removeComponent()
      //*******************************************************************************************
      //! \brief A remove component command interface
      //! \param componentURI URI-style link to component to be removed
      //! \return empty string or an error message if command failed
      //*******************************************************************************************
      virtual ErrorMessage removeComponent(const std::string& componentURI) = 0;

      //*******************************************************************************************
      //                                         rewire()
      //*******************************************************************************************
      //! \brief A wire command interface
      //! \param referenceURI URI-style link to a local reference
      //! \param target full target link (including target IP address if service is remote)
      //! \param bindingType name - if binding should be used, empty string - if shouldn't
      //! \return empty string if command completed successfully or an error message
      //*******************************************************************************************
      virtual ErrorMessage rewire(const std::string& referenceURI,
                                  const std::string& target,
                                  const std::string& bindingType) = 0;

      //*******************************************************************************************
      //                                   rewireByDiscovery()
      //*******************************************************************************************
      //! \brief Rewire a reference by using discovery protocol
      //! \ingroup runtimeManagement
      //! \todo std::string rewireByDiscovery(const std::string& referenceURI, 
      //!                                     const std::string& targetService);
      //*******************************************************************************************

      //*******************************************************************************************
      //                                     setProperty()
      //*******************************************************************************************
      //! \brief A set command interface
      //! \param propertyURI URI path to a property to be changed
      //! \param newValues new values for the property
      //! \return empty string if command completed successfully or an error message
      //*******************************************************************************************
      virtual ErrorMessage setProperty(const std::string& propertyURI, 
                                       const PropertyValues& newValues) = 0;

      //! @}
      // end of runtimeManagement group                                 

      //! \name Retrieve information from the runtime
      //!
      //! NOTE:
      //!   The section 5.8 from the Assembly Specification v1.1 is extended by the following
      //! definitions:
      //!   #parameter(NAME) - to specify a parameter artifact
      //!   #implementation() - to specify a component implementation
      //!
      //! @{


      //*******************************************************************************************
      //                                  getContributions()
      //*******************************************************************************************
      //! \brief Retrieve the base URIs of all the available contributions.      
      //! \return A collection of base URIs.
      //*******************************************************************************************
      virtual ContributionDatas getContributions() const = 0;

      virtual ContributionData getContribution(const std::string& contributionBaseUri) const =0;

      
      //*******************************************************************************************
      //                                  getComponents()
      //*******************************************************************************************
      //! \brief Retrieve the URIs of all the components contained in the contribution with the
      //!        given base URI.
      //! \param[in] contributionBaseURI The base URI of the contribution to retrieve the 
      //!            components for.
      //! \return A collection containing the URIs of all the components from the given
      //!         contribution.
      //*******************************************************************************************
      virtual Components getComponents(const std::string& contributionBaseURI) const = 0;

      //*******************************************************************************************
      //                                  getDomainLevelComponents()
      //*******************************************************************************************
      //! \brief Retrieve the URIs of all the domain-level components.      
      //! \return A collection containing the URIs of all the domain-level components.
      //*******************************************************************************************
      virtual Components getDomainLevelComponents() const = 0;

      //*******************************************************************************************
      //                               getAttributes()
      //*******************************************************************************************
      //! \brief Retrieve all the SCDL attributes for the specified artifact
      //! \param artifactURI A URI-style link for the artifact being requested
      //! \return A collection of attributes
      //*******************************************************************************************
      virtual Attributes getAttributes(const std::string& artifactURI) const = 0;

      //*******************************************************************************************
      //                               getServices()
      //*******************************************************************************************
      //! \brief Retrieve all the services for the scpecified componet
      //! \param componentURI A URI-style link for the service being requested.
      //! The component is relativ to the domain.
      //! \return A collection of services names, relative to the component URI
      //*******************************************************************************************
      virtual Services getServices(const std::string& componentURI) const = 0;

      //*******************************************************************************************
      //                               getReferences()
      //*******************************************************************************************
      //! \brief Retrieve all the references for the scpecified component.
      //! \param componentURI A URI-style link for the component being requested
      //! \return A collection of references names, relative to the component URI
      //*******************************************************************************************
      virtual References getReferences(const std::string& componentURI) const = 0;

      //*******************************************************************************************
      //                               getPropertiesNames()
      //*******************************************************************************************
      //! \brief Retrieve all the properties names for the scpecified componet
      //! \param componentURI A URI-style link for the component being requested
      //! \return A collection of properties names, relative to the component URI
      //*******************************************************************************************
      virtual PropertiesNames getPropertiesNames(const std::string& componentURI) const = 0;

      //*******************************************************************************************
      //                               getImplementationType()
      //*******************************************************************************************
      //! \brief Retrieve an implementation type for the specified component
      //! \param componentURI A URI-style link for the component being requested
      //! \return An implementation type
      //*******************************************************************************************
      virtual ImplementationType getImplementationType(const std::string& componentURI) const = 0;

      //*******************************************************************************************
      //                               getPropertyValues()
      //*******************************************************************************************
      //! \brief Retrieve all the values for the property specified.
      //! The values are actually retrieved from the internal SCA Model, from a SCAPropertyBase
      //! They are built from either SCAPropertyBase::content or SCAPropertyBase::value
      //! \param propertyURI A URI-style link for the property being requested
      //! \return A collection of property values
      //*******************************************************************************************
      virtual PropertyValues getPropertyValues(const std::string& propertyURI) const = 0;

      //*******************************************************************************************
      //                               getServiceState()
      //*******************************************************************************************
      //! \brief Retreive a state of the specified service
      //! \param serviceURI A URI-style link for the service being requested
      //! \return A service state value
      //*******************************************************************************************
      virtual ServiceState getServiceState(const std::string& serviceURI) const = 0;

      //*******************************************************************************************
      //                               getServicesStates()
      //*******************************************************************************************
      //! \brief Request for a states for all the child services
      //! \param componentURI component which contains services
      //! \return a map, each key of which represents a service name and value is a state
      //*******************************************************************************************
      virtual ServicesStates getServicesStates(const std::string& componentURI) const = 0;

      //*******************************************************************************************
      //                               getReferenceState()
      //*******************************************************************************************
      //! \brief Request for a state for the specified reference
      //! \param refernceURI A URI-style link for the reference being requested
      //! \return A reference state value
      //*******************************************************************************************
      virtual ReferenceState getReferenceState(const std::string& referenceURI) const = 0;

      //*******************************************************************************************
      //                               getReferencesStates()
      //*******************************************************************************************
      //! \brief Request for a states for all the child references
      //! \param componentURI component which contains references
      //! \return a map, each key of which represents a reference name and value is a state
      //*******************************************************************************************
      virtual ReferencesStates getReferencesStates(const std::string& componentURI) const = 0;

      //*******************************************************************************************
      //                               getReferenceTargets()
      //*******************************************************************************************
      //! \brief Get a list of the target service to which scpecified reference is wired
      //! \param refernceURI A URI-style link for the reference being requested
      //! \return A list of targets
      //*******************************************************************************************
      virtual ReferenceTargets getReferenceTargets(const std::string& referenceURI) const = 0;

      //*******************************************************************************************
      //                               getComponentState()
      //*******************************************************************************************
      //! \brief Get the component state
      //! \param componentURI component which contains references
      //! \return A component state
      //*******************************************************************************************
      virtual ComponentState getComponentState(const std::string& componentURI) const = 0;

      //*******************************************************************************************
      //                               setOwnerProcessExceptionHandler()
      //*******************************************************************************************
      //! \brief Owner process(i.e. Trentino Console) injects a callback to be used by the runtime
      //! to be called in case of hardware exception. Owner process decides how to react to the 
      //! exceptional situation.
      //! \param ownerProcessExceptionHandlerPtr : funtion pointer to be triggered
      //*******************************************************************************************
      virtual void setOwnerProcessExceptionHandler(ownerProcessExceptionHandlerPtr) = 0;
                               

  }; //class ManagementInterface

} //namespace Trentino

#endif //ManagementInterfaceH