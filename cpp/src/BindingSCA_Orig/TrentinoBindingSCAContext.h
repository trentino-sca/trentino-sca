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

#ifndef TrentinoBindingSCAContextH
#define TrentinoBindingSCAContextH

//specific
#include <Runtime/ServiceRegistry/ServiceRegistry.h>
#include <Runtime/Invocation/TrentinoInvocation.h>


namespace Trentino{
   namespace Binding{
      namespace SCA{
         class Context;
         typedef boost::shared_ptr<Context> ContextPtr;
         //****************************************************************************************************
         //                                   Context
         //****************************************************************************************************
         //! \brief This clas contains external dependencies of the SCA Binding Module
         //****************************************************************************************************
         class Context{

            //services
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
            //data
         private:
            Trentino::Invocation::InvokerPtr mInvoker;
            Trentino::ServiceRegistry::ServiceRegistryPtr mServiceRegistry;
            }; // class Context
      }//namespace SCA
   }//namespace TBinding
}//namepsace Trentino

#endif //TrentinoBindingSCAContextH

