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
#include "BasicCalculatorReturnVoidGen__TrentinoGenProxiesWrappers.h"

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
#include "../BasicCalculatorReturnVoid/services/TrentinoExampleBasicCalculatorCalculator.h"

namespace Trentino{
namespace Gen{
namespace BasicCalculatorReturnVoidGen{
   //*************************************************************************************************
   //                                          WRAPPERS
   //*************************************************************************************************

	//*************************************************************************************************
	//wrapper class definition for wrapper: Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper
	//*************************************************************************************************
	// invoke method for wrapper: Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper
	void Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper::invoke(
		const Trentino::Invocation::InvocationDataPtr& data 
		,const Trentino::Invocation::InvocationContextPtr& ctx
		,void* targetInstance) const
	{
		assert(targetInstance != nullptr);
		Trentino::Example::BasicCalculatorReturnVoid::Calculator* const myInstance = static_cast<Trentino::Example::BasicCalculatorReturnVoid::Calculator*>(targetInstance);
		const std::string& op = data->operation();
		      if(op =="add" )
      {
      		
			int& param0 = *static_cast<int*>(data->parameters()[0]);
      		
			int& param1 = *static_cast<int*>(data->parameters()[1]);
      		myInstance->add(  param0, param1 );
      	
      }

		
	}
	
   //*************************************************************************************************
   //class declaration&definition InitializerTrentino_Example_BasicCalculator_CalculatorImplWrapperRflx
   //*************************************************************************************************
	class InitializerTrentino_Example_BasicCalculatorReturnVoid_CalculatorWrapperRflx
   {
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper**>(retVal) = new Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper();
		}

		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper* p = static_cast<Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper*>(thisPtr);
			delete p;
		}
 		
   		public:
   		//construction
		InitializerTrentino_Example_BasicCalculatorReturnVoid_CalculatorWrapperRflx()
		{
			// METHOD SIGNATURES
			static const Trentino::Reflection::Data::Method::Param deleteParam[] = {"Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper *"
			};

         	static Trentino::Reflection::Data::Method::MetaData mdm[] = {
				{ "new", "Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper*", nullptr, 0, newObjectNoParam },
				{ "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
			};

			// OBJECT
			static Trentino::Reflection::Data::Object::MetaData mdo = { 
				"Trentino_Example_BasicCalculatorReturnVoid_CalculatorWrapper", 
				nullptr, 
				nullptr,
				0,
				mdm,
				COUNT_OF(mdm),
			};

			mmdoHandle = &mdo;

			Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
		}

		~InitializerTrentino_Example_BasicCalculatorReturnVoid_CalculatorWrapperRflx()
		{
			Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
		}

		//data
		private:
		Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

	}; //class InitializerTrentino_Example_BasicCalculatorReturnVoid_CalculatorWrapperRflx

   
	static InitializerTrentino_Example_BasicCalculatorReturnVoid_CalculatorWrapperRflx mInitializerTrentino_Example_BasicCalculatorReturnVoid_CalculatorWrapperRflx1; 



   //*************************************************************************************************
   //                                          PROXIES
   //*************************************************************************************************


}//namespace Gen
}//namespace Trentino
} //namespace BasicCalculatorReturnVoidGen

