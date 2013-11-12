// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
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

import java.util.List;

import org.junit.Test;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.cpp.model.HeaderFile;

/**
 * @author z002ttbb
 *
 */
public class EclipseASTVisitor2BaseClassTest {
	

	/**
     * 
     */
    private static final String COMPLEX_TYPE_WITH_BASECLASS = "ComplexClassWithBaseClasses.h";
	/**
     * 
     */
    private static final String CLASSNAME = "Test::Application::System2::Facade";

	@Test
	public void returnParamWithBasicTypeInt(){
		String path = COMPLEX_TYPE_WITH_BASECLASS;
		HeaderFile f = HeaderUtil.getHeaderFile(path);
		assertNotNull("No header file found",f);
		ClassModel model = f.getClasses().get(0);
		List<String> bases = model.getBaseClasses();
		assertEquals(bases.size(),2);
		for(String b : bases){
			if(!b.equals("Test::Application::System::IService") ){
				assertEquals("Test::Application::System::IStorageRackCommandService", b);
			}
			else if(!b.equals("Test::Application::System::IStorageRackCommandService") ){
				assertEquals("Test::Application::System::IService", b);
			}
		}

	}


}
