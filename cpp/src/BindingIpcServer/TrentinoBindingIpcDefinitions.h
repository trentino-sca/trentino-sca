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

#ifndef TrentinoBindingIpcDefinitionsH
#define TrentinoBindingIpcDefinitionsH

//specific
#include "TrentinoBindingIPCImportExport.h"

namespace Trentino {
namespace Binding {
namespace IPC
{

   const char *const ACTION_STR = "Action";
   const char *const CLIENT_STR = "Client";
   const char *const REPLYTO_STR = "ReplyTo";

   class DataHandler;
   class BindingHelperIpc;
   class IpcSoapMsg;
   typedef boost::shared_ptr<DataHandler> DataHandlerPtr;
   typedef boost::shared_ptr<Trentino::Binding::IPC::BindingHelperIpc> BindingHelperIpcPtr;
   typedef boost::shared_ptr<Trentino::Binding::IPC::IpcSoapMsg> SoapPtr;
   class DataHandlerIpc;
   typedef boost::shared_ptr<Trentino::Binding::IPC::DataHandlerIpc> DataHandlerIpcPtr;
}// namespace IPC
} // namespace Binding
}// namespace Trentino


#endif //TrentinoBindingIpcDefinitionsH
