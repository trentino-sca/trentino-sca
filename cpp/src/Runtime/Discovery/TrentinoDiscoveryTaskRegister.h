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

#ifndef TrentinoDiscoveryTaskRegisterH
#define TrentinoDiscoveryTaskRegisterH

// standart
#include <string>

// specific
#include "TrentinoDiscoveryTask.h"
#include "TrentinoDiscovery.h"

//#include "../../DiscoverySLP/TrentinoDiscoverySlp.h"

namespace Trentino{
namespace Discovery
{
   //class declaration
   //**********************************************************************************************
   //                             DiscoveryTask
   //**********************************************************************************************
   //! \ingroup Discovery
   //! \brief Discovery tasks are implemented here
   //
   //! Consider converting to command pattern but needs further heap allocation 
   //**********************************************************************************************
   class DiscoveryTaskRegister : public DiscoveryTask
   {
      // additional
   private:
        //friend class Trentino::Discovery::SLP::OpenSLP::TrentinoDiscoverySlp;


      //construction
   public:
      //****************************************************************************************
      //                               DiscoveryTaskRegister()
      //****************************************************************************************
      //! \brief Actual constructor to be used each time a service register task is created
      //!
      //! \param callback function of the discovery layer to be called once a task is finished 
      //!  without success
      //! \param retryCount
      //! \param retryInterval
      //! \param methodInterface Interface used for actually doing the task(for example implemented
      //!  by OpenSLP)
      //! \param stringIdentifier Identifier to be used while registering the task. It reflects the 
      //!  class attribute of interface.cpp. But while registering it is concatenated with a unique 
      //!  identifier to make the registration unique (to be able to deregister the correct service later
      //! \param serviceAttributes Attributes of the service that is registered.
      //! \param runtimeCB Callback to be triggered once the task succeeds or once all the 
      //!  retries are consumed.
      //****************************************************************************************
      DiscoveryTaskRegister( DiscoveryTask::discoveryFrameWorkCBFuncPtr funcPtr, 
                     int retryCount,
                     int retryInterval,
                     DiscoveryMethodInterface* methodInterface,
                     std::string serviceIdentifier, 
                     ConstMetadataConstSharedPtr serviceAttributes,
                     onDiscoveryTaskRegsiterCB runtimeCB);
      
      ~DiscoveryTaskRegister();
      //operators
   private:
      //****************************************************************************************
      //                               operator=
      //****************************************************************************************
      //! \brief Explicitly implemented in private to avoid its usage
      //****************************************************************************************
      DiscoveryTaskRegister& operator=(const DiscoveryTaskRegister& ) ;

      // services
   public:
      //****************************************************************************************
      //                               execute()
      //****************************************************************************************
      //! \brief Overridden func of base
      //****************************************************************************************
      bool execute();

      //****************************************************************************************
      //                               onTaskCancelled()
      //****************************************************************************************
      //! \brief Once all the retries fail to call the runtimeCB with the last error
      //****************************************************************************************
      void onTaskCancelled();

      std::string getServiceIdentifier()
      {
         return mServiceIdentifier;
      }

      std::string getServiceIdentifierUnique()
      {
         return mServiceIdentifierUnique;
      }

      void setServiceIdentifierUnique(std::string serviceIdentifierUnique)
      {
         mServiceIdentifierUnique = serviceIdentifierUnique;
      }

      ConstMetadataConstSharedPtr getAttributes();


      //data
   private:

      //! Service identifier to be used for registering the service
      std::string mServiceIdentifier;

      //! Service identifier that is uniquely defining the service
      //! This identifier is created by concatanating mServiceIdentifier
      //! with a uid
      std::string mServiceIdentifierUnique;

      //! Attributes of the service to be registered
      ConstMetadataConstSharedPtr mServiceAttributes;
      
      //! Runtime callback function to be triggered once the task is 
      //! finished successfully or once all the retries are consumed
      onDiscoveryTaskRegsiterCB mRuntimeCB;

   }; // class DiscoveryTaskRegister


} // namespace Discovery
} // namespace Trentino
#endif //TrentinoDiscoveryTaskRegisterH

