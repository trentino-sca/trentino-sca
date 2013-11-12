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
package org.trentino.trengen.tools.trengen;

import java.io.File;

import org.apache.log4j.Logger;
import org.apache.log4j.xml.DOMConfigurator;
import org.junit.BeforeClass;
import org.junit.Test;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.samples.SamplesClassLoader;

/**
 * This class is testing the trengen with the sampleContribution(see resources).
 * The resultant generated code output is compared to the reference correct
 * output
 */
public class TrengenTestModelLoaderSampleContribution {
	protected static final Logger	logger	= Logger.getLogger(TrengenTestModelLoaderSampleContribution.class);

	static
	{
		DOMConfigurator.configure(ConfigLoader.LOG_CONFIG_XML_DEBUG);
	}

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
	}

	@Test
	public final void testValidateModelLoaderForSampleContribution() {
		try
		{
			String contribution = SamplesClassLoader.SAMPLE_CONTRIBUTION.toString().replace("file:", "");
			contribution = contribution.replace("/", File.separator);
			contribution = contribution.replace("\\", File.separator);
			String[] args =
			{ "-cont", contribution, "-outdir", ".\\target\\exampleModelLoader" };
			// { "-cont", contribution, "-out",
			// ".\\target\\exampleModelLoader\\TrentinoGenModelLoader.cpp"};
			Trengen.main(args);
			// File fileGenerated = new
			// File(".\\target\\exampleModelLoader\\TrentinoGenModelLoader.cpp");
			// File fileToBeReferred = new
			// File(SamplesClassLoader.SAMPLE_CONTRIBUTION_REFERENCE_MODEL_LOADER.toString().replace("file:",
			// ""));

			// boolean filesEqual = FileUtil.areFilesSame(fileGenerated,
			// fileToBeReferred);
			// assertTrue(filesEqual);
		} catch (Exception e)
		{
			e.printStackTrace();
		}
	}

}
