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
#include "I:/Trentino/trentino/DEV/cpp/src/Tests/CoreTest/TestData/ValidContribution1/BuilderImpl.h"
#include "I:/Trentino/trentino/DEV/cpp/src/Tests/CoreTest/TestData/ValidContribution1/LoggerImpl.h"
#pragma warning(pop)

namespace Trentino{
namespace Gen
{
	//*************************************************************************************************
	// class declaration
	// InitializerTrentino_Example_ValidContribution1_BuilderImplRflx
	//*************************************************************************************************

   	class InitializerTrentino_Example_ValidContribution1_BuilderImplRflx
  	 {
  	 
		//! This is the new callback to create component, retVal is a pointer of pointer which contains
		//! the address of object
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino::Example::ValidContribution1::BuilderImpl**>(retVal) = 
			new Trentino::Example::ValidContribution1::BuilderImpl();
		}
		
		//! you need only thisPtr and a simple static_cast to destroy object by default delete
		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino::Example::ValidContribution1::BuilderImpl* p = 
			static_cast<Trentino::Example::ValidContribution1::BuilderImpl*>(thisPtr);
			delete p;
		}
		
		//a setter method is needed for each reference of the componentType
	 
		//! special cast call callback to get correct address of baseclasses in multiple inherited classes
		//! you don´t need this callback if you don´t have any mulitple inheritance in your component/class
		//! This callback is used by castCall function
		static void* TRENTINO_STDCALL castCallMyComponent (void* thisPtr, const char* castInto )
		{
			
			if(strcmp(castInto, "Trentino::Example::ValidContribution1::Build") == 0)
			{
				return static_cast<Trentino::Example::ValidContribution1::Build*>
				(static_cast<Trentino::Example::ValidContribution1::BuilderImpl*>(thisPtr));
			}
			
			return thisPtr;
		}

		//construction
		
		public:
		InitializerTrentino_Example_ValidContribution1_BuilderImplRflx()
		{

			//struct is necessary to find correct parameterlist by runtime
			static const Trentino::Reflection::Data::Method::Param deleteParamMyComponent[] = {"Trentino::Example::ValidContribution1::BuilderImpl *"};
			
			//define all "public" functions seen by reflection runtime
			static Trentino::Reflection::Data::Method::MetaData mdmMyComponent[] = {
            //word "new" is reserved and can be overloaded with parameter constructors, will be
			//called by ReflectObject::newInstance
			{ "new", "Trentino::Example::ValidContribution1::BuilderImpl*", nullptr, 0, newObjectNoParam },
			//word "delete" is reserved for destroying object and will be called by 
			//ReflectObject::deleteInstance or ReflectObject::deleteRegisteredInstance
			{ "delete", nullptr, deleteParamMyComponent, COUNT_OF(deleteParamMyComponent), deleteObject },
         };

         //register whole object
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino::Example::ValidContribution1::BuilderImpl", 
            nullptr, //or if you have a base class set it here! e.g. "Trentino::Example::ValidContribution1::BuilderImplBase"
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

      ~InitializerTrentino_Example_ValidContribution1_BuilderImplRflx()
      {
         //Important: don´t forget to unregister, rflx dlls can be unloaded!
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   };//class InitializerTrentino_Example_ValidContribution1_BuilderImplRflx
   static InitializerTrentino_Example_ValidContribution1_BuilderImplRflx mInitializerTrentino_Example_ValidContribution1_BuilderImplRflx1;

	//*************************************************************************************************
	// class declaration
	// InitializerTrentino_Example_ValidContribution1_LoggerImplRflx
	//*************************************************************************************************

   	class InitializerTrentino_Example_ValidContribution1_LoggerImplRflx
  	 {
  	 
		//! This is the new callback to create component, retVal is a pointer of pointer which contains
		//! the address of object
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
		{
			*reinterpret_cast<Trentino::Example::ValidContribution1::LoggerImpl**>(retVal) = 
			new Trentino::Example::ValidContribution1::LoggerImpl();
		}
		
		//! you need only thisPtr and a simple static_cast to destroy object by default delete
		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
		{
			Trentino::Example::ValidContribution1::LoggerImpl* p = 
			static_cast<Trentino::Example::ValidContribution1::LoggerImpl*>(thisPtr);
			delete p;
		}
		
		//a setter method is needed for each reference of the componentType
	 
		//! special cast call callback to get correct address of baseclasses in multiple inherited classes
		//! you don´t need this callback if you don´t have any mulitple inheritance in your component/class
		//! This callback is used by castCall function
		static void* TRENTINO_STDCALL castCallMyComponent (void* thisPtr, const char* castInto )
		{
			
			if(strcmp(castInto, "Trentino::Example::ValidContribution1::Logger") == 0)
			{
				return static_cast<Trentino::Example::ValidContribution1::Logger*>
				(static_cast<Trentino::Example::ValidContribution1::LoggerImpl*>(thisPtr));
			}
			
			return thisPtr;
		}

		//construction
		
		public:
		InitializerTrentino_Example_ValidContribution1_LoggerImplRflx()
		{

			//struct is necessary to find correct parameterlist by runtime
			static const Trentino::Reflection::Data::Method::Param deleteParamMyComponent[] = {"Trentino::Example::ValidContribution1::LoggerImpl *"};
			
			//define all "public" functions seen by reflection runtime
			static Trentino::Reflection::Data::Method::MetaData mdmMyComponent[] = {
            //word "new" is reserved and can be overloaded with parameter constructors, will be
			//called by ReflectObject::newInstance
			{ "new", "Trentino::Example::ValidContribution1::LoggerImpl*", nullptr, 0, newObjectNoParam },
			//word "delete" is reserved for destroying object and will be called by 
			//ReflectObject::deleteInstance or ReflectObject::deleteRegisteredInstance
			{ "delete", nullptr, deleteParamMyComponent, COUNT_OF(deleteParamMyComponent), deleteObject },
         };

         //register whole object
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino::Example::ValidContribution1::LoggerImpl", 
            nullptr, //or if you have a base class set it here! e.g. "Trentino::Example::ValidContribution1::LoggerImplBase"
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

      ~InitializerTrentino_Example_ValidContribution1_LoggerImplRflx()
      {
         //Important: don´t forget to unregister, rflx dlls can be unloaded!
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   };//class InitializerTrentino_Example_ValidContribution1_LoggerImplRflx
   static InitializerTrentino_Example_ValidContribution1_LoggerImplRflx mInitializerTrentino_Example_ValidContribution1_LoggerImplRflx2;


}// namespace Gen
}//namespace Trentino

