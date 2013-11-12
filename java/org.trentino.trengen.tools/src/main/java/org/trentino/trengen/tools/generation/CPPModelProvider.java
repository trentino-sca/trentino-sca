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
package org.trentino.trengen.tools.generation;

import javax.xml.bind.JAXBElement;

import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.sca.model.CPPInterface;
import org.trentino.trengen.sca.model.Contract;
import org.trentino.trengen.sca.model.Interface;
import org.trentino.trengen.tools.scavalidation.DirectoryScanner;
import org.trentino.trengen.tools.scavalidation.IConformanceManagerCppImpArtifacts;
import org.trentino.trengen.tools.trengen.Trengen;

/**
 * @author z002ttbb
 */
public class CPPModelProvider {

	private IConformanceManagerCppImpArtifacts	conformanceManagerCppImplArtifacts;

	/**
	 * @param conformanceManagerCppImplArtifacts
	 */
	public CPPModelProvider (IConformanceManagerCppImpArtifacts conformanceManagerCppImplArtifacts) {
		this.conformanceManagerCppImplArtifacts = conformanceManagerCppImplArtifacts;
	}

	/**
	 * @param service
	 * @return
	 */
	public ClassModel getClassModel(Contract contract) {
		return getClassModelFromConformanceManagerCppImplArtifacts(contract);
	}

	private ClassModel getClassModelFromConformanceManagerCppImplArtifacts(Contract contract) {
		JAXBElement<? extends Interface> itf = contract.getInterface();
		if(itf == null || itf.isNil())
		{
			return null;
		}
		Interface itfValue = itf.getValue();
		if(itfValue instanceof CPPInterface)
		{
			CPPInterface cppInterface = (CPPInterface) itfValue;
			String fullHeaderPath = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), cppInterface.getHeader());
			if(fullHeaderPath != null)
			{
				ClassModel classModel = conformanceManagerCppImplArtifacts.getClassModelForInterface(cppInterface,
				        conformanceManagerCppImplArtifacts.GetHeaderFile(fullHeaderPath));
				return classModel;
			}
			else
			{
				return null;
			}
		}
		return null;
	}

}
