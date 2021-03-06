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
#include "TrentinoExampleBasicCalculatorDividerImpl.h"
#include <iostream>
using namespace Trentino::Example::BasicCalculator;


//class Divider

//construction

DividerImpl::DividerImpl(){}

DividerImpl ::~DividerImpl(){}

//methods

int DividerImpl::divide(int a, int b)
{
	std::cout << "divide service of Divider interface is called " << a <<"/" << b << std::endl;
   if( a % 10 ==0) {
      throw std::runtime_error("Simulate some runtime error");
      }

    return a/b;
}

