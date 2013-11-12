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
#include <Global/TrentinoGlobal.h>
#include <Runtime/ReflectionRuntime/TrentinoReflectionRegistration.h>
#include <string.h>


//specific
//implementation.cpp/@header
#include "TrentinoLocalCallDataExchangeServiceABImpl.h"

//specific
//implementation.cpp/@header
#include "TrentinoLocalCallDataExchangeServiceABImpl.h"


namespace Trentino{
namespace Gen
{
	//*************************************************************************************************
	// class declaration
	// InitializerTrentino_Example_MyComponentRflx
	//*************************************************************************************************
	//After Initializer put the namespaces with underscore
	//get the class name from implementation.cpp/@class 
   	class InitializerTrentino_LocalCallDataExchange_ServiceAImplRflx
  	 {
      //! This is the new callback to create MyComponent, retVal is a pointer of pointer which contains
      //! the address of object
      static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
      {
         *reinterpret_cast<Trentino::LocalCallDataExchange::ServiceAImpl**>(retVal) = 
            new Trentino::LocalCallDataExchange::ServiceAImpl();
      }

      //! you need only thisPtr and a simple static_cast to destroy object by default delete
      static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
      {
         Trentino::LocalCallDataExchange::ServiceAImpl* p = 
            static_cast<Trentino::LocalCallDataExchange::ServiceAImpl*>(thisPtr);
         delete p;
      }
 	//a setter method is needed for each reference of the componentType
	 static void TRENTINO_STDCALL setServiceBMethod(void* thisPtr, void* /*retVal*/, void* params[])
      {
         //first cast in correct targettype
         Trentino::LocalCallDataExchange::ServiceAImpl* p = 
            static_cast<Trentino::LocalCallDataExchange::ServiceAImpl*>(thisPtr);

         //all parameters are pointers pointers which must be dereferenced to a normal pointer to object
         p->setServiceB(*reinterpret_cast<Trentino::LocalCallDataExchange::ServiceB**>(params[0]));
      }
	//! special cast call callback to get correct address of baseclasses in multiple inherited classes
      //! you don´t need this callback if you don´t have any mulitple inheritance in your component/class
      //! This callback is used by castCall function
	  // For each service of the componentType a dedicated if is required
      static void* TRENTINO_STDCALL castCallMyComponent (void* thisPtr, const char* castInto)
      {
         //ok by string compare, we must first cast basic void* into derived class pointer and
         //cast it into specified baseclass Trentino::Example::ServiceA to get correct offset 
         //of class pointer 
	    if(strcmp(castInto, "Trentino::LocalCallDataExchange::ServiceA") == 0)
         {
            return static_cast<Trentino::LocalCallDataExchange::ServiceA*>
               (static_cast<Trentino::LocalCallDataExchange::ServiceAImpl*>(thisPtr));
         }
         //no conversion found, pass through
         return thisPtr;
      }
      //construction
   public:
      InitializerTrentino_LocalCallDataExchange_ServiceAImplRflx()
      {
         //delete parameter
         //struct is necessary to find correct parameterlist by runtime
         static const Trentino::Reflection::Data::Method::Param deleteParamMyComponent[] = {
            "ptr", "Trentino::LocalCallDataExchange::ServiceAImpl*"
         };

         //Parameterlist for Trentino::Example::ServiceA::setFunc1
		 //We have to set the parameters for each reference of compType
         static const Trentino::Reflection::Data::Method::Param setServiceBMethodParams[] = {
            "param1", "Trentino::LocalCallDataExchange::ServiceB*" //content of the reference/interface.cpp/@class 
         };
         //define all "public" functions seen by reflection runtime
         static Trentino::Reflection::Data::Method::MetaData mdmMyComponent[] = {
            //register here Trentino::Example::ServiceA::setFunc1
			 //for each reference of componentType we need an entry here
            { "setServiceB", nullptr, setServiceBMethodParams, COUNT_OF(setServiceBMethodParams), setServiceBMethod },
            //word "new" is reserved and can be overloaded with parameter constructors, will be
            //called by ReflectObject::newInstance
            { "new", "Trentino::LocalCallDataExchange::ServiceAImpl*", nullptr, 0, newObjectNoParam },
            //word "delete" is reserved for destroying object and will be called by 
            //ReflectObject::deleteInstance or ReflectObject::deleteRegisteredInstance
            { "delete", nullptr, deleteParamMyComponent, COUNT_OF(deleteParamMyComponent), deleteObject },
         };

         //register whole object
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino::LocalCallDataExchange::ServiceAImpl", //content of @header of the implementation.cpp
            nullptr, //or if you have a base class set it here! e.g. "Trentino::LocalCallDataExchange::ServiceAImplBase"
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

      ~InitializerTrentino_LocalCallDataExchange_ServiceAImplRflx()
      {
         //Important: don´t forget to unregister, rflx dlls can be unloaded!
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   };//class InitializerTrentino_LocalCallDataExchange_ServiceAImplRflx
   static InitializerTrentino_LocalCallDataExchange_ServiceAImplRflx init1;

	//*************************************************************************************************
	// class declaration
	// InitializerTrentino_Example_MyComponentRflx
	//*************************************************************************************************
	//After Initializer put the namespaces with underscore
	//get the class name from implementation.cpp/@class 
   	class InitializerTrentino_LocalCallDataExchange_ServiceBImplRflx
  	 {
      //! This is the new callback to create MyComponent, retVal is a pointer of pointer which contains
      //! the address of object
      static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
      {
         *reinterpret_cast<Trentino::LocalCallDataExchange::ServiceBImpl**>(retVal) = 
            new Trentino::LocalCallDataExchange::ServiceBImpl();
      }

      //! you need only thisPtr and a simple static_cast to destroy object by default delete
      static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
      {
         Trentino::LocalCallDataExchange::ServiceBImpl* p = 
            static_cast<Trentino::LocalCallDataExchange::ServiceBImpl*>(thisPtr);
         delete p;
      }
 	//a setter method is needed for each reference of the componentType
	 static void TRENTINO_STDCALL setServiceAMethod(void* thisPtr, void* /*retVal*/, void* params[])
      {
         //first cast in correct targettype
         Trentino::LocalCallDataExchange::ServiceBImpl* p = 
            static_cast<Trentino::LocalCallDataExchange::ServiceBImpl*>(thisPtr);

         //all parameters are pointers pointers which must be dereferenced to a normal pointer to object
         p->setServiceA(*reinterpret_cast<Trentino::LocalCallDataExchange::ServiceA**>(params[0]));
      }
	//! special cast call callback to get correct address of baseclasses in multiple inherited classes
      //! you don´t need this callback if you don´t have any mulitple inheritance in your component/class
      //! This callback is used by castCall function
	  // For each service of the componentType a dedicated if is required
      static void* TRENTINO_STDCALL castCallMyComponent (void* thisPtr, const char* castInto)
      {
         //ok by string compare, we must first cast basic void* into derived class pointer and
         //cast it into specified baseclass Trentino::Example::ServiceA to get correct offset 
         //of class pointer 
	    if(strcmp(castInto, "Trentino::LocalCallDataExchange::ServiceB") == 0)
         {
            return static_cast<Trentino::LocalCallDataExchange::ServiceB*>
               (static_cast<Trentino::LocalCallDataExchange::ServiceBImpl*>(thisPtr));
         }
         //no conversion found, pass through
         return thisPtr;
      }
      //construction
   public:
      InitializerTrentino_LocalCallDataExchange_ServiceBImplRflx()
      {
         //delete parameter
         //struct is necessary to find correct parameterlist by runtime
         static const Trentino::Reflection::Data::Method::Param deleteParamMyComponent[] = {
            "ptr", "Trentino::LocalCallDataExchange::ServiceBImpl*"
         };

         //Parameterlist for Trentino::Example::ServiceA::setFunc1
		 //We have to set the parameters for each reference of compType
         static const Trentino::Reflection::Data::Method::Param setServiceAMethodParams[] = {
            "param1", "Trentino::LocalCallDataExchange::ServiceA*" //content of the reference/interface.cpp/@class 
         };
         //define all "public" functions seen by reflection runtime
         static Trentino::Reflection::Data::Method::MetaData mdmMyComponent[] = {
            //register here Trentino::Example::ServiceA::setFunc1
			 //for each reference of componentType we need an entry here
            { "setServiceA", nullptr, setServiceAMethodParams, COUNT_OF(setServiceAMethodParams), setServiceAMethod },
            //word "new" is reserved and can be overloaded with parameter constructors, will be
            //called by ReflectObject::newInstance
            { "new", "Trentino::LocalCallDataExchange::ServiceBImpl*", nullptr, 0, newObjectNoParam },
            //word "delete" is reserved for destroying object and will be called by 
            //ReflectObject::deleteInstance or ReflectObject::deleteRegisteredInstance
            { "delete", nullptr, deleteParamMyComponent, COUNT_OF(deleteParamMyComponent), deleteObject },
         };

         //register whole object
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino::LocalCallDataExchange::ServiceBImpl", //content of @header of the implementation.cpp
            nullptr, //or if you have a base class set it here! e.g. "Trentino::LocalCallDataExchange::ServiceBImplBase"
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

      ~InitializerTrentino_LocalCallDataExchange_ServiceBImplRflx()
      {
         //Important: don´t forget to unregister, rflx dlls can be unloaded!
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   };//class InitializerTrentino_LocalCallDataExchange_ServiceBImplRflx
   static InitializerTrentino_LocalCallDataExchange_ServiceBImplRflx init2;


}// namespace Gen
}//namespace Trentino

