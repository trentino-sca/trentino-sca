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

//standard
#include <Global/TrentinoGlobal.h>
#include <Runtime/ReflectionRuntime/TrentinoReflectionRegistration.h>
#include <string.h>


//specific
#pragma warning(push)
#pragma warning(disable:4290)
#include "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/BasicCalculatorRemoteClient/TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorImpl.h"
#pragma warning(pop)

namespace Trentino{
namespace Gen
{
	//*************************************************************************************************
	// class declaration
	// InitializerTrentino_Example_BasicCalculatorRemoteClient_BasicCalculatorRemoteClientImplRflx
	//*************************************************************************************************

   	class InitializerTrentino_Example_BasicCalculatorRemoteClient_BasicCalculatorRemoteClientImplRflx
  	 {
  	 
		//! This is the new callback to create component, retVal is a pointer of pointer which contains
		//! the address of object
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorRemoteClientImpl**>(retVal) = 
			new Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorRemoteClientImpl();
		}
		
		//! you need only thisPtr and a simple static_cast to destroy object by default delete
		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorRemoteClientImpl* p = 
			static_cast<Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorRemoteClientImpl*>(thisPtr);
			delete p;
		}
		
		//a setter method is needed for each reference of the componentType
		static void TRENTINO_STDCALL setBasicCalculatorRefMethod(void* thisPtr, void* /*retVal*/, void* params[])
		{
			Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorRemoteClientImpl* p = 
			static_cast<Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorRemoteClientImpl*>(thisPtr);
			p->setBasicCalculatorRef(*reinterpret_cast<Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator**>(params[0]));
		}
	 
		//! special cast call callback to get correct address of baseclasses in multiple inherited classes
		//! you don´t need this callback if you don´t have any mulitple inheritance in your component/class
		//! This callback is used by castCall function
		static void* TRENTINO_STDCALL castCallMyComponent (void* thisPtr, const char*  /*castInto*/ )
		{
			
			
			return thisPtr;
		}

		//construction
		
		public:
		InitializerTrentino_Example_BasicCalculatorRemoteClient_BasicCalculatorRemoteClientImplRflx()
		{

			//struct is necessary to find correct parameterlist by runtime
			static const Trentino::Reflection::Data::Method::Param deleteParamMyComponent[] = {"Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorRemoteClientImpl *"};
			static const Trentino::Reflection::Data::Method::Param setBasicCalculatorMethodParams[] = {"Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator *" };
			
			//define all "public" functions seen by reflection runtime
			static Trentino::Reflection::Data::Method::MetaData mdmMyComponent[] = {
			{ "setBasicCalculatorRef", nullptr, setBasicCalculatorMethodParams, COUNT_OF(setBasicCalculatorMethodParams), setBasicCalculatorRefMethod },
            //word "new" is reserved and can be overloaded with parameter constructors, will be
			//called by ReflectObject::newInstance
			{ "new", "Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorRemoteClientImpl*", nullptr, 0, newObjectNoParam },
			//word "delete" is reserved for destroying object and will be called by 
			//ReflectObject::deleteInstance or ReflectObject::deleteRegisteredInstance
			{ "delete", nullptr, deleteParamMyComponent, COUNT_OF(deleteParamMyComponent), deleteObject },
         };

         //register whole object
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorRemoteClientImpl", 
            nullptr, //or if you have a base class set it here! e.g. "Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorRemoteClientImplBase"
            nullptr, //we still don´t support native properties
            0, //so count of properties are 0 (for Trentino it is default!)
            mdmMyComponent, //ok register here my methodlist, incl. new and delete functions
            COUNT_OF(mdmMyComponent), //number of functions
         };

         // store it in initializer class to unregister it by destructor
         mmdoHandle = &mdo;

         //register class in reflection runtime
         Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
      }

      ~InitializerTrentino_Example_BasicCalculatorRemoteClient_BasicCalculatorRemoteClientImplRflx()
      {
         //Important: don´t forget to unregister, rflx dlls can be unloaded!
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   };//class InitializerTrentino_Example_BasicCalculatorRemoteClient_BasicCalculatorRemoteClientImplRflx
   static InitializerTrentino_Example_BasicCalculatorRemoteClient_BasicCalculatorRemoteClientImplRflx mInitializerTrentino_Example_BasicCalculatorRemoteClient_BasicCalculatorRemoteClientImplRflx1;


}// namespace Gen
}//namespace Trentino

