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
#include "BasicCalculatorGen_Trentino_Example_BasicCalculator_TrentinoGenProxiesWrappers.h"

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
#include "../BasicCalculator/services/TrentinoExampleBasicCalculatorDivider.h"
#include "../BasicCalculator/services/TrentinoExampleBasicCalculatorCalculator.h"
#include "../BasicCalculator/services/TrentinoExampleBasicCalculatorDivider.h"

namespace Trentino{
namespace Gen{
namespace BasicCalculatorGen{
   //*************************************************************************************************
   //                                          WRAPPERS
   //*************************************************************************************************

	//*************************************************************************************************
	//wrapper class definition for wrapper: Trentino_Example_BasicCalculator_CalculatorWrapper
	//*************************************************************************************************
	// invoke method for wrapper: Trentino_Example_BasicCalculator_CalculatorWrapper
	void Trentino_Example_BasicCalculator_CalculatorWrapper::invoke(
		const Trentino::Invocation::InvocationDataPtr& data 
		,const Trentino::Invocation::InvocationContextPtr& ctx
		,void* targetInstance) const
	{
		assert(targetInstance != nullptr);
		Trentino::Example::BasicCalculator::Calculator* const myInstance = static_cast<Trentino::Example::BasicCalculator::Calculator*>(targetInstance);
		const std::string& op = data->operation();
		      if(op =="add" )
      {
      		
			int& param0 = *static_cast<int*>(data->parameters()[0]);
      		
			int& param1 = *static_cast<int*>(data->parameters()[1]);
			 				int* result = new int;
				*result =  myInstance->add( param0, param1 ); 
				data->setResponse(result);
      	
      }

		else
		      if(op =="div" )
      {
      		
			int& param0 = *static_cast<int*>(data->parameters()[0]);
      		
			int& param1 = *static_cast<int*>(data->parameters()[1]);
			 				int* result = new int;
				*result =  myInstance->div( param0, param1 ); 
				data->setResponse(result);
      	
      }

		else
		      if(op =="div2" )
      {
      		
			int& param0 = *static_cast<int*>(data->parameters()[0]);
      		
			int& param1 = *static_cast<int*>(data->parameters()[1]);
			 				int* result = new int;
				*result =  myInstance->div2( param0, param1 ); 
				data->setResponse(result);
      	
      }

		
	}
	
   //*************************************************************************************************
   //class declaration&definition InitializerTrentino_Example_BasicCalculator_CalculatorImplWrapperRflx
   //*************************************************************************************************
	class InitializerTrentino_Example_BasicCalculator_CalculatorWrapperRflx
   {
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino_Example_BasicCalculator_CalculatorWrapper**>(retVal) = new Trentino_Example_BasicCalculator_CalculatorWrapper();
		}

		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino_Example_BasicCalculator_CalculatorWrapper* p = static_cast<Trentino_Example_BasicCalculator_CalculatorWrapper*>(thisPtr);
			delete p;
		}
 		
   		public:
   		//construction
		InitializerTrentino_Example_BasicCalculator_CalculatorWrapperRflx()
		{
			// METHOD SIGNATURES
			static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_BasicCalculator_CalculatorWrapper *"
			};

         	static Trentino::Reflection::Data::Method::MetaData mdm[] = {
				{ "new", "Trentino_Example_BasicCalculator_CalculatorWrapper*", nullptr, 0, newObjectNoParam },
				{ "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
			};

			// OBJECT
			static Trentino::Reflection::Data::Object::MetaData mdo = { 
				"Trentino_Example_BasicCalculator_CalculatorWrapper", 
				nullptr, 
				nullptr,
				0,
				mdm,
				COUNT_OF(mdm),
			};

			mmdoHandle = &mdo;

			Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
		}

		~InitializerTrentino_Example_BasicCalculator_CalculatorWrapperRflx()
		{
			Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
		}

		//data
		private:
		Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

	}; //class InitializerTrentino_Example_BasicCalculator_CalculatorWrapperRflx

   
	static InitializerTrentino_Example_BasicCalculator_CalculatorWrapperRflx mInitializerTrentino_Example_BasicCalculator_CalculatorWrapperRflx1; 

	//*************************************************************************************************
	//wrapper class definition for wrapper: Trentino_Example_BasicCalculator_DividerWrapper
	//*************************************************************************************************
	// invoke method for wrapper: Trentino_Example_BasicCalculator_DividerWrapper
	void Trentino_Example_BasicCalculator_DividerWrapper::invoke(
		const Trentino::Invocation::InvocationDataPtr& data 
		,const Trentino::Invocation::InvocationContextPtr& ctx
		,void* targetInstance) const
	{
		assert(targetInstance != nullptr);
		Trentino::Example::BasicCalculator::Divider* const myInstance = static_cast<Trentino::Example::BasicCalculator::Divider*>(targetInstance);
		const std::string& op = data->operation();
		      if(op =="divide" )
      {
      		
			int& param0 = *static_cast<int*>(data->parameters()[0]);
      		
			int& param1 = *static_cast<int*>(data->parameters()[1]);
			 				int** result = new int*;
					*result =  &myInstance->divide(  param0, param1 ); 
				data->setResponse(result);
      	
      }

		
	}
	
   //*************************************************************************************************
   //class declaration&definition InitializerTrentino_Example_BasicCalculator_CalculatorImplWrapperRflx
   //*************************************************************************************************
	class InitializerTrentino_Example_BasicCalculator_DividerWrapperRflx
   {
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino_Example_BasicCalculator_DividerWrapper**>(retVal) = new Trentino_Example_BasicCalculator_DividerWrapper();
		}

		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino_Example_BasicCalculator_DividerWrapper* p = static_cast<Trentino_Example_BasicCalculator_DividerWrapper*>(thisPtr);
			delete p;
		}
 		
   		public:
   		//construction
		InitializerTrentino_Example_BasicCalculator_DividerWrapperRflx()
		{
			// METHOD SIGNATURES
			static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_BasicCalculator_DividerWrapper *"
			};

         	static Trentino::Reflection::Data::Method::MetaData mdm[] = {
				{ "new", "Trentino_Example_BasicCalculator_DividerWrapper*", nullptr, 0, newObjectNoParam },
				{ "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
			};

			// OBJECT
			static Trentino::Reflection::Data::Object::MetaData mdo = { 
				"Trentino_Example_BasicCalculator_DividerWrapper", 
				nullptr, 
				nullptr,
				0,
				mdm,
				COUNT_OF(mdm),
			};

			mmdoHandle = &mdo;

			Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
		}

		~InitializerTrentino_Example_BasicCalculator_DividerWrapperRflx()
		{
			Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
		}

		//data
		private:
		Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

	}; //class InitializerTrentino_Example_BasicCalculator_DividerWrapperRflx

   
	static InitializerTrentino_Example_BasicCalculator_DividerWrapperRflx mInitializerTrentino_Example_BasicCalculator_DividerWrapperRflx2; 



   //*************************************************************************************************
   //                                          PROXIES
   //*************************************************************************************************

//*************************************************************************************************
//Proxy class definition Trentino_Example_BasicCalculator_DividerProxy
//*************************************************************************************************
      Trentino_Example_BasicCalculator_DividerProxy::Trentino_Example_BasicCalculator_DividerProxy(Trentino::RuntimeModel::WireBase* wire):mWire(wire){}  
 int& Trentino_Example_BasicCalculator_DividerProxy::divide( int a, int b)
 {
      assert(mWire);
      const Trentino::RuntimeModel::ServiceBasePtr targetService = mWire->service().lock();
   
      if(targetService.get() == nullptr)
         throw std::runtime_error("service unavailable");
   
      Trentino::Invocation::InvocationDataPtr invocationData(new Trentino::Invocation::InvocationData());     
      invocationData->setTargetService(targetService); 
      invocationData->setOperation("divide");
   
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
		        	boost::scoped_ptr<int*> responsePtr(static_cast<int**>(invocationData->response()));
        return **responsePtr;
   }

  //class declaration&definition
  //****************************************************************************************************
  //                                         InitializerTrentino_Example_BasicCalculator_DividerProxyRflx
  //****************************************************************************************************
  //! \brief based on implementation.cpp/class (including the parsing of namespaces in the header)
  //! most parts are static right??
  //****************************************************************************************************
   class InitializerTrentino_Example_BasicCalculator_DividerProxyRflx
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

         *reinterpret_cast<Trentino_Example_BasicCalculator_DividerProxy**>(retVal) = 
            new Trentino_Example_BasicCalculator_DividerProxy(
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
         Trentino_Example_BasicCalculator_DividerProxy* p = 
            static_cast<Trentino_Example_BasicCalculator_DividerProxy*>(thisPtr);
         delete p;
      }


      //construction
   public:
      //****************************************************************************************************
      //                   InitializerTrentino_Example_BasicCalculator_DividerProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      InitializerTrentino_Example_BasicCalculator_DividerProxyRflx()
      {
         // METHOD SIGNATURES
         static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_BasicCalculator_DividerProxy *"
         };

         static const Trentino::Reflection::Data::Method::Param newParam[] = {"Trentino::RuntimeModel::Wire *"};

         static Trentino::Reflection::Data::Method::MetaData mdm[] = {
            { "new", "Trentino_Example_BasicCalculator_DividerProxy *", newParam, COUNT_OF(newParam), newObjectWithParam }, 
            { "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
         };

         // OBJECT
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino_Example_BasicCalculator_DividerProxy", 
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
      //                ~InitializerTrentino_Example_BasicCalculator_DividerProxyRflx()
      //****************************************************************************************************
      //! \brief
      //! \return 
      //****************************************************************************************************
      ~InitializerTrentino_Example_BasicCalculator_DividerProxyRflx()
      {
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   }; //class InitializerTrentino_Example_BasicCalculator_DividerProxyRflx
   static InitializerTrentino_Example_BasicCalculator_DividerProxyRflx mInitializerTrentino_Example_BasicCalculator_DividerProxyRflx3;



}//namespace Gen
}//namespace Trentino
}//namespace BasicCalculatorGen

