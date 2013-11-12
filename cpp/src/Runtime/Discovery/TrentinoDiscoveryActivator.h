// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2013
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

#ifndef TrentinoDiscoveryActivatorH
#define TrentinoDiscoveryActivatorH

//standard
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/thread/recursive_mutex.hpp>

//specific
#include "TrentinoDiscoveryInterface.h"
#include "TrentinoDiscoveryManagementInterface.h"
#include "TrentinoDiscoveryFactory.h"
#include "../Core/TrentinoCoreBootstrappingRuntimeConfiguration.h"
#include "../RuntimeModel/TrentinoRuntimeModel.h"

using Trentino::RuntimeModel::ServiceBases;



namespace Trentino{
namespace Discovery
{

      typedef boost::shared_ptr<listFoundServices> listFoundServicesPtr;
      typedef struct{
         listFoundServicesPtr serviceList;
         Trentino::RuntimeModel::ServiceBasePtr service;
      } findServiceEntry;
      typedef boost::shared_ptr<findServiceEntry> findServiceEntryPtr;

	//**********************************************************************************************
	//                             DiscoveryMethodInterface
	//**********************************************************************************************
	//! \ingroup Discovery
	//! \brief An intermediary responsible for instantiating, initialization and starting of
	//! discovery framework
	//!
	//**********************************************************************************************
   class DiscoveryActivator
   {


	public:
	   typedef boost::shared_ptr<Trentino::SCA::Model::Metadata> MetadataSharedPtr;

		static DiscoveryActivator* instance(void);

      void startDiscoveryActivator();

      void stopDiscoveryActivator()
      {
         delete mInstance;
         //mDiscoveryManagementInterface->stop();
      }

      //****************************************************************************************
      //                                registerServiceAsync()
      //****************************************************************************************
      //! \brief Service dicovery request to register a service. Works asyncronously.
      //! The method calls appropriate method of DiscoveryInterface and exits.
      //! \param svc - service to be registered
      //! \retval - boolean success indication
      //****************************************************************************************
      virtual bool registerServiceAsync(Trentino::RuntimeModel::ServiceBasePtr svc);

      //****************************************************************************************
      //                                registerRemotableServices()
      //****************************************************************************************
      //! \brief Service dicovery request to register a set of services. Works asyncronously.
      //! \param services - services to be registered
      //! \retval - boolean success indication
      //****************************************************************************************
      virtual void registerRemotableServices(ServiceBases services);

      //****************************************************************************************
      //                                deregisterService()
      //****************************************************************************************
      //! \brief Service dicovery request to deregister a service.
      //! The method calls appropriate method of DiscoveryInterface and exits.
      //! \param svc - service to be deregistered
      //! \retval - boolean success indication
      //****************************************************************************************
      virtual bool deregisterService(Trentino::RuntimeModel::ServiceBasePtr svc);

      //****************************************************************************************
      //                                deregisterService()
      //****************************************************************************************
      //! \brief Service dicovery request to deregister a set of services.
      //! \param services - services to be deregistered
      //! \retval - boolean success indication
      //****************************************************************************************
      virtual bool deregisterServices(ServiceBases services);

      //****************************************************************************************
      //                                discoverServices()
      //****************************************************************************************
      //! \brief Service dicovery request to find services for given references
      //! \retval - boolean success indication
      //****************************************************************************************
      virtual bool discoverServices(Trentino::RuntimeModel::ReferenceBases references);




	private:
       DiscoveryActivator();
       virtual ~DiscoveryActivator();
		//**********************************************************************************************
		//                           DiscoveryActivator()
		//**********************************************************************************************
		//! \brief Constructor
		//! \param[in] c - reference to the RuntimeConfiguration object
		//**********************************************************************************************
		DiscoveryActivator(boost::shared_ptr<const Trentino::Core::Bootstrapping::RuntimeConfiguration> c);

		//**********************************************************************************************
      //                           checkAvailability()
      //**********************************************************************************************
      //! \brief Function checks if the discovery framework is up and running.
		//
      //**********************************************************************************************
		bool checkAvailability(void);

		static DiscoveryActivator *mInstance;
		DiscoveryManagementInterface* mDiscoveryManagementInterface;
		DiscoveryInterface* mDiscoveryInterface;
		bool mDiscoveryInterfaceReady;
		bool mDiscoveryInterfaceEnabled;
      bool mIsDA;


		void discoveryStartCallback(bool status, std::string returnValOrStatusInfo);
		static void discoveryStartCallbackMediator(bool status, std::string retval);

      //**********************************************************************************************
      //                           mRegistrationMap
      //**********************************************************************************************
      //! \brief Map of ids returned by service registration interface to the service pointers.
      //! Used in callback to fill the registration id after registration is complete.
      //**********************************************************************************************
		std::map<int, Trentino::RuntimeModel::ServiceBasePtr> mRegistrationMap;

      //**********************************************************************************************
      //                           mRegistrationMapMutex
      //**********************************************************************************************
      //! \brief Mutex used to access the registration map
      //**********************************************************************************************
		boost::recursive_mutex mRegistrationMapMutex;

      void discoveryTaskRegisterCallback(int reqId, bool status, std::string returnValOrStatusInfo);
      static void discoveryTaskRegisterCallbackMediator(int reqId, bool status, std::string retval);



      //============================================================================================

      std::map<int, findServiceEntryPtr> mFindServicemap;
      //**********************************************************************************************
      //                           mFindServiceMapMutex
      //**********************************************************************************************
      //! \brief Mutex used to access the discovery map
      //**********************************************************************************************
      boost::recursive_mutex mFindServiceMapMutex;
      void discoveryFindServiceTaskCallback(int reqID, bool status, std::string returnValOrStatusInfo);
      static void discoveryFindServiceTaskCallbackMediator(int reqID, bool status, std::string returnValOrStatusInfo);


	};



}
}

#endif // TrentinoDiscoveryActivatorH
