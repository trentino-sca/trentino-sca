extern "C"
{
#ifndef SLPDDLL_H_INCLUDED
#define SLPDDLL_H_INCLUDED

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h> 
#include <stdio.h>
#include <process.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h> 
#include <limits.h>
#include <string.h>

#define G_SERVICENAME "slpd"
#define G_SERVICEDISPLAYNAME "Service Location Protocol"

#ifndef MAX_PATH
# define MAX_PATH    256
#endif

typedef DWORD pid_t;
typedef DWORD uid_t;
typedef int socklen_t;
typedef DWORD gid_t;
typedef SOCKET sockfd_t;

#define inet_aton(opt,bind) ((bind)->s_addr = inet_addr(opt))

#ifdef WIN32
	#ifdef OPENSLPDEAMON_EXPORTS
		#define OPENSLPDEAMON_IMPORT_EXPORT __declspec(dllexport)
	#else
		#define OPENSLPDEAMON_IMPORT_EXPORT __declspec(dllimport)       
	#endif
#else
	#define OPENSLPDEAMON_IMPORT_EXPORT 
#endif

static VOID WINAPI SLPDServiceMain(DWORD argc, LPTSTR * argv);

OPENSLPDEAMON_IMPORT_EXPORT void callXXX(char* a);

OPENSLPDEAMON_IMPORT_EXPORT VOID SLPDCmdInstallService(int automatic , BOOL& resultCode, char* installServiceResult);

OPENSLPDEAMON_IMPORT_EXPORT VOID SLPDCmdRemoveService(void);

static VOID SLPDCmdDebugService(int argc, char **argv);

OPENSLPDEAMON_IMPORT_EXPORT VOID SLPDCmdStartService(BOOL& resultCode,  char* startServiceResult);
		  
OPENSLPDEAMON_IMPORT_EXPORT VOID SLPDCmdStopService();




	  
#endif /* SLPDDLL_H_INCLUDED */

/*=========================================================================*/

}