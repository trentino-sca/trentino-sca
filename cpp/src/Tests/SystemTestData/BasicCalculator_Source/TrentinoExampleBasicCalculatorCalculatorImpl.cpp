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

//specific
#include "TrentinoExampleBasicCalculatorCalculatorImpl.h"
#include <iostream>


using namespace Trentino::Example::BasicCalculator;
using namespace oasis::sca;

//class Calculator

//Construction

CalculatorImpl::CalculatorImpl() : mDivider(nullptr)
{
   //does nothing here
}

CalculatorImpl::~CalculatorImpl()
{
   //does nothing here
}

inline void  CalculatorImpl::setDivider(Divider* divider)
{
	std::cout<<"setter function is called"<<std::endl;
	mDivider = divider;
	for(int i=0; i< 1000 ; i++)
	{
   try{
       int res = mDivider->divide(i,4);
      }catch(std::runtime_error& ex){
           //do nothing
      }
	 
	}
	
	
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


