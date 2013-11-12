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
package org.trentino.trengen.tools.generation.reflection;

import java.util.ArrayList;
import java.util.List;

import org.trentino.trengen.sca.model.CPPImplementationFunction;
import org.trentino.trengen.sca.model.Implementation;
import org.trentino.trengen.tools.generation.ImplementationUtils;

public class ReflectionObject {
	private String	            implHeader;	                                  // returns the implementation.cpp/@header
	private String	            implClass;	                                      // returns the implementation.cpp/@class by
	                                                                              // replacing the : with _
	private String	            implClassWithNamespaces;
	private String	            implClassAsNamespace;	                          // returns the
	                                                                              // implementation.cpp/@class by
	                                                                              // replacing the : with ::
	private List<Service>	    listServices	= new ArrayList<Service>();	  // list of
	                                                                              // services
	                                                                              // of
	                                                                              // componentType
	                                                                              // (name of
	                                                                              // service
	                                                                              // and
	                                                                              // interface
	                                                                              // class
	                                                                              // is
	                                                                              // included)
	private List<Reference>	    listReferences	= new ArrayList<Reference>();	  // list
	                                                                              // of
	                                                                              // services
	                                                                              // of
	                                                                              // componentType
	                                                                              // (name
	                                                                              // of
	                                                                              // service
	                                                                              // and
	                                                                              // interface
	                                                                              // class
	                                                                              // is
	                                                                              // included)
	private List<PropertyReflx>	listProperties	= new ArrayList<PropertyReflx>(); // list
	                                                                              // of
	                                                                              // services
	                                                                              // of
	                                                                              // componentType
	                                                                              // (name
	                                                                              // of
	                                                                              // service
	                                                                              // and
	                                                                              // interface
	                                                                              // class
	// is included)

	/**
	 * store lifecycleMethods or methods used for special purpose
	 */
	private Implementation	    implementation;

	public String getImplClassWithNamespaces() {
		return implClassWithNamespaces;
	}

	public void setImplClassWithNamespaces(String implClassWithNamespaces) {
		this.implClassWithNamespaces = implClassWithNamespaces;
	}

	public String getImplHeader() {
		return implHeader;
	}

	public void setImplHeader(String implHeader) {
		this.implHeader = implHeader;
	}

	public String getImplClass() {
		return implClass;
	}

	public void setImplClass(String implClass) {
		this.implClass = implClass;
	}

	public List<Reference> getListReferences() {
		return listReferences;
	}

	public void setListReferences(List<Reference> listReferences) {
		this.listReferences = listReferences;
	}

	public List<Service> getListServices() {
		return listServices;
	}

	public void setListServices(List<Service> listServices) {
		this.listServices = listServices;
	}

	public void setListProperties(List<PropertyReflx> listProperties) {
		this.listProperties = listProperties;
	}

	public String getImplClassAsNamespace() {
		return implClassAsNamespace;
	}

	public void setImplClassAsNamespace(String implClassAsNamespace) {
		this.implClassAsNamespace = implClassAsNamespace;
	}

	public List<PropertyReflx> getListProperties() {
		return listProperties;
	}

	public List<CPPImplementationFunction> getListCPPImplementationFunction() {
		return ImplementationUtils.getListCPPImplementationFunction(implementation);
	}

	/**
	 * @param impl
	 */
	public void setImplementation(Implementation impl) {
		this.implementation = impl;
	}

	public boolean isInitMethod(CPPImplementationFunction aFunction) {
		if(aFunction == null)
		{
			return false;
		}
		return Boolean.TRUE.equals(aFunction.isInit());
	}

	public boolean isDestroyMethod(CPPImplementationFunction aFunction) {
		if(aFunction == null)
		{
			return false;
		}
		return Boolean.TRUE.equals(aFunction.isDestroy());
	}

}
