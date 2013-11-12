// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
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

#define TRENTINOEXAMPLEBASICCALCULATORREMOTE_IMPORT_EXPORT

//specific
#include "TrentinoExampleBasicCalculatorRemoteBasicCalculatorImpl.h"


using namespace Trentino::Example::BasicCalculatorRemote;

typedef Trentino::Example::BasicCalculatorRemote::BasicCalculator::ComplexNumber ComplexNumber;
typedef Trentino::Example::BasicCalculatorRemote::BasicCalculator::Address Address;
typedef Trentino::Example::BasicCalculatorRemote::BasicCalculator::Phone Phone;
typedef Trentino::Example::BasicCalculatorRemote::BasicCalculator::Person Person;
typedef Trentino::Example::BasicCalculatorRemote::BasicCalculator::TupleComplexNumber TupleComplexNumber;

//class Calculator

//Construction

BasicCalculatorImpl::BasicCalculatorImpl()
{

}

BasicCalculatorImpl::~BasicCalculatorImpl()
{
   //does nothing here
}

//services
	 ComplexNumber BasicCalculatorImpl::add (const ComplexNumber& a,const ComplexNumber& b){
	 ComplexNumber res;
	 res.set_a(a.a()+b.a());
	 res.set_b(a.b()+b.b());
	 return res;
	 }
	 
	 tint32_t BasicCalculatorImpl::addSimple (const tint32_t a,const tint32_t b){
	 return a+b;
	 }
	 ComplexNumber BasicCalculatorImpl::divide (const ComplexNumber& a,const ComplexNumber& b){
	 ComplexNumber res;
	 res.set_a(a.a()/b.a());
	 res.set_b(a.b()/b.b());
	 return res;
	 }
	 void BasicCalculatorImpl::multiply (const ComplexNumber& a,const ComplexNumber& b, ComplexNumber& c){
	 c.set_a(a.a()*b.a());
	 c.set_b(a.b()*b.b());
	 }
	 ComplexNumber BasicCalculatorImpl::divide2 (const TupleComplexNumber& tuple){
       ComplexNumber res = tuple.a();
	   return res;
	 }
	 tuint32_t BasicCalculatorImpl::calculateAge (const Person& person) throw (ValidationException){
	 ValidationException* exception = new ValidationException();
	 exception->set_details("There is no age information!...");
	  throw exception;
	 }


