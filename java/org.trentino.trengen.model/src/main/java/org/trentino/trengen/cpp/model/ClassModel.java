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

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class ClassModel {
	private String	          className;
	private String	          namespace;

	private List<ClassMember>	members	  = new ArrayList<ClassMember>();
	private List<ClassMethod>	methods	  = new ArrayList<ClassMethod>();
	private List<String>	  baseClasses	= new ArrayList<String>();
  
	private List<ClassModel>  baseClassesResolved = new ArrayList<ClassModel>();
	public String getClazzName() {
		return className;
	}

	public void setClassName(String className) {
		this.className = className;
	}

	public String getNamespace() {
		return namespace;
	}
	
	public String getFullQualifiedClassName(){
		String res = namespace!=null && namespace.length() >0?namespace+"::":"";
		return res+className;
	}

	public void setNamespace(String namespace) {
		this.namespace = namespace;
	}

	public List<ClassMember> getMembers() {
		return members;
	}

	public void setMembers(List<ClassMember> members) {
		this.members = members;
	}

	public List<ClassMethod> getMethods() {
		return methods;
	}


	public List<String> getBaseClasses() {
		return baseClasses;
	}

	public void setBaseClasses(List<String> baseClasses) {
		this.baseClasses = baseClasses;
	}

	public String getNamespaceAsPath() {
		if(namespace == null)
		{
			return null;
		}
		String res = namespace.replace('.', File.separatorChar);
		res = res.replace("::", "" + File.separatorChar);
		return res;
	}

	@Override
	public String toString() {
		return namespace + "::" + className;
	}
}
