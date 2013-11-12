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

#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB
#endif

//header
#include "LocalCallDataExchangeExtendedGen_Trentino_LocalCallDataExchange_TrentinoGenProxiesWrappers.h"

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
#include "../LocalCallDataExchangeExtended/services/TrentinoLocalCallDataExchangeServiceAB.h"
#include "../LocalCallDataExchangeExtended/services/TrentinoLocalCallDataExchangeServiceAB.h"

namespace Trentino{
namespace Gen{
namespace LocalCallDataExchangeExtendedGen{
   //*************************************************************************************************
   //                                          WRAPPERS
   //*************************************************************************************************

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
				*result =  myInstance->method_with_two_parameters_passed_by_value( param0, param1 ); 
				data->setResponse(result);
      	
      }

		else
		      if(op =="method_with_two_parameters_first_by_value_second_by_reference" )
      {
      		
			Trentino::LocalCallDataExchange::ClassA& param0 = *static_cast<Trentino::LocalCallDataExchange::ClassA*>(data->parameters()[0]);
      		
			Trentino::LocalCallDataExchange::ClassB& param1 = *static_cast<Trentino::LocalCallDataExchange::ClassB*>(data->parameters()[1]);
			 				Trentino::LocalCallDataExchange::ClassC* result = new Trentino::LocalCallDataExchange::ClassC;
				*result =  myInstance->method_with_two_parameters_first_by_value_second_by_reference( param0, param1 ); 
				data->setResponse(result);
      	
      }

		else
		      if(op =="method_with_two_parameters_first_by_const_value_second_by_reference" )
      {
      		
			const Trentino::LocalCallDataExchange::ClassA& param0 = *static_cast<const Trentino::LocalCallDataExchange::ClassA*>(data->parameters()[0]);
      		
			Trentino::LocalCallDataExchange::ClassB& param1 = *static_cast<Trentino::LocalCallDataExchange::ClassB*>(data->parameters()[1]);
			 				Trentino::LocalCallDataExchange::ClassC* result = new Trentino::LocalCallDataExchange::ClassC;
				*result =  myInstance->method_with_two_parameters_first_by_const_value_second_by_reference( param0, param1 ); 
				data->setResponse(result);
      	
      }

		else
		      if(op =="method_with_two_parameters_first_by_value_second_const_reference" )
      {
      		
			Trentino::LocalCallDataExchange::ClassA& param0 = *static_cast<Trentino::LocalCallDataExchange::ClassA*>(data->parameters()[0]);
      		
			const Trentino::LocalCallDataExchange::ClassB& param1 = *static_cast<const Trentino::LocalCallDataExchange::ClassB*>(data->parameters()[1]);
			 				Trentino::LocalCallDataExchange::ClassC* result = new Trentino::LocalCallDataExchange::ClassC;
				*result =  myInstance->method_with_two_parameters_first_by_value_second_const_reference( param0, param1 ); 
				data->setResponse(result);
      	
      }

		else
		      if(op =="method_with_two_arguments_return_const_value" )
      {
      		
			const Trentino::LocalCallDataExchange::ClassA& param0 = *static_cast<const Trentino::LocalCallDataExchange::ClassA*>(data->parameters()[0]);
      		
			const Trentino::LocalCallDataExchange::ClassB& param1 = *static_cast<const Trentino::LocalCallDataExchange::ClassB*>(data->parameters()[1]);
			 				 Trentino::LocalCallDataExchange::ClassC* result = new  Trentino::LocalCallDataExchange::ClassC;
				*result =  myInstance->method_with_two_arguments_return_const_value( param0, param1 ); 
				data->setResponse(result);
      	
      }

		else
		      if(op =="method_with_one_value_return_a_const_Reference" )
      {
      		
			const Trentino::LocalCallDataExchange::ClassB& param0 = *static_cast<const Trentino::LocalCallDataExchange::ClassB*>(data->parameters()[0]);
			 				 Trentino::LocalCallDataExchange::ClassC** result = new  Trentino::LocalCallDataExchange::ClassC*;
					*result =  const_cast< Trentino::LocalCallDataExchange::ClassC*>(&myInstance->method_with_one_value_return_a_const_Reference(  param0 )); 
				data->setResponse(result);
      	
      }

		else
		      if(op =="method_has_many_value_or_const_parameters" )
      {
      		
			Trentino::LocalCallDataExchange::ClassA& param0 = *static_cast<Trentino::LocalCallDataExchange::ClassA*>(data->parameters()[0]);
      		
			Trentino::LocalCallDataExchange::ClassB& param1 = *static_cast<Trentino::LocalCallDataExchange::ClassB*>(data->parameters()[1]);
      		
			const Trentino::LocalCallDataExchange::ClassC& param2 = *static_cast<const Trentino::LocalCallDataExchange::ClassC*>(data->parameters()[2]);
      		
			const Trentino::LocalCallDataExchange::ClassA& param3 = *static_cast<const Trentino::LocalCallDataExchange::ClassA*>(data->parameters()[3]);
      		
			const Trentino::LocalCallDataExchange::ClassB& param4 = *static_cast<const Trentino::LocalCallDataExchange::ClassB*>(data->parameters()[4]);
			 				Trentino::LocalCallDataExchange::ClassC** result = new Trentino::LocalCallDataExchange::ClassC*;
					*result =  &myInstance->method_has_many_value_or_const_parameters(  param0, param1, param2, param3, param4 ); 
				data->setResponse(result);
      	
      }

		else
		      if(op =="method_has_a_pointer_and_a_value_return_a_pointer" )
      {
      		
			Trentino::LocalCallDataExchange::ClassA& param0 = *static_cast<Trentino::LocalCallDataExchange::ClassA*>(data->parameters()[0]);
      		
			Trentino::LocalCallDataExchange::ClassB& param1 = *static_cast<Trentino::LocalCallDataExchange::ClassB*>(data->parameters()[1]);
			 				Trentino::LocalCallDataExchange::ClassC** result = new Trentino::LocalCallDataExchange::ClassC*;
				*result =  myInstance->method_has_a_pointer_and_a_value_return_a_pointer( &param0, param1 ); 
				data->setResponse(result);
      	
      }

		else
		      if(op =="method_has_two_pointers_return_a_pointer" )
      {
      		
			Trentino::LocalCallDataExchange::ClassA& param0 = *static_cast<Trentino::LocalCallDataExchange::ClassA*>(data->parameters()[0]);
      		
			Trentino::LocalCallDataExchange::ClassB& param1 = *static_cast<Trentino::LocalCallDataExchange::ClassB*>(data->parameters()[1]);
			 				Trentino::LocalCallDataExchange::ClassC** result = new Trentino::LocalCallDataExchange::ClassC*;
				*result =  myInstance->method_has_two_pointers_return_a_pointer( &param0, &param1 ); 
				data->setResponse(result);
      	
      }

		else
		      if(op =="method_has_two_const_pointers_return_a_pointer" )
      {
      		
			const Trentino::LocalCallDataExchange::ClassA& param0 = *static_cast<const Trentino::LocalCallDataExchange::ClassA*>(data->parameters()[0]);
      		
			const Trentino::LocalCallDataExchange::ClassB& param1 = *static_cast<const Trentino::LocalCallDataExchange::ClassB*>(data->parameters()[1]);
			 				Trentino::LocalCallDataExchange::ClassC** result = new Trentino::LocalCallDataExchange::ClassC*;
				*result =  myInstance->method_has_two_const_pointers_return_a_pointer( &param0, &param1 ); 
				data->setResponse(result);
      	
      }

		else
		      if(op =="method_has_a_template_class_as_argument" )
      {
      		
			const std::vector<Trentino::LocalCallDataExchange::ClassA>& param0 = *static_cast<const std::vector<Trentino::LocalCallDataExchange::ClassA>*>(data->parameters()[0]);
			 				Trentino::LocalCallDataExchange::ClassC** result = new Trentino::LocalCallDataExchange::ClassC*;
				*result =  myInstance->method_has_a_template_class_as_argument( param0 ); 
				data->setResponse(result);
      	
      }

		else
		      if(op =="method_take_and_return_pointer_of_pointer" )
      {
      		
			const Trentino::LocalCallDataExchange::ClassA*& param0 = *static_cast<const Trentino::LocalCallDataExchange::ClassA**>(data->parameters()[0]);
			 				Trentino::LocalCallDataExchange::ClassC*** result = new Trentino::LocalCallDataExchange::ClassC**;
				*result =  myInstance->method_take_and_return_pointer_of_pointer( &param0 ); 
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
			static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_LocalCallDataExchange_ServiceBWrapper *"
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

   
	static InitializerTrentino_LocalCallDataExchange_ServiceBWrapperRflx mInitializerTrentino_LocalCallDataExchange_ServiceBWrapperRflx1; 



   //*************************************************************************************************
   //                                          PROXIES
   //*************************************************************************************************

//*************************************************************************************************
//Proxy class definition Trentino_LocalCallDataExchange_ServiceBProxy
//*************************************************************************************************
      Trentino_LocalCallDataExchange_ServiceBProxy::Trentino_LocalCallDataExchange_ServiceBProxy(Trentino::RuntimeModel::WireBase* wire):mWire(wire){}  
 Trentino::LocalCallDataExchange::ClassC Trentino_LocalCallDataExchange_ServiceBProxy::method_with_two_parameters_passed_by_value( Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB b)
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
        	//here4
       		 	params.push_back(&a);
      	    
        	//here4
       		 	params.push_back(&b);
      	    
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
		 		boost::scoped_ptr<Trentino::LocalCallDataExchange::ClassC> responsePtr(static_cast<Trentino::LocalCallDataExchange::ClassC*>(invocationData->response()));
        return *responsePtr;
   }

 Trentino::LocalCallDataExchange::ClassC Trentino_LocalCallDataExchange_ServiceBProxy::method_with_two_parameters_first_by_value_second_by_reference( Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b)
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
        	//here4
       		 	params.push_back(&a);
      	    
        	//here4
       		 	params.push_back(&b);
      	    
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
		 		boost::scoped_ptr<Trentino::LocalCallDataExchange::ClassC> responsePtr(static_cast<Trentino::LocalCallDataExchange::ClassC*>(invocationData->response()));
        return *responsePtr;
   }

 Trentino::LocalCallDataExchange::ClassC Trentino_LocalCallDataExchange_ServiceBProxy::method_with_two_parameters_first_by_const_value_second_by_reference( const Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b)
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

        	//here2
       		 	params.push_back(const_cast<Trentino::LocalCallDataExchange::ClassA*>(&a));
        	//here4
       		 	params.push_back(&b);
      	    
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
		 		boost::scoped_ptr<Trentino::LocalCallDataExchange::ClassC> responsePtr(static_cast<Trentino::LocalCallDataExchange::ClassC*>(invocationData->response()));
        return *responsePtr;
   }

 Trentino::LocalCallDataExchange::ClassC Trentino_LocalCallDataExchange_ServiceBProxy::method_with_two_parameters_first_by_value_second_const_reference( Trentino::LocalCallDataExchange::ClassA a, const Trentino::LocalCallDataExchange::ClassB& b)
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
        	//here4
       		 	params.push_back(&a);
      	    

        	//here2
       		 	params.push_back(const_cast<Trentino::LocalCallDataExchange::ClassB*>(&b));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
		 		boost::scoped_ptr<Trentino::LocalCallDataExchange::ClassC> responsePtr(static_cast<Trentino::LocalCallDataExchange::ClassC*>(invocationData->response()));
        return *responsePtr;
   }

 const Trentino::LocalCallDataExchange::ClassC Trentino_LocalCallDataExchange_ServiceBProxy::method_with_two_arguments_return_const_value( const Trentino::LocalCallDataExchange::ClassA& a, const Trentino::LocalCallDataExchange::ClassB& b)
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

        	//here2
       		 	params.push_back(const_cast<Trentino::LocalCallDataExchange::ClassA*>(&a));

        	//here2
       		 	params.push_back(const_cast<Trentino::LocalCallDataExchange::ClassB*>(&b));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
		 		boost::scoped_ptr<const Trentino::LocalCallDataExchange::ClassC> responsePtr(static_cast<const Trentino::LocalCallDataExchange::ClassC*>(invocationData->response()));
        return *responsePtr;
   }

 const Trentino::LocalCallDataExchange::ClassC& Trentino_LocalCallDataExchange_ServiceBProxy::method_with_one_value_return_a_const_Reference( const Trentino::LocalCallDataExchange::ClassB& b)
 {
      assert(mWire);
      const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_with_one_value_return_a_const_Reference");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(1);

        	//here2
       		 	params.push_back(const_cast<Trentino::LocalCallDataExchange::ClassB*>(&b));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
		        	boost::scoped_ptr<const Trentino::LocalCallDataExchange::ClassC*> responsePtr(static_cast<const Trentino::LocalCallDataExchange::ClassC**>(invocationData->response()));
        return **responsePtr;
   }

 Trentino::LocalCallDataExchange::ClassC& Trentino_LocalCallDataExchange_ServiceBProxy::method_has_many_value_or_const_parameters( Trentino::LocalCallDataExchange::ClassA a, Trentino::LocalCallDataExchange::ClassB& b, const Trentino::LocalCallDataExchange::ClassC c, const Trentino::LocalCallDataExchange::ClassA a2, const Trentino::LocalCallDataExchange::ClassB& b2)
 {
      assert(mWire);
      const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_has_many_value_or_const_parameters");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(5);
        	//here4
       		 	params.push_back(&a);
      	    
        	//here4
       		 	params.push_back(&b);
      	    

        	//here2
       		 	params.push_back(const_cast<Trentino::LocalCallDataExchange::ClassC*>(&c));

        	//here2
       		 	params.push_back(const_cast<Trentino::LocalCallDataExchange::ClassA*>(&a2));

        	//here2
       		 	params.push_back(const_cast<Trentino::LocalCallDataExchange::ClassB*>(&b2));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
		        	boost::scoped_ptr<Trentino::LocalCallDataExchange::ClassC*> responsePtr(static_cast<Trentino::LocalCallDataExchange::ClassC**>(invocationData->response()));
        return **responsePtr;
   }

 Trentino::LocalCallDataExchange::ClassC* Trentino_LocalCallDataExchange_ServiceBProxy::method_has_a_pointer_and_a_value_return_a_pointer( Trentino::LocalCallDataExchange::ClassA* a, Trentino::LocalCallDataExchange::ClassB b)
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
        	//here3
        		 params.push_back(a);
        		 
      	    
        	//here4
       		 	params.push_back(&b);
      	    
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
		 		boost::scoped_ptr<Trentino::LocalCallDataExchange::ClassC*> responsePtr(static_cast<Trentino::LocalCallDataExchange::ClassC**>(invocationData->response()));
        return *responsePtr;
   }

 Trentino::LocalCallDataExchange::ClassC* Trentino_LocalCallDataExchange_ServiceBProxy::method_has_two_pointers_return_a_pointer( Trentino::LocalCallDataExchange::ClassA* a, Trentino::LocalCallDataExchange::ClassB* b)
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
        	//here3
        		 params.push_back(a);
        		 
      	    
        	//here3
        		 params.push_back(b);
        		 
      	    
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
		 		boost::scoped_ptr<Trentino::LocalCallDataExchange::ClassC*> responsePtr(static_cast<Trentino::LocalCallDataExchange::ClassC**>(invocationData->response()));
        return *responsePtr;
   }

 Trentino::LocalCallDataExchange::ClassC* Trentino_LocalCallDataExchange_ServiceBProxy::method_has_two_const_pointers_return_a_pointer( const Trentino::LocalCallDataExchange::ClassA* a, const Trentino::LocalCallDataExchange::ClassB* b)
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

        	//here1
        		params.push_back(const_cast<Trentino::LocalCallDataExchange::ClassA*>(a));
        		 

        	//here1
        		params.push_back(const_cast<Trentino::LocalCallDataExchange::ClassB*>(b));
        		 
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
		 		boost::scoped_ptr<Trentino::LocalCallDataExchange::ClassC*> responsePtr(static_cast<Trentino::LocalCallDataExchange::ClassC**>(invocationData->response()));
        return *responsePtr;
   }

 Trentino::LocalCallDataExchange::ClassC* Trentino_LocalCallDataExchange_ServiceBProxy::method_has_a_template_class_as_argument( const std::vector<Trentino::LocalCallDataExchange::ClassA>& valuesOfA)
 {
      assert(mWire);
      const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_has_a_template_class_as_argument");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(1);

        	//here2
       		 	params.push_back(const_cast<std::vector<Trentino::LocalCallDataExchange::ClassA>*>(&valuesOfA));
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
		 		boost::scoped_ptr<Trentino::LocalCallDataExchange::ClassC*> responsePtr(static_cast<Trentino::LocalCallDataExchange::ClassC**>(invocationData->response()));
        return *responsePtr;
   }

 Trentino::LocalCallDataExchange::ClassC** Trentino_LocalCallDataExchange_ServiceBProxy::method_take_and_return_pointer_of_pointer( const Trentino::LocalCallDataExchange::ClassA** a)
 {
      assert(mWire);
      const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("method_take_and_return_pointer_of_pointer");
   
      Trentino::Invocation::InvocationData::Parameters params;
      params.reserve(1);

        	//here1
        		params.push_back(const_cast<Trentino::LocalCallDataExchange::ClassA**>(a));
        		 
      invocationData->setParameters(params);
   
      const Trentino::Invocation::InvocationContextPtr ctx = mWire->invocationContext();
      
      if(!ctx->currentInvoker()->invoke(invocationData, ctx))
	  {
		throw std::runtime_error("service unavailable");
	  }
		 		boost::scoped_ptr<Trentino::LocalCallDataExchange::ClassC**> responsePtr(static_cast<Trentino::LocalCallDataExchange::ClassC***>(invocationData->response()));
        return *responsePtr;
   }

  //class declaration&definition
  //****************************************************************************************************
  //                                         InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx
  //****************************************************************************************************
  //! \brief based on implementation.cpp/class (including the parsing of namespaces in the header)
  //! most parts are static right??
  //****************************************************************************************************
   class InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx
   {
      //****************************************************************************************************
      //                                         newObjectWithParam()
      //****************************************************************************************************
      //! \brief
      //! \param void *
      //! \param void * retVal
      //! \param void * params[]
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL newObjectWithParam(void* /*thisPtr*/, void* retVal, void* params[])
      {

         *reinterpret_cast<Trentino_LocalCallDataExchange_ServiceBProxy**>(retVal) = 
            new Trentino_LocalCallDataExchange_ServiceBProxy(
            *reinterpret_cast<Trentino::RuntimeModel::WireBase**>(params[0]));   
      }

      //****************************************************************************************************
      //                                         deleteObject()
      //****************************************************************************************************
      //! \brief
      //! \param void * thisPtr
      //! \param void *
      //! \param void * *
      //! \return void TRENTINO_STDCALL
      //****************************************************************************************************
      static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
      {
         Trentino_LocalCallDataExchange_ServiceBProxy* p = 
            static_cast<Trentino_LocalCallDataExchange_ServiceBProxy*>(thisPtr);
         delete p;
      }


      //construction
   public:
      //****************************************************************************************************
      //                   InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx()
      {
         // METHOD SIGNATURES
         static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_LocalCallDataExchange_ServiceBProxy *"
         };

         static const Trentino::Reflection::Data::Method::Param newParam[] = {"Trentino::RuntimeModel::Wire *"};

         static Trentino::Reflection::Data::Method::MetaData mdm[] = {
            { "new", "Trentino_LocalCallDataExchange_ServiceBProxy *", newParam, COUNT_OF(newParam), newObjectWithParam }, 
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

      //****************************************************************************************************
      //                ~InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      ~InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx()
      {
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   }; //class InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx
   static InitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx mInitializerTrentino_LocalCallDataExchange_ServiceBProxyRflx2;



}//namespace Gen
}//namespace Trentino
} //namespace LocalCallDataExchangeExtendedGen

