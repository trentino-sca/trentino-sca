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

using namespace Trentino::Example::BasicCalculatorRemoteClient;
typedef BasicCalculator::ComplexNumber ComplexNumber;
typedef BasicCalculator::TupleComplexNumber TupleComplexNumber;
typedef BasicCalculator::Person Person;
typedef BasicCalculator::ComplexNumber ComplexNumber;

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
	 
	 void BasicCalculatorRemoteClientImpl::setBasicCalculatorRef(BasicCalculator* basicCalc)
	 {
		m_basicCalc = basicCalc;
	 }

void BasicCalculatorRemoteClientImpl::onInit()
{
         try{
		 
		  std::cout << "Calling initialization method "<< std::endl;	
		// addSimple
		int addSimpleRet = m_basicCalc->addSimple(3, 5);
		std::cout<<"addSimple returned " << addSimpleRet << std::endl;
		
		ComplexNumber* cn1 = new ComplexNumber();
		cn1->set_a(50);
		cn1->set_b(40);
		
		ComplexNumber* cn2 = new ComplexNumber();
		cn2->set_a(10);
		cn2->set_b(2);
		
		// add
		ComplexNumber addRet = m_basicCalc->add(*cn1, *cn2);
		std::cout<<"add returned " << addRet.a() <<" "<<addRet.b() << std::endl;
		
		// multiply
		ComplexNumber* cn3 = new ComplexNumber();
		m_basicCalc->multiply(*cn1, *cn2, *cn3);
		std::cout<<"multiply returned " << cn3->a() <<" "<<cn3->b() << std::endl;
		
		// divide
		ComplexNumber divideRet = m_basicCalc->divide(*cn1, *cn2);
		std::cout<<"divide returned " << divideRet.a() <<" "<<divideRet.b() << std::endl;
		
		// divide2
		TupleComplexNumber* tupleCN = new TupleComplexNumber();
		ComplexNumber& tupleCN1 = tupleCN->mutable_a();
		tupleCN1.set_a(cn1->a());
		tupleCN1.set_b(cn1->b());
		
		ComplexNumber& tupleCN2 = tupleCN->mutable_b();
		tupleCN2.set_a(cn2->a());
		tupleCN2.set_b(cn2->b());
		
		ComplexNumber divide2Ret = m_basicCalc->divide2(*tupleCN);
		std::cout<<"divide2 returned " << divide2Ret.a() <<" "<<divide2Ret.b() << std::endl;
		
		//calculateAge
		
		Person* child = new Person();
		child->set_name("ipek");
		child->set_surname("tatli");
		
		//int age = m_basicCalc->calculateAge(*child);
		//std::cout<<"calculateAge returned " << age  << std::endl; // DOES NOT WORK!
		 
		 }
		 catch(std::runtime_error& e){
		 std::cout << "Unexpected error during remote access of BasicCalculator Service " << e.what()<< std::endl;
		 }catch (...){
		 std::cout << "Unexpected error during remote access of BasicCalculator Service "<< std::endl;
		 }
       
}

