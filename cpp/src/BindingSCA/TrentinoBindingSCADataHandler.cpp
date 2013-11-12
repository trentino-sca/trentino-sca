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
   void checkRequest(const trentino::bindingsca::csoap::Soap& request, Trentino::RuntimeModel::ErrorCode& ec){
      if(!request.has_envelope()){
         ec.assign(errc::bad_message);
         std::string desc ("message has no envelope");
         ec.setDescription(desc);
         return;
         }
      const trentino::bindingsca::csoap::Soap_Envelope env = request.envelope();
      if(!env.has_header()){
         ec.assign(errc::bad_message);
         std::string desc ("message has no header");
         ec.setDescription(desc);
         return;
         }
      }

   void buildErrorResponseImpl( trentino::bindingsca::csoap::Soap& response, const trentino::bindingsca::csoap::Soap_faultcodeEnum &fCode 
      ,ErrorCode& ec, const FaultDetailBuilderPtr& faultDetailBuilder)
      {
      trentino::bindingsca::csoap::Soap_Envelope* envelope =response.mutable_envelope();
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
      ec.assign(boost::system::errc::success);
      }

   void invokeAndPrepareResponseImpl(void* handler, 
      Trentino::Invocation::InvocationData& invocationDataPtr,
      const Trentino::RuntimeModel::ServiceBasePtr& targetService,
      void* retVal,
      Trentino::Invocation::InvocationContext& invocationContextPtr ,
      const  SCABindingHelper* scaBindingHelperBasePtr, 
      trentino::bindingsca::csoap::Soap& response, 
      Trentino::RuntimeModel::ErrorCode& ec){

         DataHandler* dataHandler = static_cast<DataHandler*>(handler);
         //Now invoke the service
         //todo: One way calls is not implemented yet. In case of one  way call, this method should return at this
         // point and let the Invoker proxy perform invocation later
         if(scaBindingHelperBasePtr->isOneWay(invocationDataPtr)){
            dataHandler->dependencies()->invokerProxy()->invokeLater(invocationDataPtr,targetService,retVal, invocationContextPtr, ec);
            ec.assign(invocation_delayed);
            std::string desc ="Invocation delayed";
            ec.setDescription(desc);
            return;
            }
         //Invocation is not depayed, call direcly
         dataHandler->dependencies()->invokerProxy()->invoke(invocationDataPtr,targetService,retVal, invocationContextPtr, ec);

         //check if error occurred during invocation, the invocation proxy handles exceptions generated during invocation
         if(!ec.isSuccess()){
            //error during invocation, the error code give enough information about the error so that we can build a meanings full message
            FaultDetailBuilderPtr detailBuilder = scaBindingHelperBasePtr->getFaultBuilder();
            if(!detailBuilder){
               DefaultFaultDetailBuilder * builder= new DefaultFaultDetailBuilder("",C_500_INTERNAL_SERVER_ERROR,"Unexpected error occured.\n"+ec.description());
               detailBuilder.reset(builder);
               }
            const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_MustUnderstand;
            buildErrorResponseImpl(response,errorCode,ec,detailBuilder);
            logError("Error during invocation. Exception is reported to client");
            return;
            }

         //Invocation ok.
         scaBindingHelperBasePtr->serializeResponse(invocationDataPtr,retVal,response, ec);
         if(!ec.isSuccess()){
            //error during invocation, cannot serialize response
            //Service not found, service is not available, create the corresponding response
            const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_Receiver;

            //but again we should be able to provide more details about the error
            const DefaultFaultDetailBuilderPtr detailBuilder (new DefaultFaultDetailBuilder("",C_500_INTERNAL_SERVER_ERROR,"Cannot serialize soap response"));
            buildErrorResponseImpl(response,errorCode,ec,detailBuilder);
            //reset the error to success
            ec.assign(boost::system::errc::success);
            logError("Error after invocation. Cannot serialize soap response");
            return;
            }
      }
   }

void DataHandler::dataToResponse(const trentino::bindingsca::csoap::Soap& request, trentino::bindingsca::csoap::Soap& response ,  ErrorCode& ec ) const
   {
   //init to success
   ec.assign(boost::system::errc::success);
   checkRequest(request, ec);
   if(!ec.isSuccess()){
      //reset to success
      ec.assign(boost::system::errc::success);
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

   ServiceInfo serviceInfo;
   mDeps->serviceInfoReader()->readServiceInfo(request, serviceInfo, ec);
   if(!ec.isSuccess()){
      handleServiceInfoCannotBeUnderstood(ec, response);
      //if another error occurs, it is handled by the caller
      logError("Cannot parse header of incoming message");
      return;
      }

   //Service info were found continue

   //2. search for the service in the registry
   //Here we use a wrapper around the service registry to be able to make wide range of tests without the service registry itself

   if(!mSCAContext->serviceRegistry()){
      ec.assign(service_registry_not_available);
      const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_Receiver;
      //but again we should be able to provide more details about the error
      const DefaultFaultDetailBuilderPtr detailBuilder (new DefaultFaultDetailBuilder("",C_500_INTERNAL_SERVER_ERROR,"Service Registry not instantiated"));
      buildErrorResponse(response,errorCode,ec,detailBuilder);
      logError("Service Registry not available");
      return;
      }

   const ServiceBasePtr& runtimeServicePtr = mSCAContext->serviceRegistry()->findService(serviceInfo);
   if(!runtimeServicePtr){
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

   InvocationData invocationDataPtr;
   //set the action and target service
   invocationDataPtr.setOperation(serviceInfo.properties()->get(Constants::mAction));
   invocationDataPtr.setTargetService(serviceInfo.serviceName());
   invocationDataPtr.setTargetComponent(serviceInfo.componentName());

   //invocation data are available
   //now we create an invocation context

   InvocationContext invocationContextPtr;

   //invoke
   scaBindingHelperBasePtr->invoke(invokeAndPrepareResponseImpl,(void*)this, invocationDataPtr,runtimeServicePtr,invocationContextPtr,
      *const_cast<trentino::bindingsca::csoap::Soap*>(&request), response, ec);

   }


void DataHandler::invokeAndPrepareResponse(Trentino::Invocation::InvocationData& invocationDataPtr,
                                           const Trentino::RuntimeModel::ServiceBasePtr& targetService,
                                           void* retVal,
                                           Trentino::Invocation::InvocationContext& invocationContextPtr ,
                                           const  SCABindingHelperBasePtr& scaBindingHelperBasePtr, 
                                           trentino::bindingsca::csoap::Soap& response, 
                                           ErrorCode& ec) const
   {
   invokeAndPrepareResponseImpl((void*)this,invocationDataPtr,targetService, retVal,invocationContextPtr,scaBindingHelperBasePtr.get(),response,ec);
   }


void DataHandler::handleServiceNotFound( ErrorCode &ec, trentino::bindingsca::csoap::Soap& response )
   {

   //Service not found, service is not available, create the corresponding response
   const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_Receiver;

   //but again we should be able to provide more details about the error
   const DefaultFaultDetailBuilderPtr detailBuilder (new DefaultFaultDetailBuilder("",C_404_NOT_FOUND,"No corresponding service found or Service is not active"));
   buildErrorResponse(response,errorCode,ec,detailBuilder);
   //reset the error to success
   ec.assign(boost::system::errc::success);
   }

void DataHandler::handleBindingHelperNotFound( ErrorCode &ec, trentino::bindingsca::csoap::Soap& response ){
   const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_Receiver;
   //but again we should be able to provide more details about the error
   const DefaultFaultDetailBuilderPtr detailBuilder (new DefaultFaultDetailBuilder("",C_501_NOT_IMPLEMENTED,"Service found but Binding not implemented"));
   buildErrorResponse(response,errorCode,ec,detailBuilder);
   //reset the error to success
   ec.assign(boost::system::errc::success);
   }

void DataHandler::handleServiceInfoCannotBeUnderstood( ErrorCode &ec, trentino::bindingsca::csoap::Soap& response )
   {
   //error when parsing service info. This should never happens
   //We cannot read the header of the Soap message normally, so we cannot understand this message
   const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_MustUnderstand;
   const DefaultFaultDetailBuilderPtr detailBuilder(new DefaultFaultDetailBuilder("",C_400_BAD_REQUEST,"Cannot understand header. Cannot derive service metadata"));
   buildErrorResponse(response,errorCode,ec,detailBuilder);
   }


void DataHandler::buildErrorResponse( trentino::bindingsca::csoap::Soap& response, const trentino::bindingsca::csoap::Soap_faultcodeEnum &fCode 
                                     ,ErrorCode& ec, const FaultDetailBuilderPtr& faultDetailBuilder)
   {
   buildErrorResponseImpl(response,fCode,ec,faultDetailBuilder);
   }


DataHandler::DataHandler()
   {

   }

const bool DataHandler::isServiceActive( const ConstServiceBasePtr& runtimeServicePtr, 
                                        ErrorCode& /*ec*/ )
   {
   return runtimeServicePtr &&(runtimeServicePtr->state() == ServiceBase::Available);
   }





void Trentino::Binding::SCA::DataHandler::handle( const Soap& request, Soap& response ) const
   {
   ErrorCode ec;
   dataToResponse(request, response, ec);
   }
