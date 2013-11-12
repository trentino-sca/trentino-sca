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


#include "TrentinoBindingSCASCABodyDeserializer.h"
#include "../Runtime/RuntimeModel/TrentinoRuntimeModel.h"
#include "../Runtime/Invocation/TrentinoInvocation.h"
#include "TrentinoBindingSCASCABindingHelper.h"

using namespace Trentino::Invocation;
using namespace Trentino::RuntimeModel;

const Trentino::Invocation::InvocationDataPtr 
   Trentino::Binding::SCA::SCABodyDeserializerImpl::deserialize( trentino::bindingsca::csoap::Soap& request, 
   const Trentino::RuntimeModel::ConstServiceBasePtr& /*runtimeServicePtr*/,
   const SCABindingHelperBasePtr& /*scaBindingHelper*/, 
   Trentino::RuntimeModel::ErrorCode& /*ec*/ ) const
{
   (void) request;
   throw "not implemented: deprecated";
}
