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
#include "TrentinoCoreContributionLoadingLoggingErrorHandler.h"

//specific
#include "./../../Utils/TrentinoUtilsLogging.h"

using Trentino::Core::ContributionLoading::LoggingErrorHandler;
using Trentino::Core::ContributionLoading::Error;
using Trentino::Core::ContributionLoading::Warning;

//class LoggingErrorHandler
   //construction
LoggingErrorHandler::LoggingErrorHandler()
{}

LoggingErrorHandler::~LoggingErrorHandler()
{}

   //services
void LoggingErrorHandler::issueError( Error /*error*/, const std::string& msg )
{
   //In case logging is turned off and logError() is defined to nothing, (void)msg ensures
   //that the "unreferenced formal parameter" warning won't be issued.  
   (void)msg; 
   logError("%s", msg.c_str());
}

void LoggingErrorHandler::issueWarning( Warning /*warning*/, const std::string& msg )
{
   //In case logging is turned off and logWarn() is defined to nothing, (void)msg ensures
   //that the "unreferenced formal parameter" warning won't be issued.  
   (void)msg;
   logWarn("%s", msg.c_str());
}
