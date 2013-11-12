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

import java.net.URL;

public final class ScaValidationLoaderClass {

	private ScaValidationLoaderClass () {
	}

	public static URL	  LOCAL_COMPOSITE	                 = ScaValidationLoaderClass.class.getResource("local_services_refs_wires.composite");
	private static String	TRENGEN_SCAVALIDATIONFOLDER_TEMP	= LOCAL_COMPOSITE.toString().replace("file:", "");
	public static String	TRENGEN_SCAVALIDATIONFOLDER	     = TRENGEN_SCAVALIDATIONFOLDER_TEMP.toString().replace(
	                                                                 "local_services_refs_wires.composite", "");
	public static URL	  HELLOWORLD_COMPONENTTYPE	         = ScaValidationLoaderClass.class.getResource("HelloWorldComponent4srw.componentType");
	public static URL	  CLIENT_COMPONENTTYPE	             = ScaValidationLoaderClass.class.getResource("ClientComponent4srw.componentType");
	public static URL	  HELLOWORLD_CPPHEADER	             = ScaValidationLoaderClass.class.getResource("HelloWorldComponent4srw.h");
	public static URL	  CLIENT_CPPHEADER	                 = ScaValidationLoaderClass.class.getResource("ClientComponent4srw.h");
	public static URL	  BASE_HEADER	                     = ScaValidationLoaderClass.class.getResource("Base.h");
	public static URL	  CHILD_HEADER	                     = ScaValidationLoaderClass.class.getResource("Child.h");

	public static URL	  SCAREFERENCEEXAMPLE_HEADER	     = ScaValidationLoaderClass.class.getResource("SCAReferenceExample.h");

	public static URL	  SAMPLE_CONTRIBUTION	             = ScaValidationLoaderClass.class.getResource("SampleContribution/meta-inf");

}
