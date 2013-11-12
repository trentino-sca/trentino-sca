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

package org.trentino.trengen.tools.scavalidation.utils;

import static org.junit.Assert.assertFalse;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.net.URL;

import org.apache.log4j.Logger;
import org.apache.log4j.xml.DOMConfigurator;
import org.junit.Test;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.trengen.Trengen;

public class FileURICheckerTest {
	protected static final Logger	logger	= Logger.getLogger(FileURICheckerTest.class);

	static
	{
		DOMConfigurator.configure(ConfigLoader.LOG_CONFIG_XML_DEBUG);
	}

	private boolean LoadConfig(final String configFileName) {
		try
		{
			URL url = this.getClass().getResource(configFileName);

			File configFile = new File(url.toURI());
			if(configFile.exists())
			{
				InputStream is = null;
				is = new FileInputStream(configFile);

				Trengen.getProperties().load(is);
			}
		} catch (Exception ex)
		{
			return false;
		}
		return true;
	}

	@Test
	public final void isDereferancableURI_uriIsNull_returnFalse() {
		boolean result = FileURIChecker.isDereferancableURI(null);
		assertFalse("Null URI check fails for @file attribute", result);
	}

	/**
	 * The goal of this test is to be able to receive 'false' as the return
	 * value once the defined IP is not appropriate within the config.
	 */
	@Test
	public final void isDereferancableURI_IPisUnappropriate_returnFalse() {
		if(!LoadConfig("TrengenUnappropriateWrongIp.config"))
		{
			return;
		}
		// because we are testing the correctness of IP, we gave a correct URI.
		boolean result = FileURIChecker.isDereferancableURI("http://www.google.com");
		assertFalse("Defined ip in the proxy is not appropriate", result);
	}
}
