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

package org.trentino.trengen.tools.generation.reflection;

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
import org.trentino.trengen.tools.configuration.ConfigLoader;
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
public class TestGenerationReflectionBasicCalculator extends TrentinoTest {

	protected static final Logger	logger	= Logger.getLogger(TestGenerationReflectionBasicCalculator.class);

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
				cppTp = config.getTemplate("ReflectionGenerator_cpp.ftl");
			} catch (IOException e)
			{
				throw new IllegalStateException("cannot create template");
			}

			File outputDir = new File(".\\target\\exampleReflection");
			if(!outputDir.exists())
			{
				outputDir.mkdirs();
			}
			String fileName = "TrentinoGenReflection";

			FileOutputStream fos;
			try
			{
				fos = new FileOutputStream(new File(outputDir, fileName + ".cpp"));
			} catch (FileNotFoundException e)
			{
				throw new TrengenException(e);
			}

			Map<String, java.lang.Object> root = new HashMap<String, java.lang.Object>();
			root.put("reflectionObjectList", getReflectionObjects());
			root.put("includesList", getReflexIncludes());
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

	private List<ReflectionObject> getReflectionObjects() {
		List<ReflectionObject> listReflectionObjects = new ArrayList<ReflectionObject>();
		ReflectionObject refObj = new ReflectionObject();
		refObj.setImplHeader("HeaderGiven");
		refObj.setImplClass("Trentino_Example_BasicCalculator_CalculatorImpl");
		refObj.setImplClassAsNamespace("Trentino::Example::BasicCalculator::CalculatorImpl");
		Reference ref = new Reference();
		ref.setReferenceInterfaceHeader("Trentino::Example::BasicCalculator::Divider");
		ref.setNameGen("Divider");
		ref.setReferenceName("Divider");
		ref.setInterfaceClassNamespacesSemicolonSeperated("Trentino::Example::BasicCalculator::Divider");
		ref.setReferenceInterfaceClass("ComponentContext");
		refObj.getListReferences().add(ref);

		Service service = new Service();
		service.setServiceName("Calculator");
		service.setServiceInterfaceClass("Divider");
		service.setServiceInterfaceHeader("Trentino::Example::BasicCalculator::Calculator");
		refObj.getListServices().add(service);

		listReflectionObjects.add(refObj);
		return listReflectionObjects;
	}

	private List<String> getReflexIncludes() {
		List<String> listReflectionObjects = new ArrayList<String>();
		listReflectionObjects.add("HeaderGiven.h");
		return listReflectionObjects;
	}

}
