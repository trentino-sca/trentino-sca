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

#ifndef TrentinoLocalCallDataExchangeH
#define TrentinoLocalCallDataExchangeH
#ifdef WIN32
#ifdef LOCALDATACALLEXCHANGE_EXPORTS
#undef LOCALDATACALLEXCHANGE_IMPORT_EXPORT
#define LOCALDATACALLEXCHANGE_IMPORT_EXPORT __declspec(dllexport)
#else
#undef LOCALDATACALLEXCHANGE_IMPORT_EXPORT
#define LOCALDATACALLEXCHANGE_IMPORT_EXPORT __declspec(dllimport)       
#endif //BASICCALCULATOR_EXPORTS
#else
#define LOCALDATACALLEXCHANGE_IMPORT_EXPORT
#endif //WIN32
//standard
#include <string>
#include <vector>
namespace Trentino{
namespace LocalCallDataExchange{

      //****************************************************************************************************
      //                                         ClassA
      //****************************************************************************************************
      //! \brief simple class with 3 fields haveing standard types
      //****************************************************************************************************
      class ClassA {
		  
      public:
		  ClassA(){ a = 5; b=5; c="i am in const a object";}
         int a ;
         int b ;
         std::string c;
         };


      //****************************************************************************************************
      //                                         ClassB
      //****************************************************************************************************
      //! \brief a complex class having a vector of strings as well as an object of class A
      //****************************************************************************************************
      class ClassB {
      public:
         std::vector<std::string> elems;
         ClassA aObject;
         };

      }//namespace LocalCallDataExchange
   }//namespace Trentino

#endif //TrentinoLocalCallDataExchangeH