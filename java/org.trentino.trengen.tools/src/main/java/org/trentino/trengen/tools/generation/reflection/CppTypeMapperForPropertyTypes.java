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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
// **********************************************************************************
package org.trentino.trengen.tools.generation.reflection;

// import java.awt.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * @author z002ttbb
 */
public class CppTypeMapperForPropertyTypes {

	static final Map<String, String>	mapTypes1	   = new HashMap<String, String>();
	static final Map<String, String>	mapTypes2	   = new HashMap<String, String>();

	// this list keeps the list of all cpp primitive types
	static final List<String>	     cppPrimitiveTypes	= new ArrayList<String>();

	static
	{
		mapTypes2.put("anySimpleType", "std::string");
		mapTypes2.put("anyURI", "std::string");
		mapTypes2.put("base64Binary", "char*");
		mapTypes2.put("boolean", "bool");
		mapTypes2.put("byte", "int8_t");
		mapTypes2.put("date", "std::string");
		mapTypes2.put("dateTime", "std::string");
		mapTypes2.put("decimal", "std::string");
		mapTypes2.put("double", "double");
		mapTypes2.put("duration", "std::string");
		mapTypes2.put("ENTITIES", "std::list<std::string>");
		mapTypes2.put("ENTITY", "std::string");
		mapTypes2.put("float", "float");
		mapTypes2.put("gDay", "std::string");
		mapTypes2.put("gMonth", "std::string");
		mapTypes2.put("gMonthDay", "std::string");
		mapTypes2.put("gYear", "std::string");
		mapTypes2.put("gYearMonth", "std::string");
		mapTypes2.put("hexBinary", "char*");
		mapTypes2.put("ID", "std::string");
		mapTypes2.put("IDREF", "std::string");
		mapTypes2.put("IDREFS", "std::list<std::string>");
		mapTypes2.put("int", "int32_t");
		mapTypes2.put("integer", "std::string");
		mapTypes2.put("language", "std::string");
		mapTypes2.put("long", "int64_t");
		mapTypes2.put("Name", "std::string");
		mapTypes2.put("NCName", "std::string");
		mapTypes2.put("negativeInteger", "std::string");
		mapTypes2.put("NMTOKEN", "std::string");
		mapTypes2.put("NMTOKENS", "std::list<std::string>");
		mapTypes2.put("nonNegativeInteger", "std::string");
		mapTypes2.put("nonPositiveInteger", "std::string");
		mapTypes2.put("normalizedString", "std::string");
		mapTypes2.put("NOTATION", "std::string");
		mapTypes2.put("positiveInteger", "std::string");
		mapTypes2.put("QName", "std::string");
		mapTypes2.put("short", "int16_t");
		mapTypes2.put("string", "std::string");
		mapTypes2.put("time", "std::string");
		mapTypes2.put("token", "std::string");
		mapTypes2.put("unsignedByte", "uint8_t");
		mapTypes2.put("unsignedInt", "uint32_t");
		mapTypes2.put("unsignedLong", "uint64_t");
		mapTypes2.put("unsignedShort", "uint16_t");

	}

	static
	{
		mapTypes1.put("anySimpleType", "char*");
		mapTypes1.put("anyURI", "char*");
		mapTypes1.put("base64Binary", "char*");
		mapTypes1.put("boolean", "bool");
		mapTypes1.put("byte", "int8_t");
		mapTypes1.put("date", "char*");
		mapTypes1.put("dateTime", "char*");
		mapTypes1.put("decimal", "char*");
		mapTypes1.put("double", "double");
		mapTypes1.put("duration", "char*");
		mapTypes1.put("ENTITIES", "std::string");
		mapTypes1.put("ENTITY", "char*");
		mapTypes1.put("float", "float");
		mapTypes1.put("gDay", "char*");
		mapTypes1.put("gMonth", "char*");
		mapTypes1.put("gMonthDay", "char*");
		mapTypes1.put("gYear", "char*");
		mapTypes1.put("gYearMonth", "char*");
		mapTypes1.put("hexBinary", "char*");
		mapTypes1.put("ID", "char*");
		mapTypes1.put("IDREF", "char*");
		mapTypes1.put("IDREFS", "std::string");
		mapTypes1.put("int", "int32_t");
		mapTypes1.put("integer", "char*");
		mapTypes1.put("language", "char*");
		mapTypes1.put("long", "int64_t");
		mapTypes1.put("Name", "char*");
		mapTypes1.put("NCName", "char*");
		mapTypes1.put("negativeInteger", "char*");
		mapTypes1.put("NMTOKEN", "char*");
		mapTypes1.put("NMTOKENS", "std::string");
		mapTypes1.put("nonNegativeInteger", "char*");
		mapTypes1.put("nonPositiveInteger", "char*");
		mapTypes1.put("normalizedString", "char*");
		mapTypes1.put("NOTATION", "char*");
		mapTypes1.put("positiveInteger", "char*");
		mapTypes1.put("QName", "char*");
		mapTypes1.put("short", "int16_t");
		mapTypes1.put("string", "char*");
		mapTypes1.put("time", "char*");
		mapTypes1.put("token", "char*");
		mapTypes1.put("unsignedByte", "uint8_t");
		mapTypes1.put("unsignedInt", "uint32_t");
		mapTypes1.put("unsignedLong", "uint64_t");
		mapTypes1.put("unsignedShort", "uint16_t");

	}

	public String getMatchingType1(String givenType) {
		return mapTypes1.get(givenType);
	}

	public String getMatchingType2(String givenType) {
		return mapTypes2.get(givenType);
	}
}
