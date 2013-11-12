//// **********************************************************************************
//// Trentino - A C++ based lightweight, non-invasive SCA runtime.
//// Copyright (C) Siemens AG, 2012
//// All Rights Reserved
//// http://trentino.sourceforge.net/
////
//// This library is free software; you can redistribute it and/or
//// modify it under the terms of the GNU Lesser General Public
//// License as published by the Free Software Foundation; either
//// version 2.1 of the License, or (at your option) any later version.
////
//// This library is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//// Lesser General Public License for more details.
////
//// You should have received a copy of the GNU Lesser General Public
//// License along with this library; if not, write to the Free Software
//// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//// **********************************************************************************
//
////header
//#include "TrentinoBindingIpcClientDataHandler.h"
//
////standard
//#include <boost/shared_ptr.hpp>
//#include <boost/thread.hpp>
//
//
////Logging
//#include "../Utils/TrentinoUtilsLogging.h"
//
////specific
//
////Ipc Binding specific
//#include "../BindingIpcServer/TrentinoBindingIpcFaultDetailBuilder.h"
//#include "TrentinoBindingIpcClientBindingHelper.h"
//
//
////runtime specific
//#include "../Runtime/RuntimeModel/TrentinoRuntimeModelService.h"
//#include "../Runtime/RuntimeModel/TrentinoRuntimeModel.h"
//#include "../Runtime/Invocation/TrentinoInvocationInvocationData.h"
//#include "../Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h"
//
//
//using namespace Trentino::Binding::IPC;
//using namespace  boost::system;
//
//
//   //void checkRequest(const SoapMsgPtr& request, Trentino::RuntimeModel::ErrorCode& ec)
//   //{
//   //   //if(!request)
//   //   //{
//   //   //   ec.assign(errc::bad_message,system_category());
//   //   //   std::string desc ("request is empty");
//   //   //   ec.setDescription(desc);
//   //   //   return;
//   //   //   
//   //   //}
//   //   //if(!request->has_envelope()){
//   //   //   ec.assign(errc::bad_message,system_category());
//   //   //   std::string desc ("message has no envelope");
//   //   //   ec.setDescription(desc);
//   //   //   return;
//   //   //   }
//   //   //const trentino::bindingsca::csoap::Soap_Envelope env = request->envelope();
//   //   //if(!env.has_header()){
//   //   //   ec.assign(errc::bad_message,system_category());
//   //   //   std::string desc ("message has no header");
//   //   //   ec.setDescription(desc);
//   //   //   return;
//   //   //   }
//   //   //}
//   //}
//Trentino::Binding::IPC::Client::IpcDataHandlerClient::IpcDataHandlerClient()
//{
//
//   boost::thread t(boost::ref(*this));
//
//}
//
//void Trentino::Binding::IPC::Client::IpcDataHandlerClient::dataToResponse(const IpcSoapMsg& request) const
//{
//   request;
//   // read the filled response 
//
//}
//
//
//
//
//
//void Trentino::Binding::IPC::Client::IpcDataHandlerClient::checkMemory()
//{
//   boost::interprocess::named_condition cndClientData(boost::interprocess::open_or_create, "cndClientData"); 
//   boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx"); 
//   boost::interprocess::named_condition cndServerData(boost::interprocess::open_or_create, "cndServerData"); 
//   boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(named_mtx);
//
//   while(true)
//   {
//      cndServerData.wait(lock);
//
//      //string serviceInfo = unmapServiceInfo();
//      //dataToResponse(serviceInfo);
//      //boost::interprocess::scoped_lock<boost::interprocess::named_mutex> unlock(named_mtx);
//      cndClientData.notify_all(); 
//      boost::this_thread::interruption_point();
//   }
//}
//
//// Operator() called by the thread
//void Trentino::Binding::IPC::Client::IpcDataHandlerClient::operator () ()
//{
//   checkMemory();
//   boost::this_thread::yield(); 
//}