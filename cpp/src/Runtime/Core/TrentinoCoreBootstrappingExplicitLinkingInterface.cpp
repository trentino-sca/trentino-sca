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
#include <iostream>
#include <stdexcept>
#include <boost/smart_ptr/make_shared.hpp>

//specific
#include "../../Global/TrentinoGlobal.h"
#include "TrentinoCoreBootstrappingRuntimeBootstrapper.h"
#include "TrentinoCoreBootstrappingRuntimeConfiguration.h"
#include "TrentinoCoreBootstrappingBootHelper.h"

using namespace Trentino::Core::Bootstrapping;

typedef BootHelper<RuntimeBootstrapper> Booter;
static Booter booter;
static Booter::BootPtr app;


extern "C" TRENTINO_DLLEXPORT RuntimeConfiguration* TRENTINO_CDECL
   createRuntimeConfiguration1(RuntimeConfiguration::Source source, const char* configFile)
{
   return new RuntimeConfiguration(configFile, source);
}

   
extern "C" TRENTINO_DLLEXPORT void TRENTINO_CDECL 
   boot(const RuntimeConfiguration* config)
{   
   app = booter.boot(RuntimeBootstrapper::RuntimeConfigurationConstPtr(config));      
}

extern "C" TRENTINO_DLLEXPORT void TRENTINO_CDECL 
   bootDefault()
{  
   app = booter.boot(boost::make_shared<RuntimeConfiguration>());      
}

#pragma warning(push)
#pragma warning(disable:4297)

extern "C" TRENTINO_DLLEXPORT Trentino::ManagementInterface* TRENTINO_CDECL 
   getManagementInterface()
{
   if(app)
   {
      return &app->managementInterface();         
   }     
   else
   {
      // this is problematic here to throw a C++ exception if extern "C" clause is used:
      throw std::runtime_error("getManagementInterface() called before boot()!");
   }   
}

#pragma warning(pop)

extern "C" TRENTINO_DLLEXPORT void TRENTINO_CDECL shutdown()
{
   if(app)
   {
      booter.shutdown(app);
      app.reset();
   }
}
