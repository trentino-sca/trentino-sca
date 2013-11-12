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
package org.trentino.trengen.tools.configuration;

import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;

import org.apache.log4j.Logger;

public class ConfigLoader {
	protected static final Logger	logger	                           = Logger.getLogger(ConfigLoader.class);

	public static URL	          LOG_CONFIG_XML	                   = ConfigLoader.class.getResource("log4j.xml");
	public static URL	          LOG_CONFIG_XML_DEBUG	               = ConfigLoader.class.getResource("log4j_debug.xml");
	public static URL	          TRENGEN_CONFIG	                   = ConfigLoader.class.getResource("trengen.config");
	public static URL	          UNAPPROPRIATE_WRONGIP_TRENGEN_CONFIG	= ConfigLoader.class.getResource("TrengenUnappropriateWrongIp.config");

	private ConfigLoader () {
	}

	static
	{
		// try to load the configuration from <Trentino root>/cfg/trengen.comfig
		File file = new File("../cfg/trengen.config");
		boolean loaded = false;
		if(file.exists())
		{
			try
			{
				TRENGEN_CONFIG = file.toURI().toURL();
				loaded = true;
			} catch (MalformedURLException e)
			{
				// Mute, minimal log
				logger.error("../cfg/trengen.config not loaded");
				loaded = false;
			}
		}
		if(!loaded)
		{
			file = new File("trengen.config");
			if(file.exists())
			{
				try
				{
					TRENGEN_CONFIG = file.toURI().toURL();
				} catch (MalformedURLException e)
				{
					// Mute, minimal log
					logger.error("trengen.config not found");
				}
			}
		}
	}

}
