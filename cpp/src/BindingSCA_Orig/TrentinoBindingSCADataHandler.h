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
#ifndef TrentinoBindingSCADataHandlerH
#define TrentinoBindingSCADataHandlerH

//standtard
#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>

//Root header
#include "TrentinoBindingSCAImpl.h"

//compact soap
#include <Binding/CompactSoap/BindingCompactSoapProtobufMessages.h>
#include <Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h>
#include <Runtime/RuntimeModel/TrentinoRuntimeModel.h>

#include "TrentinoBindingSCASCABodyDeserializer.h"
#include "TrentinoBindingSCAInvokerProxy.h"
#include "TrentinoBindingSCAServiceInfoReader.h"
#include "TrentinoBindingSCAContext.h"
#include "TrentinoBindingSCAZeroMqDataHandler.h"


namespace Trentino{
   namespace Binding{
      namespace SCA{
         class DataHandler;
         typedef boost::shared_ptr<DataHandler> DataHandlerPtr;
         //*****************************************************************************
         //                            DataHandlerData
         //*****************************************************************************
         //! \brief that holds datas of a DataHandler
         //*****************************************************************************
         class BINDINGSCA_IMPORT_EXPORT DataHandlerDependencies {

         public:
            //services
            //! \brief parse a soap message to find out information about the service been invoked
            const ServiceInfoReaderPtr& serviceInfoReader() const{
               return mServiceInfoReader;
            }


            void setServiceInfoReader(ServiceInfoReaderPtr val) { mServiceInfoReader.swap(val);}

            //! \brief can read soap message body and create invocation data
            const  SCABodyDeserializerPtr sCABodyDeserializer() const{
               return mSCABodyDeserializer;
            }

            void setSCABodyDeserializer(SCABodyDeserializerPtr val) { mSCABodyDeserializer.swap(val); }

            //! \brief a wrapper around the Invocation layer. can invoke a method
            const  InvokerProxyPtr invokerProxy() const{
               return mInvokerProxy;
            }

            void setInvokerProxy(InvokerProxyPtr val) { mInvokerProxy .swap(val);}
            
            
            const std::string bindingId(){
               return mBindingId;
            }

            void setBindingId(const std::string& bindingId)
            {
               mBindingId = bindingId;
            }
            //data
         private:

            //! \brief parse a soap message to find out information about the service been invoked
            ServiceInfoReaderPtr mServiceInfoReader;

            //! \brief can read soap message body and create invocation data
            SCABodyDeserializerPtr mSCABodyDeserializer;

            //! \brief a wrapper around the Invocation layer. can invoke a method
            InvokerProxyPtr mInvokerProxy;

            std::string mBindingId;

         };//class SCABindingDataHandlerDependencies



         //*****************************************************************************
         //                            SCABindingDataHandler
         //*****************************************************************************
         //! \brief main class that process incoming messages to response. 
         //! this class is independent of the Transport protocol, but still depend on 
         //! SCA Binding serialization mechanism
         //*****************************************************************************

         class BINDINGSCA_IMPORT_EXPORT DataHandler: public ZeroMqDataHandler {

         public:
            //construction
            DataHandler();

            //services
         public:

             virtual void handle(const SoapPtr& request, SoapPtr& response) const;
            //****************************************************************************
            //                         dataToResponse()
            //****************************************************************************
            //! \brief given a data received from the transport layer, process the data and 
            //! call the invocation layer, transform the result of the invocation
            //! layer back to a message that is sent back to the client
            //****************************************************************************
            void dataToResponse(const SoapPtr& request, SoapPtr& response , Trentino::RuntimeModel::ErrorCode& ec) const;


            void invokeAndPrepareResponse(Trentino::Invocation::InvocationDataPtr& invocationDataPtr,
               Trentino::Invocation::InvocationContextPtr& invocationContextPtr ,
               const  SCABindingHelperBasePtr& scaBindingHelperBasePtr, 
               SoapPtr& response, 
               Trentino::RuntimeModel::ErrorCode& ec) const;
           
            //****************************************************************************************************
            //                                         buildErrorResponse()
            //****************************************************************************************************
            //! \brief given an error message, build the corresponding Soap response
            //! this version of the method does not provide details about the error as 
            //! required by the web service specification
            //! \param trentino::bindingsca::csoap::Soap & response
            //! \param const trentino::bindingsca::csoap::Soap_faultcodeEnum & fCode
            //! \param Trentino::RuntimeModel::ErrorCode & ec
            //! \param const FaultDetailBuilderPtr & faultDetailBuilder
            //! \return void
            //****************************************************************************************************
            static void buildErrorResponse(SoapPtr& response,const trentino::bindingsca::csoap::Soap_faultcodeEnum &fCode
               ,Trentino::RuntimeModel::ErrorCode& ec,const FaultDetailBuilderPtr& faultDetailBuilder );

         public:


            void setDependencies(const boost::shared_ptr<DataHandlerDependencies> deps){
               mDeps = deps;
            }


            //****************************************************************************************************
            //                                         handleServiceNotFound()
            //****************************************************************************************************
            //! \brief create the corresponding Fault message when the Service cannot be found
            //! \param Trentino::RuntimeModel::ErrorCode & ec
            //! \param trentino::bindingsca::csoap::Soap & response
            //! \return void
            //****************************************************************************************************
            static void handleServiceNotFound( Trentino::RuntimeModel::ErrorCode &ec, SoapPtr& response );

            //****************************************************************************************************
            //                                         handleBindingHelperNotFound()
            //****************************************************************************************************
            //! \brief  create the corresponding fault message when a Binding helper cannot be found
            //! \param Trentino::RuntimeModel::ErrorCode & ec
            //! \param trentino::bindingsca::csoap::Soap & response
            //! \return void
            //****************************************************************************************************
            static void handleBindingHelperNotFound( Trentino::RuntimeModel::ErrorCode &ec, SoapPtr& response );

            //****************************************************************************************************
            //                                         handleServiceInfoCannotBeUnderstood()
            //****************************************************************************************************
            //! \brief create the corresponding fualt message when a service cannot be understood by the Binding
            //! \param Trentino::RuntimeModel::ErrorCode & ec
            //! \param trentino::bindingsca::csoap::Soap & response
            //! \return void
            //****************************************************************************************************
            static void handleServiceInfoCannotBeUnderstood( Trentino::RuntimeModel::ErrorCode &ec, SoapPtr& response );

            //****************************************************************************************************
            //                                         isServiceActive()
            //****************************************************************************************************
            //! \brief check if the Service is active
            //! \param const Trentino::RuntimeModel::ServiceBasePtr & runtimeServicePtr
            //! \param Trentino::RuntimeModel::ErrorCode & ec
            //! \return const bool
            //****************************************************************************************************
            static const bool isServiceActive( const Trentino::RuntimeModel::ConstServiceBasePtr& runtimeServicePtr, Trentino::RuntimeModel::ErrorCode& ec );

            
            //****************************************************************************************************
            //                                         sCAContext()
            //****************************************************************************************************
            //! \brief get the SCA Binding Context. This context content dependencies for the SCA Binding
            //! \return Trentino::Binding::SCA::ContextPtr
            //****************************************************************************************************
            Trentino::Binding::SCA::ContextPtr sCAContext() const{ 
               return mSCAContext;
               }

            //****************************************************************************************************
            //                                         setSCAContext()
            //****************************************************************************************************
            //! \brief set The SCA Binding Context
            //! \param Trentino::Binding::SCA::ContextPtr val
            //! \return void
            //****************************************************************************************************
            void setSCAContext(const Trentino::Binding::SCA::ContextPtr& val){
               mSCAContext = val;
               }

         private:
            //****************************************************************************************************
            //                                         createInvocationContextPtr()
            //****************************************************************************************************
            //! \brief create the Invocation Context and initialize it with default data
            //! \param const Trentino::ServiceRegistry::ServiceInfoPtr & serviceInfo
            //! \param Trentino::RuntimeModel::ErrorCode & ec
            //! \return Trentino::Invocation::InvocationContextPtr
            //****************************************************************************************************
            Trentino::Invocation::InvocationContextPtr createInvocationContextPtr( const Trentino::ServiceRegistry::ServiceInfoPtr& serviceInfo, Trentino::RuntimeModel::ErrorCode& ec ) const;
           
            //data
            //! \brief all service dependencies bundled to simplify refactory and test
            boost::shared_ptr<DataHandlerDependencies> mDeps;

            ContextPtr mSCAContext;
         };//end class DataHandler

      }//namespapce SCA
   }//namespace Binding
}//namepspace Trentino


#endif //TrentinoBindingSCADataHandlerH

