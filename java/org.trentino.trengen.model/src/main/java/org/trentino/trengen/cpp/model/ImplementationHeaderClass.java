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

public class ImplementationHeaderClass extends ClassModel {
	private boolean	componentType;

	public boolean isComponentType() {
		return componentType;
	}

	public void setComponentType(boolean componentType) {
		this.componentType = componentType;
	}

	private ScopeType	scope	            = ScopeType.stateless;

	private boolean	  eagerInit	            = false;
	/**
	 * Spec_cpp lines 1375 to 1376
	 * Annotation on service implementation class or method to indicate that a service or method allows
	 * pass by reference semantics.
	 */
	private boolean	  allowsPassByReference	= false;

	public ScopeType getScope() {
		return scope;
	}

	public void setScope(ScopeType scope) {
		this.scope = scope;
	}

	public boolean isEagerInit() {
		return eagerInit;
	}

	public void setEagerInit(boolean eagerInit) {
		this.eagerInit = eagerInit;
	}

	public boolean isAllowsPassByReference() {
		return allowsPassByReference;
	}

	public void setAllowsPassByReference(boolean allowsPassByReference) {
		this.allowsPassByReference = allowsPassByReference;
	}

}
