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

//standard
#ifdef WIN32
#define WINVER 0x0503
#  include <windows.h>
#else
#  include <dlfcn.h>
#endif

//header
#include "TrentinoUtilsDynamicLibrary.h"


#include <assert.h>
#include <string>

//specific
#include "../Global/TrentinoGlobal.h"
#include "TrentinoUtilsLogging.h"
#include "TrentinoUtilsLoggingLogger.h"
#ifdef WIN32
#  include <winbase.h>
#endif

using namespace std;
using namespace Trentino::Utils;


//class DynamicLibrary
   //construction
DynamicLibrary::DynamicLibrary(const string& filePath) : 
mFilePath(filePath), mLibHandle(nullptr)
{
}

DynamicLibrary::~DynamicLibrary()
{

}

   //services
void DynamicLibrary::load()
{
   #ifdef WIN32
      mLibHandle = ::LoadLibraryA(mFilePath.c_str());
      if(mLibHandle == nullptr)
      {
         LPSTR buffer = nullptr;
         const DWORD error = GetLastError();
         ::FormatMessageA( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER  
                         , NULL
                         , error
                         , 0
                         , (LPSTR)&buffer
                         , 0
                         , NULL);

         string strBuffer;
         if(buffer)
         {
            strBuffer.assign(buffer);
            ::LocalFree(buffer);
         }

         throw runtime_error( "Failed loading library " + mFilePath + ". " + strBuffer.c_str());
      }
   #else
      mLibHandle = ::dlopen(mFilePath.c_str(), RTLD_LAZY);
      if(mLibHandle == nullptr)
      {
         logError("Failed loading library %s", mFilePath.c_str());
         throw runtime_error( "Failed loading library " + mFilePath + ". " + ::dlerror()); 
      }
   #endif
      logInfo("Library %s successfully loaded...", mFilePath.c_str());
}

void DynamicLibrary::load(std::set<std::string> dllDirectoryList)
{
if(dllDirectoryList.size()==0)
   {
   //no dependencies, just load using default load method
    load();
    return;
   }

   #ifdef WIN32
    std::string first = *dllDirectoryList.begin();
   //safe set and unset DLL directory
   struct SetDLLDirectoryInitializer {
   public:
      SetDLLDirectoryInitializer(std::string dir)
         {
         SetDllDirectoryA(dir.c_str());
         }

      ~SetDLLDirectoryInitializer()
         {
         SetDllDirectoryA(NULL);
         }

      }setDLLDirectory(first);
   

   mLibHandle = ::LoadLibraryExA(mFilePath.c_str(), NULL
                                ,LOAD_WITH_ALTERED_SEARCH_PATH);
   if(mLibHandle == nullptr)
      {
      LPSTR buffer = nullptr;
      const DWORD error = GetLastError();
      ::FormatMessageA( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER  
         , NULL
         , error
         , 0
         , (LPSTR)&buffer
         , 0
         , NULL);

      string strBuffer;
      if(buffer)
         {
         strBuffer.assign(buffer);
         ::LocalFree(buffer);
         }

      throw runtime_error( "Failed loading library " + mFilePath + ". " + strBuffer.c_str());
      }
   #else
   mLibHandle = ::dlopen(mFilePath.c_str(), RTLD_LAZY);
   if(mLibHandle == nullptr)
      {
      logError("Failed loading library %s", mFilePath.c_str());
      throw runtime_error( "Failed loading library " + mFilePath + ". " + ::dlerror()); 
      }
   #endif
   logInfo("Library %s successfully loaded...", mFilePath.c_str());
}

void DynamicLibrary::unload(DynamicLibrary::UnloadAction unloadAction)
{   
   //!\todo check for errors and throw appropriate exceptions
   if(unloadAction == DynamicLibrary::Once)
   {      
   #ifdef WIN32
      ::FreeLibrary(reinterpret_cast<HMODULE>(mLibHandle));
   #else
      ::dlclose(mLibHandle);
   #endif
   }
   else if(unloadAction == DynamicLibrary::Complete)
   {
   #ifdef WIN32
      while(::FreeLibrary(reinterpret_cast<HMODULE>(mLibHandle)));
   #else
      while(::dlclose(mLibHandle) == 0);
   #endif
   }
   logInfo("Library %s successfully unloaded...", mFilePath.c_str());
   if(isLoaded() == false)
   {
      mLibHandle = nullptr;
   }

}

void* DynamicLibrary::getProcAddress(const std::string& funcName) const
{
   assert(mLibHandle != nullptr);
   void* funcResult = nullptr;
   #ifdef WIN32
      funcResult = reinterpret_cast<void*>(::GetProcAddress(reinterpret_cast<HMODULE>(mLibHandle), funcName.c_str()));

      if(funcResult == nullptr)
      {
         throw std::runtime_error(
            "Failed retrieving address for function: " + funcName + "in " + mFilePath);
      }
   #else
      funcResult = reinterpret_cast<void*>(::dlsym(mLibHandle, funcName.c_str()));

   char* error = ::dlerror();
   if(error != nullptr)
   {
         throw std::runtime_error( "Failed retrieving address for function " + funcName + 
         ". " + error);  
   }
#endif
   return funcResult;
}


bool DynamicLibrary::isLoaded() const
{
#ifdef WIN32
   return (::GetModuleHandleA(mFilePath.c_str()) != nullptr);
#else
   void* module;
   module = ::dlopen(mFilePath.c_str(), RTLD_LAZY | RTLD_NOLOAD);

   if (module)
   {
      dlclose(module);
      return true;
   }

   return false;
#endif
}
