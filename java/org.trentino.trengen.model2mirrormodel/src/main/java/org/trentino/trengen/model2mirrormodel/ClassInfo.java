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

import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

/**
 * hold data needed to generated a Cpp class from the Java annotations
 */
public class ClassInfo implements Comparable<ClassInfo> {

	private static final String	OBJECT	              = "Object";

	private static String[]	    EXTENTIONPOINTCLASSES	=
	                                                  { "Binding", "Implementation", "Import", "Interface" };
	/**
	 * the name of the class
	 */
	private String	            name;

	/**
	 * The super class of this class. Null if the super class is Object
	 */
	private ClassInfo	        superClass;

	private Set<FieldInfo>	    fieldInfos	          = new TreeSet<FieldInfo>();

	private boolean	            eNum	              = false;

	/**
	 * value is initialized in the hasElement() method
	 */
	private Boolean	            hasElement	          = null;

	/**
	 * value is initialized in the hasElement method
	 */
	private Boolean	            hasAttribute	      = null;

	/**
	 * True if the class has a field that is a list. Initialized in the
	 * hasElement method
	 */
	private Boolean	            hasJavaList	          = null;

	private boolean	            abstractClass;

	private Set<ClassInfo>	    subClasses	          = new HashSet<ClassInfo>();

	public ClassInfo (String name) {
		this.name = name;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public ClassInfo getSuperClass() {
		return superClass;
	}

	public void setSuperClass(ClassInfo superClass) {
		this.superClass = superClass;
		if(superClass != null)
		{
			superClass.getSubClasses().add(this);
		}
	}

	/**
	 * @return
	 */
	public Set<ClassInfo> getSubClasses() {
		return subClasses;
	}

	public void addField(FieldInfo fInfo) {
		fieldInfos.add(fInfo);
	}

	public Set<FieldInfo> getFieldInfos() {
		return fieldInfos;
	}

	public void setFieldInfos(Set<FieldInfo> fieldInfos) {
		this.fieldInfos = fieldInfos;
	}

	@Override
	public String toString() {
		StringBuffer buf = new StringBuffer();
		buf.append("class ").append(name);
		if(superClass != null)
		{
			buf.append(" extends ").append(superClass.name);
		}
		buf.append(" { \n");
		for (FieldInfo fieldInfo : getFieldInfos())
		{
			buf.append(fieldInfo.toString());
		}
		buf.append("}\n");
		return buf.toString();
	}

	public void setEnum(boolean b) {
		this.eNum = b;
	}

	/**
	 * return true if this Classinfo is an enum type
	 */
	public boolean isEnum() {
		return eNum;
	}

	public boolean hasSuperclass() {
		return superClass != null && !OBJECT.equals(superClass.name);
	}

	/**
	 * return true if this class has an element Used by the freemarker template
	 */
	public boolean hasElements() {
		initFields();
		return hasElement.booleanValue();
	}

	public void initFields() {
		if(hasElement == null || hasJavaList == null || hasAttribute == null)
		{
			hasElement = Boolean.FALSE;
			hasAttribute = Boolean.FALSE;
			hasJavaList = Boolean.FALSE;
			for (FieldInfo f : getFieldInfos())
			{
				if(f.isElement())
				{
					hasElement = Boolean.TRUE;
				}
				if(f.isAttribute())
				{
					hasAttribute = Boolean.TRUE;
				}
				if(f.isList())
				{
					hasJavaList = Boolean.TRUE;
				}
			}
		}
	}

	/**
	 * return true if this class has at least one element
	 */
	public boolean hasAttributes() {
		initFields();
		// Value is initialized in the hasElement method
		return hasAttribute.booleanValue();
	}

	/**
	 * return true if this class has at leat one element or one attribute
	 */
	public boolean hasData() {
		return hasElements() || hasAttributes();
	}

	/**
	 * true if the class has getter and setters
	 */
	public boolean hasAccessors() {
		return hasData();
	}

	public boolean hasJavaList() {
		initFields();
		return hasJavaList.booleanValue();
	}

	public boolean hasSpecificTypes() {
		return true;
	}

	public int compareTo(ClassInfo o) {
		if(o == null)
		{
			return 1;
		}
		if(name == null && o.name == null)
		{
			return 0;
		}
		return name.compareTo(o.name);
	}

	public boolean isAbstractClass() {
		return abstractClass;
	}

	public void setAbstractClass(boolean abstractClass) {
		this.abstractClass = abstractClass;
	}

	public boolean isExtentionPoint() {

		for (String point : EXTENTIONPOINTCLASSES)
		{
			if(point.equals(this.name))
			{
				return true;
			}
		}
		return false;
	}

	public boolean isSubClassOfExtentionPoint() {
		if(getSuperClass() == null)
		{
			return false;
		}
		return getSuperClass().isExtentionPoint();
	}

}
