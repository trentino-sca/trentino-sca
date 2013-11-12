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

import java.util.ArrayList;
import java.util.List;

/**
 * Represent a class method from a class in a header file
 * 
 * @author z002ttbb
 */
public class ClassMethod {
	public ClassMethod() {
		name = null;
		returnType = null;
	}

	public ClassMethod(String name, String returnType) {
		super();
		this.name = name;
		this.returnType = returnType;
	}

	private String name;
	private boolean pureVirtual;
	private String attribute;
	private String access;
	private String returnType;
	private List<ClassMethodArgument> arguments = new ArrayList<ClassMethodArgument>();

	public String getAccess() {
		return access;
	}

	public void setAccess(String access) {
		this.access = access;
	}

	public boolean isPureVirtual() {
		return pureVirtual;
	}

	public void setPureVirtual(boolean pureVirtual) {
		this.pureVirtual = pureVirtual;
	}

	public String getAttribute() {
		return attribute;
	}

	public void setAttribute(String attribute) {
		this.attribute = attribute;
	}

	/**
	 * Spec_cpp lines 1375 to 1376 Annotation on service implementation class or
	 * method to indicate that a service or method allows pass by reference
	 * semantics.
	 */
	private boolean allowsPassByReference = false;
	/**
	 * See SPEC_CPP lines 1302 to 1316
	 */
	private boolean endConversation = false;
	private boolean oneWay = false;

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getReturnType() {
		return returnType;
	}

	public void setReturnType(String returnType) {
		this.returnType = returnType;
	}

	public List<ClassMethodArgument> getArguments() {
		return arguments;
	}

	public void setArguments(List<ClassMethodArgument> arguments) {
		this.arguments = arguments;
	}

	public boolean isAllowsPassByReference() {
		return allowsPassByReference;
	}

	public void setAllowsPassByReference(boolean allowsPassByReference) {
		this.allowsPassByReference = allowsPassByReference;
	}

	public boolean isEndConversation() {
		return endConversation;
	}

	public void setEndConversation(boolean endConversation) {
		this.endConversation = endConversation;
	}

	public boolean isOneWay() {
		return oneWay;
	}

	public void setOneWay(boolean oneWay) {
		this.oneWay = oneWay;
	}

	@Override
	public String toString() {
		return returnType + " " + name + "(" + arguments.toString() + ")";
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if (obj == null || !(obj instanceof ClassMethod)) {
			return false;
		}
		ClassMethod other = (ClassMethod) obj;
		if(!this.name.equals(other.name)){
			return false;
		}
		int len = arguments.size();
		if(len !=other.arguments.size()){
			return false;
		}
		for(int i=0; i<len;i++){
			ClassMethodArgument arg1= arguments.get(i);
			ClassMethodArgument arg2= other.arguments.get(i);
			if(!arg1.getType().equals(arg2.getType())){
				return false;
			}
		}
		return true;
	}
}
