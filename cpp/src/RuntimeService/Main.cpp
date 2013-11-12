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

//specific
#include "TrentinoRuntimeService.h"

//standard
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>

#pragma comment(lib, "advapi32.lib")

using namespace Trentino;
using Trentino::RuntimeService;

// Microsoft Windows services, formerly known as NT services, enable you to create long-running
// executable applications that run in their own Windows sessions. These services can be
// automatically started when the computer boots, can be paused and restarted, and do not show
// any user interface.
//
// This application represents a Windows service with an empty body.
// Test procedure steps:
// 1. Install this service to the system SCM (must be done only once):
//    TrentinoRuntimeService.exe -install
// 2. Check that service is installed:
//    Go to Start -> Settings -> Control Panel -> Administrative Tools -> Services
//    and check that TrentinoRuntimeService presented here
// 3. Check that service can be started or stopped by clicking right mouse button on the service.

void __cdecl _tmain(int /*argc*/, TCHAR *argv[])
{
   RuntimeService service;

   // install the Trentino service to the SCM.
   // Must be executed only once before the first service start
   if( lstrcmpi( argv[1], TEXT("install")) == 0 )
    {
       service.doInstall();
       return;
    }

   // Windows service entry point.
   service.startDispatcher();
}