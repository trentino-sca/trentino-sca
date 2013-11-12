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
package org.trentino.trengen.tools.generation.proxieswrappers;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.regex.Pattern;

import org.trentino.trengen.cpp.model.ClassMethodArgument;
import org.trentino.trengen.cpp.model.ClassModel;

public class InterfaceMethod {
	public InterfaceMethod (String name, String returnType) {
		this.name = name;
		this.returnType = returnType;
	}

	private String	                  name;
	private String	                  returnType;
	private List<ClassMethodArgument>	arguments	= new ArrayList<ClassMethodArgument>();
	private String id;

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

	public String getTrimmedReturnType() {
		int index = returnType.lastIndexOf("::");
		if(index != -1)
		{
			String trimmed = returnType.substring(index + 2);
			return trimmed;
		}
		return returnType;
	}

	public String getNamespaceOfReturnType() {
		int index = returnType.lastIndexOf("::");
		if(index != -1)
		{
			String namespace = returnType.substring(0, index);
			return namespace;
		}
		return returnType;
	}

	public boolean isReturnTypeSimple() {
		List<String> cppPrimitiveTypes = new ArrayList<String>();

		cppPrimitiveTypes.add("tuint32_t");
		cppPrimitiveTypes.add("tint32_t");
		cppPrimitiveTypes.add("tint64_t");
		cppPrimitiveTypes.add("tuint64_t");
		cppPrimitiveTypes.add("double");
		cppPrimitiveTypes.add("float");
		cppPrimitiveTypes.add("std::string");
		cppPrimitiveTypes.add("bool");
		cppPrimitiveTypes.add("void");

		if(cppPrimitiveTypes.contains(getTrimmedReturnType()))
		{
			return true;
		}
		return false;
	}
	
	
	public void setId(String id){
		this.id = id;
	}
	
	public String getId(){
		if(id==null){
			return getName();
		}
		return id;
	}


	/**
	 * Build the ids of a method.
	 * Id is needed since the name of a method does not uniquely indentify the method.
	 * The Id is build based on the following algorithm
	 * <ul>If the method is unique, then the id is the method name</ul>
	 * <ul>If the method is overloaded, then the id is the method name plus underscore, followoed by
	 * a hashcode of the parameters types concatened.  
     * @param classModel
     * @param interfaceMethods
     */
    public static void buildIds(ClassModel classModel, List<InterfaceMethod> interfaceMethods) {
    	Map<String,List<InterfaceMethod>> methodsParName = groupMethodByName(classModel, interfaceMethods);
    	
	    for(Entry<String, List<InterfaceMethod>> entry : methodsParName.entrySet()){
	    	List<InterfaceMethod> value = entry.getValue();
	    	if(value.size()==1){
	    		value.get(0).setId(entry.getKey());
	    		continue;
	    	}
	    	for(InterfaceMethod method : value){
	    		String id = method.buildId();
	    		method.setId(id);
	    	}
	    }
	    
    }


	/**
     * @return
     */
    private String buildId() {
	    StringBuffer buf = new StringBuffer();
	    for(ClassMethodArgument arg : arguments){
	    	String type = arg.getType();
	    	buf.append(type);
	    }
	    String val = buf.toString();
	    val = val.replaceAll("[ &\\*:\\.<>\\(\\),]*", "");
	    return getName()+"_"+val;
    }


	/**
     * @param classModel
     * @param interfaceMethods
     * @return
     */
    private static Map<String, List<InterfaceMethod>> groupMethodByName(ClassModel classModel, List<InterfaceMethod> interfaceMethods) {
    	Map<String,List<InterfaceMethod>> methodsByName =	new HashMap<String,List<InterfaceMethod>>();
    	for(InterfaceMethod method : interfaceMethods){
    		List<InterfaceMethod> list = methodsByName.get(method.getName());
    		if(list ==null){
    			list = new ArrayList<InterfaceMethod>();
    			methodsByName.put(method.getName(), list);
    		}
    		list.add(method);
    	}
	    return methodsByName;
    }
}
