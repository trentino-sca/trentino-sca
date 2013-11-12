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

#ifndef TrentinoServiceRegistryServiceRegistryBaseH
#define TrentinoServiceRegistryServiceRegistryBaseH

//specific
#include "ServiceRegistry.h"
#include "../RuntimeModel/TrentinoRuntimeModelServiceBase.h"
#include "../RuntimeModel/TrentinoRuntimeModelErrorCode.h"

namespace Trentino{
namespace ServiceRegistry
{
   
   //**********************************************************************************************
   //                                         ServiceRegistryBase
   //**********************************************************************************************
   //! \brief The service registry interface is the central point for getting information about 
   //!        services provided by a Runtime or accessed by a Runtime
   //**********************************************************************************************
   class ServiceRegistryBase
   {
      //services
   public:
      //*******************************************************************************************
      //                                         findService()
      //*******************************************************************************************
      //! \brief Searches for a services according to the given service description.
      //! \param[in] serviceInfo Describes the search criteria. Passing an empty pointer will cause
      //!            undefined behavior. 
      //! \param[out] ec Reserved for future use. 
      //! \return A shared pointer to the found service or an empty shared pointer if no service 
      //!         could be found.
      //*******************************************************************************************
      virtual Trentino::RuntimeModel::ServiceBasePtr findService(
         const ServiceInfo& serviceInfo) const = 0;

      //*******************************************************************************************
      //                                         findService()
      //*******************************************************************************************
      //! \brief Searches for a services according to the given service description.
      //! \param[in] servicename, the name of the service in the form <component name> / <service name>
      //! \param[out] ec Reserved for future use. 
      //! \return A shared pointer to the found service or an empty shared pointer if no service 
      //!         could be found.
      //*******************************************************************************************
      virtual Trentino::RuntimeModel::ServiceBasePtr findService(
         const std::string& componentName,
         const std::string& serviceName) const = 0;

      //*******************************************************************************************
      //                                         findRemotableServices()
      //*******************************************************************************************
      //! \brief Searches for a remotable services
      //! \return List of remotable services
      //*******************************************************************************************
      virtual Trentino::RuntimeModel::ServiceBases findRemotableServices() const = 0;

      //*******************************************************************************************
      //                                         findRemotableServices()
      //*******************************************************************************************
      //! \brief Searches for a remotable services within given contibution by contribution URI
      //! \return List of remotable services
      //*******************************************************************************************
      virtual Trentino::RuntimeModel::ServiceBases findRemotableServices(std::string contributionURI) const = 0;

      //*******************************************************************************************
       //                                         findRemoteReferences()
       //*******************************************************************************************
       //! \brief Searches for a remote references within given contibution by contribution URI
       //! \return List of remote references
       //*******************************************************************************************
       virtual Trentino::RuntimeModel::ReferenceBases findRemoteReferences(std::string contributionURI) const = 0;

   }; //class ServiceRegistryBase 

}//namespace ServiceRegistry
}//namespace Trentino

#endif //TrentinoServiceRegistryServiceRegistryBaseH
