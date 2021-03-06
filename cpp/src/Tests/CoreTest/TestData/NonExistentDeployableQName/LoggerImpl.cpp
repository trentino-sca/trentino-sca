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
#include "LoggerImpl.h"
#include <iostream>
#include <string>
using namespace Trentino::Example::Builder;


//class BuildImpl

//construction

LoggerImpl::LoggerImpl(){}

LoggerImpl ::~LoggerImpl(){}

//methods

void LoggerImpl::log(std::string logMsg)
{
	std::cout << "log service of LoggerImpl is called with logMsg: " << logMsg << std::endl;
	std::cout << "writeFile service is triggered by LoggerImpl (via its log service) logMsg:" << logMsg << std::endl;
	mFileLogger->writeFile(logMsg);
	std::cout << "writeConsole service is triggered by LoggerImpl (via its Log service) logMsg:" << logMsg << std::endl;
	mConsoleLogger->writeConsole(logMsg);
}

void  LoggerImpl::setFileLogger(LoggerFile* loggerFile)
{
	std::cout << "FileLogger reference of LoggerImpl is being set "<< std::endl;
	mFileLogger = loggerFile;
}

void  LoggerImpl::setConsoleLogger(LoggerConsole* loggerConsole)
{
	std::cout << "ConsoleLogger reference of LoggerImpl is being set "<< std::endl;	
	mConsoleLogger = loggerConsole;
}
