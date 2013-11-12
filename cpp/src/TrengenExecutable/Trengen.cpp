#ifdef WIN32
#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include <windows.h> //CreateProcess() etc.

#else
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

#endif

#include <cstdlib>
#include <iostream>
#include <string>

#pragma warning(push)
#pragma warning(disable:4100)

#include <boost/algorithm/string/replace.hpp>
#include <boost/scoped_array.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/path.hpp>
#pragma warning(pop)

#include "../Utils/TrentinoUtilsEnvironment.h"

namespace fs = boost::filesystem;
using namespace std;

 /* REMARK: Trengen.jar should be in the same directory with Trengen.exe */
 /* TODO: In the future, directory of the jar file may be read from the config file. */
int main(int argc, char* argv[])
{
	#ifdef WIN32

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	::ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	std::string exeDir = Trentino::Utils::Environment::executablePath();
	std::string jarDir;

	size_t pos = exeDir.find_last_of("\\");
	if(pos != std::string::npos)
		jarDir.assign(exeDir.begin(), exeDir.begin() + pos+1 );
	else
		jarDir = exeDir;
	
	std::string command = "java -cp ";
	command = command.append(jarDir+"Trengen.jar;");
	command = command.append(jarDir+"org.eclipse.cdt.core_5.3.1.201109151620.jar;");
	command = command.append(jarDir+"org.eclipse.core.resources_3.7.100.v20110510-0712.jar;");
	command = command.append(jarDir+"org.eclipse.equinox.common_3.6.0.v20110523.jar org.trentino.trengen.tools.trengen.Trengen");

	for (int i = 1; i < argc; i++)
	{
	  command = command.append(" ");
      //if the argument doesn't start with '-', it's actually an argument representing
      //an argument's value for Trengen (e.g. a path), so it should be put in quotes
      const string argument = 
         argv[i][0] == '-' ? argv[i] : string("\"") + argv[i] + "\"";            
		command = command.append(argument);
	}

	const std::wstring fullCmdLineW = std::wstring(command.begin(), command.end());
    boost::scoped_array<WCHAR> cstrFullCmdLineW(new WCHAR[fullCmdLineW.size() + 1]);   
    wcscpy_s(cstrFullCmdLineW.get(), fullCmdLineW.size() + 1, fullCmdLineW.c_str());
   
    if ( !::CreateProcess( NULL, cstrFullCmdLineW.get(), NULL, NULL, FALSE,
                        NULL, NULL, NULL, &si, &pi) )
    {         
      LPTSTR buffer;
      ::FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER  
                     , NULL
                     , GetLastError()
                     , 0
                     , (LPTSTR)&buffer
                     , 0
                     , NULL);

      const std::wstring wstrBuffer(buffer);
      ::LocalFree(buffer);

      std::cout<<"SYSTEM ERROR: " + std::string(wstrBuffer.begin(), wstrBuffer.end()) + 
					"(" + command + ")";      
    }   

    ::CloseHandle(pi.hThread);
    ::WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    ::GetExitCodeProcess(pi.hProcess, &exitCode);
    if(exitCode != EXIT_SUCCESS)
    {
      std::cout<</*"ERROR: ExitCode=" + boost::lexical_cast<std::string>(exitCode) + */
                        "FAILED";
    } 

    return EXIT_SUCCESS;

#else
   std::string exeDir = Trentino::Utils::Environment::executablePath();
   std::string exeName;

   size_t pos = exeDir.find_last_of("/");
   if(pos != std::string::npos)
      exeName.assign(exeDir.begin() + pos + 1, exeDir.end());
   else
      exeName = exeDir;

   std::string jarDir = exeDir;
   boost::algorithm::replace_all(jarDir, exeName, "");

   std::string Trengen = jarDir;
   Trengen = Trengen.append("Trengen.jar:"); //name of the jar is Trengen.jar
   Trengen = Trengen.append(jarDir.c_str());
   Trengen = Trengen.append("org.eclipse.cdt.core_5.3.1.201109151620.jar:");
   Trengen = Trengen.append(jarDir.c_str());
   Trengen = Trengen.append("org.eclipse.core.resources_3.7.100.v20110510-0712.jar:");
   Trengen = Trengen.append(jarDir.c_str());
   Trengen = Trengen.append("org.eclipse.equinox.common_3.6.0.v20110523.jar");

   char** linux_commands = (char**)malloc((argc + 4) * sizeof(char*));
   linux_commands[0] = const_cast<char*>("java"); //The first argument, by convention, should point to the file to be executed
   linux_commands[1] = const_cast<char*>("-cp");
   linux_commands[2] = const_cast<char*>(Trengen.c_str()); //name of the jar is Trengen.jar
   linux_commands[3] = const_cast<char*>("org.trentino.trengen.tools.trengen.Trengen");

   int index;
   for (index=1; index < argc; index++) 
      linux_commands[index + 3] = argv[index];

   linux_commands[argc + 3] = NULL; //The array of pointers to arguments must be NULL-terminated

   int ret = execvp("java", linux_commands);
   free(linux_commands);

   return ret;
#endif
}