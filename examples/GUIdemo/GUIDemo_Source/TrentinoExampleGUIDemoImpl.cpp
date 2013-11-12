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

//standard
#include <oasis/sca/ComponentContext.h>

//specific
#include "TrentinoExampleGUIDemoImpl.h"
#include <iostream>


using namespace Trentino::Example::GUIDemo;
using namespace oasis::sca;

//class GUIDemo

//Construction

GUIDemoImpl::GUIDemoImpl() : mLCD(nullptr)
{
	std::cout << "GUIDemoImpl::GUIDemoImpl()" << std::endl;

   //does nothing here
}

GUIDemoImpl::~GUIDemoImpl()
{

	void *ptr;

	ptr = startGuiThreaded();

	if (ptr !=  NULL)
		stopGuiThreaded(ptr);
	//does nothing here
}

//services
/*int GUIDemoImpl::add(int a, int b)
{
	std::cout << "CalculatorImpl::add" << std::endl;
	std::cout << "add service of calculator interface is called " << a <<"+" << b << std::endl;
	return a+b;
}

//example with dependency injection
int CalculatorImpl::div(int a, int b)
{
	std::cout << "CalculatorImpl::div" << std::endl;
	std::cout << "div service of calculator interface is called " << a <<"+" << b << std::endl;
	int result = mDivider->divide(a,b);
	return result;
}*/


