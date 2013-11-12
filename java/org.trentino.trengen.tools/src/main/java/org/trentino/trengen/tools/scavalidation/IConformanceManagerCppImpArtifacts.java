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
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.trentino.trengen.ValidationException;

import org.apache.log4j.Logger;
import org.trentino.trengen.cpp.model.ClassMethod;
import org.trentino.trengen.cpp.model.ClassMethodArgument;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.cpp.model.HeaderFile;
import org.trentino.trengen.sca.model.CPPFunction;
import org.trentino.trengen.sca.model.CPPImplementation;
import org.trentino.trengen.sca.model.CPPImplementationScope;
import org.trentino.trengen.sca.model.CPPInterface;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.tools.trengen.OSValidator;
import org.trentino.trengen.tools.trengen.Trengen;

public abstract class IConformanceManagerCppImpArtifacts {
	protected static final Logger	               logger	                = Logger.getLogger(IConformanceManagerCppImpArtifacts.class);

	// keeps the header file path along with the parsed Headerfile
	// helps us to avoid parsing the same file several times
	protected static final Map<String, HeaderFile>	mapHeadeFile	        = new HashMap<String, HeaderFile>();

	// We keep this as a map to make sure that the qualified names for classes
	// are uniquely represented here
	public static final Map<String, String>	       allClassesOfContribution	= new HashMap<String, String>();

	// this map keeps the classModels according the fully qualified(namespaces)
	// names of classes
	// to be able to use the already parsed class models
	private static final Map<String, ClassModel>	mapClassModel	        = new HashMap<String, ClassModel>();

	enum FunctionTypes {
		HeaderFile, CallBackHeaderFile
	}

	/**
	 * [CPP80003] A C++ header file used to define an interface MUST declare at
	 * least one class with: At least one public member function. All public
	 * member functions are pure virtual.
	 */
	private boolean hasAnyPublicMethods(ClassModel classModel, String parentHeaderFileName) {
		int numberOfPublicMethods = 0;
		List<ClassMethod> classMethods = classModel.getMethods();
		for (ClassMethod classMethod : classMethods)
		{
			if(classMethod == null)
			{
				continue;
			}
			if(classMethod.getAccess().trim().equals("public"))
			{
				numberOfPublicMethods++;

				// if(!classMethod.getAttribute().trim().equals("virtual") ||
				// !classMethods.get(j).isPureVirtual())
				// if the method is pure virtual signature should be starting
				// with virtual keyword.
				if(!classMethod.isPureVirtual())
				{
					throw new ValidationException(ConformanceManagerConstants.CI_CPP80003_VIOLATED + " public member function '"
					        + classMethod.getName() + "' is not pure virtual in the class" + classModel.getClazzName() + " in header file "
					        + parentHeaderFileName);
				}
			}
		}

		if(numberOfPublicMethods < 1)
		{
			logger.error(ConformanceManagerConstants.CI_CPP80003_VIOLATED + " There are not any public member functions in "
			        + classModel.getClazzName() + " @" + parentHeaderFileName);
			return false;
		}
		return true;
	}

	/**
	 * This method checks if the function names, return types and arguments of 2
	 * ClassMethods are the same (used by checkInterfaceImplCompatibility() and
	 * checkMethods() functions)
	 */
	protected boolean isSignaturesSame(ClassMethod firstMethod, ClassMethod secondMethod) {
		String firstRetType = firstMethod.getReturnType();
		String secondRetType = secondMethod.getReturnType();
		 if(!typesEquals(firstRetType, secondRetType))
		{
			throw new ValidationException("Return types are not the same for method "+firstMethod.getName());
		}

		if(!firstMethod.getAccess().trim().equals(secondMethod.getAccess().trim()))
		{
			throw new ValidationException("Function access modifiers are different for interface and implementation.\nMethod1: "+firstMethod+"\nCMethod2: "+secondMethod);
		}

		if(!firstMethod.getName().trim().equals(secondMethod.getName().trim()))
		{
			throw new ValidationException("Function names are not the same. for.\nMethod1: "+firstMethod+"\nCMethod2: "+secondMethod);
		}

		List<ClassMethodArgument> firstArgs = firstMethod.getArguments();
		List<ClassMethodArgument> secondArgs = secondMethod.getArguments();
		if(firstArgs.size() != secondArgs.size())
		{
			return false;
		}
		for (int i = 0; i < firstArgs.size(); i++)
		{
			String type1 = firstArgs.get(i).getType();
			String type2 = secondArgs.get(i).getType();
			if(!typesEquals(type1, type2))
			{
				return false;
			}
		}
		return true;
	}

	/**
     * @param type1
     * @param type2
     * @return
     */
    private boolean typesEquals(String type1, String type2) {
    	type1 = type1.trim();
    	type2 = type2.trim();
    	String doublespace = "  ";
		String space = " ";
		while(type1.contains(doublespace)){
    		type1 = type1.replace(doublespace, space);
    	}
    	while(type2.contains(doublespace)){
    		type2 = type2.replace(doublespace, space);
    	}
	    if(type1.equals(type2)){
	    	return true;
	    }

		//both should be pointer or not
		String suffix = "*";
		while(type1.endsWith(suffix) || type2.endsWith(suffix)){
			if(type1.endsWith(suffix) ^ type2.endsWith(suffix)){
				return false;
			}
			type1 = type1.substring(0,type1.length()-2);
			type2 = type2.substring(0,type2.length()-2);
		}

		
		
		//both should be reference or not
		suffix = "&";
		if(type1.endsWith(suffix) ^ type2.endsWith(suffix)){
			return false;
		}
		
		if(type1.endsWith(suffix)){
			type1 = type1.substring(0,type1.length()-1);
			type2 = type2.substring(0,type2.length()-1);
		}
		
	    
	    //both should be const or not
	    String prefix = "const ";
		if(type1.startsWith(prefix) ^ type2.startsWith(prefix)){
	    	return false;
	    }
		if(type1.startsWith(prefix)){
			type1 = type1.substring(6);
			type2 = type2.substring(6);
		}
		
		if(!type1.contains("::")){
			type1 ="::"+type1;
			type2=type2+"::";
		}
		if(!type2.contains("::")){
			type2 ="::"+type2;
			type1=type1+"::";
		}
		if(type1.contains(type2)||type2.contains(type1)){
			return true;
		}
		
	    return false;
    }

	/**
	 * This method checks is the first class in the first headerFile is base of
	 * the second class in the second headerFile.
	 */
	public abstract boolean isFirstClassBaseOfSecondClass(HeaderFile firstHeader, String firstClass, HeaderFile secondHeader, String secondClass,
	        String pathOfSecondHeader);

	/**
	 * [ASM80002]:Remotable service Interfaces MUST NOT make use of method or
	 * operation overloading.
	 */
	private boolean check_CI80002(ClassModel classModel) {
		List<ClassMethod> methods = classModel.getMethods();
		int methodsSize = methods.size();
		if(methodsSize > 0)
		{
			for (int i = 0; i < methodsSize; i++)
			{
				for (int j = i + 1; j < methodsSize; j++)
				{
					ClassMethod classMethod = methods.get(j);
					if(methods.get(i).getName().equals(classMethod.getName()))
					{
						ValidationException e = new ValidationException("Remotable service of interface must not make use of method or operation overloading");
						e.addMessage("Class :"+classModel.getFullQualifiedClassName());
						e.addMessage("Method: "+classMethod.getName());
						throw e;
					}
				}
			}
		}
		return true;
	}

	public HeaderFileWithFullPath getHeaderFileWithFullPath(String relativePath, String fileDescription) {
		String fullHeaderPath = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), relativePath);
		if(fullHeaderPath == null)
		{
			return null;
		}
		HeaderFileWithFullPath res = new HeaderFileWithFullPath();
		res.fullPath = fullHeaderPath;
		if((fullHeaderPath == null) || !new File(fullHeaderPath).exists())
		{
			String formattedLogMsg = "Error while parsing header file for " + fileDescription + ". Expected file was not found in " + fullHeaderPath
			        + ".";
			logger.error(formattedLogMsg);
			return res;
		}
		HeaderFile headerFile = GetHeaderFile(fullHeaderPath);
		res.headerFile = headerFile;
		if(headerFile == null)
		{
			logger.error("Error while parsing header file for " + fileDescription + ". File has not correct format. Path: " + fullHeaderPath);
		}
		return res;
	}

	/**
	 * This method checks is the first interface is a subset of second interface
	 * @throws ValidationException
	 */
	public boolean isSubset(CPPInterface firstInterface, CPPInterface secondInterface) throws ValidationException {
		if(firstInterface.isRemotable() != secondInterface.isRemotable())
		{
			logger.error("interfaces should be either both remotable or else both local for the services using " + firstInterface.getHeader()
			        + " and " + secondInterface.getHeader());
			return false;
		}
		String fullHeaderPathFirstHeader = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), firstInterface.getHeader());
		if(fullHeaderPathFirstHeader == null)
		{
			return false;
		}
		HeaderFile firstHeader = GetHeaderFile(fullHeaderPathFirstHeader);
		if(firstHeader == null)
		{
			// informative log is written by the caller of the caller of caller
			return false;
		}

		ClassModel firstModel = getClassModelForInterface(firstInterface, firstHeader);
		if(firstModel == null)
		{
			return false;
		}
		String fullHeaderPathSecondHeader = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(),
		        secondInterface.getHeader());
		HeaderFile secondHeader = GetHeaderFile(fullHeaderPathSecondHeader);
		if(secondHeader == null)
		{
			// informative log is written by the caller of the caller of caller
			return false;
		}

		ClassModel secondModel = getClassModelForInterface(secondInterface, secondHeader);

		if(secondModel == null)
		{
			return false;
		}

		if(!isFirstClassBaseOfSecondClass(firstHeader, firstModel.getFullQualifiedClassName(), secondHeader, secondModel.getFullQualifiedClassName(),
		        fullHeaderPathSecondHeader))
		{
			return false;
		}

		List<ClassMethod> firstMethods = firstModel.getMethods();
		List<ClassMethod> secondMethods = secondModel.getMethods();

		List<String> extractedFunctionsListFirst = extractExcludedFunctions(firstInterface, FunctionTypes.HeaderFile);
		List<String> extractedFunctionsListSecond = extractExcludedFunctions(secondInterface, FunctionTypes.HeaderFile);

		if(!checkMethods(firstMethods, secondMethods, extractedFunctionsListFirst, extractedFunctionsListSecond))
		{
			return false;
		}
		return true;
	}

	/**
	 * To be able to ignore the excluded functions during the subset check we
	 * need to keep track of excluded functions (related conformance items :
	 * [CPP20016] and [CPP20017]
	 * Checks the method names, return types, signatures
	 */
	private boolean checkMethods(List<ClassMethod> firstMethods, List<ClassMethod> secondMethods, List<String> extractedFunctionsListFirst,
	        List<String> extractedFunctionsListSecond) {
		for (ClassMethod firstMethod: firstMethods)
		{
			String methodNameFirstInterface = firstMethod.getName();
			if(extractedFunctionsListFirst.contains(methodNameFirstInterface))
			{
				continue;
			}
			boolean exists = false;
			boolean methodFound = false;
			for (ClassMethod secondMethod:  secondMethods)
			{
				exists = false;
				String methodNameSecondInterface =secondMethod.getName();
				if(extractedFunctionsListSecond.contains(methodNameSecondInterface))
				{
					continue;
				}
				if(firstMethod.getArguments().size()!=secondMethod.getArguments().size()){
					continue;
				}
				if(methodNameFirstInterface.equals(methodNameSecondInterface))
				{
                    methodFound =true;
					if(isSignaturesSame(firstMethod, secondMethod))
					{
						exists = true;
					}
					break;
				}
			}
			if(!methodFound){
				throw new ValidationException("Method in Service Interface is not defined in Service implementation: Method name:"+methodNameFirstInterface);
			}
			if(!exists)
			{
				// logger.error()
				return false;
			}
		}
		return true;
	}

	/**
	 * Checks if the first callback header is subset(base) of the second one.
	 */
	public boolean isCallbackSubset(CPPInterface firstInterface, CPPInterface secondInterface) {
		if(firstInterface.isRemotable() != secondInterface.isRemotable())
		{
			logger.error("interfaces should be either both remotable or else both local for the services using " + firstInterface.getHeader()
			        + " and " + secondInterface.getHeader());
			return false;
		}

		if((firstInterface.getCallbackHeader() == null) || (secondInterface.getCallbackHeader() == null))
		{
			return true;
		}

		HeaderFileWithFullPath headerFileWithFullPath = getHeaderFileWithFullPath(firstInterface.getCallbackHeader(), "Interface CallbackHeader "
		        + firstInterface.getCallbackHeader());
		if(headerFileWithFullPath.headerFile == null)
		{
			return false;
		}
		HeaderFile firstHeader = headerFileWithFullPath.headerFile;

		ClassModel firstModel = getClassModelCallback(firstInterface, firstHeader);
		if(firstModel == null)
		{
			return false;
		}

		HeaderFileWithFullPath headerFileWithFullPath2 = getHeaderFileWithFullPath(secondInterface.getCallbackHeader(), "Interface CallbackHeader "
		        + secondInterface.getCallbackHeader());
		if(headerFileWithFullPath2.headerFile == null)
		{
			return false;
		}
		HeaderFile secondHeader = headerFileWithFullPath2.headerFile;

		ClassModel secondModel = getClassModelCallback(secondInterface, secondHeader);
		if(secondModel == null)
		{
			return false;
		}

		if(!isFirstClassBaseOfSecondClass(firstHeader, firstModel.getClazzName(), secondHeader, secondModel.getClazzName(),
		        headerFileWithFullPath2.fullPath))
		{
			return false;
		}

		List<ClassMethod> firstMethods = firstModel.getMethods();
		List<ClassMethod> secondMethods = secondModel.getMethods();

		List<String> extractedFunctionsListFirst = extractExcludedFunctions(firstInterface, FunctionTypes.CallBackHeaderFile);
		List<String> extractedFunctionsListSecond = extractExcludedFunctions(secondInterface, FunctionTypes.CallBackHeaderFile);
		try
		{
			if(!checkMethods(firstMethods, secondMethods, extractedFunctionsListFirst, extractedFunctionsListSecond))
			{
				return false;
			}
		} catch (ValidationException e)
		{
			e.addMessage("Interface incompatibility for classes: " + firstInterface.getClazz() + "and" + firstInterface.getClazz());
		   throw e;
		}

		return true;
	}

	/**
	 * To be able to ignore the excluded functions during the subset check we
	 * need to keep track of excluded functions (related conformance items :
	 * [CPP20016] and [CPP20017] If the header file identified by the @header
	 * attribute of an <interface.cpp/> element contains function declarations
	 * that are not operations of the interface, then the functions that are not
	 * operations of the interface MUST be excluded using <function/> child
	 * elements of the <interface.cpp/> element with exclude="true". [CPP20016]
	 */
	private List<String> extractExcludedFunctions(CPPInterface cppInterface, FunctionTypes functionType) {
		List<CPPFunction> functionList = new ArrayList<CPPFunction>();
		if(functionType.equals(FunctionTypes.HeaderFile))
		{
			functionList = cppInterface.getFunction();
		}
		else if(functionType.equals(FunctionTypes.CallBackHeaderFile))
		{
			functionList = cppInterface.getCallbackFunction();
		}
		List<String> excludedFunctions = new ArrayList<String>();
		for (int i = 0; i < functionList.size(); i++)
		{
			CPPFunction cppFunction = functionList.get(i);
			if((cppFunction.isExclude() != null) && cppFunction.isExclude())
			{
				excludedFunctions.add(cppFunction.getName());
			}
		}
		return excludedFunctions;
	}

	/**
	 * This method checks if the interfaces are same.
	 */
	public boolean isSame(CPPInterface firstInterface, CPPInterface secondInterface) {
		String fullHeaderPathOfFirstInterface = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(),
		        firstInterface.getHeader());
		if(fullHeaderPathOfFirstInterface == null)
		{
			return false;
		}
		HeaderFile firstHeader = GetHeaderFile(fullHeaderPathOfFirstInterface);

		if(firstHeader == null)
		{
			// informative log is written by the caller of the caller of caller
			return false;
		}

		ClassModel firstModel = getClassModelForInterface(firstInterface, firstHeader);
		if(null == firstModel)
		{
			return false;
		}

		String fullHeaderPathOfSecondInterface = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(),
		        secondInterface.getHeader());
		HeaderFile secondHeader = GetHeaderFile(fullHeaderPathOfSecondInterface);
		if(secondHeader == null)
		{
			return false;
		}
		ClassModel secondModel = getClassModelForInterface(secondInterface, secondHeader);
		if(null == secondModel)
		{
			return false;
		}

		if(fullHeaderPathOfSecondInterface.equals(fullHeaderPathOfFirstInterface) && firstModel.getClazzName().equals(secondModel.getClazzName()))
		{
			return true;
		}
		return false;
	}

	/**
	 * Checks if the callback headers are same.
	 */
	public boolean isCallbackSame(CPPInterface firstInterface, CPPInterface secondInterface) {
		if((firstInterface.getCallbackHeader() == null) || (secondInterface.getCallbackHeader() == null))
		{
			return true;
		}

		HeaderFileWithFullPath headerFileWithFullPath = getHeaderFileWithFullPath(firstInterface.getCallbackHeader(), "Interface CallbackHeader "
		        + firstInterface.getCallbackHeader());
		if(headerFileWithFullPath.headerFile == null)
		{
			return false;
		}
		HeaderFile firstHeader = headerFileWithFullPath.headerFile;

		ClassModel firstModel = getClassModelCallback(firstInterface, firstHeader);
		if(null == firstModel)
		{
			return false;
		}

		HeaderFileWithFullPath headerFileWithFullPath2 = getHeaderFileWithFullPath(secondInterface.getCallbackHeader(), "Interface CallbackHeader "
		        + secondInterface.getCallbackHeader());
		if(headerFileWithFullPath2.headerFile == null)
		{
			return false;
		}
		HeaderFile secondHeader = headerFileWithFullPath2.headerFile;

		ClassModel secondModel = getClassModelCallback(secondInterface, secondHeader);
		if(null == secondModel)
		{
			return false;
		}

		if(firstHeader.getName().equals(secondHeader.getName()) && firstModel.getClazzName().equals(secondModel.getClazzName()))
		{
			return true;
		}
		return false;
	}

	/**
	 * [CPP20005]:If the header file identified by the header attribute of an
	 * <interface.cpp/> element contains more than one class, then the class
	 * attribute MUST be specified for the <interface.cpp/> element.
	 * [CPP20006]: Checks out if @callbackClass attribute according to the
	 * callbackHeader attribute
	 * @callbackHeader full name of the header file that describes the callback
	 *                 interface, including relative path from the composite
	 *                 root.
	 *                 [CPP80003] A C++ header file used to define an interface
	 *                 MUST declare at least one class with: At least one public
	 *                 member function. All public member functions are pure
	 *                 virtual.
	 */
	public boolean checkCallBackHeader(CPPInterface interfaceToCheck) {
		if(interfaceToCheck.getCallbackHeader() == null)
		{
			return true;
		}
		HeaderFileWithFullPath headerFileWithFullPath = getHeaderFileWithFullPath(interfaceToCheck.getCallbackHeader(), "Interface "
		        + interfaceToCheck.getClazz());
		if(headerFileWithFullPath.headerFile == null)
		{
			return false;
		}
		HeaderFile headerFile = headerFileWithFullPath.headerFile;

		if(headerFile.getClasses().isEmpty())
		{
			logger.error("Class declaration not found in the Header file: for Interface " + interfaceToCheck.getClazz() + ". Path:"
			        + interfaceToCheck.getCallbackHeader());
			return false;
		}

		String className = interfaceToCheck.getCallbackClass();

		if(null == className)
		{
			if((headerFile.getClasses().size() > 1))
			{
				logger.error(ConformanceManagerConstants.CI_CPP20005_VIOLATED);
				return false;
			}
			else
			{
				interfaceToCheck.setCallbackClass(headerFile.getClasses().get(0).getNamespace() + "::"
				        + headerFile.getClasses().get(0).getClazzName());
			}
		}

		ClassModel model = getClassModelCallback(interfaceToCheck, headerFile);
		if(null == model)
		{
			return false;
		}

		if(!hasAnyPublicMethods(model, interfaceToCheck.getCallbackHeader()))
		{
			logger.error(ConformanceManagerConstants.CI_CPP80003_VIOLATED);
			return false;
		}

		return true;
	}

	/**
	 * Searches for the availibility of the library defined in the
	 * implementation xml element the path info is also used to eb able to
	 * resolve the librarys that are identified along with a relative path
	 */
	public boolean validateLibrary(Component comp) {
		if(null != comp.getImplementation())
		{
			CPPImplementation cppImplementation = (CPPImplementation) comp.getImplementation().getValue();
			String libraryName = cppImplementation.getLibrary();

			if(libraryName == null || "".equals(libraryName))
			{
				logger.warn("Library file is missing for the library@impl of Component: " + comp.getName());
				return false;
			}

			if(OSValidator.isWindows())
			{
				libraryName = libraryName + ".dll";
			}
			else if(OSValidator.isUnix())
			{
				libraryName = "lib" + libraryName + ".so"; // On Linux, they
				                                           // have the prefix
				                                           // "lib"
			}

			String libraryPath = cppImplementation.getPath();
			File fileFound = null;

			if(libraryPath == null)
			{
				fileFound = DirectoryScanner.searchLibraryInTheWholeContribution(libraryName);
			}
			else
			{
				String libFullName = new File(libraryPath,libraryName).getPath();
				//(libraryPath.endsWith(File.separator)) ? libraryName : (File.separator + libraryName);
				String fullHeaderPathFirstHeader = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), libFullName);
				// fileFound = DirectoryScanner.searchLibrary(libFullName);
				fileFound = fullHeaderPathFirstHeader == null ? null : new File(fullHeaderPathFirstHeader);
			}

			if(fileFound == null)
			{
				logger.warn("Library couldn't be validated for  component:" + comp.getName() + " Be sure that path attribute of library is correct.");
			}
			else if(!fileFound.exists())
			{
				logger.warn("Library couldn't be validated for  component:" + comp.getName() + " Be sure that path attribute of library is correct.");
			}
			else
			{
				logger.info("Library is validated for component:" + comp.getName());
				return true;
			}
		}
		return true;
	}

	/**
	 * Searches for the availibilty of the header for the header files no path
	 * defining attribute is available
	 */
	private boolean validateImplementationHeader(ComponentWrapper compWrapper) {
		Component comp = compWrapper.getScaModelComponent();
		if(null != comp.getImplementation())
		{
			CPPImplementation cppImplementation = (CPPImplementation) comp.getImplementation().getValue();

			CPPImplementationScope scope = cppImplementation.getScope();

			if(scope != null)
			{
				if((scope.compareTo(CPPImplementationScope.STATELESS) == 0) && cppImplementation.isEagerInit())
				{
					logger.error("Once @scope is stateless @eagerInit is not allowed to be true for the component:" + comp.getName());
					return false;
				}
			}
			String fullHeaderPath = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), cppImplementation.getHeader());
			if(fullHeaderPath == null)
			{
				logger.error("Implementation header is missing for component:" + comp.getName());
				return false;
			}
			HeaderFile headerFile = GetHeaderFile(fullHeaderPath);

			if(headerFile == null)
			{
				logger.error("Error while parsing the header file of the component:" + comp.getName());
				return false;
			}
			if(headerFile.getClasses().isEmpty())
			{
				logger.error("No class declaration exists in component:" + comp.getName());
				return false;
			}

			ClassModel model = getClassModelForImplementation(cppImplementation, headerFile);
			if(model == null)
			{
				return false;
			}

			// set the parsed header for future use
			compWrapper.setComponentHeader(headerFile);
		}
		return true;
	}

	public abstract void setAllClasses(HeaderFile headerFile, String givenPath);

	private String getClassName(String originalClassName) {
		String className = originalClassName.replace("const ", "");
		className = className.replace("&", "");
		className = className.replace("*", "");

		// for example; classname can be Map<string, string>. Thus it can have
		// commas.
		if(className.contains("<") && className.contains(">"))
		{
			int index = className.indexOf("<");
			int indexEnd = className.indexOf(">");
			className = className.substring(index + 1, indexEnd);
		}

		className = className.trim();
		return className; // this can be separated by commas
	}

	// BUG 535: code is refactored.
	private static String getOriginalClassName(String originalClassName, String className) {
		String originalClassNameTemp = originalClassName.replace("&", "");
		originalClassNameTemp = originalClassNameTemp.replace("*", "");
		originalClassNameTemp = originalClassNameTemp.replace("const ", "");
		originalClassNameTemp = originalClassNameTemp.trim();
		if(originalClassNameTemp.contains("<") && originalClassNameTemp.contains(">"))
		{
			int start = originalClassNameTemp.indexOf("<");
			int end = originalClassNameTemp.indexOf(">");
			originalClassNameTemp = originalClassNameTemp.substring(start + 1, end).trim();
		}

		String classNameTemp = className.replace("&", "");
		classNameTemp = classNameTemp.replace("*", "");
		classNameTemp = classNameTemp.replace("const ", "");
		classNameTemp = classNameTemp.trim();

		originalClassName = originalClassName.replace(originalClassNameTemp, classNameTemp);
		return originalClassName;
	}

	public String getClassWithNamespace(HeaderFile headerFile, String originalClassName) {
		String className = getClassName(originalClassName);

		if(className.contains(","))
		{
			String[] classNames = className.split(",");
			for (String cname : classNames)
			{
				cname = cname.trim();
				className = findTheTypeFromTheContribution(headerFile, cname, originalClassName);
				className += ",";
			}
			int index = className.lastIndexOf(",");
			className = className.substring(0, index);
			return className.substring(0, className.length() - 1);
		}
		else
		{
			className = findTheTypeFromTheContribution(headerFile, className, originalClassName);
			return className;
		}
	}

	private String findTheTypeFromTheContribution(HeaderFile headerFile, String type, String originalTypeName) {
		for (Map.Entry<String, String> entry : allClassesOfContribution.entrySet())
		{
			String key = entry.getKey();
			int index = key.lastIndexOf("::");
			String classNam = key.substring(index + 2);
			// String namespace = key.substring(0, index);
			if(type.equals(classNam))
			{
				if(headerFile.getUsingDirectives().size() == 0)
				{
					key = getOriginalClassName(originalTypeName, key);
					return key;
				}
				// TODO this will be used when using-directives are supported.
				/*
				 * for (int j = 0; j < headerFile.getUsingDirectives().size();
				 * j++) {
				 * if(headerFile.getUsingDirectives().get(j).equals(namespace))
				 * { ; } { key = getOriginalClassName(originalTypeName, key);
				 * return key; } }
				 */
			}
		}
		type = getOriginalClassName(originalTypeName, type);
		return type;
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
	public abstract HeaderFile GetHeaderFile(String fullHeaderPath);

	/**
	 * This function returns the class model for the interface.cpp and changes
	 * the class attribute of interface.cpp to be fully qualified(to include
	 * namespaces) this class attribute is used later on
	 * @throws ValidationException
	 */
	public ClassModel getClassModelForInterface(CPPInterface cppInterface, HeaderFile headerFile) throws ValidationException {
		String classNameOfInterface = cppInterface.getClazz();
		StringBuilder classNameWithNameSpaces = new StringBuilder();
		ClassModel classModel = getClassModel(headerFile, classNameOfInterface, classNameWithNameSpaces);
		cppInterface.setClazz(classNameWithNameSpaces.toString());
		return classModel;
	}

	/**
	 * This function returns the class model for the callback interface header
	 * and changes the class attribute of interface.cpp to be fully qualified(to
	 * include namespaces) this class attribute is used later on
	 * @throws ValidationException
	 */
	private ClassModel getClassModelCallback(CPPInterface cppInterface, HeaderFile headerFile) throws ValidationException {
		String classNameOfInterface = cppInterface.getCallbackClass();
		StringBuilder classNameWithNameSpaces = new StringBuilder();
		ClassModel classModel = getClassModel(headerFile, classNameOfInterface, classNameWithNameSpaces);
		cppInterface.setCallbackClass(classNameWithNameSpaces.toString());
		return classModel;
	}

	/**
	 * This function returns the class model for the implementation.cpp and
	 * changes the class attribute of implementation.cpp to be fully
	 * qualified(to include namespaces) this class attribute is used later on
	 * @throws ValidationException
	 */
	private ClassModel getClassModelForImplementation(CPPImplementation cppImplementation, HeaderFile headerFile) throws ValidationException {
		String classNameOfImplementation = cppImplementation.getClazz();
		StringBuilder classNameWithNameSpaces = new StringBuilder();
		ClassModel classModel = getClassModel(headerFile, classNameOfImplementation, classNameWithNameSpaces);
		cppImplementation.setClazz(classNameWithNameSpaces.toString());
		return classModel;
	}

	/**
	 * This is a class used for finding the classModel for implementation.cpp
	 * and interface.cpp It also sets the fully qualified name for the class
	 * attributes of impl.cpp and interface.cpp
	 * @param headerFile
	 * @param classNameOfImplOrInterface
	 * @param classNameWithNameSpaces
	 * @return
	 * @throws ValidationException
	 */
	private ClassModel getClassModel(HeaderFile headerFile, String classNameOfImplOrInterface, StringBuilder classNameWithNameSpaces)
	        throws ValidationException {
		if(classNameOfImplOrInterface == null)
		{
			throw new IllegalArgumentException("input classname is null. Please report a bug");
		}

		String className = null;
		String namespace = null;
		if(!mapClassModel.containsKey(classNameOfImplOrInterface))
		{
			ClassModel classModel = null;
			// extracts the class name without namespaces
			if(classNameOfImplOrInterface.contains("::"))
			{
				int index = classNameOfImplOrInterface.lastIndexOf("::");
				className = classNameOfImplOrInterface.substring(index + 2);
				namespace = classNameOfImplOrInterface.substring(0, index);
			}
			else if(classNameOfImplOrInterface.contains(":"))
			{
				int index = classNameOfImplOrInterface.lastIndexOf(":");
				className = classNameOfImplOrInterface.substring(index + 1);
				namespace = classNameOfImplOrInterface.substring(0, index);
			}
			else
			{
				className = classNameOfImplOrInterface;
			}

			int size = headerFile.getClasses().size();
			boolean exists = false;
			for (int i = 0; i < size; i++)
			{
				String classNameInHeader = headerFile.getClasses().get(i).getClazzName();

				// search for the classes in the headerFile with the className
				if(classNameInHeader.equals(className))
				{
					classModel = headerFile.getClasses().get(i);
					String nameSpaceOfClassModel = classModel.getNamespace();
					if((nameSpaceOfClassModel != null && namespace != null && nameSpaceOfClassModel.equals(namespace))
					        || (((nameSpaceOfClassModel == null || nameSpaceOfClassModel == "") && (namespace == null) || namespace == "")))
					{
						exists = true;
						break;
					}
				}
			}

			if(classModel == null || !exists)
			{
				String message = String.format("There is no class with the name '%s' in the headerfile '%s'.\n  ", classNameOfImplOrInterface,
				        headerFile.getName());
				throw new ValidationException(message);
			}

			if(namespace == null) // class name matches and no namespace was
			                      // specified in the impl.cpp than get the
			                      // namespace from the heade
			{
				classNameWithNameSpaces.append(className);
			}
			else
			{
				classNameWithNameSpaces.append(namespace + "::" + className);
			}

			classModel = changeParametersAndRetTypesToFullQualified(headerFile, classModel);

			mapClassModel.put(classNameWithNameSpaces.toString(), classModel);
			return classModel;
		}
		else
		{
			classNameWithNameSpaces.append(classNameOfImplOrInterface);
			return mapClassModel.get(classNameOfImplOrInterface);
		}
	}

	/**
	 * This function changes all the parameter types and return types to
	 * fully-qualified names.
	 */
	private ClassModel changeParametersAndRetTypesToFullQualified(HeaderFile headerFile, ClassModel classModel) {
		List<ClassMethod> methods = classModel.getMethods();

		for (ClassMethod method : methods)
		{
			String methodRetType = "void";
			if(method.getReturnType() != null)
			{
				methodRetType = method.getReturnType();
			}
			methodRetType = methodRetType.trim();

			if(!methodRetType.contains("::"))
			{
				methodRetType = getClassWithNamespace(headerFile, methodRetType);
			}
			methodRetType = methodRetType.replaceAll("[ ]+", " ");
			method.setReturnType(methodRetType);

			List<ClassMethodArgument> args = method.getArguments();
			List<ClassMethodArgument> changedArgs = new ArrayList<ClassMethodArgument>();
			for (int i = 0; i < args.size(); i++)
			{
				String argType = args.get(i).getType().trim();

				if(!argType.contains("::"))
				{
					argType = getClassWithNamespace(headerFile, argType);
				}
				// TODO using directives will be supported later!
				// if (args.get(i).getType().equals(argType))
				// usingDirectivesMap.put(classModel.getNamespace(),"");
				argType = argType.replaceAll("[ ]+", " ");
				ClassMethodArgument cma = new ClassMethodArgument(args.get(i).getName(), argType);
				changedArgs.add(cma);
			}
			method.setArguments(changedArgs);

		}
		return classModel;
	}

	/**
	 * This function goes through the cpp implementation artifacts to validate
	 * against the cpp artifact related specification called by
	 * scaValidationManager
	 */
	public boolean checkCPPArtifactsImplementation(ComponentWrapper componentWrapper, File componentFile) {
		Component component = componentWrapper.getScaModelComponent();

		// validates header for the implementation
		if(!validateImplementationHeader(componentWrapper))
		{
			return false;
		}

		// validates library for the implementation
		return validateLibrary(component);
	}

	/**
	 * Checks out header of the interface of the componentType service ,
	 * validates it and check out the compatibility of the interface with tem
	 * implementation [CPP20001] A C++ implementation MUST implement all of the
	 * operation(s) of the service interface(s) of its componentType.
	 */
	// Function is changed because cppImplementation class must inherit from the
	// cppInterface class of the service.
	public boolean checkInterfaceImplCompatibility(CPPInterface cppInterface, CPPImplementation cppImplementation, String componentName) {
		String fullHeaderPathFirstHeader = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), cppInterface.getHeader());
		if(fullHeaderPathFirstHeader == null)
		{
			return false;
		}
		HeaderFile firstHeader = GetHeaderFile(fullHeaderPathFirstHeader);
		if(firstHeader == null)
		{
			// informative log is written by the caller of the caller of caller
			return false;
		}

		ClassModel firstModel = getClassModelForInterface(cppInterface, firstHeader);
		if(firstModel == null)
		{
			return false;
		}
		String fullHeaderPathSecondHeader = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(),
		        cppImplementation.getHeader());
		HeaderFile secondHeader = GetHeaderFile(fullHeaderPathSecondHeader);
		if(secondHeader == null)
		{
			// informative log is written by the caller of the caller of caller
			return false;
		}

		ClassModel secondModel = getClassModelForImplementation(cppImplementation, secondHeader);

		if(secondModel == null)
		{
			return false;
		}

		String fc = firstModel.getFullQualifiedClassName();
		String sc = secondModel.getFullQualifiedClassName();
		if(!isFirstClassBaseOfSecondClass(firstHeader, fc, secondHeader, sc,
		        fullHeaderPathSecondHeader))
		{
			ValidationException ex = new ValidationException(String.format("Class '%s' in header file '%s' should be base class of class '%s' in header file '%s'",fc,firstHeader.getName(),sc, secondHeader.getName()));
			ex.setLastEntity(cppInterface);
			throw ex;
		}

		List<ClassMethod> firstMethods = firstModel.getMethods();
		List<ClassMethod> secondMethods = secondModel.getMethods();

		List<String> extractedFunctionsListFirst = extractExcludedFunctions(cppInterface, FunctionTypes.HeaderFile);
		List<String> extractedFunctionsListSecond = new ArrayList<String>();
         try{
        	 if(!checkMethods(firstMethods, secondMethods, extractedFunctionsListFirst, extractedFunctionsListSecond))
     		{
     			throw new ValidationException(ConformanceManagerConstants.CI_CPP20001_VIOLATED);
     		}
         }
         catch (ValidationException e) {
			e.addMessage("\nService header file:"+firstHeader.getName());
			e.addMessage("\nImplementation header file:"+secondHeader.getName()+"\n");
			e.addMessage(ConformanceManagerConstants.CI_CPP20001_VIOLATED);
			throw e;
		}
		
		return true;

		/*
		 * ClassModel classModelImplementation =
		 * getClassModelImplementation(cppImplementation);
		 * if(classModelImplementation == null) {
		 * logger.error("Class is null for the component : " + componentName);
		 * return false; }
		 * HeaderFileWithFullPath headerFileWithFullPath =
		 * GetHeaderFileWithFullPath(cppInterface.getHeader(), "Interface " +
		 * cppInterface.getClazz()); if(headerFileWithFullPath.headerFile ==
		 * null) { return false; } HeaderFile headerFile =
		 * headerFileWithFullPath.headerFile;
		 * if(headerFile.getClasses().isEmpty()) { logger.error(
		 * "Class declaration not found in the Header file: for Interface " +
		 * cppInterface.getClazz() + ". Path:" +
		 * cppInterface.getCallbackHeader()); return false; }
		 * ClassModel interfaceClass = getClassModelForInterface(cppInterface,
		 * headerFile); if(interfaceClass == null) { return false; }
		 * List<ClassMethod> methodsImp = classModelImplementation.getMethods();
		 * List<ClassMethod> methodsInterface = interfaceClass.getMethods();
		 * for (int i = 0; i < methodsInterface.size(); i++) { boolean exists =
		 * false; for (int j = 0; j < methodsImp.size(); j++) {
		 * if(methodsInterface
		 * .get(i).getName().equals(methodsImp.get(j).getName())) {
		 * if(isSignaturesSame(methodsInterface.get(i), methodsImp.get(j))) {
		 * exists = true; break; } } } if(!exists) {
		 * logger.error(ConformanceManagerConstants.CI_CPP20001_VIOLATED +
		 * " There is no matching operation in the implementation for method: "
		 * + methodsInterface.get(i).getName() + " in implementation class: " +
		 * classModelImplementation.getClazzName()); return false; } } return
		 * true;
		 */
	}

	/**
	 * Gets the implementation class to be used while checking the compatibility
	 * with the interface
	 */
	protected ClassModel getClassModelImplementation(CPPImplementation cppImplementation) {
		if(cppImplementation == null)
		{
			return null;
		}
		// no path is given for the header info in the implementation
		// Assumption: it is assumed that if the user wants to specify
		// a path relative to the contribution directory that relative
		// path will be included in the header attribute. Otherwise
		// whole tree is searched for the impl header
		String headerImp = cppImplementation.getHeader();
		String classImp = cppImplementation.getClazz();

		HeaderFileWithFullPath headerFileWithFullPath = getHeaderFileWithFullPath(cppImplementation.getHeader(), "CPP Implementation "
		        + cppImplementation.getClazz());
		if(headerFileWithFullPath.headerFile == null)
		{
			return null;
		}
		HeaderFile headerFileImp = headerFileWithFullPath.headerFile;

		ClassModel implementationClass = getClassModelForImplementation(cppImplementation, headerFileImp);
		if(implementationClass == null)
		{
			logger.error("The class declared in the header: " + headerImp + " does not match the @class attribute: " + classImp
			        + " of implementation");
			return null;
		}

		return implementationClass;
	}

	/**
	 * * [CPP20005]:If the header file identified by the header attribute of an
	 * <interface.cpp/> element contains more than one class, then the class
	 * attribute MUST be specified for the <interface.cpp/> element.
	 * Checks if the header file is null or not, checks if the header file is
	 * null or not, checks if the
	 */
	public boolean checkCPPInterfaceArtifactExistence(CPPInterface cppInterface, boolean isService) {

		HeaderFileWithFullPath headerFileWithFullPath = getHeaderFileWithFullPath(cppInterface.getHeader(), "Interface " + cppInterface.getClazz());
		if(headerFileWithFullPath == null || headerFileWithFullPath.headerFile==null)
		{
			String msg = "Cannot find header file '%s' for CPP Interface '%s'.\nMake sure that the given path is correct.";
			String message = String.format(msg, cppInterface.getHeader(), cppInterface.getClazz());
			throw new ValidationException(message);
		}
		HeaderFile headerFile = headerFileWithFullPath.headerFile;
		if(headerFile.getClasses().isEmpty())
		{
			throw new ValidationException("Class declaration not found in the Header file: for Interface " + cppInterface.getClazz() + ". Path:"
			        + cppInterface.getCallbackHeader());
		}

		String interfaceName = cppInterface.getClazz();
		if(null == interfaceName)
		{
			if((headerFile.getClasses().size() > 1))
			{
				throw new ValidationException(ConformanceManagerConstants.CI_CPP20005_VIOLATED);
			}
			else
			{
				cppInterface.setClazz(headerFile.getClasses().get(0).getNamespace() + "::" + headerFile.getClasses().get(0).getClazzName());
			}
		}

		ClassModel classModel = getClassModelForInterface(cppInterface, headerFile);

		if(!hasAnyPublicMethods(classModel, cppInterface.getHeader()))
		{
			throw new ValidationException(ConformanceManagerConstants.CI_CPP80003_VIOLATED);
		}

		if((isService == true) && ((cppInterface.isRemotable() != null) && (cppInterface.isRemotable() == true)))
		{
			if(!check_CI80002(classModel))
			{
				return false;
			}
		}
		return true;
	}
}
