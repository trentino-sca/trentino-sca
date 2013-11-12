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
#include "TrentinoTestsUtilsTypeNameTest.h"

//standard
#include <string>
#include <list>

//specific
#include "../../Utils/TrentinoUtilsTypeName.h"

using namespace std;
using Trentino::Tests::Utils::TypeNameTest;
using Trentino::Utils::TypeName;


namespace
{
   const string CharTypeName = "char";
   const string SignedCharTypeName = "char";
   const string UnsignedCharTypeName = "unsigned char";
   const string ShortTypeName = "short";
   const string UnsignedShortTypeName ="unsigned short";
   const string IntTypeName = "int";
   const string UnsignedIntTypeName = "unsigned int";
   const string LongTypeName = "long";
   const string UnsignedLongTypeName = "unsigned long";
   const string LongLongTypeName = "long long";
   const string UnsignedLongLongTypeName = "unsigned long long";
   const string FloatTypeName = "float";
   const string DoubleTypeName = "double";
   const string TestMePtrTypeName = "Trentino::Foo::Bar::TestMe *";
   const string TestMeTypeName = "Trentino::Foo::Bar::TestMe";
   const string TestMeStdListTypeName = 
      "std::list<class Trentino::Foo::Bar::TestMe,class std::allocator<class Trentino::Foo::Bar::TestMe> >";

} //namespace

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

//class TypeNameTest
   //services
TEST_F( TypeNameTest,test)
{
   ASSERT_EQ(string(TypeName<char>::name()), CharTypeName);
   ASSERT_EQ(string(TypeName<signed char>::name()), SignedCharTypeName);
   ASSERT_EQ(string(TypeName<unsigned char>::name()), UnsignedCharTypeName);
   ASSERT_EQ(string(TypeName<short>::name()), ShortTypeName);
   ASSERT_EQ(string(TypeName<unsigned short>::name()), UnsignedShortTypeName);
   ASSERT_EQ(string(TypeName<int>::name()), IntTypeName);
   ASSERT_EQ(string(TypeName<unsigned int>::name()), UnsignedIntTypeName);
   ASSERT_EQ(string(TypeName<long>::name()), LongTypeName);
   ASSERT_EQ(string(TypeName<unsigned long>::name()), UnsignedLongTypeName);
   ASSERT_EQ(string(TypeName<long long>::name()), LongLongTypeName);
   ASSERT_EQ(string(TypeName<unsigned long long>::name()), UnsignedLongLongTypeName);
   ASSERT_EQ(string(TypeName<float>::name()), FloatTypeName);
   ASSERT_EQ(string(TypeName<double>::name()), DoubleTypeName);
   ASSERT_EQ(string(TypeName<Trentino::Foo::Bar::TestMe*>::name()), TestMePtrTypeName);
   ASSERT_EQ(string(TypeName<Trentino::Foo::Bar::TestMe>::name()), TestMeTypeName);
   ASSERT_EQ(string(TypeName< list<Trentino::Foo::Bar::TestMe> >::name()), TestMeStdListTypeName);   
}
