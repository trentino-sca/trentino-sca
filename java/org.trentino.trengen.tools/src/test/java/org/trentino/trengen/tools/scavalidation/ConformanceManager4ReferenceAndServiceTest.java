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

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

import org.apache.log4j.Logger;
import org.apache.log4j.xml.DOMConfigurator;
import org.junit.BeforeClass;
import org.junit.Ignore;
import org.junit.Test;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentService;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.ComponentTypeReference;
import org.trentino.trengen.sca.model.Reference;
import org.trentino.trengen.sca.model.Service;
import org.trentino.trengen.sca.model.Wire;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.samples.SamplesClassLoader;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.tools.trengen.TrentinoTest;

public class ConformanceManager4ReferenceAndServiceTest extends TrentinoTest {
	protected static final Logger	                      logger	       = Logger.getLogger(ConformanceManager4ReferenceAndServiceTest.class);
	private static CompositeWrapper	                      compositeWrapper	= new CompositeWrapper();
	// private static ConformanceManagerCppImplArtifactsTuscany
	// conformanceManagerCppImplArtifactsTuscany = new
	// ConformanceManagerCppImplArtifactsTuscany();

	private static ConformanceManager4ReferenceAndService	conformanceManager4ReferenceAndService;	                                         // =
	                                                                                                                                             // new
	                                                                                                                                             // ConformanceManager4ReferenceAndService(compositeWrapper,
	                                                                                                                                             // conformanceManagerCppImplArtifactsTuscany)



	@BeforeClass
	public static void initialize() throws IOException, Exception {
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

		IConformanceManagerCppImpArtifacts cppImpconformanceMng = new ConformanceManagerCppImplArtifactsEclipseCDT();
		conformanceManager4ReferenceAndService = new ConformanceManager4ReferenceAndService(compositeWrapper, cppImpconformanceMng);
	}

	@Test
	public final void test_ASM40004() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Class<?>[] classes = new Class[3];
		classes[0] = ComponentTypeReference.class;
		classes[1] = ArrayList.class;
		classes[2] = String.class;
		Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM40004", classes);
		method.setAccessible(true);

		ComponentTypeReference ctR = new ComponentTypeReference();
		ctR.setName("reference1");

		List<String> referenceNames = new ArrayList<String>();
		referenceNames.add("1");
		referenceNames.add("2");
		Boolean output = (Boolean) method.invoke(conformanceManager4ReferenceAndService, ctR, referenceNames, "componentName");

		assertTrue(output);
	}

	@Ignore
	@Test
	public final void test_ASM60007() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		boolean output = conformanceManager4ReferenceAndService.checkAllReferencePromotions();
		assertTrue(output);
	}

	@Test
	public final void test_OnNewWireOfComposite() {
		Wire w = new Wire();
		w.setSource("sourceComp/source");
		w.setTarget("targetComp/target");

		conformanceManager4ReferenceAndService.OnNewWireOfComposite(w);

		assertTrue(compositeWrapper.wires.contains(w));
	}

	@Test
	public final void test_getCorrespondingComponentType() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("getCorrespondingComponentWrapper", Component.class);
		method.setAccessible(true);

		for (int i = 0; i < compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().size(); i++)
		{
			if(compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Component.class))
			{
				Component component = (Component) compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i);
				ComponentWrapper wrapper =(ComponentWrapper) method.invoke(conformanceManager4ReferenceAndService, component);
				ComponentType compType = wrapper.getScaModelComponentType();
				assertNotNull(compType);
			}
		}
	}

	@Test
	public final void test_check_ASM90002() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM90002", Object.class);
		method.setAccessible(true);

		for (ComponentWrapper componentWrapper: compositeWrapper.listComponentWrappers)
		{
			Component component = componentWrapper.getScaModelComponent();
			ComponentType componentType = componentWrapper.getScaModelComponentType();

			for (int j = 0; j < component.getServiceOrReferenceOrProperty().size(); j++)
			{
				if(component.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentService.class))
				{
					ComponentService cs = (ComponentService) component.getServiceOrReferenceOrProperty().get(j);
					Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, cs);
					assertFalse(ret);
					break;
				}
			}

			for (int j = 0; j < componentType.getServiceOrReferenceOrProperty().size(); j++)
			{
				if(componentType.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentService.class))
				{
					ComponentService cs = (ComponentService) componentType.getServiceOrReferenceOrProperty().get(j);
					Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, cs);
					assertTrue(ret);
					break;
				}
			}
		}

		for (int i = 0; i < compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().size(); i++)
		{
			if(compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Service.class))
			{
				Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, compositeWrapper.getComposite()
				        .getRequiresOrPolicySetAttachmentOrService().get(i));
				assertFalse(ret);
				break;
			}
		}
	}

	@Test
	public final void test_check_ASM50002_ASM40003() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Class<?>[] classes = new Class[2];
		classes[0] = ComponentService.class;
		classes[1] = ArrayList.class;
		Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM50002_ASM40003", classes);
		method.setAccessible(true);

		for (ComponentWrapper componentWrapper :compositeWrapper.listComponentWrappers)
		{
			Component component = componentWrapper.getScaModelComponent();
			ComponentType componentType = componentWrapper.getScaModelComponentType();

			List<String> referenceNames = new ArrayList<String>();
			referenceNames.add("HelloWorldServiceCompType");
			for (int j = 0; j < component.getServiceOrReferenceOrProperty().size(); j++)
			{
				if(component.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentService.class))
				{
					ComponentService cs = (ComponentService) component.getServiceOrReferenceOrProperty().get(j);

					Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, cs, referenceNames);
					assertTrue(ret);
				}
			}

			referenceNames.clear();
			referenceNames.add("HelloWorldServiceCompType");
			for (int j = 0; j < componentType.getServiceOrReferenceOrProperty().size(); j++)
			{
				if(componentType.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentService.class))
				{
					ComponentService cs = (ComponentService) componentType.getServiceOrReferenceOrProperty().get(j);

					Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, cs, referenceNames);
					assertFalse(ret);
				}
			}
			break;
		}
	}

	@Test
	public final void test_check_ASM60003() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Class<?>[] classes = new Class[1];
		classes[0] = Service.class;
		Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM60003", classes);
		method.setAccessible(true);

		conformanceManager4ReferenceAndService.serviceNames.add("HelloWorldService");

		for (int i = 0; i < compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().size(); i++)
		{
			if(compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Service.class))
			{
				Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, compositeWrapper.getComposite()
				        .getRequiresOrPolicySetAttachmentOrService().get(i));
				assertFalse(ret);
			}
		}

	}

	@Test
	public final void test_check_ASM60006() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Class<?>[] classes = new Class[2];
		classes[0] = Reference.class;
		classes[1] = ArrayList.class;
		Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM60006", classes);
		method.setAccessible(true);

		List<String> referenceNames = new ArrayList<String>();
		referenceNames.add("compositeRef");
		for (int i = 0; i < compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().size(); i++)
		{
			if(compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Reference.class))
			{
				Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, compositeWrapper.getComposite()
				        .getRequiresOrPolicySetAttachmentOrService().get(i), referenceNames);
				assertFalse(ret);
				break;
			}
		}
	}

	@Ignore
	@Test
	public final void test_check_ASM50039() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {

		for (ComponentWrapper componentWrapper :compositeWrapper.listComponentWrappers)
		{
			Component component = componentWrapper.getScaModelComponent();
			ComponentType componentType = componentWrapper.getScaModelComponentType();

			for (int j = 0; j < component.getServiceOrReferenceOrProperty().size(); j++)
			{
				if(component.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentReference.class))
				{
					Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM50039", ComponentReference.class);
					method.setAccessible(true);
					ComponentReference cr = (ComponentReference) component.getServiceOrReferenceOrProperty().get(j);
					Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, cr);
					assertFalse(ret);
					break;
				}
			}

			for (int j = 0; j < componentType.getServiceOrReferenceOrProperty().size(); j++)
			{
				if(componentType.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentTypeReference.class))
				{
					Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM50039", ComponentTypeReference.class);
					method.setAccessible(true);
					ComponentTypeReference cr = (ComponentTypeReference) componentType.getServiceOrReferenceOrProperty().get(j);
					Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, cr);
					assertFalse(ret);
					break;
				}
			}
		}

		for (int i = 0; i < compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().size(); i++)
		{
			if(compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Reference.class))
			{
				Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM50039", Reference.class);
				method.setAccessible(true);
				Reference r = (Reference) compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i);
				Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, r);
				assertTrue(ret);
				break;
			}
		}
	}

	@Test
	public final void test_check_ASM50040() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {

		for (ComponentWrapper componentWrapper :compositeWrapper.listComponentWrappers)
		{
			Component component = componentWrapper.getScaModelComponent();
			ComponentType componentType = componentWrapper.getScaModelComponentType();

			int num = 1;
			for (int j = 0; j < component.getServiceOrReferenceOrProperty().size(); j++)
			{
				if(component.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentReference.class) && (num == 2))
				{
					num++;
					Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM50040", ComponentReference.class);
					method.setAccessible(true);
					ComponentReference cr = (ComponentReference) component.getServiceOrReferenceOrProperty().get(j);
					Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, cr);
					assertFalse(ret);
					break;
				}
			}

			num = 1;
			for (int j = 0; j < componentType.getServiceOrReferenceOrProperty().size(); j++)
			{
				if(componentType.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentTypeReference.class) && (num == 2))
				{
					Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM50040", ComponentTypeReference.class);
					method.setAccessible(true);
					ComponentTypeReference cr = (ComponentTypeReference) componentType.getServiceOrReferenceOrProperty().get(j);
					Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, cr);
					assertFalse(ret);
					break;
				}
			}
		}

		int num = 1;
		for (int i = 0; i < compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().size(); i++)
		{
			if(compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Reference.class) && (num == 2))
			{
				Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM50040", Reference.class);
				method.setAccessible(true);
				Reference r = (Reference) compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i);
				Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, r);
				assertTrue(ret);
				break;
			}
		}
	}

	@Test
	public final void test_check_ASM50041() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {

		for (ComponentWrapper componentWrapper :compositeWrapper.listComponentWrappers)
		{
			Component component = componentWrapper.getScaModelComponent();
			ComponentType componentType = componentWrapper.getScaModelComponentType();

			int num = 1;
			for (int j = 0; j < component.getServiceOrReferenceOrProperty().size(); j++)
			{
				if(component.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentReference.class) && (num == 3))
				{
					num++;
					Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM50041", ComponentReference.class);
					method.setAccessible(true);
					ComponentReference cr = (ComponentReference) component.getServiceOrReferenceOrProperty().get(j);
					Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, cr);
					assertFalse(ret);
					break;
				}
			}

			num = 1;
			for (int j = 0; j < componentType.getServiceOrReferenceOrProperty().size(); j++)
			{
				if(componentType.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentTypeReference.class) && (num == 3))
				{
					Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM50041", ComponentTypeReference.class);
					method.setAccessible(true);
					ComponentTypeReference cr = (ComponentTypeReference) componentType.getServiceOrReferenceOrProperty().get(j);
					Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, cr);
					assertFalse(ret);
					break;
				}
			}
		}

		int num = 1;
		for (int i = 0; i < compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().size(); i++)
		{
			if(compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Reference.class) && (num == 3))
			{
				Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM50041", Reference.class);
				method.setAccessible(true);
				Reference r = (Reference) compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i);
				Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, r);
				assertFalse(ret);
				break;
			}
		}
	}

	@Test
	public final void test_check_ASM50026() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {

		for (ComponentWrapper componentWrapper :compositeWrapper.listComponentWrappers)
		{
			Component component = componentWrapper.getScaModelComponent();
			ComponentType componentType = componentWrapper.getScaModelComponentType();

			int num = 1;
			for (int j = 0; j < component.getServiceOrReferenceOrProperty().size(); j++)
			{
				if(component.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentReference.class) && (num == 4))
				{
					num++;
					Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM50026", ComponentReference.class);
					method.setAccessible(true);
					ComponentReference cr = (ComponentReference) component.getServiceOrReferenceOrProperty().get(j);
					Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, cr);
					assertFalse(ret);
					break;
				}
			}

			num = 1;
			for (int j = 0; j < componentType.getServiceOrReferenceOrProperty().size(); j++)
			{
				if(componentType.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentTypeReference.class) && (num == 4))
				{
					Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM50026", ComponentTypeReference.class);
					method.setAccessible(true);
					ComponentTypeReference cr = (ComponentTypeReference) componentType.getServiceOrReferenceOrProperty().get(j);
					Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, cr);
					assertFalse(ret);
					break;
				}
			}
		}

		int num = 1;
		for (int i = 0; i < compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().size(); i++)
		{
			if(compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Reference.class) && (num == 4))
			{
				Method method = ConformanceManager4ReferenceAndService.class.getDeclaredMethod("check_ASM50026", Reference.class);
				method.setAccessible(true);
				Reference r = (Reference) compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i);
				Boolean ret = (Boolean) method.invoke(conformanceManager4ReferenceAndService, r);
				assertFalse(ret);
				break;
			}
		}
	}
}
