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
#ifndef TrentinoServiceRegistryServiceInfoH
#define TrentinoServiceRegistryServiceInfoH

#include "ServiceRegistry.h"
#include "TrentinoServiceRegistryServiceProperties.h"


namespace Trentino{
namespace ServiceRegistry
{
   //class declaration
   //******************************************************************************
   //                  ServiceInfo
   //******************************************************************************
   //! \brief Informations used to query or describe a service
   //******************************************************************************
   class ServiceInfo{
      //contructors
   public:
      ServiceInfo();
      virtual ~ServiceInfo();

      // services
   public:
   
      //****************************************************************************************************
      //                                         serviceName()
      //****************************************************************************************************
      //! \brief return the name of the service
      //! \return const std::string&
      //****************************************************************************************************
      const std::string& serviceName() const;


      //****************************************************************************************************
      //                                         setServiceName()
      //****************************************************************************************************
      //! \brief set the new name of the service
      //! \param std::string serviceName the new name of the servcie
      //! \return void
      //****************************************************************************************************
      void setServiceName(const std::string& serviceName);

      //****************************************************************************************************
      //                                         componentName()
      //****************************************************************************************************
      //! \brief get the component name for this service
      //! \return std::string
      //****************************************************************************************************
      std::string componentName() const;

      //****************************************************************************************************
      //                                         setComponentName()
      //****************************************************************************************************
      //! \brief set the componentr name for this service.
      //! \param std::string val
      //! \return void
      //****************************************************************************************************
      void setComponentName(std::string val);

      //****************************************************************************************************
      //                                         properties()
      //****************************************************************************************************
      //! \brief return all the properties of this ServiceInfo
      //! \return const Trentino::ServiceRegistry::ServicePropertiesPtr&
      //****************************************************************************************************
      const Trentino::ServiceRegistry::ServicePropertiesPtr& properties() const;

      // data
   private:
      std::string mServiceName;
      std::string mComponentName;

      ServicePropertiesPtr mProperties;

   }; //class ServiceInfo
  
   #include "TrentinoServiceRegistryServiceInfo.inl"


} //namespace ServiceRegistry
} //namespace Trentino

#endif //TrentinoServiceRegistryServiceInfoH
