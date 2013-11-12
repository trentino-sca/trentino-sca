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

//Logging
#include "../Utils/TrentinoUtilsLogging.h"
#include <boost/noncopyable.hpp>
#include <Binding/CompactSoap/TrentinoBindingCompactSoapUtil.h>

using namespace Trentino::Binding::SCA;
using namespace Trentino::Binding::CompactSoap;


namespace {

   const char* mWorkerDealerAddress ="inproc://workers";
   const char* mBindingScaPort= "binding.sca.port";
   const char* mBindingScaMaxThreadNumber= "binding.sca.thread.number";  


   int getIntOption(const Options& options, const char* optionName)
      {
      int result =-1;
      try{
         result = options[optionName].as<int>();
         }catch(...){
            logError("Integer Option %s not found using default value -1", optionName);
         }
      return result;
      }


   std::string getHostWithPort(const Options& options){
      std::string res("tcp://*:");
      std::stringstream ss;
      ss << getIntOption(options,mBindingScaPort);
      res+=ss.str();
      return res;
      }
   }


namespace Trentino{
   namespace Binding{
      namespace SCA{

         class Worker{

            //construction
         public:
            Worker(ZeroMqServerPtr serverPtr):
               mSocket(new Socket(serverPtr->mContext, ZMQ_REP)),
                  mServerPtr(serverPtr)
                  {
                  mServerPtr->mWorkerSockets.push_back(mSocket);
                  }

               //services
               void operator()(){
                  mSocket->connect (mWorkerDealerAddress);
                  while (!mServerPtr->mStoped) {
                     // Wait for next request from client
                     zmq::message_t request;
                     mSocket->recv (&request);

                     // Do some 'work'
                     SoapPtr soapRequest(new Soap);
                     CompactSoapUtil::fromZMQMsg(request,soapRequest.get());

                     SoapPtr soapResponse (new Soap);
                     mServerPtr->mHandler->handle(soapRequest, soapResponse);

                     if(soapResponse)
                        {
                        Trentino::Binding::CompactSoap::ZMQMessagePtr reply = new zmq::message_t(soapResponse->ByteSize());
                        CompactSoapUtil::toZMQMsg(soapResponse.get(),reply);
                        // Send reply back to client
                        mSocket->send (*reply);
                        } 

                     }
                  }
               //data
         private:
            ZeroMqServerPtr mServerPtr;
            SocketPtr mSocket;
            };//class Worker 

         }
      }
   }

ZeroMqServer::ZeroMqServer(zmq::context_t& context, const Options options, const ZeroMqDataHandlerPtr& handler):
   mOptions(options),
      mHandler(handler),
      mStarted(false),
      mStoped(false),
      mContext(context),
      mClients(mContext, ZMQ_ROUTER),
      mDealer(mContext, ZMQ_DEALER),
      mThreadNumber(1)
      {
      }

   ZeroMqServer::~ZeroMqServer()
      {
      }

   void ZeroMqServer::start()
      {
      if(mStarted){
         return;
         }
      mStarted =true;
      std::string host = getHostWithPort(mOptions);
      mClients.bind (host.c_str());
      mThreadNumber = getIntOption(mOptions,mBindingScaMaxThreadNumber);
      mDealer.bind(mWorkerDealerAddress);
      // Launch pool of worker threads
      for(int threadNbr=0; threadNbr < mThreadNumber; threadNbr++){
         Worker w(shared_from_this());  
         ThreadPtr workerThread ( new boost::thread(w));
         mWorkerThreads.push_back(workerThread);
         }
      zmq_device(ZMQ_QUEUE, (void*)mClients, (void*)mDealer);
      }


   bool ZeroMqServer::isStarted()
      {
      return mStarted;
      }


   void ZeroMqServer::stop()
      {
      Sockets::iterator it;
      mStoped = true;

      //close the sockets
      for(it = mWorkerSockets.begin(); it!=mWorkerSockets.end();++it){
         SocketPtr socket = *it;
         socket->close();
         }

      //stop the threads
      WorkerThreads::iterator tit;
      for(tit=mWorkerThreads.begin();tit!=mWorkerThreads.end();++tit){
         ThreadPtr wthread = *tit;
         try
            {
            wthread->interrupt();
            }
         catch (...)
            {
            logError("Error while interrupting socket thread");
            }

         }
      }
