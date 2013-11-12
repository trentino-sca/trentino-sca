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

#define TRENTINO_EXAMPLE_BASICPRINTER_IMPORT_EXPORT

//specific
#include "TrentinoExampleBasicPrinterImpl2.h"

using namespace Trentino::Example;

typedef Trentino::Example::BasicPrinter::ComplexNumber ComplexNumber;
typedef Trentino::Example::BasicPrinter::Address Address;
typedef Trentino::Example::BasicPrinter::Phone Phone;
typedef Trentino::Example::BasicPrinter::Person Person;
typedef Trentino::Example::BasicPrinter::TupleComplexNumber TupleComplexNumber;

BasicPrinterImpl2::BasicPrinterImpl2()
{
	
}

BasicPrinterImpl2::~BasicPrinterImpl2()
{
   //does nothing here
}

//services
	 ComplexNumber BasicPrinterImpl2::add (const ComplexNumber& a,const ComplexNumber& b){
	 ComplexNumber res;
	 res.set_a(a.a()+b.a());
	 res.set_b(a.b()+b.b());
	 return res;
	 }
	 // floor=4, colour=yellow -----> a+b 
	 tint32_t BasicPrinterImpl2::addSimple (const tint32_t a,const tint32_t b){
		printf("floor=4, color=yellow\n");
		return a+b;
	 }
	 ComplexNumber BasicPrinterImpl2::divide (const ComplexNumber& a,const ComplexNumber& b){
	 ComplexNumber res;
	 res.set_a(a.a()/b.a());
	 res.set_b(a.b()/b.b());
	 return res;
	 }
	 void BasicPrinterImpl2::multiply (const ComplexNumber& a,const ComplexNumber& b, ComplexNumber& c){
	 c.set_a(a.a()*b.a());
	 c.set_b(a.b()*b.b());
	 }
	 ComplexNumber BasicPrinterImpl2::divide2 (const TupleComplexNumber& tuple){
       ComplexNumber res = tuple.a();
	   return res;
	 }
	 tuint32_t BasicPrinterImpl2::calculateAge (const Person& person) throw (ValidationException){
	 ValidationException* exception = new ValidationException();
	 exception->set_details("There is no age information!...");
	  throw exception;
	 }


