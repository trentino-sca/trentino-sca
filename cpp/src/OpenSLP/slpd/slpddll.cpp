extern "C"
{
#include "slpddll.h"
#include "slp_types.h"

#include "slpd_cmdline.h"
#include "slpd_log.h"
#include "slpd_property.h"
#include "slpd_database.h"
#include "slpd_socket.h"
#include "slpd_incoming.h"
#include "slpd_outgoing.h"
#include "slpd_knownda.h"
#include "slpd.h"

#include "slp_linkedlist.h"
#include "slp_xid.h"

#include <direct.h>

/*  internal and display names of the service  */
#define G_SERVICENAME         "slpd"    
#define G_SERVICEDISPLAYNAME  "Service Location Protocol"

SERVICE_STATUS ssStatus;       /* current status of the service  */
SERVICE_STATUS_HANDLE sshStatusHandle; 
BOOL bDebug = FALSE; 
TCHAR szErr[256];

/* externals (variables) from slpd_main.c */
extern int G_SIGALRM;
extern int G_SIGTERM;
extern int G_SIGHUP;
extern int G_SIGINT;

SC_HANDLE schService;

/* externals (functions) from slpd_main.c */
void LoadFdSets(SLPList * socklist, int * highfd, 
	  fd_set * readfds, fd_set * writefds);
void HandleSigTerm(void);
void HandleSigAlrm(void);

/** Reports the current status of the service to the SCM.
 *
 * @param[in] dwCurrentState - The state of the service.
 * @param[in] dwWin32ExitCode - The error code to report.
 * @param[in] dwWaitHint - Worst case estimate to next checkpoint.
 *
 * @return A boolean value; TRUE on success, FALSE on failure.
 *
 * @internal
 */
BOOL ReportStatusToSCMgr(DWORD dwCurrentState, 
	  DWORD dwWin32ExitCode, DWORD dwWaitHint) 
{
   static DWORD dwCheckPoint = 1; 
   BOOL fResult = TRUE; 

   /* when debugging we don't report to the SCM */
   if (G_SlpdCommandLine.action != SLPD_DEBUG)
   {
	  if (dwCurrentState == SERVICE_START_PENDING)
		 ssStatus.dwControlsAccepted = 0;
	  else
		 ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP; 

	  ssStatus.dwCurrentState = dwCurrentState; 
	  ssStatus.dwWin32ExitCode = dwWin32ExitCode; 
	  ssStatus.dwWaitHint = dwWaitHint; 

	  if (dwCurrentState == SERVICE_RUNNING 
			|| dwCurrentState == SERVICE_STOPPED)
		 ssStatus.dwCheckPoint = 0;
	  else
		 ssStatus.dwCheckPoint = dwCheckPoint++; 

	  /* report the status of the service to the service control manager.*/
	  if ((fResult = SetServiceStatus( sshStatusHandle, &ssStatus)) == 0)
		 SLPDLog("SetServiceStatus failed\n"); 
   }
   return fResult; 
} 

/** Copies error message text to a string.
 *
 * @param[out] lpszBuf - A destination buffer.
 * @param[in] dwSize - The size of @p lpszBuf in bytes.
 *
 * @return A pointer to the destination buffer (for convenience). 
 *
 * @internal
 */
LPTSTR GetLastErrorText(LPTSTR lpszBuf, DWORD dwSize) 
{
   DWORD dwRet; 
   LPTSTR lpszTemp = 0;

   dwRet = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER 
		 | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY, 
		 0, GetLastError(), LANG_NEUTRAL, (LPTSTR)&lpszTemp, 0, 0); 

   /* supplied buffer is not long enough */
   if (!dwRet || (long)dwSize < (long)dwRet + 14)
	  lpszBuf[0] = 0;
   else
   {
	  lpszTemp[lstrlen(lpszTemp)-2] = 0;
	  sprintf(lpszBuf, "%s (0x%x)", lpszTemp, GetLastError()); 
   } 

   if (lpszTemp)
	  LocalFree((HLOCAL)lpszTemp );

   return lpszBuf; 
} 

/** Signal the service to stop, and then report it.
 */
void ServiceStop(void) 
{
   G_SIGTERM = 1;
  // ReportStatusToSCMgr(SERVICE_STOPPED, NO_ERROR, 3000);
} 

/** Start the service and report it.
 *
 * @param[in] argc - The number of arguments in @p argv.
 * @param[in] argv - An array of argument string pointers.
 *
 * @internal
 */
// muge: rewritten ServiceStart method
void ServiceStart2(BOOL* resultCode, char* resultMessage )
{
   fd_set readfds;
   fd_set writefds;
   int highfd;
   int fdcount = 0;
   time_t curtime;
   time_t alarmtime;
   struct timeval timeout;
   WSADATA wsaData; 
   WORD wVersionRequested = MAKEWORD(1, 1); 

   char cCurrentPath[FILENAME_MAX];
   char cLogfilePath[FILENAME_MAX];
   
   _getcwd(cCurrentPath, sizeof(cCurrentPath));	
   _getcwd(cLogfilePath, sizeof(cLogfilePath));	

   strncpy ( cCurrentPath, cCurrentPath, strlen(cCurrentPath)- strlen(strrchr(cCurrentPath,'\\'))+1 );
   strncpy ( cLogfilePath, cLogfilePath, strlen(cLogfilePath)- strlen(strrchr(cLogfilePath,'\\'))+1 );

   strcat(cCurrentPath, SLPD_CONFFILE);
   strcat(cLogfilePath, "\\.\\slpd.log");
   ////printf ("The current working directory is \n%s\n", cCurrentPath);
   strncpy (G_SlpdCommandLine.cfgfile, cCurrentPath, sizeof(cCurrentPath));
   strncpy (G_SlpdCommandLine.logfile, cLogfilePath, sizeof(cLogfilePath));
   //strncpy (G_SlpdCommandLine.cfgfile, "C:\\WINDOWS\\slp.conf", 36);
   strncpy (G_SlpdCommandLine.regfile, "", 0);
   /* service initialization */
   //if (!ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 3000))
	  //return;

   if (WSAStartup(wVersionRequested, &wsaData) != 0)
   {
      //ReportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 0); 
      *resultCode = false;
      strncpy( resultMessage, "Slpd initialization failed during WSAStartup", 45);
      return;
   }

   /* parse the command line */
   //if (SLPDParseCommandLine(argc, argv))
   //{
	  //ReportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 0);
	  //goto cleanup_winsock;
   //}

   /*if (!ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 3000))
	  goto cleanup_winsock;*/

   /* Initialize the preferences so we know if the log file is to be
	  overwritten or appended.*/
   if (SLPDPropertyInit(G_SlpdCommandLine.cfgfile))
   {
	  fprintf(stderr, "slpd initialization failed during property load\n");
     *resultCode = false;
     strncpy( resultMessage, "Slpd initialization failed during property load", 48);
	  goto cleanup_winsock;
   }

   /* initialize the log file */
   //if (SLPDLogFileOpen(G_SlpdCommandLine.logfile, G_SlpdProperty.appendLog))
   if (SLPDLogFileOpen(G_SlpdCommandLine.logfile, G_SlpdProperty.appendLog))
   {
      fprintf(stderr, "Could not open logfile %s\n",G_SlpdCommandLine.logfile);
     
      *resultCode = false;
      strncpy( resultMessage, "Slpd initialization failed. Could not open logfile.", 52);
      goto cleanup_winsock;
   }

   /* seed the XID generator */
   SLPXidSeed();

   /* log startup message */
   SLPDLog("****************************************\n");
   SLPDLogTime();
   SLPDLog("SLPD daemon started -- service start\n");
   SLPDLog("****************************************\n");
   //SLPDLog("Command line = %s\n",argv[0]);
   // char cCurrentPath[FILENAME_MAX];

   //_getcwd(cCurrentPath, sizeof(cCurrentPath));	
   //strncpy ( cCurrentPath, cCurrentPath, strlen(cCurrentPath)- strlen(strrchr(cCurrentPath,'\\'))+1 );

   //strcat(cCurrentPath, SLPD_CONFFILE);
   ////printf ("The current working directory is \n%s\n", cCurrentPath);
   //strncpy (G_SlpdCommandLine.cfgfile, cCurrentPath, sizeof(cCurrentPath));
   SLPDLog("Using configuration file = %s\n",G_SlpdCommandLine.cfgfile);
   SLPDLog("Using registration file = %s\n",G_SlpdCommandLine.regfile);
   //if (!ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 3000))
	  //goto cleanup_winsock;

   /* initialize for the first time */
   SLPDPropertyReinit();  /*So we get any property-related log messages*/
   if (SLPDDatabaseInit(G_SlpdCommandLine.regfile) 
   || SLPDIncomingInit() 
   || SLPDOutgoingInit() 
   || SLPDKnownDAInit())
   {
      SLPDLog("slpd initialization failed\n");
      
      *resultCode = false;
      strncpy( resultMessage, "Slpd initialization failed", 27);
      goto cleanup_winsock;

   }
   SLPDLog("Agent Interfaces = %s\n", G_SlpdProperty.interfaces);

   /* service is now running, perform work until shutdown    */
   //if (!ReportStatusToSCMgr(SERVICE_RUNNING, NO_ERROR, 0))
	  //goto cleanup_winsock;

   /* main loop */
   *resultCode = true;
   strncpy( resultMessage, "Slpd initialization succeeded", 30);
   SLPDLog("Startup complete entering main run loop ...\n\n");
   G_SIGTERM   = 0;
   time(&curtime);
   alarmtime = curtime + 2;  /*Start with a shorter time so SAs register with us quickly on startup*/
   while (G_SIGTERM == 0)
   {
	  /* load the fdsets up with all valid sockets in the list  */
	  highfd = 0;
	  FD_ZERO(&readfds);
	  FD_ZERO(&writefds);
	  LoadFdSets(&G_IncomingSocketList, &highfd, &readfds, &writefds);
	  LoadFdSets(&G_OutgoingSocketList, &highfd, &readfds, &writefds);

     /* Before select(), check to see if we got a signal */
	  if (G_SIGALRM)
		 goto HANDLE_SIGNAL;

	  /* main select -- we time out every second so the outgoing retries can occur*/
	  time(&curtime);  
	  timeout.tv_sec = 1;
	  timeout.tv_usec = 0;
	  fdcount = select(highfd + 1, &readfds, &writefds, 0, &timeout);
	  if (fdcount > 0) 
	  {
		 SLPDIncomingHandler(&fdcount, &readfds, &writefds);
		 SLPDOutgoingHandler(&fdcount, &readfds, &writefds);
		 SLPDOutgoingRetry(time(0) - curtime);
	  }
	  else if (fdcount == 0)
		 SLPDOutgoingRetry(time(0) - curtime);

	  /* handle signals */
	  HANDLE_SIGNAL:
	  time(&curtime);
	  if (curtime >= alarmtime)
	  {
		 HandleSigAlrm();
		 alarmtime = curtime + SLPD_AGE_INTERVAL;
	  }
   }

   /* Got SIGTERM */
   HandleSigTerm();

cleanup_winsock:
   ;
   WSACleanup();    

} 


void ServiceStart(int argc, char ** argv)
{
   fd_set readfds;
   fd_set writefds;
   int highfd;
   int fdcount = 0;
   time_t curtime;
   time_t alarmtime;
   struct timeval timeout;
   WSADATA wsaData; 
   WORD wVersionRequested = MAKEWORD(1, 1); 

   /* service initialization */
   if (!ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 3000))
	  return;

   if (WSAStartup(wVersionRequested, &wsaData) != 0)
   {
	  ReportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 0); 
	  return;
   }

   /* parse the command line */
   if (SLPDParseCommandLine(argc, argv))
   {
	  ReportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 0);
	  goto cleanup_winsock;
   }

   if (!ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 3000))
	  goto cleanup_winsock;

   /* Initialize the preferences so we know if the log file is to be
	  overwritten or appended.*/
   if (SLPDPropertyInit(G_SlpdCommandLine.cfgfile))
   {
	  fprintf(stderr, "slpd initialization failed during property load\n");
	  goto cleanup_winsock;
   }

   /* initialize the log file */
   if (SLPDLogFileOpen(G_SlpdCommandLine.logfile, G_SlpdProperty.appendLog))
   {
	  fprintf(stderr, "Could not open logfile %s\n",G_SlpdCommandLine.logfile);
	  goto cleanup_winsock;
   }

   /* seed the XID generator */
   SLPXidSeed();

   /* log startup message */
   SLPDLog("****************************************\n");
   SLPDLogTime();
   SLPDLog("SLPD daemon started -- service start\n");
   SLPDLog("****************************************\n");
   SLPDLog("Command line = %s\n",argv[0]);
    char cCurrentPath[FILENAME_MAX];

   _getcwd(cCurrentPath, sizeof(cCurrentPath));	
   strncpy ( cCurrentPath, cCurrentPath, strlen(cCurrentPath)- strlen(strrchr(cCurrentPath,'\\'))+1 );

   strcat(cCurrentPath, SLPD_CONFFILE);
   //printf ("The current working directory is \n%s\n", cCurrentPath);
   strncpy (G_SlpdCommandLine.cfgfile, cCurrentPath, sizeof(cCurrentPath));
   SLPDLog("Using configuration file = %s\n",G_SlpdCommandLine.cfgfile);
   SLPDLog("Using registration file = %s\n",G_SlpdCommandLine.regfile);
   if (!ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 3000))
	  goto cleanup_winsock;

   /* initialize for the first time */
   SLPDPropertyReinit();  /*So we get any property-related log messages*/
   if (SLPDDatabaseInit(G_SlpdCommandLine.regfile) 
		 || SLPDIncomingInit() 
		 || SLPDOutgoingInit() 
		 || SLPDKnownDAInit())
   {
	  SLPDLog("slpd initialization failed\n");
	  goto cleanup_winsock;
   }
   SLPDLog("Agent Interfaces = %s\n", G_SlpdProperty.interfaces);

   /* service is now running, perform work until shutdown    */
   if (!ReportStatusToSCMgr(SERVICE_RUNNING, NO_ERROR, 0))
	  goto cleanup_winsock;

   /* main loop */
   SLPDLog("Startup complete entering main run loop ...\n\n");
   G_SIGTERM   = 0;
   time(&curtime);
   alarmtime = curtime + 2;  /*Start with a shorter time so SAs register with us quickly on startup*/
   while (G_SIGTERM == 0)
   {
	  /* load the fdsets up with all valid sockets in the list  */
	  highfd = 0;
	  FD_ZERO(&readfds);
	  FD_ZERO(&writefds);
	  LoadFdSets(&G_IncomingSocketList, &highfd, &readfds, &writefds);
	  LoadFdSets(&G_OutgoingSocketList, &highfd, &readfds, &writefds);

	  /* Before select(), check to see if we got a signal */
	  if (G_SIGALRM)
		 goto HANDLE_SIGNAL;

	  /* main select -- we time out every second so the outgoing retries can occur*/
	  time(&curtime);  
	  timeout.tv_sec = 1;
	  timeout.tv_usec = 0;
	  fdcount = select(highfd + 1, &readfds, &writefds, 0, &timeout);
	  if (fdcount > 0) 
	  {
		 SLPDIncomingHandler(&fdcount, &readfds, &writefds);
		 SLPDOutgoingHandler(&fdcount, &readfds, &writefds);
		 SLPDOutgoingRetry(time(0) - curtime);
	  }
	  else if (fdcount == 0)
		 SLPDOutgoingRetry(time(0) - curtime);

	  /* handle signals */
	  HANDLE_SIGNAL:
	  time(&curtime);
	  if (curtime >= alarmtime)
	  {
		 HandleSigAlrm();
		 alarmtime = curtime + SLPD_AGE_INTERVAL;
	  }
   }

   /* Got SIGTERM */
   HandleSigTerm();

cleanup_winsock:

   WSACleanup();     
} 

/** Handles console control events.
 *
 * @param[in] dwCtrlType - The type of control event.
 *
 * @return A boolean value; TRUE if the event was handled, FALSE if not.
 *
 * @internal
 */
BOOL WINAPI ControlHandler(DWORD dwCtrlType) 
{
   switch(dwCtrlType)
   {
	  case CTRL_BREAK_EVENT:  /* use Ctrl+C or Ctrl+Break to simulate */
	  case CTRL_C_EVENT:      /* SERVICE_CONTROL_STOP in debug mode */
		 printf("2Stopping %s.\n", G_SERVICEDISPLAYNAME); 
		 ServiceStop(); 
		 return TRUE; 
   } 
   return FALSE; 
} 

/** Called by the SCM whenever ControlService is called on this service.
 *
 * @param[in] dwCtrlCode - The type of control requested.
 *
 * @internal
 */
VOID WINAPI ServiceCtrl(DWORD dwCtrlCode) 
{
   switch(dwCtrlCode)
   {
	  case SERVICE_CONTROL_STOP: 
		 ReportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 0); 
		 ServiceStop(); 
		 return; 

	  case SERVICE_CONTROL_INTERROGATE: 
		 break; 

	  default: 
		 break; 
   } 
   ReportStatusToSCMgr(ssStatus.dwCurrentState, NO_ERROR, 0); 
} 

/** Win32 service main entry point.
 *
 * @param[in] argc - The number of arguments in @p argv.
 *
 * @param[in] argv - An array of argument string pointers.
 *
 * @internal
 */
void WINAPI SLPDServiceMain(DWORD argc, LPTSTR * argv) 
{
   sshStatusHandle = RegisterServiceCtrlHandler(G_SERVICENAME, ServiceCtrl);      

   if (sshStatusHandle != 0)
   {
	  /* SERVICE_STATUS members that don't change */
	  ssStatus.dwServiceType = SERVICE_WIN32_SHARE_PROCESS; 
	  ssStatus.dwServiceSpecificExitCode = 0; 

	  /* report the status to the service control manager.    */
	  if (ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 3000))
		 ServiceStart(argc, argv); 
   }

   /* try to report the stopped status to the service control manager. */
   if (sshStatusHandle)
	  ReportStatusToSCMgr(SERVICE_STOPPED, 0, 0);
} 

/** Install the service.
 *
 * @param[in] automatic - A flag indicating whether or not the service
 *    should be installed to start automatically at boot time.
 *
 * @internal
 */
void callXXX(char* a)
{
   bool f;
   strncpy(a, "deneme", sizeof(a) - 1);
   a[sizeof(a) - 1] = 0;
   //a[0] = 'd';
  //TCHAR* str =  SLPDCmdInstallService(1,f);
   //return str;

}

void SLPDCmdInitializeSlp(int automatic , BOOL* resultCode, char* resultMsg) 
{ 
   try
   {
      ServiceStart2(resultCode, resultMsg);
   }
   catch (...)
   {
      //printf("OpenSCManager failed - %s\n", GetLastErrorText(szErr, 256)); 
      resultCode = false;
      strncpy(resultMsg, "SLP initialization failed due to an exception - SLP - ", sizeof(resultMsg) - 1);

      //return "Installing of SLP service failed due to an exception";
   }
} 
/** Stop a service by service handle.
 *
 * @param[in] schService - A handle to the service to be stopped.
 *
 * @internal
 */
bool SLPDHlpStopService(SC_HANDLE schService)
{
   //try
   //{

	  // printf("in SLPDHlpStopService...................\n");
   //   /* try to stop the service */
	  // Sleep(1000);
   //   if (!ControlService(schService, SERVICE_CONTROL_STOP,  &ssStatus))
	  // {	 
		 //  printf( "ControlService failed (%d)\n", GetLastError() );
   //   }
   //   else
   //   {
	  //   printf("1Stopping %s.", G_SERVICEDISPLAYNAME);
	  //   Sleep(1000);

	  //   /*while (QueryServiceStatus(schService, &ssStatus))
	  //   {
		 //   if (ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
		 //   {
			//   printf(".");
			//   Sleep(1000);
		 //   }
		 //   else
			//   break; 
	  //   } */
	  //   if (ssStatus.dwCurrentState == SERVICE_STOPPED)
   //     {
		 //   printf("\n%s stopped.\n", G_SERVICEDISPLAYNAME);
   //       return true;
   //     }
	  //   else
   //     {
		 //   printf("\n%s failed to stop.\n", G_SERVICEDISPLAYNAME); 
   //       return false;
   //     }
   //   }
   //}
   //catch(...)
   //{
   //   return false;
   //}
   //ipek koc
   /* try to stop the service */
   Sleep(50000);
   if (ControlService(schService, SERVICE_CONTROL_STOP, &ssStatus))
   {
      printf( "ControlService failed (%d)\n", GetLastError() );
      printf("Stopping %s.", G_SERVICEDISPLAYNAME);
      Sleep(1000);

      while (QueryServiceStatus(schService, &ssStatus))
      {
         if (ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
         {
            printf(".");
            Sleep(1000);
         }
         else
            break; 
      } 
      if (ssStatus.dwCurrentState == SERVICE_STOPPED)
      {
         printf("\n%s stopped.\n", G_SERVICEDISPLAYNAME);
         return true;
      }
      else
      {
         printf("\n%s failed to stop.\n", G_SERVICEDISPLAYNAME); 
         return false;
      }
      printf( "ControlService failed (%d)\n", GetLastError() );
   }
    //   SERVICE_STATUS_PROCESS ssp;

    //DWORD dwStartTime = GetTickCount();
    //DWORD dwBytesNeeded;
    //DWORD dwTimeout = 30000; // 30-second time-out
    //DWORD dwWaitTime;

    //// Get a handle to the SCM database. 
 
    //SC_HANDLE schSCManager = OpenSCManager( 
    //    NULL,                    // local computer
    //    NULL,                    // ServicesActive database 
    //    SC_MANAGER_ALL_ACCESS);  // full access rights 
 
    //if (NULL == schSCManager) 
    //{
    //    printf("OpenSCManager failed (%d)\n", GetLastError());
    //    return false;
    //}

    //// Get a handle to the service.

    ////schService = OpenService( 
    ////    schSCManager,         // SCM database 
    ////    szSvcName,            // name of service 
    ////    SERVICE_STOP | 
    ////    SERVICE_QUERY_STATUS | 
    ////    SERVICE_ENUMERATE_DEPENDENTS);  
 
    //if (schService == NULL)
    //{ 
    //    printf("OpenService failed (%d)\n", GetLastError()); 
    //    CloseServiceHandle(schSCManager);
    //    return false;
    //}    

    //// Make sure the service is not already stopped.

    //if ( !QueryServiceStatusEx( 
    //        schService, 
    //        SC_STATUS_PROCESS_INFO,
    //        (LPBYTE)&ssp, 
    //        sizeof(SERVICE_STATUS_PROCESS),
    //        &dwBytesNeeded ) )
    //{
    //    printf("QueryServiceStatusEx failed (%d)\n", GetLastError()); 
    //                CloseServiceHandle(schService); 
    //        CloseServiceHandle(schSCManager);
    //        return false;
    //}

    //if ( ssp.dwCurrentState == SERVICE_STOPPED )
    //{
    //    printf("Service is already stopped.\n");
    //                CloseServiceHandle(schService); 
    //        CloseServiceHandle(schSCManager);
    //        return false;
    //}

    //// If a stop is pending, wait for it.

    //while ( ssp.dwCurrentState == SERVICE_STOP_PENDING ) 
    //{
    //    printf("Service stop pending...\n");

    //    // Do not wait longer than the wait hint. A good interval is 
    //    // one-tenth of the wait hint but not less than 1 second  
    //    // and not more than 10 seconds. 
 
    //    dwWaitTime = ssp.dwWaitHint / 10;

    //    if( dwWaitTime < 1000 )
    //        dwWaitTime = 1000;
    //    else if ( dwWaitTime > 10000 )
    //        dwWaitTime = 10000;

    //    Sleep( dwWaitTime );

    //    if ( !QueryServiceStatusEx( 
    //             schService, 
    //             SC_STATUS_PROCESS_INFO,
    //             (LPBYTE)&ssp, 
    //             sizeof(SERVICE_STATUS_PROCESS),
    //             &dwBytesNeeded ) )
    //    {
    //        printf("QueryServiceStatusEx failed (%d)\n", GetLastError()); 
    //                    CloseServiceHandle(schService); 
    //        CloseServiceHandle(schSCManager);
    //        return false;
    //    }

    //    if ( ssp.dwCurrentState == SERVICE_STOPPED )
    //    {
    //        printf("Service stopped successfully.\n");
    //                    CloseServiceHandle(schService); 
    //        CloseServiceHandle(schSCManager);
    //        return true;
    //    }

    //    if ( GetTickCount() - dwStartTime > dwTimeout )
    //    {
    //        printf("Service stop timed out.\n");
    //        CloseServiceHandle(schService); 
    //        CloseServiceHandle(schSCManager);
    //        return false;
    //    }
    //}

    //// If the service is running, dependencies must be stopped first.

    ////StopDependentServices();

    //// Send a stop code to the service.

    //if ( !ControlService( 
    //        schService, 
    //        SERVICE_CONTROL_STOP, 
    //        (LPSERVICE_STATUS) &ssp ) )
    //{
    //    printf( "ControlService failed (%d)\n", GetLastError() );
    //        CloseServiceHandle(schService); 
    //        CloseServiceHandle(schSCManager);
    //        return false;
    //}

    //// Wait for the service to stop.

    //while ( ssp.dwCurrentState != SERVICE_STOPPED ) 
    //{
    //    Sleep( ssp.dwWaitHint );
    //    if ( !QueryServiceStatusEx( 
    //            schService, 
    //            SC_STATUS_PROCESS_INFO,
    //            (LPBYTE)&ssp, 
    //            sizeof(SERVICE_STATUS_PROCESS),
    //            &dwBytesNeeded ) )
    //    {
    //        printf( "QueryServiceStatusEx failed (%d)\n", GetLastError() );
    //        CloseServiceHandle(schService); 
    //        CloseServiceHandle(schSCManager);
    //        return false;
    //    }

    //    if ( ssp.dwCurrentState == SERVICE_STOPPED )
    //        break;

    //    if ( GetTickCount() - dwStartTime > dwTimeout )
    //    {
    //        printf( "Wait timed out\n" );
    //        CloseServiceHandle(schService); 
    //        CloseServiceHandle(schSCManager);
    //        return false;
    //    }
    //}
    //printf("Service stopped successfully\n");
    //return true;
}
void SLPDCmdInstallService(int automatic , BOOL& resultCode, char* a) 
{ 
   char cCurrentPath[FILENAME_MAX];

   _getcwd(cCurrentPath, sizeof(cCurrentPath));	
   strncpy ( cCurrentPath, cCurrentPath, strlen(cCurrentPath)- strlen(strrchr(cCurrentPath,'\\'))+1 );

	strcat(cCurrentPath, SLPD_CONFFILE);
	printf ("The current working directory is \n%s\n", cCurrentPath);
   try
   {
      SERVICE_TABLE_ENTRY dispatchTable[] = 
      { 
         {G_SERVICENAME, (LPSERVICE_MAIN_FUNCTION)SLPDServiceMain}, 
         {0, 0} 
      }; 
      StartServiceCtrlDispatcher(dispatchTable);
     // SC_HANDLE schService; 
      SC_HANDLE schSCManager; 

      DWORD start_type;
      TCHAR szPath[512]; 
	  strncpy (G_SlpdCommandLine.cfgfile, cCurrentPath, sizeof(cCurrentPath));
      if (GetModuleFileName(0, szPath, 512) == 0)
      {
	    // printf("Unable to install %s - %s\n", G_SERVICEDISPLAYNAME, GetLastErrorText(szErr, 256));
	     //return false; 
        resultCode = false;
        strncpy(a, "Unable to install SLP", 22);
        a[22] = 0;
        //return GetLastErrorText(szErr, 256);
      }

      if (automatic)
	     start_type = SERVICE_AUTO_START;
      else
	     start_type = SERVICE_DEMAND_START;

      schSCManager = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
      if (schSCManager)
      {
	     schService = CreateService(schSCManager, G_SERVICENAME, 
			   G_SERVICEDISPLAYNAME, SERVICE_ALL_ACCESS, 
            SERVICE_WIN32_SHARE_PROCESS, start_type, 
			   //SERVICE_ERROR_NORMAL, "D:\\Projects\\Trentino\\Development\\ServiceDiscovery\\ipek\\openslp-2.0.beta2\\win32\\Debug\\slpd.exe", 0, 0, "", 0, 0);
            SERVICE_ERROR_NORMAL, szPath, 0, 0, "", 0, 0);
	     if (schService)
	     {
		    //printf("%s installed.\n", G_SERVICEDISPLAYNAME ); 
           strncpy(a, "Installed - SLP", 16);
           a[16] = 0;
           if (!StartService(schService, 0, 0))
            {
               //printf("StartService failed - %s\n", GetLastErrorText(szErr,256));
               //CloseServiceHandle(schService); 
               GetLastErrorText(szErr, 256);
               resultCode = false;
               strncpy(a, "StartService failed - SLP - ", 29);
               a[29] = 0;
               strncat(a,szErr,256);
            }
            else
            {
               //CloseServiceHandle(schService); 
               resultCode = true;
               strncpy(a, "Started - SLP - ", 17);
               a[17] = 0;
            }
		    //CloseServiceHandle(schService); 

          //CloseServiceHandle(schSCManager); 
          resultCode = true;
          //return "Service Location Protocol service is installed";
	     }
	     else
        {
		    printf("CreateService failed - %s\n", GetLastErrorText(szErr, 256)); 
          strncpy(a, "CreateService failed - SLP - ", 30);
          a[30] = 0;
          strncat(a,szErr,256);
          
          //CloseServiceHandle(schService); 
          
          resultCode = false;
          //return GetLastErrorText(szErr, 256);
        }
        SLPDHlpStopService(schService);

		    /* now remove the service    */
		    if (DeleteService(schService))
			   printf("%s removed.\n", G_SERVICEDISPLAYNAME );
		    else
			   printf("DeleteService failed - %s\n", GetLastErrorText(szErr,256)); 

        CloseServiceHandle(schSCManager); 

      }
      else
      {
	     //printf("OpenSCManager failed - %s\n", GetLastErrorText(szErr, 256)); 
         printf("CreateService failed - %s\n", GetLastErrorText(szErr, 256)); 
         strncpy(a, "OpenSCManager failed - SLP - ", 30);
         a[30] = 0;
         strncat(a,szErr,256);
        resultCode = false;
        //CloseServiceHandle(schService); 
        //CloseServiceHandle(schSCManager); 
        //return GetLastErrorText(szErr, 256);
      }
   }

   catch (...)
   {
      //printf("OpenSCManager failed - %s\n", GetLastErrorText(szErr, 256)); 
      resultCode = false;
      strncpy(a, "Installing of SLP service failed due to an exception - SLP - ", sizeof(a) - 1);

      //return "Installing of SLP service failed due to an exception";
   }
} 


 
/** Uninstall the service.
 *
 * @internal
 */
void SLPDCmdRemoveService(void)
{
   try
   {
      //SC_HANDLE schService; 
      SC_HANDLE schSCManager; 

      schSCManager = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
      if (schSCManager)
      {
	     //schService = OpenService(schSCManager, G_SERVICENAME, SERVICE_ALL_ACCESS); 
	     if (schService)
	     {
		    SLPDHlpStopService(schService);

		    /* now remove the service    */
		    if (DeleteService(schService))
			   printf("%s removed.\n", G_SERVICEDISPLAYNAME );
		    else
			   printf("DeleteService failed - %s\n", GetLastErrorText(szErr,256)); 

		    //CloseServiceHandle(schService); 
	     }
	     else
		    printf("OpenService failed - %s\n", GetLastErrorText(szErr,256)); 

	     CloseServiceHandle(schSCManager); 
      }
      else
	     printf("OpenSCManager failed - %s\n", GetLastErrorText(szErr,256));
   }
   catch(...)
   {
      return;
   }
} 

/** Start the service.
 *
 * @internal
 */
void SLPDCmdStartService(BOOL& resultCode, char* startServiceResult)
{
   try
   {
      SC_HANDLE schService; 
      SC_HANDLE schSCManager; 

      schSCManager = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
      if (schSCManager)
      {
         schService = OpenService(schSCManager, G_SERVICENAME, SERVICE_ALL_ACCESS); 
         if (schService)
         {
            if (!StartService(schService, 0, 0))
            {
               //printf("StartService failed - %s\n", GetLastErrorText(szErr,256));
               CloseServiceHandle(schService); 
               GetLastErrorText(szErr, 256);
               resultCode = false;
               strncpy(startServiceResult, "StartService failed - SLP - ", 29);
               startServiceResult[29] = 0;
               strncat(startServiceResult,szErr,256);
            }
            else
            {
               CloseServiceHandle(schService); 
               resultCode = true;
               strncpy(startServiceResult, "Started - SLP - ", 17);
               startServiceResult[17] = 0;
            }

         }
         else
         {
            //printf("OpenService failed - %s\n", GetLastErrorText(szErr,256)); 
            CloseServiceHandle(schSCManager); 
            resultCode = false;
            GetLastErrorText(szErr, 256);
            strncpy(startServiceResult, "OpenService failed - SLP - ", 28);
            startServiceResult[28] = 0;
            strncat(startServiceResult,szErr,256);
         }

      }
      else
      {
         //printf("OpenSCManager failed - %s\n", GetLastErrorText(szErr,256)); 
         resultCode = false;
         GetLastErrorText(szErr, 256);
         strncpy(startServiceResult, "OpenSCManager failed - SLP - ", 30);
         startServiceResult[30] = 0;
         strncat(startServiceResult,szErr,256);
      }
   }
   catch (...)
   {
      resultCode = false;
      strncpy(startServiceResult, "Exception - SLP - ", 19);
      startServiceResult[19] = 0;
      strncat(startServiceResult,szErr,256);

   }
}

/** Stop the service.
 *
 * @internal
 */
void SLPDCmdStopService(void)
{
   try
   {
	   printf("slpd is stopped...\n");
      //SC_HANDLE schService; 
      SC_HANDLE schSCManager; 

      schSCManager = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
      if (schSCManager)
      {
	     //schService = OpenService(schSCManager, G_SERVICENAME, SERVICE_ALL_ACCESS); 
	     if (schService)
	     {
		    SLPDHlpStopService(schService);
		    //CloseServiceHandle(schService); 
	     }
	     else
		    printf("OpenService failed - %s\n", GetLastErrorText(szErr,256)); 
	     CloseServiceHandle(schSCManager); 
      }
      else
	     printf("OpenSCManager failed - %s\n", GetLastErrorText(szErr,256)); 
   }
   catch (...)
   {
      return;
   }
}

void SLPDCmdDeinitializeSlp(void)
{
   ServiceStop();
   // muge: Somehow I was getting am getting a ntdll.dll!_DbgBreakPoint@0() without this sleep
   // only when running from the visual studio debugger
   Sleep(1000);
}
/** Debug the service.
 *
 * @param[in] argc - The number of arguments in @p argv.
 *
 * @param[in] argv - An array of argument string pointers.
 *
 * @internal
 */
void SLPDCmdDebugService(int argc, char ** argv) 
{
   printf("Debugging %s.\n", G_SERVICEDISPLAYNAME); 

   SetConsoleCtrlHandler(ControlHandler, TRUE); 
   ServiceStart(argc, argv); 
}

/** The main program entry point (when not executed as a service). 
 *
 * @param[in] argc - The number of arguments in @p argv.
 *
 * @param[in] argv - An array of argument string pointers.
 */
/*void __cdecl main(int argc, char ** argv) 
{
   SERVICE_TABLE_ENTRY dispatchTable[] = 
   { 
	  {G_SERVICENAME, (LPSERVICE_MAIN_FUNCTION)SLPDServiceMain}, 
	  {0, 0} 
   }; 


   if (SLPDParseCommandLine(argc, argv))
	  SLPDFatal("Invalid command line\n");

   switch (G_SlpdCommandLine.action)
   {
	  case SLPD_DEBUG:
		 SLPDCmdDebugService(argc, argv);
		 break;
	  case SLPD_INSTALL:
		 SLPDCmdInstallService(G_SlpdCommandLine.autostart);
		 break;
	  case SLPD_REMOVE:
		 SLPDCmdRemoveService();
		 break;
	  case SLPD_START:
		 SLPDCmdStartService();
		 break;
	  case SLPD_STOP:
		 SLPDCmdStopService();
		 break;
	  default:
		 SLPDPrintUsage();
		 StartServiceCtrlDispatcher(dispatchTable);
		 break;
   } 
} */

/*=========================================================================*/
}