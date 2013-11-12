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

//header
#include "TrentinoBindingSCAZeroMqServer.h"

//standard
#include <zmq.hpp>

using namespace Trentino::Binding::SCA;

namespace {

const char* mWorkerDealerAddress ="inproc://workers";
const char* mBindingScaPort= "binding.sca.port";
 const char* mBindingScaMaxThreadNumber= "binding.sca.thread.number";  
const char* getHostWithPort(const Options& options){
std::string res("tcp://*:");
      std::stringstream ss;
      ss << getIntOption(options,mBindingScaPort);
      res+=ss.str();
      return res;
}

   int getIntOption(Options& options, const char* optionName)
      {
      int result =-1;
      try{
         result = options[optionName].as<int>();
         }catch(...){
            logError("Integer Option %s not found using default value -1", optionName);
         }
      return result;
      }

}

namespace Trentino{
namespace Binding{
namespace SCA{

class Worker {

//construction
public:
Worker(ZeroMqServerPtr serverPtr):
mSocket(serverPtr->mContext, ZMQ_REP),
mServerPtr(serverPtr)
{}

//services
 void operator()(){
     mSocket.connect (mWorkerDealerAddress);
	 while (true) {
	// Wait for next request from client
	zmq::message_t request;
	mSocket.recv (&request);

	// Do some 'work'
	SoapPtr soapRequest = ZMQSOAPUTil::fromZMQMsg(request);
	//send an empty pointer. Message will be created by the handler
	SoapPtr soapResponse();
	mServerPtr->mHandler->handle(soapRequest, soapResponse);

	if(soapResponse)
	{
	zmq::message_t reply = ZMQSOAPUTil::toZMQMsg(soapResponse);

	} 

	// Send reply back to client
	zmq::message_t reply (6);
	memcpy ((void *) reply.data (), "World", 6);
	mSocket.send (reply);
	}
	return (NULL);
	}
 //data
private:
zmq::socket_t mSocket;
ZeroMqServerPtr mServerPtr
 };//class Worker 
 }
 }
 }

ZeroMqServer::ZeroMqServer(const Options options, const DataHandlerPtr& handler):
mOptions(options),
mHandler(handler),
,Started(false),
mContext(1),
mClients(mContext, ZMQ_ROUTER),
mWorkersSocket(mContext, ZMQ_DEALER)
{
}

ZeroMqServer::~ZeroMqServer()
{
}

void ZeroMqServer::start(){
const char* host = getHostWithPort(mOptions);
 mClients.bind (host);
 mThreadNumber = getIntOption(options,mBindingScaMaxThreadNumber);
 mWorkersSocket.bind(mWorkerDealerAddress);
 // Launch pool of worker threads
 for(int threadNbr=0; threadNbr != mThreadNumber; threadNbr++){
  Worker w(mContext, mHandler);  
  boost::thread workerThread(w);
  mWorkerThreads.push_back(workerThread);
 }
}