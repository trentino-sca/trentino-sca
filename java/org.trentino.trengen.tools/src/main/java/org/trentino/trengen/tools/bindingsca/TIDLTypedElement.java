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
package org.trentino.trengen.tools.bindingsca;

import javax.lang.model.element.Element;

import org.trentino.trengen.tools.generation.bindingsca.CppTypeMapper;

/**
 * @author z002ttbb
 */
public class TIDLTypedElement<T extends Element> extends TIDLNamedElement {

	private TIDLType	type;
	private String className;
	
	public String getClassName() {
		CppTypeMapper mapper= new CppTypeMapper();
		String typeStr = mapper.name(type);
		int indx = typeStr.lastIndexOf(":");
		className = typeStr.substring(indx+1);
		return className;
	}


	/**
	 * @param typeObj
	 */
	public void setType(TIDLType typeObj) {
		this.type = typeObj;

	}


	public TIDLType getType() {
		return type;
	}



	private T	typeElement;

	public T getTypeElement() {
		return typeElement;
	}

	/**
	 * @param param
	 */
	public void setTypeElement(T param) {
		typeElement = param;
	}

}