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
#include <string.h>
//needed: to get all reflection runtime symbols
#include <Runtime/ReflectionRuntime/TrentinoReflectionRegistration.h>

//specific
//implementation.cpp/@header
#include "../SCAReferenceExample/TrentinoExampleMyComponent.h"
#include "../SCAReferenceExample/SCAReferenceExampleImpl.h"

namespace Trentino{
namespace Gen
{
   //*************************************************************************************************
   //class declaration
   //InitializerTrentino_Example_MyComponentRflx
   //*************************************************************************************************
	//After Initializer put the namespaces with underscore
	//get the class name from implementation.cpp/@class 
   class InitializerTrentino_Example_MyComponentRflx
   {
      //! This is the new callback to create MyComponent, retVal is a pointer of pointer which contains
      //! the address of object
      static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
      {
         *reinterpret_cast<Trentino::Example::MyComponent**>(retVal) = 
            new Trentino::Example::MyComponent();
      }

      //! you need only thisPtr and a simple static_cast to destroy object by default delete
      static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
      {
         Trentino::Example::MyComponent* p = 
            static_cast<Trentino::Example::MyComponent*>(thisPtr);
         delete p;
      }

	  //a setter method is needed for each reference of the componentType
      static void TRENTINO_STDCALL setFunc1Method(void* thisPtr, void* /*retVal*/, void* params[])
      {
         //first cast in correct targettype
         Trentino::Example::MyComponent* p = 
            static_cast<Trentino::Example::MyComponent*>(thisPtr);

         //all parameters are pointers pointers which must be dereferenced to a normal pointer to object
         p->setFunc1(*reinterpret_cast<Trentino::Example::ReferenceExample**>(params[0]));
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
         if(strcmp(castInto, "Trentino::Example::ServiceA") == 0)
         {
            return static_cast<Trentino::Example::ServiceA*>
               (static_cast<Trentino::Example::MyComponent*>(thisPtr));
         }
         //ok by string compare, we must first cast basic void* into derived class pointer and
         //cast it into specified baseclass "Trentino::Example::ServiceB" to get correct offset 
         //of class pointer
         else if(strcmp(castInto, "Trentino::Example::ServiceB") == 0)
         {
            return static_cast<Trentino::Example::ServiceB*>
               (static_cast<Trentino::Example::MyComponent*>(thisPtr));
         }

         //no conversion found, pass through
         return thisPtr;
      }


      //construction
   public:
      InitializerTrentino_Example_MyComponentRflx()
      {
         //delete parameter
         //struct is necessary to find correct parameterlist by runtime
         static const Trentino::Reflection::Data::Method::Param deleteParamMyComponent[] = {
            "Trentino::Example::MyComponent*"
         };

         //Parameterlist for Trentino::Example::ServiceA::setFunc1
		 //We have to set the parameters for each reference of compType
         static const Trentino::Reflection::Data::Method::Param setFunc1MethodParams[] = {
            "Trentino::Example::ReferenceExample*", //content of the reference/interface.cpp/@class 
         };

         //define all "public" functions seen by reflection runtime
         static Trentino::Reflection::Data::Method::MetaData mdmMyComponent[] = {
            //register here Trentino::Example::ServiceA::setFunc1
			 //for each reference of componentType we need an entry here
            { "setFunc1", nullptr, setFunc1MethodParams, COUNT_OF(setFunc1MethodParams), setFunc1Method },
            //word "new" is reserved and can be overloaded with parameter constructors, will be
            //called by ReflectObject::newInstance
            { "new", "Trentino::Example::MyComponent*", nullptr, 0, newObjectNoParam },
            //word "delete" is reserved for destroying object and will be called by 
            //ReflectObject::deleteInstance or ReflectObject::deleteRegisteredInstance
            { "delete", nullptr, deleteParamMyComponent, COUNT_OF(deleteParamMyComponent), deleteObject },
         };

         //register whole object
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "Trentino::Example::MyComponent", //content of @header of the implementation.cpp
            castCallMyComponent,  //cast call function callback
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

      ~InitializerTrentino_Example_MyComponentRflx()
      {
         //Important: don´t forget to unregister, rflx dlls can be unloaded!
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   };//class InitializerTrentino_Example_ServiceImplRflx

   //! must be instantiated! naming of static variable should be unique here in this cpp file
   static InitializerTrentino_Example_MyComponentRflx init1;


   //*************************************************************************************************
   //class declaration
   //InitializerTrentinoNamespace_SCAReferenceExampleImplRflx
   //*************************************************************************************************
   class InitializerTrentinoNamespace_SCAReferenceExampleImplRflx
   {
      //! This is the new callback to create MyComponent, retVal is a pointer of pointer which contains
      //! the address of object
      static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
      {
         *reinterpret_cast<TrentinoNamespace::SCAReferenceExampleImpl**>(retVal) = 
            new TrentinoNamespace::SCAReferenceExampleImpl();
      }

      //! you need only thisPtr and a simple static_cast to destroy object by default delete
      static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
      {
         TrentinoNamespace::SCAReferenceExampleImpl* p = 
            static_cast<TrentinoNamespace::SCAReferenceExampleImpl*>(thisPtr);
         delete p;
      }

      static void TRENTINO_STDCALL setProperty1(void* thisPtr, void* /*retVal*/, void* params[])
      {
         //first cast in correct targettype
         TrentinoNamespace::SCAReferenceExampleImpl* p = 
            static_cast<TrentinoNamespace::SCAReferenceExampleImpl*>(thisPtr);

         //all parameters are pointers pointers which must be dereferenced to a normal pointer to object
         p->setProperty1(*reinterpret_cast<int*>(params[0]));
      }

      static void TRENTINO_STDCALL setProperty2(void* thisPtr, void* /*retVal*/, void* params[])
      {
         //first cast in correct targettype
         TrentinoNamespace::SCAReferenceExampleImpl* p = 
            static_cast<TrentinoNamespace::SCAReferenceExampleImpl*>(thisPtr);

         //all parameters are pointers pointers which must be dereferenced to a normal pointer to object
         //! \todo: using std objects as parameters?
         p->setProperty2(*reinterpret_cast<std::string*>(params[0]));
      }

      static void TRENTINO_STDCALL setProperty3(void* thisPtr, void* /*retVal*/, void* params[])
      {
         //first cast in correct targettype
         TrentinoNamespace::SCAReferenceExampleImpl* p = 
            static_cast<TrentinoNamespace::SCAReferenceExampleImpl*>(thisPtr);

         //all parameters are pointers pointers which must be dereferenced to a normal pointer to object
         p->setProperty3(*reinterpret_cast<bool*>(params[0]));
      }

      static void TRENTINO_STDCALL setMultiProperty(void* thisPtr, void* /*retVal*/, void* params[])
      {
         //first cast in correct targettype
         TrentinoNamespace::SCAReferenceExampleImpl* p = 
            static_cast<TrentinoNamespace::SCAReferenceExampleImpl*>(thisPtr);

         //all parameters are pointers pointers which must be dereferenced to a normal pointer to object
         //! \todo: using std objects as parameters?
         p->setMultiProperty(*reinterpret_cast< std::list< std::string >* >(params[0]));
      }

      static void TRENTINO_STDCALL setValueFileProperty(void* thisPtr, void* /*retVal*/, void* params[])
      {
         //first cast in correct targettype
         TrentinoNamespace::SCAReferenceExampleImpl* p = 
            static_cast<TrentinoNamespace::SCAReferenceExampleImpl*>(thisPtr);

         //all parameters are pointers pointers which must be dereferenced to a normal pointer to object
         p->setValueFileProperty(*reinterpret_cast<int*>(params[0]));
      }


      //construction
   public:
      InitializerTrentinoNamespace_SCAReferenceExampleImplRflx()
      {
         //delete parameter
         //struct is necessary to find correct parameterlist by runtime
         static const Trentino::Reflection::Data::Method::Param deleteParamSCAReferenceExampleImpl[] = {
            "TrentinoNamespace::SCAReferenceExampleImpl*"
         };

         static const Trentino::Reflection::Data::Method::Param setProperty1Param[] = {
            "int"
         };
         static const Trentino::Reflection::Data::Method::Param setProperty2Param[] = {
            "std::string"
         };
         static const Trentino::Reflection::Data::Method::Param setProperty3Param[] = {
            "bool"
         };
         static const Trentino::Reflection::Data::Method::Param setMultiPropertyParam[] = {
            "std::list<std::string>>"
         };
         static const Trentino::Reflection::Data::Method::Param setValueFilePropertyParam[] = {
            "int"
         };


         //define all "public" functions seen by reflection runtime
         static Trentino::Reflection::Data::Method::MetaData mdm[] = {
            { "Property1", nullptr, setProperty1Param, COUNT_OF(setProperty1Param), setProperty1 },
            { "Property2", nullptr, setProperty2Param, COUNT_OF(setProperty2Param), setProperty2 },
            { "Property3", nullptr, setProperty3Param, COUNT_OF(setProperty3Param), setProperty3 },
            { "MultiProperty", nullptr, setMultiPropertyParam, COUNT_OF(setMultiPropertyParam), setMultiProperty },
            { "ValueFileProperty", nullptr, setValueFilePropertyParam, COUNT_OF(setValueFilePropertyParam), setValueFileProperty },
            //word "new" is reserved and can be overloaded with parameter constructors, will be
            //called by ReflectObject::newInstance
            { "new", "TrentinoNamespace::SCAReferenceExampleImpl*", nullptr, 0, newObjectNoParam },
            //word "delete" is reserved for destroying object and will be called by 
            //ReflectObject::deleteInstance or ReflectObject::deleteRegisteredInstance
            { "delete", nullptr, deleteParamSCAReferenceExampleImpl, 
               COUNT_OF(deleteParamSCAReferenceExampleImpl), deleteObject },
         };

         //register whole object
         static Trentino::Reflection::Data::Object::MetaData mdo = { 
            "TrentinoNamespace::SCAReferenceExampleImpl", //name of component
            nullptr,  //cast call function callback, currently not neccessary here
            nullptr, //we still don´t support native properties
            0, //so count of properties are 0 (for Trentino it is default!)
            mdm, //ok register here my methodlist, incl. new and delete functions
            COUNT_OF(mdm), //number of functions
         };

         // store it in initializer class to unregister it by destructor
         mmdoHandle = &mdo;

         //register class in reflection runtime
         Trentino::Reflection::Registration::registerMetaData(mmdoHandle);
      }

      ~InitializerTrentinoNamespace_SCAReferenceExampleImplRflx()
      {
         //Important: don´t forget to unregister, rflx dlls can be unloaded!
         Trentino::Reflection::Registration::unregisterMetaData(mmdoHandle);
      }

      //data
   private:
      Trentino::Reflection::Data::Object::MetaData* mmdoHandle;

   };//class InitializerTrentinoNamespace_SCAReferenceExampleImplRflx

}//namespace Gen
}//namespace Trentino