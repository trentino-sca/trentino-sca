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

import static org.junit.Assert.assertNull;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBElement;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;

import org.apache.log4j.Logger;
import org.apache.log4j.xml.DOMConfigurator;
import org.junit.Before;
import org.junit.Test;
import org.trentino.trengen.sca.model.CPPInterface;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.Composite;
import org.trentino.trengen.sca.model.Reference;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.scavalidation.utils.UnZipUtil;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.tools.trengen.TrentinoTest;
import org.trentino.trengen.tools.samples.SamplesClassLoader;

/**
 * This sample application demonstrates how to use ConformanceManager functions.
 */
public class ConformanceManagerTest extends TrentinoTest {

	protected static final Logger	                     logger	= Logger.getLogger(ConformanceManagerTest.class);
	private ConformanceManagerCppImplArtifactsEclipseCDT	mng	= null;



	@Before
	public final void initialize() {
		String fileName = ConfigLoader.TRENGEN_CONFIG.toString().replace("file:", "");

		File configFile = new File(fileName);
		if(configFile.exists())
		{
			InputStream is = null;
			try
			{
				is = new FileInputStream(fileName);
			} catch (FileNotFoundException e)
			{
				e.printStackTrace();
			}
			try
			{
				Trengen.getProperties().load(is);
			} catch (IOException e)
			{
				e.printStackTrace();
			}
		}
		// System.out.println(properties.getProperty("proxy.address.host"));
		// System.out.println(properties.getProperty("proxy.address.ip"));

		try
		{
			String contribution = SamplesClassLoader.SAMPLE_CONTRIBUTION.toString().replace("file:", "");
			contribution = contribution.replace("/", File.separator);
			contribution = contribution.replace("\\", File.separator);
			String[] args =
			{ "-cont", contribution };
			Trengen.initInstance(args);
			Trengen env = Trengen.getInstance();
			// CompositeOrFragmentFileHandler composite_handler = new
			// CompositeOrFragmentFileHandler();

			// Check and access the input SCA composite directory
			String name = contribution;

			if(null == name)
			{
				logger.error("Please provide a SCA composite directory name as a \"-cont\" option.");
				env.printUsage();
				System.exit(-1);
			}
			env.setScaValidationFolder(new File(name));

			File file = Trengen.getScaValidationFolder().get(0);
			if(!file.isDirectory())
			{
				if(name.endsWith(".zip"))
				{
					if(!UnZipUtil.extractFolder(file.getAbsolutePath()))
					{
						logger.error("Contribution can be specified either with a directory path or with a valid zip file");
						return;
					}
					else
					{
						String unzippedDirName = name.substring(0, name.lastIndexOf('.'));
						file.delete();
						env.setScaValidationFolder(new File(unzippedDirName));
					}
				}
				else
				{
					logger.error("Source should be either a directory or a valid zip file");
					return;
				}

			}
			mng = new ConformanceManagerCppImplArtifactsEclipseCDT();
			ScaValidationManager scaValidationManager = new ScaValidationManager(mng);
			if(null == scaValidationManager.validate(Trengen.getScaValidationFolder(),new File(name)))
			{
				logger.error("There is some problem in SCA Validation Manager");
				return;
			}
		} catch (Exception exception)
		{
			logger.error("Unexpected error occurred while runnning the Trengen tool. The Java exception is below.", exception);
			exception.printStackTrace();

		}

		logger.info("Finished!");
	}

	@Test
	public void validate() throws Exception {
		Trengen.initInstance("-cont",new File(ScaValidationLoaderClass.TRENGEN_SCAVALIDATIONFOLDER).getCanonicalPath());

		try
		{

			JAXBContext jc = JAXBContext.newInstance("org.trentino.trengen.sca.model");
			Unmarshaller u = jc.createUnmarshaller();

			JAXBElement<?> poElement = (JAXBElement<?>) u.unmarshal(new FileInputStream("local.composite"));
			Composite ct = (Composite) poElement.getValue();

			JAXBElement<?> poElement2 = (JAXBElement<?>) u.unmarshal(new FileInputStream("HelloWorldComponent.componentType"));
			assertNull(poElement2);

			ComponentType comp = (ComponentType) poElement2.getValue();
			ComponentWrapper cw = new ComponentWrapper();
			cw.setScaModelComponentType(comp);

			JAXBElement<?> poElement3 = (JAXBElement<?>) u.unmarshal(new FileInputStream("ClientComponent.componentType"));
			ComponentType comp2 = (ComponentType) poElement3.getValue();
			ComponentWrapper cw2 = new ComponentWrapper();
			cw2.setScaModelComponentType(comp2);

			CompositeWrapper compositeWrapper = new CompositeWrapper();
			compositeWrapper.setComposite(ct);
			Reference reference = new Reference();
			ComponentReference ref = new ComponentReference();
			for (int index = 0; index < compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().size(); index++)
			{
				if(compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(index).getClass()
				        .equals(org.trentino.trengen.sca.model.Reference.class))
				{
					reference = (Reference) compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(index);
				}
				else if(compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(index).getClass()
				        .equals(org.trentino.trengen.sca.model.Component.class))
				{
					if(index == 3)
					{
						Component component = (Component) compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(index);
						cw.setScaModelComponent(component);
					}
					else if(index == 4)
					{
						Component component = (Component) compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(index);
						cw2.setScaModelComponent(component);

						for (int h = 0; h < component.getServiceOrReferenceOrProperty().size(); h++)
						{
							if(component.getServiceOrReferenceOrProperty().get(h).getClass().equals(ComponentReference.class))
							{
								ref = (ComponentReference) component.getServiceOrReferenceOrProperty().get(h);
							}
						}
					}
				}
			}
			compositeWrapper.getListComponents().add(cw);
			compositeWrapper.getListComponents().add(cw2);
			if((reference.getInterface() != null) && (ref.getInterface() != null))
			{
				CPPInterface compositeInterface = (CPPInterface) reference.getInterface().getValue();
				CPPInterface componentInterface = (CPPInterface) ref.getInterface().getValue();
				if(!(mng.isSame(componentInterface, compositeInterface) || mng.isSubset(componentInterface, compositeInterface)))
				{
					System.out.println("no!!");
				}
				else
				{
					System.out.println("yes!!");
				}
			}

		} catch (JAXBException je)
		{
			logger.error("JAXBExpection occured in parsing ");
		} catch (IOException ioe)
		{
			logger.error("file could not be found");
		}

	}

}
