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

#ifndef BindingCompactSoapProtobufMessagesH
#define BindingCompactSoapProtobufMessagesH

//standard
#include <boost/shared_ptr.hpp>
//specific
#include "BindingCompactSoapImportExport.h"
#pragma warning(push)
#pragma warning(disable:4512 4244 4127)
#include "compact_soap.pb.h"
#include "ws_addressing.pb.h"
#pragma warning(pop)
namespace Trentino{
namespace Binding{
namespace SCA{
   typedef ::google::protobuf::MessageLite Message;
   typedef boost::shared_ptr<Message> MessagePtr;
   typedef trentino::bindingsca::csoap::Soap SoapMessage;
   typedef boost::shared_ptr<trentino::bindingsca::csoap::Soap> SoapPtr;
         
}
}
}


#endif //BindingCompactSoapProtobufMessagesH
