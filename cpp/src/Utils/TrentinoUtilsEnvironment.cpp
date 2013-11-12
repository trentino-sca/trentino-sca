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
#include "TrentinoUtilsEnvironment.h"

//standard
#include <vector>
#include <stdexcept>
#ifdef WIN32
   #include <Windows.h>
#else
   #include <stdlib.h>
   #include <stdio.h>
   #include <unistd.h>
#endif

//specific
#include "../Global/TrentinoGlobal.h"

using namespace Trentino::Utils::Environment;
using namespace std;

string Trentino::Utils::Environment::executablePath()
{
  
   #ifdef WIN32
      //taken from http://msdn.microsoft.com/en-us/library/windows/desktop/ms683197%28v=vs.85%29.aspx
      //(19.07.2012)

      vector<char> exePath(MAX_PATH);      
      //Try to get the executable path with a buffer of MAX_PATH characters.      
      DWORD result = ::GetModuleFileNameA( nullptr
                                          , &exePath[0]
                                          , static_cast<DWORD>(exePath.size()));

      //As long the function returns the buffer size, it is indicating that the buffer
      //was too small. Keep enlarging the buffer by a factor of 2 until it fits.
      while(result == exePath.size()) 
      {
         exePath.resize(exePath.size() * 2);
         result = ::GetModuleFileNameA( nullptr
                                    , &exePath[0]
                                    , static_cast<DWORD>(exePath.size()) );
      }

      //If the function returned 0, something went wrong
      if(result == 0) 
      {
         LPSTR buffer = nullptr;
         ::FormatMessageA( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER  
                           , NULL
                           , GetLastError()
                           , 0
                           , buffer
                           , 0
                           , NULL);
            

         const string errorString(buffer);
         ::LocalFree(buffer);
      
         throw runtime_error("GetModuleFileName() failed. " + errorString);
      }

      //We've got the path, construct a standard string from it
      return std::string(exePath.begin(), exePath.begin() + result);
   #elif defined __linux || defined __CYGWIN__
      //taken from http://www.linuxquestions.org/questions/programming-9/get-full-path-of-a-command-in-c-117965/
      //(19.07.2012)      
     
     /* /proc/self is a symbolic link to the process-ID subdir
      * of /proc, e.g. /proc/4323 when the pid of the process
      * of this program is 4323.
      *
      * Inside /proc/<pid> there is a symbolic link to the
      * executable that is running as this <pid>.  This symbolic
      * link is called "exe".
      *
      * So if we read the path where the symlink /proc/self/exe
      * points to we have the full path of the executable.
      */

      const int MaxPathLen = 1024;   /* make this larger if you need to. */           
      char fullpath[MaxPathLen];

      int length = readlink("/proc/self/exe", fullpath, sizeof(fullpath));
     
     /* Catch some errors: */
     if (length < 0) 
     {
         throw runtime_error("Error resolving symlink /proc/self/exe");         
     }
     if (length >= MaxPathLen) 
     {
          throw runtime_error("Path for symlink /proc/self/ex' too long");
     }

     /* I don't know why, but the string this readlink() function 
      * returns is appended with a '@'.
      */
     fullpath[length] = '\0'; //Strip '@' off the end. 

     return fullpath;
   #else
      assert(false);
   #endif
  
}