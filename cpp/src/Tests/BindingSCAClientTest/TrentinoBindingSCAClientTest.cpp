// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright 2012 by Siemens AG. All rights reserved.
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
#include "TrentinoBindingSCAClientTest.h"
#include "../../BindingSCAClient/TrentinoBindingSCAClientProxyDelegate.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;
using testing::ReturnPointee;
using ::testing::NiceMock;
using namespace Trentino::Binding::SCA::Tests;
using namespace Trentino::Binding::SCA;

namespace{

   }

const char* add_action ="BasicCalculator/add";
const char* add_referenceName ="BasicCalculatorRef";
//class TrentinoBindingSCATest
TEST_F(TrentinoBindingSCAITTest, invoke_4_plus_4_response_is_not_null){
 
   Trentino::Example::BasicCalculatorRemoteClient::protobuf::BasicCalculatorRequest_addRequest add_req;
   Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber pb_a;

   Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber* temppb_a = add_req.mutable_a();
   temppb_a->set_a(2);
   temppb_a->set_b(2);


   Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber* temppb_b = add_req.mutable_b();
   temppb_b->set_a(2);
   temppb_b->set_b(2);

   MessagePtr messageToSend(static_cast<::google::protobuf::MessageLite*>(&add_req));
   Trentino::Binding::SCA::Client::SoapPtr response = mDelegate.send(messageToSend, add_action, add_referenceName);
   ASSERT_TRUE(response);
 }

