// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright 2011 by Siemens AG. All rights reserved.
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

#ifndef PersonH
#define PersonH

#ifdef WIN32
#ifdef PROPERTIES_EXPORTS
#define PROPERTIES_IMPORT_EXPORT __declspec(dllexport)
#else
#define PROPERTIES_IMPORT_EXPORT __declspec(dllimport)
#endif
#else 
#define PROPERTIES_IMPORT_EXPORT
#endif

//standard
#include <string>
#include <list>

//specific
#include "../../../../Global/TrentinoGlobal.h"

namespace Trentino{
namespace Tests{
namespace Core
{

   class PROPERTIES_IMPORT_EXPORT ComponentWithProperties
   {
   public:
      void set_anySimpleType_S(const std::string& value);
      void set_anyURI_S(const std::string& value);
      void set_base64Binary_S(char* value);
      void set_boolean_S(bool value);
      void set_byte_S(int8_t value);
      void set_date_S(const std::string& value);
      void set_dateTime_S(const std::string& value);
      void set_decimal_S(const std::string& value);
      void set_double_S(double value);
      void set_duration_S(const std::string& value);
      void set_ENTITY_S(const std::string& value);
      void set_ENTITIES_S(const std::list<std::string>& value);
      void set_float_S(float value);
      void set_gDay_S(const std::string& value);
      void set_gMonth_S(const std::string& value);
      void set_gMonthDay_S(const std::string& value);
      void set_gYear_S(const std::string& value);
      void set_gYearMonth_S(const std::string& value);
      void set_hexBinary_S(char* value);
      void set_ID_S(const std::string& value);
      void set_IDREF_S(const std::string& value);
      void set_IDREFS_S(const std::list<std::string>& value);
      void set_int_S(int32_t value);
      void set_integer_S(const std::string& value);
      void set_language_S(const std::string& value);
      void set_long_S(int64_t value);
      void set_Name_S(const std::string& value);
      void set_NCName_S(const std::string& value);
      void set_negativeInteger_S(const std::string& value);
      void set_NMTOKEN_S(const std::string& value);
      void set_NMTOKENS_S(const std::list<std::string>& value);
      void set_nonNegativeInteger_S(const std::string& value);
      void set_nonPositiveInteger_S(const std::string& value);
      void set_normalizedString_S(const std::string& value);
      void set_NOTATION_S(const std::string& value);
      void set_positiveInteger_S(const std::string& value);
      void set_QName_S(const std::string& value);
      void set_short_S(int16_t value);
      void set_string_S(const std::string& value);
      void set_time_S(const std::string& value);
      void set_token_S(const std::string& value);
      void set_unsignedByte_S(uint8_t value);
      void set_unsignedInt_S(uint32_t value);
      void set_unsignedLong_S(uint64_t value);
      void set_unsignedShort_S(uint16_t value);   

      void set_anySimpleType_M(const std::list< std::string >& value);
      void set_anyURI_M(const std::list< std::string >& value);
      void set_base64Binary_M(const std::list< char* > value);
      void set_boolean_M(const std::list< bool > value);
      void set_byte_M(const std::list< int8_t > value);
      void set_date_M(const std::list< std::string >& value);
      void set_dateTime_M(const std::list< std::string >& value);
      void set_decimal_M(const std::list< std::string >& value);
      void set_double_M(const std::list< double > value);
      void set_duration_M(const std::list< std::string >& value);
      void set_ENTITY_M(const std::list< std::string >& value);
      void set_ENTITIES_M(const std::list< std::list<std::string> >& value);
      void set_float_M(const std::list< float > value);
      void set_gDay_M(const std::list< std::string >& value);
      void set_gMonth_M(const std::list< std::string >& value);
      void set_gMonthDay_M(const std::list< std::string >& value);
      void set_gYear_M(const std::list< std::string >& value);
      void set_gYearMonth_M(const std::list< std::string >& value);
      void set_hexBinary_M(const std::list< char* > value);
      void set_ID_M(const std::list< std::string >& value);
      void set_IDREF_M(const std::list< std::string >& value);
      void set_IDREFS_M(const std::list< std::list<std::string> >& value);
      void set_int_M(const std::list< int32_t > value);
      void set_integer_M(const std::list< std::string >& value);
      void set_language_M(const std::list< std::string >& value);
      void set_long_M(const std::list< int64_t > value);
      void set_Name_M(const std::list< std::string >& value);
      void set_NCName_M(const std::list< std::string >& value);
      void set_negativeInteger_M(const std::list< std::string >& value);
      void set_NMTOKEN_M(const std::list< std::string >& value);
      void set_NMTOKENS_M(const std::list< std::list<std::string> >& value);
      void set_nonNegativeInteger_M(const std::list< std::string >& value);
      void set_nonPositiveInteger_M(const std::list< std::string >& value);
      void set_normalizedString_M(const std::list< std::string >& value);
      void set_NOTATION_M(const std::list< std::string >& value);
      void set_positiveInteger_M(const std::list< std::string >& value);
      void set_QName_M(const std::list< std::string >& value);
      void set_short_M(std::list< int16_t > value);
      void set_string_M(const std::list< std::string >& value);
      void set_time_M(const std::list< std::string >& value);
      void set_token_M(const std::list< std::string >& value);
      void set_unsignedByte_M(const std::list< uint8_t > value);
      void set_unsignedInt_M(const std::list< uint32_t > value);
      void set_unsignedLong_M(const std::list< uint64_t > value);
      void set_unsignedShort_M(const std::list< uint16_t > value);

      //data
   public:
      std::string anySimpleType_S;
      std::string anyURI_S;
      std::string base64Binary_S;
      bool boolean_S;
      int8_t byte_S;
      std::string date_S;
      std::string dateTime_S;
      std::string decimal_S;
      double double_S;
      std::string duration_S;
      std::string ENTITY_S;
      std::list<std::string> ENTITIES_S;
      float float_S;
      std::string gDay_S;
      std::string gMonth_S;
      std::string gMonthDay_S;
      std::string gYear_S;
      std::string gYearMonth_S;
      std::string hexBinary_S;
      std::string ID_S;
      std::string IDREF_S;
      std::list<std::string> IDREFS_S;
      int32_t int_S;
      std::string integer_S;
      std::string language_S;
      int64_t long_S;
      std::string Name_S;
      std::string NCName_S;
      std::string negativeInteger_S;
      std::string NMTOKEN_S;
      std::list<std::string> NMTOKENS_S;
      std::string nonNegativeInteger_S;
      std::string nonPositiveInteger_S;
      std::string normalizedString_S;
      std::string NOTATION_S;
      std::string positiveInteger_S;
      std::string QName_S;
      int16_t short_S;
      std::string string_S;
      std::string time_S;
      std::string token_S;
      uint8_t unsignedByte_S;
      uint32_t unsignedInt_S;
      uint64_t unsignedLong_S;
      uint16_t unsignedShort_S;           

      std::list< std::string > anySimpleType_M;
      std::list< std::string > anyURI_M;
      std::list< std::string  > base64Binary_M;
      std::list< bool > boolean_M;
      std::list< int8_t > byte_M;
      std::list< std::string > date_M;
      std::list< std::string > dateTime_M;
      std::list< std::string > decimal_M;
      std::list< double > double_M;
      std::list< std::string > duration_M;
      std::list< std::string > ENTITY_M;
      std::list< std::list<std::string> > ENTITIES_M;
      std::list< float > float_M;
      std::list< std::string > gDay_M;
      std::list< std::string > gMonth_M;
      std::list< std::string > gMonthDay_M;
      std::list< std::string > gYear_M;
      std::list< std::string > gYearMonth_M;
      std::list< std::string  > hexBinary_M;      
      std::list< std::string > ID_M;
      std::list< std::string > IDREF_M;
      std::list< std::list<std::string> > IDREFS_M;
      std::list< int32_t > int_M;      
      std::list< std::string > integer_M;
      std::list< std::string > language_M;
      std::list< int64_t > long_M;        
      std::list< std::string > Name_M;
      std::list< std::string > NCName_M;
      std::list< std::string > negativeInteger_M;
      std::list< std::string > NMTOKEN_M;
      std::list< std::list<std::string> > NMTOKENS_M;
      std::list< std::string > nonNegativeInteger_M;
      std::list< std::string > nonPositiveInteger_M;
      std::list< std::string > normalizedString_M;
      std::list< std::string > NOTATION_M;
      std::list< std::string > positiveInteger_M;
      std::list< std::string > QName_M;
      std::list< int16_t > short_M;  
      std::list< std::string > string_M;
      std::list< std::string > time_M;
      std::list< std::string > token_M;
      std::list< uint8_t > unsignedByte_M;
      std::list< uint32_t > unsignedInt_M;
      std::list< uint64_t > unsignedLong_M;
      std::list< uint16_t > unsignedShort_M;
   }; //class ComponentWithProperties
} //namespace Core
} //namespace Tests
} //namespace Trentino

#endif
