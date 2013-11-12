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

#ifndef TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorImplH
#define TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorImplH

//standard
//#include <oasis\sca\ComponentContext.h>

//specific
#include "services/TrentinoExampleBasicCalculatorRemoteClientBasicCalculator.h"


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
namespace BasicCalculatorRemoteClient
{

   //class declaration
   //**********************************************************************************************
   //                             CalculatorImpl
   //**********************************************************************************************
   //! CalculatorImpl implementation testcode
   //**********************************************************************************************
   class BASICCALCULATOR_IMPORT_EXPORT BasicCalculatorRemoteClientImpl : public BasicCalculator
   {
   public:
      BasicCalculatorRemoteClientImpl();
      virtual ~BasicCalculatorRemoteClientImpl();

	virtual ComplexNumber add (const ComplexNumber& a,const ComplexNumber& b);
	virtual tint32_t addSimple (const tint32_t a,const tint32_t b);
	virtual ComplexNumber divide (const ComplexNumber& a,const ComplexNumber& b);
	virtual void multiply (const ComplexNumber& a,const ComplexNumber& b, ComplexNumber& c);
	virtual ComplexNumber divide2 (const TupleComplexNumber& tuple);
	virtual tuint32_t calculateAge (const Person& person) throw (ValidationException);
	virtual std::string changeString (const std::string& str);

	virtual void setBasicCalculatorRef(BasicCalculator* basicCalc);

   private :
		BasicCalculator* m_basicCalc;


   };//class BasicCalculatorRemoteClientImpl

}//namespace BasicCalculatorRemoteClient
}//namespace Example
}//namespace Trentino



#endif //TrentinoExampleBasicCalculatorCalculatorH