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
#include "BuilderImpl.h"
#include <iostream>
using namespace Trentino::Example::Builder;


//class BuildImpl

//construction

BuilderImpl::BuilderImpl(){}

BuilderImpl ::~BuilderImpl(){}

//methods

void BuilderImpl::build(int versionID)
{
	std::cout << "build service of BuilderImpl is called with version ID: " << versionID << std::endl;
	std::cout << "executeLinker service is triggered by BuilderImpl (via Build service) version ID:" << versionID << std::endl;
	mExecuteLinker->executeLinker(versionID);
	std::cout << "excecuteCompiler service is triggered by BuilderImpl (via Build service) version ID: " << versionID << std::endl;
	mExecuteCompiler->executeCompiler(versionID);
}

void  BuilderImpl::setExecuteLinker(ExecuteLinker* executeLinker)
{
	std::cout << "ExecuteLinker reference of BuilderImpl is being set "<< std::endl;
	mExecuteLinker = executeLinker;
}

void  BuilderImpl::setExecuteCompiler(ExecuteCompiler* executeCompiler)
{
	std::cout << "executeCompiler reference of BuilderImpl is being set "<< std::endl;	
	mExecuteCompiler = executeCompiler;
}
