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
#ifndef TrentinoBindingIpcClientDataHandlerH
#define TrentinoBindingIpcClientDataHandlerH

//standard
#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>
#include <boost/interprocess/managed_shared_memory.hpp> 
#include <boost/interprocess/sync/named_mutex.hpp> 
#include <boost/interprocess/sync/named_condition.hpp> 
#include <boost/interprocess/sync/scoped_lock.hpp> 


#include <../Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h>
#include <../Runtime/RuntimeModel/TrentinoRuntimeModel.h>

//#include "TrentinoBindingIpcInvokerProxy.h"
#include "../BindingIpcServer/TrentinoBindingIpcServiceInfoReaderFromIpcSoap.h"
//#include "TrentinoBindingIpcContext.h"
#include "../BindingIpcServer/TrentinoBindingIpcMemoryMapObj.h"
#include "../BindingIpcServer/TrentinoBindingIpcSoapMsg.h"
#include "TrentinoBindingIpcClientDefs.h"

namespace Trentino{
namespace Binding{
namespace IPC{
namespace Client
{
   

   //*****************************************************************************
   //                            DataHandlerData
   //*****************************************************************************
   //! \brief that holds datas of a DataHandler
   //*****************************************************************************
   class BINDINGIPCCLIENT_IMPORT_EXPORT DataHandlerDependencies 
   {

      public:
      //services
      //! \brief parse a soap message to find out information about the service been invoked
      const IpcServiceInfoReaderFromIpcSoapPtr& serviceInfoReader() const
      {
         return mServiceInfoReader;
      }


      void setServiceInfoReader(IpcServiceInfoReaderFromIpcSoapPtr val) 
      { 
         mServiceInfoReader.swap(val);
      }

         
            
      const std::string bindingId()
      {
         return mBindingId;
      }

      void setBindingId(const std::string& bindingId)
      {
         mBindingId = bindingId;
      }
      //data
   private:

      //! \brief parse a soap message to find out information about the service been invoked
      IpcServiceInfoReaderFromIpcSoapPtr mServiceInfoReader;

      std::string mBindingId;

   };//class SCABindingDataHandlerDependencies



   //*****************************************************************************
   //                            SCABindingDataHandler
   //*****************************************************************************
   //! \brief main class that process incoming messages to response. 
   //! this class is independent of the Transport protocol, but still depend on 
   //! SCA Binding serialization mechanism
   //*****************************************************************************

   class BINDINGIPCCLIENT_IMPORT_EXPORT IpcDataHandlerClient
   {
      public:
      //construction
      IpcDataHandlerClient();

      void operator () ();

      //services
      public:
      void checkMemory();
      //****************************************************************************
      //                         dataToResponse()
      //****************************************************************************
      //! \brief given a data received from the transport layer, process the data and 
      //! call the invocation layer, transform the result of the invocation
      //! layer back to a message that is sent back to the client
      //****************************************************************************
      void dataToResponse(const IpcSoapMsg& request) const;

           
      void start()
      {

      }
      void stop()
      {

      }
      bool isStarted()
      {
         return true;
      }
   public:
      void setDependencies(const boost::shared_ptr<DataHandlerDependencies> deps)
      {
         mDeps = deps;
      }





   private:
     

      //data
      //! \brief all service dependencies bundled to simplify refactory and test
      boost::shared_ptr<DataHandlerDependencies> mDeps;


     /* boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx"); 

      boost::interprocess::named_condition named_cnd(boost::interprocess::open_or_create, "cnd"); 
       boost::interprocess::named_condition named_cnd2(boost::interprocess::open_or_create, "cnd2"); */

   };//end class DataHandler

}//namespace client
}//namespace IPC
}//namespace Binding
}//namespace Trentino


#endif //TrentinoBindingIPCDataHandlerH

