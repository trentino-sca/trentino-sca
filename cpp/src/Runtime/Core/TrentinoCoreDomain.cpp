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
#include "TrentinoCoreDomain.h"

//standard
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>

//specific
#include "../../Global/TrentinoGlobal.h"
#include "./../../Utils/TrentinoUtilsLogging.h"
#include "TrentinoCoreRuntime.h"
#include "../SCAModel/TrentinoSCAModelComponent.h"
#include "../SCAModel/TrentinoSCAModelComponentService.h"
#include "../RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "../RuntimeModel/TrentinoRuntimeModelComponent.h" 
#include "../RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "../RuntimeModel/TrentinoRuntimeModelServiceBase.h"
#include "../RuntimeModel/TrentinoRuntimeModelReferenceBase.h"



using namespace std;
using Trentino::Core::Domain;
using Trentino::Core::Runtime;
using Trentino::ManagementInterface;
using Trentino::Utils::URI;
namespace RuntimeModel = Trentino::RuntimeModel;

ManagementInterface::ownerProcessExceptionHandlerPtr Domain::mOwnerProcessExcepionHandlerFunc;

//class Domain
//additional
//class ManagementInterfaceImpl
//construction
Domain::ManagementInterfaceImpl::ManagementInterfaceImpl(Domain& domain)
: mDomain(domain) //don't ever call any methods on the passed Domain instance here!!!
{}

//services
ManagementInterface::ErrorMessage Domain::ManagementInterfaceImpl::install(
   const string& contributionDirectoryPath, 
   const std::string& contributionBaseURI)
{  
   assert(mDomain.mLocalRuntime);

   //Before assigning the give base uri to a contribution, we must ensure
   //that the uri is unique _across the domain_.
   //Since the domain currently consists of only the local runtime, it's
   //sufficient to check only the local runtime.
   if(mDomain.mLocalRuntime->findContribution(contributionBaseURI))
   {
      return "Base URI '" + contributionBaseURI + "' already in use";
   }

   return mDomain.mLocalRuntime->managementInterface().install(
      contributionDirectoryPath, contributionBaseURI);      
}

void Domain::ManagementInterfaceImpl::update(const std::string& contributionDirectoryPath,
                           const std::string& contributionBaseURI,
                           Trentino::Utils::DataObject& res)
 {
    assert(mDomain.mLocalRuntime);
    mDomain.mLocalRuntime->managementInterface().update(
     contributionDirectoryPath, contributionBaseURI,res);   
 }

ManagementInterface::ErrorMessage Domain::ManagementInterfaceImpl::deploy(
   const std::string& contributionBaseURI)
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().deploy(contributionBaseURI);
}

ManagementInterface::ErrorMessage Domain::ManagementInterfaceImpl::remove(
   const std::string& contributionIdentifier)
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().remove(contributionIdentifier);
}

ManagementInterface::ErrorMessage Domain::ManagementInterfaceImpl::removeComponent(
   const string& componentURI)
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().removeComponent(componentURI);
}

ManagementInterface::ErrorMessage Domain::ManagementInterfaceImpl::rewire(
   const string& referenceURI, 
   const string& target, 
   const string& bindingType)
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().rewire(referenceURI,target,bindingType);
}

ManagementInterface::ErrorMessage Domain::ManagementInterfaceImpl::setProperty(
   const string& propertyURI, const ManagementInterface::PropertyValues& newValues)
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().setProperty(propertyURI,newValues);
}

Trentino::ManagementInterface::ContributionDatas Domain::ManagementInterfaceImpl::getContributions() const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getContributions();
}

Trentino::ManagementInterface::ContributionData Domain::ManagementInterfaceImpl::getContribution(const std::string& contributionBaseURI) const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getContribution(contributionBaseURI);
}


ManagementInterface::Components Domain::ManagementInterfaceImpl::getComponents(
   const std::string& contributionBaseURI) const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getComponents(contributionBaseURI);
}
         
ManagementInterface::Components Domain::ManagementInterfaceImpl::getDomainLevelComponents() const
{
   ManagementInterface::Components result;

   BOOST_FOREACH(const RuntimeModel::ConstCompositePtr& composite, mDomain.mDomainLevelComposites)
   {
      transform( composite->components().begin()
               , composite->components().end()
               , back_inserter(result)
               , boost::bind(&RuntimeModel::Component::uri, _1) );
   }

   return result;
}

ManagementInterface::Attributes Domain::ManagementInterfaceImpl::getAttributes(
   const string& artifactURI) const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getAttributes(artifactURI);
}

ManagementInterface::Services Domain::ManagementInterfaceImpl::getServices(
   const string& componentURI) const 
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getServices(componentURI);
}

ManagementInterface::References Domain::ManagementInterfaceImpl::getReferences(
   const string& componentURI) const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getReferences(componentURI);
}

ManagementInterface::PropertiesNames Domain::ManagementInterfaceImpl::getPropertiesNames(
   const std::string& componentURI) const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getPropertiesNames(componentURI);
}

ManagementInterface::ImplementationType Domain::ManagementInterfaceImpl::getImplementationType(
   const string& componentURI) const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getImplementationType(componentURI);
}

ManagementInterface::PropertyValues Domain::ManagementInterfaceImpl::getPropertyValues(
   const string& propertyURI) const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getPropertyValues(propertyURI);
}

ManagementInterface::ServiceState Domain::ManagementInterfaceImpl::getServiceState(
   const string& serviceURI) const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getServiceState(serviceURI);
}

ManagementInterface::ServicesStates Domain::ManagementInterfaceImpl::getServicesStates(
   const string& componentURI) const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getServicesStates(componentURI);
}

ManagementInterface::ReferenceState Domain::ManagementInterfaceImpl::getReferenceState(
   const string& referenceURI) const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getReferenceState(referenceURI);
}

ManagementInterface::ReferencesStates Domain::ManagementInterfaceImpl::getReferencesStates(
   const string& componentURI) const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getReferencesStates(componentURI);
}

ManagementInterface::ReferenceTargets Domain::ManagementInterfaceImpl::getReferenceTargets(
   const string& referenceURI) const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getReferenceTargets(referenceURI);
}

ManagementInterface::ComponentState Domain::ManagementInterfaceImpl::getComponentState(
   const string& componentURI)  const
{
   assert(mDomain.mLocalRuntime);
   return mDomain.mLocalRuntime->managementInterface().getComponentState(componentURI);
}
void Domain::ManagementInterfaceImpl::setOwnerProcessExceptionHandler(ManagementInterface::ownerProcessExceptionHandlerPtr exceptionHandlerFunc)  
{
   mDomain.mOwnerProcessExcepionHandlerFunc = exceptionHandlerFunc;
}

#pragma warning(push)
#pragma warning(disable:4355)
   //construction
Domain::Domain()
: mURI()
, mLocalRuntime(nullptr)
, mManagementInterface(*this) //this is OK, ManagementInterfaceImpl won't use it during construction
{}
#pragma warning(pop)

   //services
void Domain::setup(const URI& uri)
{
   mURI = uri;
   logInfo("%s: Domain available at URI '%s'", __FUNCTION__, uri.c_str());
}

void Domain::registerLocalRuntime(Runtime& runtime)
{
   mLocalRuntime = &runtime;
   logInfo("%s: Local runtime joined the domain '%s'", __FUNCTION__, mURI.c_str());
}

void Domain::unregisterLocalRuntime()
{
   mLocalRuntime = nullptr; 
   logInfo("%s: Local runtime left the domain '%s'", __FUNCTION__, mURI.c_str());
}

Trentino::ManagementInterface& Domain::managementInterface()
{
   if(!mLocalRuntime)
   {
      //Since the current implementation of Domain's management interface
      //forwards all the calls to the local runtime's management interface, 
      //it makes to sense to return a valid management interface if the local 
      //runtime isn't available. 
      throw runtime_error("Local runtime not available");   
   }

   return mManagementInterface;
}

void Domain::addToDomainLevelComposite(const RuntimeModel::CompositePtr& composite)
{   
   BOOST_FOREACH(const RuntimeModel::ConstComponentPtr& component, composite->components())
   {
      const string componentName = component->scaComponent()->name();
      if(findDomainLevelComponentByName(componentName))
      {
         throw runtime_error(
            "Component name '" + componentName + "' already in use in the domain"); 
      }      
   }

   mDomainLevelComposites.push_back(composite);
}

void Domain::removeFromDomainLevelComposite(const RuntimeModel::ConstCompositePtr& composite)
{
   const RuntimeModel::Composites::iterator it = 
      find( mDomainLevelComposites.begin()
          , mDomainLevelComposites.end()
          , composite);
   if(it != mDomainLevelComposites.end())
   {
      mDomainLevelComposites.erase(it);
   }      
}

RuntimeModel::ComponentPtr Domain::findDomainLevelComponentByName( const std::string& name ) const
{
   BOOST_FOREACH(const RuntimeModel::ConstCompositePtr& composite, mDomainLevelComposites)
   {
      const RuntimeModel::ComponentPtr& component = composite->findComponentByName(name);
      if(component)
      {
         return component;
      }
   }   
  
   return RuntimeModel::ComponentPtr();
}

RuntimeModel::ServiceBases Domain::findDomandLevelServicesByName( const std::string& name ) const                                    
{
   RuntimeModel::ServiceBases result;
   BOOST_FOREACH(const RuntimeModel::ConstCompositePtr& composite, mDomainLevelComposites)
   {
      BOOST_FOREACH(const RuntimeModel::ConstComponentPtr& component, composite->components())
      {
         const RuntimeModel::ServiceBasePtr service = component->findServiceByName(name);
         if(service)
         {
            result.push_back(service);
         }
      }
   }   
  
   return result;
}

RuntimeModel::ServiceBases Domain::findRemotableServices() const
{
   return findRemotableServices("");
}

RuntimeModel::ServiceBases Domain::findRemotableServices(Trentino::Utils::URI contribution_uri) const
{
   RuntimeModel::ServiceBases result;

   BOOST_FOREACH(const RuntimeModel::ConstCompositePtr& composite, mDomainLevelComposites)
   {
      BOOST_FOREACH(const RuntimeModel::ConstComponentPtr& component, composite->components())
      {
         BOOST_FOREACH(const RuntimeModel::ServiceBasePtr& service, component->services())
         {
            boost::shared_ptr<Trentino::RuntimeModel::Contribution> contribution(composite->contribution());
            bool contribution_match = ( (contribution_uri == "") ||
                                       ((contribution_uri != "")&&(contribution_uri == contribution->baseURI())) );
            if ( (service->isRemotable() || (service->bindings().size() > 0)) & contribution_match)
            {
               result.push_back(service);
            }
         }
      }
   }
   return result;
}


Trentino::RuntimeModel::ReferenceBases Trentino::Core::Domain::findRemoteReferences(
      Trentino::Utils::URI contribution_uri) const {

   RuntimeModel::ReferenceBases result;
   BOOST_FOREACH(const RuntimeModel::ConstCompositePtr& composite, mDomainLevelComposites)
   {
      boost::shared_ptr<Trentino::RuntimeModel::Contribution> contribution(composite->contribution());
      bool contribution_match = ( (contribution_uri == "") ||
                                             ((contribution_uri != "")&&(contribution_uri == contribution->baseURI())) );
      if (contribution_match)
      {
         BOOST_FOREACH(const RuntimeModel::ConstComponentPtr& component, composite->components())
         {
            BOOST_FOREACH(const RuntimeModel::ReferenceBasePtr& reference, component->references())
            {
               BOOST_FOREACH(const RuntimeModel::ServiceBasePtr& service, reference->getTargetServices())
               {
                  if(service->scaServiceType()->isRemote())
                  {
                     result.push_back(reference);
                     break;
                  }
               }//targets
            }//references
         }//components
      }//contribution_match
   }//composites

   return result;
}
