// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright 2012 by Siemens AG. All rights reserved.
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

#ifndef TrentinoExampleBasicCalculatorICalculatorH
#define TrentinoExampleBasicCalculatorICalculatorH

namespace Trentino{
namespace Example{
namespace BasicCalculator
{
   //class declaration
   //**********************************************************************************************
   //                             Calculator
   //**********************************************************************************************
   //! Calculator interface testcode
   //**********************************************************************************************
   class Calculator 
   {
		public:
			virtual int add(int a, int b) = 0;
			virtual int div(int a, int b) = 0;

			/**
			* a div method whose implementation use a ComponentContext as defined in the spec
			* @param a
			* @param b
			* @return
			*/
			virtual int div2(int a, int b) = 0;

	};//class Calculator

}//namespace BasicCalculator
}//namespace Example
}//namespace Trentino

#endif //TrentinoExampleBasicCalculatorICalculatorH