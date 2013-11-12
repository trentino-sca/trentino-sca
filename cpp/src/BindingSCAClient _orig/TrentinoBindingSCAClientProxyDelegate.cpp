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

#include "TrentinoBindingSCAClientProxyDelegate.h"
#include "TrentinoBindingSCAClientProxyDelegateImpl.h"
#include <Binding/CompactSoap/BindingCompactSoapProtobufMessages.h>



using namespace std; 
using namespace Trentino::Binding::SCA::Client;
using namespace Trentino::Binding::SCA;

Trentino::Binding::SCA::Client::BindingProxyDelegate::BindingProxyDelegate(const char* host):
    mInternalHandler(new Trentino::Binding::SCA::Client::BindingProxyDelegateImpl(host))
{
}


void BindingProxyDelegate::send(const ::google::protobuf::MessageLite* message, trentino::bindingsca::csoap::Soap* soap, const char* action, const char* from) const
   {
   mInternalHandler->send(message,soap,action,from);
   }

