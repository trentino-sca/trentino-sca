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

package org.trentino.trengen.tools.generation.modelloader;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.annotation.processing.FilerException;

import org.junit.Test;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.scamodelmirror.CPPImplementation;
import org.trentino.trengen.scamodelmirror.CPPImplementationScope;
import org.trentino.trengen.scamodelmirror.CPPInterface;
import org.trentino.trengen.scamodelmirror.Component;
import org.trentino.trengen.scamodelmirror.ComponentReference;
import org.trentino.trengen.scamodelmirror.ComponentService;
import org.trentino.trengen.scamodelmirror.ComponentType;
import org.trentino.trengen.scamodelmirror.ComponentTypeReference;
import org.trentino.trengen.scamodelmirror.Composite;
import org.trentino.trengen.scamodelmirror.ContributionType;
import org.trentino.trengen.scamodelmirror.DeployableType;
import org.trentino.trengen.tools.templates.TemplateLoaderClass;
import org.trentino.trengen.tools.trengen.TrentinoTest;
import org.trentino.trengen.xml.schema.AnyURI;
import org.trentino.trengen.xml.schema.NCName;
import org.trentino.trengen.xml.schema.Name;
import org.trentino.trengen.xml.schema.QName;

import freemarker.template.Configuration;
import freemarker.template.DefaultObjectWrapper;
import freemarker.template.Template;
import freemarker.template.TemplateException;

/**
 * This class is testing the model loader with the in memory basic calculator
 * sample The output is not compared with any reference but instead we trace
 */
public class TestGeneratorModelLoaderTestBasicCalculator extends TrentinoTest {
	@Test
	public void dummyTest() {
		try
		{
			Configuration config = new Configuration();
			config.setClassForTemplateLoading(TemplateLoaderClass.class, "");
			config.setObjectWrapper(new DefaultObjectWrapper());
			Template cppTp = null;

			try
			{
				cppTp = config.getTemplate("ModelLoader_cpp.ftl");
			} catch (IOException e)
			{
				throw new IllegalStateException("cannot create template");
			}

			File outputDir = new File(".\\target\\exampleModelLoader");
			if(!outputDir.exists())
			{
				outputDir.mkdirs();
			}
			String fileName = "TrentinoGenModelLoader";

			FileOutputStream fos;
			try
			{
				fos = new FileOutputStream(new File(outputDir, fileName + ".cpp"));
			} catch (FileNotFoundException e)
			{
				throw new TrengenException(e);
			}

			Map<String, java.lang.Object> root = new HashMap<String, java.lang.Object>();
			root.put("mirrorObjectList", getExampleMirrorBasicCalculator());
			root.put("mirrorContribution", getExampleMirrorBasicCalculatorContribution());
			root.put("mirrorComponentTypeList", getExampleMirrorBasicCalculatorComponentType());
			root.put("componentTypeComponentAssocList", getExampleMirrorBasicCalculatorComponentTypeComponentAssoc());
			root.put("applicationName", "BASICCALCULATOR");
			root.put("contributionName", "BasicCalculator");
			try
			{

				PrintWriter pw = new PrintWriter(fos);
				cppTp.process(root, pw);
				pw.flush();
			}

			catch (FilerException filerEx)
			{
				System.out.println("Problem with Processing Environment Filer: " + filerEx.getMessage());
				throw new IllegalStateException(filerEx);
			}

			catch (IOException ioEx)
			{
				throw new IllegalStateException(ioEx);

			} catch (TemplateException e)
			{
				e.printStackTrace();
				throw new IllegalStateException(e);
			} finally
			{
				if(fos != null)
				{
					try
					{
						fos.close();
					} catch (IOException e)
					{
						e.printStackTrace();
					}
				}
			}
		} catch (TrengenException e)
		{
			e.printStackTrace();
		} catch (Exception e)
		{
			e.printStackTrace();
		}
	}

	private List<CompositeMirrorWrapper> getExampleMirrorBasicCalculator() {
		// create a sevice and assoc it with a service
		CPPInterface calculatorServiceInterface = new CPPInterface();
		calculatorServiceInterface.setNameGen("calculatorServiceInterface2");
		Name name = new Name("Trentino$Example$BasicCalculator$Calculator");
		calculatorServiceInterface.setClazz(name);
		ComponentService calculatorService = new ComponentService();
		calculatorService.setName(new NCName("Calculator"));
		calculatorService.setNameGen("Calculator");
		calculatorService.setInterface(calculatorServiceInterface);

		// create a sevice and assoc it with a service
		CPPInterface interfaceReference = new CPPInterface();
		interfaceReference.setNameGen("dividerReferenceInterface2");
		name = new Name("Trentino$Example$BasicCalculator$Divider");
		interfaceReference.setClazz(name);
		ComponentReference dividerReference = new ComponentReference();
		dividerReference.setName(new NCName("Divider"));
		dividerReference.setNameGen("Divider");
		dividerReference.setInterface(interfaceReference);
		dividerReference.setMultiplicity("1..1");
		dividerReference.setAutowire(false);
		dividerReference.targets().add("DividerComponent/Divider");

		Component calculatorComponent = new Component();
		calculatorComponent.setName(new NCName("CalculatorComponent"));
		calculatorComponent.setNameGen("CalculatorComponent");
		calculatorComponent.serviceElements().add(calculatorService);
		calculatorComponent.referenceElements().add(dividerReference);

		// create a sevice(divider) and assoc it with an interface
		CPPInterface dividerServiceInterface = new CPPInterface();
		dividerServiceInterface.setNameGen("calculatorServiceInterface2");
		name = new Name("Trentino$Example$BasicCalculator$Divider");
		dividerServiceInterface.setClazz(name);
		ComponentService dividerService = new ComponentService();
		dividerService.setName(new NCName("Divider"));
		dividerService.setNameGen("Divider");
		dividerService.setInterface(dividerServiceInterface);

		CPPImplementation dividerComponentImpl = new CPPImplementation();
		dividerComponentImpl.setNameGen("dividerComponentImpl");
		name = new Name("Trentino$Example$BasicCalculator$DividerImpl");
		dividerComponentImpl.setClazz(name);
		CPPImplementationScope dividerComponentImplScope = new CPPImplementationScope("composite");
		dividerComponentImplScope.setNameGen("dividerComponentImplScope");
		dividerComponentImpl.setScope(dividerComponentImplScope);

		Component dividerComponent = new Component();
		dividerComponent.setName(new NCName("DividerComponent"));
		dividerComponent.setNameGen("DividerComponent");
		dividerComponent.serviceElements().add(dividerService);
		dividerComponent.setImplementation(dividerComponentImpl);

		Composite composite = new Composite();
		composite.setName(new NCName("BasicCalculatorComposite"));
		composite.setNameGen("BasicCalculatorComposite");
		composite.setTargetNamespace(new AnyURI("BasicCalculatorNamespace"));
		composite.componentElements().add(calculatorComponent);
		composite.componentElements().add(dividerComponent);

		CompositeMirrorWrapper compositeMirrorWrapper = new CompositeMirrorWrapper();
		compositeMirrorWrapper.setNameGen("BasicCalculatorCompositeWrapper");
		compositeMirrorWrapper.setComposite(composite);

		List<CompositeMirrorWrapper> compositeWrapperList = new ArrayList<CompositeMirrorWrapper>();
		compositeWrapperList.add(compositeMirrorWrapper);
		return compositeWrapperList;
	}

	/**
	 * This class returns the mirror componentTypes as a map, fileName of
	 * componentType is given as a key
	 */
	private List<ComponentType> getExampleMirrorBasicCalculatorComponentType() {
		List<ComponentType> componentTypeList = new ArrayList<ComponentType>();
		ComponentType dividerComponent = new ComponentType();

		CPPInterface dividerServiceInterface = new CPPInterface();
		dividerServiceInterface.setNameGen("calculatorServiceInterface");
		dividerServiceInterface.setClazz(new Name("Trentino$Example$BasicCalculator$Divider"));
		ComponentService dividerService = new ComponentService();
		dividerService.setName(new NCName("Divider"));
		dividerService.setNameGen("Divider");
		dividerService.setInterface(dividerServiceInterface);

		dividerComponent.setNameGen("DividerImpl");
		dividerComponent.serviceElements().add(dividerService);
		componentTypeList.add(dividerComponent);

		CPPInterface calculatorServiceInterface = new CPPInterface();
		calculatorServiceInterface.setNameGen("calculatorServiceInterface");
		Name name = new Name("Trentino$Example$BasicCalculator$Calculator");
		calculatorServiceInterface.setClazz(name);
		ComponentService calculatorService = new ComponentService();
		calculatorService.setName(new NCName("Calculator"));
		calculatorService.setNameGen("Calculator");
		calculatorService.setInterface(calculatorServiceInterface);

		// create a sevice and assoc it with a service
		CPPInterface interfaceReference = new CPPInterface();
		interfaceReference.setNameGen("dividerReferenceInterface");
		name = new Name("Trentino$Example$BasicCalculator$Divider");
		interfaceReference.setClazz(name);
		ComponentTypeReference dividerReference = new ComponentTypeReference();
		dividerReference.setName(new NCName("Divider"));
		dividerReference.setNameGen("Divider2");
		dividerReference.setInterface(interfaceReference);
		dividerReference.setMultiplicity("1..1");
		dividerReference.setAutowire(false);
		dividerReference.targets().add("DividerComponent/Divider");

		ComponentType calculatorComponent = new ComponentType();
		calculatorComponent.setNameGen("CalculatorImpl");
		calculatorComponent.serviceElements().add(calculatorService);
		calculatorComponent.referenceElements().add(dividerReference);
		componentTypeList.add(calculatorComponent);

		return componentTypeList;
	}

	private List<ComponentComponentTypeAssociation> getExampleMirrorBasicCalculatorComponentTypeComponentAssoc() {
		List<ComponentComponentTypeAssociation> componentTypeComponentAssocMap = new ArrayList<ComponentComponentTypeAssociation>();
		ComponentComponentTypeAssociation componentComponentTypeAssoc = new ComponentComponentTypeAssociation(
		        "BasicCalculatorComposite_CalculatorComponent", "CalculatorImpl");
		componentTypeComponentAssocMap.add(componentComponentTypeAssoc);

		ComponentComponentTypeAssociation componentComponentTypeAssoc2 = new ComponentComponentTypeAssociation(
		        "BasicCalculatorComposite_DividerComponent", "DividerImpl");
		componentTypeComponentAssocMap.add(componentComponentTypeAssoc2);

		return componentTypeComponentAssocMap;
	}

	private ContributionType getExampleMirrorBasicCalculatorContribution() {
		ContributionType contributionType = new ContributionType();
		contributionType.setNameGen("ContributionName");
		DeployableType deployable = new DeployableType();
		deployable.setNameGen("deployable");
		QName qName = new QName("xxx", "yyry", "zzzrr");
		qName.setNameGen("generatedQNameName");
		deployable.setComposite(qName);
		contributionType.deployableElements().add(deployable);

		return contributionType;
	}
}
