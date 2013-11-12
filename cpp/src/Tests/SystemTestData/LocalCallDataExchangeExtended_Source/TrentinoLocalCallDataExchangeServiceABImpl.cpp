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

#include "TrentinoLocalCallDataExchangeServiceABImpl.h"
#include <iostream>

using namespace Trentino::LocalCallDataExchange;

Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceAImpl::method_with_two_parameters_first_by_value_second_by_reference( ClassA a, ClassB& b )
{
	std::cout << "-->IN ServiceAImpl : method_with_two_parameters_first_by_value_second_by_reference is returning with smth assigned to x of classC" << std::endl;

	ClassC res;
	if(a.a ==2 && b.elems.size()==2 && b.aObject.b ==1)
	{
		res.x = std::string("OK");
	}
	else
	{
		res.x = std::string("NOK");
	}
	b.aObject.b =2;
	std::cout << "-->OUT ServiceAImpl : method_with_two_parameters_first_by_value_second_by_reference" << std::endl;

	return res;
}

Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceAImpl::method_with_two_parameters_first_by_const_value_second_by_reference( const ClassA a, ClassB& b )
{
	std::cout << "-->IN ServiceAImpl : method_with_two_parameters_first_by_const_value_second_by_reference is redirected to serviceAImpl's method_with_two_parameters_first_by_value_second_by_reference" << std::endl;
	std::cout << "-->OUT ServiceAImpl : method_with_two_parameters_first_by_const_value_second_by_reference" << std::endl;

	return method_with_two_parameters_first_by_value_second_by_reference(a,b);
}

Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceAImpl::method_with_two_parameters_first_by_value_second_const_reference( ClassA a, const ClassB& b )
{
	std::cout << "-->IN ServiceAImpl : method_with_two_parameters_first_by_value_second_const_reference is returning with smth assigned to x of classC" << std::endl;
	ClassC res;
	if(a.a ==2 && b.elems.size()==2 && b.aObject.b ==1)
	{
		res.x = std::string("OK");
	}
	else
	{
		res.x = std::string("NOK");
	}
	std::cout << "-->OUT ServiceAImpl : method_with_two_parameters_first_by_value_second_const_reference" << std::endl;

	return res;
}


Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceAImpl::method_with_two_parameters_passed_by_value( ClassA a, ClassB b )
{
	std::cout << "-->IN ServiceAImpl : method_with_two_parameters_passed_by_value is redirected to serviceAImpl's method_with_two_parameters_first_by_value_second_const_reference" << std::endl;
	std::cout << "-->OUT ServiceAImpl : method_with_two_parameters_passed_by_value" << std::endl;
	return method_with_two_parameters_first_by_value_second_const_reference(a,b);
}

const ClassC Trentino::LocalCallDataExchange::ServiceAImpl::method_with_two_arguments_return_const_value( const ClassA& a, const ClassB& b )
{
	std::cout << "-->IN ServiceAImpl : method_with_two_arguments_return_const_value is returning with smth assigned to x of classC" << std::endl;

	ClassC res;
	if(a.a ==2 && b.elems.size()==2 && b.aObject.b ==1)
	{
		res.x = std::string("OK");
	}
	else
	{
		res.x = std::string("NOK");
	}
	std::cout << "-->OUT ServiceAImpl : method_with_two_arguments_return_const_value" << std::endl;

	return res;
}

const ClassC& Trentino::LocalCallDataExchange::ServiceAImpl::method_with_one_value_return_a_const_Reference( const ClassB& b )
{
	std::cout << "-->IN ServiceAImpl : method_with_one_value_return_a_const_Reference is redirected to serviceB impl for the same func" << std::endl;
	std::cout << "-->OUT ServiceAImpl : method_with_one_value_return_a_const_Reference" << std::endl;

    return mServiceB->method_with_one_value_return_a_const_Reference(b);
}

ClassC& Trentino::LocalCallDataExchange::ServiceAImpl::method_has_many_value_or_const_parameters( ClassA a, ClassB& b, const ClassC c, const ClassA a2, const ClassB& b2 )
{
	std::cout << "-->IN ServiceAImpl : method_has_many_value_or_const_parameters is redirected to serviceB impl for the same func" << std::endl;
	std::cout << "-->OUT ServiceAImpl : method_has_many_value_or_const_parameters" << std::endl;

	return mServiceB->method_has_many_value_or_const_parameters(a,b,c,a2,b2);
}

ClassC* Trentino::LocalCallDataExchange::ServiceAImpl::method_has_a_pointer_and_a_value_return_a_pointer( ClassA* a, ClassB b )
{
	std::cout << "-->IN ServiceAImpl : method_has_a_pointer_and_a_value_return_a_pointer is returning with smth assigned to x of classC" << std::endl;

	ClassC* res = new ClassC();
    if(a->a ==2 && b.elems.size()==2 && b.aObject.b ==1)
	{
      res->x = std::string("OK");
	}
	else
	{
		res->x = std::string("NOK");
	}
   b.aObject.b =2;
	std::cout << "-->OUT ServiceAImpl : method_has_a_pointer_and_a_value_return_a_pointer" << std::endl;

   return res;
   }

ClassC* Trentino::LocalCallDataExchange::ServiceAImpl::method_has_two_pointers_return_a_pointer( ClassA* a, ClassB* b )
{
	std::cout << "-->IN ServiceAImpl : method_has_two_pointers_return_a_pointer is redirected to serviceAImpl's method_has_two_const_pointers_return_a_pointer" << std::endl;
	std::cout << "-->OUT ServiceAImpl : method_has_two_pointers_return_a_pointer" << std::endl;
	
	return method_has_two_const_pointers_return_a_pointer(a,b);
}

ClassC* Trentino::LocalCallDataExchange::ServiceAImpl::method_has_two_const_pointers_return_a_pointer( const ClassA* a, const ClassB* b )
{
	std::cout << "-->IN ServiceAImpl : method_has_two_const_pointers_return_a_pointer is redirected to serviceB impl for the same func" << std::endl;
	std::cout << "-->OUT ServiceAImpl : method_has_two_const_pointers_return_a_pointer" << std::endl;
	return mServiceB->method_has_two_const_pointers_return_a_pointer(a,b);
}

ClassC* Trentino::LocalCallDataExchange::ServiceAImpl::method_has_a_template_class_as_argument( const std::vector<ClassA>& valuesOfA )
{
	std::cout << "-->IN ServiceAImpl : method_has_a_template_class_as_argument is redirected to serviceB impl for the same func" << std::endl;
	std::cout << "-->OUT ServiceAImpl : method_has_a_template_class_as_argument" << std::endl;

	return (*mServiceB).method_has_a_template_class_as_argument(valuesOfA);
}

void Trentino::LocalCallDataExchange::ServiceAImpl::setServiceB( ServiceB* val )
   {
    mServiceB = val; 
	std::cout << "ServiceB interfaced reference of ServiceAImpl is set  " << std::endl;

	
	ClassA* classA =  new ClassA();
	classA->a = 4;
	classA->b = 4;
	classA->c = "c member of ClassA";
	ClassB classB;
	classB.aObject.a = 23;
	classB.aObject.b = 9;
	classB.aObject.c =  "c member of ClassC";
	classB.elems.push_back("Trentino System Test trial");

	ClassC classC2;
	classC2.a = 20;
	classC2.b = 3;
	classC2.c = "c of ClassC2";
	classC2.x = "x of ClassC2 of setter function";
	
	std::cout<<"Arguments dump: 1st oaram classA*: a-> "<< classA->a << " b->: " << classA->b << " c->: " << classA->c << std::endl;
	std::cout<<"Arguments dump: 2nd param classB: aObject.a-> "<< classB.aObject.a << " aObject.a->: " << classB.aObject.b << " aObject.c->: " << classB.aObject.c << " elems.count: " << classB.elems.size() << std::endl;
	
	// FINE
	std::cout << "--> method_has_a_pointer_and_a_value_return_a_pointer method of ServiceB interfaced reference of ServiceAImpl" << std::endl;
	ClassC* classC = mServiceB->method_has_a_pointer_and_a_value_return_a_pointer(classA, classB);
	std::cout << "<-- method_has_a_pointer_and_a_value_return_a_pointer returns ClassC* ClassC->c" << classC->x << std::endl;
	delete classC;
	std::cout << "--> method_has_a_template_class_as_argument method of ServiceB interfaced reference of ServiceAImpl" << std::endl;
	std::vector<ClassA> classAVector;
	classAVector.push_back(*classA);
	ClassC* classCptr8 =mServiceB->method_has_a_template_class_as_argument(classAVector);
	std::cout << "<-- method_has_a_template_class_as_argument method of ServiceB interfaced reference of ServiceAImpl: ClassC->c" << classCptr8->x << std::endl;
	delete classCptr8; 
	
	//problem with reference as return type
	std::cout << "--> method_has_many_value_or_const_parameters method of ServiceB interfaced reference of ServiceAImpl" << std::endl;
	const ClassC& classC5 = mServiceB->method_has_many_value_or_const_parameters(*classA,classB,classC2,*classA,classB);
	std::cout << "<-- method_has_many_value_or_const_parameters returns ClassC&: ClassC->x" << classC5.x << std::endl;
	delete &classC5;
	//const ClassC& classC3 = deneme();
	//const ClassC& classc4 = deneme2();
	//const ClassC& classC5 = denemeB();
	//const ClassC& classc6 = denemeB2();
	//
	//int y = 9;
	
	std::cout << "--> method_has_two_const_pointers_return_a_pointer method of ServiceB interfaced reference of ServiceAImpl" << std::endl;
	ClassC* newCptr = mServiceB->method_has_two_const_pointers_return_a_pointer(classA,&classB);
	std::cout << "<-- method_has_two_const_pointers_return_a_pointer returns ClassC* ClassC->c" << newCptr->x << std::endl;
	delete newCptr;
	
	std::cout << "--> method_has_two_pointers_return_a_pointer method of ServiceB interfaced reference of ServiceAImpl" << std::endl;
	newCptr = mServiceB->method_has_two_pointers_return_a_pointer(classA,&classB);
	std::cout << "<-- method_has_two_pointers_return_a_pointer returns ClassC* ClassC->c" << newCptr->x << std::endl;
	delete newCptr;
	//problem
	std::cout << "--> method_with_one_value_return_a_const_Reference method of ServiceB interfaced reference of ServiceAImpl" << std::endl;
	ClassC& classC28 = const_cast<ClassC&>(mServiceB->method_with_one_value_return_a_const_Reference(classB));
	std::cout << "<-- method_with_one_value_return_a_const_Reference returns ClassC& ClassC->c" << classC28.x << std::endl;
	delete &classC28;
	
	std::cout << "--> method_with_two_arguments_return_const_value method of ServiceB interfaced reference of ServiceAImpl" << std::endl;
	classC2 = mServiceB->method_with_two_arguments_return_const_value(*classA,classB);
	std::cout << "<-- method_with_two_arguments_return_const_value returns ClassC ClassC->c" << classC2.x << std::endl;
	
	std::cout << "--> method_with_two_parameters_first_by_const_value_second_by_reference method of ServiceB interfaced reference of ServiceAImpl" << std::endl;
	classC2 = mServiceB->method_with_two_parameters_first_by_const_value_second_by_reference(*classA,classB);
	std::cout << "<-- method_with_two_parameters_first_by_const_value_second_by_reference returns ClassC ClassC->c" << classC2.x << std::endl;
	
	std::cout << "--> method_with_two_parameters_first_by_value_second_by_reference method of ServiceB interfaced reference of ServiceAImpl" << std::endl;
	classC2 = mServiceB->method_with_two_parameters_first_by_value_second_by_reference(*classA,classB);
	std::cout << "<-- method_with_two_parameters_first_by_value_second_by_reference returns ClassC ClassC->c" << classC2.c << std::endl;
	
	std::cout << "--> method_with_two_parameters_first_by_value_second_const_reference method of ServiceB interfaced reference of ServiceAImpl" << std::endl;
	classC2 = mServiceB->method_with_two_parameters_first_by_value_second_const_reference(*classA,classB);
	std::cout << "<-- method_with_two_parameters_first_by_value_second_const_reference returns classC ClassC->c" << classC2.x << std::endl;
	
	std::cout << "--> method_with_two_parameters_passed_by_value method of ServiceB interfaced reference of ServiceAImpl" << std::endl;
	classC2 = mServiceB->method_with_two_parameters_passed_by_value(*classA,classB);
	std::cout << "<-- method_with_two_parameters_passed_by_value returns ClassC->c" << classC2.x << std::endl;

	
	std::cout << "--> method_take_and_return_pointer_of_pointer method of ServiceB interfaced reference of ServiceAImpl" << std::endl;
	const ClassA aXXX;
	
	//ClassA* aPtr= ;
	const ClassA* prtA = &aXXX;
	const ClassA** ptrAA = &prtA;


	//const ClassA** prtA = const_cast<ClassA**>(&classA);
	ClassC** classCptrToPtr = mServiceB->method_take_and_return_pointer_of_pointer(ptrAA);
	std::cout << "<-- method_take_and_return_pointer_of_pointer returns ClassC**->c" << (**classCptrToPtr).x << std::endl;
	//delete *classCptrToPtr;
   }

Trentino::LocalCallDataExchange::ClassC& Trentino::LocalCallDataExchange::ServiceAImpl::deneme(  )
{
	ClassC classCmuge2;
	

	classCmuge2.a = 24;
	classCmuge2.b =4;
	classCmuge2.c =  "c member of ClassC";
	classCmuge2.x = "Trentino is running olaaaaaa from method_has_many_value_or_const_parameters!!!";
	return classCmuge2;

}
 Trentino::LocalCallDataExchange::ClassC& Trentino::LocalCallDataExchange::ServiceAImpl::deneme2(  )
{
	ClassC* classCmuge = new ClassC();
	
	classCmuge->a = 24;
	classCmuge->b =4;
	classCmuge->c =  "c member of ClassC";
	classCmuge->x = "Trentino is running olaaaaaa from method_has_many_value_or_const_parameters!!!";
	return *classCmuge;
}


Trentino::LocalCallDataExchange::ClassC** Trentino::LocalCallDataExchange::ServiceAImpl::method_take_and_return_pointer_of_pointer( const Trentino::LocalCallDataExchange::ClassA** a )
   {
   ClassC* val = new ClassC;


   if((**a).a==2){
         val->x ="OK";
      }
   return &val;
   }

 Trentino::LocalCallDataExchange::ClassC& Trentino::LocalCallDataExchange::ServiceBImpl::denemeB(  )
{
	ClassC classCmuge2;
	

	classCmuge2.a = 24;
	classCmuge2.b =4;
	classCmuge2.c =  "c member of ClassC";
	classCmuge2.x = "Trentino is running olaaaaaa from method_has_many_value_or_const_parameters!!!";
	return classCmuge2;

}
 Trentino::LocalCallDataExchange::ClassC& Trentino::LocalCallDataExchange::ServiceBImpl::denemeB2(  )
{
	ClassC* classCmuge = new ClassC();
	
	classCmuge->a = 24;
	classCmuge->b =4;
	classCmuge->c =  "c member of ClassC";
	classCmuge->x = "Trentino is running olaaaaaa from method_has_many_value_or_const_parameters!!!";
	return *classCmuge;
}
Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceBImpl::method_with_two_parameters_passed_by_value( ClassA a, ClassB b )
{
	ClassC classC;
	std::cout<<"Arguments dump: 1st param classA: a-> "<< a.a << " b->: " << a.b << " c->: " << a.c << std::endl;
	std::cout<<"Arguments dump: 2nd param classB: aObject.a-> "<< b.aObject.a << " aObject.a->: " << b.aObject.b << " aObject.c->: " << b.aObject.c << " elems.count: " << b.elems.size() << std::endl;
	
	classC.a = 24;
	classC.b =4;
	classC.c =  "c member of ClassC";
	classC.x = "Trentino is running olaaaaaa from method_with_two_parameters_passed_by_value!!!";

	return classC;
}

Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceBImpl::method_with_two_parameters_first_by_value_second_by_reference( ClassA a, ClassB& b )
{
	ClassC classC;
	std::cout<<"Arguments dump: 1st param classA: a-> "<< a.a << " b->: " << a.b << " c->: " << a.c << std::endl;
	std::cout<<"Arguments dump: 2nd param classB&: aObject.a-> "<< b.aObject.a << " aObject.a->: " << b.aObject.b << " aObject.c->: " << b.aObject.c << " elems.count: " << b.elems.size() << std::endl;
	
	classC.a = 24;
	classC.b =4;
	classC.c =  "c member of ClassC";
	classC.x = "Trentino is running olaaaaaa from method_with_two_parameters_first_by_value_second_by_reference!!!";
	return classC;
}

Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceBImpl::method_with_two_parameters_first_by_const_value_second_by_reference( const ClassA a, ClassB& b )
{
	ClassC classC;
	std::cout<<"Arguments dump: 1st param const classA: a-> "<< a.a << " b->: " << a.b << " c->: " << a.c << std::endl;
	std::cout<<"Arguments dump: 2nd param classB&: aObject.a-> "<< b.aObject.a << " aObject.a->: " << b.aObject.b << " aObject.c->: " << b.aObject.c << " elems.count: " << b.elems.size() << std::endl;
	
	classC.a = 24;
	classC.b =4;
	classC.c =  "c member of ClassC";
	classC.x = "Trentino is running olaaaaaa from method_with_two_parameters_first_by_const_value_second_by_reference!!!";
	return classC;
}

Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceBImpl::method_with_two_parameters_first_by_value_second_const_reference( ClassA a, const ClassB& b )
{
	ClassC classC;
	std::cout<<"Arguments dump: 1st param classA: a-> "<< a.a << " b->: " << a.b << " c->: " << a.c << std::endl;
	std::cout<<"Arguments dump: 2nd param classB&: aObject.a-> "<< b.aObject.a << " aObject.a->: " << b.aObject.b << " aObject.c->: " << b.aObject.c << " elems.count: " << b.elems.size() << std::endl;
	
	classC.a = 24;
	classC.b =4;
	classC.c =  "c member of ClassC";
	classC.x = "Trentino is running olaaaaaa from method_with_two_parameters_first_by_value_second_const_reference!!!";
	return classC;
}

const ClassC Trentino::LocalCallDataExchange::ServiceBImpl::method_with_two_arguments_return_const_value( const ClassA& a, const ClassB& b )
{
	ClassC classC;
	std::cout<<"Arguments dump: 1st param classA&: a-> "<< a.a << " b->: " << a.b << " c->: " << a.c << std::endl;
	std::cout<<"Arguments dump: 2nd param classB&: aObject.a-> "<< b.aObject.a << " aObject.a->: " << b.aObject.b << " aObject.c->: " << b.aObject.c << " elems.count: " << b.elems.size() << std::endl;
	
	classC.a = 24;
	classC.b =4;
	classC.c =  "c member of ClassC";
	classC.x = "Trentino is running olaaaaaa from method_with_two_arguments_return_const_value!!!";
	return classC;
}

const ClassC& Trentino::LocalCallDataExchange::ServiceBImpl::method_with_one_value_return_a_const_Reference( const ClassB& b )
{
	ClassC* classC = new ClassC();
	std::cout<<"Arguments dump: 1st paam classB&: aObject.a-> "<< b.aObject.a << " aObject.a->: " << b.aObject.b << " aObject.c->: " << b.aObject.c << " elems.count: " << b.elems.size() << std::endl;
	
	classC->a = 24;
	classC->b =4;
	classC->c =  "c member of ClassC";
	classC->x = "Trentino is running olaaaaaa from method_with_one_value_return_a_const_Reference!!!";
	return *classC;
  
}

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1, c.x="OK", a2.a is 1 and b2.aObject.b is 2
ClassC& Trentino::LocalCallDataExchange::ServiceBImpl::method_has_many_value_or_const_parameters( ClassA a, ClassB& b, const ClassC c, const ClassA a2, const ClassB& b2 )
{
	
	ClassC* classC = new ClassC();
	std::cout<<"Arguments dump: 1st param classA: a-> "<< a.a << " b->: " << a.b << " c->: " << a.c << std::endl;
	std::cout<<"Arguments dump: 2nd param &classB: aObject.a-> "<< b.aObject.a << " aObject.a->: " << b.aObject.b << " aObject.c->: " << b.aObject.c << " elems.count: " << b.elems.size() << std::endl;
	std::cout<<"Arguments dump: 3rd param const classC: a-> "<< c.a << " b->: " << c.b << " c->: " << c.c << "x->:" << c.x << std::endl;
	std::cout<<"Arguments dump: 4th param const classA: a-> "<< a2.a << " b->: " << a2.b << " c->: " << a2.c << std::endl;
	std::cout<<"Arguments dump: 5th param &classB: aObject.a-> "<< b2.aObject.a << " aObject.a->: " << b2.aObject.b << " aObject.c->: " << b2.aObject.c << " elems.count: " << b2.elems.size() << std::endl;
	
	classC->a = 24;
	classC->b =4;
	classC->c =  "c member of ClassC";
	classC->x = "Trentino is running olaaaaaa from method_has_many_value_or_const_parameters!!!";

	return *classC;
}
//tested
ClassC* Trentino::LocalCallDataExchange::ServiceBImpl::method_has_a_pointer_and_a_value_return_a_pointer( ClassA* a, ClassB b )
{
	ClassC* classC = new ClassC();
	std::cout<<"Arguments dump: 1st oaram classA*: a-> "<< a->a << " b->: " << a->b << " c->: " << a->c << std::endl;
	std::cout<<"Arguments dump: 2nd param classB: aObject.a-> "<< b.aObject.a << " aObject.a->: " << b.aObject.b << " aObject.c->: " << b.aObject.c << " elems.count: " << b.elems.size() << std::endl;
	
	classC->a = 24;
	classC->b =4;
	classC->c =  "c member of ClassC*";
	classC->x = "Trentino is running olaaaaaa from method_has_a_pointer_and_a_value_return_a_pointer!!!";

	return classC;
}
//tested
ClassC* Trentino::LocalCallDataExchange::ServiceBImpl::method_has_two_pointers_return_a_pointer( ClassA* a, ClassB* b )
{
	ClassC* classC =  new ClassC();
	std::cout<<"Arguments dump: 1st param classA* : a-> "<< a->a << " b->: " << a->b << " c->: " << a->c << std::endl;
	std::cout<<"Arguments dump: 2nd param classB* : aObject.a-> "<< b->aObject.a << " aObject.a->: " << b->aObject.b << " aObject.c->: " << b->aObject.c << " elems.count: " << b->elems.size() << std::endl;
	
	classC->a = 24;
	classC->b =4;
	classC->c =  "c member of ClassC";
	classC->x = "Trentino is running olaaaaaa from method_has_two_pointers_return_a_pointer!!!";

	return classC;
}

//tested
ClassC* Trentino::LocalCallDataExchange::ServiceBImpl::method_has_two_const_pointers_return_a_pointer( const ClassA* a, const ClassB* b )
{
	ClassC* classC =  new ClassC();
	std::cout<<"Arguments dump: 1st param const classA* : a-> "<< a->a << " b->: " << a->b << " c->: " << a->c << std::endl;
	std::cout<<"Arguments dump: 2nd param const classB*: aObject.a-> "<< b->aObject.a << " aObject.a->: " << b->aObject.b << " aObject.c->: " << b->aObject.c << " elems.count: " << b->elems.size() << std::endl;
	
	classC->a = 24;
	classC->b =4;
	classC->c =  "c member of ClassC";
	classC->x = "Trentino is running olaaaaaa from method_has_two_const_pointers_return_a_pointer!!!";

	return classC;
}

ClassC* Trentino::LocalCallDataExchange::ServiceBImpl::method_has_a_template_class_as_argument( const std::vector<ClassA>& valuesOfA )
{
	std::cout<<"Arguments dump: 1st param std::vector<ClassA>& valuesOfA : size of vector "<< valuesOfA.size() << std::endl;
	
	ClassC* res = new ClassC();
	res->x = "Trentino is running olaaaaaa from method_has_a_template_class_as_argument!!!";
    
	return res;
}

Trentino::LocalCallDataExchange::ClassC** Trentino::LocalCallDataExchange::ServiceBImpl::method_take_and_return_pointer_of_pointer( const Trentino::LocalCallDataExchange::ClassA** a )
{
	std::cout<<"Arguments dump: 1st param ClassA** a: "<< (**a).a << "b: "<< (**a).b <<" c:" << (**a).c << std::endl;
	
    ClassC* val = new ClassC();

	val->x="Trentino is running olaaaaa from method_take_and_return_pointer_of_pointer";
   return &val;
}

void Trentino::LocalCallDataExchange::ServiceBImpl::setServiceA( ServiceA* val )
{
    mServiceA = val;
	std::cout << "ServiceA interfaced reference of ServiceBImpl is set  " << std::endl;
	/*std::cout << "ServiceA service of ServiceBImpl is called with" << std::endl;
	mServiceA->method_has_a_pointer_and_a_value_return_a_pointer();
	mServiceA->method_has_a_template_class_as_argument();
	mServiceA->method_has_many_value_or_const_parameters();
	mServiceA->method_has_two_const_pointers_return_a_pointer();
	mServiceA->method_has_two_pointers_return_a_pointer();
	mServiceA->method_with_one_value_return_a_const_Reference();
	mServiceA->method_with_two_arguments_return_const_value();
	mServiceA->method_with_two_parameters_first_by_const_value_second_by_reference();
	mServiceA->method_with_two_parameters_first_by_value_second_by_reference();
	*/
}
