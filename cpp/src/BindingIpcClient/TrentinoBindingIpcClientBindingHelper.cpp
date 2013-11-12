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

#include "TrentinoBindingIpcClientBindingHelper.h"

#include "../BindingIpcServer/TrentinoBindingIpcMemoryMapObj.h"


using namespace std; 
using namespace Trentino::Binding::IPC::Client;
using namespace Trentino::Binding::IPC;

std::string IpcClientBindingHelper::mFulldestination;
bool IpcClientBindingHelper::hasEnding (std::string const &fullString, std::string const &ending)
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

void IpcClientBindingHelper::createHeader(SoapMsgPtr soapMsgPtr, const char* action, const char* from,const std::string& fullDestination )
{
   std::string actionExtended = fullDestination +"/" + action;
   IpcSoapAddressing& addressing = soapMsgPtr->envelope_mutable().header_mutable().addressing_mutable();
   addressing.setAction(actionExtended.c_str());
   addressing.set_to(fullDestination);
   addressing.set_from(from);
}

void IpcClientBindingHelper::convertHostToFullDestination(const char* host)
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
}



SoapMsgPtr IpcClientBindingHelper::prepareIpcSoap(Trentino::Binding::IPC::IpcMemoryMapObj* message, const char* action, const char* from ) 
{
   boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024); 

   boost::shared_ptr<IpcSoapMsg> soapMsgPtr =  boost::shared_ptr<IpcSoapMsg>(managed_shm.construct<IpcSoapMsg>("IpcSoapMsg")());

   soapMsgPtr->envelope_mutable().body_mutable().setMemMappedObj(message);

   //SoapMsgPtr soapMsgPtr = SoapMsgPtr(new IpcSoapMsg());

   //IpcSoapEnvelope& env = soapMsgPtr->envelope_mutable();
   //IpcSoapBody& bodyPtr = env.body_mutable();
   //bodyPtr.setMemMappedObj(message);

   createHeader(soapMsgPtr, action, from,mFulldestination);
   
   return soapMsgPtr;
}


