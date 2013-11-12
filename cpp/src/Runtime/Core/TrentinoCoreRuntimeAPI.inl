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

//construction
inline
RuntimeAPI::RuntimeAPI() : mManagementInterface(nullptr)
{
   //create();
}

inline
RuntimeAPI::RuntimeAPI(const std::string& runtimeFilePath, const std::string& commandLine) : mManagementInterface(nullptr)
{
   create(runtimeFilePath,commandLine);   
}


inline
RuntimeAPI::~RuntimeAPI()
{
   try
   {
      destroy();
   }
   
   //! \todo should we do anything here? Can throw a exception in catch block...
   catch(...) {};
}

inline
Trentino::ManagementInterface* RuntimeAPI::managementInterface() const
{
   return mManagementInterface;
}

inline
const Trentino::Utils::DynamicLibraryPtr& RuntimeAPI::runtimeDLL() const
{
   return mRuntimeDLL;
}

//management
inline
void RuntimeAPI::create(const std::string& runtimeFilePath, const std::string& commandLine)
{
   if(mRuntimeDLL.get() != nullptr)
   {
      logError("Can´t load runtime more than once: %s", runtimeFilePath.c_str());
      return;
   }

   mRuntimeDLL = boost::make_shared<Trentino::Utils::DynamicLibrary>(runtimeFilePath);     

   try
   {
      mRuntimeDLL->load();
      assert(mRuntimeDLL->isLoaded());

      const Trentino::Core::Bootstrapping::BootFunc boot = 
         mRuntimeDLL->functionAddress<Trentino::Core::Bootstrapping::BootFunc>(
            Trentino::Core::Bootstrapping::BootFuncName);
      assert(boot != nullptr);

      const Trentino::Core::Bootstrapping::GetManagementInterfaceFunc getRuntimeManagementInteface = 
         mRuntimeDLL->functionAddress<Trentino::Core::Bootstrapping::GetManagementInterfaceFunc>(
            Trentino::Core::Bootstrapping::GetManagementInterfaceFuncName);
      assert(getRuntimeManagementInteface != nullptr);

      const Trentino::Core::Bootstrapping::CreateRuntimeConfiguration1Func 
         createRuntimeConfiguration1 =
            mRuntimeDLL->functionAddress<Trentino::Core::Bootstrapping::CreateRuntimeConfiguration1Func>(
               Trentino::Core::Bootstrapping::CreateRuntimeConfiguration1FuncName);
      assert(createRuntimeConfiguration1);

      // only for integrity
      Trentino::Core::Bootstrapping::ShutdownFunc shutdown = 
         mRuntimeDLL->functionAddress<Trentino::Core::Bootstrapping::ShutdownFunc>(
            Trentino::Core::Bootstrapping::ShutdownFuncName);  
      assert(shutdown != nullptr);
      (void) shutdown;

      Trentino::Core::Bootstrapping::RuntimeConfiguration* const runtimeConfiguration = 
         createRuntimeConfiguration1(
            Trentino::Core::Bootstrapping::RuntimeConfiguration::DefaultConfigFile, commandLine.c_str());
      assert(runtimeConfiguration != nullptr);
      boot(runtimeConfiguration);

      mManagementInterface = getRuntimeManagementInteface();  
   }
   catch(std::exception& e)
   {
      if(mRuntimeDLL->isLoaded())
      {
         mRuntimeDLL->unload();
         assert(mRuntimeDLL->isLoaded() == false);
      }
      
      throw std::runtime_error(
         "Cannot boot Trentino Runtime: " + std::string(e.what()));
   }

   if(mManagementInterface == nullptr)
   {
      destroy();
      throw std::runtime_error(
         "ManagementInterface couldn't be retrieved. Trentino Runtime shut down.");      
   }

}

inline
void RuntimeAPI::destroy()
{
   if(mRuntimeDLL.get() != nullptr)
   {
      assert(mRuntimeDLL->isLoaded() == true);

      Trentino::Core::Bootstrapping::ShutdownFunc shutdown = nullptr; 
      try
      {      
         shutdown = 
            mRuntimeDLL->functionAddress<Trentino::Core::Bootstrapping::ShutdownFunc>(
               Trentino::Core::Bootstrapping::ShutdownFuncName);      
      }
      catch(std::exception& e)
      {
         (void) e;
         logError("Cannot shutdown Trentino Runtime: %s", e.what());
         return;
      }

      shutdown();   
      mManagementInterface = nullptr;
      mRuntimeDLL->unload();
      //can be loaded implicitly, so it can be still loaded here
      //assert(mRuntimeDLL->isLoaded() == false);
      mRuntimeDLL.reset();
   }
}

