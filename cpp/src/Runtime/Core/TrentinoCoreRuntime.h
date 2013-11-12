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

#ifndef TrentinoCoreRuntimeH
#define TrentinoCoreRuntimeH

//standard
#include <string>
#include <set>

//specific
#include "./../../Global/TrentinoGlobal.h"
#include "./../TrentinoManagementInterface.h"
#include "./../RuntimeModel/TrentinoRuntimeModel.h"
#include "./../../Utils/TrentinoUtilsURI.h"

#ifdef WIN32
   #ifdef CORE_EXPORTS
      #define RUNTIME_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define RUNTIME_IMPORT_EXPORT __declspec(dllimport)       
   #endif //CORE_EXPORTS
#else
   #define RUNTIME_IMPORT_EXPORT
#endif //WIN32

namespace Trentino{
namespace Core
{
   //class declaration
   //**********************************************************************************************
   //                                   Runtime
   //**********************************************************************************************
   //! \ingroup Core
   //! \brief Represents a single Trentino Runtime and offers functionality for querying 
   //!        information about the available SCA entities.
   //!
   //! Provides and Implementation of the ManagementInterface.
   //**********************************************************************************************
   class Runtime
   {
      //additional
   public:
      typedef std::set<Trentino::RuntimeModel::ContributionPtr> Contributions;
      //services
   public:
      static void  onException()
      {
         mOwnerProcessExcepionHandlerFunc();
      }
   private:
      //*******************************************************************************************
      //                                  ManagementInterfaceImpl
      //*******************************************************************************************      
      //! \brief Nested class implementation of the ManagementInterface.    
      //*******************************************************************************************
      class ManagementInterfaceImpl : public Trentino::ManagementInterface
      {
         //construction
      public:
         //****************************************************************************************
         //                                ManagementInterfaceImpl()
         //****************************************************************************************
         //! \param[in] runtime Reference to the Runtime instance that called this constructor.
         //****************************************************************************************
         explicit ManagementInterfaceImpl(Runtime& runtime);
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
         

         //management
      private:
         //****************************************************************************************
         //                               findServiceByServiceURI()
         //****************************************************************************************
         //! \brief Finds a service with the given structural URI.
         //! \param[in] Structural URI of the service to search for.
         //! \return A shared pointer to the found service or an empty shared pointer if a service
         //!         with the given URI could not be found.
         //****************************************************************************************
         Trentino::RuntimeModel::ConstServiceBasePtr findServiceByServiceURI(
            const std::string& serviceURI) const;

         //****************************************************************************************
         //                                findComponentByURI()
         //****************************************************************************************
         //! \brief finds the component with the given componentURI
         //! \param componentURI Component URI to search for
         //! \return Shared pointer to the found component or an empty shared pointer if a 
         //!         component with the given URI could not be found.
         //****************************************************************************************
         Trentino::RuntimeModel::ConstComponentPtr findComponentByURI(
            const std::string& componentURI) const;         

         //****************************************************************************************
         //                               findReferenceByReferenceURI()
         //****************************************************************************************
         //! \brief Finds a service with the given structural URI.
         //! \param Structural URI of the reference to search for.
         //! \return A shared pointer to the found reference or an empty shared pointer if a 
         //!         reference with the given URI could not be found.
         //****************************************************************************************
         Trentino::RuntimeModel::ConstReferenceBasePtr findReferenceByReferenceURI(
            const std::string& referenceURI) const;

         //****************************************************************************************
         //                                 findPropertyByPropertyURI()
         //****************************************************************************************
         //! \brief Finds a property with the given structural URI.         
         //! \param Structural URI of the property to search for.
         //! \return A shared pointer to the found property or an empty shared pointer if a 
         //!         property with the given URI could not be found.
         //****************************************************************************************
         Trentino::RuntimeModel::ConstPropertyPtr findPropertyByPropertyURI(
            const std::string& propertyURI) const;


         //data
      private:
         //! Reference to the Runtime instance that has created this object
         Runtime& mRuntime;

         
      };

      friend class ManagementInterfaceImpl;

      //construction
   public:
      //*******************************************************************************************
      //                                       Runtime()
      //*******************************************************************************************         
      //! \brief Initializes all the members with default values.
      //*******************************************************************************************
      Runtime();

      //*******************************************************************************************
      //                                       ~Runtime()
      //*******************************************************************************************         
      //! \brief Empty destructor.
      //*******************************************************************************************
      RUNTIME_IMPORT_EXPORT ~Runtime();
   private:
      //*******************************************************************************************
      //                                 Runtime(const Runtime&);
      //*******************************************************************************************
      //! \brief Disallow inadvertent copy construction.      
      //*******************************************************************************************
      Runtime(const Runtime&);

      //operators
   private:
      //*******************************************************************************************
      //                                      operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.      
      //*******************************************************************************************
      void operator=(const Runtime&);

      //services
   public:
      //*******************************************************************************************
      //                                 managementInterface()
      //*******************************************************************************************
      //! \brief Returns the runtime's ManagementInterface implementation.
      //! \return Reference to a ManagementInterface implementation.      
      //*******************************************************************************************
      Trentino::ManagementInterface& managementInterface();

      //*******************************************************************************************
      //                                 contribution()
      //*******************************************************************************************
      //! \brief Returns a collection of contributions installed in the runtime.
      //! \return Const reference the the collection of contributions installed in the runtime.
      //*******************************************************************************************
      const Contributions& contributions() const;
      
      //*******************************************************************************************
      //                                 findContribution()
      //*******************************************************************************************
      //! \brief Finds a contribution by its base URI. 
      //! \param[in] Base URI to search for.
      //! \return A shared pointer to the found contribution or an empty shared pointer if a 
      //!         contribution with the given base URI could not be found.
      //******************************************************************************************* 
      RUNTIME_IMPORT_EXPORT Trentino::RuntimeModel::ContributionPtr findContribution(
          const Trentino::Utils::URI& baseURI) const;

      //data
   private:
      //! Implementation of ManagementInterface
      ManagementInterfaceImpl mManagementInterface; 
      //! Collection of cotributions installed in the runtime.
      Contributions mContributions;

      static ManagementInterface::ownerProcessExceptionHandlerPtr mOwnerProcessExcepionHandlerFunc;
   };

      //services
   inline Trentino::ManagementInterface& Runtime::managementInterface()                                           
   {
      return mManagementInterface;             
   }
      
   inline const Runtime::Contributions& Runtime::contributions() const
   {
      return mContributions;
   }

}//namespace Core
}//namespace Trentino


#endif//TrentinoCoreRuntimeH
