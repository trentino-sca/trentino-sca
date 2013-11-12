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
#include "TrentinoRuntimeServiceControl.h"

// ************************************************************************************************
//! \todo
//! This is the implentation for the TrentinoRuntimeServiceControl. Currently it's
//! correctly implemented for Windows OS only, but to have console compiled for Linux
//! some implementation for Linux is needed. To provide working code ASAP lets use
//! this file for Linux code and separate OS specific sections by #ifdef.
// ************************************************************************************************
#if defined(WIN32)

//standard
#include <aclapi.h>
#include <sstream>

#define SVCNAME TEXT("TrentinoRuntimeService")

static SC_HANDLE handleSCManager;
static SC_HANDLE handleService;

using namespace std;
using namespace Trentino;
using Trentino::RuntimeServiceControl;

static bool WINAPI stopDependentServices()
{
   const DWORD dwTimeout = 30000; // 30-second time-out

   DWORD bytesNeeded;
   DWORD count;
   LPENUM_SERVICE_STATUS   dependencies = 0;
   DWORD startTime = GetTickCount();

   // Pass a zero-length buffer to get the required buffer size.
   if ( EnumDependentServices(
            handleService,
            SERVICE_ACTIVE, 
            dependencies,
            0,
            &bytesNeeded,
            &count ) ) 
   {
      // If the Enum call succeeds, then there are no dependent
      // services, so do nothing.
      return TRUE;
   } 
   else 
   {
      if ( GetLastError() != ERROR_MORE_DATA )
         return FALSE; // Unexpected error

      // Allocate a buffer for the dependencies.
      dependencies = (LPENUM_SERVICE_STATUS) HeapAlloc( 
                                                GetProcessHeap(),
                                                HEAP_ZERO_MEMORY,
                                                bytesNeeded );

      if ( !dependencies )
         return FALSE;

      __try {
         // Enumerate the dependencies.
         if ( !EnumDependentServices(
                  handleService,
                  SERVICE_ACTIVE, 
                  dependencies,
                  bytesNeeded,
                  &bytesNeeded,
                  &count ) )
            return FALSE;

         DWORD i;
         for ( i = 0; i < count; i++ ) 
         {
            ENUM_SERVICE_STATUS ess;
            ess = *(dependencies + i);

            SC_HANDLE depService;
            // Open the service.
            depService = OpenService(
                           handleSCManager, 
                           ess.lpServiceName, 
                           SERVICE_STOP | SERVICE_QUERY_STATUS );

            if ( !depService )
               return FALSE;

            SERVICE_STATUS_PROCESS  ssp;
            __try {
               // Send a stop code.
               if ( !ControlService(
                        depService, 
                        SERVICE_CONTROL_STOP,
                        (LPSERVICE_STATUS) &ssp ) )
                  return FALSE;

               // Wait for the service to stop.
               while ( ssp.dwCurrentState != SERVICE_STOPPED ) 
               {
                  Sleep( ssp.dwWaitHint );
                  if ( !QueryServiceStatusEx( 
                           depService, 
                           SC_STATUS_PROCESS_INFO,
                           (LPBYTE)&ssp, 
                           sizeof(SERVICE_STATUS_PROCESS),
                           &bytesNeeded ) )
                     return FALSE;

                  if ( ssp.dwCurrentState == SERVICE_STOPPED )
                     break;

                  if ( GetTickCount() - startTime > dwTimeout )
                     return FALSE;
               }
            } 
            __finally 
            {
               // Always release the service handle.
               CloseServiceHandle( depService );
            }
         }
      } 
      __finally 
      {
         // Always free the enumeration buffer.
         HeapFree( GetProcessHeap(), 0, dependencies );
      }
   } 
   return TRUE;
}

// Starts the service if possible.
void WINAPI RuntimeServiceControl::start()
{
   // Get a handle to the SCM database. 
   handleSCManager = OpenSCManager( 
      0,                       // local computer
      0,                       // servicesActive database 
      SC_MANAGER_ALL_ACCESS);  // full access rights 

   if ( handleSCManager == 0 ) 
   {
      mErrorMessage = "OpenSCManager failed";
      mErrorCode = GetLastError();
      return;
   }

   // Get a handle to the service.
   handleService = OpenService( 
      handleSCManager,         // SCM database 
      SVCNAME,              // name of service 
      SERVICE_ALL_ACCESS);  // full access 

   if ( handleService == 0 )
   { 
      mErrorMessage = "OpenService failed";
      mErrorCode = GetLastError(); 
      CloseServiceHandle(handleSCManager);
      return;
   }    

   SERVICE_STATUS_PROCESS serviceStatus; 
   DWORD bytesNeeded;

   // Check the status in case the service is not stopped. 
   if ( !QueryServiceStatusEx( 
      handleService,                     // handle to service 
      SC_STATUS_PROCESS_INFO,         // information level
      (LPBYTE) &serviceStatus,             // address of structure
      sizeof(SERVICE_STATUS_PROCESS), // size of structure
      &bytesNeeded ) )              // size needed if buffer is too small
   {
      mErrorMessage = "QueryServiceStatusEx failed";
      mErrorCode = GetLastError();
      CloseServiceHandle(handleService); 
      CloseServiceHandle(handleSCManager);
      return; 
   }

   // Check if the service is already running. It would be possible 
   // to stop the service here, but for simplicity this example just returns. 
   if((serviceStatus.dwCurrentState != SERVICE_STOPPED) &&
      (serviceStatus.dwCurrentState != SERVICE_STOP_PENDING))
   {
      mErrorMessage = "Cannot start the service because it is already running.";
      CloseServiceHandle(handleService); 
      CloseServiceHandle(handleSCManager);
      return; 
   }

   // Save the tick count and initial checkpoint.
   DWORD startTickCount = GetTickCount();
   DWORD oldCheckPoint = serviceStatus.dwCheckPoint;
   DWORD waitTime;

   // Wait for the service to stop before attempting to start it.
   while ( serviceStatus.dwCurrentState == SERVICE_STOP_PENDING )
   {
      // Do not wait longer than the wait hint. A good interval is 
      // one-tenth of the wait hint but not less than 1 second  
      // and not more than 10 seconds. 

      waitTime = serviceStatus.dwWaitHint / 10;

      if ( waitTime < 1000 )
         waitTime = 1000;
      else if ( waitTime > 10000 )
         waitTime = 10000;

      Sleep( waitTime );

      // Check the status until the service is no longer stop pending. 
      if ( !QueryServiceStatusEx( 
               handleService,                     // handle to service 
               SC_STATUS_PROCESS_INFO,            // information level
               (LPBYTE) &serviceStatus,                // address of structure
               sizeof(SERVICE_STATUS_PROCESS),    // size of structure
               &bytesNeeded ) )                 // size needed if buffer is too small
      {
         mErrorMessage = "QueryServiceStatusEx failed";
         mErrorCode = GetLastError();
         CloseServiceHandle(handleService); 
         CloseServiceHandle(handleSCManager);
         return; 
      }

      if ( serviceStatus.dwCheckPoint > oldCheckPoint )
      {
         // Continue to wait and check.

         startTickCount = GetTickCount();
         oldCheckPoint = serviceStatus.dwCheckPoint;
      }
      else
      {
         if ( GetTickCount() - startTickCount > serviceStatus.dwWaitHint )
         {
            mErrorMessage = "Timeout waiting for service to stop";
            CloseServiceHandle(handleService); 
            CloseServiceHandle(handleSCManager);
            return; 
         }
      }
   }

   // Attempt to start the service.
   if ( !StartService(
            handleService,  // handle to service 
            0,              // number of arguments 
            0) )            // no arguments 
   {
      mErrorMessage = "StartService failed";
      mErrorCode = GetLastError();
      CloseServiceHandle(handleService); 
      CloseServiceHandle(handleSCManager);
      return; 
   }

   // Check the status until the service is no longer start pending. 
   if ( !QueryServiceStatusEx( 
      handleService,                  // handle to service 
      SC_STATUS_PROCESS_INFO,         // info level
      (LPBYTE)&serviceStatus,         // address of structure
      sizeof(SERVICE_STATUS_PROCESS), // size of structure
      &bytesNeeded ) )              // if buffer too small
   {
      mErrorMessage = "QueryServiceStatusEx failed";
      mErrorCode = GetLastError();
      CloseServiceHandle(handleService); 
      CloseServiceHandle(handleSCManager);
      return; 
   }

   // Save the tick count and initial checkpoint.
   startTickCount = GetTickCount();
   oldCheckPoint = serviceStatus.dwCheckPoint;

   while ( serviceStatus.dwCurrentState == SERVICE_START_PENDING ) 
   { 
      // Do not wait longer than the wait hint. A good interval is 
      // one-tenth the wait hint, but no less than 1 second and no 
      // more than 10 seconds. 

      waitTime = serviceStatus.dwWaitHint / 10;
         
      if ( waitTime < 1000 )
         waitTime = 1000;
      else if ( waitTime > 10000 )
         waitTime = 10000;

      Sleep( waitTime );

      // Check the status again. 
      if ( !QueryServiceStatusEx( 
               handleService,                  // handle to service 
               SC_STATUS_PROCESS_INFO,         // info level
               (LPBYTE) &serviceStatus,        // address of structure
               sizeof(SERVICE_STATUS_PROCESS), // size of structure
               &bytesNeeded ) )                // if buffer too small
      {
         mErrorMessage = "QueryServiceStatusEx failed";
         mErrorCode = GetLastError();
         break; 
      }

      if ( serviceStatus.dwCheckPoint > oldCheckPoint )
      {
         // Continue to wait and check.
         startTickCount = GetTickCount();
         oldCheckPoint = serviceStatus.dwCheckPoint;
      }
      else
      {
         if( GetTickCount() - startTickCount > serviceStatus.dwWaitHint )
         {
            // No progress made within the wait hint.
            break;
         }
      }
   } 

   // Determine whether the service is running.
   if ( serviceStatus.dwCurrentState == SERVICE_RUNNING )
   {
      ostringstream out;
      out << "Service not started.\n" << endl
         << "  Current State: " + serviceStatus.dwCurrentState << endl 
         << "  Exit Code: " << serviceStatus.dwWin32ExitCode << endl 
         << "  Check Point: " << serviceStatus.dwCheckPoint << endl 
         << "  Wait Hint: " << serviceStatus.dwWaitHint << endl;
      mErrorMessage = out.str();
   } 

   CloseServiceHandle(handleService); 
   CloseServiceHandle(handleSCManager);
}

void WINAPI RuntimeServiceControl::updateServiceDACL()
{
   // Get a handle to the SCM database. 
   handleSCManager = OpenSCManager( 
                        0,                       // local computer
                        0,                       // ServicesActive database 
                        SC_MANAGER_ALL_ACCESS);  // full access rights 

   if ( handleSCManager == 0 ) 
   {
      mErrorMessage = "OpenSCManager failed";
      mErrorCode = GetLastError();
      return;
   }

   // Get a handle to the service
   handleService = OpenService( 
                     handleSCManager,           // SCManager database 
                     SVCNAME,                   // name of service 
                     READ_CONTROL | WRITE_DAC); // access

   if ( handleService == 0 )
   { 
      mErrorMessage = "OpenService failed";
      mErrorCode = GetLastError(); 
      CloseServiceHandle(handleSCManager);
      return;
   }    

   PSECURITY_DESCRIPTOR psd = 0;
   DWORD bytesNeeded = 0;
   PACL newAcl = NULL;

   // Get the current security descriptor.
   if ( !QueryServiceObjectSecurity(
            handleService,
            DACL_SECURITY_INFORMATION, 
            &psd,                       // using NULL does not work on all versions
            0, 
            &bytesNeeded ) )
   {
      DWORD size = 0;
      if ( GetLastError() == ERROR_INSUFFICIENT_BUFFER )
      {
         size = bytesNeeded;
         psd = (PSECURITY_DESCRIPTOR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
         if ( psd == NULL )
         {
            // Note: HeapAlloc does not support GetLastError.
            mErrorMessage = "HeapAlloc failed";
            goto dacl_cleanup;
         }

         if ( !QueryServiceObjectSecurity(
                  handleService,
                  DACL_SECURITY_INFORMATION,
                  psd,
                  size,
                  &bytesNeeded ) )
         {
            mErrorMessage = "QueryServiceObjectSecurity failed";
            mErrorCode = GetLastError();
            goto dacl_cleanup;
         }
      }
      else 
      {
         mErrorMessage = "QueryServiceObjectSecurity failed";
         mErrorCode = GetLastError();
         goto dacl_cleanup;
      }
   }

   PACL pacl = NULL;
   BOOL daclPresent = FALSE;
   BOOL daclDefaulted = FALSE;
   // Get the DACL.
   if ( !GetSecurityDescriptorDacl(psd, &daclPresent, &pacl, &daclDefaulted) )
   {
      mErrorMessage = "GetSecurityDescriptorDacl failed";
      mErrorCode = GetLastError();
      goto dacl_cleanup;
   }

   EXPLICIT_ACCESS ea;
   // Build the ACE.
   BuildExplicitAccessWithName(
      &ea,
      TEXT("GUEST"),
      SERVICE_START | SERVICE_STOP | READ_CONTROL | DELETE,
      SET_ACCESS, NO_INHERITANCE);

   DWORD error = 0;
   error = SetEntriesInAcl(1, &ea, pacl, &newAcl);
   if (error != ERROR_SUCCESS)
   {
      mErrorMessage = "SetEntriesInAcl failed";
      mErrorCode = error;
      goto dacl_cleanup;
   }

   SECURITY_DESCRIPTOR  sd;
   // Initialize a new security descriptor.
   if ( !InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION) )
   {
      mErrorMessage = "InitializeSecurityDescriptor failed";
      mErrorCode = GetLastError();
      goto dacl_cleanup;
   }

   // Set the new DACL in the security descriptor.
   if ( !SetSecurityDescriptorDacl(&sd, TRUE, newAcl, FALSE) )
   {
      mErrorMessage = "SetSecurityDescriptorDacl failed";
      mErrorCode = GetLastError();
      goto dacl_cleanup;
   }

   // Set the new DACL for the service object.
   if ( !SetServiceObjectSecurity(handleService, DACL_SECURITY_INFORMATION, &sd) )
   {
      mErrorMessage = "SetServiceObjectSecurity failed";
      mErrorCode = GetLastError();
      goto dacl_cleanup;
   }

dacl_cleanup:
   CloseServiceHandle(handleSCManager);
   CloseServiceHandle(handleService);

   if( NULL != newAcl )
      LocalFree((HLOCAL)newAcl);
   if( NULL != psd )
      HeapFree(GetProcessHeap(), 0, (LPVOID)psd);
}

// Stops the service.
void WINAPI RuntimeServiceControl::stop()
{
   const DWORD timeout = 30000; // 30-second time-out
   DWORD startTime = GetTickCount();

   // Get a handle to the SCM database. 
   handleSCManager = OpenSCManager( 
                        NULL,                    // local computer
                        NULL,                    // ServicesActive database 
                        SC_MANAGER_ALL_ACCESS);  // full access rights 

   if ( NULL == handleSCManager ) 
   {
      mErrorMessage = "OpenSCManager failed";
      mErrorCode = GetLastError();
      return;
   }

   // Get a handle to the service.
   handleService = OpenService( 
      handleSCManager,         // SCM database 
      SVCNAME,            // name of service 
      SERVICE_STOP | 
      SERVICE_QUERY_STATUS | 
      SERVICE_ENUMERATE_DEPENDENTS);  

   if ( handleService == NULL )
   { 
      mErrorMessage = "OpenService failed";
      mErrorCode = GetLastError(); 
      CloseServiceHandle(handleSCManager);
      return;
   }    

   SERVICE_STATUS_PROCESS ssp;
   DWORD bytesNeeded;

   // Make sure the service is not already stopped.
   if ( !QueryServiceStatusEx( 
            handleService, 
            SC_STATUS_PROCESS_INFO,
            (LPBYTE)&ssp, 
            sizeof(SERVICE_STATUS_PROCESS),
            &bytesNeeded ) )
   {
      mErrorMessage = "QueryServiceStatusEx failed";
      mErrorCode = GetLastError(); 
      goto stop_cleanup;
   }

   if ( ssp.dwCurrentState == SERVICE_STOPPED )
   {
      // Service is already stopped
      goto stop_cleanup;
   }

   DWORD waitTime;
   // If a stop is pending, wait for it.
   while ( ssp.dwCurrentState == SERVICE_STOP_PENDING ) 
   {
      // Do not wait longer than the wait hint. A good interval is 
      // one-tenth of the wait hint but not less than 1 second  
      // and not more than 10 seconds. 
      waitTime = ssp.dwWaitHint / 10;

      if ( waitTime < 1000 )
         waitTime = 1000;
      else if ( waitTime > 10000 )
         waitTime = 10000;

      Sleep( waitTime );

      if ( !QueryServiceStatusEx( 
               handleService, 
               SC_STATUS_PROCESS_INFO,
               (LPBYTE)&ssp, 
               sizeof(SERVICE_STATUS_PROCESS),
               &bytesNeeded ) )
      {
         mErrorMessage = "QueryServiceStatusEx failed";
         mErrorCode = GetLastError();
         goto stop_cleanup;
      }

      if ( ssp.dwCurrentState == SERVICE_STOPPED )
      {
         // Service stopped successfully
         goto stop_cleanup;
      }

      if ( GetTickCount() - startTime > timeout )
      {
         mErrorMessage = "Service stop timed out.";
         goto stop_cleanup;
      }
   }

   // If the service is running, dependencies must be stopped first.
   stopDependentServices();

   // Send a stop code to the service.
   if ( !ControlService( 
      handleService, 
      SERVICE_CONTROL_STOP, 
      (LPSERVICE_STATUS) &ssp ) )
   {
      mErrorMessage = "ControlService failed";
      mErrorCode = GetLastError();
      goto stop_cleanup;
   }

   // Wait for the service to stop.
   while ( ssp.dwCurrentState != SERVICE_STOPPED ) 
   {
      Sleep( ssp.dwWaitHint );
      if ( !QueryServiceStatusEx( 
               handleService, 
               SC_STATUS_PROCESS_INFO,
               (LPBYTE)&ssp, 
               sizeof(SERVICE_STATUS_PROCESS),
               &bytesNeeded ) )
      {
         mErrorMessage = "QueryServiceStatusEx failed";
         mErrorCode = GetLastError();
         goto stop_cleanup;
      }

      if ( ssp.dwCurrentState == SERVICE_STOPPED )
         break;

      if ( GetTickCount() - startTime > timeout )
      {
         mErrorMessage = "Wait timed out";
         goto stop_cleanup;
      }
   }

stop_cleanup:
   CloseServiceHandle(handleService); 
   CloseServiceHandle(handleSCManager);
}

#else

// Linux TrentinoRuntimeServiceControl implementation
using namespace std;
using namespace Trentino;
using Trentino::RuntimeServiceControl;

void RuntimeServiceControl::start() {}
void RuntimeServiceControl::stop() {}

#endif //WIN32