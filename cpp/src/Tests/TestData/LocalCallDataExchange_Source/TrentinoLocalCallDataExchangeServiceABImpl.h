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

#ifndef TrentinoLocalCallDataExchangeServiceABImplH
#define TrentinoLocalCallDataExchangeServiceABImplH
#include "services/TrentinoLocalCallDataExchangeServiceAB.h"

//standard
//#include <oasis/sca/ComponentContext.h>

namespace Trentino{
   namespace LocalCallDataExchange{

      //****************************************************************************************************
      //                                         ServiceA
      //****************************************************************************************************
      //! \brief Servcie a test if complex data passed by values are accessed by the service implementation
      //****************************************************************************************************
      class LOCALDATACALLEXCHANGE_IMPORT_EXPORT ServiceAImpl : public ServiceA {
      public:
 //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_passed_by_value(Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB b) ;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         //! value of b.aObject is changed from 1 to two.
         virtual   Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_first_by_value_second_by_reference(Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b);

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         //! value of b.aObject is changed from 1 to two.
         virtual   Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_first_by_const_value_second_by_reference(const Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b);

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_first_by_value_second_const_reference(Trentino::LocalCallDataExchange::ClassA a, const Trentino::LocalCallDataExchange::ClassB& b);

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  const Trentino::LocalCallDataExchange::ClassC method_with_two_arguments_return_const_value(const Trentino::LocalCallDataExchange::ClassA& a, const Trentino::LocalCallDataExchange::ClassB& b);

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual   const Trentino::LocalCallDataExchange::ClassC& method_with_one_value_return_a_const_Reference(const Trentino::LocalCallDataExchange::ClassB& b);

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1, c.x="OK", c.a is 1 and b2.aObject.b is 2
         virtual  const Trentino::LocalCallDataExchange::ClassC& method_has_many_value_or_const_parameters(Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b, const Trentino::LocalCallDataExchange::ClassC c, const Trentino::LocalCallDataExchange::ClassA a2, const Trentino::LocalCallDataExchange::ClassB& b2);



         //*********************************************POINTERS*******************************************************

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  Trentino::LocalCallDataExchange::ClassC* method_has_a_pointer_and_a_value_return_a_pointer(Trentino::LocalCallDataExchange::ClassA* a, Trentino::LocalCallDataExchange::ClassB b);
         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual   Trentino::LocalCallDataExchange::ClassC* method_has_two_pointers_return_a_pointer(Trentino::LocalCallDataExchange::ClassA* a, Trentino::LocalCallDataExchange::ClassB* b);

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  Trentino::LocalCallDataExchange::ClassC* method_has_two_const_pointers_return_a_pointer(const Trentino::LocalCallDataExchange::ClassA* a, const Trentino::LocalCallDataExchange::ClassB* b);

         //! \brief return x="OK" if vector has two elements
         virtual   Trentino::LocalCallDataExchange::ClassC* method_has_a_template_class_as_argument(const std::vector<Trentino::LocalCallDataExchange::ClassA>& valuesOfA);        
         void setServiceB(ServiceB* val);
      private:
         //ComponentContext
         //oasis::sca::ComponentContext* mComponentContext;
         ServiceB* mServiceB;
         };


      //****************************************************************************************************
      //                                         ServiceB
      //****************************************************************************************************
      //! \brief B is the same as A. B is used to combine service Call chains
      //****************************************************************************************************
      class LOCALDATACALLEXCHANGE_IMPORT_EXPORT ServiceBImpl: public ServiceB {
      public:
                  //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_passed_by_value(Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB b) ;

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         //! value of b.aObject is changed from 1 to two.
         virtual   Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_first_by_value_second_by_reference(Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b);

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         //! value of b.aObject is changed from 1 to two.
         virtual   Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_first_by_const_value_second_by_reference(const Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b);

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_first_by_value_second_const_reference(Trentino::LocalCallDataExchange::ClassA a, const Trentino::LocalCallDataExchange::ClassB& b);

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  const Trentino::LocalCallDataExchange::ClassC method_with_two_arguments_return_const_value(const Trentino::LocalCallDataExchange::ClassA& a, const Trentino::LocalCallDataExchange::ClassB& b);

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual   const Trentino::LocalCallDataExchange::ClassC& method_with_one_value_return_a_const_Reference(const Trentino::LocalCallDataExchange::ClassB& b);

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1, c.x="OK", c.a is 1 and b2.aObject.b is 2
         virtual  const Trentino::LocalCallDataExchange::ClassC& method_has_many_value_or_const_parameters(Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b, const Trentino::LocalCallDataExchange::ClassC c, const Trentino::LocalCallDataExchange::ClassA a2, const Trentino::LocalCallDataExchange::ClassB& b2);



         //*********************************************POINTERS*******************************************************

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  Trentino::LocalCallDataExchange::ClassC* method_has_a_pointer_and_a_value_return_a_pointer(Trentino::LocalCallDataExchange::ClassA* a, Trentino::LocalCallDataExchange::ClassB b);
         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual   Trentino::LocalCallDataExchange::ClassC* method_has_two_pointers_return_a_pointer(Trentino::LocalCallDataExchange::ClassA* a,Trentino::LocalCallDataExchange::ClassB* b);

         //! \brief return x="OK" if a.a is 2, b.elems has two elements, b.aObject.b is 1
         virtual  Trentino::LocalCallDataExchange::ClassC* method_has_two_const_pointers_return_a_pointer(const Trentino::LocalCallDataExchange::ClassA* a, const Trentino::LocalCallDataExchange::ClassB* b);

         //! \brief return x="OK" if vector has two elements
         virtual   Trentino::LocalCallDataExchange::ClassC* method_has_a_template_class_as_argument(const std::vector<Trentino::LocalCallDataExchange::ClassA>& valuesOfA);
         void setServiceA(ServiceA* val);
      private:
         //ComponentContext
         //oasis::sca::ComponentContext* mComponentContext;
         ServiceA* mServiceA;

         };
      }//namespace LocalCallDataExchange
   }//namespace Trentino

#endif //TrentinoLocalCallDataExchangeServiceABImplH