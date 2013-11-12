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

#ifndef TrentinoExampleBasicPrinterImplH
#define TrentinoExampleBasicPrinterImplH

//standard
//#include <oasis\sca\ComponentContext.h>

//specific
#include "services/TrentinoExampleBasicPrinter.h"


#ifdef WIN32
   #ifdef BASICPRINTER_EXPORTS
      #undef BASICPRINTER_IMPORT_EXPORT
      #define BASICPRINTER_IMPORT_EXPORT __declspec(dllexport)
   #else
      #undef BASICPRINTER_IMPORT_EXPORT
      #define BASICPRINTER_IMPORT_EXPORT __declspec(dllimport)       
   #endif //BASICPRINTER_EXPORTS
   #else
      #define BASICPRINTER_IMPORT_EXPORT
#endif //WIN32

#ifndef nullptr
   #define nullptr 0
#endif



namespace Trentino{
namespace Example{

   //class declaration
   //**********************************************************************************************
   //                             CalculatorImpl
   //**********************************************************************************************
   //! CalculatorImpl implementation testcode
   //**********************************************************************************************
   class BASICPRINTER_IMPORT_EXPORT BasicPrinterImpl : public BasicPrinter
   {
   public:
      BasicPrinterImpl();
      virtual ~BasicPrinterImpl();

	virtual ComplexNumber add (const ComplexNumber& a,const ComplexNumber& b);
	virtual tint32_t addSimple (const tint32_t a,const tint32_t b);
	virtual ComplexNumber divide (const ComplexNumber& a,const ComplexNumber& b);
	virtual void multiply (const ComplexNumber& a,const ComplexNumber& b, ComplexNumber& c);
	virtual ComplexNumber divide2 (const TupleComplexNumber& tuple);
	virtual tuint32_t calculateAge (const Person& person) throw (ValidationException);

   private :



   };//class BasicPrinterImpl

}//namespace Example
}//namespace Trentino



#endif //TrentinoExampleBASICPRINTERCalculatorH