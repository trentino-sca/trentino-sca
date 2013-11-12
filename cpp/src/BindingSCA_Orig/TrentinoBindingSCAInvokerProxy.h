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
#ifndef TrentinoBindingSCAInvokerProxyH
#define TrentinoBindingSCAInvokerProxyH

#include "TrentinoBindingSCAImpl.h"
#include <Runtime/Invocation/TrentinoInvocationInvoker.h>
#include <Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h>


namespace Trentino{
   namespace Binding{
      namespace SCA{
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
         class BINDINGSCA_IMPORT_EXPORT InvokerProxyBase {

         public:
            //***************************************************************************************
            //                              invoke
            //***************************************************************************************
            //! \brief synchronous invoke the service with the given data, handle error
            //***************************************************************************************
            virtual void invoke( Trentino::Invocation::InvocationDataPtr& invocationDataPtr,  
               Trentino::Invocation::InvocationContextPtr& invocationContextPtr, 
               Trentino::RuntimeModel::ErrorCode& ec ) const =0;

            //***************************************************************************************
            //                              invokeLater
            //***************************************************************************************
            //! \brief asynchronous invoke the service with the given data, handle error
            //***************************************************************************************
            virtual void invokeLater(  Trentino::Invocation::InvocationDataPtr& invocationDataPtr, 
               Trentino::Invocation:: InvocationContextPtr& invocationContextPtr, 
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
         class BINDINGSCA_IMPORT_EXPORT InvokerProxy : public InvokerProxyBase {



            //constructors
         public:
            InvokerProxy(Trentino::Invocation::InvokerPtr invoker);
            virtual ~InvokerProxy();

            //services
         public:

            //! \sa InvokerProxy::invoke
            virtual void invoke(Trentino::Invocation::InvocationDataPtr& invocationDataPtr, 
               Trentino::Invocation::InvocationContextPtr& invocationContextPtr, 
               Trentino::RuntimeModel::ErrorCode& ec ) const;

            //! \sa InvokerProxy::invokeLater
            virtual void invokeLater(  Trentino::Invocation::InvocationDataPtr& invocationDataPtr, 
               Trentino::Invocation:: InvocationContextPtr& invocationContextPtr, 
               Trentino::RuntimeModel::ErrorCode& ec ) const;

            //! \sa InvokerProxy::isOneWay      
            virtual bool isOneWay( Trentino::Invocation::InvocationDataPtr& invocationDataPtr ) const;

            //data
         private :
            Trentino::Invocation::InvokerPtr mInvoker;
            }; //Class InvokerProxyImpl

         }//namespace SCA

      }//namespace Binding

   }//namespace Trentino

#endif //TrentinoBindingSCAInvokerProxyH

