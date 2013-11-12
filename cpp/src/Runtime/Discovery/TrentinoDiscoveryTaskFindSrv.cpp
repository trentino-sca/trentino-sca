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
#include "TrentinoDiscoveryTaskFindSrv.h"

//specific
#include "TrentinoDiscoveryMethodInterface.h"
#include "../../Utils/TrentinoUtilsLogging.h"
#include "TrentinoDiscoveryFoundService.h"

using namespace Trentino::Discovery;

DiscoveryTaskFindSrv::DiscoveryTaskFindSrv( discoveryFrameWorkCBFuncPtr funcPtr, 
   int retryCount,
   int retryInterval,
   DiscoveryMethodInterface* methodInterface,
   std::string serviceIdentifier, 
   ConstMetadataConstSharedPtr serviceAttributes, 
   runtimefindSrvCB runtimeCB,
   //listFoundServicesPtr foundServicesPtr)
   //listFoundServices& foundServices)
   //son listFoundServices* foundServices2)
   listFoundServices* rawServicesList)
   :DiscoveryTask(funcPtr, retryCount, retryInterval, methodInterface),
   mServiceIdentifier(serviceIdentifier),
   mFilterAttributes(serviceAttributes),
   mRuntimeCB(runtimeCB),
   mRawFoundServicesList(rawServicesList)
{
      mTaskID = createID();
}

DiscoveryTaskFindSrv::~DiscoveryTaskFindSrv()
{
}

bool DiscoveryTaskFindSrv::execute()
{
   mDiscoveryMethodInterface->findSrv(mTaskPtr);
   if(mStatus)
   {
      logInfo(mReturnValue.c_str());
      mRuntimeCB(getID(), mStatus, mReturnValue);
      return true;
   }
   else
   {
      logError(mReturnValue.c_str());
      return false;
   }
}

ConstMetadataConstSharedPtr DiscoveryTaskFindSrv::getFilterAttributes()
{
   return mFilterAttributes;
}

void DiscoveryTaskFindSrv::onTaskCancelled()
{
   mRuntimeCB(getID(), mStatus, mReturnValue);
}

void DiscoveryTaskFindSrv::onNewServiceFound(boost::shared_ptr<DiscoveryFoundService> foundService)
{
   //mFoundServices.push_back(foundService);
   //mFoundServicesPtr->push_back(foundService);
   //mFoundServices->push_back(foundService);
}

void DiscoveryTaskFindSrv::onNewServiceFound(std::string serviceUrl, MetadataSharedPtr mandatoryAttributes)
{
   boost::shared_ptr<DiscoveryFoundService> foundService(new DiscoveryFoundService(serviceUrl, mandatoryAttributes));
   //mFoundServices.push_back(foundService);
}

void DiscoveryTaskFindSrv::onNewServiceFound(std::string serviceUrl, Trentino::SCA::Model::Metadata& mandatoryAttributes)
{
   mandatoryAttributes;
   serviceUrl;
   //boost::shared_ptr<DiscoveryFoundService> foundService(new DiscoveryFoundService(serviceUrl, mandatoryAttributes));
   DiscoveryFoundService* foundService = new DiscoveryFoundService(serviceUrl, mandatoryAttributes);
   mRawFoundServicesList->push_back(foundService);
   // mFoundServices.push_back(foundService);
}
