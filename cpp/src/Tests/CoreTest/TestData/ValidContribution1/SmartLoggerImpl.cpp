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
#include "SmartLoggerImpl.h"
#include <iostream>
using namespace Trentino::Example::ValidContribution1;


//class SmartLoggerImpl

//construction

SmartLoggerImpl::SmartLoggerImpl(){}

SmartLoggerImpl ::~SmartLoggerImpl(){}

//methods

void SmartLoggerImpl::write(std::string logMsg)
{
	std::cout << "write service of SmartLoggerImpl is called with log message: " << logMsg << std::endl;

}

void SmartLoggerImpl::writeFile(std::string logMsg)
{
	std::cout << "write service of SmartLoggerImpl is called with log message: " << logMsg << std::endl;

}
void SmartLoggerImpl::writeConsole(std::string logMsg)
{
	std::cout << "write service of SmartLoggerImpl is called with log message: " << logMsg << std::endl;

}

