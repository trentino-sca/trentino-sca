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

//specific
#include "services/TrentinoExampleLoggingLoggingServiceImpl.h"
#include <iostream>


using namespace Trentino::Example::Logging;


//class Calculator

//Construction
namespace
{
	void doLog (const char* level, const char* msg)
	{
	std::cout<<"["<<level<<"] "<<msg<<std::endl;
	}
}


LoggingServiceImpl::LoggingServiceImpl()
{
   //does nothing here
}

LoggingServiceImpl::~LoggingServiceImpl()
{
   //does nothing here
}

 void  LoggingServiceImpl::setLoggerName(const std::string& name)
{
	mLoggerName = name;
}

//services
 void LoggingServiceImpl::logError(const char* log)
 {
 doLog("Error",log);
 }
 void LoggingServiceImpl::logDebug(const char* log)
 {
  doLog("Debug",log);
 }
 
 void LoggingServiceImpl::logInfo(const char* log)
 {
  doLog("Info",log);
 }


