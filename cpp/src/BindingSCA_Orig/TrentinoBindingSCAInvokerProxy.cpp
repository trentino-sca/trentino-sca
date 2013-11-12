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
#include "TrentinoBindingSCAInvokerProxy.h"

//standard
#include <vector>
#include <exception>
#include <boost/shared_ptr.hpp>

//specific
#include "../Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h"
#include "TrentinoBindingSCATrentinoBindingSCA.h"
#include "../Runtime/SCAModel/TrentinoSCAModelInterface.h"
#include "../Runtime/SCAModel/TrentinoSCAModelCPPInterface.h"
#include "../Runtime/Invocation/TrentinoInvocationInvocationData.h"
#include "../Runtime/Invocation/TrentinoInvocation.h"
#include "../Runtime/RuntimeModel/TrentinoRuntimeModelServiceBase.h"
#include "../Runtime/SCAModel/TrentinoSCAModel.h"
#include "../Runtime/SCAModel/TrentinoSCAModelComponentService.h"
#include "../Runtime/SCAModel/TrentinoSCAModelCPPFunction.h"


using namespace Trentino::SCA::Model;

//class InvokerProxy
Trentino::Binding::SCA::InvokerProxy::InvokerProxy(Trentino::Invocation::InvokerPtr invoker): mInvoker (invoker)
{

}

Trentino::Binding::SCA::InvokerProxy::~InvokerProxy()
{
   mInvoker.reset();
}

void Trentino::Binding::SCA::InvokerProxy::invoke( Trentino::Invocation::InvocationDataPtr& invocationDataPtr, Trentino::Invocation::InvocationContextPtr& invocationContextPtr, Trentino::RuntimeModel::ErrorCode& ec ) const
{
   try{
      mInvoker->invoke(invocationDataPtr,invocationContextPtr);
   }catch (std::exception& ex) {
      ec.assign(Trentino::RuntimeModel::invocation_exception, boost::system::get_system_category());
      ec.setException(boost::shared_ptr<std::exception>(new std::runtime_error(ex.what())));
      //Fixme, how to copy a reference 
   }catch (...) {
      ec.assign(Trentino::RuntimeModel::invocation_exception, boost::system::get_system_category());
      //Fixme, how to copy a reference 
   }
}

void Trentino::Binding::SCA::InvokerProxy::invokeLater(  Trentino::Invocation::InvocationDataPtr& invocationDataPtr, Trentino::Invocation:: InvocationContextPtr& invocationContextPtr, Trentino::RuntimeModel::ErrorCode& ec ) const
{
   //later invocation is just redirecting to direct invocation.
   //future implementation will delay invocation to a later time
   invoke(invocationDataPtr,invocationContextPtr,ec);
}

bool Trentino::Binding::SCA::InvokerProxy::isOneWay( Trentino::Invocation::InvocationDataPtr& invocationDataPtr ) const
{
   InterfacePtr interfacePtr = invocationDataPtr->targetService()->scaServiceType()->interfaceElement();
   
   //Interface is not a polymorphic type
   Trentino::SCA::Model::CPPInterfacePtr cppInterfacePtr = boost::static_pointer_cast<CPPInterface>(interfacePtr);

   //get the CPP interface
   const std::vector<CPPFunctionPtr> functions= cppInterfacePtr->functionElements();

   for (std::vector<CPPFunctionPtr>::const_iterator it = functions.begin(); it!=functions.end(); it++) {
    const  CPPFunctionPtr& val = *it;

      if(val->name() == invocationDataPtr->operation().data()){
         return val->isOneWay();
      }
   }
   return false;
}
