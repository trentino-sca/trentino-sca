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

import java.io.File;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

import javax.annotation.processing.ProcessingEnvironment;
import javax.lang.model.element.TypeElement;

/**
 * This class holds all necessary informations for the mapping
 * to JAVA. The class is filled during processing, until the processing
 * is over.
 */
public class Context {

	private final ProcessingEnvironment	processingEnv;
	private Map<String, TypeElement>	pojosToProcess	= new HashMap<String, TypeElement>();
	private File	                    outputDir	   = new File(".\\target\\generated-sources");
	private Set<ClassInfo>	            classes;

	public Context (ProcessingEnvironment processingEnv) {
		this.processingEnv = processingEnv;
		Map<String, String> options = this.processingEnv.getOptions();
		if(options == null || !options.containsKey("outputDirectory"))
		{
			outputDir = new File(".\\target\\generated-sources");
		}
		else
		{
			outputDir = new File(options.get("outputDirectory"));
		}
	}

	/**
	 * @return the list of Pojos to process
	 */
	public Map<String, TypeElement> getPojosToProcess() {

		return pojosToProcess;
	}

	/**
	 * Annotation processing environment.
	 * @return
	 */

	public ProcessingEnvironment getProcessingEnv() {
		return processingEnv;
	}

	/**
	 * output directory of generated artifacts
	 * @return
	 */
	public File getOutputDir() {
		return outputDir;
	}

	/**
	 * main model used to generate objects.
	 * @param classes
	 */
	public void setClasses(Set<ClassInfo> classes) {
		this.classes = classes;
	}

	public Set<ClassInfo> getClasses() {
		return classes;
	}

	public boolean isExtentionPoint(String typeName) {
		ClassInfo info = BuilderUtil.getClassInfoByClassName(typeName, classes);
		if(info == null)
		{
			return false;
		}
		boolean value = info.isExtentionPoint();
		return value;
	}

	/**
	 * Only call this when you are sure that the class exists
	 * @param typeName
	 * @return
	 */
	public ClassInfo getClassInfo(String typeName) {
		ClassInfo info = BuilderUtil.getClassInfoByClassName(typeName, classes);
		return info;
	}

}
