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
#include "Utils/TrentinoUtilsLogging.h"


using namespace Trentino::SCA::Model;

//class InvokerProxy
Trentino::Binding::SCA::InvokerProxy::InvokerProxy(Trentino::Invocation::InvokerPtr invoker): mInvoker (invoker)
   {

   }

Trentino::Binding::SCA::InvokerProxy::~InvokerProxy()
   {
   mInvoker.reset();
   }

void Trentino::Binding::SCA::InvokerProxy::invoke( Trentino::Invocation::InvocationData& invocationDataPtr,
                                                  const Trentino::RuntimeModel::ServiceBasePtr& targetService,
                                                  void* retVal,
                                                  Trentino::Invocation::InvocationContext& invocationContextPtr, Trentino::RuntimeModel::ErrorCode& ec ) const
   {
   try{
      mInvoker->invoke(invocationDataPtr,retVal,invocationContextPtr,targetService);
      }catch (std::exception& ex) {
         ec.assign(Trentino::RuntimeModel::invocation_exception);
         ec.setException(boost::shared_ptr<std::exception>(new std::runtime_error(ex.what())));
         logError("Unexpected exception occured '%s'",ex.what());
         //Fixme, how to copy a reference 
      }
   catch(boost::exception& ex)
      {
      std::string msg = boost::diagnostic_information(ex);
      ec.assign(Trentino::RuntimeModel::invocation_exception);
      ec.setException(boost::shared_ptr<std::exception>(new std::runtime_error(msg)));
      logError("Unexpected exception occurred '%s'",msg);
      }
   catch (std::string& ex) {
      ec.assign(Trentino::RuntimeModel::invocation_exception);
      ec.setException(boost::shared_ptr<std::exception>(new std::runtime_error(ex)));
      logError("Unexpected exception occurred '%s'",ex);
      }
   catch (...) {
      ec.assign(Trentino::RuntimeModel::invocation_exception);
      logError("Unhandled exception occurred during service invocation");
      }
   }

void Trentino::Binding::SCA::InvokerProxy::invokeLater(Trentino::Invocation::InvocationData& invocationDataPtr,
                                                       const Trentino::RuntimeModel::ServiceBasePtr& targetService,
                                                       void* retVal,Trentino::Invocation:: InvocationContext& invocationContextPtr,
                                                       Trentino::RuntimeModel::ErrorCode& ec ) const
   {
   //later invocation is just redirecting to direct invocation.
   //future implementation will delay invocation to a later time
   invoke(invocationDataPtr,targetService,retVal,invocationContextPtr,ec);
   }

bool Trentino::Binding::SCA::InvokerProxy::isOneWay( Trentino::Invocation::InvocationDataPtr& /*invocationDataPtr*/ ) const
   {
   return false;
   }
