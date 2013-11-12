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
package org.trentino.trengen.tools.generation.bindingsca;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.Contract;
import org.trentino.trengen.tools.bindingsca.TIDLInterfaceModel;
import org.trentino.trengen.tools.bindingsca.TIDLType;
import org.trentino.trengen.tools.generation.Context;
import org.trentino.trengen.tools.generation.proxieswrappers.ReferenceServiceInterface;

/**
 * contains input data needed by the generator
 */
public class ContextCppInterface extends Context implements Comparable<ContextCppInterface> {

	public ContextCppInterface (TIDLInterfaceModel tidlInterfaceModel, File tidlPropertiesFile, File javaFile) {
		super();
		this.tidlInterfaceModel = tidlInterfaceModel;
		this.tidlPropertiesFile = tidlPropertiesFile;
		this.javaFile = javaFile;
		pbtmapper = new ProtobufTypeMapper(tidlInterfaceModel);
	}

	private File	                  outputDir;
	private TIDLInterfaceModel	      tidlInterfaceModel;
	private List<String>	          includes	= new ArrayList<String>();
	private File	                  tidlPropertiesFile;
	private File	                  javaFile;
	private ReferenceServiceInterface	referenceServiceInterface;

	public List<String> getIncludes() {
		return includes;
	}

	public TIDLInterfaceModel getTidlInterfaceModel() {
		return tidlInterfaceModel;
	}

	public void setTidlInterfaceModel(TIDLInterfaceModel tidlInterfaceModel) {
		this.tidlInterfaceModel = tidlInterfaceModel;
	}

	@Override
	public File getOutputDir() {
		return outputDir;
	}

	@Override
	public void setOutputDir(File outputDir) {
		this.outputDir = outputDir;
	}

	/**
	 * @return
	 */
	public String getFileName() {
		String prefix = null;
		if(getTidlPropertiesFile() != null)
		{
			prefix = getTidlPropertiesFile().getName();
			prefix = prefix.replaceFirst(".tidl.properties", "");
		}
		else
		{
			prefix = getJavaFile().getName();
			prefix = prefix.replaceFirst(".java", "");
		}

		return prefix;
	}

	/**
	 * return the name of the headerfile of this interface.
	 * The name of the header file is equals the name of tidl.properties file
	 * if a such file exists. Otherwise, it is the name of the java file without
	 * extension
	 * @return String
	 */
	public String getHeaderFilenamePrefix() {
		return getFileName();
	}

	public String getNamespace() {
		String name = tidlInterfaceModel.getQualifiedName();
		name = name.substring(0, name.lastIndexOf("."));
		name = name.replace('.', '_');
		return name;
	}

	public boolean hasInclude() {
		return includes.size() != 0;
	}

	public String getClassName() {
		return tidlInterfaceModel.getName();
	}

	public boolean hasBeanUtils() {
		return getTidlInterfaceModel().isUseComplexTypes();
	}

	/**
	 * @param tidl
	 */
	public void setTidlPropertiesFile(File tidl) {
		this.tidlPropertiesFile = tidl;

	}

	public File getTidlPropertiesFile() {
		return tidlPropertiesFile;
	}

	/**
	 * @return true if the corresponding cpp file of the generated cpp interface can be inlined in
	 *         the header file withoit causing any compilation error
	 */
	@Deprecated
	public boolean canInlineCppImplementation() {
		return true;
	}

	/**
	 * @param javaFile
	 */
	public void setJavaFile(File javaFile) {
		this.javaFile = javaFile;
	}

	public File getJavaFile() {
		return javaFile;
	}

	public boolean hasEnclosedNonEnumTypes() {
		for (TIDLType t : tidlInterfaceModel.getEnclosedClasses())
		{
			if(t.isEnclosed() && !t.isEnumeration())
			{
				return true;
			}
		}
		return false;
	}

	public boolean hasEnclosedTypes() {
		for (TIDLType t : tidlInterfaceModel.getEnclosedClasses())
		{
			if(t.isEnclosed())
			{
				return true;
			}
		}
		return false;
	}

	/**
	 * @param referenceServiceInterface
	 */
	public void setReferenceServiceInterface(ReferenceServiceInterface referenceServiceInterface) {
		this.referenceServiceInterface = referenceServiceInterface;
	}

	public ReferenceServiceInterface getReferenceServiceInterface() {
		return referenceServiceInterface;
	}

	public String getNameGeneratedFile() {
		if(referenceServiceInterface != null)
		{
			return referenceServiceInterface.getClassName();
		}
		return getFileName();
	}

	CppTypeMapper	tMapper	= new CppTypeMapper();

	public CppTypeMapper getTmapper() {
		return tMapper;
	}

	ProtobufTypeMapper	pbtmapper;

	public ProtobufTypeMapper getPbtmapper() {
		return pbtmapper;
	}

	public boolean isReference() {
		if(referenceServiceInterface == null)
		{
			throw new IllegalStateException("Referenceinterface should be define before call if this methid");
		}
		Contract c = referenceServiceInterface.getContract();
		return c instanceof ComponentReference;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if(!(obj instanceof ContextCppInterface))
		{
			return false;
		}
		ContextCppInterface other = (ContextCppInterface) obj;
		if(tidlInterfaceModel != null)
		{
			return tidlInterfaceModel.equals(other.tidlInterfaceModel);
		}
		if(referenceServiceInterface != null)
		{
			return referenceServiceInterface.equals(other.referenceServiceInterface);
		}
		return super.equals(obj);
	}

	public boolean hasBeanUtil() {
		return !tidlInterfaceModel.getAllComplexTypes().isEmpty();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		if(tidlInterfaceModel != null)
		{
			return tidlInterfaceModel.toString();
		}
		if(referenceServiceInterface != null)
		{
			return referenceServiceInterface.toString();
		}
		return super.toString();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Comparable#compareTo(java.lang.Object)
	 */
	@Override
	public int compareTo(ContextCppInterface o) {
		if(o == null)
		{
			return 1;
		}
		if(this.equals(o))
		{
			return 0;
		}
		if(tidlInterfaceModel != null && o.tidlInterfaceModel != null)
		{
			return tidlInterfaceModel.getQualifiedName().compareTo(o.tidlInterfaceModel.getQualifiedName());
		}
		if(referenceServiceInterface != null && o.referenceServiceInterface != null)
		{
			return referenceServiceInterface.toString().compareTo(o.referenceServiceInterface.toString());
		}
		return -1;
	}
}
