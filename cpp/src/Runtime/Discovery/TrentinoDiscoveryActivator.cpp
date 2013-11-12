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

#include "../../Utils/TrentinoUtilsLoggingLogger.h"
#include "../../Utils/TrentinoUtilsPatternStaticClass.h"

#include "../SCAModel/TrentinoSCAModel.h"
#include "../SCAModel/TrentinoSCAModelComponent.h"
#include "../SCAModel/TrentinoSCAModelComponentService.h"
#include "../SCAModel/TrentinoSCAModelComponentReference.h"
#include "../SCAModel/TrentinoSCAModelCPPInterface.h"
#include "../SCAModel/TrentinoSCAModelImplementation.h"

#include "../RuntimeModel/TrentinoRuntimeModel.h"
#include "../RuntimeModel/TrentinoRuntimeModelComponent.h"
#include "../RuntimeModel/TrentinoRuntimeModelService.h"
#include "../RuntimeModel/TrentinoRuntimeModelReference.h"

#include "../Core/TrentinoCoreComponentCPPImplementationManager.h"
#include "../Core/TrentinoCoreBootstrappingRuntimeBootstrapper.h"
#include "../Binding/TrentinoBindingBindingManagerBase.h"
//#include "../../BindingSCAClient/Binding/SCA/Client/TrentinoBindingSCAClientProxyDelegate.h"

#include "TrentinoDiscoveryActivator.h"

#include <boost/thread.hpp>

using namespace boost;
using namespace boost::this_thread;
//#include "../SCAModel/TrentinoSCAModelMetadata.h"
#define DISCOVERY_FAILED 0
using namespace Trentino::Discovery;
namespace SCAModel = Trentino::SCA::Model;
namespace RuntimeModel = Trentino::RuntimeModel;
namespace ContributionLoading = Trentino::Core::ContributionLoading;

Trentino::Discovery::DiscoveryActivator* Trentino::Discovery::DiscoveryActivator::mInstance = nullptr;

DiscoveryActivator::DiscoveryActivator()
{
	mDiscoveryManagementInterface = nullptr;
	mDiscoveryInterface = nullptr;
	mDiscoveryInterfaceReady = false;
	mDiscoveryInterfaceEnabled = false;
}

DiscoveryActivator::~DiscoveryActivator()
{
   Trentino::Core::Bootstrapping::RuntimeBootstrapper& bootstrapper = Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
   boost::shared_ptr<const Trentino::Core::Bootstrapping::RuntimeConfiguration> c = bootstrapper.configuration();

   if(c->enableRemoteServiceDiscovery() == false)
   {
      return;
   }
   mDiscoveryManagementInterface->stop(mIsDA);
}



void DiscoveryActivator::discoveryStartCallback(bool status, std::string retval)
{
   if (status == true)
   {
      mDiscoveryInterfaceReady = true;
      mDiscoveryInterfaceEnabled = true;
      mDiscoveryInterface = mDiscoveryManagementInterface->getDiscoveryInterface();
   }
   else
   { //! \todo what to do here? - continue working and consider discovery disabled to avoid blocking
      logError("Discovery subsystem start failed, discovery will be unavailable!");
      mDiscoveryInterfaceEnabled = false;
   }
 
}

void Trentino::Discovery::DiscoveryActivator::discoveryStartCallbackMediator(bool status, std::string retval) {

   mInstance->discoveryStartCallback(status, retval);

}

DiscoveryActivator* Trentino::Discovery::DiscoveryActivator::instance() 
{
	if (mInstance == nullptr)
	{
		mInstance = new DiscoveryActivator();
	}

	assert(mInstance);
	return mInstance;
}

void DiscoveryActivator::startDiscoveryActivator()
{
   Trentino::Core::Bootstrapping::RuntimeBootstrapper& bootstrapper = Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
   boost::shared_ptr<const Trentino::Core::Bootstrapping::RuntimeConfiguration> c = bootstrapper.configuration();

   if(c->enableRemoteServiceDiscovery() == true)
   {
      mDiscoveryManagementInterface =
         Trentino::Discovery::DiscoveryFactory::getDiscoveryManagementInterface(Trentino::Discovery::DiscoveryManagementInterface::SLP);
      //! \todo Add timeout/retries for discovery start
      mIsDA = c->startDiscoveryProxy();
      mDiscoveryManagementInterface->start(c->startDiscoveryProxy(),
         c->discoveryMaxRetry(),
         c->discoveryRetryInterval(),
         DiscoveryActivator::discoveryStartCallbackMediator);
      //boost::this_thread::sleep(boost::posix_time::millisec(50000));
      //  mDiscoveryManagementInterface->stop();
   }

}

void Trentino::Discovery::DiscoveryActivator::registerRemotableServices(
      ServiceBases services)
{
   Trentino::RuntimeModel::ServiceBases::const_iterator it;
   for(it = services.begin(); it != services.end(); ++it)
   {
      Trentino::RuntimeModel::ServiceBasePtr service = *it;
      this->registerServiceAsync(service);
   }
}





bool DiscoveryActivator::registerServiceAsync(Trentino::RuntimeModel::ServiceBasePtr service)
{

   if (!this->checkAvailability()) return false;

   Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
   Trentino::Binding::BindingManagerBasePtr bindingManager = booter.bindingManagerBasePtr();
   boost::shared_ptr<Trentino::SCA::Model::Metadata> bindingMetadata = bindingManager->getServiceMetadata("", service);
   Trentino::SCA::Model::MetadataPtr serviceMetadata = service->metaData();

   MetadataPtr joinedMetadata(new Metadata());
   //joinedMetadata.reset(new Metadata());

   // Get all service metadata and merge it
   std::vector<MetadataStringAttributePtr> temp = bindingMetadata->stringAttributesElements();
   for(size_t i = 0; i < temp.size(); i++) {
      MetadataStringAttribute *attr = new MetadataStringAttribute();
      attr->setName(temp[i]->name().c_str());
      attr->setValue(temp[i]->value().c_str());
      joinedMetadata->addStringAttributesElement(attr/*temp[i].get()*/);
      }
   /*
   if (serviceMetadata != nullptr)
   {
   temp = serviceMetadata->stringAttributesElements();
   }
   else
   {
   temp.clear();
   }
   */
   if(serviceMetadata!= nullptr){
      for(size_t i = 0; i < serviceMetadata->stringAttributesElements().size(); i++) {
         MetadataStringAttribute *attr = new MetadataStringAttribute();
         attr->setName(serviceMetadata->stringAttributesElements()[i]->name().c_str());
         attr->setValue(serviceMetadata->stringAttributesElements()[i]->value().c_str());
         joinedMetadata->addStringAttributesElement(attr);
         }}


   // Now call registration method
   const Trentino::SCA::Model::CPPInterfacePtr scaCPPInterface
      = boost::static_pointer_cast<Trentino::SCA::Model::CPPInterface>(service->scaServiceType()->interfaceElement());

   mRegistrationMapMutex.lock();
   int reqid = mDiscoveryInterface->registerService(scaCPPInterface->clazz(), joinedMetadata, DiscoveryActivator::discoveryTaskRegisterCallbackMediator);
   if (reqid!=0)
      {
      Trentino::RuntimeModel::ServiceBasePtr ptr(service);
      logInfo("Registration request issued, got reqId %d", reqid);
      std::vector<MetadataStringAttributePtr>::const_iterator it = joinedMetadata->stringAttributesElements().begin();
      for(size_t i = 0 ; i<joinedMetadata->stringAttributesElements().size(); i++)
         {
         logInfo("\t%s = %s",(*it)->name().c_str(), (*it)->value().c_str());
         it++;
         }
      ptr = service;
      mRegistrationMap[reqid] = ptr;
      mRegistrationMapMutex.unlock();
      }
   else
      {
      logError("Service registration failed! %s::%s", scaCPPInterface->clazz().c_str(), service->name().c_str());
      mRegistrationMapMutex.unlock();
      return false;
      }
   return true;

}



void Trentino::Discovery::DiscoveryActivator::discoveryTaskRegisterCallback(int reqId, bool status, std::string returnValOrStatusInfo)
{

   logInfo("Service registration result: reqID %d  status %d %s", reqId, status, returnValOrStatusInfo.data());
      if (status == true)
      {
         mRegistrationMapMutex.lock();
         if ( mRegistrationMap.count(reqId) == 1 )
         {
            mRegistrationMap[reqId]->setDiscoveryId(returnValOrStatusInfo);
            mRegistrationMap.erase(reqId);
         }
         else
         {
            logError("Unknown service registration reqId %d!", reqId);
         }
         mRegistrationMapMutex.unlock();
      }
      else
      {
         logError("Service registration failed!");
      }
}

void Trentino::Discovery::DiscoveryActivator::discoveryTaskRegisterCallbackMediator(int reqId, bool status, std::string retval)
{
   mInstance->discoveryTaskRegisterCallback(reqId, status, retval);
}

bool Trentino::Discovery::DiscoveryActivator::checkAvailability(void) {

   if (mDiscoveryInterfaceEnabled)
   {
      while(!mDiscoveryInterfaceReady);
      assert(mDiscoveryManagementInterface);
      assert(mDiscoveryInterface);
      return true;
   }
   return false;
}

bool Trentino::Discovery::DiscoveryActivator::deregisterService(
      Trentino::RuntimeModel::ServiceBasePtr svc) {

   if (!this->checkAvailability()) return false;
   mDiscoveryInterface->deregisterService(svc->discoveryId());
   return true;
}

bool Trentino::Discovery::DiscoveryActivator::deregisterServices(
      ServiceBases services) {
   if (!this->checkAvailability()) return false;

   Trentino::RuntimeModel::ServiceBases::const_iterator it;
     for(it = services.begin(); it != services.end(); ++it)
     {
        Trentino::RuntimeModel::ServiceBasePtr service = *it;
        this->deregisterService(service);
     }

     return true;

}


bool Trentino::Discovery::DiscoveryActivator::discoverServices(Trentino::RuntimeModel::ReferenceBases references)
{
   if (!this->checkAvailability()) return false;
   BOOST_FOREACH(const RuntimeModel::ReferenceBasePtr &reference, references)// Iterate over all given references
   {
      BOOST_FOREACH(const RuntimeModel::ServiceBasePtr &target, reference->getTargetServices()) // Check all referenced services
      {
           RuntimeModel::ComponentPtr component(target->component());

           if( (target->scaServiceType()->isRemote())    // In case there is remote (fake service)
                && (component->scaComponent()->implementationElement()->xsdType() !=
                      ContributionLoading::XSDTypeImplementationComposite)
              )
           {
              // Find the address property
              RuntimeModel::PropertyPtr address_property = component->findPropertyByName("_Trentino_internal_adress_property_do_not_use_this_name_");
              if (address_property) // Property is found
              {
                 if /* (strlen(address_property->values()[0].c_str())==0) // If the property value is empty */
                    ( Trentino::Binding::isFakeUri(address_property->values()[0].c_str()) )
                 {
                    //Do the job and leave
                    // Now call registration method
                    const Trentino::SCA::Model::CPPInterfacePtr scaCPPInterface
                    = boost::static_pointer_cast<Trentino::SCA::Model::CPPInterface>(target->scaServiceType()->interfaceElement());
                    findServiceEntryPtr newEntry;
                    newEntry.reset(new findServiceEntry);
                    newEntry->service=target;
                    newEntry->serviceList.reset(new listFoundServices);

                    logInfo("Calling findService: %s ", scaCPPInterface->clazz().c_str());
                    MetadataPtr md =  reference->metaData();
                    std::vector<MetadataStringAttributePtr> attrs = md->stringAttributesElements();
                    BOOST_FOREACH(const MetadataStringAttributePtr& a, attrs)
                    {
                       logInfo("%s = %s", a->name().c_str(), a->value().c_str());
                    }

                    mFindServiceMapMutex.lock();
                    int reqId = mDiscoveryInterface->findService(scaCPPInterface->clazz(), reference->metaData()/*scaReference()->metadataElement()*/, *(newEntry->serviceList.get()), DiscoveryActivator::discoveryFindServiceTaskCallbackMediator);
                    logInfo("ReqId %d", reqId);
                    mFindServicemap[reqId] = newEntry;
                    mFindServiceMapMutex.unlock();
                    break;
                 }
              }
           }
      }
   }

   return false;
}

void Trentino::Discovery::DiscoveryActivator::discoveryFindServiceTaskCallback(
      int reqID, bool status, std::string returnValOrStatusInfo)
{
         if(!status)
         {
            return;
         }

         if(mFindServicemap.count(reqID) != 1)
         {
            logError("Unknown find service request id %d!", reqID);
            return;
         }

         logInfo("FindService callback triggered for reqId %d %d %s", reqID,status, returnValOrStatusInfo.c_str());
         logInfo("services found %d", mFindServicemap[reqID]->serviceList->size());

         if (mFindServicemap[reqID]->serviceList->size()<=0) return;


         mFindServiceMapMutex.lock();

         listFoundServices::iterator it = mFindServicemap[reqID]->serviceList->begin();
         for( size_t i = 0; i< mFindServicemap[reqID]->serviceList->size(); i++)
         {
            //mFindServicemap[reqID]->serviceList.
            DiscoveryFoundService* foundSrvc = *it;
            logInfo("\tService %s", foundSrvc->getServiceUrl().c_str());
            logInfo("\tMetedata attributes: %d", foundSrvc->mMetaDatasOfService->stringAttributesElements().size());
            BOOST_FOREACH(const MetadataStringAttributePtr& metaAttr, foundSrvc->mMetaDatasOfService->stringAttributesElements())
            {
               logInfo("\t\t%s = %s", metaAttr->name().c_str(), metaAttr->value().c_str() );
            }
            it++;
         }

         RuntimeModel::ComponentPtr c(mFindServicemap[reqID]->service->component());

         RuntimeModel::ImplementationPtr impl = c->implementation();
         RuntimeModel::PropertyPtr address_property = c->findPropertyByName("_Trentino_internal_adress_property_do_not_use_this_name_");
         if(address_property.get())
            {
               Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
               Trentino::Core::ComponentImplementationManagerBasePtr componentImplementationManager = booter.componentImplementationManager();


            Trentino::Reflection::ReflectMethodPtr method = address_property->setterMethod();
            if(method.get())
               {
                  Trentino::Core::Bootstrapping::RuntimeBootstrapper& booter =Trentino::Core::Bootstrapping::RuntimeBootstrapper::instance();
                  Trentino::Binding::BindingManagerBasePtr bindingManager = booter.bindingManagerBasePtr();
                  DiscoveryFoundService* foundSrvc =mFindServicemap[reqID]->serviceList->front();  /* *it*/;

                  std::string uri = bindingManager->getServiceUri("binding.sca", *foundSrvc->mMetaDatasOfService.get());
                  const void* voidPtr =  uri.c_str();
                  //void * params[1] = {(void*)uri.c_str()};
                  void * setterParams[] = {&voidPtr};
                  void* const instance = componentImplementationManager->getInstance(mFindServicemap[reqID]->service);
                  method->invoke(instance, setterParams/*params*/);
                  componentImplementationManager->releaseInstance(instance, mFindServicemap[reqID]->service);
               }
            }

         mFindServicemap.erase(reqID);
         mFindServiceMapMutex.unlock();


}

void Trentino::Discovery::DiscoveryActivator::discoveryFindServiceTaskCallbackMediator(
      int reqID, bool status, std::string returnValOrStatusInfo) {
   mInstance->discoveryFindServiceTaskCallback(reqID, status, returnValOrStatusInfo);

}
