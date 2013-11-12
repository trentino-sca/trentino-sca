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
#ifndef LocalCallDataExchangeGen_Trentino_LocalCallDataExchange_TrentinoGenProxiesWrappersH
#define LocalCallDataExchangeGen_Trentino_LocalCallDataExchange_TrentinoGenProxiesWrappersH
#define BOOST_ALL_NO_LIB


//standard
#include <boost/scoped_ptr.hpp>

#include <Global/TrentinoGlobal.h>
#include <Runtime/Invocation/TrentinoInvocation.h>
#include <Runtime/Invocation/TrentinoInvocationInvocationData.h>
#include <Runtime/Invocation/TrentinoInvocationInvocationContext.h> //! \todo: currently not used
#include <Runtime/Invocation/TrentinoInvocationInvokerBase.h>
#include <Runtime/Invocation/TrentinoInvocationServiceInvocationWrapperBase.h>
#include <Runtime/RuntimeModel/TrentinoRuntimeModelWireBase.h>
#include <Runtime/RuntimeModel/TrentinoRuntimeModelServiceBase.h>
#include <Runtime/ReflectionRuntime/TrentinoReflectionRegistration.h>

//specific
#include "../LocalCallDataExchange/services/TrentinoLocalCallDataExchangeServiceAB.h"
#include "../LocalCallDataExchange/services/TrentinoLocalCallDataExchangeServiceAB.h"
#include "../LocalCallDataExchange/services/TrentinoLocalCallDataExchangeServiceAB.h"
#include "../LocalCallDataExchange/services/TrentinoLocalCallDataExchangeServiceAB.h"

namespace Trentino{
namespace Gen{
namespace LocalCallDataExchangeGen{
   //*************************************************************************************************
   //                                          WRAPPERS
   //*************************************************************************************************

	//*************************************************************************************************
	//wrapper class declaration Trentino_LocalCallDataExchange_ServiceBWrapper
	//*************************************************************************************************
   
	class Trentino_LocalCallDataExchange_ServiceBWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data, 
                  const Trentino::Invocation::InvocationContextPtr& ctx,
                  void* targetInstance) const;
   
	};// class Trentino_LocalCallDataExchange_ServiceBWrapper
  

	//*************************************************************************************************
	//wrapper class declaration Trentino_LocalCallDataExchange_ServiceAWrapper
	//*************************************************************************************************
   
	class Trentino_LocalCallDataExchange_ServiceAWrapper : public Trentino::Invocation::ServiceInvocationWrapperBase 
	{
     	//services
   		public:
      	void invoke(const Trentino::Invocation::InvocationDataPtr& data, 
                  const Trentino::Invocation::InvocationContextPtr& ctx,
                  void* targetInstance) const;
   
	};// class Trentino_LocalCallDataExchange_ServiceAWrapper
  



   //*************************************************************************************************
   //                                          PROXIES
   //*************************************************************************************************

//*************************************************************************************************
//Proxy class definition Trentino_LocalCallDataExchange_ServiceBProxy
//*************************************************************************************************
 class Trentino_LocalCallDataExchange_ServiceBProxy :public Trentino::LocalCallDataExchange::ServiceB
   {
      //construction
   public:
      Trentino_LocalCallDataExchange_ServiceBProxy(Trentino::RuntimeModel::WireBase* wire);

      //services
   public:
  		virtual Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_passed_by_value ( Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB b);
  		virtual Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_first_by_value_second_by_reference ( Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b);
  		virtual Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_first_by_const_value_second_by_reference ( const Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b);
  		virtual Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_first_by_value_second_const_reference ( Trentino::LocalCallDataExchange::ClassA a, const Trentino::LocalCallDataExchange::ClassB& b);
  		virtual const Trentino::LocalCallDataExchange::ClassC method_with_two_arguments_return_const_value ( const Trentino::LocalCallDataExchange::ClassA& a, const Trentino::LocalCallDataExchange::ClassB& b);
  		virtual const Trentino::LocalCallDataExchange::ClassC& method_with_one_value_return_a_const_Reference ( const Trentino::LocalCallDataExchange::ClassB& b);
  		virtual const Trentino::LocalCallDataExchange::ClassC& method_has_many_value_or_const_parameters ( Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b, const Trentino::LocalCallDataExchange::ClassC c, const Trentino::LocalCallDataExchange::ClassA a2, const Trentino::LocalCallDataExchange::ClassB& b2);
  		virtual Trentino::LocalCallDataExchange::ClassC* method_has_a_pointer_and_a_value_return_a_pointer ( Trentino::LocalCallDataExchange::ClassA* a, Trentino::LocalCallDataExchange::ClassB b);
  		virtual Trentino::LocalCallDataExchange::ClassC* method_has_two_pointers_return_a_pointer ( Trentino::LocalCallDataExchange::ClassA* a, Trentino::LocalCallDataExchange::ClassB* b);
  		virtual Trentino::LocalCallDataExchange::ClassC* method_has_two_const_pointers_return_a_pointer ( const Trentino::LocalCallDataExchange::ClassA* a, const Trentino::LocalCallDataExchange::ClassB* b);
  		virtual Trentino::LocalCallDataExchange::ClassC* method_has_a_template_class_as_argument ( const std::vector<Trentino::LocalCallDataExchange::ClassA>& valuesOfA);
      //data
   private:
      Trentino::RuntimeModel::WireBase* mWire;
   }; //class Trentino_LocalCallDataExchange_ServiceBProxy

//*************************************************************************************************
//Proxy class definition Trentino_LocalCallDataExchange_ServiceAProxy
//*************************************************************************************************
 class Trentino_LocalCallDataExchange_ServiceAProxy :public Trentino::LocalCallDataExchange::ServiceA
   {
      //construction
   public:
      Trentino_LocalCallDataExchange_ServiceAProxy(Trentino::RuntimeModel::WireBase* wire);

      //services
   public:
  		virtual Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_passed_by_value ( Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB b);
  		virtual Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_first_by_value_second_by_reference ( Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b);
  		virtual Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_first_by_const_value_second_by_reference ( const Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b);
  		virtual Trentino::LocalCallDataExchange::ClassC method_with_two_parameters_first_by_value_second_const_reference ( Trentino::LocalCallDataExchange::ClassA a, const Trentino::LocalCallDataExchange::ClassB& b);
  		virtual const Trentino::LocalCallDataExchange::ClassC method_with_two_arguments_return_const_value ( const Trentino::LocalCallDataExchange::ClassA& a, const Trentino::LocalCallDataExchange::ClassB& b);
  		virtual const Trentino::LocalCallDataExchange::ClassC& method_with_one_value_return_a_const_Reference ( const Trentino::LocalCallDataExchange::ClassB& b);
  		virtual const Trentino::LocalCallDataExchange::ClassC& method_has_many_value_or_const_parameters ( Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b, const Trentino::LocalCallDataExchange::ClassC c, const Trentino::LocalCallDataExchange::ClassA a2, const Trentino::LocalCallDataExchange::ClassB& b2);
  		virtual Trentino::LocalCallDataExchange::ClassC* method_has_a_pointer_and_a_value_return_a_pointer ( Trentino::LocalCallDataExchange::ClassA* a, Trentino::LocalCallDataExchange::ClassB b);
  		virtual Trentino::LocalCallDataExchange::ClassC* method_has_two_pointers_return_a_pointer ( Trentino::LocalCallDataExchange::ClassA* a, Trentino::LocalCallDataExchange::ClassB* b);
  		virtual Trentino::LocalCallDataExchange::ClassC* method_has_two_const_pointers_return_a_pointer ( const Trentino::LocalCallDataExchange::ClassA* a, const Trentino::LocalCallDataExchange::ClassB* b);
  		virtual Trentino::LocalCallDataExchange::ClassC** method_take_and_return_pointer_of_pointer ( const Trentino::LocalCallDataExchange::ClassA** a);
  		virtual Trentino::LocalCallDataExchange::ClassC* method_has_a_template_class_as_argument ( const std::vector<Trentino::LocalCallDataExchange::ClassA>& valuesOfA);
      //data
   private:
      Trentino::RuntimeModel::WireBase* mWire;
   }; //class Trentino_LocalCallDataExchange_ServiceAProxy


}//namespace Gen
}//namespace Trentino
}//namespace LocalCallDataExchangeGen

#endif //LocalCallDataExchangeGen_Trentino_LocalCallDataExchange_TrentinoGenProxiesWrappersH

