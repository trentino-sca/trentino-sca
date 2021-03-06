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
import java.io.IOException;

import org.apache.log4j.Logger;
import org.apache.log4j.xml.DOMConfigurator;
import org.junit.Test;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.generation.CPPModelProvider;
import org.trentino.trengen.tools.generation.modelloader.SCAModelToSCAMirrorModelConverter;
import org.trentino.trengen.tools.samples.SamplesClassLoader;
import org.trentino.trengen.tools.scavalidation.ConformanceManagerCppImplArtifactsEclipseCDT;
import org.trentino.trengen.tools.scavalidation.ContributionTypeWrapper;
import org.trentino.trengen.tools.scavalidation.ScaValidationLoaderClass;
import org.trentino.trengen.tools.scavalidation.ScaValidationManager;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.tools.trengen.TrentinoTest;

public class TestGenerationProxiesWrappersBasicCalculatorFromSCDL extends TrentinoTest {

	protected static final Logger	                            logger	                                  = Logger.getLogger(TestGenerationProxiesWrappersBasicCalculatorFromSCDL.class);

	static
	{
		DOMConfigurator.configure(ConfigLoader.LOG_CONFIG_XML_DEBUG);
	}

	private static ConformanceManagerCppImplArtifactsEclipseCDT	conformanceManagerCppImplArtifactsEclipse	= new ConformanceManagerCppImplArtifactsEclipseCDT();

	@Test
	public void dummyTest() {
		System.out.println(SamplesClassLoader.BASICCALCULATOR_CONTRIBUTION_STRING);
		try
		{
			Trengen.getInstance().setContributionTypeWrapper(createContributonTypeWrapper());
			SCAModelToSCAMirrorModelConverter converter = new SCAModelToSCAMirrorModelConverter(new CPPModelProvider(
			        conformanceManagerCppImplArtifactsEclipse));
			ContextProxiesWrappers context = new ContextProxiesWrappers(converter);
			context.setOutputDir(new File(".\\target\\exampleProxiesWrappers"));
			ProxyGenerator gen = new ProxyGenerator(context);
			gen.generate();
		} catch (TrengenException e)
		{
			e.printStackTrace();
		} catch (Exception e)
		{
			e.printStackTrace();
		}
	}

	private ContributionTypeWrapper createContributonTypeWrapper() throws IOException, Exception {
		Trengen.initInstance("-cont",new File(SamplesClassLoader.BASICCALCULATOR_CONTRIBUTION_STRING).getCanonicalPath());
		Trengen.getInstance().setScaValidationFolder(new File(SamplesClassLoader.BASICCALCULATOR_CONTRIBUTION_STRING));
		
		ScaValidationManager scaValidationManager = new ScaValidationManager(conformanceManagerCppImplArtifactsEclipse);
		// public static ContributionTypeWrapper contributionTypeWrapper = new
		// ContributionTypeWrapper();
		ContributionTypeWrapper contributionTypeWrapper = null;
		try
		{
			contributionTypeWrapper = scaValidationManager.validate(Trengen.getScaValidationFolder(),Trengen.getScaValidationFolder().get(0));
		} catch (Exception e)
		{
			e.printStackTrace();
		}
		return contributionTypeWrapper;
	}
}
