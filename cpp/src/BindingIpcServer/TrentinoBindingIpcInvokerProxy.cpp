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
#include "TrentinoBindingIpcInvokerProxy.h"

//specific
#include "../Runtime/SCAModel/TrentinoSCAModelCPPInterface.h"
#include "../Runtime/Invocation/TrentinoInvocationInvocationData.h"
#include "../Runtime/RuntimeModel/TrentinoRuntimeModelServiceBase.h"
#include "../Runtime/SCAModel/TrentinoSCAModelComponentService.h"
#include "../Runtime/SCAModel/TrentinoSCAModelCPPFunction.h"

using namespace Trentino::SCA::Model;

//class InvokerProxy
Trentino::Binding::IPC::InvokerProxy::InvokerProxy(Trentino::Invocation::InvokerPtr invoker): mInvoker (invoker)
{

}

Trentino::Binding::IPC::InvokerProxy::~InvokerProxy()
{
   mInvoker.reset();
}

void Trentino::Binding::IPC::InvokerProxy::invoke(Trentino::Invocation::InvocationData& invocationDataPtr,
   void* retVal,
   Trentino::Invocation::InvocationContext& invocationContextPtr, 
   Trentino::RuntimeModel::ErrorCode& ec) const
{
   try
   {
      mInvoker->invoke(invocationDataPtr, retVal, invocationContextPtr);
   }
   catch (std::exception& ex) 
   {
      ec.assign(Trentino::RuntimeModel::invocation_exception);
      ec.setException(boost::shared_ptr<std::exception>(new std::runtime_error(ex.what())));
      //Fixme, how to copy a reference 
   }
   catch (...) 
   {
      ec.assign(Trentino::RuntimeModel::invocation_exception);
      //Fixme, how to copy a reference 
   }
}

void Trentino::Binding::IPC::InvokerProxy::invokeLater(  Trentino::Invocation::InvocationData& invocationData,
   void* retVal,
   Trentino::Invocation:: InvocationContext& invocationContextPtr,
   Trentino::RuntimeModel::ErrorCode& ec ) const
{
   //later invocation is just redirecting to direct invocation.
   //future implementation will delay invocation to a later time
   invoke(invocationData, retVal, invocationContextPtr, ec);
}

bool Trentino::Binding::IPC::InvokerProxy::isOneWay( Trentino::Invocation::InvocationDataPtr& /*invocationDataPtr*/ ) const
{
   return false;
}
