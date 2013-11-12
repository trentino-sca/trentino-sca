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
package org.trentino.trengen.tools.scavalidation;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

public final class XSDSchemaTypes {
	static final HashMap<String, String>	xsdBuiltinTypeRegexs	= new HashMap<String, String>() {
		                                                             private static final long	serialVersionUID	= 7634049030449585524L;

		                                                             {
			                                                             put("language", "[a-zA-Z]{1,8}(-[a-zA-Z0-9]{1,8})*");
		                                                             }
	                                                             };

	static final HashMap<String, String>	xsdBuiltinTypes	     = new HashMap<String, String>() {
		                                                             private static final long	serialVersionUID	= -8655063853855614109L;

		                                                             {
			                                                             put("anySimpleType", "String");
			                                                             put("anyType", "Not Supported");
			                                                             put("anyURI", "String");
			                                                             put("base64Binary", "char*");
			                                                             put("boolean", "bool");
			                                                             put("byte", "int8_t");
			                                                             put("date", "String");
			                                                             put("dateTime", "String");
			                                                             put("decimal", "String");
			                                                             put("double", "double");
			                                                             put("duration", "String");
			                                                             put("ENTITIES", "std::list<std::string> ");
			                                                             put("ENTITY", "String");
			                                                             put("float", "float");
			                                                             put("gDay", "String");
			                                                             put("gMonth", "String");
			                                                             put("gMonthDay", "String");
			                                                             put("gYear", "String");
			                                                             put("gYearMonth", "String");
			                                                             put("hexBinary", "char*");
			                                                             put("ID", "String");
			                                                             put("IDREF", "String");
			                                                             put("IDREFS", "std::list<std::string> ");
			                                                             put("int", "int32_t ");
			                                                             put("integer", "String");
			                                                             put("language", "String");
			                                                             put("long", "int64_t ");
			                                                             put("Name", "String");
			                                                             put("NCName", "String");
			                                                             put("negativeInteger", "String");
			                                                             put("NMTOKEN", "String");
			                                                             put("NMTOKENS", "std::list<std::string> ");
			                                                             put("nonNegativeInteger", "String");
			                                                             put("nonPositiveInteger", "String");
			                                                             put("normalizedString", "String");
			                                                             put("NOTATION", "String");
			                                                             put("positiveInteger", "String");
			                                                             put("QName", "String");
			                                                             put("short", "int16_t ");
			                                                             put("string", "String");
			                                                             put("time", "String");
			                                                             put("token", "String");
			                                                             put("unsignedByte", "uint8_t ");
			                                                             put("unsignedInt", "uint32_t ");
			                                                             put("unsignedLong", "uint64_t ");
			                                                             put("unsignedShort", "t16_t ");
		                                                             }
	                                                             };

	static final List<String>	         xsdBuiltinTypesList	 = Arrays.asList("anySimpleType", "anyType", "anyURI", "base64Binary", "boolean",
	                                                                     "byte", "date", "dateTime", "decimal", "double", "duration", "ENTITIES",
	                                                                     "ENTITY", "float", "gDay", "gMonth", "gMonthDay", "gYear", "gYearMonth",
	                                                                     "hexBinary", "ID", "IDREF", "IDREFS", "int", "integer", "language", "long",
	                                                                     "Name", "NCName", "negativeInteger", "NMTOKEN", "NMTOKENS",
	                                                                     "nonNegativeInteger", "nonPositiveInteger", "normalizedString", "NOTATION",
	                                                                     "positiveInteger", "QName", "short", "string", "time", "token",
	                                                                     "unsignedByte", "unsignedInt", "unsignedLong", "unsignedShort");

	private XSDSchemaTypes () {

	}

	public static boolean IsXSDBuiltinType(String type) {
		return xsdBuiltinTypes.containsKey(type);

	}

	public static boolean IsCompatible(String value, String type) {

		// String lang = "1Denmark";
		// String value2 = "language";
		// String regex = xsdBuiltinTypeRegexs.get(value2);
		// boolean fMatches = false;
		// if(regex != null)
		// {
		// fMatches = lang.matches(xsdBuiltinTypeRegexs.get(value2));
		// }
		return true;
	}

}
