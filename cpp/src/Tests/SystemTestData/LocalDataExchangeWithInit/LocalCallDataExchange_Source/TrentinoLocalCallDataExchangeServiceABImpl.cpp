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

#include "TrentinoLocalCallDataExchangeServiceABImpl.h"
#include <iostream>

using namespace Trentino::LocalCallDataExchange;

Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceAImpl::method_with_two_parameters_first_by_value_second_by_reference( ClassA a, ClassB& b )
   {
   ClassC res;
   if(a.a ==2 && b.elems.size()==2 && b.aObject.b ==1){
      res.x = std::string("OK");
      }
   b.aObject.b =2;
   return res;
   }

Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceAImpl::method_with_two_parameters_first_by_const_value_second_by_reference( const ClassA a, ClassB& b )
   {
     return method_with_two_parameters_first_by_value_second_by_reference(a,b);
   }

Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceAImpl::method_with_two_parameters_first_by_value_second_const_reference( ClassA a, const ClassB& b )
   {
   ClassC res;
   if(a.a ==2 && b.elems.size()==2 && b.aObject.b ==1){
      res.x = std::string("OK");
      }
   return res;
   }


Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceAImpl::method_with_two_parameters_passed_by_value( ClassA a, ClassB b )
   {
   return method_with_two_parameters_first_by_value_second_const_reference(a,b);
   }

const ClassC Trentino::LocalCallDataExchange::ServiceAImpl::method_with_two_arguments_return_const_value( const ClassA& a, const ClassB& b )
   {
   ClassC res;
   if(a.a ==2 && b.elems.size()==2 && b.aObject.b ==1){
      res.x = std::string("OK");
      }
   return res;
   }

const ClassC& Trentino::LocalCallDataExchange::ServiceAImpl::method_with_one_value_return_a_const_Reference( const ClassB& b )
   {
     return mServiceB->method_with_one_value_return_a_const_Reference(b);
   }

const ClassC& Trentino::LocalCallDataExchange::ServiceAImpl::method_has_many_value_or_const_parameters( ClassA a, ClassB& b, const ClassC c, const ClassA a2, const ClassB& b2 )
   {
   return mServiceB->method_has_many_value_or_const_parameters(a,b,c,a2,b2);
   }

ClassC* Trentino::LocalCallDataExchange::ServiceAImpl::method_has_a_pointer_and_a_value_return_a_pointer( ClassA* a, ClassB b )
   {
   ClassC* res = new ClassC();
   if(a->a ==2 && b.elems.size()==2 && b.aObject.b ==1){
      res->x = std::string("OK");
      }
   b.aObject.b =2;
   return res;
   }

ClassC* Trentino::LocalCallDataExchange::ServiceAImpl::method_has_two_pointers_return_a_pointer( ClassA* a, ClassB* b )
   {
      return method_has_two_const_pointers_return_a_pointer(a,b);
   }

ClassC* Trentino::LocalCallDataExchange::ServiceAImpl::method_has_two_const_pointers_return_a_pointer( const ClassA* a, const ClassB* b )
   {
   return mServiceB->method_has_two_const_pointers_return_a_pointer(a,b);
   }

ClassC* Trentino::LocalCallDataExchange::ServiceAImpl::method_has_a_template_class_as_argument( const std::vector<ClassA>& valuesOfA )
   {
    return (*mServiceB).method_has_a_template_class_as_argument(valuesOfA);
   }

void Trentino::LocalCallDataExchange::ServiceAImpl::setServiceB( ServiceB* val )
   {
    mServiceB = val; 
   }

Trentino::LocalCallDataExchange::ClassC** Trentino::LocalCallDataExchange::ServiceAImpl::method_take_and_return_pointer_of_pointer( const Trentino::LocalCallDataExchange::ClassA** a )
   {
   ClassC* val = new ClassC;


   if((**a).a==2){
         val->x ="OK";
      }
   return &val;
   }






Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceBImpl::method_with_two_parameters_passed_by_value( ClassA a, ClassB b )
   {
  return mServiceA->method_with_two_parameters_passed_by_value(a,b);
   }

Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceBImpl::method_with_two_parameters_first_by_value_second_by_reference( ClassA a, ClassB& b )
   {
   return mServiceA->method_with_two_parameters_first_by_value_second_by_reference(a,b);
   }

Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceBImpl::method_with_two_parameters_first_by_const_value_second_by_reference( const ClassA a, ClassB& b )
   {
    return mServiceA->method_with_two_parameters_first_by_const_value_second_by_reference(a,b);
   }

Trentino::LocalCallDataExchange::ClassC Trentino::LocalCallDataExchange::ServiceBImpl::method_with_two_parameters_first_by_value_second_const_reference( ClassA a, const ClassB& b )
   {
       return mServiceA->method_with_two_parameters_first_by_value_second_const_reference(a,b);
   }

const ClassC Trentino::LocalCallDataExchange::ServiceBImpl::method_with_two_arguments_return_const_value( const ClassA& a, const ClassB& b )
   {
          return mServiceA->method_with_two_arguments_return_const_value(a,b);
   }

const ClassC& Trentino::LocalCallDataExchange::ServiceBImpl::method_with_one_value_return_a_const_Reference( const ClassB& b )
   {
   ClassC* val = new ClassC;
   val->x ="OK";
   return *val;
   }

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1, c.x="OK", a2.a is 1 and b2.aObject.b is 2
const ClassC& Trentino::LocalCallDataExchange::ServiceBImpl::method_has_many_value_or_const_parameters( ClassA a, ClassB& b, const ClassC c, const ClassA a2, const ClassB& b2 )
   {
   ClassC* res = new ClassC;
   if(a.a ==2 && b.elems.size()==2 && b.aObject.b ==1 && c.x =="OK" && a2.a==1 && b2.aObject.b==2){
      res->x = std::string("OK");
      }
   return *res;
   }

ClassC* Trentino::LocalCallDataExchange::ServiceBImpl::method_has_a_pointer_and_a_value_return_a_pointer( ClassA* a, ClassB b )
   {
  return mServiceA->method_has_a_pointer_and_a_value_return_a_pointer(a,b);
   }

ClassC* Trentino::LocalCallDataExchange::ServiceBImpl::method_has_two_pointers_return_a_pointer( ClassA* a, ClassB* b )
   {
         return method_has_two_const_pointers_return_a_pointer(a,b);
   }

ClassC* Trentino::LocalCallDataExchange::ServiceBImpl::method_has_two_const_pointers_return_a_pointer( const ClassA* a, const ClassB* b )
   {
   ClassC* res = new ClassC;
   if(a->a ==2 && b->elems.size()==2 && b->aObject.b ==1){
      res->x = std::string("OK");
      }
   return res;
   }

ClassC* Trentino::LocalCallDataExchange::ServiceBImpl::method_has_a_template_class_as_argument( const std::vector<ClassA>& valuesOfA )
   {
      ClassC* res= new ClassC;
      if(valuesOfA.size()==2){
             res->x = std::string("OK");
         }
         return res;
   }

void Trentino::LocalCallDataExchange::ServiceBImpl::setServiceA( ServiceA* val )
{
	std::cout<< "setter function is called..." <<std::endl;
    mServiceA = val;
}

   void Trentino::LocalCallDataExchange::ServiceBImpl::init(  )
   {
	std::cout<< "init() function is called..." <<std::endl;
   }