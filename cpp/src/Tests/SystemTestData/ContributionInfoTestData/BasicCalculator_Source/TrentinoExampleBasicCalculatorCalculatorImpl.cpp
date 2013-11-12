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
#include "TrentinoExampleBasicCalculatorCalculatorImpl.h"
#include <iostream>


using namespace Trentino::Example::BasicCalculator;
using namespace oasis::sca;

//class Calculator

//Construction

CalculatorImpl::CalculatorImpl() : mDivider(nullptr), mComponentContext(nullptr)
{
   //does nothing here
}

CalculatorImpl::~CalculatorImpl()
{
   //does nothing here
}

//services
int CalculatorImpl::add(int a, int b)
{
	std::cout << "add service of calculator interface is called " << a <<"+" << b << std::endl;
	return a+b;
}

//example with dependency injection
int CalculatorImpl::div(int a, int b)
{
	std::cout << "div service of calculator interface is called " << a <<"+" << b << std::endl;
	int result = mDivider->divide(a,b);
	return result;
}

//example using component context

int CalculatorImpl::div2(int a, int b)
{
	std::cout << "div2 service of calculator interface is called " << a <<"+" << b << std::endl;
   ServiceProxyPtr service = mComponentContext->getService("divider");
	Divider* divider = dynamic_cast<Divider*>(service.ptr_);
	return divider->divide(a,b);
}


