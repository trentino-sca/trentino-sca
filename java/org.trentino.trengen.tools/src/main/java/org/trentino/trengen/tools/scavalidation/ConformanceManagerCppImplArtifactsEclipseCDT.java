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

package org.trentino.trengen.tools.scavalidation;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import org.apache.log4j.Logger;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.cpp.model.HeaderFile;
import org.trentino.trengen.cpp.parser.eclipse.EclipseCPPParser;
import org.trentino.trengen.tools.trengen.Trengen;

/**
 * Cpp artifact related conformance items checks are done in this class For
 * example -->Relationship (being superset, subset or same) between interfaces
 * of services and references. -->implementation interface compatibility checks
 * -->checks about the availability of the specified headers, paths, libraries
 * ...etc
 */
public class ConformanceManagerCppImplArtifactsEclipseCDT extends IConformanceManagerCppImpArtifacts {
	protected static final Logger	logger	= Logger.getLogger(ConformanceManagerCppImplArtifactsEclipseCDT.class);
	private EclipseCPPParser eclipseCPPParser;

	/**
	 * This method checks is the first class in the first headerFile is base of
	 * the second class in the second headerFile.
	 */
	// After switching to eclipse CDT parser no need to explicitly check the
	// included files
	public boolean isFirstClassBaseOfSecondClass(HeaderFile firstHeader, String firstClassName, HeaderFile secondHeader, String secondClassName,
	        String pathOfSecondHeader) {
		 firstClassName = firstClassName.trim();
		// List<String> includedFiles = new ArrayList<String>();
		// int index = pathOfSecondHeader.lastIndexOf("/");
		// if(index == -1)
		// {
		// index = pathOfSecondHeader.lastIndexOf("\\");
		// }
		// if(index != 1)
		// {
		// pathOfSecondHeader = pathOfSecondHeader.substring(0, index);
		// }
		// for (int i = 0; i < secondHeader.getIncludedFile().size(); i++)
		// {
		// String incFile =
		// secondHeader.getIncludedFile().get(i).getPath().replace("\"", "");
		//
		// File f = DirectoryScanner.SearchArtifactFullPath(pathOfSecondHeader,
		// incFile);
		// includedFiles.add(f.getAbsolutePath());
		// }
		//
		List<String> baseClassesOfSecondClass = new ArrayList<String>();
		for (int i = 0; i < secondHeader.getClasses().size(); i++)
		{
			// Find the second class in the second header
			ClassModel classModel = secondHeader.getClasses().get(i);
			String className = classModel.getFullQualifiedClassName();
			if(className.equals(secondClassName.trim()))
			{
				baseClassesOfSecondClass = classModel.getBaseClasses();
				break;
			}
		}
		// first if the name of the base classes of the second class mathes the
		// first class 
		for (String abaseClassesOfSecondClass:  baseClassesOfSecondClass)
		{
			
			if(abaseClassesOfSecondClass.trim().equals(firstClassName))
			{
				return true;
			}
		}
		// second recursively search for the base classes of the base classes of
		// the second class for a match
		// After switching to eclipse CDT parser no need to explicitly check the
		// included files(see part commented out below)
		// but instead we should keep recursively checking for the base class of
		// of the secondclass
		for (String baseClassName:  baseClassesOfSecondClass)
		{
			if(isFirstClassBaseOfSecondClass(firstHeader, firstClassName, secondHeader, baseClassName, pathOfSecondHeader))
			{
				return true;
			}
		}
		// for (int j = 0; j < includedFiles.size(); j++)
		// {
		// // TO-REVIEW
		//
		// secondHeader = GetHeaderFile(includedFiles.get(j));
		// if(secondHeader == null)
		// {
		// // informative log is written by the caller of the caller of
		// // caller
		// return false;
		// }
		//
		// for (int k = 0; k < secondHeader.getClasses().size(); k++)
		// {
		// if(isFirstClassBaseOfSecondClass(firstHeader, firstClass,
		// secondHeader, secondHeader.getClasses().get(k).getClazzName(),
		// pathOfSecondHeader))
		// {
		// return true;
		// }
		// }
		// }
		return false;
	}

	// After switching to eclipse CDT parser no need to explicitly check the
	// included files
	public void setAllClasses(HeaderFile headerFile, String givenPath) {
		if(headerFile == null)
		{
			return;
		}
		List<ClassModel> classModels = headerFile.getClasses();
		int size = classModels.size();
		for (int i = 0; i < size; i++)
		{
			ClassModel classModel = classModels.get(i);
			if(classModel ==null){
				continue;
			}
			allClassesOfContribution.put(classModel.getNamespace() + "::" + classModel.getClazzName(), "");
			// This part of code is required once we use Turcany parser since
			// the included files needed to be explicitly resolved
			// for (int j = 0; j < headerFile.getIncludedFile().size(); j++)
			// {
			// // TO-REVIEW
			// String filePath =
			// headerFile.getIncludedFile().get(j).getPath().replace("\"", "");
			// String fullHeaderPath =
			// DirectoryScanner.makeHeaderAttributeFullPath(givenPath,
			// filePath);
			// HeaderFile h = GetHeaderFile(fullHeaderPath);
			// int index = fullHeaderPath.lastIndexOf(File.separator);
			// if(index != 1)
			// {
			// fullHeaderPath = fullHeaderPath.substring(0, index);
			// }
			// setAllClasses(h, fullHeaderPath);
			// }
		}
	}

	/**
	 * This function gets the header attribute of the interface or the
	 * implementation elements ->Interface @header (string)attribute must have
	 * the relative path according to the contribution dir ->Interface @callback
	 * (string) attribute must have relative path according to the contribution
	 * dir ->Implementation @header (NCName) attribute (see assumption below) no
	 * path is given for the header info in the implementation (besides header
	 * attribute is only mentioned in xsd not in description)
	 */
	public HeaderFile GetHeaderFile(String fullHeaderPath) {
		if(fullHeaderPath == null)
		{
			throw new ValidationException("The Path of the header file cannot be null");
		}
		if(eclipseCPPParser==null){
			try{
				String incDir = Trengen.getInstance().getOption("includedirs");
				String excDir = Trengen.getInstance().getOption("exclude");
				String[] paths=null;
				String[] excludes=null;
				if(incDir!=null){
					paths = incDir.split("[;,]");
				}
				if(excDir!=null){
					excludes = excDir.split("[;,]");
				}
				eclipseCPPParser = new EclipseCPPParser(null,paths,excludes);
			}catch (Error e)
			{
				throw new IllegalStateException("There is a problem with the Eclipse jars. Please be sure that they are in the same path with your Trengen.exe.\n",e);
			}catch (Exception e)
			{
				throw new IllegalStateException("There is a problem with the Eclipse jars. Please be sure that they are in the same path with your Trengen.exe.\n",e);
			}
		}
		
		
		if(!mapHeadeFile.containsKey(fullHeaderPath))
		{
			HeaderFile headerFile = eclipseCPPParser.parse(fullHeaderPath);
			mapHeadeFile.put(fullHeaderPath, headerFile);
			int index = fullHeaderPath.lastIndexOf(File.separator);
			if(index != 1)
			{
				fullHeaderPath = fullHeaderPath.substring(0, index);
			}
			setAllClasses(headerFile, fullHeaderPath);
			return headerFile;
		}
		else
		{
			return mapHeadeFile.get(fullHeaderPath);
		}
	}
}
