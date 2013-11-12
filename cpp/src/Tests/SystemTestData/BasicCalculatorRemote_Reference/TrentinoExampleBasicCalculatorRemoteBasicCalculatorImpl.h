// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************

#ifndef TrentinoExampleBasicCalculatorRemoteBasicCalculatorImplH
#define TrentinoExampleBasicCalculatorRemoteBasicCalculatorImplH

//standard
//#include <oasis\sca\ComponentContext.h>

//specific
#include "services/TrentinoExampleBasicCalculatorRemoteBasicCalculator.h"


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

#ifndef nullptr
   #define nullptr 0
#endif



namespace Trentino{
namespace Example{
namespace BasicCalculatorRemote
{

   //class declaration
   //**********************************************************************************************
   //                             CalculatorImpl
   //**********************************************************************************************
   //! CalculatorImpl implementation testcode
   //**********************************************************************************************
   class BASICCALCULATOR_IMPORT_EXPORT BasicCalculatorImpl : public BasicCalculator
   {
   public:
      BasicCalculatorImpl();
      virtual ~BasicCalculatorImpl();

	virtual ComplexNumber add (const ComplexNumber& a,const ComplexNumber& b);
	virtual tint32_t addSimple (const tint32_t a,const tint32_t b);
	virtual ComplexNumber divide (const ComplexNumber& a,const ComplexNumber& b);
	virtual void multiply (const ComplexNumber& a,const ComplexNumber& b, ComplexNumber& c);
	virtual ComplexNumber divide2 (const TupleComplexNumber& tuple);
	virtual tuint32_t calculateAge (const Person& person) throw (ValidationException);

   private :



   };//class BasicCalculatorImpl

}//namespace BasicCalculator
}//namespace Example
}//namespace Trentino



#endif //TrentinoExampleBasicCalculatorCalculatorH