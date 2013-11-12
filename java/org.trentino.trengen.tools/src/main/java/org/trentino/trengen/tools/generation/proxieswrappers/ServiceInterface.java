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
import java.util.List;

// This class is generated for all the services of components and componentTypes
public class ServiceInterface {
	// interface.cpp/@class if @class is not available since it is optional,
	// name is processed
	// according to the iinterface.cpp/@header
	private String	              interfaceClassName;

	// This info is gathered by parsing the header of interface, the namespace
	// hierarchy of
	// the class is reflected by using '_' between the namespaces
	private String	              interfaceClassNamespaces;

	// This info is gathered by parsing the header of interface, the namespace
	// hierarchy of
	// the class is reflected by using '::' between the namespaces
	private String	              interfaceClassNamespacesSemicolonSeperated;

	private List<InterfaceMethod>	interfaceMethods	= new ArrayList<InterfaceMethod>();

	private String	              interfaceHeader;

	public String getInterfaceClassName() {
		return interfaceClassName;
	}

	void setInterfaceClassName(String interfaceClassName) {
		this.interfaceClassName = interfaceClassName;
	}

	public String getInterfaceClassNamespaces() {
		return interfaceClassNamespaces;
	}

	void setInterfaceClassNamespaces(String interfaceClassNamespaces) {
		this.interfaceClassNamespaces = interfaceClassNamespaces;
	}

	public List<InterfaceMethod> getInterfaceMethods() {
		return interfaceMethods;
	}

	public void setInterfaceMethods(List<InterfaceMethod> interfaceMethods) {
		this.interfaceMethods = interfaceMethods;
	}

	public String getInterfaceClassNamespacesSemicolonSeperated() {
		return interfaceClassNamespacesSemicolonSeperated;
	}

	public void setInterfaceClassNamespacesSemicolonSeperated(String interfaceClassNamespacesSemicolonSeperated) {
		this.interfaceClassNamespacesSemicolonSeperated = interfaceClassNamespacesSemicolonSeperated;
	}

	public String getInterfaceHeader() {
		return interfaceHeader;
	}

	public void setInterfaceHeader(String interfaceHeader) {
		this.interfaceHeader = interfaceHeader;
	}
}
