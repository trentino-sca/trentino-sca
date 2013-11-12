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

#include "TrentinoBindingIpcClientBindingTransport.h"


//specific
#include "../BindingIpcServer/TrentinoBindingIpcMemoryMapObj.h"
#include "TrentinoBindingIpcClientCommon.h"

using namespace std; 
using namespace Trentino::Binding::IPC::Client;
using namespace Trentino::Binding::IPC;

string Trentino::Binding::IPC::Client::BindingIpcClientTransport::mFulldestination;

// The ipc shared memory, condition, lock and mutex variables are initialized at the start up of the transport 
// Intead of doing it for each send repetetively.
BindingIpcClientTransport::BindingIpcClientTransport(const char* host)
   :mConditionClientData(boost::interprocess::open_or_create, "cndClientData"),
   mNamed_mtx(boost::interprocess::open_or_create, "mtx"),
   mConditionServerData(boost::interprocess::open_or_create, "cndServerData"),
   mLock(mNamed_mtx)
{
  //read the config file
	int iShm = Trentino::Binding::IPC::Client::TrentinoBindingIpcClientCommon::getInstance().getSharedMemorySize();	
   // 3178 is a key to identify the shared memory could be changed possibly with a more unique identifier
	mManaged_shm = boost::interprocess::managed_shared_memory(boost::interprocess::open_or_create, "3178", iShm);
	mFulldestination = host;
}

BindingIpcClientTransport::~BindingIpcClientTransport()
{
   bool stat;
   stat = mManaged_shm.destroy<IpcSoapMsg>("IpcSoapMsgReq");
}


void BindingIpcClientTransport::send(Trentino::Binding::IPC::IpcMemoryMapObj* memMappedObj, const char* action, const char* from )
{
   try
   {
      std::string actionExtended = mFulldestination;
      actionExtended +="/";
      actionExtended += action;
      std::pair<IpcSoapMsg*, std::size_t> p = mManaged_shm.find<IpcSoapMsg>("IpcSoapMsgReq"); 
      bool stat = true;


	   if((p.first) != NULL)
	   {
	      stat = mManaged_shm.destroy<IpcSoapMsg>("IpcSoapMsgReq"); 
	   }
         
  
      IpcSoapMsg* ipcSoapMsgPtr = mManaged_shm.construct<IpcSoapMsg>("IpcSoapMsgReq")(mManaged_shm, actionExtended, from, mFulldestination);
      
      ipcSoapMsgPtr->envelope_mutable().body_mutable().setMemMappedObj(memMappedObj);

      std::cout << ipcSoapMsgPtr->envelope().header().addressing().mFrom << std::endl; 
      std::cout << ipcSoapMsgPtr->envelope().header().addressing().mAction << std::endl; 
      std::cout << ipcSoapMsgPtr->envelope().header().addressing().mTo << std::endl; 

      mConditionClientData.notify_all(); 
      mConditionServerData.wait(mLock);
   }
   catch (...)
   {
      //managed_shm.destroy<Trentino::Example::BasicCalculatorRemote::IpcMemoryMapObj_addSimple>("MemMappedTest");
   }
}
