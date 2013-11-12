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
#include "TrentinoBindingIpcServer_DataHandlerTest.h"

//Standard
#include <fstream>
#include <vector>
#include <boost/system/error_code.hpp>
#include "boost/exception/detail/exception_ptr.hpp"
#include <boost/thread.hpp>

#include <boost/interprocess/managed_shared_memory.hpp> 
#include <boost/interprocess/sync/named_mutex.hpp> 
#include <boost/interprocess/sync/named_condition.hpp> 
#include <boost/interprocess/sync/scoped_lock.hpp> 
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/allocators/allocator.hpp> 
#include <boost/interprocess/containers/string.hpp> 

//tests
#include <gmock/gmock.h>
#include <gtest/gtest.h>

//Class used from a generated service header
#include"TrentinoExampleBasicCalculatorRemoteBasicCalculator.h"
#include "TrentinoGenIPCTypes.h"
//Class under test
#include "../../BindingIpcServer/TrentinoBindingIpcDataHandler.h"
#include "../../BindingIpcServer/TrentinoBindingIpcSoapMsg.h"
#include "../../BindingIpcServer/TrentinoBindingIpcMemoryMapObj.h"
#include "../../BindingIpcClient/TrentinoBindingIpcClientBindingTransport.h"


#include "../../Runtime/ServiceRegistry/TrentinoServiceRegistryServiceInfo.h"

#include "../../Utils/TrentinoUtilsURI.h"
#include "../../Runtime/Invocation/TrentinoInvocationInvocationData.h"
#include "../../BindingSCA/TrentinoBindingSCAContext.h"


using namespace Trentino::Binding::IPC;

/*
virtual Trentino::Example::BasicCalculatorRemote::BasicCalculator::ComplexNumber  add (const Trentino::Example::BasicCalculatorRemote::BasicCalculator::ComplexNumber& a,const Trentino::Example::BasicCalculatorRemote::BasicCalculator::ComplexNumber& b) =0;
virtual tint32_t  addSimple (const tint32_t a,const tint32_t b) =0;
virtual Trentino::Example::BasicCalculatorRemote::BasicCalculator::ComplexNumber  divide (const Trentino::Example::BasicCalculatorRemote::BasicCalculator::ComplexNumber& a,const Trentino::Example::BasicCalculatorRemote::BasicCalculator::ComplexNumber& b) =0;
virtual void  multiply (const Trentino::Example::BasicCalculatorRemote::BasicCalculator::ComplexNumber& a,const Trentino::Example::BasicCalculatorRemote::BasicCalculator::ComplexNumber& b, Trentino::Example::BasicCalculatorRemote::BasicCalculator::ComplexNumber& c) =0;
virtual Trentino::Example::BasicCalculatorRemote::BasicCalculator::ComplexNumber  divide2 (const Trentino::Example::BasicCalculatorRemote::BasicCalculator::TupleComplexNumber& tuple) =0;
virtual tuint32_t  calculateAge (const Trentino::Example::BasicCalculatorRemote::BasicCalculator::Person& person) throw (Trentino::Example::BasicCalculatorRemote::BasicCalculator::ValidationException)=0;*/

//**************************************************************************
//! Prepare test data to call: tint32_t  addSimple (const tint32_t a,const tint32_t b) =0;
//**************************************************************************
//TEST(DataHandlerbuildErrorResponse,SoapBodyAllwaysContainsAFAultMessage)
//{
//   boost::interprocess::shared_memory_object::remove("3178"); 
//   boost::interprocess::named_mutex::remove("mtx"); 
//   boost::interprocess::named_condition::remove("cndClientData");
//   boost::interprocess::named_condition::remove("cndServerData");
//
//   //Trentino::Binding::IPC::IpcMemoryChecker memchecker;
//   //memchecker.start();
//   DataHandlerIpc dataHandlerIpc;
//   dataHandlerIpc.start();
//   
//   // TODO fill corresponding MemMappedObj
//
//   boost::interprocess::named_condition cndClientData(boost::interprocess::open_or_create, "cndClientData"); 
//   boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx"); 
//   boost::interprocess::named_condition cndServerData(boost::interprocess::open_or_create, "cndServerData"); 
//   boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(named_mtx);
//
//
//
//   boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "3178", 1024); 
//   //int *i = managed_shm.construct<int>("Integer")(99); 
//   //i;
//   MemMappedTest* memMappedTest = managed_shm.construct<MemMappedTest>("MemMappedTest")();
//   //MemMappedTest* memMappedTest = new MemMappedTest();
//   memMappedTest->y = 102;
//   MemMappedTest* memMappedTest2 = managed_shm.construct<MemMappedTest>("MemMappedTest2")();
//   //MemMappedTest* memMappedTest = new MemMappedTest();
//   memMappedTest2->y = 202;
//   IpcSoapMsg* soapMsgPtr = managed_shm.construct<IpcSoapMsg>("IpcSoapMsg")();
//   soapMsgPtr->envelope_mutable().body_mutable().setMemMappedObj(memMappedTest);
//
//   soapMsgPtr->envelope_mutable().body_mutable().setMemMappedObj2(memMappedTest2);
//
//
//   //SoapMsgPtr ipcSoapMsgPt = IpcClientBindingHelper.prepareIpcSoap(memMappedAdd, "add", "BasicCalculatorRef");
//   //lock(IPM)
//   cndClientData.notify_all(); 
//   cndServerData.wait(lock);
//   //std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer");
//   int y = (static_cast<MemMappedTest*>(&(*soapMsgPtr->envelope_mutable().body_mutable().mMemoryMappedObj.get())))->y;
//   int z = (static_cast<MemMappedTest*>(&(*soapMsgPtr->envelope_mutable().body_mutable().mMemoryMappedObj2.get())))->y;
//   y;
//   z;
//   
//
//}
//
void createHeader( boost::interprocess::managed_shared_memory& managed_shm, IpcSoapMsg& /*soapMsg*/, const char* action, const char* from,const std::string& fullDestination )
{
   //IpcSoapHeader& header= soapMsg.envelope_mutable().header_mutable();
   //IpcSoapAddressing& addr = header.addressing_mutable();
   std::string actionExtended = fullDestination +"/" + action;
  from;
 
  string FileMeasure="Hello FILE!";
  int TempNumOne=FileMeasure.size();
  char Filename[100];
  int a;
  for (a=0;a<TempNumOne;a++)
  {
     Filename[a]=FileMeasure[a];
  } 

  Filename[a] = 0;
  std::string s = "akooo";
   std::string s3 = from;
  std::basic_string<char> s2(Filename);
  void_allocator alloc_inst (managed_shm.get_segment_manager());

  my_string deneme(s3.c_str(),alloc_inst);

  //soapMsg.envelope_mutable().header_mutable().addressing_mutable().mTo = managed_shm.find_or_construct<my_string>("mTo")(fullDestination.c_str(), managed_shm.get_segment_manager()); 
  //soapMsg.envelope_mutable().header_mutable().addressing_mutable().mFrom = managed_shm.find_or_construct<my_string>("mFrom")(s2.c_str(), managed_shm.get_segment_manager()); 
  //soapMsg.envelope_mutable().header_mutable().addressing_mutable().mAction = managed_shm.find_or_construct<my_string>("mAction")(Filename, managed_shm.get_segment_manager()); 
  //soapMsg.envelope_mutable().header_mutable().addressing_mutable().mAction(s3.c_str(),alloc_inst);

   //soapMsg.envelope_mutable().header_mutable().addressing_mutable().mFrom = Filename;

   //soapMsg.envelope_mutable().header_mutable().addressing_mutable().setAction(actionExtended.c_str());
   //soapMsg.envelope_mutable().header_mutable().addressing_mutable().set_to(fullDestination);
   //soapMsg.envelope_mutable().header_mutable().addressing_mutable().set_from(from);
   //soapMsg.envelope_mutable().header_mutable().addressing_mutable().y = 9;
   
   // soapMsg.envelope_mutable().header_mutable().addressing_mutable().mFromYeni2->insert(0,"ali");
   //soapMsg.envelope_mutable().header_mutable().addressing_mutable().mTo = "Weili";
}
//**************************************************************************
//! Prepare test data to call: tint32_t  addSimple (const tint32_t a,const tint32_t b) =0;
//**************************************************************************
TEST(DataHandlerbuildErrorResponse,AddSimple)
{
 
   boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "3178", 1024);
   boost::interprocess::named_condition cndClientData(boost::interprocess::open_or_create, "cndClientData"); 
   boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx"); 
   boost::interprocess::named_condition cndServerData(boost::interprocess::open_or_create, "cndServerData"); 
   boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(named_mtx);

   managed_shm.destroy<Trentino::Example::BasicCalculatorRemote::IpcMemoryMapObj_addSimple>("MemMappedTest");
   managed_shm.destroy<Trentino::Example::BasicCalculatorRemote::IpcMemoryMapObj_addSimple>("MemMappedTest123");
   managed_shm.destroy<Trentino::Example::BasicCalculatorRemote::IpcMemoryMapObj_addSimple>("MemMappedTest234");
   managed_shm.destroy<Trentino::Example::BasicCalculatorRemote::IpcMemoryMapObj_addSimple>("MemMappedTest567");

   try
   {
  
      Trentino::Example::BasicCalculatorRemote::IpcMemoryMapObj_addSimple* addSimpleReq = managed_shm.construct< Trentino::Example::BasicCalculatorRemote::IpcMemoryMapObj_addSimple>("MemMappedTest123")();
      //tint32_t* intA = managed_shm.construct<tint32_t>("MemMappedTest234")();
      //*intA = 102;
      //tint32_t* intB = managed_shm.construct<tint32_t>("MemMappedTest567")();
      //*intB = 202;
      addSimpleReq->set_a(104);
      addSimpleReq->set_b(107);
      
      std::string actionExtended = "ipc://3178/BasicCalculatorImpl/BasicCalculator";
      actionExtended +="/" ;
      actionExtended += "addSimple";
      managed_shm.destroy<int>("IpcSoapMsg"); 
      IpcSoapMsg* ipcSoapMsgPtr = managed_shm.construct<IpcSoapMsg>("IpcSoapMsgReq")(managed_shm,actionExtended,"BasicCalculatorRef","ipc://3178/BasicCalculatorImpl/BasicCalculator");
      
      //my_string*  mActionPtr = managed_shm.find_or_construct<my_string>("mActionPtr")("addSimple", managed_shm.get_segment_manager());
      //my_string* mFromPtr = managed_shm.find_or_construct<my_string>("mFromPtr")("Basic", managed_shm.get_segment_manager());
      //my_string* mToPtr = managed_shm.find_or_construct<my_string>("mToPtr")("ipc://3178/BasicCalculatorImpl/BasicCalculator", managed_shm.get_segment_manager());
      //mFromPtr->insert(5,"CalculatorRef");
      //std::cout << *mFromPtr << std::endl; 

      //mActionPtr;
      //mFromPtr;
      //mToPtr;
      ipcSoapMsgPtr->envelope_mutable().body_mutable().setMemMappedObj(addSimpleReq);
  
       
      //IpcSoapMsg* ipcSoapMsgPtr = Trentino::Binding::IPC::Client::IpcClientBindingHelper::prepareIpcSoap(addSimpleReq, "addSimple", "BasicCalculatorRef","ipc://3178/BasicCalculatorImpl/BasicCalculator");
      
      std::cout << ipcSoapMsgPtr->envelope().header().addressing().mFrom << std::endl; 
      std::cout << ipcSoapMsgPtr->envelope().header().addressing().mAction << std::endl; 
      std::cout << ipcSoapMsgPtr->envelope().header().addressing().mTo << std::endl; 

      cndClientData.notify_all(); 
      cndServerData.wait(lock);

      tint32_t yy  = addSimpleReq->returnValue();
      yy;
      ////std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer");
      //int y = (static_cast<MemMappedTest*>(&(*soapMsgPtr->envelope_mutable().body_mutable().mMemoryMappedObj.get())))->y;
      //int z = (static_cast<MemMappedTest*>(&(*soapMsgPtr->envelope_mutable().body_mutable().mMemoryMappedObj2.get())))->y;

   }
   catch (...)
   {
         managed_shm.destroy<Trentino::Example::BasicCalculatorRemote::IpcMemoryMapObj_addSimple>("MemMappedTest");
   }
   

}



