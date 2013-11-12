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

#ifndef TrentinoLocalCallDataExchangeServiceABH
#define TrentinoLocalCallDataExchangeServiceABH

#include "TrentinoLocalCallDataExchange.h"

namespace Trentino{
   namespace LocalCallDataExchange{

      //****************************************************************************************************
      //                                         ServiceA
      //****************************************************************************************************
      //! \brief Servcie a test if complex data passed by values are accessed by the service implementation
      //****************************************************************************************************
      class ServiceA {
      public:
         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual ClassC method_with_two_parameters_passed_by_value(ClassA a, ClassB b) =0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         //! value of b.aObject is changed from 1 to two.
         virtual   ClassC method_with_two_parameters_first_by_value_second_by_reference(ClassA a, ClassB& b)=0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         //! value of b.aObject is changed from 1 to two.
         virtual   ClassC method_with_two_parameters_first_by_const_value_second_by_reference(const ClassA a, ClassB& b)=0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  ClassC method_with_two_parameters_first_by_value_second_const_reference(ClassA a, const ClassB& b)=0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  const ClassC method_with_two_arguments_return_const_value(const ClassA& a, const ClassB& b)=0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual   const ClassC& method_with_one_value_return_a_const_Reference(const ClassB& b)=0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1, c.x="OK", c.a is 1 and b2.aObject.b is 2
         virtual  const ClassC& method_has_many_value_or_const_parameters(ClassA a, ClassB& b, const ClassC c, const ClassA a2, const ClassB& b2)=0;



         //*********************************************POINTERS*******************************************************

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  ClassC* method_has_a_pointer_and_a_value_return_a_pointer(ClassA* a, ClassB b)=0;
         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual   ClassC* method_has_two_pointers_return_a_pointer(ClassA* a, ClassB* b)=0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  ClassC* method_has_two_const_pointers_return_a_pointer(const ClassA* a, const ClassB* b)=0;

         //! \brief return x="OK" if vector has two elements
         virtual   ClassC* method_has_a_template_class_as_argument(const std::vector<ClassA>& valuesOfA)=0;
         };


      //****************************************************************************************************
      //                                         ServiceB
      //****************************************************************************************************
      //! \brief B is the same as A. B is used to combine service Call chains
      //****************************************************************************************************
      class ServiceB {
      public:
         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual ClassC method_with_two_parameters_passed_by_value(ClassA a, ClassB b) =0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         //! value of b.aObject is changed from 1 to two.
         virtual   ClassC method_with_two_parameters_first_by_value_second_by_reference(ClassA a, ClassB& b)=0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         //! value of b.aObject is changed from 1 to two.
         virtual   ClassC method_with_two_parameters_first_by_const_value_second_by_reference(const ClassA a, ClassB& b)=0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  ClassC method_with_two_parameters_first_by_value_second_const_reference(ClassA a, const ClassB& b)=0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  const ClassC method_with_two_arguments_return_const_value(const ClassA& a, const ClassB& b)=0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual   const ClassC& method_with_one_value_return_a_const_Reference(const ClassB& b)=0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1, c.x="OK", c.a is 1 and b2.aObject.b is 2
         virtual  const ClassC& method_has_many_value_or_const_parameters(ClassA a, ClassB& b, const ClassC c, const ClassA a2, const ClassB& b2)=0;



         //*********************************************POINTERS*******************************************************

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  ClassC* method_has_a_pointer_and_a_value_return_a_pointer(ClassA* a, ClassB b)=0;
         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual   ClassC* method_has_two_pointers_return_a_pointer(ClassA* a, ClassB* b)=0;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  ClassC* method_has_two_const_pointers_return_a_pointer(const ClassA* a, const ClassB* b)=0;

         //! \brief return x="OK" if vector has two elements
         virtual   ClassC* method_has_a_template_class_as_argument(const std::vector<ClassA>& valuesOfA)=0;
         };
      }//namespace LocalCallDataExchange
   }//namespace Trentino

#endif //TrentinoLocalCallDataExchangeServiceABH