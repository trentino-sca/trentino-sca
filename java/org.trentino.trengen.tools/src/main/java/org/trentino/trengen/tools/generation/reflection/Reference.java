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

public class Reference {
	private String	referenceName;	                            // the name of the reference of componentType
	private String	referenceInterfaceHeader;	                // the interface/@class : are
	                                                            // replaced with:: ???? what if
	                                                            // the class is not available
	                                                            // in the
	                                                            // interface???
	private String	referenceInterfaceClass;
	private String	nameGen;
	private String	interfaceClassNamespacesSemicolonSeperated;
	private boolean	multiplictyBiggerThanOne	= false;

	public String getNameGen() {
		return nameGen;
	}

	public void setNameGen(String nameGen) {
		this.nameGen = nameGen;
	}

	public String getInterfaceClassNamespacesSemicolonSeperated() {
		return interfaceClassNamespacesSemicolonSeperated;
	}

	public String getReferenceInterfaceClass() {
		return referenceInterfaceClass;
	}

	public void setReferenceInterfaceClass(String referenceInterfaceClass) {
		this.referenceInterfaceClass = referenceInterfaceClass;
	}

	public String getReferenceName() {
		return referenceName;
	}

	public void setReferenceName(String referenceName) {
		this.referenceName = referenceName;
	}

	public String getReferenceInterfaceHeader() {
		return referenceInterfaceHeader;
	}

	public void setReferenceInterfaceHeader(String referenceInterfaceHeader) {
		this.referenceInterfaceHeader = referenceInterfaceHeader;
	}

	public void setInterfaceClassNamespacesSemicolonSeperated(String className) {
		this.interfaceClassNamespacesSemicolonSeperated = className;
	}

	public boolean isMultiplictyBiggerThanOne() {
		return multiplictyBiggerThanOne;
	}

	public void setMultiplictyBiggerThanOne(boolean multiplictyBiggerThanOne) {
		this.multiplictyBiggerThanOne = multiplictyBiggerThanOne;
	}

}
