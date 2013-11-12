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

void ServiceInfoReaderImpl::readServiceInfo(const trentino::bindingsca::csoap::Soap& request,
                                                      Trentino::ServiceRegistry::ServiceInfo& result,
                                                      Trentino::RuntimeModel::ErrorCode& ec ) const
{

   const trentino::bindingsca::csoap::Addressing& addr = request.envelope().header().addressing();
   if(!addr.has_action()){
      ec.assign(Trentino::RuntimeModel::header_has_no_action);
   }else if(!addr.has_to()){
      ec.assign(Trentino::RuntimeModel::header_has_no_destination);
   }
   else if(!addr.has_from()){
      ec.assign(Trentino::RuntimeModel::header_has_no_sender);
      std::string desc ="header.addressing is missing field 'from'";
      ec.setDescription(desc);
   }
   if(ec.value() != 0){
      return;
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
      ec.assign(1);
      return;
   }

   std::string sep("/");
   std::size_t serviceStartPos = serviceUrl.find_last_of(sep);
   if(serviceStartPos == serviceUrl.npos){
      ec.assign(Trentino::RuntimeModel::header_has_no_destination);
      std::string desc ="header.addressing.to: invalid format. Format should be URI format with the form host/<component name>/<service name>";
      ec.setDescription(desc);
      return;
      }

   std::size_t componentNameSartPos = serviceUrl.find_last_of(sep,serviceStartPos-1);
   if(componentNameSartPos == serviceUrl.npos){
      componentNameSartPos =0;
      }
   
   std::string serviceName = serviceUrl.substr(serviceStartPos+1);
   std::string componentName = serviceUrl.substr(componentNameSartPos==0?0:componentNameSartPos+1);
   componentName = componentName.substr(0,componentName.find_last_of(sep));
   if(serviceName.length()==0 || componentName.length()==0){
      ec.assign(Trentino::RuntimeModel::header_has_no_destination);
      std::string desc ="header.addressing.to: invalid format. Format should be URI format with the form host/<component name>/<service name>";
      ec.setDescription(desc);
      return;
   }

   //get component name
 

   //get the method name from the action
   const std::string& actionUrl = addr.action();
   if(actionUrl.length() ==0){
      ec.assign(1);
      return;
   }
   std:: string actionName = getLastPartsOfUrl(actionUrl);
   if(actionName.length()==0){
      ec.assign(Trentino::RuntimeModel::header_has_no_action);
      std::string desc ="header.addressing.action: invalid format. Format should be URI format";
      ec.setDescription(desc);
      return;
   }

   const std::string& clientUrl = addr.from();
   if(clientUrl.length()==0){
      ec.assign(Trentino::RuntimeModel::header_has_no_sender);
      return;
   }



   //initialise the result
   result.setServiceName(serviceName);
   result.setComponentName(componentName);
   result.properties()->put(Constants::mAction, actionName);
   result.properties()->put(Constants::mClient, clientUrl);

   //if reply to is present the read
   if(addr.has_replyto() && addr.replyto().has_address()){
      result.properties()->put(Constants::mReplyTo, addr.replyto().address());
   }

}

ServiceInfoReaderImpl::ServiceInfoReaderImpl()
{

}

ServiceInfoReaderImpl::~ServiceInfoReaderImpl()
{

}
