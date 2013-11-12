// // **********************************************************************************
// // Trentino - A C++ based lightweight, non-invasive SCA runtime.
// // Copyright (C) Siemens AG, 2012
// // All Rights Reserved
// // http://trentino.sourceforge.net/
// //
// // This library is free software; you can redistribute it and/or
// // modify it under the terms of the GNU Lesser General Public
// // License as published by the Free Software Foundation; either
// // version 2.1 of the License, or (at your option) any later version.
// //
// // This library is distributed in the hope that it will be useful,
// // but WITHOUT ANY WARRANTY; without even the implied warranty of
// // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// // Lesser General Public License for more details.
// //
// // You should have received a copy of the GNU Lesser General Public
// // License along with this library; if not, write to the Free Software
// // Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
// // **********************************************************************************
//
// package org.trentino.trengen.tools.scavalidation;
//
// import java.io.File;
// import java.util.ArrayList;
// import java.util.List;
//
// import org.apache.log4j.Logger;
// import org.apache.tuscany.sca.cpp.tools.common.Configuration;
// import org.trentino.trengen.cpp.model.ClassModel;
// import org.trentino.trengen.cpp.model.HeaderFile;
// import org.trentino.trengen.cpp.parser.tuscany.TuscanyCPPParser;
//
// /**
// * Cpp artifact related conformance items checks are done in this class For
// * example -->Relationship (being superset, subset or same) between interfaces
// * of services and references. -->implementation interface compatibility checks
// * -->checks about the availability of the specified headers, paths, libraries
// * ...etc
// */
// public class ConformanceManagerCppImplArtifactsTuscany extends IConformanceManagerCppImpArtifacts
// {
// protected static final Logger logger = Logger.getLogger(ConformanceManagerCppImplArtifactsTuscany.class);
// static
// {
// Configuration.initialise();
// }
//
// /*
// * This method checks is the first class in the first headerFile is base of
// * the second class in the second headerFile.
// */
// public boolean isFirstClassBaseOfSecondClass(HeaderFile firstHeader, String firstClass, HeaderFile secondHeader, String secondClass,
// String pathOfSecondHeader)
// {
//
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
// String incFile = secondHeader.getIncludedFile().get(i).getPath().replace("\"", "");
//
// File f = DirectoryScanner.SearchArtifactFullPath(pathOfSecondHeader, incFile);
// includedFiles.add(f.getAbsolutePath());
// }
//
// List<String> baseClasses = new ArrayList<String>();
// for (int i = 0; i < secondHeader.getClasses().size(); i++)
// {
// if(secondHeader.getClasses().get(i).getClazzName().equals(secondClass.trim()))
// {
// baseClasses = secondHeader.getClasses().get(i).getBaseClasses();
// break;
// }
// }
//
// for (int i = 0; i < baseClasses.size(); i++)
// {
// if(baseClasses.get(i).trim().equals(firstClass.trim()))
// {
// return true;
// }
// }
//
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
// if(isFirstClassBaseOfSecondClass(firstHeader, firstClass, secondHeader, secondHeader.getClasses().get(k).getClazzName(),
// pathOfSecondHeader))
// {
// return true;
// }
// }
// }
// return false;
// }
//
// public void setAllClasses(HeaderFile headerFile, String givenPath)
// {
// if(headerFile == null)
// {
// return;
// }
// List<ClassModel> classModels = headerFile.getClasses();
// int size = classModels.size();
// for (int i = 0; i < size; i++)
// {
// allClassesOfContribution.put(classModels.get(i).getNamespace() + "::" + classModels.get(i).getClazzName(), "");
// // This part of code is required once we use Tuscany parser since the included files needed to be explicitly resolved
// for (int j = 0; j < headerFile.getIncludedFile().size(); j++)
// {
// // TO-REVIEW
// String filePath = headerFile.getIncludedFile().get(j).getPath().replace("\"", "");
// if(filePath.startsWith("<") && filePath.endsWith(">"))
// {
// // ignore standard header files
// continue;
// }
//
// String fullHeaderPath = DirectoryScanner.makeHeaderAttributeFullPath(new File(givenPath), filePath);
// if(fullHeaderPath == null)
// {
// continue;
// }
// HeaderFile h = GetHeaderFile(fullHeaderPath);
// int index = fullHeaderPath.lastIndexOf(File.separator);
// if(index != 1)
// {
// fullHeaderPath = fullHeaderPath.substring(0, index);
// }
// setAllClasses(h, fullHeaderPath);
// }
// }
// }
//
// /**
// * This function gets the header attribute of the interface or the
// * implementation elements ->Interface @header (string)attribute must have
// * the relative path according to the contribution dir ->Interface @callback
// * (string) attribute must have relative path according to the contribution
// * dir ->Implementation @header (NCName) attribute (see assumption below) no
// * path is given for the header info in the implementation (besides header
// * attribute is only mentioned in xsd not in description)
// */
// public HeaderFile GetHeaderFile(String fullHeaderPath)
// {
// if(fullHeaderPath == null)
// {
// throw new IllegalArgumentException("The path of the header file cannot be null");
// }
// TuscanyCPPParser parserTuscany = new TuscanyCPPParser();
//
// if(!mapHeadeFile.containsKey(fullHeaderPath))
// {
// HeaderFile headerFileTuscany = parserTuscany.parse(fullHeaderPath);
//
// mapHeadeFile.put(fullHeaderPath, headerFileTuscany);
// int index = fullHeaderPath.lastIndexOf(File.separator);
// if(index != 1)
// {
// fullHeaderPath = fullHeaderPath.substring(0, index);
// }
// setAllClasses(headerFileTuscany, fullHeaderPath);
// return headerFileTuscany;
// }
// else
// {
// return mapHeadeFile.get(fullHeaderPath);
// }
// }
// }
