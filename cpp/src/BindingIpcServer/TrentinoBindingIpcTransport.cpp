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
#include "TrentinoBindingIpcTransport.h"


//Logging
#include "../Utils/TrentinoUtilsLogging.h"
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

#include <boost/filesystem/path.hpp>
#include "../Utils/TrentinoUtilsEnvironment.h"

using namespace Trentino::Binding::IPC;
IpcDataHandlerPtr BindingIpcServerTransport::mDataHandler;

namespace fs = boost::filesystem;

// function to work threaded
void BindingIpcServerTransport::checkMemory()
{
   //muge what if not remove and move it to constructor did not work
   boost::interprocess::shared_memory_object::remove(mMemoryID.c_str());
   boost::interprocess::named_mutex::remove("mtx"); 
   boost::interprocess::named_condition::remove("cndClientData");
   boost::interprocess::named_condition::remove("cndServerData");

   //read the config file to get the shared memory size
   mConfiguration.configOptions().add_options()("binding.ipc.sharedmemorysize", boost::program_options::value<int>()->default_value(1024));
   mConfiguration.parse(true);
   int iSharedMemorySize = mConfiguration.optionsMap()["binding.ipc.sharedmemorysize"].as<int>();
   //--end read

   boost::interprocess::managed_shared_memory mManaged_shm(boost::interprocess::open_or_create, mMemoryID.c_str(), iSharedMemorySize); 
   boost::interprocess::named_condition mConditionClientData(boost::interprocess::open_or_create, "cndClientData"); 
   boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx"); 
   boost::interprocess::named_condition mConditionServerData(boost::interprocess::open_or_create, "cndServerData"); 
   boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(named_mtx);
   while(true)
   {
      mConditionClientData.wait(lock);

      std::pair<IpcSoapMsg*, std::size_t> p = mManaged_shm.find<IpcSoapMsg>("IpcSoapMsgReq"); 
      
      std::pair<my_string*, std::size_t>  pair1 = mManaged_shm.find<my_string>("mActionPtr");
      std::pair<my_string*, std::size_t>  pair2 = mManaged_shm.find<my_string>("mFromPtr");
      std::pair<my_string*, std::size_t> pair3 = mManaged_shm.find<my_string>("mToPtr");
      
      IpcSoapMsg response(mManaged_shm, "", "", "");
      mDataHandler->handle(*(p.first), response, mManaged_shm);


      mConditionServerData.notify_all(); 
      boost::this_thread::interruption_point();
         
      //write the response back again to the share mem
   }

}
string BindingIpcServerTransport::configFilePath() const
{
   return ( fs::path(Trentino::Utils::Environment::executablePath()).parent_path() / fs::path("../cfg/Binding.conf") ).string();
}

BindingIpcServerTransport::BindingIpcServerTransport(string memoryID)
   :mConfiguration(configFilePath()),
   mStarted(false),
   mStoped(false),
   mMemoryID(memoryID)//,
   //mManaged_shm(boost::interprocess::open_or_create, "3178", 1024),
   //mConditionClientData(boost::interprocess::open_or_create, "cndClientData"),
   //mNamed_mtx(boost::interprocess::open_or_create, "mtx"),
   //mConditionServerData(boost::interprocess::open_or_create, "cndServerData"),
   //mLock(mNamed_mtx)
{
}

BindingIpcServerTransport::~BindingIpcServerTransport()
{
   boost::interprocess::shared_memory_object::remove(mMemoryID.c_str());
   boost::interprocess::named_mutex::remove("mtx"); 
   boost::interprocess::named_condition::remove("cndClientData");
   boost::interprocess::named_condition::remove("cndServerData");
}

void BindingIpcServerTransport::start()
{
   if(mStarted)
   {
      return;
   }
   boost::thread t(boost::ref(*this));
   mStarted =true;


}


bool BindingIpcServerTransport::isStarted()
{
   return mStarted;
}


void BindingIpcServerTransport::stop()
{

}

// Operator() called by the thread
void Trentino::Binding::IPC::BindingIpcServerTransport::operator () ()
{
   checkMemory();
   boost::this_thread::yield(); 
}
