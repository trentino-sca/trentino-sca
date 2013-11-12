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

   //! a class that take care of deleting the worker thread
   struct WorkerDeleter{
      WorkerDeleter(Worker* w){worker = w;}
      ~WorkerDeleter(){if(worker!=nullptr) delete worker;}
      Worker* worker;
      };

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

   void work(Worker* worker){
      boost::scoped_ptr<Worker> wDel(worker);
      //WorkerDeleter wDel (worker);
      Socket mSocket(worker->mContext, ZMQ_REP);
      mSocket.connect (mWorkerDealerAddress);

      while (worker!=nullptr && !worker->mStop) {
         try{
            // Wait for next request from client
            zmq::message_t request;
            try{
               mSocket.recv (&request);
               }catch(zmq::error_t& e){
                  logError(e.what());
                  continue;
               }

            // Do some 'work'
            Soap soapRequest;
            Soap soapResponse;
            CompactSoapUtil::fromZMQMsg(request,&soapRequest);
            worker->mHandler->handle(soapRequest, soapResponse);
            zmq::message_t reply(soapResponse.ByteSize());
            CompactSoapUtil::toZMQMsg(&soapResponse,&reply);
               // Send reply back to client
               try{
               mSocket.send (reply);
                  }catch(zmq::error_t& e){
                     logError(e.what());
                  }
               }
         catch (std::exception& ex) {
            logError("Unexpected exception occured in Binding SCA '%s'",ex.what());
            //Fixme, how to copy a reference 
            }
         catch(boost::exception& ex)
            {
            std::string msg = boost::diagnostic_information(ex);
            logError("Unexpected exception occured in Binding SCA '%s'",msg);
            }
         catch (std::string& ex) {
            logError("Unexpected exception occured in Binding SCA '%s'",ex);
            }
         catch (...) {
            logError("Unexpected exception occured in Binding SCA");
            }
         } 
      }
   }



ZeroMqServer::ZeroMqServer(zmq::context_t& context, const Options options, const CompactSoapDataHandlerPtr& handler):
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
         stop();
      }

   void ZeroMqServer::start()
      {
   if(mStarted)
   {
         return;
         }
      mStarted =true;
      std::string host = getHostWithPort(mOptions);
      logInfo("Listening from host '%s'", host.c_str());
      mClients.bind (host.c_str());
      mThreadNumber = getIntOption(mOptions,mBindingScaMaxThreadNumber);
      mDealer.bind(mWorkerDealerAddress);
      // Launch pool of worker threads
   for(int threadNbr=0; threadNbr < mThreadNumber; threadNbr++)
   {
         Worker* w =new Worker(mHandler,mContext);
         mWorkers.push_back(w);
         }

      zmq_device(ZMQ_QUEUE, (void*)mClients, (void*)mDealer);
      //zmq_proxy((void*)mClients, (void*)mDealer,NULL);
      }


   bool ZeroMqServer::isStarted()
      {
      return mStarted;
      }


   void ZeroMqServer::stop()
      {
      if(mStoped)
         {
          return;
         }
      Workers::iterator it;
      mStoped = true;

      //close the sockets
      int linger =0;
   for(it = mWorkers.begin(); it!=mWorkers.end();++it)
   {
         Worker* worker = *it;
         worker->mStop = true;
         }
      mWorkers.clear();
      mClients.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
      mClients.close();
      mDealer.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
      mDealer.close();
      }


   //Clas Worker
   Trentino::Binding::SCA::Worker::Worker( CompactSoapDataHandlerPtr handler,zmq::context_t& context ) :
      mStop(false),
         mHandler(handler),
         mContext(context)
         {
         boost::thread workerThread(work, this);
         }
