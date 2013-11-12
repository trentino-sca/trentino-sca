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

import java.util.ArrayList;
import java.util.List;

import javax.lang.model.element.ExecutableElement;

/**
 * @author z002ttbb
 */
public class TIDLFunctionModel {
	private String	                 name;

	private List<TIDLParameterModel>	arguments	    = new ArrayList<TIDLParameterModel>();
	private List<TIDLExceptionModel>	exceptions	    = new ArrayList<TIDLExceptionModel>();
	private List<TIDLParameterModel>	returnArguments	= null;

	private ExecutableElement	     typeElement;

	private TIDLType	             returnType;
	
	private String methodId;

	public List<TIDLParameterModel> getArguments() {
		return arguments;
	}

	public List<TIDLParameterModel> getReturnArguments() {
		if(returnArguments == null)
		{
			returnArguments = new ArrayList<TIDLParameterModel>();
			if(returnType != null && !returnType.isVoid())
			{
				TIDLParameterModel returnParamModel = new TIDLParameterModel();
				returnParamModel.setType(returnType);
				returnParamModel.setName(getName() + "Response_");
				returnArguments.add(returnParamModel);
			}
			for (TIDLParameterModel arg : arguments)
			{
				if(arg.isHasInOut() || arg.isHasOut())
				{
					returnArguments.add(arg);
				}
			}
		}
		return returnArguments;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	/**
	 * @param method
	 */
	public void setTypeElement(ExecutableElement method) {
		this.typeElement = method;
	}

	public ExecutableElement getTypeElement() {
		return typeElement;
	}

	/**
	 * @param void1
	 */
	public void setReturnType(TIDLType returnType) {
		this.returnType = returnType;
	}

	public TIDLType getReturnType() {
		return returnType;
	}

	public boolean isReturnTypeVoid() {
		return returnType == null || returnType.equals(TIDLType.VOID);
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if(name == null || !(obj instanceof TIDLFunctionModel))
		{
			return false;
		}
		TIDLFunctionModel obj2 = (TIDLFunctionModel) obj;
		if (!name.equals(obj2.name)){
			return false;
		}
		for(int i=0; i <arguments.size(); i++){
			TIDLType a1T = arguments.get(i).getType();
			TIDLType a2T = obj2.arguments.get(i).getType();
			if(!a1T.equals(a2T)){
				return false;
			}
		}
		return true;
		
	}

	/**
	 * @return
	 */
	public List<TIDLExceptionModel> getExceptions() {
		return exceptions;
	}

	/**
     * @return
     */
    public boolean isUseComplexTypes() {
	    if(returnType.isComplexType()){
	    	return true;
	    }
	    for(TIDLParameterModel arg : arguments){
	    	if(arg.getType().isComplexType()){
	    		return true;
	    	}
	    }
	    return false;
    }

	/**
     * @return the methodId
     */
    public String getMethodId() {
	    return methodId;
    }

	/**
     * @param methodId the methodId to set
     */
    public void setMethodId(String methodId) {
	    this.methodId = methodId;
    }

}
