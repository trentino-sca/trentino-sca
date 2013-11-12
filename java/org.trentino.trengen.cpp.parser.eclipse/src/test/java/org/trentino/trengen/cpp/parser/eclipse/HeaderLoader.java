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
package org.trentino.trengen.cpp.parser.eclipse;

import java.io.File;
import java.net.URISyntaxException;
import java.net.URL;

public final class HeaderLoader {
	private HeaderLoader () {
	}

	public static URL	BASICCALCULATOR_CONTRIBUTION	= HeaderLoader.class.getResource("basiccalculator");

	public static String getFile(String name) {

		URL url = HeaderLoader.class.getResource(name);

		try
		{
			return new File(url.getFile()).getAbsolutePath();
		} catch (Exception e)
		{
			throw new IllegalStateException("Cannot open header file" + name);
		}
	}
}
