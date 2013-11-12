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
#include <gtest/gtest.h>

//specific
#include "./../../Runtime/Oasis/sca/RefCountingPointer.h"

using namespace std;
using namespace oasis::sca;

//Test objects class
class TestObject
{
public:
   //Test value
   int mTestValue;
   //Ref count
   int mRefCount;

   //construction
public:
   TestObject(int val ) : mTestValue(val), mRefCount(1) {}
   TestObject(const TestObject& obj) : mTestValue(obj.mTestValue ), mRefCount(1){}
   TestObject() : mTestValue(0), mRefCount(1){}

   //operators
public:
   TestObject& operator= (const TestObject& obj) { mTestValue = obj.mTestValue; return *this; }
   bool operator==(const TestObject& obj) const { return (obj.mTestValue == mTestValue ); }
   bool operator!=(const TestObject& obj) { return ( obj.mTestValue != mTestValue ); }
}; //class TestObject


void TrentinoFuncPtrAddRef(TestObject* aObj) { if(aObj != nullptr) ++aObj->mRefCount; }
void TrentinoFuncPtrReleaseRef(TestObject* aObj) { if(aObj != nullptr ) --aObj->mRefCount; }

void TrentinoFuncPtrAddRef(const TestObject* aObj) 
{ 
   if(aObj != nullptr) 
      ++((TestObject*)aObj)->mRefCount; 
}
void TrentinoFuncPtrReleaseRef(const TestObject* aObj) 
{ 
   if(aObj != nullptr ) 
      --((TestObject*)aObj)->mRefCount; }


TEST(RuntimeAPITest, RefCountingPointer)
{
   //test object
   TestObject testObject(42);
   TestObject testObject2(4242);

   {
      RefCountingPointer<TestObject> testPointer(&testObject);

      //post-checks
      EXPECT_NE(static_cast<TestObject*>(nullptr), testPointer.get());
      EXPECT_EQ(&testObject, testPointer.get());
      EXPECT_EQ(testObject.mTestValue, testPointer->mTestValue);
      EXPECT_EQ(testObject.mTestValue, (*testPointer).mTestValue);
      EXPECT_EQ(testObject.mRefCount, 2);

      EXPECT_EQ((void*)&testObject, (void*)testPointer);
      RefCountingPointer<TestObject> emptyPointer;
      EXPECT_EQ(true, !emptyPointer);
      EXPECT_EQ(false, !testPointer);

      //reset
      testPointer.reset();
      EXPECT_EQ(testObject.mRefCount, 1);

      //rereset
      testPointer.reset(&testObject);
      EXPECT_EQ(testObject.mRefCount, 2);
      EXPECT_EQ(42, testPointer->mTestValue);

      {
         // assignment
         RefCountingPointer<TestObject> newPtr(testPointer);
         EXPECT_EQ(testObject.mRefCount, 3);
         RefCountingPointer<TestObject> newPtr2;
         newPtr2 = testPointer;
         EXPECT_EQ(testObject.mRefCount, 4);
         RefCountingPointer<TestObject> newPtr4;
         newPtr4 = &testObject;
         EXPECT_EQ(testObject.mRefCount, 5);
      }
      EXPECT_EQ(testObject.mRefCount, 2);

      {
         //compare
         RefCountingPointer<TestObject> testPointerSame(&testObject);
         EXPECT_EQ(testObject.mRefCount, 3);
         RefCountingPointer<TestObject> testPointerOther(&testObject2);
         EXPECT_EQ(testObject2.mRefCount, 2);
         EXPECT_TRUE(testPointerSame == testPointer);
         EXPECT_FALSE(testPointerSame != testPointer);
         EXPECT_TRUE(testPointerSame == testPointer.get());
         EXPECT_FALSE(testPointerSame != testPointer.get());
         EXPECT_TRUE(testPointerSame.get() == testPointer);
         EXPECT_FALSE(testPointerSame.get() != testPointer);

         EXPECT_FALSE(testPointerOther == testPointer);
         EXPECT_TRUE(testPointerOther != testPointer);
         EXPECT_FALSE(testPointerOther == testPointer.get());
         EXPECT_TRUE(testPointerOther != testPointer.get());
         EXPECT_FALSE(testPointerOther.get() == testPointer);
         EXPECT_TRUE(testPointerOther.get() != testPointer);
      }
      EXPECT_EQ(testObject.mRefCount, 2);
      EXPECT_EQ(testObject2.mRefCount, 1);

      {
         //swap
         RefCountingPointer<TestObject> swapObj1(&testObject);
         EXPECT_EQ(testObject.mRefCount, 3);
         RefCountingPointer<TestObject> swapObj2;
         swap(swapObj1, swapObj2);
         EXPECT_EQ(static_cast<TestObject*>(nullptr), swapObj1);
         EXPECT_NE(static_cast<TestObject*>(nullptr), swapObj2);
         EXPECT_EQ(testObject.mRefCount, 3);
      }
      EXPECT_EQ(testObject.mRefCount, 2);

      // \todo senseless
      RefCountingPointer<const TestObject> newConstPtr = constCast<const TestObject>(testPointer);
      RefCountingPointer<TestObject> newReinterpretPtr = reinterpretCast<TestObject>(testPointer);
      RefCountingPointer<TestObject> newStaticPtr = staticCast<TestObject>(testPointer);
      RefCountingPointer<TestObject> newDynamicPtr = dynamicCast<TestObject>(testPointer);
      EXPECT_EQ(testObject.mRefCount, 6);


   }

   //post-checks
   EXPECT_EQ(1, testObject.mRefCount);



}
