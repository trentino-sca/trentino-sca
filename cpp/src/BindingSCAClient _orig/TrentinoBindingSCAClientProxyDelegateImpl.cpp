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

#include "TrentinoBindingSCAClientProxyDelegateImpl.h"
#include <zmq.hpp>
#include <Binding/CompactSoap/TrentinoBindingCompactSoapUtil.h>
#include <iostream>

using namespace std; 
using namespace Trentino::Binding::SCA::Client;
using namespace Trentino::Binding::CompactSoap;

//compact soap


using namespace Trentino::Binding::SCA;
using namespace trentino::bindingsca::csoap;



namespace {

   bool hasEnding (std::string const &fullString, std::string const &ending)
      {
      if (fullString.length() >= ending.length()) {
         return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
         } else {
            return false;
         }
      }

   void createHeader(Soap& soapMsg, const char* action, const char* from,const std::string& fullDestination )
      {
      Soap_Header* header= soapMsg.mutable_envelope()->mutable_header();
      Addressing* addr = header->mutable_addressing();
      std::string actionExtended = fullDestination +"/" + action;
      addr->set_action(actionExtended.c_str());
      addr->set_to(fullDestination);
      addr->set_from(from);
      }
   }

//class definition
Trentino::Binding::SCA::Client::BindingProxyDelegateImpl::BindingProxyDelegateImpl(const char* host)
      {
      mFulldestination = std::string(host);
      std::string sep("/");
      if(hasEnding(mFulldestination,sep)){
         std::size_t pos = mFulldestination.find_last_of(sep);
         mFulldestination = mFulldestination.substr(0,pos);
      }
      std::size_t pos = mFulldestination.find_last_of(sep);
      pos = mFulldestination.find_last_of(sep,pos-1);
      mHost = mFulldestination.substr(0,pos);
      }


   void Trentino::Binding::SCA::Client::BindingProxyDelegateImpl::send( const ::google::protobuf::MessageLite* message, trentino::bindingsca::csoap::Soap* response, const char* action, const char* from ) const
      {
      Soap* soapMsg = new Soap;
      Soap_Envelope* env = soapMsg->mutable_envelope();
      std::string serializedMsg;
      Soap_Body* bodyPtr;
      bodyPtr  = env->mutable_body();
      message->SerializeToString(&serializedMsg);
      bodyPtr->set_content(serializedMsg);

      createHeader(*soapMsg, action, from,mFulldestination);
      //TODO serialize once again
      SoapPtr request(soapMsg);

      zmq::context_t context (1);
      zmq::socket_t socket (context, ZMQ_REQ);

      socket.connect (mHost.c_str());
      Trentino::Binding::CompactSoap::ZMQMessagePtr zRequest = new zmq::message_t(request->ByteSize());
      CompactSoapUtil::toZMQMsg(request.get(),zRequest);
      socket.send (*zRequest);
      zmq::message_t zReply;
      socket.recv (&zReply);
      CompactSoapUtil::fromZMQMsg(zReply, response);
      }


