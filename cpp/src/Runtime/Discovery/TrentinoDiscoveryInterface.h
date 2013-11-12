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

#ifndef TrentinoDiscoveryInterfaceH
#define TrentinoDiscoveryInterfaceH

// standart
#include <string>


// specific
#include "../SCAModel/TrentinoSCAModelMetadata.h"
#include "TrentinoDiscoveryFoundService.h"
#include "TrentinoDiscovery.h"


namespace Trentino{
namespace Discovery
{


   //class declaration
   //**********************************************************************************************
   //                             DiscoveryInterface
   //**********************************************************************************************
   //! \ingroup Discovery
   //! \brief This is the interface used to communicate service discovery related requests to the 
   //! to the discovery framework
   //!  
   //**********************************************************************************************
   class DiscoveryInterface
   {
      //additional
   public:
      //typedef std::list< boost::shared_ptr<DiscoveryFoundService> > listFoundServices;
      //typedef boost::shared_ptr< std::list< boost::shared_ptr<DiscoveryFoundService> > >listFoundServicesPtr;
      //typedef std::list< DiscoveryFoundService* >rawListFoundServicesPtr;
      //typedef std::vector< DiscoveryFoundService* >rawListFoundServicesPtr;
      //construction
   protected:

      //****************************************************************************************
      //                               DiscoveryInterface()
      //****************************************************************************************
      //! \brief Constructor to be used by the derived class
      //****************************************************************************************
      DiscoveryInterface(int retryCount, int retryInterval)
         :mRetryCount(retryCount),
         mRetryInterval(retryInterval)
      {
      }

      //****************************************************************************************
      //                                ~DiscoveryInterface()
      //****************************************************************************************
      //! \brief As being the base class, virtual destructor is required
      //****************************************************************************************
      virtual ~DiscoveryInterface() {}; 

      // services
   public:

      //****************************************************************************************
      //                                registerService()
      //****************************************************************************************
      //! \brief Service discovery request to deregister a service. Works asynchronously so the
      //! caller retrieves the result via callback.
      //! The caller does not know the result, but for sure the request is repeated as many times 
      //! as configured. 
      //!
      //! \param serviceIdentifier It is agreed to pass the class attribute of the interface.cpp
      //! \param serviceAttributes Metadata of the service to be registered
      //! \param onServiceRegistered Callback to be called once the service registration task is finished
      //! with/wo success
      //! callback gets a boolean status info. If the stat is true, unique identifier of the 
      //! registration is also passed in the second argument of the callback
      //! 
      //! \return The id passed to the caller to let it find its request once the callback is 
      //! triggered.
      //****************************************************************************************
      virtual int  registerService(std::string serviceIdentifier, 
         ConstMetadataConstSharedPtr serviceAttributes, 
         onDiscoveryTaskRegsiterCB onServiceFoundFn) = 0;

      //****************************************************************************************
      //                                deregisterService()
      //****************************************************************************************
      //! \brief Service discovery request to deregister a service. Works synchronously. 
      //! The caller does not know the result, but for sure the request is repeated as many times 
      //! as configured. So no callback is given to be called as the task is accomplished 
      //! successfully or unsuccessfully.
      //****************************************************************************************
      virtual void deregisterService(std::string serviceIdentifier) = 0;

      //****************************************************************************************
      //                                findService()
      //****************************************************************************************
      //! \brief Service discovery request to find a service. Works synchronously. 
      //! The caller is notified about the result with the given callback function.
      //!
      //! \param serviceIdentifier It is agreed to pass the class attribute of the interface.cpp
      //! \param serviceAttributes Metadata of the service to be registered
      //! \param foundServices List of all the services matching the service identifier and given service
      //! attributes
      //! \param onServiceRegistered Callback to be called once the service registration task is finished
      //! with/wo success
      //! callback gets a boolean status info. If the stat is true, unique identifier of the 
      //! registration is also passed in the second argument of the callback
      //! 
      //! \return The id passed to the caller to let it find its request once the callback is 
      //! triggered.
      //****************************************************************************************
      virtual int findService(std::string serviceIdentifier,
         ConstMetadataConstSharedPtr serviceAttributes, 
         listFoundServices& foundServices,
         onDiscoveryTaskFindSrvCB onServiceFoundFn) = 0;

      //virtual DiscoveryInterface* getDiscoveryInterface() = 0;

      //data
   protected:
      //! How many times to retry to execute the discovery task in case of failure
      int mRetryCount;

      //! How long to wait between the retries of a task. (in seconds)
      int mRetryInterval;

   };


} // namespace Discovery
} // namespace Trentino

#endif//TrentinoDiscoveryInterfaceH