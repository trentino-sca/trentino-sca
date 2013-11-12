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

#include "TrentinoBindingSCAClientProxyDelegate.h"
#include "TrentinoBindingSCAClientProxyDelegateImpl.h"
#include <Binding/CompactSoap/BindingCompactSoapProtobufMessages.h>
#include "../../../../Runtime/Binding/TrentinoBindingBindingManagerBase.h"



using namespace std; 
using namespace Trentino::Binding::SCA::Client;
using namespace Trentino::Binding::SCA;

Trentino::Binding::SCA::Client::BindingProxyDelegate::BindingProxyDelegate(const char* host)
{

   if (!Trentino::Binding::isFakeUri(host))
   {
     mInternalHandler.reset(new Trentino::Binding::SCA::Client::BindingProxyDelegateImpl(host));
   }

}

Trentino::Binding::SCA::Client::BindingProxyDelegate::~BindingProxyDelegate()
{
mInternalHandler.reset();
}



void BindingProxyDelegate::send(const ::google::protobuf::MessageLite* message, trentino::bindingsca::csoap::Soap* soap, const char* action, const char* from) const
{

   if( !mInternalHandler.get())
   {
      throw runtime_error("Service unavailable!");
   }
   else
   {
      mInternalHandler->send(message,soap,action,from);
   }
}

void Trentino::Binding::SCA::Client::BindingProxyDelegate::setHost(
      const char* host) {

   if (!mInternalHandler.get() && !Trentino::Binding::isFakeUri(host))
   {
      mInternalHandler.reset(new Trentino::Binding::SCA::Client::BindingProxyDelegateImpl(host));
   }


}


