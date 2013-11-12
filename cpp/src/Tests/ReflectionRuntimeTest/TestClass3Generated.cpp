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
#include "./../../Runtime/ReflectionRuntime/TrentinoReflectionDataRegistry.h"

using namespace Trentino::Reflection;
using namespace Trentino::Reflection::Data;
using namespace Trentino::Tests::Reflection;
using Trentino::Utils::TypeName;

//class declaration
class InitializerTestClassMulitple
{
public:

   // Gobal new operator called for TestClass
   static void TRENTINO_STDCALL newObjectNoParamDerived1(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
   {
      *reinterpret_cast<TestClassMulitpleDerived1**>(retVal) = new TestClassMulitpleDerived1();
   }

   static void TRENTINO_STDCALL newObjectNoParamDerived2(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
   {
      *reinterpret_cast<TestClassMulitpleDerived2**>(retVal) = new TestClassMulitpleDerived2();
   }

   static void TRENTINO_STDCALL deleteObjectDerived1(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
   {
      TestClassMulitpleDerived1* p = static_cast<TestClassMulitpleDerived1*>(thisPtr);
      delete p;
   }

   static void TRENTINO_STDCALL deleteObjectDerived2(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
   {
      TestClassMulitpleDerived2* p = static_cast<TestClassMulitpleDerived2*>(thisPtr);
      delete p;
   }

   static void* TRENTINO_STDCALL castCallDerived1 (void* thisPtr, const char* castInto)
   {
      if(strcmp(castInto, "Trentino::Tests::Reflection::TestBaseClassSuper") == 0)
      {
         return static_cast<TestBaseClassSuper*>(static_cast<TestClassMulitpleDerived1*>(thisPtr));
      }
      else if(strcmp(castInto, "Trentino::Tests::Reflection::TestBaseClassA") == 0)
      {
         return static_cast<TestBaseClassA*>(static_cast<TestClassMulitpleDerived1*>(thisPtr));
      }
      else if(strcmp(castInto, "Trentino::Tests::Reflection::TestBaseClassB") == 0)
      {
         return static_cast<TestBaseClassB*>(static_cast<TestClassMulitpleDerived1*>(thisPtr));
      }

      return thisPtr;
   }

   static void* TRENTINO_STDCALL castCallDerived2 (void* thisPtr, const char* castInto)
   {
      if(strcmp(castInto, "Trentino::Tests::Reflection::TestBaseClassSuper") == 0)
      {
         return static_cast<TestBaseClassSuper*>(static_cast<TestClassMulitpleDerived2*>(thisPtr));
      }
      else if(strcmp(castInto, "Trentino::Tests::Reflection::TestBaseClassB") == 0)
      {
         return static_cast<TestBaseClassB*>(static_cast<TestClassMulitpleDerived2*>(thisPtr));
      }

      return thisPtr;
   }


   //construction
   InitializerTestClassMulitple()
   {
      // delete parameter
      static const Method::Param deleteParamDerived1[] = {
         { TypeName<TestClassMulitpleDerived1*>::name() }
      };
      static const Method::Param deleteParamDerived2[] = {
         { TypeName<TestClassMulitpleDerived2*>::name() }
      };

      static Method::MetaData mdmDerived1[] = {
         { "new", TypeName<TestClassMulitpleDerived1*>::name(), nullptr, 0, newObjectNoParamDerived1 },
         { "delete", nullptr, deleteParamDerived1, COUNT_OF(deleteParamDerived1), deleteObjectDerived1 },
      };

      static Method::MetaData mdmDerived2[] = {
         { "new", TypeName<TestClassMulitpleDerived2*>::name(), nullptr, 0, newObjectNoParamDerived2 },
         { "delete", nullptr, deleteParamDerived2, COUNT_OF(deleteParamDerived2), deleteObjectDerived2 },
      };

      // OBJECT
      static Object::MetaData mdoDerived1 = { 
         TypeName<TestClassMulitpleDerived1>::name(), 
         castCallDerived1,
         mdmDerived1,
         COUNT_OF(mdmDerived1),
      };

      static Object::MetaData mdoDerived2 = { 
         TypeName<TestClassMulitpleDerived2>::name(), 
         castCallDerived2,
         mdmDerived2,
         COUNT_OF(mdmDerived2),
      };

      // important to unregister!
      mmdoHandleDerived1 = &mdoDerived1;
      Registration::registerMetaData(registry,*mmdoHandleDerived1);

      mmdoHandleDerived2 = &mdoDerived2;
      Registration::registerMetaData(registry,*mmdoHandleDerived2);
   }

   ~InitializerTestClassMulitple()
   {
      Registration::unregisterMetaData(registry,*mmdoHandleDerived1);
      Registration::unregisterMetaData(registry,*mmdoHandleDerived2);
   }

   //data
private:
   Object::MetaData* mmdoHandleDerived1;
   Object::MetaData* mmdoHandleDerived2;
   DataRegistry registry;

};//class InitializerTestClass

static InitializerTestClassMulitple init;
