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
#include "TrentinoInvocationRecoveryService.h"

//specific
#include "./../RuntimeModel/TrentinoRuntimeModelService.h"
#include "./../../Utils/TrentinoUtilsLogging.h"
#include "../Core/TrentinoCoreDomain.h"

using namespace Trentino::Invocation;

InvocationRecoveryService* InvocationRecoveryService::Instance = 0;

InvocationRecoveryService::InvocationRecoveryService()
{}

InvocationRecoveryService* InvocationRecoveryService::getInstance()
{
   if (Instance == 0)
   {
      Instance = new InvocationRecoveryService;
   }

   return Instance;
}

void InvocationRecoveryService::Recover(const Trentino::Invocation::InvocationData& data,
                                       unsigned int u)
{
   
   logError("System exception #%d happened during call the service with @name='%s'",
            u, data.targetService().c_str());

   logError("Runtime is shutting down");    
   Trentino::Core::Domain::onException();
   // NOTE: 
   // Currently there is no logic to process operating system exceptions. To prevent the Runtime of
   // executing maliscious code - lets stop it in infinite loop. The idea is to implement a global
   // service, which can be able to process such exceptions. So the call will look something like
   // following: bootstrapper->getHandler()->handleException(some_data); Where some data is
   // self-contained information about bad SCA artifact.
   //for(;;);
}

void InvocationRecoveryService::Recover(const Trentino::Invocation::InvocationData& data)
{

   logError("System exception happened during call the service with @name='%s'", data.targetService().c_str());

   logError("Runtime is shutting down");    
   Trentino::Core::Domain::onException();
   // NOTE: 
   // Currently there is no logic to process operating system exceptions. To prevent the Runtime of
   // executing maliscious code - lets stop it in infinite loop. The idea is to implement a global
   // service, which can be able to process such exceptions. So the call will look something like
   // following: bootstrapper->getHandler()->handleException(some_data); Where some data is
   // self-contained information about bad SCA artifact.
   //for(;;);
}