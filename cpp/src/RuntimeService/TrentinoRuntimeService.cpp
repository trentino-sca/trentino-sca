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
#include "TrentinoRuntimeService.h"

//standard
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>

#pragma comment(lib, "advapi32.lib")

#define SVCNAME      TEXT("TrentinoRuntimeService")
#define SVC_ERROR    ((DWORD)0xC0020001L)

static SERVICE_STATUS svcStatus; 
static SERVICE_STATUS_HANDLE svcStatusHandle; 
static HANDLE svcStopEvent;

using namespace std;
using namespace Trentino;
using Trentino::RuntimeService;

// Sets the current service status and reports it to the SCM.
//
// Parameters:
//   dwCurrentState - The current state (see SERVICE_STATUS)
//   dwWin32ExitCode - The system error code
//   dwWaitHint - Estimated time for pending operation, 
//     in milliseconds
static void reportServiceStatus(DWORD currentState,
                                DWORD win32ExitCode,
                                DWORD waitHint)
{
   // Fill in the SERVICE_STATUS structure.
   svcStatus.dwCurrentState = currentState;
   svcStatus.dwWin32ExitCode = win32ExitCode;
   svcStatus.dwWaitHint = waitHint;

   if ( currentState == SERVICE_START_PENDING )
   {
      svcStatus.dwControlsAccepted = 0;
   } else
   {
      svcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
   }

   static DWORD checkPoint = 1;

   if ( (currentState == SERVICE_RUNNING) ||
        (currentState == SERVICE_STOPPED) )
   {
        svcStatus.dwCheckPoint = 0;
   } else
   {
      svcStatus.dwCheckPoint = checkPoint++;
   }

   // Report the status of the service to the SCM.
   SetServiceStatus( svcStatusHandle, &svcStatus );
}

// Logs messages to the event log
//
// Parameters:
//   szFunction - name of function that failed
// 
// Remarks:
//   The service must have an entry in the Application event log.
static void serviceReportEvent(LPTSTR function) 
{ 
   HANDLE eventSource;
   eventSource = RegisterEventSource(0, SVCNAME);

   if ( eventSource != 0 )
   {
      TCHAR buffer[80];
      StringCchPrintf(buffer, 80, TEXT("%s failed with %d"), function, GetLastError());

      LPCTSTR strings[2];
      strings[0] = SVCNAME;
      strings[1] = buffer;

      ReportEvent(
         eventSource,         // event log handle
         EVENTLOG_ERROR_TYPE, // event type
         0,                   // event category
         SVC_ERROR,           // event identifier
         0,                   // no security identifier
         2,                   // size of lpszStrings array
         0,                   // no binary data
         strings,             // array of strings
         0);                  // no binary data

      DeregisterEventSource(eventSource);
   }
}

// Called by SCM whenever a control code is sent to the service
// using the ControlService function.
//
// Parameters:
//   dwCtrl - control code
static void WINAPI serviceCtrlHandler(DWORD ctrl)
{
   // Handle the requested control code. 
   switch( ctrl ) 
   {  
      case SERVICE_CONTROL_STOP: 
         reportServiceStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);

         // Signal the service to stop.
         SetEvent(svcStopEvent);
         reportServiceStatus(svcStatus.dwCurrentState, NO_ERROR, 0);
         
         return;
 
      case SERVICE_CONTROL_INTERROGATE: 
         break; 
 
      default: 
         break;
   } 
}

// Main service loop
static void serviceWorker()
{
   // TO_DO: Declare and set any required variables.
   //   Be sure to periodically call ReportSvcStatus() with 
   //   SERVICE_START_PENDING. If initialization fails, call
   //   ReportSvcStatus with SERVICE_STOPPED.

   // Create an event. The control handler function, SvcCtrlHandler,
   // signals this event when it receives the stop control code.
   svcStopEvent = CreateEvent(
                         0,       // default security attributes
                         TRUE,    // manual reset event
                         FALSE,   // not signaled
                         0);      // no name

   if ( svcStopEvent == 0 )
   {
       reportServiceStatus( SERVICE_STOPPED, NO_ERROR, 0 );
       return;
   }

   // Report running status when initialization is complete.
   reportServiceStatus( SERVICE_RUNNING, NO_ERROR, 0 );

   // TO_DO: Perform work until service stops.
   bool cond = true;
   while ( cond )
   {
        // Check whether to stop the service.
       WaitForSingleObject(svcStopEvent, INFINITE);

       reportServiceStatus( SERVICE_STOPPED, NO_ERROR, 0 );
       return;
   }
}

// Entry point for the service
//
// Parameters:
//   dwArgc - Number of arguments in the lpszArgv array
//   lpszArgv - Array of strings. The first string is the name of
//     the service and subsequent strings are passed by the process
//     that called the StartService function to start the service.
static void WINAPI serviceMain(DWORD /*argc*/, LPTSTR* /*argv*/)
{
   // Register the handler function for the service
   svcStatusHandle = RegisterServiceCtrlHandler( 
                        SVCNAME, 
                        serviceCtrlHandler);

   if( !svcStatusHandle )
   { 
      serviceReportEvent(TEXT("RegisterServiceCtrlHandler")); 
      return; 
   } 

   // These SERVICE_STATUS members remain as set here
   svcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS; 
   svcStatus.dwServiceSpecificExitCode = 0;    

   // Report initial status to the SCM
   reportServiceStatus( SERVICE_START_PENDING, NO_ERROR, 3000 );

   // Perform service-specific initialization and work.
   serviceWorker();   
}

void RuntimeService::startDispatcher()
{
   SERVICE_TABLE_ENTRY dispatchTable[] = 
   { 
      { SVCNAME, (LPSERVICE_MAIN_FUNCTION) serviceMain }, 
      { 0, 0 } 
   }; 

   if ( !StartServiceCtrlDispatcher(dispatchTable) ) 
   { 
      serviceReportEvent(TEXT("StartServiceCtrlDispatcher")); 
   }
}

// Install a service in the SCM database
void RuntimeService::doInstall()
{
   TCHAR path[MAX_PATH];
   if( !GetModuleFileName( 0, path, MAX_PATH ) )
   {
      mErrorMessage = "Cannot install service";
      mErrorCode = GetLastError();
      return;
   }

   SC_HANDLE SCManager;
   // Get a handle to the SCM database. 
   SCManager = OpenSCManager(
                  0,                       // local computer
                  0,                       // ServicesActive database 
                  SC_MANAGER_ALL_ACCESS);  // full access rights 

   if ( SCManager == 0 ) 
   {
      mErrorMessage = "OpenSCManager failed";
      mErrorCode = GetLastError();
      return;
   }

   SC_HANDLE service;
   // Create the service
   service = CreateService( 
               SCManager,                 // SCM database 
               SVCNAME,                   // name of service 
               SVCNAME,                   // service name to display 
               SERVICE_ALL_ACCESS,        // desired access 
               SERVICE_WIN32_OWN_PROCESS, // service type 
               SERVICE_DEMAND_START,      // start type 
               SERVICE_ERROR_NORMAL,      // error control type 
               path,                      // path to service's binary 
               0,                         // no load ordering group 
               0,                         // no tag identifier 
               0,                         // no dependencies 
               0,                         // LocalSystem account 
               0);                        // no password 

   if ( service == 0 ) 
   {
      mErrorMessage = "CreateService failed ";
      mErrorCode = GetLastError();
      CloseServiceHandle(SCManager);
      return;
   }

   CloseServiceHandle(service); 
   CloseServiceHandle(SCManager);
}