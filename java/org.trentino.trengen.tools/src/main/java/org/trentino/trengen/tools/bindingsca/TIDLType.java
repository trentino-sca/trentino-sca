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
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.lang.model.element.TypeElement;

import org.trentino.tidl.NumberType;
import org.trentino.tidl.PrimitiveType;

/**
 * @author z002ttbb
 */
public class TIDLType extends TIDLNamedElement implements Comparable<TIDLType>, TIDLTypeContainer {

	public static final TIDLType	VOID	  = new TIDLType() {
		                                          public String getName() {
			                                          return "void";
		                                          };

		                                          public String getQualifiedName() {
			                                          return getName();
		                                          };
	                                          };
	public static final TIDLType	NULLVALUE	= new TIDLType() {
		                                          public String getName() {
			                                          return "null";
		                                          };

		                                          public String getQualifiedName() {
			                                          return getName();
		                                          };
	                                          };
	private TypeElement	         typeElement;
	private String	             qualifiedName;
	private String               className;

	private List<TIDLFieldModel>	fields	  = new ArrayList<TIDLFieldModel>();
	private Set<TIDLType>	     declaredTypes;
	private Map<String, Boolean>	useType	  = new HashMap<String, Boolean>();
	private boolean	             enclosed	  = false;
	String	                     itfName	  = null;
	private boolean enumeration;
	

	public List<TIDLFieldModel> getFields() {
		return fields;
	}

	/**
	 * @param theType
	 */
	public void setTypeElement(TypeElement theType) {
		this.typeElement = theType;
	}

	/**
	 * @param qname
	 */
	public void setQualifiedName(String qname) {
		this.qualifiedName = qname;
	}

	public TypeElement getTypeElement() {
		return typeElement;
	}

	public String getQualifiedName() {
		return qualifiedName;
	}

	public String getNamespace() {
		if(qualifiedName == null)
		{
			return null;
		}
		String nameSpace = qualifiedName.substring(0, qualifiedName.lastIndexOf("."));
		return nameSpace.replace(".", "::");
	}
	
	public String getClassName() {
		if(qualifiedName == null)
		{
			return null;
		}
		className = qualifiedName.substring(qualifiedName.lastIndexOf("."), qualifiedName.length());
		return className.replace(".", "");
	}

	public boolean isPrimitive() {
		return !isVoid() && typeElement.getAnnotation(PrimitiveType.class) != null;
	}

	public boolean isType(String typeAlias) {
		// all primitive types apart of String
		if(typeAlias == null)
		{
			return false;
		}
		if(typeAlias.equalsIgnoreCase("int"))
		{
			return isPrimitive() && getName() != null && !getName().contains("TString") && !getName().contains("TBool")
			        && !getName().contains("TFloat");
		}
		if(typeAlias.equalsIgnoreCase("string"))
		{
			return isPrimitive() && getName() != null && getName().contains("TString");
		}
		return false;
	}

	/**
	 * @return
	 */
	public boolean useType(String typeAlias) {
		if(useType.get(typeAlias) != null)
		{
			return useType.get(typeAlias);
		}
		for (TIDLFieldModel field : fields)
		{
			TIDLType type = field.getType();
			if(type.isType(typeAlias))
			{
				useType.put(typeAlias, Boolean.TRUE);
				return true;
			}
			else if(type.getQualifiedName().equals(this.getQualifiedName())){
				//infinite loop
				continue;
			}
			else if(type.useType(typeAlias))
			{
				useType.put(typeAlias, Boolean.TRUE);
				return true;
			}
		}
		return false;
	}

	public boolean isComplexType() {
		return !isPrimitive() && !isVoid();
	}

	public boolean isVoid() {
		return this.equals(VOID);
	}

	/**
	 * @return
	 */
	private Set<TIDLType> getDeclaredTypes() {
		if(declaredTypes == null)
		{
			declaredTypes = new HashSet<TIDLType>();
			for (TIDLFieldModel field : fields)
			{
				TIDLType type = field.getType();
				if(type.isComplexType())
				{
					declaredTypes.add(type);
					declaredTypes.addAll(type.getDeclaredTypes());
				}
			}
		}
		return declaredTypes;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if(obj == null)
		{
			return false;
		}
		if(!(obj instanceof TIDLType))
		{
			return false;
		}
		if(this.qualifiedName == null)
		{
			return super.equals(obj);
		}
		return this.qualifiedName.equals(((TIDLType) obj).qualifiedName);

	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Comparable#compareTo(java.lang.Object)
	 */
	@Override
	public int compareTo(TIDLType o) {
		if(o ==null){
			return 1;
		}
		if(this.equals(o)){
			return 0;
		}
		if(this.qualifiedName == null)
		{
			return -1;
		}
		if(hasFieldWithType(o)){
			return 1;
		}
		if(o.hasFieldWithType(this)){
			return -1;
		}
		return this.qualifiedName.compareTo(o.qualifiedName);
	}

	private boolean hasFieldWithType(TIDLType o) {
		for(TIDLFieldModel field : fields){
			TIDLType fType = field.getType();
			if(fType.equals(this)){
				continue;
			}
			if(fType.equals(o)){
				return true;
			}
			if(fType.hasFieldWithType(o)){
				return true;
			}
			
		}
		return false;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return getQualifiedName();
	}

	/**
	 * @param b
	 */
	public void setEnclosed(boolean b) {
		enclosed = b;
	}

	public boolean isEnclosed() {
		return enclosed;
	}


	/**
     * @return
     */
    public boolean isNumber() {
	   return typeElement.getAnnotation(NumberType.class) != null;
    }

	/**
     * @param b
     */
    public void setEnumeration(boolean b) {
	    enumeration = true;
	    
    }

	public boolean isEnumeration() {
    	return enumeration;
    }

	private TIDLTypeContainerSupport tIDLTypeContainerSupport = new TIDLTypeContainerSupport();
	private TIDLType enclosingClass;
	private boolean directlyEnclosedinModel;
	/* (non-Javadoc)
     * @see org.trentino.trengen.tools.bindingsca.TIDLTypeContainer#getEnclosedClasses()
     */
    @Override
    public Set<TIDLType> getEnclosedClasses() {
	    return tIDLTypeContainerSupport.getEnclosedClasses();
    }

	/**
     * @param ns
     * @return
     */
    public boolean isEnclosedIn(String ns) {
	    return ns!=null && this.getNamespace().startsWith(ns);
    }
    
    public boolean hasEnclosedClasses(){
    	return getEnclosedClasses().size() >0;
    }

	/**
     * @return
     */
    public TIDLType getEnclosingClass() {
	    return enclosingClass;
    }

	public void setEnclosingClass(TIDLType enclosingClass) {
    	this.enclosingClass = enclosingClass;
    }

	/**
     * @param b
     */
    public void setDirectlyEnclosedinModel(boolean b) {
    	directlyEnclosedinModel = b;
    }

	public boolean isDirectlyEnclosedinModel() {
    	return directlyEnclosedinModel;
    }

}
