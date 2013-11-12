// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************
package org.trentino.trengen.cpp.parser.eclipse;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;

import org.junit.BeforeClass;
import org.junit.Test;
import org.trentino.trengen.cpp.model.ClassMethod;
import org.trentino.trengen.cpp.model.HeaderFile;

/**
 * @author z002ttbb
 *         This test check that Trentino is able to parse all the methods of an interface,
 *         including the ones declared in a base class
 */
public class BaseClassParserTest {

	/**
     * 
     */
	private static final String	COMPLEX_TYPE_WITH_BASECLASS	= "ComplexClassWithBaseClassesIncluded.h";
	/**
     * 
     */
	private static final String	CLASSNAME	                = "Test::Application::System2::Facade";

	private static HeaderFile	headerFile;

	@BeforeClass
	public static void getHeaderFile() {
		String path = COMPLEX_TYPE_WITH_BASECLASS;
		String inc1 = HeaderLoader.getFile("Test");
		headerFile = HeaderUtil.getHeaderFile(path, inc1);
	}

	@Test
	public void testBaseClassMethodIncludedUsingInclusionWithBracket() {
		String qName = CLASSNAME;
		String methodName = "method3";
		String expected = null;
		doTest(qName, methodName, expected);
	}

	@Test
	public void testBaseClassMethodIncludedBaseMethod1() {
		String qName = CLASSNAME;
		String methodName = "baseMethod1";
		String expected = null;
		doTest(qName, methodName, expected);
	}

	@Test
	public void testBaseClassMethodIncludedBaseMethod2() {
		String qName = CLASSNAME;
		String methodName = "baseMethod2";
		String expected = null;
		doTest(qName, methodName, expected);
	}

	private void doTest(String qName, String methodName, String expected) {
		assertNotNull("No header file found", headerFile);
		ClassMethod method = HeaderUtil.getMethod(headerFile, qName, methodName);
		assertNotNull("No method with name found: " + methodName, method);
	}
}
