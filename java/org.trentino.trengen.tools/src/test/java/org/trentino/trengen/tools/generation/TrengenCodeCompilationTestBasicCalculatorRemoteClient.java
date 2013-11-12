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
package org.trentino.trengen.tools.generation;

import static org.junit.Assert.assertTrue;

import java.io.File;
import java.io.FileFilter;
import java.util.ArrayList;
import java.util.List;

import org.junit.BeforeClass;
import org.junit.Test;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.tools.trengen.TrentinoTest;

/**
 * @author z002ttbb
 */
public class TrengenCodeCompilationTestBasicCalculatorRemoteClient extends TrentinoTest {

    private static TrengenCodeCompilationTestUtil util;


	static String contributionName = "BasicCalculatorRemoteClient_Source";
	static String contributionPath = "BasicCalculatorRemoteClient_Source";
	
	@BeforeClass
	public static void init() throws TrengenException, Exception {
		List<String> paths = new ArrayList<String>();
		paths.add("services/TrentinoExampleBasicCalculatorRemoteClientBasicCalculator.tidl.properties");
		util = new TrengenCodeCompilationTestUtil(contributionName, contributionPath,paths,"BasicCalculatorGlobal.h");
	}

	@Test
	public void testCanCompile() throws Exception {
		FileFilter filter = new FileFilter() {
			
			@Override
			public boolean accept(File pathname) {
				return pathname.isFile() && pathname.getName().endsWith(".cpp");
			}
		};
		File[] files = util.generationDirectory.listFiles( filter );
		List<String> macros = new ArrayList<String>();
		macros.add("/D BASICCALCULATOR_EXPORTS");
		assertTrue(util.compile(files, macros));
	}



}
