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
#ifndef SCAReferenceExampleH
#define SCAReferenceExampleH

class YetAnotherSCAReferenceExample{
public:
		virtual int someMethod() = 0;
};


class YetAnotherSCAReferenceExample2
{
private:
		virtual void getSomething();
public:
		virtual int someMethod2() = 0;
};


class YetAnotherSCAReferenceExample4
{
private:
		virtual void getSomething();
		virtual int someMethod2() = 0;
};

class YetAnotherSCAReferenceExample5
{
private:
		virtual void getSomething();
public:
		virtual int someMethod2();
		virtual int someMethod3()=0;
};

class YetAnotherSCAReferenceExample6
{
private:
		virtual void getSomething();
public:
		virtual int someMethod2();
		virtual int someMethod3(int a)=0;
};

class YetAnotherSCAReferenceExample7
{
private:
		virtual void getSomething();
public:
		virtual int someMethod2();
		virtual int someMethod3()=0;
};
#endif
