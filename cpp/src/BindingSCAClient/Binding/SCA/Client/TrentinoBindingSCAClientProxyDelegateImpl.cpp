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

#include "TrentinoBindingSCAClientProxyDelegateImpl.h"
//#include "TrentinoBindingSCAClientCommon.h"
//#include <zmq.hpp>
#include <Binding/CompactSoap/TrentinoBindingCompactSoapUtil.h>
#include <iostream>
#include "../Utils/TrentinoUtilsLogging.h"

using namespace std; 
using namespace Trentino::Binding::SCA::Client;
using namespace Trentino::Binding::CompactSoap;

//compact soap


using namespace Trentino::Binding::SCA;
using namespace trentino::bindingsca::csoap;

namespace 
   {

   bool hasEnding (std::string const &fullString, std::string const &ending)
      {
      if (fullString.length() >= ending.length()) 
         {
         return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
         } 
      else 
         {
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

   void createMessage(Soap& soapMsg, const ::google::protobuf::MessageLite* message, const char* action, const char* from ,const std::string& fullDestination )
      {
      Soap_Envelope* env = soapMsg.mutable_envelope();
      std::string serializedMsg;
      Soap_Body* bodyPtr;
      bodyPtr  = env->mutable_body();
      message->SerializeToString(&serializedMsg);
      bodyPtr->set_content(serializedMsg);
      createHeader(soapMsg, action, from,fullDestination);
      }  

   std::string createUserMessage(int errNum, const char* what){
      std::string prefix;
      switch(errNum){
         case EAGAIN:
            prefix ="[11]";
            break;
         case ECONNABORTED:
            prefix ="[103]";
            break;
         case ECONNRESET:
            prefix ="[104]";
            break;
         case ENOTCONN:
            prefix ="[107]";
            break;
         case ETIMEDOUT:
            prefix ="[110]";
            break;
         case ECONNREFUSED:
            prefix ="[111]";
            break;
         case ENETDOWN:
            prefix ="[112]";
            break;
         case EHOSTUNREACH:
            prefix="[113]";
            break;
         default:
            prefix ="[131]";
         }
      prefix+=": ";
      prefix+=what;
      return prefix;
      }


   void cleanUpSocket(ZMQSocketPtr& socket){
      socket->close();
      socket.reset();
      }

   zmq::socket_t* createSocket(zmq::context_t* context, std::string& host){
      zmq::socket_t* s = new zmq::socket_t(*context, ZMQ_REQ);
      int linger =  0;

      s->setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
      s->connect (host.c_str());
      return s;
      }
   }

//class definition
Trentino::Binding::SCA::Client::BindingProxyDelegateImpl::BindingProxyDelegateImpl(const char* host)
   {
   mFulldestination = std::string(host);
   std::string sep("/");
   if(hasEnding(mFulldestination,sep))
      {
      std::size_t pos = mFulldestination.find_last_of(sep);
      mFulldestination = mFulldestination.substr(0,pos);
      }
   std::size_t pos = mFulldestination.find_last_of(sep);
   pos = mFulldestination.find_last_of(sep,pos-1);
   mHost = mFulldestination.substr(0,pos);
   mContext = new zmq::context_t(1);
   mSocket.reset(createSocket(mContext,mHost));
   }

Trentino::Binding::SCA::Client::BindingProxyDelegateImpl::~BindingProxyDelegateImpl()
   {
   mSocket->close();
   mContext->close();
   delete  mContext;
   mSocket.reset();
   }

void Trentino::Binding::SCA::Client::BindingProxyDelegateImpl::send( const ::google::protobuf::MessageLite* message, trentino::bindingsca::csoap::Soap* response, const char* action, const char* from )
   {
   Soap request;
   createMessage(request,message, action, from,mFulldestination);
   int timeOutPeriod = 1000;//TrentinoBindingSCAClientCommon::getInstance().getTimeOutPeriod();
   zmq::message_t zRequest (request.ByteSize());
   CompactSoapUtil::toZMQMsg(&request,&zRequest);

   bool expectReply = true;

   // create socket
   //zmq::socket_t mSocket(*mContext, ZMQ_REQ);
   //int linger =  0;

   //mSocket.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
   //mSocket.connect (mHost.c_str());
   //preapre socket
   if(mSocket.get() == nullptr){
      mSocket.reset(createSocket(mContext,mHost));
      }

   try{
      mSocket->send (zRequest,1);
      zmq::pollitem_t items[] = { { *mSocket, 0, ZMQ_POLLIN, 0 } };
      zmq::poll (items, 1, timeOutPeriod);

      if (items[0].revents & ZMQ_POLLIN) 
         {
         zmq::message_t zReply;
         mSocket->recv (&zReply);
         CompactSoapUtil::fromZMQMsg(zReply, response);
         expectReply =  false;
         }
      }catch(zmq::error_t& error){
         logError(error.what());
         cleanUpSocket(mSocket);
         mSocket.reset(createSocket(mContext,mHost));
         std::string msg = createUserMessage(error.num(),error.what());
         throw runtime_error(msg);
      }
   if(expectReply)
      {
      int err_num = zmq_errno ();
      if(err_num ==0 ) {
         err_num =ETIMEDOUT;
         }

      std::string what;
      if(err_num == EAGAIN){
         what ="Resource at URL is temporally unavailable. Try again later: URL:"+mFulldestination +"/" + action;
         }else if(err_num == ETIMEDOUT) {
            what = "Remote procedure call client timeout for procedure: "+ mFulldestination +"/" + action
               +"\nMake sure that the server is available or increase time out.";
         }else {
            what = zmq_strerror(err_num);
            what+="\n";
            what+=mFulldestination +"/" + action;
            }
         cleanUpSocket(mSocket);
         mSocket.reset(createSocket(mContext,mHost));
         std::string msg = createUserMessage(err_num,what.c_str());
         throw runtime_error(msg);
      }
   }


