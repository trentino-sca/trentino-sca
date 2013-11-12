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
#include "TrentinoTestsReflectionHelpersTest.h"

// standard
#include <boost/smart_ptr/scoped_ptr.hpp>
#include <list>

//specific
#include "./../../Runtime/ReflectionRuntime/TrentinoReflectionHelpersVariant.h"
#include "./../../Runtime/ReflectionRuntime/TrentinoReflectionHelpersListWrapper.h"
#include "./../../Runtime/ReflectionRuntime/TrentinoReflectionHelpersDefaultValue.h"
#include "../../Utils/TrentinoUtilsTypeName.h"

using namespace Trentino::Tests::Reflection;
using namespace Trentino::Reflection::Helpers;
using Trentino::Utils::TypeName;
using namespace std;


// testnamespace
namespace Trentino{
namespace Foo{
namespace Bar
{
   class TestMe
   {
   private:
      int mVal1;
   };
} //namespace Bar
} //namespace Foo
} //namespace Trentino

TEST_F(HelpersTest, testDefaultValue)
{
   const signed char signedCharDefault = 0;
   const unsigned char unsignedCharDefault = 0U;
   const signed short signedShortDefault = 0;
   const unsigned short unsignedShortDefault = 0U;
   const signed int signedIntDefault = 0;
   const unsigned int unsignedIntDefault = 0U;
   const signed long signedLongDefault = 0;
   const unsigned long unsignedLongDefault = 0;
   const signed long long signedLongLongDefault = 0L;
   const unsigned long long unsignedLongLongDefault = 0UL;
   const float floatDefault = 0.0f;
   const double doubleDefault = 0.0;
   const char* constCharPtrDefault = nullptr;
   void* voidPtrDefault = nullptr;
   Trentino::Foo::Bar::TestMe* objectPtrDefault = nullptr;


   ASSERT_EQ(signedCharDefault, DefaultValue<signed char>::value());
   ASSERT_EQ(unsignedCharDefault, DefaultValue<unsigned char>::value());
   ASSERT_EQ(signedShortDefault, DefaultValue<signed short>::value());
   ASSERT_EQ(unsignedShortDefault, DefaultValue<unsigned short>::value());
   ASSERT_EQ(signedIntDefault, DefaultValue<int>::value());
   ASSERT_EQ(unsignedIntDefault, DefaultValue<unsigned int>::value());
   ASSERT_EQ(signedLongDefault, DefaultValue<signed long>::value());
   ASSERT_EQ(unsignedLongDefault, DefaultValue<unsigned long>::value());
   ASSERT_EQ(signedLongLongDefault, DefaultValue<signed long long>::value());
   ASSERT_EQ(unsignedLongLongDefault, DefaultValue<unsigned long long>::value());
   ASSERT_EQ(floatDefault, DefaultValue<float>::value());
   ASSERT_EQ(doubleDefault, DefaultValue<double>::value());
   ASSERT_EQ(constCharPtrDefault, DefaultValue<const char*>::value());
   ASSERT_EQ(voidPtrDefault, DefaultValue<void*>::value());
   ASSERT_EQ(objectPtrDefault, DefaultValue<Trentino::Foo::Bar::TestMe*>::value());
}


TEST_F(HelpersTest, testVariant)
{
   Variant invalidVariant;
   ASSERT_EQ(Variant::Invalid, invalidVariant.type());

   Variant checkVariant;

   {
      // signed char
      const signed char val = -42;
      Variant variant(val);
      ASSERT_EQ(Variant::SignedChar, variant.type());
      ASSERT_EQ(val, variant.data().valueChar);
      ASSERT_EQ(val, variant.toSignedChar());
      checkVariant.fromSignedChar(val);
      ASSERT_EQ(Variant::SignedChar, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);

   }

   {
      // unsigned char
      const unsigned char val = 142;
      Variant variant(val);
      ASSERT_EQ(Variant::UnsignedChar, variant.type());
      ASSERT_EQ(val, variant.data().valueUChar);
      ASSERT_EQ(val, variant.toUnsignedChar());
      checkVariant.fromUnsignedChar(val);
      ASSERT_EQ(Variant::UnsignedChar, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }

   {
      // short
      const short val = -4242;
      Variant variant(val);
      ASSERT_EQ(Variant::Short, variant.type());
      ASSERT_EQ(val, variant.data().valueShort);
      ASSERT_EQ(val, variant.toShort());
      checkVariant.fromShort(val);
      ASSERT_EQ(Variant::Short, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }

   {
      // unsigned short
      const unsigned short val = 42424;
      Variant variant(val);
      ASSERT_EQ(Variant::UnsignedShort, variant.type());
      ASSERT_EQ(val, variant.data().valueUShort);
      ASSERT_EQ(val, variant.toUnsignedShort());
      checkVariant.fromUnsignedShort(val);
      ASSERT_EQ(Variant::UnsignedShort, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }

   {
      // bool
      const bool val = true;
      Variant variant(val);
      ASSERT_EQ(Variant::Bool, variant.type());
      ASSERT_EQ(val, variant.data().valueBool);
      ASSERT_EQ(val, variant.toBool());
      checkVariant.fromBool(val);
      ASSERT_EQ(Variant::Bool, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }

   {
      // int
      const int val = -424242;
      Variant variant(val);
      ASSERT_EQ(Variant::Int, variant.type());
      ASSERT_EQ(val, variant.data().valueInt);
      ASSERT_EQ(val, variant.toInt());
      checkVariant.fromInt(val);
      ASSERT_EQ(Variant::Int, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }

   {
      // unsigned int
      const unsigned int val = 0xc001d00d;
      Variant variant(val);
      ASSERT_EQ(Variant::UnsignedInt, variant.type());
      ASSERT_EQ(val, variant.data().valueUInt);
      ASSERT_EQ(val, variant.toUnsignedInt());
      checkVariant.fromUnsignedInt(val);
      ASSERT_EQ(Variant::UnsignedInt, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }

   {
      // long
      const long val = -424242;
      Variant variant(val);
      ASSERT_EQ(Variant::Long, variant.type());
      ASSERT_EQ(val, variant.data().valueLong);
      ASSERT_EQ(val, variant.toLong());
      checkVariant.fromLong(val);
      ASSERT_EQ(Variant::Long, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }

   {
      // unsigned long
      const unsigned long val = 0xc001d00d;
      Variant variant(val);
      ASSERT_EQ(Variant::UnsignedLong, variant.type());
      ASSERT_EQ(val, variant.data().valueULong);
      ASSERT_EQ(val, variant.toUnsignedLong());
      checkVariant.fromUnsignedLong(val);
      ASSERT_EQ(Variant::UnsignedLong, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }

   {
      // float
      const float val = 42.42f;
      Variant variant(val);
      ASSERT_EQ(Variant::Float, variant.type());
      ASSERT_EQ(val, variant.data().valueFloat);
      ASSERT_EQ(val, variant.toFloat());
      checkVariant.fromFloat(val);
      ASSERT_EQ(Variant::Float, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }

   {
      // double
      const double val = 42.42424242f;
      Variant variant(val);
      ASSERT_EQ(Variant::Double, variant.type());
      ASSERT_EQ(val, variant.data().valueDouble);
      ASSERT_EQ(val, variant.toDouble());
      checkVariant.fromDouble(val);
      ASSERT_EQ(Variant::Double, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }

   {
      // long long
      const long long val = -42424242424242LL;
      Variant variant(val);
      ASSERT_EQ(Variant::LongLong, variant.type());
      ASSERT_EQ(val, variant.data().valueLongLong);
      ASSERT_EQ(val, variant.toLongLong());
      checkVariant.fromLongLong(val);
      ASSERT_EQ(Variant::LongLong, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }

   {
      // unsigned long long
      const unsigned long long val = 0xc0debabec001d00dULL;
      Variant variant(val);
      ASSERT_EQ(Variant::UnsignedLongLong, variant.type());
      ASSERT_EQ(val, variant.data().valueULongLong);
      ASSERT_EQ(val, variant.toUnsignedLongLong());
      checkVariant.fromUnsignedLongLong(val);
      ASSERT_EQ(Variant::UnsignedLongLong, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }

   {
      // const char*
      const char* val = "LoremIpsum";
      Variant variant(val);
      ASSERT_EQ(Variant::ConstCharPtr, variant.type());
      ASSERT_TRUE(strcmp(val, variant.data().valueConstCharPtr) == 0);
      ASSERT_TRUE(strcmp(val, variant.toConstCharPtr()) == 0);
      const char* val2 = "LoremIpsum"; //string content must be equal
      checkVariant.fromConstCharPtr(val2);
      ASSERT_EQ(Variant::ConstCharPtr, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }

   {
      // void*
      boost::scoped_ptr<Trentino::Foo::Bar::TestMe> ptr(new Trentino::Foo::Bar::TestMe);
      void* val = ptr.get();
      Variant variant(val);
      ASSERT_EQ(Variant::VoidPtr, variant.type());
      ASSERT_EQ(val, variant.data().valuePtr);
      ASSERT_EQ(val, variant.toVoidPtr());
      checkVariant.fromVoidPtr(val);
      ASSERT_EQ(Variant::VoidPtr, checkVariant.type());
      ASSERT_TRUE(checkVariant == variant);
   }
}

TEST_F(HelpersTest, testVariantFromTypeName)
{
   ASSERT_EQ(Variant::fromTypeName("invalid one").type(), Variant::Invalid);
   ASSERT_EQ(Variant::fromTypeName(TypeName<char>::name()).type(), Variant::SignedChar);
   ASSERT_EQ(Variant::fromTypeName(TypeName<unsigned char>::name()).type(), Variant::UnsignedChar);
   ASSERT_EQ(Variant::fromTypeName(TypeName<short>::name()).type(), Variant::Short);
   ASSERT_EQ(Variant::fromTypeName(TypeName<unsigned short>::name()).type(), Variant::UnsignedShort);
   ASSERT_EQ(Variant::fromTypeName(TypeName<int>::name()).type(), Variant::Int);
   ASSERT_EQ(Variant::fromTypeName(TypeName<unsigned int>::name()).type(), Variant::UnsignedInt);
   ASSERT_EQ(Variant::fromTypeName(TypeName<long>::name()).type(), Variant::Long);
   ASSERT_EQ(Variant::fromTypeName(TypeName<unsigned long>::name()).type(), Variant::UnsignedLong);
   ASSERT_EQ(Variant::fromTypeName(TypeName<long long>::name()).type(), Variant::LongLong);
   ASSERT_EQ(Variant::fromTypeName(TypeName<unsigned long long>::name()).type(), Variant::UnsignedLongLong);
   ASSERT_EQ(Variant::fromTypeName(TypeName<float>::name()).type(), Variant::Float);
   ASSERT_EQ(Variant::fromTypeName(TypeName<double>::name()).type(), Variant::Double);
   ASSERT_EQ(Variant::fromTypeName(TypeName<void*>::name()).type(), Variant::VoidPtr);
   ASSERT_EQ(Variant::fromTypeName(TypeName<Trentino::Foo::Bar::TestMe*>::name()).type(), Variant::VoidPtr);
   ASSERT_EQ(Variant::fromTypeName(TypeName<const char*>::name()).type(), Variant::ConstCharPtr);
}

template<typename TYPE>
class DefaultCompareStrategy
{
public:
   static void compare(const TYPE& value1, const TYPE& value2)
   {
      ASSERT_EQ(value1, value2);
   }
}; //template class DefaultCompareStrategy

template<typename TYPE, class STRATEGY = DefaultCompareStrategy<typename TYPE::value_type> >
class Compare
{
public:
   static void lists(const TYPE& list1, const TYPE& list2)
   {
      ASSERT_EQ(list1.size(), list2.size());
      const typename TYPE::const_iterator list1End = list1.end();
      //const list<int>::const_iterator list2End = list2.end();
      typename TYPE::const_iterator iter1 = list1.begin();
      typename TYPE::const_iterator iter2 = list2.begin();
      while(iter1 != list1End)
      {
         //STRATE
         STRATEGY::compare(*iter1, *iter2);
         ++iter1;
         ++iter2;
      }
   }
};//template class Compare

template<typename TYPE>
class ListCompareStrategy
{
public:
   static void compare(const TYPE& value1, const TYPE& value2)
   {
      //now call with default strategy
      Compare<TYPE>::lists(value1, value2);
   }
};//template class ListCompareStrategy


TEST_F(HelpersTest, testListWrapper)
{
   // simple list
   {
      list<int> testListInt;
      testListInt.push_back(1);
      testListInt.push_back(2);
      ListWrapper< list<int> > listWrapperSimple(testListInt);
      list<int> testListIntBack;
      listWrapperSimple.expandToList(testListIntBack, *listWrapperSimple.listType());
      Compare< list<int> >::lists(testListInt, testListIntBack);
   }

   // std::string list
   {
      list<string> testListString;
      testListString.push_back("String1");
      testListString.push_back("String2");
      ListWrapper< list<string> > listWrapperString(testListString);
      list<string> testListStringBack;
      listWrapperString.expandToList(testListStringBack, *listWrapperString.listType());
      Compare< list<string> >::lists(testListString, testListStringBack);
   }

   // std::list<std::string> list
   list< list<string> > testListListString;
   list<string> list1;
   list1.push_back("list1_1");
   list1.push_back("list1_2");
   list<string> list2;
   list2.push_back("list2_1");
   list2.push_back("list2_2");
   testListListString.push_back(list1);
   testListListString.push_back(list2);
   ListWrapper< list< list<string> > > listWrapperListString(testListListString);
   list< list<string> > testListListStringBack;
   listWrapperListString.expandToList(testListListStringBack, *listWrapperListString.listType());
   Compare< list< list<string> >, ListCompareStrategy< list<string> > >::lists(testListListString, testListListStringBack);

}

