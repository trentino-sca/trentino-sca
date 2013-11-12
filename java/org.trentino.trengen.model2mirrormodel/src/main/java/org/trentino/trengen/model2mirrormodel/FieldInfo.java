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

package org.trentino.trengen.model2mirrormodel;

import java.math.BigInteger;

import org.apache.log4j.Logger;

/**
 * represent a field
 * @author z002ttbb
 */
public class FieldInfo implements Comparable<FieldInfo> {

	private static final String	  STD_STRING	= "std::string";
	private static final String	  LIST	     = "List";
	protected static final Logger	logger	 = Logger.getLogger(FieldInfo.class);
	/**
	 * the name of the field.
	 */
	private String	              name;
	/**
	 * the type of the field
	 */
	private String	              typeName;

	/**
	 * the list of type parameters. This is available if the type has type
	 * parametes as List or a JAXB Element
	 */
	private String[]	          typeParams;

	/**
	 * is true if this field represent an xsd attribute
	 */
	private boolean	              attribute;
	private boolean	              ncName;
	private boolean	              anyURI;

	public FieldInfo (String name) {
		logger.debug("### Creating field " + name);
		if(name.startsWith("_"))
		{
			name = name.substring(1);
		}
		if("namespace".equals(name))
		{
			name = "namespace_";
		}
		this.name = name;
	}

	public FieldInfo (String fName, String typeName, String... typeParams) {
		this(fName);
		this.typeName = typeName;
		this.typeParams = typeParams;
		if(this.typeParams != null && this.typeParams.length != 0 && "string".equals(typeParams[0].toLowerCase()))
		{
			this.typeParams[0] = STD_STRING;
		}
	}

	public String getName() {
		return name;
	}

	@Override
	public String toString() {
		String res = typeName;
		if(typeParams != null && typeParams.length > 0)
		{
			res += "<";
			for (String par : typeParams)
			{
				res += par + ", ";
			}
			res += ">";
		}
		res += "  " + name + ";\n";
		return res;
	}

	public void setAttribute(boolean b) {
		attribute = b;
	}

	public boolean isAttribute() {
		return attribute;
	}

	public boolean isElement() {
		return !isAttribute();
	}

	public String getFirstTypeParam() {
		if(typeParams == null || typeParams.length == 0)
		{
			throw new IllegalArgumentException("No type param defined.");
		}
		return typeParams[0];
	}

	public String getFirstTypeParamFull() {
		String res = getFirstTypeParam();
		if((isLikeNCName(res) || isQName(res)) && res != null && !res.contains("::"))
		{
			return "Trentino::XML::Schema::" + res;
		}
		return res;
	}

	public String getFirstTypeParamAsJavaString() {
		String value = getFirstTypeParam();
		if(STD_STRING.equals(value))
		{
			return "String";
		}
		return value;
	}

	public boolean isList() {
		return LIST.equals(typeName);
	}

	public boolean isNCName() {
		return ncName || "NCName".equals(typeName);
	}

	public boolean isAnyURI() {
		return anyURI || "AnyURI".equals(typeName);
	}

	public boolean isBoolean() {
		return Boolean.class.getSimpleName().equals(typeName);
	}

	public boolean isString() {
		return "String".equals(typeName) || "AnySimpleType".equalsIgnoreCase(typeName);
	}

	public boolean isInt() {
		return Integer.class.getSimpleName().equals(typeName) || "int".equals(typeName);
	}

	public boolean isInt64() {
		boolean ok = BigInteger.class.getSimpleName().toLowerCase().equals(typeName.toLowerCase());
		ok |= "long".equals(typeName) || "Long".equals(typeName);
		return ok;
	}

	public String getElementSuffix() {
		if(isElement())
		{
			return "Element";
		}
		return "";
	}

	public boolean isQName() {
		String typeName = this.typeName;
		return isQName(typeName);
	}

	private boolean isQName(String typeName) {
		return "QName".equals(typeName);
	}

	public String getTypeName() {
		return typeName;
	}

	public String getTypeNameFull() {
		String res = getTypeName();
		if((isLikeNCName() || isQName()) && res != null && !res.contains("::"))
		{
			return "Trentino::XML::Schema::" + res;
		}
		return res;
	}

	public void setTypeName(String typeName) {
		this.typeName = typeName;
	}

	public String[] getTypeParams() {
		return typeParams;
	}

	public void setTypeParams(String[] typeParams) {
		this.typeParams = typeParams;
	}

	public boolean isNcName() {
		return ncName;
	}

	public boolean isLikeNCName() {
		String typeName = this.typeName;
		return isLikeNCName(typeName);
	}

	private boolean isLikeNCName(String typeName) {
		return isNcName() || "NCName".equals(typeName) || "AnyURI".equals(typeName) || "Name".equals(typeName);
	}

	public void setNcName(boolean ncName) {
		this.ncName = ncName;
	}

	public void setName(String name) {
		this.name = name;
	}

	public void setAnyURI(boolean anyURI) {
		this.anyURI = anyURI;
	}

	public String getPlural() {
		if(isAttribute() && name.endsWith("s"))
		{
			return "";
		}
		return "s";
	}

	public int compareTo(FieldInfo o) {
		if(o == null)
		{
			return 1;
		}
		if(name == null)
		{
			return 1;
		}
		return name.compareTo(o.name);
	}

	public boolean firstLikeString() {
		if(typeParams == null || typeParams.length == 0)
		{
			return false;
		}
		String val = typeParams[0];
		return STD_STRING.equals(val) || "AnyURI".equalsIgnoreCase(val) || "NCName".equalsIgnoreCase(val);
	}

}
