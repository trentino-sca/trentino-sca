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
#include "TrentinoBindingSCADataHandler.h"

//standard
#include <boost/shared_ptr.hpp>


//Logging
#include "../Utils/TrentinoUtilsLogging.h"

//specific

//SCA Binding specific
#include "TrentinoBindingSCAFaultDetailBuilder.h"
#include "TrentinoBindingSCASCABindingHelper.h"
#include "TrentinoBindingSCAContext.h"

//runtime specific
#include "../Runtime/RuntimeModel/TrentinoRuntimeModelService.h"
#include "../Runtime/RuntimeModel/TrentinoRuntimeModel.h"
#include "../Runtime/Invocation/TrentinoInvocationInvocationData.h"
#include "../Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h"

#include "../Runtime/Invocation/TrentinoInvocationInvocationContext.h"
#include "../Runtime/ServiceRegistry/TrentinoServiceRegistryServiceRegistryBase.h"
#include "../Runtime/ServiceRegistry/TrentinoServiceRegistryServiceInfo.h"
#include "TrentinoBindingSCAConstants.h"

using namespace Trentino::Binding::SCA;
using namespace Trentino::RuntimeModel;
using namespace Trentino::Invocation;
using namespace Trentino::ServiceRegistry;
namespace CSOAP = trentino::bindingsca::csoap;
using namespace CSOAP;
using namespace  boost::system;

namespace {
   void checkRequest(const SoapPtr& request, Trentino::RuntimeModel::ErrorCode& ec){
      if(!request){
         ec.assign(errc::bad_message,system_category());
         std::string desc ("request is empty");
         ec.setDescription(desc);
         return;
         }
      if(!request->has_envelope()){
         ec.assign(errc::bad_message,system_category());
         std::string desc ("message has no envelope");
         ec.setDescription(desc);
         return;
         }
      const trentino::bindingsca::csoap::Soap_Envelope env = request->envelope();
      if(!env.has_header()){
         ec.assign(errc::bad_message,system_category());
         std::string desc ("message has no header");
         ec.setDescription(desc);
         return;
         }
      }
   }

void DataHandler::dataToResponse(const SoapPtr& request, SoapPtr& response ,  ErrorCode& ec ) const
   {
   //init to success
    ec.assign(boost::system::errc::success,boost::system::system_category());
    checkRequest(request, ec);
   if(!ec.isSuccess()){
      //reset to success
      ec.assign(boost::system::errc::success,boost::system::system_category());
      //Error during conversion, then we generate an error message but set our error code to success
      const Soap_faultcodeEnum errorCode = Soap_faultcodeEnum_DataEncodingUnknown;

      const DefaultFaultDetailBuilderPtr detailBuilder(new DefaultFaultDetailBuilder("",C_400_BAD_REQUEST,"Message has no valid protocol buffer format"));
      buildErrorResponse (response, errorCode,ec, detailBuilder);
      //if another error occurs, it is handled by the caller of this method
      logError("Incoming message has no valid protocol buffer format");
      return;
      }

   //we can read the message

   //1. read the informations about been called
   //This will parse the Request header to search for service location parameters
   const ServiceInfoPtr& serviceInfo = mDeps->serviceInfoReader()->readServiceInfo(*request.get(), ec);
   if(!ec.isSuccess() || !serviceInfo){
      handleServiceInfoCannotBeUnderstood(ec, response);
      //if another error occurs, it is handled by the caller
      logError("Cannot parse header of incoming message");
      return;
      }

   //Service info were found continue

   //2. search for the service in the registry
   //Here we use a wrapper around the service registry to be able to make wide range of tests without the service registry itself

   if(!mSCAContext->serviceRegistry()){
      ec.assign(service_registry_not_available, boost::system::get_system_category());
      const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_Receiver;
      //but again we should be able to provide more details about the error
      const DefaultFaultDetailBuilderPtr detailBuilder (new DefaultFaultDetailBuilder("",C_500_INTERNAL_SERVER_ERROR,"Service Registry not instantiated"));
      buildErrorResponse(response,errorCode,ec,detailBuilder);
      logError("Service Registry not available");
      return;
      }

   const ServiceBasePtr& runtimeServicePtr = mSCAContext->serviceRegistry()->findService(serviceInfo,ec);
   if(!ec.isSuccess()  || !runtimeServicePtr){
      handleServiceNotFound(ec, response);
      //if another error occurs, it is handled by the caller
      logError("No corresponding service found for Incoming message");
      return;
      }

   //Service is found, we continue

   //checkt that the service is active
   const bool serviceIsActive = isServiceActive(runtimeServicePtr,ec);

   if(!ec.isSuccess() || !serviceIsActive){
      //cannot check if the service is active, or the service is not active, we do the same as if the service was not found in the registry
      handleServiceNotFound(ec, response);
      //if another error occurs, it is handled by the caller
      logError("Service found but Not active for Incoming message");
      return;
      }

   BindingHelperBasePtr BindingHelperBasePtr = runtimeServicePtr->bindingHelperByBindingId(mDeps->bindingId());
   if(!BindingHelperBasePtr){
      handleBindingHelperNotFound(ec,response);
      logError("Service found but current binding cannot handle request: no BindingHelper Found");
      return;
      }

   SCABindingHelperBasePtr scaBindingHelperBasePtr = boost::dynamic_pointer_cast<SCABindingHelper>(BindingHelperBasePtr);

   if(!scaBindingHelperBasePtr){
      handleBindingHelperNotFound(ec,response);
      logError("Service found but current binding cannot handle request: no BindingHelper Found");
      return;
      }


   //Now create the invocation data

   InvocationDataPtr invocationDataPtr(new InvocationData());
   //set the action and target service
   invocationDataPtr->setOperation(serviceInfo->properties()->get(Constants::mAction));
   invocationDataPtr->setTargetService(runtimeServicePtr);

   //set parameters
   scaBindingHelperBasePtr->deserializeRequest(invocationDataPtr, *request.get(), ec);
   //handle invocation data creation result
   if(!ec.isSuccess() || !invocationDataPtr){
      //we could not create invocation data
      //either we cannot understand the data, or we have an internal error, ec error code helps here to make the difference
      const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_MustUnderstand;

      //reset the error to success and hanlde it
      ec.assign(boost::system::errc::success,boost::system::system_category());
      const DefaultFaultDetailBuilderPtr detailBuilder(new DefaultFaultDetailBuilder("",C_400_BAD_REQUEST,"Cannot create invocation data.\n"+ec.description()));
      buildErrorResponse(response,errorCode,ec,detailBuilder);
      //if another error occurs, it is handled by the caller
      logError("Cannot create invocation data");
      return;
      }


   //invocation data are available
   //now we create an invocation context
   InvocationContextPtr _invocationContextPtr = createInvocationContextPtr(serviceInfo, ec);
   InvocationContextPtr& invocationContextPtr = _invocationContextPtr;

   invokeAndPrepareResponse(invocationDataPtr,invocationContextPtr,scaBindingHelperBasePtr,response,ec);

   }


void DataHandler::invokeAndPrepareResponse(Trentino::Invocation::InvocationDataPtr& invocationDataPtr,
   Trentino::Invocation::InvocationContextPtr& invocationContextPtr ,
   const  SCABindingHelperBasePtr& scaBindingHelperBasePtr, 
   SoapPtr& response, 
   ErrorCode& ec) const
   {

   //Now invoke the service
   //todo: One way calls is not implemented yet. In case of one  way call, this method should return at this
   // point and let the Invoker proxy perform invocation later
   if(scaBindingHelperBasePtr->isOneWay(invocationDataPtr)){
      mDeps->invokerProxy()->invokeLater(invocationDataPtr, invocationContextPtr, ec);
      ec.assign(invocation_delayed, boost::system::system_category());
      std::string desc ="Invocation delayed";
      ec.setDescription(desc);
      return;
      }
   //Invocation is not depayed, call direcly
   mDeps->invokerProxy()->invoke(invocationDataPtr, invocationContextPtr, ec);

   //check if error occurred during invocation, the invocation proxy handles exceptions generated during invocation
   if(!ec.isSuccess()){
      //error during invocation, the error code give enough information about the error so that we can build a meanings full message
      FaultDetailBuilderPtr detailBuilder = scaBindingHelperBasePtr->getFaultBuilder();
      if(!detailBuilder){
         DefaultFaultDetailBuilder * builder= new DefaultFaultDetailBuilder("",C_500_INTERNAL_SERVER_ERROR,"Unexpected error occured.\n"+ec.description());
         detailBuilder.reset(builder);
         }
      const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_MustUnderstand;
      buildErrorResponse(response,errorCode,ec,detailBuilder);
      logError("Error during invocation. Exception is reported to client");
      return;
      }

   //Invocation ok.
   scaBindingHelperBasePtr->serializeResponse(invocationDataPtr,*response.get(), ec);
   if(!ec.isSuccess()){
      //error during invocation, cannot serialize response
      //Service not found, service is not available, create the corresponding response
      const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_Receiver;

      //but again we should be able to provide more details about the error
      const DefaultFaultDetailBuilderPtr detailBuilder (new DefaultFaultDetailBuilder("",C_500_INTERNAL_SERVER_ERROR,"Cannot serialize soap response"));
      buildErrorResponse(response,errorCode,ec,detailBuilder);
      //reset the error to success
      ec.assign(boost::system::errc::success,boost::system::system_category());
      logError("Error after invocation. Cannot serialize soap response");
      return;
      }
   }


void DataHandler::handleServiceNotFound( ErrorCode &ec, SoapPtr& response )
   {

   //Service not found, service is not available, create the corresponding response
   const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_Receiver;

   //but again we should be able to provide more details about the error
   const DefaultFaultDetailBuilderPtr detailBuilder (new DefaultFaultDetailBuilder("",C_404_NOT_FOUND,"No corresponding service found or Service is not active"));
   buildErrorResponse(response,errorCode,ec,detailBuilder);
   //reset the error to success
   ec.assign(boost::system::errc::success,boost::system::system_category());
   }

void DataHandler::handleBindingHelperNotFound( ErrorCode &ec, SoapPtr& response ){
   const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_Receiver;
   //but again we should be able to provide more details about the error
   const DefaultFaultDetailBuilderPtr detailBuilder (new DefaultFaultDetailBuilder("",C_501_NOT_IMPLEMENTED,"Service found but Binding not implemented"));
   buildErrorResponse(response,errorCode,ec,detailBuilder);
   //reset the error to success
   ec.assign(boost::system::errc::success,boost::system::system_category());
   }

void DataHandler::handleServiceInfoCannotBeUnderstood( ErrorCode &ec, SoapPtr& response )
   {
   //error when parsing service info. This should never happens
   //We cannot read the header of the Soap message normally, so we cannot understand this message
   const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_MustUnderstand;
   const DefaultFaultDetailBuilderPtr detailBuilder(new DefaultFaultDetailBuilder("",C_400_BAD_REQUEST,"Cannot understand header. Cannot derive service metadata"));
   buildErrorResponse(response,errorCode,ec,detailBuilder);
   }


void DataHandler::buildErrorResponse( SoapPtr& response, const trentino::bindingsca::csoap::Soap_faultcodeEnum &fCode 
   ,ErrorCode& ec, const FaultDetailBuilderPtr& faultDetailBuilder)
   {
   trentino::bindingsca::csoap::Soap_Envelope* envelope =response->mutable_envelope();
   trentino::bindingsca::csoap::Soap_Body* body =envelope->mutable_body();
   trentino::bindingsca::csoap::Soap_Fault* faultMsg =body->mutable_faultmessage();
   trentino::bindingsca::csoap::Soap_faultcode* faultCode =faultMsg->mutable_code();
   faultCode->set_value(fCode);
   trentino::bindingsca::csoap::Soap_subcode* subcode = faultCode->mutable_subcode();
   std::string subCode = faultDetailBuilder->createSubCode(ec);
   subcode->set_value(subCode.data());
   trentino::bindingsca::csoap::Soap_faultreason* reason =faultMsg->mutable_reason();
   std::string reasonChar = faultDetailBuilder->createReason(ec);
   reason->add_text(reasonChar.data());
   reason->add_text(ec.description());
   std::string detail = faultDetailBuilder->createDetail(ec);
   faultMsg->set_detail(detail.data());
   ec.assign(boost::system::errc::success,boost::system::system_category());
   }



Trentino::Invocation::InvocationContextPtr DataHandler::createInvocationContextPtr
   ( const Trentino::ServiceRegistry::ServiceInfoPtr& serviceInfo, ErrorCode& /*ec*/ ) const
 {
   InvocationContextPtr result( new InvocationContext());
   result->setServiceInfo(serviceInfo);
   return result;
 }


DataHandler::DataHandler()
   {

   }

const bool DataHandler::isServiceActive( const ConstServiceBasePtr& runtimeServicePtr, 
   ErrorCode& /*ec*/ )
   {
   return runtimeServicePtr &&(runtimeServicePtr->state() == ServiceBase::Available);
}





void Trentino::Binding::SCA::DataHandler::handle( const SoapPtr& request, SoapPtr& response ) const
   {
    ErrorCode ec;
    dataToResponse(request, response, ec);
   }
