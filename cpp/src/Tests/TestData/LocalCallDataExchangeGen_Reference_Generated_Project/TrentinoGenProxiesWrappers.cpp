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

//standard
#include <boost/scoped_ptr.hpp>

#include <Global/TrentinoGlobal.h>
#include <Runtime/Invocation/TrentinoInvocation.h>
#include <Runtime/Invocation/TrentinoInvocationInvocationData.h>
#include <Runtime/Invocation/TrentinoInvocationInvocationContext.h> //! \todo: currently not used
#include <Runtime/Invocation/TrentinoInvocationInvokerBase.h>
#include <Runtime/Invocation/TrentinoInvocationServiceInvocationWrapperBase.h>

#include <Runtime/RuntimeModel/TrentinoRuntimeModelWire.h>

#include <Runtime/ReflectionRuntime/TrentinoReflectionRegistration.h>

//specific
#include "../LocalCallDataExchange/services/TrentinoLocalCallDataExchangeServiceAB.h"

using namespace Trentino::LocalCallDataExchange;

namespace Trentino{
namespace Gen
{
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
	//wrapper class definition for wrapper: Trentino_LocalCallDataExchange_ServiceBWrapper
	//*************************************************************************************************
	// invoke method for wrapper: Trentino_LocalCallDataExchange_ServiceBWrapper
	void Trentino_LocalCallDataExchange_ServiceBWrapper::invoke(
		const Trentino::Invocation::InvocationDataPtr& data 
		,const Trentino::Invocation::InvocationContextPtr& ctx
		,void* targetInstance) const
	{
		assert(targetInstance != nullptr);
		Trentino::LocalCallDataExchange::ServiceB* const myInstance = static_cast<Trentino::LocalCallDataExchange::ServiceB*>(targetInstance);
		const std::string& op = data->operation();
		      if(op =="method_with_two_parameters_passed_by_value" )
      {
     	 Trentino::LocalCallDataExchange::ClassA& param0 = *static_cast<Trentino::LocalCallDataExchange::ClassA*>(data->parameters()[0]);
     	 Trentino::LocalCallDataExchange::ClassB& param1 = *static_cast<Trentino::LocalCallDataExchange::ClassB*>(data->parameters()[1]);
      	 
         Trentino::LocalCallDataExchange::ClassC* result = new Trentino::LocalCallDataExchange::ClassC;
         *result = myInstance->method_with_two_parameters_passed_by_value(param0, param1); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_with_two_parameters_first_by_value_second_by_reference" )
      {
     	 Trentino::LocalCallDataExchange::ClassA& param0 = *static_cast<Trentino::LocalCallDataExchange::ClassA*>(data->parameters()[0]);
     	 Trentino::LocalCallDataExchange::ClassB& param1 = *static_cast<Trentino::LocalCallDataExchange::ClassB*>(data->parameters()[1]);
      	 
         Trentino::LocalCallDataExchange::ClassC* result = new Trentino::LocalCallDataExchange::ClassC;
         *result = myInstance->method_with_two_parameters_first_by_value_second_by_reference(  param0, param1 ); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_with_two_parameters_first_by_const_value_second_by_reference" )
      {
     	 Trentino::LocalCallDataExchange::ClassA& param0 = *static_cast<Trentino::LocalCallDataExchange::ClassA*>(data->parameters()[0]);
     	 Trentino::LocalCallDataExchange::ClassB& param1 = *static_cast<Trentino::LocalCallDataExchange::ClassB*>(data->parameters()[1]);
      	 
         Trentino::LocalCallDataExchange::ClassC* result = new Trentino::LocalCallDataExchange::ClassC;
         *result = myInstance->method_with_two_parameters_first_by_const_value_second_by_reference(  param0, param1 ); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_with_two_parameters_first_by_value_second_const_reference" )
      {
     	 Trentino::LocalCallDataExchange::ClassA& param0 = *static_cast<Trentino::LocalCallDataExchange::ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
      	 
         ClassC* result = new ClassC;
         *result = myInstance->method_with_two_parameters_first_by_value_second_const_reference(  param0, param1 ); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_with_two_arguments_return_const_value" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
      	 
         ClassC* result = new ClassC;
         *result = myInstance->method_with_two_arguments_return_const_value(  param0, param1 ); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_with_one_value_return_a_const_Reference" )
      {
     	 ClassB& param0 = *static_cast<ClassB*>(data->parameters()[0]);
      	 
         ClassC const ** result = new const ClassC*;
         *result = &myInstance->method_with_one_value_return_a_const_Reference(  param0 ); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_has_many_value_or_const_parameters" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
     	 ClassC& param2 = *static_cast<ClassC*>(data->parameters()[2]);
     	 ClassA& param3 = *static_cast<ClassA*>(data->parameters()[3]);
     	 ClassB& param4 = *static_cast<ClassB*>(data->parameters()[4]);
      	 
         ClassC const ** result = new const ClassC*;
         *result = &myInstance->method_has_many_value_or_const_parameters(  param0, param1, param2, param3, param4 ); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_has_a_pointer_and_a_value_return_a_pointer" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
 
         ClassC** result = new ClassC*;
		 *result = myInstance->method_has_a_pointer_and_a_value_return_a_pointer(&param0, param1); 
      }

		else
		      if(op =="method_has_two_pointers_return_a_pointer" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
      	 
         ClassC** result = new ClassC*;
         *result = myInstance->method_has_two_pointers_return_a_pointer(&param0, &param1);
         data->setResponse(result);         
      }

		else
		      if(op =="method_has_two_const_pointers_return_a_pointer" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
      	 
         ClassC** result = new ClassC*;
         *result = myInstance->method_has_two_const_pointers_return_a_pointer(&param0, &param1);
         data->setResponse(result);         
      }

		else
		      if(op =="method_has_a_template_class_as_argument" )
      {
     	 std::vector<ClassA>& param0 = *static_cast<std::vector<ClassA>*>(data->parameters()[0]);
      	 
         ClassC** result = new ClassC*;
         *result = myInstance->method_has_a_template_class_as_argument(param0); 
         data->setResponse(result);         
      }

		
	}
	
   //*************************************************************************************************
   //class declaration&definition InitializerTrentino_Example_BasicCalculator_CalculatorImplWrapperRflx
   //*************************************************************************************************
	class InitializerTrentino_LocalCallDataExchange_ServiceBWrapperRflx
   {
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino_LocalCallDataExchange_ServiceBWrapper**>(retVal) = new Trentino_LocalCallDataExchange_ServiceBWrapper();
		}

		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino_LocalCallDataExchange_ServiceBWrapper* p = static_cast<Trentino_LocalCallDataExchange_ServiceBWrapper*>(thisPtr);
			delete p;
		}
 		
   		public:
   		//construction
		InitializerTrentino_LocalCallDataExchange_ServiceBWrapperRflx()
		{
			// METHOD SIGNATURES
			static const Trentino::Reflection::Data::Method::Param deleteParam[] = {
				"ptr", "Trentino_LocalCallDataExchange_ServiceBWrapper*"
			};

         	static Trentino::Reflection::Data::Method::MetaData mdm[] = {
				{ "new", "Trentino_LocalCallDataExchange_ServiceBWrapper*", nullptr, 0, newObjectNoParam },
				{ "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
			};

			// OBJECT
			static Trentino::Reflection::Data::Object::MetaData mdo = { 
				"Trentino_LocalCallDataExchange_ServiceBWrapper", 
				nullptr, 
				nullptr,
				0,
				mdm,
				COUNT_OF(mdm),
			};

			mmdoHandle = &mdo;

			Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
		}

		~InitializerTrentino_LocalCallDataExchange_ServiceBWrapperRflx()
		{
			Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
		}

		//data
		private:
		Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

	}; //class InitializerTrentino_LocalCallDataExchange_ServiceBWrapperRflx

   
	static InitializerTrentino_LocalCallDataExchange_ServiceBWrapperRflx init1; 

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
	//wrapper class definition for wrapper: Trentino_LocalCallDataExchange_ServiceAWrapper
	//*************************************************************************************************
	// invoke method for wrapper: Trentino_LocalCallDataExchange_ServiceAWrapper
	void Trentino_LocalCallDataExchange_ServiceAWrapper::invoke(
		const Trentino::Invocation::InvocationDataPtr& data 
		,const Trentino::Invocation::InvocationContextPtr& ctx
		,void* targetInstance) const
	{
		assert(targetInstance != nullptr);
		Trentino::LocalCallDataExchange::ServiceA* const myInstance = static_cast<Trentino::LocalCallDataExchange::ServiceA*>(targetInstance);
		const std::string& op = data->operation();
		      if(op =="method_with_two_parameters_passed_by_value" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
      	 
         ClassC* result = new ClassC;
         *result = myInstance->method_with_two_parameters_passed_by_value(param0, param1); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_with_two_parameters_first_by_value_second_by_reference" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
      	 
         ClassC* result = new ClassC;
         *result = myInstance->method_with_two_parameters_first_by_value_second_by_reference(param0, param1); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_with_two_parameters_first_by_const_value_second_by_reference" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
      	 
         ClassC* result = new ClassC;
         *result = myInstance->method_with_two_parameters_first_by_const_value_second_by_reference(param0, param1); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_with_two_parameters_first_by_value_second_const_reference" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
      	 
         ClassC* result = new ClassC;
         *result = myInstance->method_with_two_parameters_first_by_value_second_const_reference(param0, param1); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_with_two_arguments_return_const_value" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
      	 
         ClassC* result = new ClassC;
         *result = myInstance->method_with_two_arguments_return_const_value(param0, param1); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_with_one_value_return_a_const_Reference" )
      {
     	 ClassB& param0 = *static_cast<ClassB*>(data->parameters()[0]);
      	 
         ClassC const ** result = new const ClassC*;
         *result = &myInstance->method_with_one_value_return_a_const_Reference(  param0 ); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_has_many_value_or_const_parameters" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
     	 ClassC& param2 = *static_cast<ClassC*>(data->parameters()[2]);
     	 ClassA& param3 = *static_cast<ClassA*>(data->parameters()[3]);
     	 ClassB& param4 = *static_cast<ClassB*>(data->parameters()[4]);
      	 
         ClassC const ** result = new const ClassC*;
         *result = &myInstance->method_has_many_value_or_const_parameters(  param0, param1, param2, param3, param4 ); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_has_a_pointer_and_a_value_return_a_pointer" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
      	 
         ClassC** result = new ClassC*;
         *result = myInstance->method_has_a_pointer_and_a_value_return_a_pointer(&param0, param1); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_has_two_pointers_return_a_pointer" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
      	 
         ClassC** result = new ClassC*;
         *result = myInstance->method_has_two_pointers_return_a_pointer(&param0, &param1); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_has_two_const_pointers_return_a_pointer" )
      {
     	 ClassA& param0 = *static_cast<ClassA*>(data->parameters()[0]);
     	 ClassB& param1 = *static_cast<ClassB*>(data->parameters()[1]);
      	 
         ClassC** result = new ClassC*;
         *result = myInstance->method_has_two_const_pointers_return_a_pointer(&param0, &param1); 
         data->setResponse(result);         
      }

		else
		      if(op =="method_has_a_template_class_as_argument" )
      {
     	 std:: vector<ClassA>& param0 = *static_cast<std:: vector<ClassA>*>(data->parameters()[0]);
      	 
         ClassC** result = new ClassC*;
         *result = myInstance->method_has_a_template_class_as_argument(  param0 ); 
         data->setResponse(result);         
      }

		
	}
	
   //*************************************************************************************************
   //class declaration&definition InitializerTrentino_Example_BasicCalculator_CalculatorImplWrapperRflx
   //*************************************************************************************************
	class InitializerTrentino_LocalCallDataExchange_ServiceAWrapperRflx
   {
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino_LocalCallDataExchange_ServiceAWrapper**>(retVal) = new Trentino_LocalCallDataExchange_ServiceAWrapper();
		}

		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino_LocalCallDataExchange_ServiceAWrapper* p = static_cast<Trentino_LocalCallDataExchange_ServiceAWrapper*>(thisPtr);
			delete p;
		}
 		
   		public:
   		//construction
		InitializerTrentino_LocalCallDataExchange_ServiceAWrapperRflx()
		{
			// METHOD SIGNATURES
			static const Trentino::Reflection::Data::Method::Param deleteParam[] = {
				"ptr", "Trentino_LocalCallDataExchange_ServiceAWrapper*"
			};

         	static Trentino::Reflection::Data::Method::MetaData mdm[] = {
				{ "new", "Trentino_LocalCallDataExchange_ServiceAWrapper*", nullptr, 0, newObjectNoParam },
				{ "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
			};

			// OBJECT
			static Trentino::Reflection::Data::Object::MetaData mdo = { 
				"Trentino_LocalCallDataExchange_ServiceAWrapper", 
				nullptr, 
				nullptr,
				0,
				mdm,
				COUNT_OF(mdm),
			};

			mmdoHandle = &mdo;

			Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
		}

		~InitializerTrentino_LocalCallDataExchange_ServiceAWrapperRflx()
		{
			Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
		}

		//data
		private:
		Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

	}; //class InitializerTrentino_LocalCallDataExchange_ServiceAWrapperRflx

   
	static InitializerTrentino_LocalCallDataExchange_ServiceAWrapperRflx init2; 



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
      Trentino_LocalCallDataExchange_ServiceBProxy(Trentino::RuntimeModel::Wire* wire);

      //services
   public:
  		virtual ClassC method_with_two_parameters_passed_by_value ( ClassA a, ClassB b);
  		virtual ClassC method_with_two_parameters_first_by_value_second_by_reference ( ClassA a, ClassB& b);
  		virtual ClassC method_with_two_parameters_first_by_const_value_second_by_reference ( const ClassA a, ClassB& b);
  		virtual ClassC method_with_two_parameters_first_by_value_second_const_reference ( ClassA a, const ClassB& b);
  		virtual const ClassC method_with_two_arguments_return_const_value ( const ClassA& a, const ClassB& b);
  		virtual const ClassC& method_with_one_value_return_a_const_Reference ( const ClassB& b);
  		virtual const ClassC& method_has_many_value_or_const_parameters ( ClassA a, ClassB& b, const ClassC c, const ClassA a2, const ClassB& b2);
  		virtual ClassC* method_has_a_pointer_and_a_value_return_a_pointer ( ClassA* a, ClassB b);
  		virtual ClassC* method_has_two_pointers_return_a_pointer ( ClassA* a, ClassB* b);
  		virtual ClassC* method_has_two_const_pointers_return_a_pointer ( const ClassA* a, const ClassB* b);
  		virtual ClassC* method_has_a_template_class_as_argument ( const std:: vector<ClassA>& valuesOfA);
      //data
   private:
      Trentino::RuntimeModel::Wire* mWire;
}; //class Trentino_LocalCallDataExchange_ServiceBProxy

Trentino_LocalCallDataExchange_ServiceBProxy::Trentino_LocalCallDataExchange_ServiceBProxy(Trentino::RuntimeModel::Wire* wire) : mWire(wire) {}


 ClassC Trentino_LocalCallDataExchange_ServiceBProxy::method_with_two_parameters_passed_by_value( ClassA a, ClassB b)
 {
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
      
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_with_two_parameters_passed_by_value");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(&b);
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC> ptr(static_cast<ClassC*>(invocationData->response()));
      return *ptr;
   }

 ClassC Trentino_LocalCallDataExchange_ServiceBProxy::method_with_two_parameters_first_by_value_second_by_reference( ClassA a, ClassB& b)
 {
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_with_two_parameters_first_by_value_second_by_reference");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(&b);
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC> ptr(static_cast<ClassC*>(invocationData->response()));
      return *ptr;
   }

 ClassC Trentino_LocalCallDataExchange_ServiceBProxy::method_with_two_parameters_first_by_const_value_second_by_reference( const ClassA a, ClassB& b)
 {
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_with_two_parameters_first_by_const_value_second_by_reference");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(const_cast<ClassA*>(&a));
      params.push_back(&b);
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC> ptr(static_cast<ClassC*>(invocationData->response()));
      return *ptr;
   }

 ClassC Trentino_LocalCallDataExchange_ServiceBProxy::method_with_two_parameters_first_by_value_second_const_reference( ClassA a, const ClassB& b)
 {
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_with_two_parameters_first_by_value_second_const_reference");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(const_cast<ClassB*>(&b));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC> ptr(static_cast<ClassC*>(invocationData->response()));
      return *ptr;
   }

const ClassC Trentino_LocalCallDataExchange_ServiceBProxy::method_with_two_arguments_return_const_value( const ClassA& a, const ClassB& b)
 {
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_with_two_arguments_return_const_value");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(const_cast<ClassA*>(&a));
      params.push_back(const_cast<ClassB*>(&b));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC> ptr(static_cast<ClassC*>(invocationData->response()));
      return *ptr;
}

const ClassC& Trentino_LocalCallDataExchange_ServiceBProxy::method_with_one_value_return_a_const_Reference( const ClassB& b)
{
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_with_one_value_return_a_const_Reference");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(const_cast<ClassB*>(&b));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC*> ptr(static_cast<ClassC**>(invocationData->response()));
      return **ptr;
}

const ClassC& Trentino_LocalCallDataExchange_ServiceBProxy::method_has_many_value_or_const_parameters( ClassA a, ClassB& b, const ClassC c, const ClassA a2, const ClassB& b2)
{
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_has_many_value_or_const_parameters");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(&b);
      params.push_back(const_cast<ClassC*>(&c));
      params.push_back(const_cast<ClassA*>(&a2));
      params.push_back(const_cast<ClassB*>(&b2));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC*> ptr(static_cast<ClassC**>(invocationData->response()));
      return **ptr;
   }

 ClassC* Trentino_LocalCallDataExchange_ServiceBProxy::method_has_a_pointer_and_a_value_return_a_pointer( ClassA* a, ClassB b)
{
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_has_a_pointer_and_a_value_return_a_pointer");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(&b);
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC*> ptr(static_cast<ClassC**>(invocationData->response()));
      return *ptr;
}

ClassC* Trentino_LocalCallDataExchange_ServiceBProxy::method_has_two_pointers_return_a_pointer( ClassA* a, ClassB* b)
{
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_has_two_pointers_return_a_pointer");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(&b);
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC*> ptr(static_cast<ClassC**>(invocationData->response()));
      return *ptr;
}

 ClassC* Trentino_LocalCallDataExchange_ServiceBProxy::method_has_two_const_pointers_return_a_pointer( const ClassA* a, const ClassB* b)
{
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_has_two_const_pointers_return_a_pointer");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(&b);
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC*> ptr(static_cast<ClassC**>(invocationData->response()));
      return *ptr;
}

 ClassC* Trentino_LocalCallDataExchange_ServiceBProxy::method_has_a_template_class_as_argument( const std:: vector<ClassA>& valuesOfA)
 {
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_has_a_template_class_as_argument");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(const_cast<std::vector<ClassA>*>(&valuesOfA));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC*> ptr(static_cast<ClassC**>(invocationData->response()));
      return *ptr;
}

    //*************************************************************************************************
   //class declaration&definition
   //InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx
   //*************************************************************************************************
   //=========================================based on implementation.cpp/class (including the parsing of namespaces in the header)
   //=========================================most parts are static right??
   class InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx
   {
      static void TRENTINO_STDCALL newObjectWithParam(void* /*thisPtr*/, void* retVal, void* params[])
      {

         *reinterpret_cast<Trentino_LocalCallDataExchange_ServiceBProxy**>(retVal) = 
            new Trentino_LocalCallDataExchange_ServiceBProxy(
            *reinterpret_cast<Trentino::RuntimeModel::Wire**>(params[0]));   
      }

      static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
      {
         Trentino_LocalCallDataExchange_ServiceBProxy* p = 
            static_cast<Trentino_LocalCallDataExchange_ServiceBProxy*>(thisPtr);
         delete p;
      }


      //construction
   public:
      InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx()
      {
         // METHOD SIGNATURES
         static const Trentino::Reflection::Data::Method::Param deleteParam[] = {
            "ptr", "Trentino_LocalCallDataExchange_ServiceBProxy*"
         };

         static const Trentino::Reflection::Data::Method::Param newParam[] = {
            "ptr", "Trentino::RuntimeModel::Wire"
         };

         static Trentino::Reflection::Data::Method::MetaData mdm[] = {
            { "new", "Trentino_LocalCallDataExchange_ServiceBProxy*", newParam, COUNT_OF(newParam), newObjectWithParam }, 
            { "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
         };

         // OBJECT
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino_LocalCallDataExchange_ServiceBProxy", 
            nullptr, 
            nullptr,
            0,
            mdm,
            COUNT_OF(mdm),
         };

         mmdoHandle = &mdo;

         Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
      }

      ~InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx()
      {
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   }; //class InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx
   static InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx init3;


//*************************************************************************************************
//Proxy class definition Trentino_LocalCallDataExchange_ServiceAProxy
//*************************************************************************************************
class Trentino_LocalCallDataExchange_ServiceAProxy :public Trentino::LocalCallDataExchange::ServiceA
{
      //construction
   public:
      Trentino_LocalCallDataExchange_ServiceAProxy(Trentino::RuntimeModel::Wire* wire);

      //services
   public:
  		virtual ClassC method_with_two_parameters_passed_by_value ( ClassA a, ClassB b);
  		virtual ClassC method_with_two_parameters_first_by_value_second_by_reference ( ClassA a, ClassB& b);
  		virtual ClassC method_with_two_parameters_first_by_const_value_second_by_reference ( const ClassA a, ClassB& b);
  		virtual ClassC method_with_two_parameters_first_by_value_second_const_reference ( ClassA a, const ClassB& b);
  		virtual const ClassC method_with_two_arguments_return_const_value ( const ClassA& a, const ClassB& b);
  		virtual const ClassC& method_with_one_value_return_a_const_Reference ( const ClassB& b);
  		virtual const ClassC& method_has_many_value_or_const_parameters ( ClassA a, ClassB& b, const ClassC c, const ClassA a2, const ClassB& b2);
  		virtual ClassC* method_has_a_pointer_and_a_value_return_a_pointer ( ClassA* a, ClassB b);
  		virtual ClassC* method_has_two_pointers_return_a_pointer ( ClassA* a, ClassB* b);
  		virtual ClassC* method_has_two_const_pointers_return_a_pointer ( const ClassA* a, const ClassB* b);
  		virtual ClassC* method_has_a_template_class_as_argument ( const std:: vector<ClassA>& valuesOfA);
      //data
   private:
      Trentino::RuntimeModel::Wire* mWire;
}; //class Trentino_LocalCallDataExchange_ServiceAProxy

Trentino_LocalCallDataExchange_ServiceAProxy::Trentino_LocalCallDataExchange_ServiceAProxy(Trentino::RuntimeModel::Wire* wire) : mWire(wire) {}


 ClassC Trentino_LocalCallDataExchange_ServiceAProxy::method_with_two_parameters_passed_by_value( ClassA a, ClassB b)
 {
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_with_two_parameters_passed_by_value");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(&b);
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC> ptr(static_cast<ClassC*>(invocationData->response()));
      return *ptr;
}

ClassC Trentino_LocalCallDataExchange_ServiceAProxy::method_with_two_parameters_first_by_value_second_by_reference( ClassA a, ClassB& b)
{
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_with_two_parameters_first_by_value_second_by_reference");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(&b);
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC> ptr(static_cast<ClassC*>(invocationData->response()));
      return *ptr;
}

 ClassC Trentino_LocalCallDataExchange_ServiceAProxy::method_with_two_parameters_first_by_const_value_second_by_reference( const ClassA a, ClassB& b)
{
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_with_two_parameters_first_by_const_value_second_by_reference");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(const_cast<ClassA*>(&a));
      params.push_back(&b);
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC> ptr(static_cast<ClassC*>(invocationData->response()));
      return *ptr;
}

 ClassC Trentino_LocalCallDataExchange_ServiceAProxy::method_with_two_parameters_first_by_value_second_const_reference( ClassA a, const ClassB& b)
 {
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_with_two_parameters_first_by_value_second_const_reference");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(const_cast<ClassB*>(&b));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC> ptr(static_cast<ClassC*>(invocationData->response()));
      return *ptr;
}

 const ClassC Trentino_LocalCallDataExchange_ServiceAProxy::method_with_two_arguments_return_const_value( const ClassA& a, const ClassB& b)
 {
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_with_two_arguments_return_const_value");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(const_cast<ClassA*>(&a));
      params.push_back(const_cast<ClassB*>(&b));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC> ptr(static_cast<ClassC*>(invocationData->response()));
      return *ptr;
}

 const ClassC& Trentino_LocalCallDataExchange_ServiceAProxy::method_with_one_value_return_a_const_Reference( const ClassB& b)
 {
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_with_one_value_return_a_const_Reference");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(const_cast<ClassB*>(&b));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC*> ptr(static_cast<ClassC**>(invocationData->response()));
      return **ptr;
}

 const ClassC& Trentino_LocalCallDataExchange_ServiceAProxy::method_has_many_value_or_const_parameters( ClassA a, ClassB& b, const ClassC c, const ClassA a2, const ClassB& b2)
 {
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_has_many_value_or_const_parameters");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(&b);
      params.push_back(const_cast<ClassC*>(&c));
      params.push_back(const_cast<ClassA*>(&a2));
      params.push_back(const_cast<ClassB*>(&b2));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC*> ptr(static_cast<ClassC**>(invocationData->response()));
      return **ptr;
   }

ClassC* Trentino_LocalCallDataExchange_ServiceAProxy::method_has_a_pointer_and_a_value_return_a_pointer( ClassA* a, ClassB b)
{
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_has_a_pointer_and_a_value_return_a_pointer");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(&b);
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC*> ptr(static_cast<ClassC**>(invocationData->response()));
      return *ptr;
}

ClassC* Trentino_LocalCallDataExchange_ServiceAProxy::method_has_two_pointers_return_a_pointer( ClassA* a, ClassB* b)
{
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_has_two_pointers_return_a_pointer");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(&b);
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC*> ptr(static_cast<ClassC**>(invocationData->response()));
      return *ptr;
}

ClassC* Trentino_LocalCallDataExchange_ServiceAProxy::method_has_two_const_pointers_return_a_pointer( const ClassA* a, const ClassB* b)
{
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_has_two_const_pointers_return_a_pointer");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(&a);
      params.push_back(&b);
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC*> ptr(static_cast<ClassC**>(invocationData->response()));
      return *ptr;
}

 ClassC* Trentino_LocalCallDataExchange_ServiceAProxy::method_has_a_template_class_as_argument( const std:: vector<ClassA>& valuesOfA)
{
      assert(mWire);
	   const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();   
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_has_a_template_class_as_argument");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(2);
      params.push_back(const_cast<std::vector<ClassA>*>(&valuesOfA));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      ctx->currentInvoker()->invoke(invocationData, ctx);

      boost::scoped_ptr<ClassC*> ptr(static_cast<ClassC**>(invocationData->response()));
      return *ptr;
}

    //*************************************************************************************************
   //class declaration&definition
   //InitializerTrentino_LocalCallDataExchange_ServiceAProxyRflx
   //*************************************************************************************************
   //=========================================based on implementation.cpp/class (including the parsing of namespaces in the header)
   //=========================================most parts are static right??
   class InitializerTrentino_LocalCallDataExchange_ServiceAProxyRflx
   {
      static void TRENTINO_STDCALL newObjectWithParam(void* /*thisPtr*/, void* retVal, void* params[])
      {

         *reinterpret_cast<Trentino_LocalCallDataExchange_ServiceAProxy**>(retVal) = 
            new Trentino_LocalCallDataExchange_ServiceAProxy(
            *reinterpret_cast<Trentino::RuntimeModel::Wire**>(params[0]));   
      }

      static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
      {
         Trentino_LocalCallDataExchange_ServiceAProxy* p = 
            static_cast<Trentino_LocalCallDataExchange_ServiceAProxy*>(thisPtr);
         delete p;
      }


      //construction
   public:
      InitializerTrentino_LocalCallDataExchange_ServiceAProxyRflx()
      {
         // METHOD SIGNATURES
         static const Trentino::Reflection::Data::Method::Param deleteParam[] = {
            "ptr", "Trentino_LocalCallDataExchange_ServiceAProxy*"
         };

         static const Trentino::Reflection::Data::Method::Param newParam[] = {
            "ptr", "Trentino::RuntimeModel::Wire"
         };

         static Trentino::Reflection::Data::Method::MetaData mdm[] = {
            { "new", "Trentino_LocalCallDataExchange_ServiceAProxy*", newParam, COUNT_OF(newParam), newObjectWithParam }, 
            { "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
         };

         // OBJECT
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino_LocalCallDataExchange_ServiceAProxy", 
            nullptr, 
            nullptr,
            0,
            mdm,
            COUNT_OF(mdm),
         };

         mmdoHandle = &mdo;

         Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
      }

      ~InitializerTrentino_LocalCallDataExchange_ServiceAProxyRflx()
      {
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   }; //class InitializerTrentino_LocalCallDataExchange_ServiceAProxyRflx
   static InitializerTrentino_LocalCallDataExchange_ServiceAProxyRflx init4;



}//namespace Gen
}//namespace Trentino

