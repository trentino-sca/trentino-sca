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

#ifndef TrentinoBindingSCATrentinoBindingSCAH
#define TrentinoBindingSCATrentinoBindingSCAH

//baseclass
#include "../Runtime/Binding/TrentinoBindingTrentinoBinding.h"

//standard
#include <string>
#include <boost/shared_ptr.hpp>
#include "TrentinoBindingSCAImpl.h"
//#include <iostream>

//specific
#include "../Runtime/ServiceRegistry/ServiceRegistry.h"
#include "../Runtime/Invocation/TrentinoInvocation.h"
#include "TrentinoBindingSCAContext.h"
#include "TrentinoBindingSCAZeroMqServer.h"


namespace Trentino{
   namespace Binding{
      namespace SCA{
         class TrentinoBindingSCA;
         typedef boost::shared_ptr<TrentinoBindingSCA> TrentinoBindingSCAPtr;
         //**************************************************************************************************
         //                                TrentinoBindingSCA
         //**************************************************************************************************
         //! \brief  The Trentino SCA Binding implementation main class
         //**************************************************************************************************
         class BINDINGSCA_IMPORT_EXPORT TrentinoBindingSCA : public Trentino::Binding::TrentinoBinding 
         {
            //constructor
         public:
            TrentinoBindingSCA( const std::string &bindingId);
            virtual ~TrentinoBindingSCA();
         private:
            TrentinoBindingSCA& operator=(const TrentinoBindingSCA& );

            //services
         public:
            virtual void start();
            virtual void stop ();


            //****************************************************************************************************
            //                                         getId()
            //****************************************************************************************************
            //! \brief get the Binding ID
            //! \return const std::string
            //****************************************************************************************************
            const std::string getId(){
               return mBindingId;
            }

            //****************************************************************************************************
            //                                         setContext()
            //****************************************************************************************************
            //! \brief set the context used by this Binding
            //! \param const TrentinoBindingContextPtr & context
            //! \return void
            //****************************************************************************************************
            void  setContext( const TrentinoBindingContextPtr& context ){
               mTrentinoBindingContext = context;
            }

         public:
            //****************************************************************************************************
            //                                   setInvoker()
            //****************************************************************************************************
            //! \brief
            //! \param const Trentino::Invocation::InvokerPtr & invoker
            //! \return void
            //****************************************************************************************************
            void setInvoker(const Trentino::Invocation::InvokerPtr& invoker){
               mInvoker = invoker;
               }

            //****************************************************************************************************
            //                                         invoker()
            //****************************************************************************************************
            //! \brief return the invoker used by this binding
            //! \return const Trentino::Invocation::InvokerPtr&
            //****************************************************************************************************
            const Trentino::Invocation::InvokerPtr& invoker() const{ 
               return mInvoker;
               }


            //****************************************************************************************************
            //                                         serviceRegistry()
            //****************************************************************************************************
            //! \brief return the ServiceRegistry used by this Binding
            //! \return Trentino::ServiceRegistry::ServiceRegistryPtr
            //****************************************************************************************************
            Trentino::ServiceRegistry::ServiceRegistryPtr serviceRegistry() const{
               return mServiceRegistry;
               }


            //****************************************************************************************************
            //                                         setServiceRegistry()
            //****************************************************************************************************
            //! \brief set the Service Registry used by this Binding
            //! \param const Trentino::ServiceRegistry::ServiceRegistryPtr & val
            //! \return void
            //****************************************************************************************************
            void setServiceRegistry(const Trentino::ServiceRegistry::ServiceRegistryPtr& val){ 
               mServiceRegistry = val;
               }

            void configure( Trentino::Binding::ConfigOptions& configOptions,const Trentino::ServiceRegistry::ServiceRegistryPtr& registry, const Trentino::Invocation::InvokerPtr& invoker );
            //data
         private:
            const std::string mBindingId;
            Trentino::Binding::TrentinoBindingContextPtr mTrentinoBindingContext;
            ZeroMqServerPtr mServer;
            Trentino::Invocation::InvokerPtr mInvoker;
            Trentino::ServiceRegistry::ServiceRegistryPtr mServiceRegistry;
            ZeroMqDataHandlerPtr mDataHandler;
            zmq::context_t mContext;
            };
      }//namespace SCA
   }//namespace TBinding
}//namepsace Trentino

#endif //TrentinoBindingSCATrentinoBindingSCAH

