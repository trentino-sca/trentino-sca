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

import static org.junit.Assert.assertTrue;

import java.io.File;
import java.io.IOException;

import org.apache.log4j.Logger;
import org.apache.log4j.xml.DOMConfigurator;
import org.junit.BeforeClass;
import org.junit.Test;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.tools.trengen.TrentinoTest;

/**
 * This class is for testing the Xsd-validation.
 */
public class XsdValidationTest extends TrentinoTest {
	protected static final Logger	logger	= Logger.getLogger(XsdValidationTest.class);

	@BeforeClass
	public static void init() throws IOException, Exception
	{
		 Trengen.initInstance("-cont",new File(ScaValidationLoaderClass.TRENGEN_SCAVALIDATIONFOLDER).getCanonicalPath());
	}

	@Test
	public void validateArtifact() {
		String localCompositeString = ScaValidationLoaderClass.LOCAL_COMPOSITE.toString().replace("file:", "");
		boolean result = XsdValidator.validateArtifact(localCompositeString);
		assertTrue(result);
	}
}
