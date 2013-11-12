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

#define TRENTINOEXAMPLEBASICCALCULATORREMOTECLIENT_IMPORT_EXPORT

//specific
#include "TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorImpl.h"
#include <iostream>
#include <algorithm>
using namespace Trentino::Example::BasicCalculatorRemoteClient;

//class Calculator

//Construction

BasicCalculatorRemoteClientImpl::BasicCalculatorRemoteClientImpl()
{

}

BasicCalculatorRemoteClientImpl::~BasicCalculatorRemoteClientImpl()
{
   //does nothing here
}

//services
	 ComplexNumber BasicCalculatorRemoteClientImpl::add (const ComplexNumber& a,const ComplexNumber& b){
	 ComplexNumber res;
	 res.set_a(a.a()+b.a());
	 res.set_b(a.b()+b.b());
	 return res;
	 }
	 
	 tint32_t BasicCalculatorRemoteClientImpl::addSimple (const tint32_t a,const tint32_t b){
	 return a+b;
	 }
	 ComplexNumber BasicCalculatorRemoteClientImpl::divide (const ComplexNumber& a,const ComplexNumber& b){
	 ComplexNumber res;
	 res.set_a(a.a()/b.a());
	 res.set_b(a.b()/b.b());
	 return res;
	 }
	 void BasicCalculatorRemoteClientImpl::multiply (const ComplexNumber& a,const ComplexNumber& b, ComplexNumber& c){
	 c.set_a(a.a()*b.a());
	 c.set_b(a.b()*b.b());
	 }
	 ComplexNumber BasicCalculatorRemoteClientImpl::divide2 (const TupleComplexNumber& tuple){
       ComplexNumber res = tuple.a();
	   return res;
	 }
	 tuint32_t BasicCalculatorRemoteClientImpl::calculateAge (const Person& person) throw (ValidationException){
	  ValidationException* exception = new ValidationException();
	  exception->set_details("There is no age information!...");
	  throw exception;
	 }

	 std::string BasicCalculatorRemoteClientImpl::changeString (const std::string& str){
		std::string s = "FSTART!";
		s.append(str);
		s.append("FINISHED!");
		std::replace( s.begin(), s.end(), 'F', '*'); // replace all 'x' to 'y'
		return s;
	 }
	 
	 void BasicCalculatorRemoteClientImpl::setBasicCalculatorRef(BasicCalculator* basicCalc)
	 {
		std::cout << "BasicCalculatorRef reference of BasicCalculatorImpl is being set "<< std::endl;	
		m_basicCalc = basicCalc;

		int i = m_basicCalc->addSimple(3,5);
		std::cout<< "addSimple returned :"<< i<< std::endl;
		
		char* longtext = new char[100000]; // 100 KB
		for (int i = 0; i< 100; i++)
			longtext[i] = 'F';

		for (int i = 1000; i< 2000; i++)
			longtext[i] = 'F';

		for (int i = 90000; i< 91000; i++)
			longtext[i] = 'F';

		std::string s = m_basicCalc->changeString(longtext);
		std::cout<< "changeString returned :"<< s<< std::endl;
	 }



