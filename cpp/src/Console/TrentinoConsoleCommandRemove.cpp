// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright 2012 by Siemens AG. All rights reserved.
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
#include "TrentinoConsoleCommandRemove.h"

//specific
#include "../Runtime/TrentinoManagementInterface.h"
#include "TrentinoConsole.h"
#include "TrentinoConsoleContextAccessor.h"
#include "TrentinoConsoleOutputVisitor.h"
#include "./../Utils/TrentinoUtilsPerformanceHierarchyLogger.h"
#include "./../Utils/TrentinoUtilsPerformanceHierarchyLoggerWriter.h"

using Trentino::Console::CommandRemove;
using Trentino::Console::ContextAccessor;
using Trentino::Console::ContextAccessingCommand;
using namespace std;

//class CommandRemove
   //construction
CommandRemove::CommandRemove(const CommandArgs& commandArgs, const ContextAccessor& contextAccessor)
: ContextAccessingCommand(contextAccessor)
, mCommandArgs(commandArgs)
{}

//services
void CommandRemove::acceptOutputVisitor(Trentino::Console::OutputVisitor& visitor)
{
   visitor.visitCommandRemove(this);
}

void CommandRemove::execute()
{
   HLOGGER();
   Trentino::ManagementInterface* const iface =
      contextAccessor().managementInterface();
   if(!iface)
   {
      setErrorMessage(Trentino::Console::Errors::ManagementInterfaceNotAvailable);
      return;
   }
   const string id = commandArgs().identifier; 
   
// Component remove isn't supported yet
//   if (commandArgs().removeComponent)
//   {
//      setErrorMessage(iface->removeComponent(id));
//   }
//   else
   if (Trentino::Utils::constantExpression<bool>(true))
   {
      setErrorMessage(iface->remove(id));
   }
}
