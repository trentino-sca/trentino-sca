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
#include "TrentinoConsoleCommandBoot.h"

//standard
#include <string>
#include <exception>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/filesystem/path.hpp>

//specific
#include "../Global/TrentinoGlobal.h"
#include "TrentinoConsole.h"
#include "TrentinoConsoleOutputVisitor.h"
#include "TrentinoConsoleContext.h"
#include "TrentinoConsoleConfiguration.h"
#include "TrentinoConsoleParser.h"
#include "./../Utils/TrentinoUtilsDynamicLibrary.h"
#include "./../Utils/TrentinoUtilsEnvironment.h"
#include "./../Utils/TrentinoUtilsPerformanceHierarchyLogger.h"
#include "./../Utils/TrentinoUtilsPerformanceHierarchyLoggerWriter.h"
#include "./../Runtime/Core/TrentinoCoreRuntimeAPI.h"


using Trentino::Utils::DynamicLibrary;
using Trentino::Utils::DynamicLibraryPtr;
namespace Environment = Trentino::Utils::Environment;
namespace fs = boost::filesystem;
using namespace Trentino::Console;
using namespace Trentino::Core::Bootstrapping;
using namespace std;


//class CommandBoot
   //construction
CommandBoot::CommandBoot(Context& contextManager, const std::string& commandLine)
: ContextManagingCommand(contextManager), mCommandLine(commandLine)
{}

   //services
void CommandBoot::execute()
{
   HLOGGER();
   Context& context = currentContext();
   if(context.runtimeAPI().get() != nullptr) //runtime API already loaded
   {
      setErrorMessage(
         "Cannot boot more then once: Trentino Runtime already loaded into the current process");
      return;
   }

   const fs::path runtimeDLLPath = 
      fs::path( Environment::executablePath() ).parent_path() /
      fs::path( globalConfiguration->runtimeDLLPath() ) /
      fs::path( Environment::makeDLLName(globalConfiguration->runtimeDLLName()) );
   std::string config ="";
   if(mCommandLine.size() >4)
      {
      config = mCommandLine.substr(5);
      }
   Trentino::Core::RuntimeAPIPtr runtimeAPIPtr;
   try
   {
      runtimeAPIPtr = 
         boost::make_shared<Trentino::Core::RuntimeAPI>(runtimeDLLPath.string(), config);
   }
   catch(exception& e)
   {
      setErrorMessage(e.what());      
      return;
   }

   context.setRuntimeAPI(runtimeAPIPtr);
   runtimeAPIPtr->managementInterface()->setOwnerProcessExceptionHandler(&(Trentino::Console::Parser::scheduleExceptionAction));
}


void CommandBoot::acceptOutputVisitor(OutputVisitor& v)
{
   v.visitCommandBoot(this);   
}
