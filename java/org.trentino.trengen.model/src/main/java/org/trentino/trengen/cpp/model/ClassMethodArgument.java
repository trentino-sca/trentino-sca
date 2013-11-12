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

package org.trentino.trengen.cpp.model;

/**
 * @author z002ttbb
 *         An argument to a class method
 */
public class ClassMethodArgument {

	public ClassMethodArgument (String name, String type) {
		super();
		this.type = type;
		setName(name);
	}
	
	private static int genetaredNameCount =0;

	private String	name , type;

	public String getName() {
		return name;
	}

	public void setName(String name) {
		if(name ==null || name.length() ==0){
			this.name = "_trentino_generated_parameter_name_"+getTrimmedType()+"_"+(genetaredNameCount++);
			this.name = this.name.replaceAll("[*& :.]", "");
			return;
		}
		this.name = name;
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	@Override
	public String toString() {
		return type + " " + name;
	}

	public String getTrimmedType() {
		int index = type.lastIndexOf("::");
		if(index != -1)
		{
			String trimmed = type.substring(index + 2);
			return trimmed;
		}
		return type;
	}

	public String getBaseOfTrimmedType() {
		String base = getTrimmedType();
		base = base.replace("const ", "");
		base = base.replace("&", "");
		base = base.replace("*", "");
		return base;
	}

	public String getNamespace() {
		String typeTemp = type.replace("const ", "");
		typeTemp = typeTemp.replace("&", "");
		typeTemp = typeTemp.replace("*", "");
		int index = typeTemp.lastIndexOf("::");
		if(index != -1)
		{
			typeTemp = typeTemp.substring(0, index);
			typeTemp = typeTemp.trim();
			return typeTemp;
		}
		return "";
	}
	
	public boolean isConst(){
		return type.trim().startsWith("const ");
	}
}
