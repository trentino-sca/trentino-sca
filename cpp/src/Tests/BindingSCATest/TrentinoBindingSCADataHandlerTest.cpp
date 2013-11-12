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
#include "TrentinoBindingSCADataHandlerTest.h"

//Standard
#include <fstream>
#include <vector>
#include <boost/system/error_code.hpp>
#include "boost/exception/detail/exception_ptr.hpp"

//tests
#include <gmock/gmock.h>
#include <gtest/gtest.h>

//Class under test
#include "../../BindingSCA/TrentinoBindingSCADataHandler.h"







//specific
//compact soap library
#include "../../BindingCompactSoap/Binding/CompactSoap/BindingCompactSoapProtobufMessages.h"
//mocks
#include "TrentinoRuntimeModelMocks.h"
#include "TrentinoBindingSCAMocks.h"
#include "TrentinoServiceRegistryMocks.h"

#include "../../Runtime/ServiceRegistry/TrentinoServiceRegistryServiceInfo.h"
#include "TrentinoBindingSCADataHandlerTest.h"
#include "../../Utils/TrentinoUtilsURI.h"
#include "../../Runtime/Invocation/TrentinoInvocationInvocationData.h"
#include "../../BindingSCA/TrentinoBindingSCAContext.h"

void createMockConverterWithDefaultReturnValue();


//Usings
using namespace std;
using namespace Trentino::Binding;
using namespace Trentino::Binding::SCA;
using namespace Trentino::Binding::SCA::Tests;
using namespace Trentino::RuntimeModel;
using namespace Trentino::ServiceRegistry;
using namespace trentino::bindingsca::csoap;
using namespace Trentino::Invocation;
using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;





//****************************************************************************
//
//                           DataHandlerTest Tests
//
//****************************************************************************
//! \brief 
//****************************************************************************


namespace{
   //! Uncomment the following lines when they will be used
   //const char* CANNOT_PARSE_INPUT ("Cannot parse input");
   //const char* MSG_503_SERVICE_UNAVAILABLE ("503 Service Unavailable");
   const char* MSG_404_NOT_FOUND("404");
   const char* MSG_400_BAD_REQUEST="400";
   const char* MSG_501_NOT_IMPLEMENTED="501";

   void soapBodyAllwaysContainsAFAultMessageMethod( trentino::bindingsca::csoap::Soap_faultcodeEnum code){
      trentino::bindingsca::csoap::Soap response;
     
      Trentino::RuntimeModel::ErrorCode ec;
      const boost::shared_ptr<MockFaultDetailBuilder> mockDetailBuilderPtr(new MockFaultDetailBuilder());
      Trentino::Binding::SCA::DataHandler::buildErrorResponse(response,code,ec, mockDetailBuilderPtr);
      const bool hasFault =  response.envelope().body().has_faultmessage();
      EXPECT_EQ(0,ec.value());
      EXPECT_EQ(true,hasFault);
   }

   void checkHasFaultMessage(const trentino::bindingsca::csoap::Soap& message){
      const bool hasFault =  message.envelope().body().has_faultmessage();
      EXPECT_EQ(true,hasFault);
   }

   void checkHasBadRequest(const DataHandler& handler, const char* expectedRequestId){
      trentino::bindingsca::csoap::Soap response;
      trentino::bindingsca::csoap::Soap request;
      Trentino::RuntimeModel::ErrorCode ec;
      handler.dataToResponse(request,response,ec);
      checkHasFaultMessage(response);
      const trentino::bindingsca::csoap::Soap_Fault& fMsg = response.envelope().body().faultmessage();
      const  std::string& subcode = fMsg.code().subcode().value();

      EXPECT_STREQ((&subcode)->c_str(), expectedRequestId);
   }


   template<typename MethodPtr>
   void createMockServiceInfoReader(boost::shared_ptr<DataHandlerDependencies>& deps, DataHandlerTestHelper*helper,MethodPtr obj){
      MockServiceInfoReader* mockServiceInfoReader = new MockServiceInfoReader();
      EXPECT_CALL(*mockServiceInfoReader, readServiceInfo(_,_,_))
         .WillOnce(Invoke(helper,obj));
      deps->setServiceInfoReader(ServiceInfoReaderPtr(mockServiceInfoReader));
   }

   template<typename MethodPtr>
   void createMockSCAServiceLocator(DataHandler* handler,boost::shared_ptr<DataHandlerDependencies>& deps, DataHandlerTestHelper*helper,MethodPtr obj)
   {
      (void) deps;
      MockServiceRegistryBase* mockServiceRegistryBase = new MockServiceRegistryBase();
      EXPECT_CALL(*mockServiceRegistryBase,findService(_))
         .WillOnce(Invoke(helper,obj));
      ContextPtr context (new Context());
      context->setServiceRegistry(Trentino::ServiceRegistry::ServiceRegistryPtr(mockServiceRegistryBase));
      handler->setSCAContext(context);
   }

}

void DataHandlerTestHelper::CompactSoapConverter_toMessage_converterReturnError(trentino::bindingsca::csoap::Soap& aMessage,const ArrayInputStreamPtr& is, Trentino::RuntimeModel::ErrorCode& ec )
{
   (void)is;
   (void)aMessage;
   ec.assign(boost::system::errc::bad_message);
}

//**************************************************************************
//! 
//**************************************************************************
TEST(DataHandlerbuildErrorResponse,SoapBodyAllwaysContainsAFAultMessage)
{
   trentino::bindingsca::csoap::Soap response;
   Trentino::RuntimeModel::ErrorCode ec;
   trentino::bindingsca::csoap::Soap_faultcodeEnum code = Soap_faultcodeEnum_DataEncodingUnknown;
   soapBodyAllwaysContainsAFAultMessageMethod(code);
   code = Soap_faultcodeEnum_MustUnderstand;
   soapBodyAllwaysContainsAFAultMessageMethod(code);
   code = Soap_faultcodeEnum_Sender;
   soapBodyAllwaysContainsAFAultMessageMethod(code);
   code = Soap_faultcodeEnum_Receiver;
   soapBodyAllwaysContainsAFAultMessageMethod(code);
}


//! \brief if Error code has an Exception, then the exception message created by t5he Detail Builder is in the Fault reason
TEST(DataHandlerbuildErrorResponse, IfErrorCodeHasAnExceptionThenExceptionMessageCreatedByDetailBuilderIsInFaultReason)
{
   trentino::bindingsca::csoap::Soap response;
   Trentino::RuntimeModel::ErrorCode ec(Trentino::RuntimeModel::ExceptionPtr(new std::runtime_error("TestException")));
   trentino::bindingsca::csoap::Soap_faultcodeEnum code = Soap_faultcodeEnum_DataEncodingUnknown;
   const boost::shared_ptr<MockFaultDetailBuilder> mockDetailBuilderPtr(new MockFaultDetailBuilder);
   MockFaultDetailBuilder& mockDetailBuilder = *mockDetailBuilderPtr.get();
   const char* detailInfo = "EXCEPTIONDETAIL";
   EXPECT_CALL(mockDetailBuilder,createDetail(_))     
      .WillOnce(Return (detailInfo));
   Trentino::Binding::SCA::DataHandler::buildErrorResponse(response,code,ec, mockDetailBuilderPtr);
   const trentino::bindingsca::csoap::Soap_Fault& fMsg = response.envelope().body().faultmessage();
   const  std::string& detail = fMsg.detail();
   EXPECT_STREQ((&detail)->c_str(),detailInfo);
}


//! \brief if Service inforeader cannot find a ServiceInformation, then a soap message is returned containing the message "400 bad request"
TEST_F (DISABLED_DataHandlerTest, DataToResponseIfServiceInfoReaderCannotFindAServiceThenASoapMessageIsReturnedContainingTheMessage400BadRequest){

   createMockServiceInfoReader(
      deps,
      &helper,
      &DataHandlerTestHelper::ServiceInfoReader_readServiceInfo_ReturnNonInitializedSharedPointer);
   checkHasBadRequest(handler,MSG_400_BAD_REQUEST);
}


//! \brief if service Locator found no service, then a Soap fault message is returned containing The fault message 404 not found
TEST_F(DISABLED_DataHandlerTest, DataToResponseIfServiceLocatorFoundNoServiceThenASoapMessageisReturnedContainingTheFaultMessage404NotFound){

   createMockServiceInfoReader(
      deps,
      &helper,
      &DataHandlerTestHelper::ServiceInfoReader_readServiceInfo_ReturnDefault);

   createMockSCAServiceLocator(
      &handler,
      deps,
      &helper,
      &DataHandlerTestHelper::ServiceRegistry_findService_ReturnNullPointer);
   checkHasBadRequest(handler,MSG_404_NOT_FOUND);
}

//! \brief if service Locator assign an error, then a Soap fault message is returned containing The fault message 404 not found
TEST_F(DISABLED_DataHandlerTest, DataToResponseIfServiceLocatorAssignErrorThenASoapMessageisReturnedContainingTheFaultMessage404NotFound){

   createMockServiceInfoReader(
      deps,
      &helper,
      &DataHandlerTestHelper::ServiceInfoReader_readServiceInfo_ReturnDefault);

   createMockSCAServiceLocator(
      &handler,
      deps,
      &helper,
      &DataHandlerTestHelper::ServiceRegistry_findService_ReturnNoNullPointerButAssignError);
   checkHasBadRequest(handler,MSG_404_NOT_FOUND);
}

TEST_F(DISABLED_DataHandlerTest,DataToResponseIfServiceLocatorSaysServiceIsNotActiveThenASoapMessageisReturnedContainingTheFaultMessage404NotFound){

   createMockServiceInfoReader(
      deps,
      &helper,
      &DataHandlerTestHelper::ServiceInfoReader_readServiceInfo_ReturnDefault);

   Trentino::RuntimeModel::Tests::MockServiceBase* mockServiceBase = new Trentino::RuntimeModel::Tests::MockServiceBase();
   helper.mSCAServiceLocator_findService_defaultReturnValue = Trentino::RuntimeModel::ServiceBasePtr(mockServiceBase);
   
   ON_CALL(*mockServiceBase, state())
.WillByDefault(Return(Trentino::RuntimeModel::ServiceBase::Unavailable));

   createMockSCAServiceLocator(
      &handler,
      deps,
      &helper,
      &DataHandlerTestHelper::ServiceRegistry_findService_ReturnHelperDefaultValue);
   checkHasBadRequest(handler,MSG_404_NOT_FOUND);
}


//! \brief Service Has no SCABindingHelper then a Fault Message with code 501 Not implemented is generated
TEST_F(DISABLED_DataHandlerTest, DataToResponseServiceHasNoBindingHelperThenAFaultMessageContaining501NotImplemented){
   createMockServiceInfoReader(
      deps,
      &helper,
      &DataHandlerTestHelper::ServiceInfoReader_readServiceInfo_ReturnDefault);

   Trentino::RuntimeModel::Tests::MockServiceBase* service =  new Trentino::RuntimeModel::Tests::MockServiceBase();
   ON_CALL(*service, bindingHelperByBindingId(_))
      .WillByDefault(Return(BindingHelperBasePtr()));

   ON_CALL(*service, state())
      .WillByDefault(Return(Trentino::RuntimeModel::ServiceBase::Available));

   helper.mSCAServiceLocator_findService_defaultReturnValue = Trentino::RuntimeModel::ServiceBasePtr(service);

   createMockSCAServiceLocator(
      &handler,
      deps,
      &helper,
      &DataHandlerTestHelper::ServiceRegistry_findService_ReturnHelperDefaultValue);
   checkHasBadRequest(handler,MSG_501_NOT_IMPLEMENTED);
}




//! \brief if Service Proxy Assign an error during call, then a fault message is generated
TEST_F(DISABLED_DataHandlerTest,DataToResponseIfServiceProxyAssignAnErrorThenFaultMessageIsGenerated ){

}

//! \brief If the Service Proxy assign an error during call, and the fault builder can create a detail, then the detail should be available
//! in the fault message. 
TEST_F(DISABLED_DataHandlerTest,DataToResponseIfServiceProxyAssignErrorAndFaultBuilderCanCreateDetailThenDetailIsAvailableInTheFaultMessage){

}






//*******************************************************************************************************************************************************
//                                                   Implementation
//*******************************************************************************************************************************************************

void
   DataHandlerTestHelper::ServiceInfoReader_readServiceInfo_ReturnNonInitializedSharedPointer( 
   trentino::bindingsca::csoap::Soap request, Trentino::ServiceRegistry::ServiceInfo& info, Trentino::RuntimeModel::ErrorCode& ec )
{
   (void) request;
   (void) ec;
   (void) info;
}

void DataHandlerTestHelper::ServiceInfoReader_readServiceInfo_ReturnDefault( trentino::bindingsca::csoap::Soap request,Trentino::ServiceRegistry::ServiceInfo& info, Trentino::RuntimeModel::ErrorCode& ec )
{
   (void) request;
   (void) ec;
   (void) info;
}


//Helper methods for ServiceLocator
Trentino::RuntimeModel::ServiceBasePtr 
   Trentino::Binding::SCA::Tests::DataHandlerTestHelper::ServiceRegistry_findService_ReturnNullPointer( 
   const Trentino::ServiceRegistry::ServiceInfo& serviceInfo)
{
   (void) serviceInfo;
   return Trentino::RuntimeModel::ServiceBasePtr();
}

Trentino::RuntimeModel::ServiceBasePtr 
   Trentino::Binding::SCA::Tests::DataHandlerTestHelper::ServiceRegistry_findService_ReturnNoNullPointerButAssignError( 
   const Trentino::ServiceRegistry::ServiceInfo& serviceInfo)
{
   (void) serviceInfo;
   return Trentino::RuntimeModel::ServiceBasePtr();
}

Trentino::RuntimeModel::ServiceBasePtr 
   Trentino::Binding::SCA::Tests::DataHandlerTestHelper::ServiceRegistry_findService_ReturnHelperDefaultValue( 
   const Trentino::ServiceRegistry::ServiceInfo& serviceInfo)
{
   (void) serviceInfo;
   return mSCAServiceLocator_findService_defaultReturnValue;
}

