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

#ifndef TrentinoCoreDomainH
#define TrentinoCoreDomainH

//standard
#include <map>

//specific
#include "TrentinoCore.h"
#include "../../Utils/TrentinoUtilsURI.h"
#include "../TrentinoManagementInterface.h"
#include "../RuntimeModel/TrentinoRuntimeModel.h"

namespace Trentino{
namespace Core
{
   class Runtime;

   //**********************************************************************************************
   //                                      Domain
   //**********************************************************************************************
   //! \ingroup Core
   //! \brief Represents an SCA Domain (see Assembly Spec Version 1.1, chapter 10.1)
   //!   
   //! - In future, the Domain class should serve as a manager of the local (in-process) and all 
   //!   the remotely available runtimes. Currently the Domain manages only one local runtime. 
   //! - The Domain class provides an implementation of the ManagementInterface. The greatest part
   //!   of the methods is just forwarded to the ManagementInterface implementation provided by
   //!   Core::Runtime.   
   //**********************************************************************************************
   class Domain
   {
      //services
   public:
      static void  onException()
      {
         mOwnerProcessExcepionHandlerFunc();
      }
      //additional
   private:
      //*******************************************************************************************
      //                                  ManagementInterfaceImpl
      //*******************************************************************************************      
      //! \brief Nested class implementing the ManagementInterface.
      //!
      //! Currently, the greatest part of the methods is just forwarded to the ManagementInterface
      //! implementation provided by Core::Runtime.
      //*******************************************************************************************
      class ManagementInterfaceImpl : public Trentino::ManagementInterface
      {
         //construction
      public:
         //****************************************************************************************
         //                                ManagementInterfaceImpl()
         //****************************************************************************************
         //! \param[in] domain Reference to the Domain instance that called this constructor.
         //****************************************************************************************
         explicit ManagementInterfaceImpl(Domain& domain);
      private:
         //****************************************************************************************
         //                ManagementInterfaceImpl(const ManagementInterfaceImpl&);
         //****************************************************************************************
         //! \brief Disallow inadvertent copy construction.      
         //****************************************************************************************
         ManagementInterfaceImpl(const ManagementInterfaceImpl&);

         //operators
      private:
         //****************************************************************************************
         //                                     operator=()
         //****************************************************************************************
         //! \brief Disallow assignment.      
         //****************************************************************************************
         const ManagementInterfaceImpl& operator=(const ManagementInterfaceImpl&);

         //services
      public:      
         // all the following methods are overrides from ManagementInterface
         //(see documentation in ManagementInterface)

         ErrorMessage install( const std::string& contributionDirectoryPath 
                             , const std::string& contributionBaseURI);
         void update(const std::string& contributionDirectoryPath,
                           const std::string& contributionBaseURI,
                           Trentino::Utils::DataObject& res);
         ErrorMessage deploy(const std::string& contributionBaseURI);
         ErrorMessage remove(const std::string& contributionIdentifier);
         ErrorMessage removeComponent(const std::string& componentURI);
         ErrorMessage rewire( const std::string& referenceURI
                            , const std::string& target
                            , const std::string& bindingType);         
         ErrorMessage setProperty( const std::string& propertyURI
                                 , const PropertyValues& newValues);
         Trentino::ManagementInterface::ContributionDatas getContributions() const;
         Trentino::ManagementInterface::ContributionData getContribution(const std::string& contributionBaseURI) const;
         Components getComponents(const std::string& contributionBaseURI) const;
         Components getDomainLevelComponents() const;         
         Attributes getAttributes(const std::string& artifactURI) const;
         Services getServices(const std::string& componentURI) const;
         References getReferences(const std::string& componentURI) const;
         PropertiesNames getPropertiesNames(const std::string& componentURI) const;
         ImplementationType getImplementationType(const std::string& componentURI) const;
         PropertyValues getPropertyValues(const std::string& propertyURI) const;
         ServiceState getServiceState(const std::string& serviceURI) const;
         ServicesStates getServicesStates(const std::string& componentURI) const;
         ReferenceState getReferenceState(const std::string& referenceURI) const;
         ReferencesStates getReferencesStates(const std::string& componentURI) const;
         ReferenceTargets getReferenceTargets(const std::string& referenceURI) const;
         ComponentState getComponentState(const std::string& componentURI) const;     
         void setOwnerProcessExceptionHandler(ManagementInterface::ownerProcessExceptionHandlerPtr);

         //data
      private:
         //! Reference to the Domain instance that has created this object
         Domain& mDomain;
      };

      friend class ManagementInterfaceImpl;

      //construction
   public:
      //*******************************************************************************************
      //                                       Domain()
      //*******************************************************************************************         
      //! \brief Initializes all the members with default values.
      //*******************************************************************************************
      Domain();
   private:
      //*******************************************************************************************
      //                                 Domain(const Domain&);
      //*******************************************************************************************
      //! \brief Disallow inadvertent copy construction.      
      //*******************************************************************************************
      Domain(const Domain&);

      //operators
   private:
      //*******************************************************************************************
      //                                      operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.      
      //*******************************************************************************************
      void operator=(const Domain&);
      
      //services
   public:
      //*******************************************************************************************
      //                                        setup()
      //*******************************************************************************************
      //! \brief Assigns the Domain an URI.
      //!
      //! Currently the methods does nothing except for assigning the the Domain an URI that is 
      //! stored as a member. The URI itself isn't further used except for showing it in output
      //! messages etc. \n
      //! Actually, the setup() function is reserved for future use and shoud peform task such as
      //! announcing its availability in the network and discovering all the available remote 
      //! runtimes etc.
      //!
      //! \param[in] uri The domain's URI.
      //*******************************************************************************************
      void setup(const Trentino::Utils::URI& uri);

      //*******************************************************************************************
      //                                registerLocalRuntime()
      //*******************************************************************************************
      //! \brief Registers the local runtime with the Domain.
      //!      
      //! The registered runtime is used to forward the ManagementInterface requests to it. 
      //! \attention Before calling managementInterface(), it's requried to register a runtime.
      //! param[in] runtime Reference to a Core::Runtime object.
      //! \sa unregisterLocalRuntime(), Domain(), Domain::ManagementInterfaceImpl()
      //*******************************************************************************************
      void registerLocalRuntime(Runtime& runtime);

      //*******************************************************************************************
      //                                unregisterLocalRuntime()
      //*******************************************************************************************
      //! \brief Unregisters the local runtime from the Domain.
      //!
      //! \attention After the runtime has been unregistered managementInterface() should not be 
      //!            called.
      //! \attention Using a previously saved return value of managementInterface() after the  
      //!            runtime has been unregistered leads to undefined behavior.        
      //! \sa registerLocalRuntime()
      //*******************************************************************************************
      void unregisterLocalRuntime();

      //*******************************************************************************************
      //                                 managementInterface()
      //*******************************************************************************************
      //! \brief Returns the domain's ManagementInterface implementation.
      //! \return Reference to a ManagementInterface implementation.
      //! \throw std::runtime_error If no runtime is currently registered.      
      //! \attention Using a previously saved return value of managementInterface() after the  
      //!            runtime has been unregistered leads to undefined behavior.       
      //! \sa registerLocalRuntime(), unregisterLocalRuntime()
      //*******************************************************************************************
      Trentino::ManagementInterface& managementInterface();      

      //*******************************************************************************************
      //                                addToDomainLevelComposite()
      //*******************************************************************************************
      //! \brief Adds a composites to the virtual domain level composite and thus makes the
      //!        contained components globally visible.
      //!      
      //! \param[in] Shared pointer to the composite to add.
      //! \throw std::runtime_error If the name one of one of the components within the given 
      //!        composite already exists in the domain.
      //*******************************************************************************************
      void addToDomainLevelComposite(const Trentino::RuntimeModel::CompositePtr& composite);

      //*******************************************************************************************
      //                              removeFromDomainLevelComposite()
      //*******************************************************************************************
      //! \brief Removes a composite from the virtual domain level composite and thus makes the 
      //!        contained components globally invisible.
      //!        
      //! If the given composite isn't part of the virtual domain level composite , the method 
      //! has no effect.
      //! \param[in] Shared pointer to the composite to remove.
      //! \sa addDoDomainLevelComposite()
      //*******************************************************************************************
      void removeFromDomainLevelComposite(
         const Trentino::RuntimeModel::ConstCompositePtr& composite);
      
      //*******************************************************************************************
      //                             findDomainLevelComponentByName()
      //*******************************************************************************************
      //! \brief Searches for a component on the domain level.
      //!
      //! \param[in] name Name of the component to find.
      //! \return A shared pointer to the found component or an empty shared pointer if a component
      //!         with the given name could not be found.
      //*******************************************************************************************
      CORE_IMPORT_EXPORT Trentino::RuntimeModel::ComponentPtr findDomainLevelComponentByName(
         const std::string& name) const;

      //*******************************************************************************************
      //                             findDomandLevelServicesByName()
      //*******************************************************************************************
      //! \brief Searches for services on the domain level.
      //!
      //! \param[in] name Name of the service to find.
      //! \return A collection of  to the found service or an empty collection if no service with
      //!         the given name could not be found.
      //*******************************************************************************************
      Trentino::RuntimeModel::ServiceBases findDomandLevelServicesByName(
         const std::string& name) const;

      //*******************************************************************************************
      //                             findRemotableServices()
      //*******************************************************************************************
      //! \brief Searches for remotable services on the domain level.
      //!
      //! \return A collection of remotable services + services with bindings.
      //*******************************************************************************************
      Trentino::RuntimeModel::ServiceBases findRemotableServices() const;

      //*******************************************************************************************
      //                             findRemotableServices()
      //*******************************************************************************************
      //! \brief Searches for remotable services of a given contribution on the domain level.
      //! \param contribution_uri - contribution URI
      //! \return A collection of remotable services + services with bindings.
      //*******************************************************************************************
      Trentino::RuntimeModel::ServiceBases findRemotableServices(Trentino::Utils::URI contribution_uri) const;

      //*******************************************************************************************
      //                             findRemoteReferences()
      //*******************************************************************************************
      //! \brief Searches for remote references of a given contribution on the domain level. Remote
      //! references are those with bindings wired to fake service delegates.
      //! \param contribution_uri - contribution URI
      //! \return A collection of remote references
      //*******************************************************************************************
      Trentino::RuntimeModel::ReferenceBases findRemoteReferences(Trentino::Utils::URI contribution_uri) const;

      //data
   private:
      //! The domain's URI
      Trentino::Utils::URI mURI;
      //! Pointer to the local 
      Runtime* mLocalRuntime;
      //! Implementation of ManagementInterface
      ManagementInterfaceImpl mManagementInterface; 
      //! Used to store composites included into the virtual domain level composites. 
      //! It's a temporary solution to imitate a virtual domain level composite as described by 
      //! the spec (chapter 10.7). 
      //! \sa addToDomainLevelComposite(), findDomainLevelComponentByName()
      Trentino::RuntimeModel::Composites mDomainLevelComposites;


      static ManagementInterface::ownerProcessExceptionHandlerPtr mOwnerProcessExcepionHandlerFunc;

   }; //class Domain  

} //namespace Core
} //namespace Trentino

#endif //TrentinoCoreDomainH
