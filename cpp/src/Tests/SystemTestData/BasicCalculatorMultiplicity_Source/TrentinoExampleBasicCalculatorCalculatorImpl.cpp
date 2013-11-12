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
//#include <oasis/sca/ComponentContext.h>

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

inline void  CalculatorImpl::setDivider(std::list<Divider*> divider)
{
	std::cout<< mName <<": setter function is called"<<std::endl;
  

	mDivider = divider;

	 
	
	
	
}

//services
int CalculatorImpl::add(int a, int b)
{
	std::cout << mName<< ": add service of calculator interface is called " << a <<"+" << b << std::endl;
	return a+b;
}

//example with dependency injection
int CalculatorImpl::div(int a, int b)
{
   int result;
	std::cout<< mName << ": div service of calculator interface is called " << a <<"+" << b << std::endl;
    std::list<Divider*>::iterator it;
    for(it = mDivider.begin(); it!= mDivider.end(); ++it)
        {
         result = (*it)->divide(a,b);
        }
	return result;
}

inline void  CalculatorImpl::setName(std::string name)
{
    mName = name;
     std::list<Divider *>::iterator it;
    	for(int i=0; i< 10 ; i++)
	{
   try{
      int i = 1;
      for (it = mDivider.begin(); it != mDivider.end(); ++it)
         {
         std::cout<< mName <<": Calling service " << i++ <<std::endl;
         int res = (*it)->divide(i,4);
         }
      }catch(std::runtime_error& ex){
           //do nothing
      }
      }
    
}
