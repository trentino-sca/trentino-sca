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
#include "LinkerImpl.h"
#include <iostream>
using namespace Trentino::Example::ValidContribution1;


//class LinkerImpl
//construction

LinkerImpl::LinkerImpl(){}

LinkerImpl ::~LinkerImpl(){}

//methods

void LinkerImpl::executeLinker(int versionID)
{
	std::cout << "executeLinker service of Linker Component has been running with version ID: " << versionID << std::endl;
	//mLogger->log("log service is called from executeLinker service of LinkerImpl");
	(*(mLoggers.begin()))->log("log service is called from executeLinker service of LinkerImpl");
}

void LinkerImpl::setLog(const std::list<Logger*>& loggers)
{

      std::cout << "Logger reference of LinkerImpl is being set "<< std::endl;

      mLoggers = loggers;

 

      for( std::list<Logger*>::const_iterator it = mLoggers.begin()

      ; it != mLoggers.end()

      ; ++it)

   {

      (*it)->log("log service is triggered from setter of log ref of LinkerImpl");

   }

}


