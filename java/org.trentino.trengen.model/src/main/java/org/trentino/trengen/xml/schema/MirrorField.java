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

package org.trentino.trengen.xml.schema;

import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.List;

/**
 * This is the class hosted in the field list of mirror classes
 * members of the mirrorfield are set once getFields function of the
 * mirrorclass object is called.
 */
public class MirrorField {

	private List<MirrorClass>	listItems	= new ArrayList<MirrorClass>();
	private MirrorClass	      mirrorObject;
	private boolean	          simple;
	private boolean	          list;
	private Object	          value;
	private String	          accessor;
	private String	          name;
	private String	          argument;
	private String	          type;

	public String getArgument() {
		String argumentReturn = new String(argument);
		if(argumentReturn.startsWith("mIs"))
		{
			argumentReturn = argumentReturn.substring(3);
		}
		else if(argumentReturn.startsWith("m"))
		{
			argumentReturn = argumentReturn.substring(1);
		}

		if(argumentReturn.trim().equals("Element"))
		{
			return argumentReturn;
		}

		return argumentReturn.replace("Element", "");
	}

	public void setArgument(String argument) {
		this.argument = argument;
	}

	public boolean isSimple() {
		return simple;
	}

	public boolean isList() {
		return list;
	}

	public List<MirrorClass> getListItems() {
		return listItems;
	}

	public void setListItems(Object object) {
		if(object instanceof List<?>)
		{
			this.listItems = (List<MirrorClass>) object;
		}
	}

	public MirrorClass getMirrorObject() {
		return mirrorObject;
	}

	public void setSimple(boolean b) {
		simple = b;

	}

	public void setList(boolean b) {
		list = b;
	}

	public boolean isComplexNotList() {
		return !isSimple() && !isList();
	}

	public void setMirrorObject(java.lang.Object object) {
		mirrorObject = (MirrorClass) object;
	}

	public String getValue() {
		if((value instanceof NCName) || (value instanceof String) || (value instanceof Name) || (value instanceof AnyURI))
		{
			return "\"" + value.toString() + "\"";
		}
		else if(value instanceof ArrayList)
		{
			String returnVal = value.toString();
			returnVal = returnVal.substring(1, returnVal.length() - 1);
			returnVal = "\"" + returnVal + "\"";
			return returnVal;
		}
		else
		{
			return value.toString();
		}
	}

	public void setValue(Object val) {
		value = val;

	}

	public String getName() {
		name = name.replace(".", "");
		name = name.replace("/", "");
		name = name.replace("\\", "");
		return name;
	}

	public void setName(String nameGiven) {
		name = nameGiven;
	}

	public void setAccessor(String acc) {
		accessor = acc;
	}

	public String getAccessor() {
		if(accessor.endsWith("Elements"))
		{
			accessor = accessor.replace("Elements", "");
			accessor = "add" + accessor.substring(0, 1).toUpperCase() + accessor.substring(1) + "Element";
		}
		else if(accessor.endsWith("s"))
		{
			accessor = accessor.substring(0, accessor.length() - 1); // delete last plural "s"
			accessor = "add" + accessor.substring(0, 1).toUpperCase() + accessor.substring(1);
		}
		if(accessor.equals("content"))
		{
			accessor = accessor.replace("content", "addContentElement");
		}
		return accessor;
	}

	public String getType() {
		return type;
	}

	public void setType(Type typeGiven) {
		// System.out.println("HeresetType-42" + typeGiven.toString());
		ParameterizedType stringListType = null;
		try
		{
			stringListType = (ParameterizedType) typeGiven;

			// System.out.println("HeresetType-43");
			Class<?> stringListClass = (Class<?>) stringListType.getActualTypeArguments()[0];
			// System.out.println("HeresetType-44");
			/*
			 * if(stringListClass == null)
			 * {
			 * }
			 */
			type = stringListClass.toString();
			// System.out.println("HeresetType-43" + type);
		} catch (Exception e)
		{
			// System.out.println("HeresetType-42-xxx");
			type = "xxx";
		}

		// System.out.println(stringListClass); // class java.lang.String.
	}
}
