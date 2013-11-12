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

            //****************************************************************************************************
            //                                         getServiceMetadata()
            //****************************************************************************************************
            //! \brief get the service metatata from a binding
            //! \param Trentino::RuntimeModel::ServiceBasePtr service: pointer to a runtime service
            //! \return boost::shared_ptr<Trentino::SCA::Model::Metadata>: pointer to a metadata collection
            //****************************************************************************************************
            virtual boost::shared_ptr<Trentino::SCA::Model::Metadata> getServiceMetadata(Trentino::RuntimeModel::ServiceBasePtr service);

            //****************************************************************************************************
            //                                         getServiceUri()
            //****************************************************************************************************
            //! \brief get the service uri from given metadata from a binding
            //! \param metadata: set of metadata
            //! \return string representation of complete URI or empty string in case of error
            //****************************************************************************************************
            virtual std::string getServiceUri(Trentino::SCA::Model::Metadata &metadata);

            void configure( Trentino::Binding::ConfigOptions& configOptions,const Trentino::ServiceRegistry::ServiceRegistryPtr& registry, const Trentino::Invocation::InvokerPtr& invoker );
            //data
         private:
            const std::string mBindingId;
            Trentino::Binding::TrentinoBindingContextPtr mTrentinoBindingContext;
            ZeroMqServerPtr mServer;
            Trentino::Invocation::InvokerPtr mInvoker;
            Trentino::ServiceRegistry::ServiceRegistryPtr mServiceRegistry;
            CompactSoapDataHandlerPtr mDataHandler;
            zmq::context_t* mContext;
            };
      }//namespace SCA
   }//namespace TBinding
}//namepsace Trentino

#endif //TrentinoBindingSCATrentinoBindingSCAH

