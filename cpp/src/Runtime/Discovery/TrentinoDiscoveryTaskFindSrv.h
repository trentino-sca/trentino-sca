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

#ifndef TrentinoDiscoveryTaskFindSrvH
#define TrentinoDiscoveryTaskFindSrvH

// standart
#include <string>

// specific
#include "TrentinoDiscoveryTask.h"
#include "TrentinoDiscoveryFoundService.h"
#include "TrentinoDiscovery.h"

namespace Trentino{
namespace Discovery
{

   //class declaration
   //**********************************************************************************************
   //                             DiscoveryTaskFindSrv
   //**********************************************************************************************
   //! \ingroup Discovery
   //! \brief Discovery tasks are implemented here
   //
   //! Consider converting to command pattern but needs further heap allocation 
   //**********************************************************************************************
   class DiscoveryTaskFindSrv : public Trentino::Discovery::DiscoveryTask
   {
      // additional
   private:
      typedef void (*runtimefindSrvCB)(int serviceID, bool status, std::string returnValOrStatusInfo);

      //construction
   public:
     
      //****************************************************************************************
      //                               DiscoveryTaskFindSrv()
      //****************************************************************************************
      //! \brief Actual constructor to be used each time a find service task is created
      //! \param callback function of the discovery layer to be called once a task is finished 
      //!  wo success
      //! \param retryCount
      //! \param retryInterval
      //! \param methodInterface Interface used for actually doing the task(for example 
      //!  implemented by OpenSLP)
      //! \param stringIdentifier Identifier to be used while finding the task. It reflects the 
      //!  class attribute of interface.cpp. 
      //! \param serviceAttributes Attributes to be used for filtering services. Services found 
      //!  need to overlap with this set of attributes.
      //! \param runtimeCB Callback to be triggered once the task succeeds or once all the 
      //!  retries are consumed.
      //! \param [out] foundServices List of services to be filled with the services that are 
      //!  found as the result of task
      //****************************************************************************************
      DiscoveryTaskFindSrv( discoveryFrameWorkCBFuncPtr funcPtr, 
         int retryCount,
         int retryInterval,
         DiscoveryMethodInterface* methodInterface,
         std::string serviceIdentifier, 
         ConstMetadataConstSharedPtr serviceAttributes, 
         runtimefindSrvCB runtimeCB,
        // listFoundServicesPtr foundServicesPtr);
         //listFoundServices& foundServices);
      //son listFoundServices* foundServices2);
      listFoundServices* rawServicesList);

      ~DiscoveryTaskFindSrv();
      //operators
   private:
      //****************************************************************************************
      //                               operator=
      //****************************************************************************************
      //! \brief Explicitly implemented in private to avoid its usage
      //****************************************************************************************
      DiscoveryTaskFindSrv& operator=(const DiscoveryTaskFindSrv& );
      
      //services
   public:
      //****************************************************************************************
      //                               execute()
      //****************************************************************************************
      //! \brief Overridden func of base
      //****************************************************************************************
      bool execute();

      std::string getServiceIdentifier()
      {
         return mServiceIdentifier;
      }

      ConstMetadataConstSharedPtr getFilterAttributes();
      //****************************************************************************************
      //                               onNewServiceFound()
      //****************************************************************************************
      //! \brief Notified once discovery dll finds out a matching service. All the found services 
      //! are hosted foundServices list of the caller of findSrv
      //****************************************************************************************
      void onNewServiceFound(boost::shared_ptr<DiscoveryFoundService> foundService);

      void onNewServiceFound(std::string serviceUrl, MetadataSharedPtr mandatoryAttributes);

      void onNewServiceFound(std::string serviceUrl, Trentino::SCA::Model::Metadata& mandatoryAttributes);

      //****************************************************************************************
      //                               onTaskCancelled()
      //****************************************************************************************
      //! \brief Once all the retries fail to call the runtimeCB with the last error
      //****************************************************************************************
      void onTaskCancelled();


      // data
   private:
      //! Service identifier 
      std::string mServiceIdentifier;

      //! Metadata set to be used as a filter while finding services
      ConstMetadataConstSharedPtr mFilterAttributes;

      //! Metadata set to be used as a filter while finding services
      //DiscoveryTask::MetadataSharedPtr mServiceAttributesAll;

      //! Runtime callback to be triggered once the findSrv task is finished
      runtimefindSrvCB mRuntimeCB;

      //! List of found services that qualify the provided filter attributes
      //listFoundServices& mFoundServices;

      //listFoundServicesPtr mFoundServicesPtr;

      //listFoundServices* mFoundServices;

      listFoundServices* mRawFoundServicesList;

   }; // class DiscoveryTaskFindSrv


} // namespace Discovery
} // namespace Trentino
#endif //TrentinoDiscoveryTaskFindSrvH