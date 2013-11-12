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

#ifndef TrentinoExampleBasicCalculatorCalculatorH
#define TrentinoExampleBasicCalculatorCalculatorH

//standard
//#include <oasis\sca\ComponentContext.h>

//specific
#include "services\TrentinoExampleBasicCalculatorCalculator.h"
#include "services\TrentinoExampleBasicCalculatorDivider.h"

#ifdef WIN32
   #ifdef BASICCALCULATOR_EXPORTS
      #undef BASICCALCULATOR_IMPORT_EXPORT
      #define BASICCALCULATOR_IMPORT_EXPORT __declspec(dllexport)
   #else
      #undef BASICCALCULATOR_IMPORT_EXPORT
      #define BASICCALCULATOR_IMPORT_EXPORT __declspec(dllimport)       
   #endif //BASICCALCULATOR_EXPORTS
   #else
      #define BASICCALCULATOR_IMPORT_EXPORT
#endif //WIN32

namespace oasis{
namespace sca
{
   class ComponentContext;
} //namespace sca
} //namespace oasis

namespace Trentino{
namespace Example{
namespace BasicCalculator
{

   //class declaration
   //**********************************************************************************************
   //                             CalculatorImpl
   //**********************************************************************************************
   //! CalculatorImpl implementation testcode
   //**********************************************************************************************
   class BASICCALCULATOR_IMPORT_EXPORT CalculatorImpl : public Calculator
   {
   public:
      CalculatorImpl();
      virtual ~CalculatorImpl();

      virtual int add(int a, int b);
      virtual int div(int a, int b);
      virtual int div2(int a, int b);

      void setDivider(Divider* divider);
      void setComponentContext(oasis::sca::ComponentContext* componentContext);

   private :

      //@Reference(service="IDivider")
      Divider* mDivider;

      //ComponentContext
      oasis::sca::ComponentContext* mComponentContext;


   };//class Calculator

	#include "TrentinoExampleBasicCalculatorCalculatorImpl.inl" 

}//namespace BasicCalculator
}//namespace Example
}//namespace Trentino



#endif //TrentinoExampleBasicCalculatorCalculatorH