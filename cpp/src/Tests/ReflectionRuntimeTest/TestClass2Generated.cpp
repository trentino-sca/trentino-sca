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

//header
#include "TestClass2Generated.h"

//standard
#include <boost/smart_ptr/shared_ptr.hpp>

//specific
#include "./../../Global/TrentinoGlobal.h"
#include "TrentinoTestsReflectionRegistrationTestClass2.h"
#include "./../../Utils/TrentinoUtilsTypeName.h"
#include "./../../Runtime/ReflectionRuntime/TrentinoReflectionRegistration.h"
#include "./../../Runtime/ReflectionRuntime/TrentinoReflectionDataRegistry.h"

using namespace Trentino::Reflection;
using namespace Trentino::Reflection::Data;
using namespace Trentino::Tests::Reflection::Registration;
using Trentino::Utils::TypeName;

//class declaration
class InitializerTestClass2
{
   // Global new operator called for TestClass
   static void TRENTINO_STDCALL newObjectNoParam(void* /*thisPtr*/, void* retVal, void** /*params[]*/)
   {
      *reinterpret_cast<TestClass2**>(retVal) = new TestClass2();
   }

   // Global delete operator called for TestClass
   static void TRENTINO_STDCALL deleteObject(void* thisPtr, void* /*retVal*/, void** /*params[]*/)
   {
      TestClass2* p = static_cast<TestClass2*>(thisPtr);
      delete p;
   }


   //construction
public:
   InitializerTestClass2()
   {

      // delete parameter
      static const Method::Param deleteParam[] = {
         { TypeName<TestClass2*>::name() }
      };

      static Method::MetaData mdm[] = {
         { "new", TypeName<TestClass2*>::name(), nullptr, 0, newObjectNoParam },
         { "delete", nullptr, deleteParam, COUNT_OF(deleteParam), deleteObject },
      };

      // OBJECT
      static Object::MetaData mdo = { 
         TypeName<TestClass2>::name(), 
         nullptr, 
         mdm,
         COUNT_OF(mdm),
      };

      // important to unregister!
      mmdoHandle = &mdo;

      Registration::registerMetaData(registry,*mmdoHandle);
   }

   ~InitializerTestClass2()
   {
      Registration::unregisterMetaData(registry,*mmdoHandle);
   }

   //data
private:
   Object::MetaData* mmdoHandle;
   DataRegistry registry;

}; //class InitializerTestClass2

static boost::shared_ptr<InitializerTestClass2> init;

void TestClass2Initializer::registerManualTestClass2()
{
   init.reset(new InitializerTestClass2);
}

void TestClass2Initializer::unregisterManualTestClass2()
{
   init.reset();
}

