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
#include "TrentinoCoreRuntime.h"

//standard
#include <stdexcept>
#include <algorithm>
#pragma warning(push)
#pragma warning(disable:4100)
   #include <boost/bind.hpp>
   #include <boost/foreach.hpp>
#pragma warning(pop)
#include <exception>

//specific 
#include "./../RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "./../RuntimeModel/TrentinoRuntimeModelCommonFuncs.h"
#include "../RuntimeModel/TrentinoRuntimeModelComposite.h"
#include "../RuntimeModel/TrentinoRuntimeModelComponent.h"
#include "../RuntimeModel/TrentinoRuntimeModelServiceBase.h"
#include "../RuntimeModel/TrentinoRuntimeModelReference.h"
#include "../RuntimeModel/TrentinoRuntimeModelProperty.h"
#include "TrentinoCoreBootstrappingRuntimeBootstrapper.h"
#include "./../../Utils/TrentinoUtilsPerformanceHierarchyLogger.h"
#include "./../../Utils/TrentinoUtilsPerformanceHierarchyLoggerWriter.h"
#include "./../../Utils/TrentinoUtilsDataObject.h"
#include "./../../Utils/TrentinoUtilsLogging.h"
#include "TrentinoCoreContributionLoadingContributionLoader.h"
#include "TrentinoCoreContributionLoadingInstaller.h"
#include "TrentinoCoreDomain.h"
#include "../XML/TrentinoXMLSchemaQName.h"

using namespace Trentino;
using namespace Trentino::Core;
using namespace Trentino::RuntimeModel;
using namespace Trentino::Utils::Pattern;
using namespace std;


ManagementInterface::ownerProcessExceptionHandlerPtr Runtime::mOwnerProcessExcepionHandlerFunc;

namespace
{
Trentino::ManagementInterface::ContributionData getContributionData(Trentino::RuntimeModel::ContributionPtr cont)
   {
   Trentino::ManagementInterface::ContributionData data = Trentino::ManagementInterface::ContributionData::newInstance("contribution");
   int state = cont->state();
   data.setInt("state",state);
   std::string baseURI = cont->baseURI();
   data.setString("baseURI",baseURI);
   std::string version = cont->version();
   data.setString("version", version);
   return data;
   }
}

//class Runtime
   //additional
      //class ManagementInterfaceImpl
         //construction
Runtime::ManagementInterfaceImpl::ManagementInterfaceImpl(Runtime& runtime)
: mRuntime(runtime) //don't ever call any methods on the passed Domain instance here!!!
{}

//services
ManagementInterface::ErrorMessage Runtime::ManagementInterfaceImpl::install(
   const string& contributionDirectoryPath, 
   const std::string& contributionBaseURI)
{
   HLOGGER();

   ManagementInterface::ErrorMessage rslt;
   Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
   ContributionLoading::ContributionLoader& contribLoader = booter.contributionLoader();


   try
   {
      const ContributionPtr contribution = 
         contribLoader.install(contributionDirectoryPath, contributionBaseURI);
      mRuntime.mContributions.insert(contribution);
   }
   catch(exception& e)
   {
      rslt = e.what();     
   }

   return rslt;
}

void Runtime::ManagementInterfaceImpl::update(const std::string& contributionDirectoryPath,
                                              const std::string& contributionBaseURI,Trentino::Utils::DataObject& res)
{
   try
      {
      Trentino::RuntimeModel::ContributionPtr oldContribution = mRuntime.findContribution(contributionBaseURI);
      if(!oldContribution)
         {
         res.setBool("failed",true);
         std::string msg = "Contribution with given URI '";
         msg+=contributionBaseURI;
         msg+="'  not found in the runtime. No update. Run install to install the contribution";
         res.setString("result",msg);
         return;
         }
      Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =
         Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();

      ContributionLoading::ContributionLoader& contribLoader = booter.contributionLoader();
      Trentino::Core::ContributionLoading::ContributionConfigFile confFile;
      contribLoader.readSCAConfigFile(confFile,contributionDirectoryPath);
      std::string oldVersion = oldContribution->version();
      std:: string oldPath = oldContribution->localPath();
      std::string oldURI = oldContribution->baseURI();

      if(oldVersion == confFile.mContributionVersion)
         {
         //Same contribution version. No update necessary.
         res.setBool("failed",true);
         std::string msg ="New and old contribution has the same version. No update necessary. Version: ";
         msg+=oldVersion;
         res.setString("result",msg);
         return;
         }

      //now uninstall the old contribution
      const char* msg0 = oldVersion.c_str();

      logInfo("\nRemoving contribution with version '%s'\n",msg0);
      remove(oldURI);

      const char* msg1 = confFile.mContributionVersion.c_str();
      logInfo("\nInstalling contribution with version '%s'\n",msg1);
      std::string msg = install(contributionDirectoryPath,contributionBaseURI);
      if(msg.empty())
         {
         logInfo("\nDeploying contribution with version '%s'\n",msg1);
         deploy(contributionBaseURI);
         }
      if(msg.empty())
         {
         Trentino::RuntimeModel::ContributionPtr newContribution = mRuntime.findContribution(contributionBaseURI);
         res.setBool("failed",false);
         std::string msg ="Contribution '";
         msg+=oldURI;
         msg+="' updated from version ";
         msg+=oldVersion;
         msg+=" to version ";
         msg+=newContribution->version();
         res.setString("result",msg);
         return;
         }
      //Same contribution version. No update necessary.
      res.setBool("failed",true);

      std::string installMsg= install(oldPath,oldURI);
      if(installMsg.empty())
         {
         std::string msg ="Installation of new contribution failed. Rollback to previous version successful: current version is: ";
         msg+=oldVersion;
         res.setString("result",msg);
         return;
         }
      else
         {
         std::string msg ="Installation of new contribution failed. Rollback to previous version not successful: Manual re-installation required";
         msg+=oldVersion;
         res.setString("result",msg);
         return;
         }

      }
   catch(exception& e)
      {
      res.setBool("failed",true);
      std::string msg(e.what());
      res.setString("result",msg);
      }
}

ManagementInterface::ErrorMessage Runtime::ManagementInterfaceImpl::deploy(
   const std::string& contributionBaseURI)
{
   HLOGGER();
   ManagementInterface::ErrorMessage rslt;
   Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =
      Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
   ContributionLoading::ContributionLoader& contribLoader = booter.contributionLoader();

   const ContributionPtr contribution = mRuntime.findContribution(contributionBaseURI);
   if(!contribution)
   {
      return "Could not found contribution with the base URI '" + contributionBaseURI + "'";
   }

   try
   {  
      contribLoader.deploy(contribution);   
      contribLoader.run(contribution);
   }
   catch(exception& e)
   {
      rslt = e.what();    
      //Trentino::Core::Domain::onexit();

   }
   catch(...)
   {
    
     rslt = "Unknown error";
   }
   return rslt;
}

ManagementInterface::ErrorMessage Runtime::ManagementInterfaceImpl::remove(
   const std::string& contributionBaseURI)
{
   HLOGGER();

   ManagementInterface::ErrorMessage rslt;
   Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =
      Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
   ContributionLoading::ContributionLoader& contribLoader = booter.contributionLoader();

   const ContributionPtr contribution = mRuntime.findContribution(contributionBaseURI);
   if(!contribution)
   {
      return "Could not found contribution with the base URI '" + contributionBaseURI + "'";
   }

   try
   {       
      contribLoader.remove(contribution);
      mRuntime.mContributions.erase(contribution);
   }
   catch(exception& e)
   {
      rslt = e.what();     
   }

   return rslt;
}

ManagementInterface::ErrorMessage Runtime::ManagementInterfaceImpl::removeComponent(
   const string& /*componentURI*/)
{
   return "currently not supported!";
}

ManagementInterface::ErrorMessage Runtime::ManagementInterfaceImpl::rewire(
   const string& /*referenceURI*/, 
   const string& /*target*/, 
   const string& /*bindingType*/)
{
   return "currently not supported!";
}

ManagementInterface::ErrorMessage Runtime::ManagementInterfaceImpl::setProperty(
   const string& /*propertyURI*/, 
   const ManagementInterface::PropertyValues& /*newValues*/)
{
   return "currently not supported!";
}

ManagementInterface::ContributionDatas Runtime::ManagementInterfaceImpl::getContributions() const
{
   ManagementInterface::ContributionDatas result;
   Trentino::Core::Runtime::Contributions::const_iterator it;
   for(it =mRuntime.mContributions.begin();it!=mRuntime.mContributions.end();++it)
      {
      ManagementInterface::ContributionData data = getContributionData(*it);
      result.push_back(data);
      }
   return result;
}

ManagementInterface::ContributionData Runtime::ManagementInterfaceImpl::getContribution(
   const std::string& contributionBaseURI) const
{
   Trentino::Core::Runtime::Contributions::const_iterator it;
   for(it =mRuntime.mContributions.begin();it!=mRuntime.mContributions.end();++it)
      {
      if((*it)->baseURI() == contributionBaseURI)
         {
         ManagementInterface::ContributionData data = getContributionData(*it);
         return data;
         }
      }
   return ManagementInterface::ContributionData::newInstance("empty");
}


ManagementInterface::Components Trentino::Core::Runtime::ManagementInterfaceImpl::getComponents( 
   const std::string& contributionBaseURI ) const
{
   ManagementInterface::Components result ;
   const Trentino::RuntimeModel::ConstContributionPtr contribution = 
      mRuntime.findContribution(contributionBaseURI);
   if(!contribution)
   {
      return result;
   }

   const Trentino::RuntimeModel::Composites& composites = contribution->composites();
   Trentino::RuntimeModel::Composites::const_iterator compositeIterator;
   for( compositeIterator = composites.begin()
      ; compositeIterator != composites.end()
      ; ++compositeIterator)
   {
      Trentino::RuntimeModel::ConstCompositePtr aComposite = *compositeIterator;
      if(!aComposite)
      {
         continue;
      }

      const Trentino::RuntimeModel::Components components = aComposite->components();
      Trentino::RuntimeModel::Components::const_iterator componentIterator;
      for( componentIterator = components.begin()
         ; componentIterator != components.end()
         ; ++componentIterator)
      {
         const Trentino::RuntimeModel::ConstComponentPtr aComponent = *componentIterator;
         result.push_back(aComponent->uri());
      }
   }
   return result;
}

ManagementInterface::Components Runtime::ManagementInterfaceImpl::getDomainLevelComponents() const
{
   Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter
      =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
   return booter.managementInterface().getDomainLevelComponents();
}

ManagementInterface::Attributes Runtime::ManagementInterfaceImpl::getAttributes(
   const string& /*artifactURI*/) const
{
   return ManagementInterface::Attributes();
}

ManagementInterface::Services Runtime::ManagementInterfaceImpl::getServices(
   const string& componentURI) const 
{
   ManagementInterface::Services result;
   const Trentino::RuntimeModel::ConstComponentPtr component = findComponentByURI(componentURI);
   
   if(component)
   {
      transform( component->services().begin()
               , component->services().end()
               , back_inserter(result)
               , boost::bind(&ServiceBase::name, _1) ) ;
   }
   
   return result;
}   

ManagementInterface::References Runtime::ManagementInterfaceImpl::getReferences(
   const string& componentURI) const
{
   ManagementInterface::References result;
   const ConstComponentPtr component = findComponentByURI(componentURI);

   if(component)
   {
      transform( component->references().begin()
               , component->references().end()
               , back_inserter(result)
               , boost::bind(&ReferenceBase::name, _1) );
   }

   return result;
}

ManagementInterface::PropertiesNames Runtime::ManagementInterfaceImpl::getPropertiesNames(
   const std::string& componentURI) const
{
   ManagementInterface::PropertiesNames result;
   const Trentino::RuntimeModel::ConstComponentPtr component = findComponentByURI(componentURI);
   
   if(component)
   {
      transform( component->properties().begin()
               , component->properties().end()
               , back_inserter(result)
               , boost::bind(&Trentino::RuntimeModel::Property::name, _1) ) ;
   }
   
   return result;   
}

ManagementInterface::ImplementationType Runtime::ManagementInterfaceImpl::getImplementationType(
   const string& componentURI) const
{
   const Trentino::RuntimeModel::ConstComponentPtr component = findComponentByURI(componentURI);
  
   if(component)
   {
      return component->getImplementationType().localPart();
   }
   
   return ManagementInterface::ImplementationType();   
}

ManagementInterface::PropertyValues Runtime::ManagementInterfaceImpl::getPropertyValues(
   const string& propertyURI) const
{
   ManagementInterface::PropertyValues result;
   ConstPropertyPtr property = findPropertyByPropertyURI(propertyURI);
   
   if(property)
   {
      result.assign(property->values().begin(), property->values().end());
   }

   return result;
}

ManagementInterface::ServiceState Runtime::ManagementInterfaceImpl::getServiceState(
   const string& serviceURI) const
{
   const Trentino::RuntimeModel::ConstServiceBasePtr service = findServiceByServiceURI(serviceURI);
   if(!service)
   {
      return ManagementInterface::ServiceState();
   }
   return CommonFuncs::toString(service->state());
}

ManagementInterface::ServicesStates Runtime::ManagementInterfaceImpl::getServicesStates(
   const string& componentURI) const
{
   ManagementInterface::ServicesStates result;
   const ConstComponentPtr component = findComponentByURI(componentURI);

   if(component)
   {
      BOOST_FOREACH(const RuntimeModel::ConstServiceBasePtr& service, component->services())
      {
         result[service->name()] = CommonFuncs::toString(service->state());
      }
   }
 
   return result;
   
}

ManagementInterface::ReferenceState Runtime::ManagementInterfaceImpl::getReferenceState(
   const string& referenceURI) const
{
   const Trentino::RuntimeModel::ConstReferenceBasePtr reference = findReferenceByReferenceURI(referenceURI);
   if(!reference)
   {
      return ManagementInterface::ReferenceState();
   }
   return CommonFuncs::toString(reference->state());
}

ManagementInterface::ReferencesStates Runtime::ManagementInterfaceImpl::getReferencesStates(
   const string& componentURI) const
{
   ManagementInterface::ReferencesStates result;
   const ConstComponentPtr component = findComponentByURI(componentURI);

   if(component)
   {
      BOOST_FOREACH(const RuntimeModel::ConstReferenceBasePtr& reference, component->references())
      {
         result[reference->name()] = CommonFuncs::toString(reference->state());
      }
   }
 
   return result;
}

ManagementInterface::ReferenceTargets Runtime::ManagementInterfaceImpl::getReferenceTargets(
   const string& referenceURI) const
{
   ManagementInterface::ReferenceTargets result;
   const Trentino::RuntimeModel::ConstReferenceBasePtr aReference = 
      findReferenceByReferenceURI(referenceURI);
   if(!aReference)
   {
      return ManagementInterface::ReferenceTargets();
   }
   Trentino::RuntimeModel::ServiceBases targetServices = aReference->getTargetServices();
   Trentino::RuntimeModel::ServiceBases::const_iterator it;
   for(it = targetServices.begin(); it!=targetServices.end();++it)
   {
      Trentino::RuntimeModel::ConstServiceBasePtr aService = *it;
      if(aService)
      {
         result.push_back(
            aService->component().lock()->uri() + "#service(" + aService->name() + ")");;  
      }
   }
   return result;
}

ManagementInterface::ComponentState Runtime::ManagementInterfaceImpl::getComponentState(
   const string& componentURI)  const
{
   const ConstComponentPtr component = findComponentByURI(componentURI);
   if(component)
   {
      return CommonFuncs::toString(component->state());
   }

   return "";
}
   
      //management
Trentino::RuntimeModel::ConstComponentPtr Trentino::Core::Runtime::ManagementInterfaceImpl::
   findComponentByURI( const std::string& componentURI ) const
{   
   const Trentino::Core::Runtime::Contributions& contributions = mRuntime.contributions();
   Trentino::Core::Runtime::Contributions::const_iterator contributionIterator;
   for( contributionIterator = contributions.begin()
      ; contributionIterator != contributions.end()
      ; ++contributionIterator)
   {
      const Trentino::RuntimeModel::ConstContributionPtr contribution = *contributionIterator;
      const Trentino::RuntimeModel::Composites& composites = contribution->composites();
      Trentino::RuntimeModel::Composites::const_iterator compositeIterator;
      for( compositeIterator = composites.begin()
         ; compositeIterator != composites.end()
         ;++compositeIterator)
      {
         const Trentino::RuntimeModel::ConstCompositePtr aComposite = *compositeIterator;
         if(!aComposite)
         {
            continue;
         }

         const Trentino::RuntimeModel::Components& components = aComposite->components();
         Trentino::RuntimeModel::Components::const_iterator componentIterator;
         for( componentIterator = components.begin()
            ; componentIterator != components.end()
            ;++componentIterator)
         {

            const Trentino::RuntimeModel::ConstComponentPtr aComponent = *componentIterator;
            if(aComponent->uri() == componentURI)
            {
               return aComponent;
            }
         }
      }
   }

   return Trentino::RuntimeModel::ConstComponentPtr();
}

Trentino::RuntimeModel::ConstServiceBasePtr Trentino::Core::Runtime::ManagementInterfaceImpl::
   findServiceByServiceURI(const std::string& serviceURI ) const
{
   const std::vector<std::string> parts = 
      Trentino::Utils::URIUtil::getNameAndComponentURIByEntityURI(serviceURI);
   if(parts.size() !=2 )
   {
      return ConstServiceBasePtr();
   }

   const std::string componentURI = parts[0];
   const std::string serviceName = parts[1];

   const ConstComponentPtr component = findComponentByURI(componentURI);

   if(component)
   {
      return component->findServiceByName(serviceName);      
   }

   return ConstServiceBasePtr();
}

Trentino::RuntimeModel::ConstReferenceBasePtr Trentino::Core::Runtime::ManagementInterfaceImpl::
   findReferenceByReferenceURI( const std::string& referenceURI ) const
{    
   const std::vector<std::string> parts = 
      Trentino::Utils::URIUtil::getNameAndComponentURIByEntityURI(referenceURI);
   if(parts.size() !=2 )
   {
      return ConstReferenceBasePtr();
   }

   const std::string componentURI = parts[0];
   const std::string referenceName = parts[1];

   const ConstComponentPtr component = findComponentByURI(componentURI);

   if(component)
   {
      return component->findReferenceByName(referenceName);      
   }

   return ConstReferenceBasePtr();
}

Trentino::RuntimeModel::ConstPropertyPtr Trentino::Core::Runtime::ManagementInterfaceImpl::
   findPropertyByPropertyURI( const std::string& propertyURI ) const
{    
   const std::vector<std::string> parts = 
      Trentino::Utils::URIUtil::getNameAndComponentURIByEntityURI(propertyURI);
   if(parts.size() !=2 )
   {
      return ConstPropertyPtr();
   }

   const std::string componentURI = parts[0];
   const std::string propertyName = parts[1];

   const ConstComponentPtr component = findComponentByURI(componentURI);

   if(component)
   {
      return component->findPropertyByName(propertyName);
   }

   return ConstPropertyPtr();
}
void Trentino::Core::Runtime::ManagementInterfaceImpl::setOwnerProcessExceptionHandler(ManagementInterface::ownerProcessExceptionHandlerPtr exceptionHandlerFunc)
{    
   mRuntime.mOwnerProcessExcepionHandlerFunc = exceptionHandlerFunc;
}
#pragma warning(push)
#pragma warning(disable:4355)
   //construction
Runtime::Runtime()
: mManagementInterface(*this) //this is OK, ManagementInterfaceImpl won't use it during construction
{}
#pragma warning(pop)

Runtime::~Runtime()
{}

//services
Trentino::RuntimeModel::ContributionPtr Runtime::findContribution(
   const Trentino::Utils::URI& baseURI) const
{
   const Runtime::Contributions::const_iterator it = 
      find_if( mContributions.begin()
             , mContributions.end()
             , boost::bind(&Contribution::baseURI, _1) == baseURI);

   return it == mContributions.end() ? ContributionPtr() : *it;   
}

