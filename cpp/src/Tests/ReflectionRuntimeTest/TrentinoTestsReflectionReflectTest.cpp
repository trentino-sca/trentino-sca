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

// header
#include "TrentinoTestsReflectionReflectTest.h"

//standard
#include <string>
#include <list>
#include <vector>
#include <boost/smart_ptr/scoped_ptr.hpp>

//specific
#include "TestClass2Generated.h"
#include "./../../Runtime/ReflectionRuntime/TrentinoReflectionDataRegistry.h"
#include "./../../Runtime/ReflectionRuntime/TrentinoReflectionReflectObject.h"
#include "./../../Runtime/ReflectionRuntime/TrentinoReflectionReflectMethod.h"
#include "./../../Runtime/ReflectionRuntime/TrentinoReflectionHelpersListWrapper.h"
#include "./../../Utils/TrentinoUtilsTypeName.h"
#include "TrentinoTestsReflectionTestClass.h"

using namespace std;
using namespace Trentino::Tests::Reflection;
using namespace Trentino::Reflection::Helpers;
using namespace Trentino::Reflection;
using Trentino::Utils::TypeName;


namespace
{
   const string TestClassNameDerived1 = "Trentino::Tests::Reflection::TestClassMulitpleDerived1";
   const string TestClassNameDerived2 = "Trentino::Tests::Reflection::TestClassMulitpleDerived2";
   const string TestClassName = "Trentino::Tests::Reflection::TestClass";
   const string TestClassBaseName = "Trentino::Tests::Reflection::TestClassBase";
   const string TestClassName2 = "Trentino::Tests::Reflection::Registration::TestClass2";
   const string Access2MethodName = "access2";      
   const string AccessPropertyUnsignedLongName = "mAccessPropertyUnsignedLong";
   const string DoMultiplyMethodName = "doMultiply";
   const string NewMethodName = "new";
   const unsigned long C00lD00dValue = 0xc001d00d;
   const unsigned long DeadCodeValue = 0xdeadc0de;
   const unsigned long C0deBabeValue = 0xc0debabe;

   const int Access2MethodCount = 3;   
   const int MethodCountTestClass = 8;
   DataRegistry reg;
} //namespace

// class declaration
// Accessorclass to get data information from internal ReflectObject class
//class ReflectObjectMDataAccessor : public ReflectObject
//{
//public:
//   ReflectObjectMDataAccessor(){}
//   const Data::Object::MetaData& data() const { return mData; }
//};

TEST_F(ReflectTest,objectRegistrationTest)
{
   //currently one registered
   ASSERT_EQ(3, reg.reflectObjectCount());

   //ReflectObjectPtr foundObjTestClass = reg.reflectObjectAt(2);
   ReflectObjectPtr foundObjTestClass = reg.queryReflectObject(TestClassName);
   ASSERT_TRUE(foundObjTestClass.get() != nullptr);
   ASSERT_EQ(TestClassName, string(foundObjTestClass->className()));
   //query (without having info about it)
   ReflectObjectPtr queryObjTestClass = reg.queryReflectObject(TestClassName);
   ASSERT_TRUE(queryObjTestClass.get() != nullptr);
   //should be the correct name
   ASSERT_EQ(TestClassName, string(queryObjTestClass->className()));

   // register a second one manual to test registration ability
   TestClass2Initializer::registerManualTestClass2();
   ASSERT_EQ(4, reg.reflectObjectCount());
   //ReflectObjectPtr foundObjTestClass2 = reg.reflectObjectAt(3);
   ReflectObjectPtr foundObjTestClass2 = reg.queryReflectObject(TestClassName2);
   ASSERT_TRUE(foundObjTestClass2.get() != nullptr);
   ASSERT_EQ(TestClassName2, string(foundObjTestClass2->className()));
   ReflectObjectPtr queryObjTestClass2 = reg.queryReflectObject(TestClassName2);
   ASSERT_TRUE(queryObjTestClass2.get() != nullptr);
   //should be the correct name
   ASSERT_EQ(TestClassName2, string(queryObjTestClass2->className()));

   //unregister
   TestClass2Initializer::unregisterManualTestClass2();
   ASSERT_EQ(3, reg.reflectObjectCount());
   //ReflectObjectPtr foundObjTestClass2NotFound = reg.reflectObjectAt(3);
   ReflectObjectPtr foundObjTestClass2NotFound = reg.queryReflectObject(TestClassName2);
   ASSERT_TRUE(foundObjTestClass2NotFound.get() == nullptr);
   ReflectObjectPtr queryObjTestClass2NotFound = reg.queryReflectObject(TestClassName2);
   ASSERT_TRUE(queryObjTestClass2NotFound.get() == nullptr);
}


TEST_F(ReflectTest,reflectObjectTest)
{
   
   //currently one registered
   {
      ASSERT_EQ(3, reg.reflectObjectCount());
   }

   ReflectObjectPtr objTestClass = reg.queryReflectObject(TestClassName);
   ASSERT_TRUE(objTestClass.get() != nullptr);

   //classname and superclassname
   {
      ASSERT_STREQ(TestClassName.c_str(), objTestClass->className());
   }   

   //methodCount and methodAt
   {
      ASSERT_EQ(MethodCountTestClass, objTestClass->methodCount());
      int imeth = MethodCountTestClass;
      while(imeth--)
      {
         ASSERT_TRUE(objTestClass->methodAt(imeth).get() != nullptr);
      }
   }

   //queryMethods
   {
      std::vector<ReflectMethodPtr> methodList;
      objTestClass->queryMethods(Access2MethodName, methodList);
      ASSERT_EQ(Access2MethodCount, static_cast<int>(methodList.size()));
      int iMListCount = Access2MethodCount;
      while(iMListCount--)
      {
         ASSERT_TRUE(methodList[iMListCount].get() != nullptr);
         ASSERT_STREQ(Access2MethodName.c_str(), methodList[iMListCount]->name());
      }
   }

   //queryMethod
   {
      vector<string> accessmethodParam1;
      accessmethodParam1.push_back(TypeName<int>::name());
      accessmethodParam1.push_back(TypeName<bool>::name());
      ReflectMethodPtr foundAccess2 = 
         objTestClass->queryMethod(Access2MethodName, accessmethodParam1);
      ASSERT_TRUE(foundAccess2.get() != nullptr);
      const int paramsCount = 2;
      ASSERT_EQ(paramsCount, foundAccess2->paramsCount());
   }

   //newInstance (default constructor)
   {
      void* newInstance = objTestClass->newInstance(reg);
      //ok we do it here in a dirty way: we know the class hasn´t any vtable, startaddress is
      //set by defaultconstructor and TestClassBase::mStartValue has 0xc001d00d value
      unsigned long checkValue = *reinterpret_cast<unsigned long*>(newInstance);
      const unsigned long startVal = C00lD00dValue;
      ASSERT_EQ(startVal, checkValue);
      //InitializationCounter should be 1
      ASSERT_EQ(1, TestClass::mInitializationCounter);
      ASSERT_EQ(0, TestClass::mDeinitializationCounter);
      objTestClass->deleteInstance(reg,newInstance);
      ASSERT_EQ(1, TestClass::mInitializationCounter);
      ASSERT_EQ(1, TestClass::mDeinitializationCounter);
   }

   //newInstance (registerInstance)
   {
      void* newInstance = objTestClass->newInstance(reg,true);

      ASSERT_EQ(2, TestClass::mInitializationCounter);
      ASSERT_EQ(1, TestClass::mDeinitializationCounter);

      ReflectObjectPtr foundObject = 
         reg.queryReflectObjectByInstance(newInstance);
      ASSERT_TRUE(foundObject.get() != nullptr);

      // do this to get internal information about mData of ReflectObject
      //ReflectObjectMDataAccessor* cmp1 = 
      //   static_cast<ReflectObjectMDataAccessor*>(foundObject.get());
      //ReflectObjectMDataAccessor* cmp2 = 
      //   static_cast<ReflectObjectMDataAccessor*>(objTestClass.get());
      ASSERT_TRUE(foundObject->data().className ==  objTestClass->data().className );

      objTestClass->deleteInstance(reg,newInstance, true);

      ReflectObjectPtr noFoundObject = 
         reg.queryReflectObjectByInstance(newInstance);
      ASSERT_TRUE(noFoundObject.get() == nullptr);

      ASSERT_EQ(2, TestClass::mInitializationCounter);
      ASSERT_EQ(2, TestClass::mDeinitializationCounter);
   }

   //newInstance (deleteRegisteredInstance)
   {
      void* newInstance = objTestClass->newInstance(reg,true);

      ASSERT_EQ(3, TestClass::mInitializationCounter);
      ASSERT_EQ(2, TestClass::mDeinitializationCounter);

      bool result = ReflectObject::deleteRegisteredInstance(reg,newInstance);
      ASSERT_EQ(true, result);

      ASSERT_EQ(3, TestClass::mInitializationCounter);
      ASSERT_EQ(3, TestClass::mDeinitializationCounter);
   }
}

TEST_F(ReflectTest,reflectMethodTest)
{

   //currently one registered
   {
      ASSERT_EQ(3, reg.reflectObjectCount());
   }

   ReflectObjectPtr objTestClass = reg.queryReflectObject(TestClassName);
   ASSERT_TRUE(objTestClass.get() != nullptr);

   void* newInstance = objTestClass->newInstance(reg);
   ASSERT_TRUE(newInstance != nullptr);
   //safety
   ASSERT_EQ(4, TestClass::mInitializationCounter);
   ASSERT_EQ(3, TestClass::mDeinitializationCounter);

   //retrieve doMultiply method
   //construct params
   vector<string> paramsMultiply;
   paramsMultiply.push_back(TypeName<float>::name());
   paramsMultiply.push_back(TypeName<float>::name());
   
   //check query, name, returntype, size of params and type of params
   ReflectMethodPtr methodMultiply = objTestClass->queryMethod(DoMultiplyMethodName, paramsMultiply);
   ASSERT_TRUE(methodMultiply.get() != nullptr);
   ASSERT_STREQ(DoMultiplyMethodName.c_str(), methodMultiply->name());
   ASSERT_STREQ(TypeName<double>::name(), methodMultiply->returnType());
   ASSERT_EQ(static_cast<int>(paramsMultiply.size()), methodMultiply->paramsCount());
   int paramsCount = methodMultiply->paramsCount();
   ASSERT_TRUE(paramsCount > 0);
   while(paramsCount--)
   {
      ASSERT_TRUE(0 == strcmp(paramsMultiply[paramsCount].c_str(), methodMultiply->paramsAt(paramsCount)->type));
   }

   //doMultiply, invoke and return value
   {
      vector<Variant> paramValuesVariant;
      paramValuesVariant.push_back(Variant(5.0f));
      paramValuesVariant.push_back(Variant(5.0f));
      Variant resultDouble1 = methodMultiply->invoke(newInstance, paramValuesVariant);
      ASSERT_EQ(Variant::Double, resultDouble1.type());
      ASSERT_EQ(25.0, resultDouble1.toDouble());

      float valFloat = 6.0f;
      float* paramValues[] = {&valFloat, &valFloat};
      Variant resultDouble2 = methodMultiply->invoke(newInstance, (void**)paramValues);
      ASSERT_EQ(Variant::Double, resultDouble2.type());
      ASSERT_EQ(36.0, resultDouble2.toDouble());

   }

   {
      vector<string> paramsAccess21;
      paramsAccess21.push_back(TypeName<float>::name());
      paramsAccess21.push_back(TypeName<bool>::name());
      ReflectMethodPtr access21 = objTestClass->queryMethod(Access2MethodName, paramsAccess21);
      ASSERT_STREQ(Access2MethodName.c_str(), access21->name());
      ASSERT_EQ(static_cast<int>(paramsAccess21.size()), access21->paramsCount());
      vector<string> paramsAccess22;
      paramsAccess22.push_back(TypeName<float>::name());
      ReflectMethodPtr access22 = objTestClass->queryMethod(Access2MethodName, paramsAccess22);
      ASSERT_STREQ(Access2MethodName.c_str(), access22->name());
      ASSERT_EQ(static_cast<int>(paramsAccess22.size()), access22->paramsCount());

      //check if initial value is set
      TestClass* testClass = static_cast<TestClass*>(newInstance);
      ASSERT_EQ(DeadCodeValue, testClass->mAccessPropertyUnsignedLong);
      float valFloat = 6.0f;
      bool valBool = false;
      void* paramValues1[] = {&valFloat, &valBool};
      Variant result1 = access21->invoke(newInstance, (void**)paramValues1);
      ASSERT_EQ(Variant::Invalid, result1.type());
      ASSERT_EQ(C00lD00dValue, testClass->mAccessPropertyUnsignedLong);

      void* paramValues2[] = {&valFloat};
      Variant result2 = access22->invoke(newInstance, (void**)paramValues2);
      ASSERT_EQ(Variant::Invalid, result1.type());
      ASSERT_EQ(C0deBabeValue, testClass->mAccessPropertyUnsignedLong);

   }

   objTestClass->deleteInstance(reg,newInstance);
   //safety
   ASSERT_EQ(4, TestClass::mInitializationCounter);
   ASSERT_EQ(4, TestClass::mDeinitializationCounter);
}

TEST_F(ReflectTest,paramCtoTest)
{


   //currently one registered
   {
      ASSERT_EQ(3, reg.reflectObjectCount());
   }

   ReflectObjectPtr objTestClass = reg.queryReflectObject(TestClassName);
   ASSERT_TRUE(objTestClass.get() != nullptr);

   vector<string> paramsNew;
   paramsNew.push_back(TypeName<unsigned long>::name());
   paramsNew.push_back(TypeName<InversionClass*>::name());
   ReflectMethodPtr newMethod = objTestClass->queryMethod(NewMethodName, paramsNew);

   unsigned long valULong = C0deBabeValue;
   
   boost::scoped_ptr<InversionClass> invClass(new InversionClass);
   InversionClass* pVal = invClass.get();
   void* paramValues[] = {&valULong, &pVal};
   
   TestClass* newInstance = static_cast<TestClass*>(newMethod->invoke(nullptr, paramValues).toVoidPtr());

   //safety
   ASSERT_EQ(5, TestClass::mInitializationCounter);
   ASSERT_EQ(4, TestClass::mDeinitializationCounter);

   ASSERT_EQ(C0deBabeValue, newInstance->mAccessPropertyUnsignedLong);
   ASSERT_EQ(invClass.get(), newInstance->mInversionClass);

   objTestClass->deleteInstance(reg,newInstance);
   //safety
   ASSERT_EQ(5, TestClass::mInitializationCounter);
   ASSERT_EQ(5, TestClass::mDeinitializationCounter);
}


TEST_F(ReflectTest,newInstanceCalls)
{

   //currently one registered
   {
      ASSERT_EQ(3, reg.reflectObjectCount());
   }

   ReflectObjectPtr objTestClass = reg.queryReflectObject(TestClassName);
   ASSERT_TRUE(objTestClass.get() != nullptr);

   vector<string> paramsNew;
   paramsNew.push_back(TypeName<unsigned long>::name());
   paramsNew.push_back(TypeName<InversionClass*>::name());

   unsigned long valULong = C0deBabeValue;

   boost::scoped_ptr<InversionClass> invClass(new InversionClass);
   InversionClass* pVal = invClass.get();
   void* paramValues[] = {&valULong, &pVal};

   ASSERT_EQ(5, TestClass::mInitializationCounter);
   ASSERT_EQ(5, TestClass::mDeinitializationCounter);

   TestClass* newInstance = 
      static_cast<TestClass*>(objTestClass->newInstance(reg,paramsNew, paramValues));
   ASSERT_EQ(6, TestClass::mInitializationCounter);
   ASSERT_EQ(5, TestClass::mDeinitializationCounter);
   ASSERT_EQ(C0deBabeValue, newInstance->mAccessPropertyUnsignedLong);
   ASSERT_EQ(invClass.get(), newInstance->mInversionClass);

   vector<Variant> paramValuesVariant;
   paramValuesVariant.push_back(Variant(valULong));
   paramValuesVariant.push_back(Variant(pVal));


   TestClass* newInstance2 = 
      static_cast<TestClass*>(objTestClass->newInstance(reg, paramsNew, paramValuesVariant));
   ASSERT_EQ(7, TestClass::mInitializationCounter);
   ASSERT_EQ(5, TestClass::mDeinitializationCounter);
   ASSERT_EQ(C0deBabeValue, newInstance2->mAccessPropertyUnsignedLong);
   ASSERT_EQ(invClass.get(), newInstance2->mInversionClass);

   objTestClass->deleteInstance(reg,newInstance);
   ASSERT_EQ(7, TestClass::mInitializationCounter);
   ASSERT_EQ(6, TestClass::mDeinitializationCounter);

   objTestClass->deleteInstance(reg, newInstance2);
   ASSERT_EQ(7, TestClass::mInitializationCounter);
   ASSERT_EQ(7, TestClass::mDeinitializationCounter);
}

TEST_F(ReflectTest,reflectMulitpleInheritance)
{
   // check if cast operator isn´t supported
   ReflectObjectPtr objTestClass = reg.queryReflectObject(TestClassName);
   ASSERT_TRUE(objTestClass.get() != nullptr);
   {
      TestClass* newInstance = 
         static_cast<TestClass*>(objTestClass->newInstance(reg));

      //TestClass hasn´t any cast function, without registration
      TestClassBase* pTestObj = castCall<TestClassBase>(reg,newInstance);
      ASSERT_EQ((size_t)pTestObj, (size_t)newInstance);

      objTestClass->deleteInstance(reg,newInstance);
   }


   ReflectObjectPtr rflxObjDerived1 = reg.queryReflectObject(TestClassNameDerived1);
   ASSERT_TRUE(rflxObjDerived1.get() != nullptr);
   void* voidObj1 = rflxObjDerived1->newInstance(reg);
   TestClassMulitpleDerived1* obj1 = static_cast<TestClassMulitpleDerived1*>(voidObj1);
   //sanity check
   ASSERT_TRUE((size_t)voidObj1 == (size_t)obj1);

   //check correct initialization of object
   const string testBaseClassSuper = "TestBaseClassSuper";
   ASSERT_EQ(obj1->mValueSuper1, testBaseClassSuper);
   ASSERT_EQ(obj1->mValueSuper2, (int)0xc0debabe);
   ASSERT_EQ(obj1->mValueSuper3, 42.0f);
   ASSERT_EQ(obj1->mValueA1, (int)0xc001d00d);
   const string testBaseClassA = "TestBaseClassA";
   ASSERT_EQ(obj1->mValueA2, testBaseClassA);
   ASSERT_EQ(obj1->mValueB1, 0);
   ASSERT_EQ(obj1->mValueB2, string());

   {
      // check if correct cast
      TestBaseClassA* p1 = static_cast<TestBaseClassA*>
         (rflxObjDerived1->castCall(voidObj1, TypeName<TestBaseClassA>::name()));
      //correct cast
      TestBaseClassA* p1_1 = static_cast<TestBaseClassA*>(obj1);
      ASSERT_TRUE(p1 == p1_1);
      ASSERT_EQ(p1->mValueA1, (int)0xc001d00d);
      ASSERT_EQ(p1->mValueA2, testBaseClassA);
      p1->setData();
      const string  testBaseClassA_setData = "TestBaseClassA_setData";
      ASSERT_EQ(p1->mValueSuper1, testBaseClassA_setData);
      ASSERT_EQ(p1->mValueSuper2, 42);
      p1->setData2();

      const string testClassMulitpleDerived1_setData2 = "TestClassMulitpleDerived1::setData2";
      ASSERT_EQ(p1->mValueSuper1, testClassMulitpleDerived1_setData2);
      ASSERT_EQ(p1->mValueSuper2, -42);
      ASSERT_EQ(p1->mValueSuper3, 1.0f);
      ASSERT_EQ(p1->mValueA1, 0);
      ASSERT_EQ(p1->mValueA2, string());
   }

   const string setItTestClassMulitpleDerived1_setData = "setItTestClassMulitpleDerived1::setData";
   {
      TestBaseClassB* p2 = rflxObjDerived1->castCall<TestBaseClassB>(voidObj1);
      TestBaseClassB* p2_2 = static_cast<TestBaseClassB*>(obj1);
      ASSERT_TRUE(p2 == p2_2);
      ASSERT_EQ(p2->mValueB1, 42);
      const string testClassMulitpleDerived1_setData2 = "TestClassMulitpleDerived1::setData2";
      ASSERT_EQ(p2->mValueB2, testClassMulitpleDerived1_setData2);

      const string nothing = "setIt";
      p2->setData(1, nothing);

      ASSERT_EQ(p2->mValueB1, 1);
      ASSERT_EQ(p2->mValueB2, setItTestClassMulitpleDerived1_setData);
   }

   const string testBaseClassA_setData = "TestBaseClassA_setData";
   {
      TestBaseClassSuper* p3 = static_cast<TestBaseClassSuper*> 
         (ReflectObject::castCallRegistered(reg,voidObj1, TypeName<TestBaseClassSuper>::name()));
      TestBaseClassSuper* p3_3 = static_cast<TestBaseClassSuper*>(obj1);
      ASSERT_TRUE(p3 == p3_3);

      const string testClassMulitpleDerived1_setData2 = "TestClassMulitpleDerived1::setData2";
      ASSERT_EQ(p3->mValueSuper1, testClassMulitpleDerived1_setData2);
      ASSERT_EQ(p3->mValueSuper2, -42);
      p3->setData();
      ASSERT_EQ(p3->mValueSuper1, testBaseClassA_setData);
      ASSERT_EQ(p3->mValueSuper2, 42);
   }

   ASSERT_EQ(obj1->mValueSuper1, testBaseClassA_setData);
   ASSERT_EQ(obj1->mValueSuper2, 42);
   ASSERT_EQ(obj1->mValueSuper3, 1.0f);
   ASSERT_EQ(obj1->mValueA1, 0);
   ASSERT_EQ(obj1->mValueA2, string());
   ASSERT_EQ(obj1->mValueB1, 1);
   ASSERT_EQ(obj1->mValueB2, setItTestClassMulitpleDerived1_setData);

   rflxObjDerived1->deleteInstance(reg,obj1, true );

   ASSERT_EQ(TestClassMulitpleDerived1::mCalledVirtualDestructor_TestBaseClassSuper, 1);
   ASSERT_EQ(TestClassMulitpleDerived1::mCalledVirtualDestructor_TestBaseClassB, 1);
   ASSERT_EQ(TestClassMulitpleDerived1::mCalledVirtualDestructor_TestClassMulitpleDerived1, 1);


   ReflectObjectPtr rflxObjDerived2 = reg.queryReflectObject(TestClassNameDerived2);
   ASSERT_TRUE(rflxObjDerived2.get() != nullptr);
   void* voidObj2 = rflxObjDerived2->newInstance(reg);
   TestClassMulitpleDerived2* obj2 = static_cast<TestClassMulitpleDerived2*>(voidObj2);
   //sanity check
   ASSERT_TRUE((size_t)voidObj2 == (size_t)obj2);

   {
      TestBaseClassB* p4 = castCall<TestBaseClassB>(reg,voidObj2);
      TestBaseClassB* p4_4 = static_cast<TestBaseClassB*>(obj2);
      ASSERT_TRUE(p4 == p4_4);
      TestBaseClassSuper* p5 = castCall<TestBaseClassSuper>(reg,voidObj2);
      TestBaseClassSuper* p5_5 = static_cast<TestBaseClassSuper*>(obj2);
      ASSERT_TRUE(p5 == p5_5);

      const string testClassMulitpleDerived2_TestClassMulitpleDerived2 = 
         "TestClassMulitpleDerived2::TestClassMulitpleDerived2";
      ASSERT_EQ(p4->mValueB1, 0);
      ASSERT_EQ(p4->mValueB2, testClassMulitpleDerived2_TestClassMulitpleDerived2);

      ASSERT_EQ(p5->mValueSuper1, testClassMulitpleDerived2_TestClassMulitpleDerived2);
      ASSERT_EQ(p5->mValueSuper2, -42);
      ASSERT_EQ(p5->mValueSuper3, 42.0f);

      const string nothing = "nothing";
      p4->setData(2, nothing);
      ASSERT_EQ(obj2->mValueB1, 0);
      ASSERT_EQ(obj2->mValueB2, testClassMulitpleDerived2_TestClassMulitpleDerived2);
      p5->setData();

      ASSERT_EQ(obj2->mValueB1, 42);

      const string testClassMulitpleDerived2_setData = "TestClassMulitpleDerived2::setData";
      ASSERT_EQ(p5->mValueSuper1, testClassMulitpleDerived2_setData);
      ASSERT_EQ(p5->mValueSuper3, -42.0f);
   }

   rflxObjDerived2->deleteInstance(reg,obj2, true);
   ASSERT_EQ(TestClassMulitpleDerived1::mCalledVirtualDestructor_TestBaseClassSuper, 2);
   ASSERT_EQ(TestClassMulitpleDerived1::mCalledVirtualDestructor_TestBaseClassB, 2);
   ASSERT_EQ(TestClassMulitpleDerived1::mCalledVirtualDestructor_TestClassMulitpleDerived1, 1);
}

TEST_F(ReflectTest,testInvokeMethodByCallingLists)
{

   ReflectObjectPtr objTestClass = reg.queryReflectObject(TestClassName);
   ASSERT_TRUE(objTestClass.get() != nullptr);

   TestClass* newInstance = static_cast<TestClass*> (objTestClass->newInstance(reg));
   ASSERT_TRUE(newInstance != nullptr);

   const string setListsMethodName = "setLists";
   vector<string> paramsSetLists;
   paramsSetLists.push_back(TypeName< list<string> >::name());
   paramsSetLists.push_back(TypeName< list< list<string> > >::name());
   paramsSetLists.push_back(TypeName< list<unsigned long> >::name());
   paramsSetLists.push_back(TypeName< list<char> >::name());
   ReflectMethodPtr setListMethod = objTestClass->queryMethod(setListsMethodName, paramsSetLists);
   ASSERT_TRUE(setListMethod.get() != nullptr);

   list<string> list0;
   list< list<string> > list1;
   list<unsigned long> list2;
   list<char> list3;

   //test it with raw pointers
   {
      list0.push_back("test1");
      list1.push_back(list0);
      list1.push_back(list0);
      list2.push_back(42U);
      list3.push_back(42);
      ListWrapper<list<string> > list0Wrapper(list0);
      ListWrapper<list< list<string> > > list1Wrapper(list1);
      ListWrapper<list<unsigned long> > list2Wrapper(list2);
      ListWrapper<list<char> > list3Wrapper(list3);
      void* ppPtr[] = 
      {
          list0Wrapper.listType().get() 
         ,list1Wrapper.listType().get()
         ,list2Wrapper.listType().get()
         ,list3Wrapper.listType().get()
      };
      
      //we must commit pointer to pointer -> 
      //! \todo better solution?
      void* paramValues[] = { &ppPtr[0], &ppPtr[1], &ppPtr[2], &ppPtr[3] };

      setListMethod->invoke(newInstance, paramValues);

      ASSERT_EQ(newInstance->mListOfStrings.size(), 1U);
      ASSERT_TRUE(*newInstance->mListOfStrings.begin() == string("test1"));
      
      ASSERT_EQ(newInstance->mListListOfStrings.size(), 2U);
      const list<string>& resultListList = *newInstance->mListListOfStrings.begin();
      //should be sufficient to test one element!
      ASSERT_TRUE(*resultListList.begin() == string("test1"));

      ASSERT_EQ(newInstance->mListOfULongs.size(), 1U);
      ASSERT_TRUE(*newInstance->mListOfULongs.begin() == 42U);
      
      ASSERT_EQ(newInstance->mListOfChars.size(), 1U);
      ASSERT_TRUE(*newInstance->mListOfChars.begin() == 42);
   }

   //test it with variant
   {
      list0.clear();
      list0.push_back("test2");
      list1.clear();
      list1.push_back(list0);
      list1.push_back(list0);
      list2.clear();
      list2.push_back(43U);
      list3.clear();
      list3.push_back(43);

      vector<Variant> paramValuesVariant;
      paramValuesVariant.push_back(Variant::fromList(list0));
      paramValuesVariant.push_back(Variant::fromList(list1));
      paramValuesVariant.push_back(Variant::fromList(list2));
      paramValuesVariant.push_back(Variant::fromList(list3));

      setListMethod->invoke(newInstance, paramValuesVariant);

      ASSERT_EQ(newInstance->mListOfStrings.size(), 1U);
      ASSERT_TRUE(*newInstance->mListOfStrings.begin() == string("test2"));

      ASSERT_EQ(newInstance->mListListOfStrings.size(), 2U);
      const list<string>& resultListList = *newInstance->mListListOfStrings.begin();
      //should be sufficient to test one element!
      ASSERT_TRUE(*resultListList.begin() == string("test2"));

      ASSERT_EQ(newInstance->mListOfULongs.size(), 1U);
      ASSERT_TRUE(*newInstance->mListOfULongs.begin() == 43U);

      ASSERT_EQ(newInstance->mListOfChars.size(), 1U);
      ASSERT_TRUE(*newInstance->mListOfChars.begin() == 43);

   }
}
