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

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.trentino.trengen.TIterable.iterable;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.apache.log4j.xml.DOMConfigurator;
import org.junit.Before;
import org.junit.Test;
import org.trentino.trengen.TIterable;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.cpp.model.HeaderFile;
import org.trentino.trengen.sca.model.CPPImplementation;
import org.trentino.trengen.sca.model.CPPInterface;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentService;
import org.trentino.trengen.sca.model.Implementation;
import org.trentino.trengen.sca.model.Reference;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.scavalidation.IConformanceManagerCppImpArtifacts.FunctionTypes;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.tools.trengen.TrentinoTest;

import com.sun.tools.javac.util.Warner;

public class ConformanceManagerCppImplArtifactsTest extends TrentinoTest {
	private static final IConformanceManagerCppImpArtifacts	conformanceManagerCppImplArtifacts	= new ConformanceManagerCppImplArtifactsEclipseCDT();
	private CompositeWrapper	                            compositeWrapper	               = new CompositeWrapper();
	private IConformanceManagerCppImpArtifacts	            manager	                           = null;

	@Before
	public final void initialize() throws IOException, Exception {
		Trengen.initInstance("-cont",new File(ScaValidationLoaderClass.TRENGEN_SCAVALIDATIONFOLDER).getCanonicalPath());
		Trengen.getInstance().setScaValidationFolder(new File(ScaValidationLoaderClass.TRENGEN_SCAVALIDATIONFOLDER));
		/*
		 * String localCompositeString =
		 * ScaValidationLoaderClass.LOCAL_COMPOSITE .toString().replace("file:",
		 * ""); String HelloWorldComponentString =
		 * ScaValidationLoaderClass.HELLOWORLD_COMPONENTTYPE
		 * .toString().replace("file:", ""); String ClientComponentString =
		 * ScaValidationLoaderClass.CLIENT_COMPONENTTYPE
		 * .toString().replace("file:", "");
		 */

		FixtureUtility fu = new FixtureUtility();
		compositeWrapper = fu.setFixtureUtility(ScaValidationLoaderClass.LOCAL_COMPOSITE, ScaValidationLoaderClass.HELLOWORLD_COMPONENTTYPE,
		        ScaValidationLoaderClass.CLIENT_COMPONENTTYPE);
		manager = new ConformanceManagerCppImplArtifactsEclipseCDT();
	}


	@Test
	public final void test_GetHeaderFile() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Method method = ConformanceManagerCppImplArtifactsEclipseCDT.class.getDeclaredMethod("GetHeaderFile", String.class);
		method.setAccessible(true);

		// check if it parses and imports to map again. It should not!
		String fullFilePath = ScaValidationLoaderClass.SCAREFERENCEEXAMPLE_HEADER.toString().replace("file:", "");
		fullFilePath = fullFilePath.replace("/", File.separator);
		fullFilePath = fullFilePath.replace("\\", File.separator);
		HeaderFile headerFile = (HeaderFile) method.invoke(conformanceManagerCppImplArtifacts, fullFilePath);
		assertNotNull(headerFile);
	}

	@Test
	public final void test_getClassModelWithValidComponentType() throws Exception {

		ClassModel cm = doGetClassModel("SCAReferenceExample");
		assertNotNull(cm);
	}

	@Test(expected = ValidationException.class)
	public final void test_getClassModelWithInvalidComponentType() throws Exception {

		ClassModel cm = doGetClassModel("SCAReferenceExample2");
		assertNull(cm);
	}

	private ClassModel doGetClassModel(String scaReferenceExample) throws Exception {
		Method method = ConformanceManagerCppImplArtifactsEclipseCDT.class.getDeclaredMethod("GetHeaderFile", String.class);
		method.setAccessible(true);

		String fullFilePath = ScaValidationLoaderClass.SCAREFERENCEEXAMPLE_HEADER.toString().replace("file:", "");
		fullFilePath = fullFilePath.replace("/", File.separator);
		fullFilePath = fullFilePath.replace("\\", File.separator);
		HeaderFile headerFile = (HeaderFile) method.invoke(conformanceManagerCppImplArtifacts, fullFilePath);
		assertNotNull(headerFile);

		Class<?>[] classes = new Class[3];
		classes[0] = HeaderFile.class;
		classes[1] = String.class;
		classes[2] = StringBuilder.class;
		method = IConformanceManagerCppImpArtifacts.class.getDeclaredMethod("getClassModel", classes);
		method.setAccessible(true);
		ClassModel cm = (ClassModel) method.invoke(conformanceManagerCppImplArtifacts, headerFile, scaReferenceExample, new StringBuilder());
		return cm;
	}

	/*
	 * @Test public void test_getClassModel_WithAHeaderWithMultipleClasses()
	 * throws SecurityException, NoSuchMethodException,
	 * IllegalArgumentException, IllegalAccessException,
	 * InvocationTargetException {
	 * Method method =
	 * ConformanceManagerCppImplArtifacts.class.getDeclaredMethod
	 * ("GetHeaderFile", String.class); method.setAccessible(true);
	 * // check if it parses and imports to map again. It should not! HeaderFile
	 * headerFile = (HeaderFile)
	 * method.invoke(conformanceManagerCppImplArtifacts,
	 * "YetAnotherSCAReferenceExample.h"); assertNotNull(headerFile);
	 * Class classes[] = new Class[2]; classes[0] = HeaderFile.class; classes[1]
	 * = String.class; method =
	 * ConformanceManagerCppImplArtifacts.class.getDeclaredMethod
	 * ("getClassModel", classes); method.setAccessible(true);
	 * ClassModel cm = (ClassModel)
	 * method.invoke(conformanceManagerCppImplArtifacts, headerFile,
	 * "YetAnotherSCAReferenceExample"); assertNotNull(cm);
	 * ClassModel cm2 = (ClassModel)
	 * method.invoke(conformanceManagerCppImplArtifacts, headerFile,
	 * "YetAnotherSCAReferenceExample2"); assertNotNull(cm2);
	 * ClassModel cm3 = (ClassModel)
	 * method.invoke(conformanceManagerCppImplArtifacts, headerFile, null);
	 * assertNull(cm3);
	 * ClassModel cm4 = (ClassModel)
	 * method.invoke(conformanceManagerCppImplArtifacts, headerFile,
	 * "YetAnotherSCAReferenceExample3"); assertNull(cm4);
	 * }
	 * @Test public void test_hasAnyPublicMethods() throws SecurityException,
	 * NoSuchMethodException, IllegalArgumentException, IllegalAccessException,
	 * InvocationTargetException { Method method =
	 * ConformanceManagerCppImplArtifacts
	 * .class.getDeclaredMethod("GetHeaderFile", String.class);
	 * method.setAccessible(true);
	 * // check if it parses and imports to map again. It should not! HeaderFile
	 * headerFile = (HeaderFile)
	 * method.invoke(conformanceManagerCppImplArtifacts,
	 * "YetAnotherSCAReferenceExample.h"); assertNotNull(headerFile);
	 * Class classes[] = new Class[2]; classes[0] = HeaderFile.class; classes[1]
	 * = String.class; method =
	 * ConformanceManagerCppImplArtifacts.class.getDeclaredMethod
	 * ("getClassModel", classes); method.setAccessible(true);
	 * ClassModel cm = (ClassModel)
	 * method.invoke(conformanceManagerCppImplArtifacts, headerFile,
	 * "YetAnotherSCAReferenceExample"); assertNotNull(cm);
	 * ClassModel cm4 = (ClassModel)
	 * method.invoke(conformanceManagerCppImplArtifacts, headerFile,
	 * "YetAnotherSCAReferenceExample4"); assertNotNull(cm4);
	 * ClassModel cm5 = (ClassModel)
	 * method.invoke(conformanceManagerCppImplArtifacts, headerFile,
	 * "YetAnotherSCAReferenceExample5"); assertNotNull(cm5);
	 * method = ConformanceManagerCppImplArtifacts.class.getDeclaredMethod(
	 * "hasAnyPublicMethods", ClassModel.class); method.setAccessible(true);
	 * Boolean ret = (Boolean) method.invoke(conformanceManagerCppImplArtifacts,
	 * cm); assertTrue(ret);
	 * Boolean ret4 = (Boolean)
	 * method.invoke(conformanceManagerCppImplArtifacts, cm4);
	 * assertFalse(ret4);
	 * Boolean ret5 = (Boolean)
	 * method.invoke(conformanceManagerCppImplArtifacts, cm5);
	 * assertFalse(ret5);
	 * }
	 */

	@Test
	public final void test_ValidateHeader() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {

		Method method = ConformanceManagerCppImplArtifactsEclipseCDT.class.getDeclaredMethod("GetHeaderFile", String.class);
		method.setAccessible(true);

		// check if it parses and imports to map again. It should not!
		String fullFilePath = ScaValidationLoaderClass.HELLOWORLD_CPPHEADER.toString().replace("file:", "");
		fullFilePath = fullFilePath.replace("/", File.separator);
		fullFilePath = fullFilePath.replace("\\", File.separator);

		HeaderFile headerFile = (HeaderFile) method.invoke(conformanceManagerCppImplArtifacts, fullFilePath);
		assertNotNull(headerFile);

	}

	/*
	 * @Test public void test_isSignaturesSame() throws SecurityException,
	 * NoSuchMethodException, IllegalArgumentException, IllegalAccessException,
	 * InvocationTargetException { Method method =
	 * ConformanceManagerCppImplArtifacts
	 * .class.getDeclaredMethod("GetHeaderFile", String.class);
	 * method.setAccessible(true);
	 * HeaderFile headerFile = (HeaderFile)
	 * method.invoke(conformanceManagerCppImplArtifacts,
	 * "YetAnotherSCAReferenceExample.h"); assertNotNull(headerFile);
	 * Class classes[] = new Class[2]; classes[0] = HeaderFile.class; classes[1]
	 * = String.class; method =
	 * ConformanceManagerCppImplArtifacts.class.getDeclaredMethod
	 * ("getClassModel", classes); method.setAccessible(true);
	 * ClassModel cm5 = (ClassModel)
	 * method.invoke(conformanceManagerCppImplArtifacts, headerFile,
	 * "YetAnotherSCAReferenceExample5"); assertNotNull(cm5);
	 * ClassModel cm6 = (ClassModel)
	 * method.invoke(conformanceManagerCppImplArtifacts, headerFile,
	 * "YetAnotherSCAReferenceExample6"); assertNotNull(cm6);
	 * classes[0] = ClassMethod.class; classes[1] = ClassMethod.class; method =
	 * ConformanceManagerCppImplArtifacts
	 * .class.getDeclaredMethod("isSignaturesSame", classes);
	 * method.setAccessible(true);
	 * Boolean ret = (Boolean) method.invoke(conformanceManagerCppImplArtifacts,
	 * cm5.getMethods().get(0), cm6.getMethods().get(0)); assertTrue(ret);
	 * ret = (Boolean) method.invoke(conformanceManagerCppImplArtifacts,
	 * cm5.getMethods().get(1), cm6.getMethods().get(1)); assertTrue(ret);
	 * ret = (Boolean) method.invoke(conformanceManagerCppImplArtifacts,
	 * cm5.getMethods().get(2), cm6.getMethods().get(2)); assertFalse(ret); }
	 */

	@Test
	public final void test_extractExcludedFunctions() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Class<?>[] classes = new Class[2];
		classes[0] = CPPInterface.class;
		classes[1] = FunctionTypes.class;
		Method method = IConformanceManagerCppImpArtifacts.class.getDeclaredMethod("extractExcludedFunctions", classes);
		method.setAccessible(true);

		List<String> retArray = new ArrayList<String>();
		retArray.add("getSomething");
		retArray.add("setSomething");
		Component component = compositeWrapper.getListComponents().iterator().next().getScaModelComponent();

		for (int i = 0; i < component.getServiceOrReferenceOrProperty().size(); i++)
		{
			if(component.getServiceOrReferenceOrProperty().get(i).getClass().equals(ComponentService.class))
			{
				ComponentService compService = (ComponentService) component.getServiceOrReferenceOrProperty().get(i);
				CPPInterface cppInterface = (CPPInterface) compService.getInterface().getValue();

				List<?> excludedFunctions = (List<?>) method.invoke(conformanceManagerCppImplArtifacts, cppInterface, FunctionTypes.HeaderFile);
				assertEquals(excludedFunctions, retArray);

				excludedFunctions.clear();
				excludedFunctions = (List<?>) method.invoke(conformanceManagerCppImplArtifacts, cppInterface, FunctionTypes.CallBackHeaderFile);
				assertEquals(excludedFunctions, retArray);
				break;
			}
		}

	}

	/*
	 * @Test public void test_checkMethods() throws SecurityException,
	 * NoSuchMethodException, IllegalArgumentException, IllegalAccessException,
	 * InvocationTargetException { Method method =
	 * ConformanceManagerCppImplArtifacts
	 * .class.getDeclaredMethod("GetHeaderFile", String.class);
	 * method.setAccessible(true);
	 * HeaderFile headerFile = (HeaderFile)
	 * method.invoke(conformanceManagerCppImplArtifacts,
	 * "YetAnotherSCAReferenceExample.h"); assertNotNull(headerFile);
	 * Class classes[] = new Class[2]; classes[0] = HeaderFile.class; classes[1]
	 * = String.class; method =
	 * ConformanceManagerCppImplArtifacts.class.getDeclaredMethod
	 * ("getClassModel", classes); method.setAccessible(true);
	 * ClassModel cm5 = (ClassModel)
	 * method.invoke(conformanceManagerCppImplArtifacts, headerFile,
	 * "YetAnotherSCAReferenceExample5"); assertNotNull(cm5);
	 * ClassModel cm6 = (ClassModel)
	 * method.invoke(conformanceManagerCppImplArtifacts, headerFile,
	 * "YetAnotherSCAReferenceExample6"); assertNotNull(cm6);
	 * ClassModel cm7 = (ClassModel)
	 * method.invoke(conformanceManagerCppImplArtifacts, headerFile,
	 * "YetAnotherSCAReferenceExample7"); assertNotNull(cm7);
	 * Class classes2[] = new Class[4]; classes2[0] = List.class; classes2[1] =
	 * List.class; classes2[2] = List.class; classes2[3] = List.class; method =
	 * ConformanceManagerCppImplArtifacts
	 * .class.getDeclaredMethod("checkMethods", classes2);
	 * method.setAccessible(true);
	 * List<String> firstExcluded = new ArrayList<String>(); List<String>
	 * secondExcluded = new ArrayList<String>(); Boolean ret = (Boolean)
	 * method.invoke(conformanceManagerCppImplArtifacts, cm5.getMethods(),
	 * cm6.getMethods(), firstExcluded, secondExcluded); assertFalse(ret);
	 * ret = (Boolean) method.invoke(conformanceManagerCppImplArtifacts,
	 * cm5.getMethods(), cm7.getMethods(), firstExcluded, secondExcluded);
	 * assertTrue(ret);
	 * }
	 */

	@Test
	public final void test_checkCallBackHeader() {
		Component component = compositeWrapper.getListComponents().iterator().next().getScaModelComponent();

		for (int i = 0; i < component.getServiceOrReferenceOrProperty().size(); i++)
		{
			if(component.getServiceOrReferenceOrProperty().get(i).getClass().equals(ComponentService.class))
			{
				ComponentService compService = (ComponentService) component.getServiceOrReferenceOrProperty().get(i);
				CPPInterface cppInterface = (CPPInterface) compService.getInterface().getValue();

				Boolean ret = manager.checkCallBackHeader(cppInterface);
				assertTrue(ret);
				break;
			}
		}

	}

	@Test
	public final void test_isFirstClassBaseOfSecondClass() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Method method = ConformanceManagerCppImplArtifactsEclipseCDT.class.getDeclaredMethod("GetHeaderFile", String.class);
		method.setAccessible(true);

		String fullFilePath = ScaValidationLoaderClass.BASE_HEADER.toString().replace("file:", "");
		fullFilePath = fullFilePath.replace("/", File.separator);
		fullFilePath = fullFilePath.replace("\\", File.separator);

		HeaderFile headerFile = (HeaderFile) method.invoke(conformanceManagerCppImplArtifacts, fullFilePath);
		assertNotNull(headerFile);

		method = ConformanceManagerCppImplArtifactsEclipseCDT.class.getDeclaredMethod("GetHeaderFile", String.class);
		method.setAccessible(true);

		fullFilePath = ScaValidationLoaderClass.CHILD_HEADER.toString().replace("file:", "");
		fullFilePath = fullFilePath.replace("/", File.separator);
		fullFilePath = fullFilePath.replace("\\", File.separator);
		HeaderFile headerFileChild = (HeaderFile) method.invoke(conformanceManagerCppImplArtifacts, fullFilePath);
		assertNotNull(headerFileChild);

		Class<?>[] classes2 = new Class[5];
		classes2[0] = HeaderFile.class;
		classes2[1] = String.class;
		classes2[2] = HeaderFile.class;
		classes2[3] = String.class;
		classes2[4] = String.class;
		method = ConformanceManagerCppImplArtifactsEclipseCDT.class.getDeclaredMethod("isFirstClassBaseOfSecondClass", classes2);
		method.setAccessible(true);

		Boolean ret = (Boolean) method.invoke(conformanceManagerCppImplArtifacts, headerFile, "Base", headerFileChild, "Child", fullFilePath);
		assertTrue(ret);
	}

	@Test
	public final void test_getClassModelImplementation() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Component component = null;
         for(ComponentWrapper c: compositeWrapper.getListComponents()){
        	 Component aComp = c.getScaModelComponent();
        	 Implementation impl = aComp.getImplementation().getValue();
        	 if(impl!=null && impl instanceof CPPImplementation){
        		 CPPImplementation cppImpl = (CPPImplementation) impl;
        		if("ClientComponent".equals(cppImpl.getClazz())){
        			component = aComp;
        			break;
        		}
        	 }
        	 
         }
		Method method = IConformanceManagerCppImpArtifacts.class.getDeclaredMethod("getClassModelImplementation", CPPImplementation.class);
		method.setAccessible(true);

		ClassModel ret = (ClassModel) method.invoke(conformanceManagerCppImplArtifacts, (CPPImplementation) component.getImplementation().getValue());
		assertNotNull(ret);

	}

	@Test
	public final void test_checkCPPInterfaceArtifactExistence() {
		Component component = compositeWrapper.getListComponents().iterator().next().getScaModelComponent();

		for (int i = 0; i < component.getServiceOrReferenceOrProperty().size(); i++)
		{
			if(component.getServiceOrReferenceOrProperty().get(i).getClass().equals(ComponentService.class))
			{
				ComponentService compService = (ComponentService) component.getServiceOrReferenceOrProperty().get(i);
				CPPInterface cppInterface = (CPPInterface) compService.getInterface().getValue();

				Boolean ret = manager.checkCPPInterfaceArtifactExistence(cppInterface, true);
				assertTrue(ret);
				break;
			}
		}

	}

	/*
	 * @Test
	 * public final void test_ValidateInjectionMethods() {
	 * Boolean ret = manager.ValidateInjectionMethods(compositeWrapper.getListComponents().get(1));
	 * assertTrue(ret);
	 * }
	 */

	@Test
	public final void test_isSame() {

		Component component = compositeWrapper.getListComponents().iterator().next().getScaModelComponent();

		for (int i = 0; i < component.getServiceOrReferenceOrProperty().size(); i++)
		{
			if(component.getServiceOrReferenceOrProperty().get(i).getClass().equals(ComponentService.class))
			{
				ComponentService compService = (ComponentService) component.getServiceOrReferenceOrProperty().get(i);
				CPPInterface cppInterface = (CPPInterface) compService.getInterface().getValue();

				Boolean ret = manager.isSame(cppInterface, cppInterface);
				assertTrue(ret);
				break;
			}
		}
	}

	@Test
	public final void test_isCallbackSame() {

		Component component = compositeWrapper.getListComponents().iterator().next().getScaModelComponent();

		for (int i = 0; i < component.getServiceOrReferenceOrProperty().size(); i++)
		{
			if(component.getServiceOrReferenceOrProperty().get(i).getClass().equals(ComponentService.class))
			{
				ComponentService compService = (ComponentService) component.getServiceOrReferenceOrProperty().get(i);
				CPPInterface cppInterface = (CPPInterface) compService.getInterface().getValue();

				Boolean ret = manager.isCallbackSame(cppInterface, cppInterface);
				assertTrue(ret);
				break;
			}
		}
	}

	@Test
	public final void test_isSubset() {
		CPPInterface[] firstAndSecond = new CPPInterface[2] ;
       
		prepareTest_isSubset(firstAndSecond);
		Boolean ret = manager.isSubset(firstAndSecond[0], firstAndSecond[1]);
		assertFalse(ret);

		ret = manager.isSubset(firstAndSecond[1], firstAndSecond[0]);
		assertTrue(ret);
	}

	
	private void prepareTest_isSubset(CPPInterface[] firstAndSecond) {
		List<Object> refs = compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService();
		TIterable<Reference> references =  iterable(refs, Reference.class);
		for (Reference object :references)
		{
				Reference ref = (Reference) object;
				firstAndSecond[0] = (CPPInterface) ref.getInterface().getValue();
				break;
		}

		
		for(ComponentWrapper wrapper : compositeWrapper.getListComponents()){
			Component component = wrapper.getScaModelComponent();
			if(!"MyClientComponent".equals(component.getName())){
				continue;
			}
			List<Object> refs2 = component.getServiceOrReferenceOrProperty();
			TIterable<ComponentReference> objects = iterable(refs2, ComponentReference.class);
			for (ComponentReference object : objects)
			{
					ComponentReference compService = (ComponentReference) object;
					firstAndSecond[1] = (CPPInterface) compService.getInterface().getValue();
					break;
			}
		}
	
	}
}
