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
#include <agents.h>
#include <iostream>

using namespace Trentino::Example::BasicCalculator;
using namespace oasis::sca;

//=========================================================
class periodic_caller
{
private:
   static CalculatorImpl * mCalc;
   static Concurrency::call<int> * mCall;
   static Concurrency::timer<int> *mTimer;
public:
   static void Init(CalculatorImpl * Calc);
   static void deInit();
};

CalculatorImpl * periodic_caller::mCalc = nullptr;
Concurrency::call<int> * periodic_caller::mCall = nullptr;
Concurrency::timer<int> *periodic_caller::mTimer = nullptr;


void periodic_caller::Init(CalculatorImpl * Calc)
{
   mCalc = Calc;
   mCall = new Concurrency::call<int>( [](int x){
      if (mCalc!= nullptr) mCalc->div(100, x);
   } );
   mTimer = new Concurrency::timer<int> (5000, 10, mCall, true);
   mTimer->start();
}

void periodic_caller::deInit(void)
{
   mTimer->stop();
   delete mTimer;
   delete mCall;
}


//=========================================================




//class Calculator

//Construction

CalculatorImpl::CalculatorImpl()
{
   mLogging = nullptr;
   //does nothing here
}

CalculatorImpl::~CalculatorImpl()
{
   //does nothing here
  //periodic_caller::deInit();
}

 void  CalculatorImpl::setLoggingService(Trentino::Example::Logging::LoggingService* logging)
{
  mLogging = logging;
}

//services
int CalculatorImpl::add(int a, int b)
{
   log("add called");
	return a+b;
}

//example with dependency injection
int CalculatorImpl::div(int a, int b)
{
   try
   {
	log("Div called");
   }
   catch(std::runtime_error* &e)
   {
      std::cout << e->what() << "\n";
   }
   catch(...)
   {
      std::cout << "Unknown exception while calling div()!\n";
   }


	return a /b;
}

void CalculatorImpl::onInit()
{
div(4,2);
//periodic_caller::Init(this);

}

void CalculatorImpl::log(const char* log)
{
   if (mLogging!=nullptr) mLogging->logInfo(log);
}