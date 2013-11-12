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

//header
#include "TrentinoTestsCoreComponentWithProperties.h"

//standard
#include <boost/foreach.hpp>

using namespace std;
using Trentino::Tests::Core::ComponentWithProperties;

void ComponentWithProperties::set_anySimpleType_S(const string& value) { anySimpleType_S = value; }
void ComponentWithProperties::set_anyURI_S(const string& value) { anyURI_S = value; }
void ComponentWithProperties::set_base64Binary_S(char* value) { base64Binary_S.assign(value); }
void ComponentWithProperties::set_boolean_S(bool value) { boolean_S = value; }
void ComponentWithProperties::set_byte_S(int8_t value) { byte_S = value; }
void ComponentWithProperties::set_date_S(const string& value) { date_S = value; }
void ComponentWithProperties::set_dateTime_S(const string& value) { dateTime_S = value; }
void ComponentWithProperties::set_decimal_S(const string& value) { decimal_S = value; }
void ComponentWithProperties::set_double_S(double value) { double_S = value; }
void ComponentWithProperties::set_duration_S(const string& value) { duration_S = value; }
void ComponentWithProperties::set_ENTITY_S(const string& value) { ENTITY_S = value; }
void ComponentWithProperties::set_ENTITIES_S(const list<string>& value) { ENTITIES_S = value; }
void ComponentWithProperties::set_float_S(float value) { float_S = value; }
void ComponentWithProperties::set_gDay_S(const string& value) { gDay_S = value; }
void ComponentWithProperties::set_gMonth_S(const string& value) { gMonth_S = value; }
void ComponentWithProperties::set_gMonthDay_S(const string& value) { gMonthDay_S = value; }
void ComponentWithProperties::set_gYear_S(const string& value) { gYear_S = value; }
void ComponentWithProperties::set_gYearMonth_S(const string& value) { gYearMonth_S = value; }
void ComponentWithProperties::set_hexBinary_S(char* value) { hexBinary_S.assign(value); }
void ComponentWithProperties::set_ID_S(const string& value) { ID_S = value; }
void ComponentWithProperties::set_IDREF_S(const string& value) { IDREF_S = value; }
void ComponentWithProperties::set_IDREFS_S(const list<string>& value) { IDREFS_S = value; }
void ComponentWithProperties::set_int_S(int32_t value) { int_S = value; }
void ComponentWithProperties::set_integer_S(const string& value) { integer_S = value; }
void ComponentWithProperties::set_language_S(const string& value) { language_S = value; }
void ComponentWithProperties::set_long_S(int64_t value) { long_S = value; }
void ComponentWithProperties::set_Name_S(const string& value) { Name_S = value; }
void ComponentWithProperties::set_NCName_S(const string& value) { NCName_S = value; }
void ComponentWithProperties::set_negativeInteger_S(const string& value) { negativeInteger_S = value; }
void ComponentWithProperties::set_NMTOKEN_S(const string& value) { NMTOKEN_S = value; }
void ComponentWithProperties::set_NMTOKENS_S(const list<string>& value) { NMTOKENS_S = value; }
void ComponentWithProperties::set_nonNegativeInteger_S(const string& value) { nonNegativeInteger_S = value; }
void ComponentWithProperties::set_nonPositiveInteger_S(const string& value) { nonPositiveInteger_S = value; }
void ComponentWithProperties::set_normalizedString_S(const string& value) { normalizedString_S = value; }
void ComponentWithProperties::set_NOTATION_S(const string& value) { NOTATION_S = value; }
void ComponentWithProperties::set_positiveInteger_S(const string& value) { positiveInteger_S = value; }
void ComponentWithProperties::set_QName_S(const string& value) { QName_S = value; }
void ComponentWithProperties::set_short_S(int16_t value) { short_S = value; }
void ComponentWithProperties::set_string_S(const string& value) { string_S = value; }
void ComponentWithProperties::set_time_S(const string& value) { time_S = value; }
void ComponentWithProperties::set_token_S(const string& value) { token_S = value; }
void ComponentWithProperties::set_unsignedByte_S(uint8_t value) { unsignedByte_S = value; }
void ComponentWithProperties::set_unsignedInt_S(uint32_t value) { unsignedInt_S = value; }
void ComponentWithProperties::set_unsignedLong_S(uint64_t value) { unsignedLong_S = value; }
void ComponentWithProperties::set_unsignedShort_S(uint16_t value){ unsignedShort_S = value; }     

void ComponentWithProperties::set_anySimpleType_M(const list< string >& value) { anySimpleType_M = value; }
void ComponentWithProperties::set_anyURI_M(const list< string >& value) { anyURI_M = value; }
void ComponentWithProperties::set_base64Binary_M(const list< char* > value) 
{ 
   BOOST_FOREACH(char* v, value)
   {
      base64Binary_M.push_back(string(v));
   }
}
void ComponentWithProperties::set_boolean_M(const list< bool > value) { boolean_M = value; }
void ComponentWithProperties::set_byte_M(const list< int8_t > value) { byte_M = value; }
void ComponentWithProperties::set_date_M(const list< string >& value) { date_M = value; }
void ComponentWithProperties::set_dateTime_M(const list< string >& value) { dateTime_M = value; }
void ComponentWithProperties::set_decimal_M(const list< string >& value) { decimal_M = value; }
void ComponentWithProperties::set_double_M(const list< double > value) { double_M = value; }
void ComponentWithProperties::set_duration_M(const list< string >& value) { duration_M = value; }
void ComponentWithProperties::set_ENTITY_M(const list< string >& value) { ENTITY_M = value; }
void ComponentWithProperties::set_ENTITIES_M(const list< list<string> >& value) { ENTITIES_M = value; }
void ComponentWithProperties::set_float_M(const list< float > value) { float_M = value; }
void ComponentWithProperties::set_gDay_M(const list< string >& value) { gDay_M = value; }
void ComponentWithProperties::set_gMonth_M(const list< string >& value) { gMonth_M = value; }
void ComponentWithProperties::set_gMonthDay_M(const list< string >& value) { gMonthDay_M = value; }
void ComponentWithProperties::set_gYear_M(const list< string >& value) { gYear_M = value; }
void ComponentWithProperties::set_gYearMonth_M(const list< string >& value) { gYearMonth_M = value; }
void ComponentWithProperties::set_hexBinary_M(const list< char* > value)
   { 
   BOOST_FOREACH(char* v, value)
   {
      hexBinary_M.push_back(string(v));
   }
}
void ComponentWithProperties::set_ID_M(const list< string >& value) { ID_M = value; }
void ComponentWithProperties::set_IDREF_M(const list< string >& value) { IDREF_M = value; }
void ComponentWithProperties::set_IDREFS_M(const list< list<string> >& value) { IDREFS_M = value; }
void ComponentWithProperties::set_int_M(const list< int32_t > value) { int_M = value; }
void ComponentWithProperties::set_integer_M(const list< string >& value) { integer_M = value; }
void ComponentWithProperties::set_language_M(const list< string >& value) { language_M = value; }
void ComponentWithProperties::set_long_M(const list< int64_t > value) { long_M = value; }
void ComponentWithProperties::set_Name_M(const list< string >& value) { Name_M = value; }
void ComponentWithProperties::set_NCName_M(const list< string >& value) { NCName_M = value; }
void ComponentWithProperties::set_negativeInteger_M(const list< string >& value) { negativeInteger_M = value; }
void ComponentWithProperties::set_NMTOKEN_M(const list< string >& value) { NMTOKEN_M = value; }
void ComponentWithProperties::set_NMTOKENS_M(const list< list<string> >& value) { NMTOKENS_M = value; }
void ComponentWithProperties::set_nonNegativeInteger_M(const list< string >& value) { nonNegativeInteger_M = value; }
void ComponentWithProperties::set_nonPositiveInteger_M(const list< string >& value) { nonPositiveInteger_M = value; }
void ComponentWithProperties::set_normalizedString_M(const list< string >& value) { normalizedString_M = value; }
void ComponentWithProperties::set_NOTATION_M(const list< string >& value) { NOTATION_M = value; }
void ComponentWithProperties::set_positiveInteger_M(const list< string >& value) { positiveInteger_M = value; }
void ComponentWithProperties::set_QName_M(const list< string >& value) { QName_M = value; }
void ComponentWithProperties::set_short_M(const list< int16_t > value) { short_M = value; }
void ComponentWithProperties::set_string_M(const list< string >& value) { string_M = value; }
void ComponentWithProperties::set_time_M(const list< string >& value) { time_M = value; }
void ComponentWithProperties::set_token_M(const list< string >& value) { token_M = value; }
void ComponentWithProperties::set_unsignedByte_M(const list< uint8_t > value) { unsignedByte_M = value; }
void ComponentWithProperties::set_unsignedInt_M(const list< uint32_t > value) { unsignedInt_M = value; }
void ComponentWithProperties::set_unsignedLong_M(const list< uint64_t > value) { unsignedLong_M = value; }
void ComponentWithProperties::set_unsignedShort_M(const list< uint16_t > value) { unsignedShort_M = value; }
