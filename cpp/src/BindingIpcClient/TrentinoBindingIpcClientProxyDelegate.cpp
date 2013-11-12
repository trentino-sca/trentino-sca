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

#include "TrentinoBindingIPCClientProxyDelegate.h"
#include "TrentinoBindingIPCClientBindingTransport.h"

//#include "../../../../Runtime/Binding/TrentinoBindingBindingManagerBase.h"

using namespace std; 
using namespace Trentino::Binding::IPC::Client;
using namespace Trentino::Binding::IPC;

BindingProxyDelegateIPC::BindingProxyDelegateIPC(const char * host)
{
   mTransport.reset(new Trentino::Binding::IPC::Client::BindingIpcClientTransport(host));
}

BindingProxyDelegateIPC::~BindingProxyDelegateIPC()
{
   mTransport.reset();
}


void Trentino::Binding::IPC::Client::BindingProxyDelegateIPC::setHost(const char* host)
{
   if (!(mTransport.get()))
   {
      mTransport.reset(new Trentino::Binding::IPC::Client::BindingIpcClientTransport(host));
   }
}

void Trentino::Binding::IPC::Client::BindingProxyDelegateIPC::send(Trentino::Binding::IPC::IpcMemoryMapObj* memMappedObj, 
   const char* action, 
   const char* from ) const
{
   if(!mTransport.get())
   {
      throw runtime_error("Service unavailable!");
   }
   else
   {
      mTransport->send(memMappedObj, action, from);
   }
}
