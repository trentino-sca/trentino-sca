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
#include "TrentinoBindingIpcDataHandler.h"

//standard
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>


//Logging
#include "../Utils/TrentinoUtilsLogging.h"

//specific

//Ipc Binding specific
#include "TrentinoBindingIpcFaultDetailBuilder.h"
#include "TrentinoBindingIpcBindingHelper.h"
#include "TrentinoBindingIpcFaultDetailBuilder.h"


//runtime specific
#include "../Runtime/RuntimeModel/TrentinoRuntimeModelService.h"
#include "../Runtime/RuntimeModel/TrentinoRuntimeModel.h"
#include "../Runtime/Invocation/TrentinoInvocationInvocationData.h"


#include "../Runtime/Invocation/TrentinoInvocationInvocationContext.h"
#include "../Runtime/ServiceRegistry/TrentinoServiceRegistryServiceRegistryBase.h"
#include "../Runtime/ServiceRegistry/TrentinoServiceRegistryServiceInfo.h"

using namespace Trentino::Binding::IPC;
using namespace Trentino::RuntimeModel;
using namespace Trentino::Invocation;
using namespace Trentino::ServiceRegistry;
using namespace  boost::system;


   //void checkRequest(const SoapMsgPtr& request, Trentino::RuntimeModel::ErrorCode& ec)
   //{
   //   //if(!request)
   //   //{
   //   //   ec.assign(errc::bad_message,system_category());
   //   //   std::string desc ("request is empty");
   //   //   ec.setDescription(desc);
   //   //   return;
   //   //   
   //   //}
   //   //if(!request->has_envelope()){
   //   //   ec.assign(errc::bad_message,system_category());
   //   //   std::string desc ("message has no envelope");
   //   //   ec.setDescription(desc);
   //   //   return;
   //   //   }
   //   //const trentino::bindingsca::csoap::Soap_Envelope env = request->envelope();
   //   //if(!env.has_header()){
   //   //   ec.assign(errc::bad_message,system_category());
   //   //   std::string desc ("message has no header");
   //   //   ec.setDescription(desc);
   //   //   return;
   //   //   }
   //   //}
   //}
namespace
{
   void invokeAndPrepareResponseImpl(void* handler, 
      Trentino::Invocation::InvocationData& invocationData,
      void* retVal,
      Trentino::Invocation::InvocationContext& invocationContextPtr, 
      const  BindingHelperIpc* ipcBindingHelperBasePtr, 
      /*trentino::bindingsca::csoap::Soap& response, */
      Trentino::Binding::IPC::IpcSoapMsg& response,
      Trentino::RuntimeModel::ErrorCode& ec)
   {
      response;
         DataHandlerIpc* dataHandler = static_cast<DataHandlerIpc*>(handler);
         //Now invoke the service
         //todo: One way calls is not implemented yet. In case of one  way call, this method should return at this
         // point and let the Invoker proxy perform invocation later
         if(ipcBindingHelperBasePtr->isOneWay(invocationData))
         {
            dataHandler->invokerProxy()->invokeLater(invocationData, retVal, invocationContextPtr, ec);
            ec.assign(invocation_delayed);
            std::string desc ="Invocation delayed";
            ec.setDescription(desc);
            return;
         }
         //Invocation is not depayed, call direcly
         dataHandler->invokerProxy()->invoke(invocationData, retVal, invocationContextPtr, ec);

         //check if error occurred during invocation, the invocation proxy handles exceptions generated during invocation
         if(!ec.isSuccess())
         {
            ////error during invocation, the error code give enough information about the error so that we can build a meanings full message
            //FaultDetailBuilderPtr detailBuilder = scaBindingHelperBasePtr->getFaultBuilder();
            //if(!detailBuilder){
            //   DefaultFaultDetailBuilder * builder= new DefaultFaultDetailBuilder("",C_500_INTERNAL_SERVER_ERROR,"Unexpected error occured.\n"+ec.description());
            //   detailBuilder.reset(builder);
            //}
            //const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_MustUnderstand;
            //buildErrorResponseImpl(response,errorCode,ec,detailBuilder);
            //logError("Error during invocation. Exception is reported to client");
            //return;
         }

         //Invocation ok.
         //TODO
         ipcBindingHelperBasePtr->serializeResponse(invocationData,retVal,response, ec, dataHandler->mManaged_shm);
         if(!ec.isSuccess())
         {
            ////error during invocation, cannot serialize response
            ////Service not found, service is not available, create the corresponding response
            //const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_Receiver;

            ////but again we should be able to provide more details about the error
            //const DefaultFaultDetailBuilderPtr detailBuilder (new DefaultFaultDetailBuilder("",C_500_INTERNAL_SERVER_ERROR,"Cannot serialize soap response"));
            //buildErrorResponseImpl(response,errorCode,ec,detailBuilder);
            ////reset the error to success
            //ec.assign(boost::system::errc::success);
            //logError("Error after invocation. Cannot serialize soap response");
            //return;
         }
   }

}
Trentino::Binding::IPC::DataHandlerIpc::DataHandlerIpc()
{

}
DataHandlerIpc::~DataHandlerIpc()
{

}

void DataHandlerIpc::dataToResponse(const IpcSoapMsg& request, 
   IpcSoapMsg& response, 
   Trentino::RuntimeModel::ErrorCode& ec) const
{
   ec.assign(boost::system::errc::success);
   //we can read the message

   //1. read the informations about been called
   //This will parse the Request header to search for service location parameters
   ServiceInfo serviceInfo;
   mServiceInfoReader->readServiceInfo(request,serviceInfo, ec);
   if(!ec.isSuccess())
   {
      handleServiceInfoCannotBeUnderstood(ec, response);
      //if another error occurs, it is handled by the caller
      logError("Cannot parse header of incoming message");
      return;
   }

   //Service info were found continue

   //2. search for the service in the registry
   //Here we use a wrapper around the service registry to be able to make wide range of tests without the service registry itself

   if(!mIpcContext->serviceRegistry())
   {
      logError("Service Registry not available");
      return;
   }


    const ServiceBasePtr& runtimeServicePtr = mIpcContext->serviceRegistry()->findService(serviceInfo);

   if(!ec.isSuccess()  || !runtimeServicePtr)
   {
      handleServiceNotFound(ec, response);
      //if another error occurs, it is handled by the caller
      logError("No corresponding service found for Incoming message");
      return;
   }

   //Service is found, we continue

   //checkt that the service is active
   const bool serviceIsActive = isServiceActive(runtimeServicePtr, ec);

   if(!ec.isSuccess() || !serviceIsActive)
   {
      //cannot check if the service is active, or the service is not active, we do the same as if the service was not found in the registry
      handleServiceNotFound(ec, response);
      //if another error occurs, it is handled by the caller
      logError("Service found but Not active for Incoming message");
      return;
   }

   BindingHelperBasePtr bindingHelperBasePtr = runtimeServicePtr->bindingHelperByBindingId(mBindingId);

   if(!bindingHelperBasePtr)
   {
      handleBindingHelperNotFound(ec, response);
      logError("Service found but current binding cannot handle request: no BindingHelper Found");
      return;
   }

   BindingHelperIpcPtr bindingHelperIpcPtr = boost::dynamic_pointer_cast<BindingHelperIpc>(bindingHelperBasePtr);

   if(!bindingHelperIpcPtr)
   {
      handleBindingHelperNotFound(ec, response);
      logError("Service found but current binding cannot handle request: no BindingHelper Found");
      return;
   }

   //Now create the invocation data
   InvocationData invocationData;
   //set the action and target service
   invocationData.setOperation(serviceInfo.properties()->get(ACTION_STR));
   invocationData.setTargetService(serviceInfo.serviceName());

   //invocation data are available
   //now we create an invocation context
   InvocationContext invocationContext;
   //invocationContext.setServiceInfo(serviceInfo);

   bindingHelperIpcPtr->invoke(invokeAndPrepareResponseImpl,(void*)this, invocationData, invocationContext, *const_cast<IpcSoapMsg*>(&request), response, ec, mManaged_shm);

}

void DataHandlerIpc::handleServiceNotFound( ErrorCode &ec, IpcSoapMsg& response)
{

   //Service not found, service is not available, create the corresponding response
   //const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_Receiver;

   //but again we should be able to provide more details about the error
   const DefaultFaultDetailBuilderPtr detailBuilder (new DefaultFaultDetailBuilder("", C_404_NOT_FOUND, "No corresponding service found or Service is not active"));
   buildErrorResponse(response, ec, detailBuilder);
   //reset the error to success
   ec.assign(boost::system::errc::success);
}
//
void DataHandlerIpc::handleBindingHelperNotFound(ErrorCode &ec, IpcSoapMsg& response)
{
   //const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_Receiver;
   //but again we should be able to provide more details about the error
   const DefaultFaultDetailBuilderPtr detailBuilder (new DefaultFaultDetailBuilder("", C_501_NOT_IMPLEMENTED, "Service found but Binding not implemented"));
   buildErrorResponse(response, ec, detailBuilder);
   //reset the error to success
   ec.assign(boost::system::errc::success);
}
//
void DataHandlerIpc::handleServiceInfoCannotBeUnderstood( ErrorCode &ec, IpcSoapMsg& response )
{
   //error when parsing service info. This should never happens
   //We cannot read the header of the Soap message normally, so we cannot understand this message
   //const trentino::bindingsca::csoap::Soap_faultcodeEnum errorCode = trentino::bindingsca::csoap::Soap_faultcodeEnum_MustUnderstand;
   const DefaultFaultDetailBuilderPtr detailBuilder(new DefaultFaultDetailBuilder("", C_400_BAD_REQUEST, "Cannot understand header. Cannot derive service metadata"));
   buildErrorResponse(response, ec, detailBuilder);
}

void DataHandlerIpc::buildErrorResponse( IpcSoapMsg& response,
   ErrorCode& ec,
   const FaultDetailBuilderPtr& faultDetailBuilder)
{
   response;
   ec;
   faultDetailBuilder;
   //trentino::bindingsca::csoap::Soap_Envelope* envelope =response.envelope_mutable();
   //trentino::bindingsca::csoap::Soap_Body* body =envelope->mutable_body();
   //trentino::bindingsca::csoap::Soap_Fault* faultMsg =body->mutable_faultmessage();
   //trentino::bindingsca::csoap::Soap_faultcode* faultCode =faultMsg->mutable_code();
   //response.faultCode->set_value(fCode);
   //trentino::bindingsca::csoap::Soap_subcode* subcode = faultCode->mutable_subcode();
   //std::string subCode = faultDetailBuilder->createSubCode(ec);
   //subcode->set_value(subCode.data());
   //trentino::bindingsca::csoap::Soap_faultreason* reason =faultMsg->mutable_reason();
   //std::string reasonChar = faultDetailBuilder->createReason(ec);
   //reason->add_text(reasonChar.data());
   //reason->add_text(ec.description());
   //std::string detail = faultDetailBuilder->createDetail(ec);
   //faultMsg->set_detail(detail.data());
   //ec.assign(boost::system::errc::success,boost::system::system_category());
}

Trentino::Invocation::InvocationContextPtr DataHandlerIpc::createInvocationContextPtr( const Trentino::ServiceRegistry::ServiceInfoPtr& serviceInfo, 
   ErrorCode& /*ec*/ ) const
{
   InvocationContextPtr result( new InvocationContext());
   result->setServiceInfo(serviceInfo);
   return result;
}

const bool DataHandlerIpc::isServiceActive( const ConstServiceBasePtr& runtimeServicePtr, 
   ErrorCode& /*ec*/ )
{
   return runtimeServicePtr &&(runtimeServicePtr->state() == ServiceBase::Available);
}

void Trentino::Binding::IPC::DataHandlerIpc::handle(const IpcSoapMsg& request, IpcSoapMsg& response, boost::interprocess::managed_shared_memory& managedShm) 
{
   ErrorCode ec;
   mManaged_shm = &managedShm;
   dataToResponse(request, response, ec);
}

