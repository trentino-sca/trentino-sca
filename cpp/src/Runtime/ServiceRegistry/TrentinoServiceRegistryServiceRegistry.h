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

#ifndef TrentinoServiceRegistryServiceRegistryH
#define TrentinoServiceRegistryServiceRegistryH

#ifdef WIN32
   #ifdef CORE_EXPORTS
      #define SERVICE_REGISTRY_IMPORT_EXPORT __declspec(dllexport)
   #else
      #define SERVICE_REGISTRY_IMPORT_EXPORT __declspec(dllimport)       
   #endif //CORE_EXPORTS
#else
   #define SERVICE_REGISTRY_IMPORT_EXPORT
#endif //WIN32

//baseclass
#include "TrentinoServiceRegistryServiceRegistryBase.h"

namespace Trentino{
namespace ServiceRegistry
{
   class SERVICE_REGISTRY_IMPORT_EXPORT ServiceRegistry : public ServiceRegistryBase 
   {
      //construction
   public:
      ServiceRegistry();
      ~ServiceRegistry();

      //services
   public:
   //**********************************************************************************************
   //                                         findService()
   //**********************************************************************************************
   //override from ServiceRegistryBase (see documentation in ServieRegistryBase)
   //**********************************************************************************************
   virtual Trentino::RuntimeModel::ServiceBasePtr findService(
      const ServiceInfo& serviceInfo) const;

   //**********************************************************************************************
   //                                         findService()
   //**********************************************************************************************
   //override from ServiceRegistryBase (see documentation in ServieRegistryBase)
   //**********************************************************************************************
   virtual Trentino::RuntimeModel::ServiceBasePtr findService(
         const std::string& componentName,
         const std::string& serviceName) const;

   //**********************************************************************************************
   //                                         findRemotableServices()
   //**********************************************************************************************
   //override from ServiceRegistryBase (see documentation in ServieRegistryBase)
   //**********************************************************************************************
   virtual Trentino::RuntimeModel::ServiceBases findRemotableServices() const;

   //**********************************************************************************************
   //                                         findRemotableServices()
   //**********************************************************************************************
   //override from ServiceRegistryBase (see documentation in ServieRegistryBase)
   //**********************************************************************************************
   virtual Trentino::RuntimeModel::ServiceBases findRemotableServices(std::string contributionURI) const;

   //**********************************************************************************************
   //                                         findRemoteReferences()
   //**********************************************************************************************
   //override from ServiceRegistryBase (see documentation in ServieRegistryBase)
   //**********************************************************************************************
   virtual Trentino::RuntimeModel::ReferenceBases findRemoteReferences(std::string contributionURI) const;

   }; //class ServiceRegistry
}//namespace ServiceRegistry
}//namespace Trentino

#endif //TrentinoServiceRegistryServiceRegistryH
