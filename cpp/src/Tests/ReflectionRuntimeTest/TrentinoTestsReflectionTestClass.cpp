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

//header
#include "TrentinoTestsReflectionTestClass.h"

using namespace Trentino::Tests::Reflection;
using namespace std;


//global functions
int TestClass::mInitializationCounter = 0;
int TestClass::mDeinitializationCounter = 0;
int TestBaseClassSuper::mCalledVirtualDestructor_TestBaseClassSuper = 0;
int TestClassMulitpleDerived1::mCalledVirtualDestructor_TestClassMulitpleDerived1 = 0;
int TestBaseClassB::mCalledVirtualDestructor_TestBaseClassB = 0;

//construction
InversionClass::InversionClass(void) : mValue1(0) 
{
   //does nothing here
}

TestClassBase::TestClassBase() : mStartValue(0xc001d00d)
{
   //does nothing here
}

TestClass::TestClass() : mAccessPropertyUnsignedLong(0xdeadc0de)
{
   ++mInitializationCounter;
   mInversionClass = nullptr;
}

TestClass::TestClass(unsigned long val1, InversionClass* val2)
{
   ++mInitializationCounter;
   mAccessPropertyUnsignedLong = val1;
   mInversionClass = val2;
}


TestClass::~TestClass()
{
   ++mDeinitializationCounter;
}

void TestClass::access2(int /*param1*/, bool /*param2*/)
{
}

void TestClass::access2(float /*param1*/, bool /*param2*/)
{
   mAccessPropertyUnsignedLong = 0xc001d00d;
}

void TestClass::access2(float /*param1*/)
{
   mAccessPropertyUnsignedLong = 0xc0debabe;
}

double TestClass::doMultiply(float val1, float val2)
{
   return val1 * val2;;
}

void TestClass::setLists( const std::list<std::string>& paramListString
   ,const std::list< std::list<std::string> >& paramListListString
   ,const std::list<unsigned long>& paramListULong
   ,const std::list<char>& paramListChar)
{
   mListOfStrings = paramListString;
   mListListOfStrings = paramListListString;
   mListOfULongs = paramListULong;
   mListOfChars = paramListChar;
}


//management
void TestClass::setInversionClass(InversionClass* inversionClass)
{
   mInversionClass = inversionClass;
}


//*************************************************************************************************
//                                     TestBaseClassSuper
//*************************************************************************************************
TestBaseClassSuper::TestBaseClassSuper()
{
   mValueSuper1 = "TestBaseClassSuper";
   mValueSuper2 = 0xc0debabe;
   mValueSuper3 = 42.0f;
    
}
TestBaseClassSuper::~TestBaseClassSuper()
{
   ++mCalledVirtualDestructor_TestBaseClassSuper;
}

void TestBaseClassSuper::setData()
{
   mValueSuper1 = "TestBaseClassSuper_setData";
   mValueSuper3 = 42.42f;
}

//*************************************************************************************************
//                                     TestBaseClassA
//*************************************************************************************************
TestBaseClassA::TestBaseClassA() : TestBaseClassSuper()
{
   mValueA1 = 0xc001d00d;
   mValueA2 = "TestBaseClassA";
}

TestBaseClassA::~TestBaseClassA()
{
}

void TestBaseClassA::setData()
{
   mValueSuper1 = "TestBaseClassA_setData";
   mValueSuper2 = 42;
}

void TestBaseClassA::setData2()
{
   mValueSuper1 = "TestBaseClassA_setData2";
   mValueSuper3 = 4242.42f;
}

//*************************************************************************************************
//                                     TestBaseClassB
//*************************************************************************************************
TestBaseClassB::TestBaseClassB()
{
   mValueB1 = 0;
   mValueB2 = string();
}

TestBaseClassB::~TestBaseClassB()
{
   ++mCalledVirtualDestructor_TestBaseClassB;
}

void TestBaseClassB::setData(int valueB1, const string& valueB2)
{
   mValueB1 = valueB1;
   mValueB2 = valueB2;
}

//*************************************************************************************************
//                                     TestClassMulitpleDerived1
//*************************************************************************************************
TestClassMulitpleDerived1::TestClassMulitpleDerived1() : TestBaseClassA(), TestBaseClassB()
{
}

TestClassMulitpleDerived1::~TestClassMulitpleDerived1()
{
   ++mCalledVirtualDestructor_TestClassMulitpleDerived1;
}

void TestClassMulitpleDerived1::setData2()
{
   mValueSuper1 = "TestClassMulitpleDerived1::setData2";
   mValueSuper2 = -42;
   mValueSuper3 = 1.0f;
   mValueA1 = 0;
   mValueA2 = string();
   mValueB1 = 42;
   mValueB2 = "TestClassMulitpleDerived1::setData2";
}

void TestClassMulitpleDerived1::setData(int valueB1, const std::string& valueB2)
{
   TestBaseClassB::setData(valueB1, valueB2 + "TestClassMulitpleDerived1::setData");
}

//*************************************************************************************************
//                                     TestClassMulitpleDerived2
//*************************************************************************************************
TestClassMulitpleDerived2::TestClassMulitpleDerived2() : TestBaseClassB(), TestBaseClassSuper()
{
   mValueB2 = "TestClassMulitpleDerived2::TestClassMulitpleDerived2";
   mValueSuper1 = "TestClassMulitpleDerived2::TestClassMulitpleDerived2";
   mValueSuper2 = -42;
}

TestClassMulitpleDerived2::~TestClassMulitpleDerived2()
{
}

void TestClassMulitpleDerived2::setData(int /*valueB1*/, const string& /*valueB2*/)
{
}

void TestClassMulitpleDerived2::setData()
{
   mValueB1 = 42;
   mValueSuper3 = -42.0f;
   mValueSuper1 = "TestClassMulitpleDerived2::setData";
}
