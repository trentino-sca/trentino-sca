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

#ifndef TrentinoTestsReflectionTestClassH
#define TrentinoTestsReflectionTestClassH

//standard
#include <stdio.h>
#include <string>
#include <list>

//specific
#include "./../../Global/TrentinoGlobal.h"

namespace Trentino{
namespace Tests{
namespace Reflection
{
   //class declaration
   class InversionClass
   {
      //construction
   public:
      InversionClass();
      //data
   private:
      int mValue1;
   }; //class InversionClass

   
   //class declaration
   class TestClassBase
   {
      //construction
   public:
      TestClassBase();
      //service
   public:      
      bool access1(float param1, int param2);
      //data
   public:
      unsigned long mStartValue;
      float mAccessPropertyFloat;
   }; //class TestClassBase
   
   //class declaration
   class TestClass : TestClassBase
   {
      //construction
   public:
      TestClass();
      ~TestClass();
      TestClass(unsigned long val1, InversionClass* val2);
      //service
   public:
      void access2(int param1, bool param2);
      void access2(float param1, bool param2);
      void access2(float param1);

      double doMultiply(float val1, float val2);     

      void setLists( const std::list<std::string>& paramListString
                    ,const std::list< std::list<std::string> >& paramListListString
                    ,const std::list<unsigned long>& paramListULong
                    ,const std::list<char>& paramListChar);

      //management
   public:
      void setInversionClass(InversionClass* inversionClass);

      //data
   public:
      unsigned long mAccessPropertyUnsignedLong;
      InversionClass* mInversionClass;

      std::list<std::string> mListOfStrings;
      std::list< std::list<std::string> > mListListOfStrings;
      std::list<unsigned long> mListOfULongs;
      std::list<char> mListOfChars;

      static int mInitializationCounter;
      static int mDeinitializationCounter;
   private:
   }; //class TestClass

   class TestBaseClassSuper
   {
      //construction
   public:
      TestBaseClassSuper();
      virtual ~TestBaseClassSuper();

      //service
   public:
      virtual void setData();

      //data
   public:
      std::string mValueSuper1;
      int mValueSuper2;
      float mValueSuper3;
      static int mCalledVirtualDestructor_TestBaseClassSuper;
   }; //class TestBaseClassSuper

   class TestBaseEvil
   {
   private:
      //data
      unsigned long mEvilVar;
      //construction
   public:
      TestBaseEvil() : mEvilVar(0xdeadc0de) {}
      virtual ~TestBaseEvil() {}
   };

   class TestBaseClassA : public TestBaseClassSuper
   {
      //construction
   public:
      TestBaseClassA();
      virtual ~TestBaseClassA();

      //service
   public:
      virtual void setData();
      virtual void setData2();

      //data
   public:
      int mValueA1;
      std::string mValueA2;
   }; //class TestBaseClassA


   class TestBaseClassB
   {
      //construction
   public:
      TestBaseClassB();
      virtual ~TestBaseClassB();
      //service
   public:
      virtual void setData(int valueB1, const std::string& valueB2);
      //data
   public:
      int mValueB1;
      std::string mValueB2;
      static int mCalledVirtualDestructor_TestBaseClassB;
   };//class TestBaseClassB

   class TestClassMulitpleDerived1: public TestBaseEvil, public TestBaseClassA, public TestBaseClassB
   {
      //construction
   public:
      TestClassMulitpleDerived1();
      virtual ~TestClassMulitpleDerived1();

      //service
   public:
      virtual void setData(int valueB1, const std::string& valueB2);
      virtual void setData2();

      //data
   public:
      static int mCalledVirtualDestructor_TestClassMulitpleDerived1;
   };//class TestClassMulitpleDerived1

   class TestClassMulitpleDerived2: public TestBaseEvil, public TestBaseClassB, public TestBaseClassSuper
   {
      //construction
   public:
      TestClassMulitpleDerived2();
      virtual ~TestClassMulitpleDerived2();
      //service
   public:
      virtual void setData(int valueB1, const std::string& valueB2);
      virtual void setData();
   };//class TestClassMulitpleDerived2


} //namespace Reflection
} //namespace Tests
} //namespace Trentino

#endif //TrentinoTestsReflectionTestClassH
