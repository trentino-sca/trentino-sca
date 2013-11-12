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
#include "J:/Trentino/src/BR/762-pb3k0295-SD/cpp/src/Tests/SystemTestData/BasicPrinter_Source/TrentinoExampleBasicPrinterImpl.h"
#include "J:/Trentino/src/BR/762-pb3k0295-SD/cpp/src/Tests/SystemTestData/BasicPrinter_Source/TrentinoExampleBasicPrinterImpl2.h"
#pragma warning(pop)

namespace Trentino{
namespace Gen
{
	//*************************************************************************************************
	// class declaration
	// InitializerTrentino_Example_BasicPrinterImplRflx
	//*************************************************************************************************

   	class InitializerTrentino_Example_BasicPrinterImplRflx
  	 {
  	 
		//! This is the new callback to create component, retVal is a pointer of pointer which contains
		//! the address of object
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void* /*params*/[])
		{
			*reinterpret_cast<Trentino::Example::BasicPrinterImpl**>(retVal) = 
			new Trentino::Example::BasicPrinterImpl();
		}
		
		//! you need only thisPtr and a simple static_cast to destroy object by default delete
		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void* /*params*/[])
		{
			Trentino::Example::BasicPrinterImpl* p = 
			static_cast<Trentino::Example::BasicPrinterImpl*>(thisPtr);
			delete p;
		}
		
		//a setter method is needed for each reference of the componentType
	 
	 	 	//a setter method is needed for each property of the componentType
		//For every class with more than one base class, a corresponding castCall() function must be generated 
		//and registered in the reflection class.   This also applies to the class if any of its predecessors 
		//have more than one base class or even there are more than one base classes in the whole inheritance 
		//hierarchy since this causes the same kind of problem as with direct inheritance.  As as a robust 
		//solution can be considered the generation of cast function for all classes disregarding the actual 
		//number of base classes.		
		static void* TRENTINO_STDCALL castCallMyComponent (void* thisPtr, const char* castInto )
		{
			
			if(strcmp(castInto, "Trentino::Example::BasicPrinter") == 0)
			{
				return static_cast<Trentino::Example::BasicPrinter*>
				(static_cast<Trentino::Example::BasicPrinterImpl*>(thisPtr));
			}
			
			return thisPtr;
		}
		
		//construction
		
		public:
		InitializerTrentino_Example_BasicPrinterImplRflx()
		{

			//struct is necessary to find correct parameterlist by runtime
			static const Trentino::Reflection::Data::Method::Param deleteParamMyComponent[] = {{"Trentino::Example::BasicPrinterImpl *"}};
			//define all "public" functions seen by reflection runtime
			static Trentino::Reflection::Data::Method::MetaData mdmMyComponent[] = {
            //word "new" is reserved and can be overloaded with parameter constructors, will be
			//called by ReflectObject::newInstance
			{ "new", "Trentino::Example::BasicPrinterImpl*", nullptr, 0, newObjectNoParam },
			//word "delete" is reserved for destroying object and will be called by 
			//ReflectObject::deleteInstance or ReflectObject::deleteRegisteredInstance
			{ "delete", nullptr, deleteParamMyComponent, COUNT_OF(deleteParamMyComponent), deleteObject },
         };

         //register whole object
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino::Example::BasicPrinterImpl", 
            nullptr, //passing a pointer to the generated cast call function
            mdmMyComponent, //ok register here my methodlist, incl. new and delete functions
            COUNT_OF(mdmMyComponent), //number of functions
         };

         // store it in initializer class to unregister it by destructor
         mmdoHandle = &mdo;

         //register class in reflection runtime
         Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
      }

      ~InitializerTrentino_Example_BasicPrinterImplRflx()
      {
         //Important: don´t forget to unregister, rflx dlls can be unloaded!
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   };//class InitializerTrentino_Example_BasicPrinterImplRflx
   static InitializerTrentino_Example_BasicPrinterImplRflx mInitializerTrentino_Example_BasicPrinterImplRflx1;

	//*************************************************************************************************
	// class declaration
	// InitializerTrentino_Example_BasicPrinterImpl2Rflx
	//*************************************************************************************************

   	class InitializerTrentino_Example_BasicPrinterImpl2Rflx
  	 {
  	 
		//! This is the new callback to create component, retVal is a pointer of pointer which contains
		//! the address of object
		static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void* /*params*/[])
		{
			*reinterpret_cast<Trentino::Example::BasicPrinterImpl2**>(retVal) = 
			new Trentino::Example::BasicPrinterImpl2();
		}
		
		//! you need only thisPtr and a simple static_cast to destroy object by default delete
		static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void* /*params*/[])
		{
			Trentino::Example::BasicPrinterImpl2* p = 
			static_cast<Trentino::Example::BasicPrinterImpl2*>(thisPtr);
			delete p;
		}
		
		//a setter method is needed for each reference of the componentType
	 
	 	 	//a setter method is needed for each property of the componentType
		//For every class with more than one base class, a corresponding castCall() function must be generated 
		//and registered in the reflection class.   This also applies to the class if any of its predecessors 
		//have more than one base class or even there are more than one base classes in the whole inheritance 
		//hierarchy since this causes the same kind of problem as with direct inheritance.  As as a robust 
		//solution can be considered the generation of cast function for all classes disregarding the actual 
		//number of base classes.		
		static void* TRENTINO_STDCALL castCallMyComponent (void* thisPtr, const char* castInto )
		{
			
			if(strcmp(castInto, "Trentino::Example::BasicPrinter") == 0)
			{
				return static_cast<Trentino::Example::BasicPrinter*>
				(static_cast<Trentino::Example::BasicPrinterImpl2*>(thisPtr));
			}
			
			return thisPtr;
		}
		
		//construction
		
		public:
		InitializerTrentino_Example_BasicPrinterImpl2Rflx()
		{

			//struct is necessary to find correct parameterlist by runtime
			static const Trentino::Reflection::Data::Method::Param deleteParamMyComponent[] = {{"Trentino::Example::BasicPrinterImpl2 *"}};
			//define all "public" functions seen by reflection runtime
			static Trentino::Reflection::Data::Method::MetaData mdmMyComponent[] = {
            //word "new" is reserved and can be overloaded with parameter constructors, will be
			//called by ReflectObject::newInstance
			{ "new", "Trentino::Example::BasicPrinterImpl2*", nullptr, 0, newObjectNoParam },
			//word "delete" is reserved for destroying object and will be called by 
			//ReflectObject::deleteInstance or ReflectObject::deleteRegisteredInstance
			{ "delete", nullptr, deleteParamMyComponent, COUNT_OF(deleteParamMyComponent), deleteObject },
         };

         //register whole object
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino::Example::BasicPrinterImpl2", 
            nullptr, //passing a pointer to the generated cast call function
            mdmMyComponent, //ok register here my methodlist, incl. new and delete functions
            COUNT_OF(mdmMyComponent), //number of functions
         };

         // store it in initializer class to unregister it by destructor
         mmdoHandle = &mdo;

         //register class in reflection runtime
         Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
      }

      ~InitializerTrentino_Example_BasicPrinterImpl2Rflx()
      {
         //Important: don´t forget to unregister, rflx dlls can be unloaded!
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   };//class InitializerTrentino_Example_BasicPrinterImpl2Rflx
   static InitializerTrentino_Example_BasicPrinterImpl2Rflx mInitializerTrentino_Example_BasicPrinterImpl2Rflx2;


}// namespace Gen
}//namespace Trentino

