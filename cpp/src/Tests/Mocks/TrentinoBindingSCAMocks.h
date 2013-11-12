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

#ifndef TrentinoBindingSCAMocksH
#define TrentinoBindingSCAMocksH

//standard
#include <boost/shared_ptr.hpp>

//tests
#include <gmock/gmock.h>

//specific
#include "../../BindingSCA/TrentinoBindingSCAFaultDetailBuilder.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h"
#include "../../BindingSCA/TrentinoBindingSCAServiceInfoReader.h"
#include "../../BindingSCA/TrentinoBindingSCASCABodyDeserializer.h"
#include "../../BindingSCA/TrentinoBindingSCAInvokerProxy.h"
#include "../../Runtime/RuntimeModel/TrentinoRuntimeModelService.h"
#include "../../BindingSCA/TrentinoBindingSCASCABindingHelper.h"


namespace Trentino{
   namespace Binding{
      namespace SCA{
         namespace Tests{

            class MockFaultDetailBuilder: public Trentino::Binding::SCA::FaultDetailBuilder{

            public:
               MockFaultDetailBuilder(){
                  using ::testing::Return;
                  using ::testing::_;
                  std::string emptyVal;
                  ON_CALL(*this, createSubCode(_))
                     .WillByDefault(Return(emptyVal));
                  ON_CALL(*this, createReason(_))
                     .WillByDefault(Return(emptyVal));
                  ON_CALL(*this, createDetail(_))
                     .WillByDefault(Return(emptyVal));
               }
               //virtual std::string createSubCode( Trentino::RuntimeModel::ErrorCode& ec ) const =0;
               MOCK_CONST_METHOD1(createSubCode, std::string (const Trentino::RuntimeModel::ErrorCode& ec));
               // virtual std::string createReason( Trentino::RuntimeModel::ErrorCode& ec ) const=0;
               MOCK_CONST_METHOD1(createReason, std::string (const Trentino::RuntimeModel::ErrorCode& ec));
               //virtual std::string createDetail(const Trentino::RuntimeModel::ErrorCode& ec) const =0;
               MOCK_CONST_METHOD1(createDetail, std::string (const Trentino::RuntimeModel::ErrorCode& ec));



            };//class MockFaultDetailBuilder



            class MockServiceInfoReader: public Trentino::Binding::SCA::ServiceInfoReader{
            public:
               MOCK_CONST_METHOD3(readServiceInfo,
                  void(const trentino::bindingsca::csoap::Soap& request, Trentino::ServiceRegistry::ServiceInfo& info,Trentino::RuntimeModel::ErrorCode& ec));
            };// class MockServiceInfoReader

            class MockSCABodyDeserializer: public Trentino::Binding::SCA::SCABodyDeserializer{
            public:
               MOCK_CONST_METHOD4(deserialize,
                  const Trentino::Invocation::InvocationDataPtr(trentino::bindingsca::csoap::Soap request, const Trentino::RuntimeModel::ConstServiceBasePtr& runtimeServicePtr,const SCABindingHelperBasePtr& scaBindingHelper,Trentino::RuntimeModel::ErrorCode& ec));
            };

            class MockInvokerProxy : public Trentino::Binding::SCA::InvokerProxyBase{
            public:
               MOCK_CONST_METHOD3(invoke,
                  void(Trentino::Invocation::InvocationDataPtr& invocationDataPtr, Trentino::Invocation::InvocationContextPtr& invocationContextPtr, Trentino::RuntimeModel::ErrorCode& ec));
               MOCK_CONST_METHOD3(invokeLater,
                  void(Trentino::Invocation::InvocationDataPtr& invocationDataPtr, Trentino::Invocation:: InvocationContextPtr& invocationContextPtr, Trentino::RuntimeModel::ErrorCode& ec));
               MOCK_CONST_METHOD1(isOneWay,
                  bool(Trentino::Invocation::InvocationDataPtr& invocationDataPtr));
            };



            class MockSCABindingHelper : public Trentino::Binding::SCA::SCABindingHelper {
            public:
               MOCK_CONST_METHOD0(getFaultBuilder,
                  const FaultDetailBuilderPtr());
               MOCK_CONST_METHOD3(serializeResponse,
                  void(const Trentino::Invocation::InvocationDataPtr& invocationDataPtr, trentino::bindingsca::csoap::Soap& resp, Trentino::RuntimeModel::ErrorCode& ec));
               MOCK_CONST_METHOD3(deserializeRequest,
                  void(const Trentino::Invocation::InvocationDataPtr& invocationDataPtr, trentino::bindingsca::csoap::Soap& req, Trentino::RuntimeModel::ErrorCode& ec));
               MOCK_CONST_METHOD1(isOneWay,
                  bool(Trentino::Invocation::InvocationDataPtr& invocationDataPtr));
               MOCK_CONST_METHOD0(version,
                  int());
               };

         } // namespace Trentino
      } // namespace Binding
   } //SCA
} // namespace Tests
#endif TrentinoBindingSCAMocksH

