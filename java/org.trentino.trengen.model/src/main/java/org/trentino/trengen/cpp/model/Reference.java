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
 * 1.8.2.6. @Reference Annotation on a service implementation class data member
 * to define a reference of the service. Format: //
 * @Reference(name=�referenceName�, interfaceHeader=�LoanService.h�, //
 *                                  interfaceClass=�LoanService�,
 *                                  required=�true�) where � name (optional)
 *                                  specifies the name of the reference. If name
 *                                  is not specified the reference name is taken
 *                                  from the name of the following data member.
 *                                  � interfaceHeader (required) specifies the
 *                                  C++ header defining the interface for the
 *                                  reference. � interfaceClass (optional)
 *                                  specifies the C++ class defining the
 *                                  interface for the reference. If not
 *                                  specified the class is derived from the type
 *                                  of the annotated data member. � required
 *                                  (optional) specifies whether a value must be
 *                                  set for this reference. Default is true
 */
public class Reference {
	private String	name , interfaceHeader , interfaceClass;
	// Default is true
	private boolean	required	= true;

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getInterfaceHeader() {
		return interfaceHeader;
	}

	public void setInterfaceHeader(String interfaceHeader) {
		this.interfaceHeader = interfaceHeader;
	}

	public String getInterfaceClass() {
		return interfaceClass;
	}

	public void setInterfaceClass(String interfaceClass) {
		this.interfaceClass = interfaceClass;
	}

	public boolean isRequired() {
		return required;
	}

	public void setRequired(boolean required) {
		this.required = required;
	}

}
