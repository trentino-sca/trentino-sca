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
#ifndef TrentinoBindingIpcDataHandlerH
#define TrentinoBindingIpcDataHandlerH

//standard
#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>
#include <boost/interprocess/managed_shared_memory.hpp> 
#include <boost/interprocess/sync/named_mutex.hpp> 
#include <boost/interprocess/sync/named_condition.hpp> 
#include <boost/interprocess/sync/scoped_lock.hpp> 
#include <boost/interprocess/creation_tags.hpp>


#include <Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h>
#include <Runtime/RuntimeModel/TrentinoRuntimeModel.h>

//#include "TrentinoBindingSCASCABodyDeserializer.h"
#include "TrentinoBindingIpcInvokerProxy.h"
#include "TrentinoBindingIpcServiceInfoReaderFromIpcSoap.h"
#include "TrentinoBindingIpcContext.h"
//#include "TrentinoBindingIpcMemoryChecker.h"
#include "TrentinoBindingIpcMemoryMapObj.h"
#include "TrentinoBindingIpcSoapMsg.h"
#include "TrentinoBindingIpcDefinitions.h"
#include "TrentinoBindingIpcFaultDetailBuilder.h"

namespace Trentino{
namespace Binding{
namespace IPC
{
   
   //*****************************************************************************
   //                            SCABindingDataHandler
   //*****************************************************************************
   //! \brief main class that process incoming messages to response. 
   //! this class is independent of the Transport protocol, but still depend on 
   //! SCA Binding serialization mechanism
   //*****************************************************************************

   class BINDINGIPC_IMPORT_EXPORT DataHandlerIpc
   {
      typedef boost::shared_ptr<FaultDetailBuilder> FaultDetailBuilderPtr;
      public:
      //construction
      DataHandlerIpc();
      ~DataHandlerIpc();

      //services
      public:
      virtual void handle(const IpcSoapMsg& request, IpcSoapMsg& response, boost::interprocess::managed_shared_memory& managedShm) ;

      //****************************************************************************
      //                         dataToResponse()
      //****************************************************************************
      //! \brief given a data received from the transport layer, process the data and 
      //! call the invocation layer, transform the result of the invocation
      //! layer back to a message that is sent back to the client
      //****************************************************************************
      void dataToResponse(const IpcSoapMsg& request, 
         IpcSoapMsg& respnonse, 
         Trentino::RuntimeModel::ErrorCode& ec) const;


      void invokeAndPrepareResponse(Trentino::Invocation::InvocationDataPtr& invocationDataPtr,
         Trentino::Invocation::InvocationContextPtr& invocationContextPtr ,
         const  BindingHelperIpcPtr& bindingHelperIpcPtr,  
         Trentino::RuntimeModel::ErrorCode& ec) const;
           
   public:
      //void setDependencies(const boost::shared_ptr<DataHandlerDependencies> deps)
      //{
      //   mDeps = deps;
      //}

      void setServiceInfoReader(IpcServiceInfoReaderFromIpcSoapPtr val) 
      { 
         mServiceInfoReader.swap(val);
      }

         //   //! \brief can read soap message body and create invocation data
         //   //const  SCABodyDeserializerPtr sCABodyDeserializer() const
         //   //{
         //   //   return mSCABodyDeserializer;
         //   //}

         //   //void setSCABodyDeserializer(SCABodyDeserializerPtr val) { mSCABodyDeserializer.swap(val); }

         //   ////! \brief a wrapper around the Invocation layer. can invoke a method
         const  InvokerProxyPtr invokerProxy() const
         {
            return mInvokerProxy;
         }

         void setInvokerProxy(InvokerProxyPtr val) 
         { 
            mInvokerProxy .swap(val);
         }
      
         //   const std::string bindingId();
         //   //{
         //   //   return mBindingId;
         //   //}

         void setBindingId(const std::string& bindingId)
         {
            mBindingId = bindingId;
         }
         //data

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
         static void buildErrorResponse(IpcSoapMsg& response,
            Trentino::RuntimeModel::ErrorCode& ec,
            const FaultDetailBuilderPtr& faultDetailBuilder );
      //****************************************************************************************************
      //                                         handleServiceNotFound()
      //****************************************************************************************************
      //! \brief create the corresponding Fault message when the Service cannot be found
      //! \param Trentino::RuntimeModel::ErrorCode & ec
      //! \param trentino::bindingsca::csoap::Soap & response
      //! \return void
      //****************************************************************************************************
      static void handleServiceNotFound( Trentino::RuntimeModel::ErrorCode &ec, IpcSoapMsg& response );

      //****************************************************************************************************
      //                                         handleBindingHelperNotFound()
      //****************************************************************************************************
      //! \brief  create the corresponding fault message when a Binding helper cannot be found
      //! \param Trentino::RuntimeModel::ErrorCode & ec
      //! \param trentino::bindingsca::csoap::Soap & response
      //! \return void
      //****************************************************************************************************
      static void handleBindingHelperNotFound( Trentino::RuntimeModel::ErrorCode &ec, IpcSoapMsg& response );

      //****************************************************************************************************
      //                                         handleServiceInfoCannotBeUnderstood()
      //****************************************************************************************************
      //! \brief create the corresponding fualt message when a service cannot be understood by the Binding
      //! \param Trentino::RuntimeModel::ErrorCode & ec
      //! \param trentino::bindingsca::csoap::Soap & response
      //! \return void
      //****************************************************************************************************
      static void handleServiceInfoCannotBeUnderstood( Trentino::RuntimeModel::ErrorCode &ec,
         IpcSoapMsg& response );

      //****************************************************************************************************
      //                                         isServiceActive()
      //****************************************************************************************************
      //! \brief check if the Service is active
      //! \param const Trentino::RuntimeModel::ServiceBasePtr & runtimeServicePtr
      //! \param Trentino::RuntimeModel::ErrorCode & ec
      //! \return const bool
      //****************************************************************************************************
      static const bool isServiceActive( const Trentino::RuntimeModel::ConstServiceBasePtr& runtimeServicePtr,
         Trentino::RuntimeModel::ErrorCode& ec );

            
      //****************************************************************************************************
      //                                         sCAContext()
      //****************************************************************************************************
      //! \brief get the SCA Binding Context. This context content dependencies for the SCA Binding
      //! \return Trentino::Binding::SCA::ContextPtr
      //****************************************************************************************************
      Trentino::Binding::IPC::ContextPtr ipcContext() const
      { 
         return mIpcContext;
      }

      //****************************************************************************************************
      //                                         setSCAContext()
      //****************************************************************************************************
      //! \brief set The SCA Binding Context
      //! \param Trentino::Binding::SCA::ContextPtr val
      //! \return void
      //****************************************************************************************************
      void setIpcContext(const Trentino::Binding::IPC::ContextPtr& val)
      {
         mIpcContext = val;
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
      //boost::shared_ptr<DataHandlerDependencies> mDeps;

      //IpcMemoryChecker mIpcMemoryChecker;

      ContextPtr mIpcContext;

      // following 3 members used to be dependencies
      //! \brief parse a soap message to find out information about the service been invoked
      IpcServiceInfoReaderFromIpcSoapPtr mServiceInfoReader;

      //! \brief can read soap message body and create invocation data
      //SCABodyDeserializerPtr mSCABodyDeserializer;

      //! \brief a wrapper around the Invocation layer. can invoke a method
      InvokerProxyPtr mInvokerProxy;

      std::string mBindingId;

      public:
      boost::interprocess::managed_shared_memory* mManaged_shm;

   };//end class DataHandler

}//namespace IPC
}//namespace Binding
}//namespace Trentino


#endif //TrentinoBindingIPCDataHandlerH

