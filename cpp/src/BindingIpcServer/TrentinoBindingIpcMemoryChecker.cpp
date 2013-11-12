//// **********************************************************************************
//// Trentino - A C++ based lightweight, non-invasive SCA runtime.
//// Copyright (C) Siemens AG, 2012
//// All Rights Reserved
//// http://trentino.sourceforge.net/
////
//// This library is free software; you can redistribute it and/or
//// modify it under the terms of the GNU Lesser General Public
//// License as published by the Free Software Foundation; either
//// version 2.1 of the License, or (at your option) any later version.
////
//// This library is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//// Lesser General Public License for more details.
////
//// You should have received a copy of the GNU Lesser General Public
//// License along with this library; if not, write to the Free Software
//// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//// **********************************************************************************
//
////header
//#include "TrentinoBindingIpcMemoryChecker.h"
//
//
////Logging
//#include "../Utils/TrentinoUtilsLogging.h"
//#include <boost/noncopyable.hpp>
//
//
//using namespace Trentino::Binding::IPC;
//
//namespace 
//{
//
//   const char* mWorkerDealerAddress ="inproc://workers";
//   const char* mBindingScaPort= "binding.sca.port";
//   const char* mBindingScaMaxThreadNumber= "binding.sca.thread.number";  
//
//int getIntOption(const Options& options, const char* optionName)
//{
//   int result =-1;
//   try{
//   result = options[optionName].as<int>();
//   }catch(...){
//   logError("Integer Option %s not found using default value -1", optionName);
//   }
//   return result;
//}
//
//
//std::string getHostWithPort(const Options& options)
//{
//   std::string res("tcp://*:");
//   std::stringstream ss;
//   ss << getIntOption(options,mBindingScaPort);
//   res+=ss.str();
//   return res;
//}
//
//void work(Worker* worker)
//{
//   Socket mSocket(worker->mContext, ZMQ_REP);
//   mSocket.connect (mWorkerDealerAddress);
//   while (!worker->mStop) 
//   {
//      // Wait for next request from client
//      zmq::message_t request;
//      try
//      {
//         mSocket.recv (&request);
//      }
//      catch(zmq::error_t& e)
//      {
//         logError(e.what());
//         continue;
//      }
//
//      // Do some 'work'
//      SoapPtr soapRequest(new Soap);
//      CompactSoapUtil::fromZMQMsg(request,soapRequest.get());
//
//      SoapPtr soapResponse (new Soap);
//      worker->mHandler->handle(soapRequest, soapResponse);
//      if(soapResponse)
//      {
//         Trentino::Binding::CompactSoap::ZMQMessagePtr reply = new zmq::message_t(soapResponse->ByteSize());
//         CompactSoapUtil::toZMQMsg(soapResponse.get(),reply);
//         // Send reply back to client
//         mSocket.send (*reply);
//      } 
//   }
//}// end of func work
//}
//
//
//IpcMemoryChecker::IpcMemoryChecker(zmq::context_t& context, const Options options, const IpcDataHandlerPtr& handler)
//   :mOptions(options),
//   mHandler(handler),
//   mStarted(false),
//   mStoped(false),
//   mClients(mContext, ZMQ_ROUTER),
//   mDealer(mContext, ZMQ_DEALER),
//   mThreadNumber(1)
//{
//}
//
//IpcMemoryChecker::~IpcMemoryChecker()
//{
//}
//
//void IpcMemoryChecker::start()
//{
//   if(mStarted)
//   {
//      return;
//   }
//   mStarted =true;
//   std::string host = getHostWithPort(mOptions);
//   mClients.bind (host.c_str());
//   mThreadNumber = getIntOption(mOptions,mBindingScaMaxThreadNumber);
//   mDealer.bind(mWorkerDealerAddress);
//   // Launch pool of worker threads
//   for(int threadNbr=0; threadNbr < mThreadNumber; threadNbr++)
//   {
//      WorkerPtr w (new Worker(mHandler,mContext));  
//      mWorkers.push_back(w);
//   }
//
//}
//
//
//bool IpcMemoryChecker::isStarted()
//{
//   return mStarted;
//}
//
//
//void IpcMemoryChecker::stop()
//{
//   Workers::iterator it;
//   mStoped = true;
//
//   //close the sockets
//   int linger =0;
//   for(it = mWorkers.begin(); it!=mWorkers.end();++it)
//   {
//      WorkerPtr worker = *it;
//      worker->mStop = true;;
//   }
//
//   mWorkers.clear();
//   mClients.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
//   mClients.close();
//   mDealer.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
//   mDealer.close();
//}
//
//
////Clas Worker
//Trentino::Binding::IPC::Worker::Worker( IpcDataHandlerPtr handler)
//   :mStop(false),
//   mHandler(handler),
//   mContext(context)
//{
//   boost::thread workerThread(work, this);
//}
//
//// Operator() called by the thread
//void operator () ()
//{
//   for (int i=0; i<m_iterations; i++)
//   {
//   cout<<i<<" - Do something in parallel (operator() )."<<endl;
//   boost::this_thread::yield(); // 'yield' discussed in section 18.6
//   }
//}
