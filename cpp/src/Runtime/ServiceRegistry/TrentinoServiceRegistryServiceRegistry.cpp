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
#include "TrentinoServiceRegistryServiceRegistry.h"

//specific
#include "TrentinoServiceRegistryServiceInfo.h"
#include "../Core/TrentinoCoreBootstrappingRuntimeBootstrapper.h"
#include "../../Utils/TrentinoUtilsLogging.h"
#include "../Core/TrentinoCoreDomain.h"
#include "../RuntimeModel/TrentinoRuntimeModelComponent.h"

using Trentino::ServiceRegistry::ServiceRegistry;
namespace RuntimeModel = Trentino::RuntimeModel;

//class Service Registry
//construction
ServiceRegistry::ServiceRegistry()
   {}

ServiceRegistry::~ServiceRegistry()
   {}

RuntimeModel::ServiceBasePtr ServiceRegistry::findService( 
   const Trentino::ServiceRegistry::ServiceInfo& serviceInfo) const
   {
   return findService(serviceInfo.componentName(),serviceInfo.serviceName());
   }


Trentino::RuntimeModel::ServiceBasePtr Trentino::ServiceRegistry::ServiceRegistry::findService(
   const std::string& componentName,
   const std::string& serviceName) const
   {
   Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =
      Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
   if(componentName != ""){
      const RuntimeModel::ComponentPtr component = booter.domain().findDomainLevelComponentByName(componentName);
      if(component){
         return  component->findServiceByName(serviceName);
         }
      }

   const RuntimeModel::ServiceBases result = 
      booter.domain().findDomandLevelServicesByName(serviceName);

   if(result.empty())
      {
      return RuntimeModel::ServiceBasePtr();
      }
   else
      {
      return result[0];
      }
   }

RuntimeModel::ServiceBases ServiceRegistry::findRemotableServices() const
   {
   Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
   Trentino::Core::Domain& domain = booter.domain() ;
   return domain.findRemotableServices();
   }

RuntimeModel::ServiceBases ServiceRegistry::findRemotableServices(std::string contributionURI) const
   {
   Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
   Trentino::Core::Domain& domain = booter.domain() ;
   return domain.findRemotableServices(contributionURI);
   }

Trentino::RuntimeModel::ReferenceBases Trentino::ServiceRegistry::ServiceRegistry::findRemoteReferences(
   std::string contributionURI) const {
      Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
      Trentino::Core::Domain& domain = booter.domain() ;
      return domain.findRemoteReferences(contributionURI);
   }