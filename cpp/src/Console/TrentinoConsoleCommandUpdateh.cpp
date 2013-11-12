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
#include "TrentinoConsoleCommandUpdateh.h"

//specific
#include "../Runtime/TrentinoManagementInterface.h"
#include "TrentinoConsole.h"
#include "TrentinoConsoleContextAccessor.h"
#include "TrentinoConsoleOutputVisitor.h"
#include "./../Utils/TrentinoUtilsPerformanceHierarchyLogger.h"
#include "./../Utils/TrentinoUtilsPerformanceHierarchyLoggerWriter.h"

using Trentino::Console::CommandUpdate;
using Trentino::Console::ContextAccessor;
using Trentino::Console::ContextAccessingCommand;
using namespace std;

//class CommandUpdate
   //construction
CommandUpdate::CommandUpdate(const CommandArgs& commandArgs, const ContextAccessor& contextAccessor)
: ContextAccessingCommand(contextAccessor)
, mCommandArgs(commandArgs)
{}

//services
void CommandUpdate::acceptOutputVisitor(Trentino::Console::OutputVisitor& visitor)
{
   visitor.visitCommandUpdate(this);
}

void CommandUpdate::execute()
{  
   HLOGGER();
   Trentino::ManagementInterface* const iface =
      contextAccessor().managementInterface();
   if(!iface)
   {
      setErrorMessage(Trentino::Console::Errors::ManagementInterfaceNotAvailable);
      return;
   }

   Trentino::Utils::DataObject msg = Trentino::Utils::DataObject::newInstance("result");
   iface->update( commandArgs().pathToContribution
                                      , commandArgs().contributionBaseURI, msg);

   if(msg.empty())
   {
      setErrorMessage("Unknown error occurend during update");
      return;
   }
   std::string message = msg.getString("result");
   bool failed = msg.getBool("failed");
   if(failed)
   {
      setErrorMessage(message);
   }
   else
   {
      setUpdateStatus(message);
   }
}
