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

package org.trentino.trengen.tools.generation.proxieswrappers;

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

import org.apache.log4j.Logger;
import org.apache.log4j.xml.DOMConfigurator;
import org.junit.Test;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.cpp.model.ClassMethodArgument;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.generation.CPPModelProvider;
import org.trentino.trengen.tools.generation.modelloader.SCAModelToSCAMirrorModelConverter;
import org.trentino.trengen.tools.scavalidation.ConformanceManagerCppImplArtifactsEclipseCDT;
import org.trentino.trengen.tools.templates.TemplateLoaderClass;
import org.trentino.trengen.tools.trengen.TrentinoTest;

import freemarker.template.Configuration;
import freemarker.template.DefaultObjectWrapper;
import freemarker.template.Template;
import freemarker.template.TemplateException;

/**
 * This class is testing the model loader with the in memory basic calculator
 * sample The output is not compared with any reference but instead we trace
 */
public class TestGenerationProxiesWrappersBasicCalculator extends TrentinoTest {
	protected static final Logger	logger	= Logger.getLogger(TestGenerationProxiesWrappersBasicCalculator.class);

	static
	{
		DOMConfigurator.configure(ConfigLoader.LOG_CONFIG_XML_DEBUG);
	}

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
				cppTp = config.getTemplate("ProxyGenerator_cpp.ftl");
			} catch (IOException e)
			{
				throw new IllegalStateException("cannot create template");
			}

			File outputDir = new File(".\\target\\exampleProxiesWrappers");
			if(!outputDir.exists())
			{
				outputDir.mkdirs();
			}
			String fileName = "TrentinoGenProxiesWrappers";

			FileOutputStream fos;
			try
			{
				fos = new FileOutputStream(new File(outputDir, fileName + ".cpp"));
			} catch (FileNotFoundException e)
			{
				throw new TrengenException(e);
			}

			Map<String, java.lang.Object> root = new HashMap<String, java.lang.Object>();
			SCAModelToSCAMirrorModelConverter converter = new SCAModelToSCAMirrorModelConverter(var());
			ContextProxiesWrappers context = new ContextProxiesWrappers(converter, "BasicCalculator");
			context.setOutputDir(new File(".", "proxygen"));
			root.put("context", context);
			root.put("serviceInterfacesList", getServiceInterfaces());
			root.put("referenceInterfacesList", getReferenceInterfaces());
			root.put("includesList", getIncludesList());

			String fileNam = "TrentinoGenProxiesWrappers";

			root.put("headerFileName", fileNam);
			root.put("rootPrefix", "BasicCalculator");
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

	private CPPModelProvider var() {
	    return new CPPModelProvider(new ConformanceManagerCppImplArtifactsEclipseCDT());
    }

	private List<String> getIncludesList() {
		List<String> list = new ArrayList<String>();
		list.add("deneme");
		return list;

	}

	private List<ReferenceServiceInterface> getServiceInterfaces() {
		List<ReferenceServiceInterface> listServiceInterfaces = new ArrayList<ReferenceServiceInterface>();

		ReferenceServiceInterface serviceInterface = new ReferenceServiceInterface();
		serviceInterface.setInterfaceClassName("Calculator");
		serviceInterface.setInterfaceClassNamespaces("Trentino_Example_BasicCalculator");
		serviceInterface.setInterfaceClassNamespacesSemicolonSeperated("Trentino::Example::BasicCalculator");

		serviceInterface.setInterfaceHeader("../BasicCalculator/services/TrentinoExampleBasicCalculatorCalculator.h");
		listServiceInterfaces.add(serviceInterface);

		// add an interface method for the invoke method generation test
		InterfaceMethod interfaceMethod = new InterfaceMethod("divide", "int");
		ClassMethodArgument classMethodArg = new ClassMethodArgument("a", "int");
		ClassMethodArgument classMethodArg2 = new ClassMethodArgument("b", "int");
		interfaceMethod.getArguments().add(classMethodArg);
		interfaceMethod.getArguments().add(classMethodArg2);
		serviceInterface.getInterfaceMethods().add(interfaceMethod);
		// end of interface method creation

		return listServiceInterfaces;
	}

	private List<ReferenceServiceInterface> getReferenceInterfaces() {
		List<ReferenceServiceInterface> listReferenceInterfaces = new ArrayList<ReferenceServiceInterface>();
		ReferenceServiceInterface referenceInterface = new ReferenceServiceInterface();
		referenceInterface.setInterfaceClassName("Divider");
		referenceInterface.setInterfaceClassNamespaces("Trentino_Example_BasicCalculator");
		referenceInterface.setInterfaceClassNamespacesSemicolonSeperated("Trentino::Example::BasicCalculator");

		// add interface method divide
		InterfaceMethod interfaceMethod = new InterfaceMethod("divide", "int");
		ClassMethodArgument classMethodArg = new ClassMethodArgument("a", "int");
		ClassMethodArgument classMethodArg2 = new ClassMethodArgument("b", "int");
		interfaceMethod.getArguments().add(classMethodArg);
		interfaceMethod.getArguments().add(classMethodArg2);
		referenceInterface.getInterfaceMethods().add(interfaceMethod);

		// one additional test
		// InterfaceMethod interfaceMethod2 = new InterfaceMethod("deneme",
		// "int");
		// ClassMethodArgument classMethodArg3 = new
		// ClassMethodArgument("argOfDeneme", "string");
		// interfaceMethod2.getArguments().add(classMethodArg3);
		// referenceInterface.getInterfaceMethods().add(interfaceMethod2);

		referenceInterface.setInterfaceHeader("../BasicCalculator/services/TrentinoExampleBasicCalculatorDivider.h");
		listReferenceInterfaces.add(referenceInterface);

		return listReferenceInterfaces;
	}
}
