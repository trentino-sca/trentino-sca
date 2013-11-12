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
#include "TrentinoConsoleCommandShutdown.h"

//standard
#include <exception>

//specific
#include "../Global/TrentinoGlobal.h"
#include "TrentinoConsoleOutputVisitor.h"
#include "TrentinoConsoleContext.h"
#include "./../Utils/TrentinoUtilsDynamicLibrary.h"
#include "./../Utils/TrentinoUtilsPerformanceHierarchyLogger.h"
#include "./../Utils/TrentinoUtilsPerformanceHierarchyLoggerWriter.h"
#include "./../Runtime/Core/TrentinoCoreBootstrappingExplicitLinkingInterface.h"

using Trentino::Utils::DynamicLibrary;
using Trentino::Utils::DynamicLibraryPtr;
using namespace Trentino::Console;
using namespace Trentino::Core::Bootstrapping;
using namespace std;

//class CommandShutdown
   //construction
CommandShutdown::CommandShutdown(Context& contextManager)
: ContextManagingCommand(contextManager)
{}

   //services
void CommandShutdown::execute()
{
   Context& context = currentContext();
   context.cleanUp();
}

void CommandShutdown::acceptOutputVisitor(OutputVisitor& v)
{
   v.visitCommandShutdown(this);   
}