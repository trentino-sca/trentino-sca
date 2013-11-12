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

// This is one of a generated class sample 

//specific
#include "./../../Global/TrentinoGlobal.h"

#include "TrentinoTestsReflectionTestClass.h"
#include "./../../Utils/TrentinoUtilsTypeName.h"
#include "./../../Runtime/ReflectionRuntime/TrentinoReflectionRegistration.h"
#include "./../../Runtime/ReflectionRuntime/TrentinoReflectionHelpersListWrapper.h"
#include "./../../Runtime/ReflectionRuntime/TrentinoReflectionDataRegistry.h"

using namespace Trentino::Reflection;
using namespace Trentino::Reflection::Helpers;
using namespace Trentino::Reflection::Data;
using namespace Trentino::Tests::Reflection;
using Trentino::Utils::TypeName;
using namespace std;

//class declaration
class InitializerTestClass
{
public:   
   //access2IntBool
   static void TRENTINO_STDCALL access2IntBoolInvokeMethod(void* thisPtr, void* /*retVal*/, void* params[])
   {
      TestClass* p = static_cast<TestClass*>(thisPtr);
      p->access2(*reinterpret_cast<int*>(params[0]), *reinterpret_cast<bool*>(params[1]));
   }

   static void TRENTINO_STDCALL access2FloatBoolInvokeMethod(void* thisPtr, void* /*retVal*/, void* params[])
   {
      TestClass* p = static_cast<TestClass*>(thisPtr);
      p->access2(*reinterpret_cast<float*>(params[0]), *reinterpret_cast<bool*>(params[1]));
   }

   static void TRENTINO_STDCALL access2FloatInvokeMethod(void* thisPtr, void* /*retVal*/, void* params[])
   {
      TestClass* p = static_cast<TestClass*>(thisPtr);
      p->access2(*reinterpret_cast<float*>(params[0]));
   }

   //doMultiply
   static void TRENTINO_STDCALL doSomethingInvokeMethod(void* thisPtr, void* retVal, void* params[])
   {
      TestClass* p = static_cast<TestClass*>(thisPtr);
      double result = 
         p->doMultiply(*reinterpret_cast<float*>(params[0]), *reinterpret_cast<float*>(params[1]));

      *reinterpret_cast<double*>(retVal) = result;
   }

   // Gobal new operator called for TestClass
   static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
   {
      *reinterpret_cast<TestClass**>(retVal) = new TestClass();
   }

   static void TRENTINO_STDCALL newObject2Param(void* /*thisPtr*/, void* retVal, void* params[])
   {
      *reinterpret_cast<TestClass**>(retVal) = 
         new TestClass( *reinterpret_cast<unsigned long*>(params[0]),
                        *reinterpret_cast<InversionClass**>(params[1]));
   }

   // Gobal delete operator called for TestClass
   static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
   {
      TestClass* p = static_cast<TestClass*>(thisPtr);
      delete p;
   }

   //doMultiply
   static void TRENTINO_STDCALL setListsMethod(void* thisPtr, void* /*retVal*/, void* params[])
   {
      TestClass* p = static_cast<TestClass*>(thisPtr);
      
      list<string> param0; 
      expandToList(param0, *(*reinterpret_cast<ListType**>(params[0])));
      list< list<string> > param1;
      expandToList(param1, *(*reinterpret_cast<ListType**>(params[1])));
      list<unsigned long> param2;
      expandToList(param2, *(*reinterpret_cast<ListType**>(params[2])));
      list<char> param3;
      expandToList(param3, *(*reinterpret_cast<ListType**>(params[3])));

      p->setLists(param0, param1, param2, param3);
   }

   //construction
   InitializerTestClass()
   {
      // METHOD SIGNATURES
      static const Method::Param access2IntBoolParams[] = {
         { TypeName<int>::name() },
         { TypeName<bool>::name() },
      };
      static const Method::Param access2FloatBoolParams[] = {
         { TypeName<float>::name() },
         { TypeName<bool>::name() },
      };
      static const Method::Param access2FloatParams[] = {
         { TypeName<float>::name() },
      };


      static const Method::Param doMultiplyParams[] = {
         { TypeName<float>::name() },
         { TypeName<float>::name() },
      };

      static const Method::Param deleteParams[] = {
         { TypeName<TestClass*>::name() }
      };

      static const Method::Param newParams[] = {
         { TypeName<unsigned long>::name() },
         { TypeName<InversionClass*>::name() },
      };

      static const Method::Param listParams[] = {
         { TypeName< list<string> >::name() },
         { TypeName< list<list<string> > >::name() },
         { TypeName< list<unsigned long> >::name() },
         { TypeName< list<char> >::name() },
      };

      static Method::MetaData mdm[] = {
         { "access2", nullptr, access2IntBoolParams, COUNT_OF(access2IntBoolParams), access2IntBoolInvokeMethod },
         { "access2", nullptr, access2FloatBoolParams, COUNT_OF(access2FloatBoolParams), access2FloatBoolInvokeMethod },
         { "access2", nullptr, access2FloatParams, COUNT_OF(access2FloatParams), access2FloatInvokeMethod },
         { "doMultiply", TypeName<double>::name(), doMultiplyParams, COUNT_OF(doMultiplyParams), doSomethingInvokeMethod },
         { "new", TypeName<TestClass*>::name(), nullptr, 0, newObjectNoParam },
         { "delete", nullptr, deleteParams, COUNT_OF(deleteParams), deleteObject },
         { "new", TypeName<TestClass*>::name(), newParams, COUNT_OF(newParams), newObject2Param },
         { "setLists", nullptr, listParams, COUNT_OF(listParams), setListsMethod },
      };


      // OBJECT
      static Object::MetaData mdo = { 
         TypeName<TestClass>::name(), 
         nullptr,
         mdm,
         COUNT_OF(mdm),
      };
     
      // important to unregister!
      mmdoHandle = &mdo;
     
      Registration::registerMetaData(registry, *mmdoHandle);
   }

   ~InitializerTestClass()
   {
      Registration::unregisterMetaData(registry, *mmdoHandle);
   }
   //data
private:
   Object::MetaData* mmdoHandle;
   DataRegistry registry;
}; //class InitializerTestClass


static InitializerTestClass init;
