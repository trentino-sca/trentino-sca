// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************

//header
#include "TrentinoBindingSCAServiceInfoReader.h"

//specific
#include "../Runtime/ServiceRegistry/TrentinoServiceRegistryServiceInfo.h"

#include "../Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h"
#include "../Runtime/Invocation/TrentinoInvocation.h"
#include "TrentinoBindingSCATrentinoBindingSCA.h"
#include "TrentinoBindingSCAConstants.h"

using namespace Trentino::RuntimeModel;
using namespace Trentino::Binding::SCA;
using namespace Trentino::ServiceRegistry;


namespace {

   //todo delete this very bad alogritm
   std::string getLastPartsOfUrl (const std::string& url, int numberOfSeparatorToSkip=1){

      std::string truncatedUrl = url;
      bool endWithBackSlash = url[url.length()-1]=='/';
      if(endWithBackSlash){
         truncatedUrl = url.substr(0,url.length()-1);
      }
      //-2 because the last char is not taken into account
      int idx = truncatedUrl.length()-2;
      //get the last index of the \ char
      //the last char is not taken into account
      while ( idx >= 0 && numberOfSeparatorToSkip >0)
      {
         if (truncatedUrl[idx] == '/'){
            numberOfSeparatorToSkip--;
            idx--;
            continue;
         }
         idx--;
      }

      if(idx <0){
         //no part found
         return truncatedUrl;
      }
      std::string res = truncatedUrl.substr(idx+2);
      return res;
   }

}

ServiceInfoPtr ServiceInfoReaderImpl::readServiceInfo(const trentino::bindingsca::csoap::Soap& request, Trentino::RuntimeModel::ErrorCode& ec ) const
{

   const trentino::bindingsca::csoap::Addressing& addr = request.envelope().header().addressing();
   if(!addr.has_action()){
      ec.assign(Trentino::RuntimeModel::header_has_no_action, boost::system::get_system_category());
   }else if(!addr.has_to()){
      ec.assign(Trentino::RuntimeModel::header_has_no_destination, boost::system::get_system_category());
   }
   else if(!addr.has_from()){
      ec.assign(Trentino::RuntimeModel::header_has_no_sender, boost::system::get_system_category());
      std::string desc ="header.addressing is missing field 'from'";
      ec.setDescription(desc);
   }
   if(ec.value() != boost::system::errc::success){
      return ServiceInfoPtr();
   }
   //get the Service name
   const std::string& serviceUrlConst = addr.to();
   std::string serviceUrl = serviceUrlConst;

   //remove trainlg slasches
   bool endWithBackSlash = serviceUrl[serviceUrl.length()-1]=='/';
   if(endWithBackSlash){
      serviceUrl = serviceUrl.substr(0,serviceUrl.length()-1);
      }

   if(serviceUrl.length()==0){
      return ServiceInfoPtr();
   }

   std::string sep("/");
   std::size_t serviceStartPos = serviceUrl.find_last_of(sep);
   if(serviceStartPos == serviceUrl.npos || serviceStartPos-1 <0){
      ec.assign(Trentino::RuntimeModel::header_has_no_destination, boost::system::get_system_category());
      std::string desc ="header.addressing.to: invalid format. Format should be URI format with the form host/<component name>/<service name>";
      ec.setDescription(desc);
      return ServiceInfoPtr();
      }

   std::size_t componentNameSartPos = serviceUrl.find_last_of(sep,serviceStartPos-1);
   if(componentNameSartPos == serviceUrl.npos){
      componentNameSartPos =0;
      }
   
   std::string serviceName = serviceUrl.substr(serviceStartPos+1);
   std::string componentName = serviceUrl.substr(componentNameSartPos==0?0:componentNameSartPos+1);
   componentName = componentName.substr(0,componentName.find_last_of(sep));
   if(serviceName.length()==0 || componentName.length()==0){
      ec.assign(Trentino::RuntimeModel::header_has_no_destination, boost::system::get_system_category());
      std::string desc ="header.addressing.to: invalid format. Format should be URI format with the form host/<component name>/<service name>";
      ec.setDescription(desc);
      return ServiceInfoPtr();
   }

   //get component name
 

   //get the method name from the action
   const std::string& actionUrl = addr.action();
   if(actionUrl.length() ==0){

      return ServiceInfoPtr();
   }
   std:: string actionName = getLastPartsOfUrl(actionUrl);
   if(actionName.length()==0){
      ec.assign(Trentino::RuntimeModel::header_has_no_action, boost::system::get_system_category());
      std::string desc ="header.addressing.action: invalid format. Format should be URI format";
      ec.setDescription(desc);
      return ServiceInfoPtr();
   }

   const std::string& clientUrl = addr.from();
   if(clientUrl.length()==0){
      ec.assign(Trentino::RuntimeModel::header_has_no_sender, boost::system::get_system_category());
      return ServiceInfoPtr();
   }



   //initialise the result
   ServiceInfoPtr result(new ServiceInfo());
   result->setServiceName(serviceName);
   result->setComponentName(componentName);
   result->properties()->put(Constants::mAction, actionName);
   result->properties()->put(Constants::mClient, clientUrl);

   //if reply to is present the read
   if(addr.has_replyto() && addr.replyto().has_address()){
      result->properties()->put(Constants::mReplyTo, addr.replyto().address());
   }
   return result;

}

ServiceInfoReaderImpl::ServiceInfoReaderImpl()
{

}

ServiceInfoReaderImpl::~ServiceInfoReaderImpl()
{

}
