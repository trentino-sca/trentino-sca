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

import org.trentino.trengen.cpp.model.ClassMethod;
import org.trentino.trengen.cpp.model.ClassMethodArgument;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.sca.model.CPPInterface;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentService;
import org.trentino.trengen.sca.model.Contract;

public class ReferenceServiceInterface implements Comparable<ReferenceServiceInterface>{

	private String	              host;

	private int	                  port;

	// interface.cpp/@class if @class is not available since it is optional,
	// name is processed
	// according to the iinterface.cpp/@header
	private String	              interfaceClassName;

	// This info is gathered by parsing the header of interface, the namespace
	// hierarchy of
	// the class is reflected by using '_' between the namespaces
	private String	              interfaceClassNamespaces;

	private String	              namespace;

	// This info is gathered by parsing the header of interface, the namespace
	// hierarchy of
	// the class is reflected by using '::' between the namespaces
	private String	              interfaceClassNamespacesSemicolonSeperated;

	private List<InterfaceMethod>	interfaceMethods	      = new ArrayList<InterfaceMethod>();

	private String	              interfaceHeader;

	private String	              rawNameSpaceSemicolonSeparated;

	private String	              namespaceUndescoreSeparated	= "";

	private CPPInterface	      cppInterface;

	private Contract	          contract;

	public String getReferenceName() {
		return contract.getName();
	}

	public String getHost() {
		return host;
	}

	public void setHost(String host) {
		this.host = host;
	}

	public String getPort() {
		return String.valueOf(port);
	}

	public int getPortInt() {
		return port;
	}

	public void setPort(int port) {
		this.port = port;
	}

	public String getNamespace() {
		return namespace;
	}

	public void setNamespace(String interfaceClassNamespace) {
		this.namespace = interfaceClassNamespace;
	}



	/**
	 * @param conformanceManagerCppImplArtifacts
	 * @param contract
	 * @param referenceInterface
	 */
	public ReferenceServiceInterface (ClassModel classModel, Contract contract) {
		CPPInterface cppInterface = (CPPInterface) contract.getInterface().getValue();
		this.cppInterface = cppInterface;
		this.contract = contract;
		String clazzName = cppInterface.getClazz();
		setInterfaceClassNamespacesSemicolonSeperated(clazzName);
		setInterfaceHeader(cppInterface.getHeader());

		String namespace = "";
		if(clazzName.contains("::"))
		{
			int index = clazzName.lastIndexOf("::");
			namespace = clazzName.substring(0, index);
		}
		setNamespace(namespace);
		String clazzNamespaces = clazzName.replace("::", "_");
		setInterfaceClassNamespaces(clazzNamespaces);

		int i = clazzName.lastIndexOf("::");
		String clazz = clazzName.substring(i + 2, clazzName.length());
		setInterfaceClassName(clazz);
		if(i > 0)
		{
			String namespaceVal = clazzName.substring(0, i);
			namespaceVal = namespaceVal.replace("::", "_");
			setNamespaceUndescoreSeparated(namespaceVal);
		}

		if(classModel != null)
		{
			this.setInterfaceMethods(getInterfaceMethods(classModel));
		}
	}

	/**
	 * Use This construction only for tests
	 */
	public ReferenceServiceInterface () {

	}

	/**
	 * The namespace of this service, separated by a ::
	 * @return
	 */
	public String getRawNameSpaceSemicolonSeparated() {
		return rawNameSpaceSemicolonSeparated;
	}

	public void setRawNameSpaceSemicolonSeparated(String rawNameSpaceSemicolonSeparated) {
		this.rawNameSpaceSemicolonSeparated = rawNameSpaceSemicolonSeparated;
	}

	public String getInterfaceClassName() {
		return interfaceClassName;
	}

	public void setInterfaceClassName(String interfaceClassName) {
		this.interfaceClassName = interfaceClassName;
	}

	public String getInterfaceClassNamespaces() {
		return interfaceClassNamespaces;
	}

	public void setInterfaceClassNamespaces(String interfaceClassNamespaces) {
		this.interfaceClassNamespaces = interfaceClassNamespaces;
	}

	public List<InterfaceMethod> getInterfaceMethods() {
		return interfaceMethods;
	}

	public void setInterfaceMethods(List<InterfaceMethod> interfaceMethods) {
		this.interfaceMethods = interfaceMethods;
	}

	public String getInterfaceHeader() {
		return interfaceHeader;
	}

	public void setInterfaceHeader(String interfaceHeader) {
		this.interfaceHeader = interfaceHeader;
	}

	public String getInterfaceClassNamespacesSemicolonSeperated() {
		return interfaceClassNamespacesSemicolonSeperated;
	}

	public String getClassName() {
		String className = interfaceClassNamespacesSemicolonSeperated.replace("::", "");
		return className;
	}

	public void setInterfaceClassNamespacesSemicolonSeperated(String interfaceClassNamespacesSemicolonSeperated) {
		this.interfaceClassNamespacesSemicolonSeperated = interfaceClassNamespacesSemicolonSeperated;
		if(interfaceClassNamespacesSemicolonSeperated != null && interfaceClassNamespacesSemicolonSeperated.lastIndexOf("::") > 0)
		{
			this.rawNameSpaceSemicolonSeparated = this.interfaceClassNamespacesSemicolonSeperated.substring(0,
			        this.interfaceClassNamespacesSemicolonSeperated.lastIndexOf("::"));
		}

	}

	public String getNamespaceUndescoreSeparated() {
		return namespaceUndescoreSeparated;
	}

	public void setNamespaceUndescoreSeparated(String namespaceVal) {
		namespaceUndescoreSeparated = namespaceVal;
	}


	private List<InterfaceMethod> getInterfaceMethods(ClassModel classModel) {
		List<InterfaceMethod> interfaceMethods = new ArrayList<InterfaceMethod>();
		List<ClassMethod> methods = classModel.getMethods();

		for (ClassMethod method : methods)
		{
			String methodRetType = "void";
			if(method.getReturnType() != null)
			{
				methodRetType = method.getReturnType();
			}
			methodRetType = methodRetType.trim();
			// if(methodRetType.equals(method.getReturnType()))
			// usingDirectivesMap.put(classModel.getNamespace(), "");

			InterfaceMethod m = new InterfaceMethod(method.getName(), methodRetType);
			List<ClassMethodArgument> args = method.getArguments();
			List<ClassMethodArgument> args2 = new ArrayList<ClassMethodArgument>(args);
			m.setArguments(args2);
			interfaceMethods.add(m);
		}
        InterfaceMethod.buildIds(classModel,interfaceMethods);
		return interfaceMethods;
	}

	public CPPInterface getCppInterface() {
		return cppInterface;
	}

	public void setCppInterface(CPPInterface cppInterface) {
		this.cppInterface = cppInterface;
	}

	public Contract getContract() {
		return contract;
	}

	public void setContract(Contract contract) {
		this.contract = contract;
	}
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
	    return getInterfaceClassName();
	}
	
	/* (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
	    if(!(obj instanceof ReferenceServiceInterface)){
	    	return false;
	    }
	    ReferenceServiceInterface obj2 = (ReferenceServiceInterface) obj;
	    if(this.cppInterface!=null){
	    	String clazz = cppInterface.getClazz();
	    	return clazz.equals(obj2.cppInterface.getClazz());
	    }
	    return super.equals(obj);
	}

	/* (non-Javadoc)
     * @see java.lang.Comparable#compareTo(java.lang.Object)
     */
    @Override
    public int compareTo(ReferenceServiceInterface o) {
	    if(o==null){
	    	return 1;
	    }
	    if(this.equals(o)){
	    	return 0;
	    }
	    String clazz = cppInterface.getClazz();
	    return clazz.compareTo(o.cppInterface.getClazz());
    }

}
