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
#ifndef TrentinoBindingIpcInvokerProxyH
#define TrentinoBindingIpcInvokerProxyH


#include <Runtime/Invocation/TrentinoInvocationInvoker.h>
#include <Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h>
#include "TrentinoBindingIpcDefinitions.h"

namespace Trentino{
namespace Binding{
namespace IPC
{
   class InvokerProxyBase;
   typedef boost::shared_ptr<InvokerProxyBase> InvokerProxyPtr;

   //class declaration 
   //********************************************************************************
   //                            InvokerProxy
   //********************************************************************************
   //! \brief
   //!
   //!
   //*******************************************************************************
   class BINDINGIPC_IMPORT_EXPORT InvokerProxyBase 
   {

   public:
      //***************************************************************************************
      //                              invoke
      //***************************************************************************************
      //! \brief synchronous invoke the service with the given data, handle error
      //***************************************************************************************
      virtual void invoke( Trentino::Invocation::InvocationData& invocationDataPtr, 
         void* retVal,
         Trentino::Invocation::InvocationContext& invocationContextPtr, 
         Trentino::RuntimeModel::ErrorCode& ec ) const =0;

      //***************************************************************************************
      //                              invokeLater
      //***************************************************************************************
      //! \brief asynchronous invoke the service with the given data, handle error
      //***************************************************************************************
      virtual void invokeLater(  Trentino::Invocation::InvocationData& invocationDataPtr, 
         void* retVal,
         Trentino::Invocation:: InvocationContext& invocationContextPtr, 
         Trentino::RuntimeModel::ErrorCode& ec ) const =0;


      //***************************************************************************************
      //                              isOneWay
      //***************************************************************************************
      //! \brief check if the call in this InvocationData is a oneWay Call
      //***************************************************************************************
      virtual bool isOneWay( Trentino::Invocation::InvocationDataPtr& invocationDataPtr ) const =0;
   }; //class InvokerProxy


   //class declaration 
   //********************************************************************************
   //                            InvokerProxyImpl
   //********************************************************************************
   //! \brief
   //!
   //!
   //*******************************************************************************
   class BINDINGIPC_IMPORT_EXPORT InvokerProxy : public InvokerProxyBase 
   {
      //constructors
   public:
      InvokerProxy(Trentino::Invocation::InvokerPtr invoker);
      virtual ~InvokerProxy();

      //services
   public:

      //! \sa InvokerProxy::invoke
      virtual void invoke(Trentino::Invocation::InvocationData& invocationDataPtr,
         void* retVal,
         Trentino::Invocation::InvocationContext& invocationContextPtr, 
         Trentino::RuntimeModel::ErrorCode& ec) const;

      //! \sa InvokerProxy::invokeLater
      virtual void invokeLater(Trentino::Invocation::InvocationData& invocationDataPtr,
         void* retVal,
         Trentino::Invocation:: InvocationContext& invocationContextPtr,
         Trentino::RuntimeModel::ErrorCode& ec  ) const;

      //! \sa InvokerProxy::isOneWay      
      virtual bool isOneWay( Trentino::Invocation::InvocationDataPtr& invocationDataPtr ) const;

      //data
   private :
      Trentino::Invocation::InvokerPtr mInvoker;
   }; //Class InvokerProxyImpl

}//namespace IPC
}//namespace Binding
}//namespace Trentino

#endif //TrentinoBindingIpcInvokerProxyH

