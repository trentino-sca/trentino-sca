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
#ifndef TrentinoBindingIpcServiceInfoReaderFromIpcSoapH
#define TrentinoBindingIpcServiceInfoReaderFromIpcSoapH

#include "../Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h"
#include "../Runtime/RuntimeModel/TrentinoRuntimeModel.h"
#include "../Runtime/ServiceRegistry/ServiceRegistry.h"
#include"TrentinoBindingIpcSoapMsg.h"

namespace Trentino{
namespace Binding{
namespace IPC
{
      class IpcServiceInfoReaderFromIpcSoap;
      typedef boost::shared_ptr<IpcServiceInfoReaderFromIpcSoap> IpcServiceInfoReaderFromIpcSoapPtr;

      //********************************************************************************
      //                            ServiceInfoReaderImpl
      //********************************************************************************
      //! \brief main class responsible of reading a soap header and therefore determine
      //! attributes of the header that are relevant for the invocation.
      //! it is also the place where validation take place if the soap header is not valid/! \brief ServiceInfoReader implementation
      //********************************************************************************
      class /*BINDINGIPC_IMPORT_EXPORT*/ IpcServiceInfoReaderFromIpcSoap 
      {
         //constructor
      public:
         IpcServiceInfoReaderFromIpcSoap(){};
         virtual ~IpcServiceInfoReaderFromIpcSoap(){};
         //services
      public:
         virtual void readServiceInfo(const IpcSoapMsg& request,
            Trentino::ServiceRegistry::ServiceInfo& result,
            Trentino::RuntimeModel::ErrorCode& ec) const;
      }; //Class IpcServiceInfoReaderFromIpcSoap

}//namespace IPC
}//namespace Binding
}//namespace Trentino

#endif //TrentinoBindingIpcServiceInfoReaderFromIpcSoapH

