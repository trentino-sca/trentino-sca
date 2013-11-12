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

import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.fail;

import java.io.File;

import org.apache.log4j.Logger;
import org.apache.log4j.xml.DOMConfigurator;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.samples.SamplesClassLoader;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.tools.trengen.TrentinoTest;

public class ScaValidationManagerTest extends TrentinoTest {
	protected static final Logger	                  logger	                                  = Logger.getLogger(ScaValidationManagerTest.class);
	private static IConformanceManagerCppImpArtifacts	conformanceManagerCppImplArtifactsEclipse	= null;

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		conformanceManagerCppImplArtifactsEclipse = new ConformanceManagerCppImplArtifactsEclipseCDT();
	}

	@Test
	public final void testValidate() throws Exception {
        Trengen.initInstance("-cont",SamplesClassLoader.SAMPLE_CONTRIBUTION.toString().replace("file:", ""));
		String sampleCont = SamplesClassLoader.SAMPLE_CONTRIBUTION.toString().replace("file:", "");
		Trengen.getInstance().setScaValidationFolder(new File(sampleCont));
		ScaValidationManager scaValidationManager = new ScaValidationManager(conformanceManagerCppImplArtifactsEclipse);
		try
		{
			ContributionTypeWrapper result = scaValidationManager.validate(Trengen.getInstance().getScaValidationFolder(), new File(sampleCont));

			assertNotNull(result);
		} catch (ValidationException e)
		{
			fail(Trengen.getInstance().stringValueOf(e));
		} catch (Exception e)
		{
			fail(e.getMessage());
		}
	}

	@Test
	public final void testValidate_ContributionWithCompositeImp() throws Exception {
        Trengen.initInstance("-cont",SamplesClassLoader.SAMPLE_CONTRIBUTION_COMPOSITE_BY_IMPL.toString().replace("file:", ""));
		String sampleCont = SamplesClassLoader.SAMPLE_CONTRIBUTION_COMPOSITE_BY_IMPL.toString().replace("file:", "");
		Trengen.getInstance().setScaValidationFolder(new File(sampleCont));
		ScaValidationManager scaValidationManager = new ScaValidationManager(conformanceManagerCppImplArtifactsEclipse);
		try
		{
			ContributionTypeWrapper result = scaValidationManager.validate(Trengen.getInstance().getScaValidationFolder(), new File(sampleCont));
			assertNotNull(result);
		} catch (ValidationException e)
		{
			String stringValueOf = Trengen.getInstance().stringValueOf(e);
			logger.error(stringValueOf);
			e.printStackTrace();
			fail(stringValueOf);
		} catch (Exception e)
		{
			fail(e.getMessage());
		}
	}

	@Test(expected = ValidationException.class)
	public final void testValidate_NotValid() throws Exception {
		Trengen.initInstance("-cont",SamplesClassLoader.SAMPLE_CONTRIBUTION_NOT_VALID.toString().replace("file:", ""));
		String sampleCont = SamplesClassLoader.SAMPLE_CONTRIBUTION_NOT_VALID.toString().replace("file:", "");
		Trengen.getInstance().setScaValidationFolder(new File(sampleCont));
		ScaValidationManager scaValidationManager = new ScaValidationManager(conformanceManagerCppImplArtifactsEclipse);
		ContributionTypeWrapper result = scaValidationManager.validate(Trengen.getInstance().getScaValidationFolder(), new File(sampleCont));
		assertNull(result);

	}
	


}
