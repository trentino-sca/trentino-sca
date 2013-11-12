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

import static org.junit.Assert.*;

import org.junit.Test;
import org.trentino.trengen.cpp.model.ClassMethod;
import org.trentino.trengen.cpp.model.HeaderFile;

/**
 * @author z002ttbb
 *
 */
public class EclipseASTVisitor2ReturnTypeTest {
	
	/**
     * 
     */
    private static final String FACTORY = "Trentino::Test::ComplexTypes::ServiceFactory";
	/**
     * 
     */
    private static final String COMPLEX_TYPE = "returnParamWithComplexType.h";
	/**
     * 
     */
    private static final String BASIC_TYPE_H = "returnParamWithBasicType.h";
	/**
     * 
     */
    private static final String DIVIDER = "Trentino::Example::BasicCalculator::Divider";

	@Test
	public void returnParamWithBasicTypeInt(){
		String path = BASIC_TYPE_H;
		String qName = DIVIDER;
		String methodName = "divideReturnInt";
		String expected = "int";
		doTest(path, qName, methodName, expected);
	}

	private void doTest(String path, String qName, String methodName, String expected) {
	    HeaderFile f = HeaderUtil.getHeaderFile(path);
		assertNotNull("No header file found",f);
		ClassMethod method = HeaderUtil.getMethod(f, qName, methodName);
		assertNotNull("No method with name found: "+methodName,method);
		assertEquals(expected, method.getReturnType());
    }
	
	@Test
	public void returnParamWithBasicTypeIntNotVirtual(){
		doTest(BASIC_TYPE_H, DIVIDER,  "divideReturnIntNotVirtual", "int");
	}
	
	@Test
	public void returnParamWithBasicTypeIntRef(){
		doTest(BASIC_TYPE_H, DIVIDER,  "divideReturnIntRef", "int&");
	}
	
	@Test
	public void returnParamWithBasicTypeIntConstRef(){
		doTest(BASIC_TYPE_H, DIVIDER,  "divideReturnConstIntRef", "const int&");
	}
	
	@Test
	public void returnParamWithBasicTypeIntConst(){
		doTest(BASIC_TYPE_H, DIVIDER,  "divideReturnConstInt", "const int");
	}
	
	@Test
	public void returnParamWithComplexTypeByValueUndefinedType(){
		doTest(COMPLEX_TYPE, FACTORY,  "getServiceReferenceUndefinedType", "Servicereference");
	}
	
	@Test
	public void returnParamWithComplexTypeByValueUndefinedType2(){
		doTest(COMPLEX_TYPE, FACTORY,  "getServiceReferenceUndefinedType2", "Test::Servicereference");
	}
	
	
	@Test
	public void returnParamWithComplexTypeByValueUndefinedTypeCont(){
		doTest(COMPLEX_TYPE, FACTORY,  "getServiceReferenceUndefinedTypeConst", "const Servicereference");
	}
	
	@Test
	public void returnParamWithComplexTypeByValueUndefinedTypeCont2(){
		doTest(COMPLEX_TYPE, FACTORY,  "getServiceReferenceUndefinedTypeConst2", "const Test::Servicereference");
	}
	
	@Test
	public void returnParamWithComplexTypeByValueUndefinedTypeConstRef(){
		doTest(COMPLEX_TYPE, FACTORY,  "getServiceReferenceUndefinedTypeConstRef", "const Servicereference&");
	}
	
	@Test
	public void returnParamWithComplexTypeByValueUndefinedTypeConstRef2(){
		doTest(COMPLEX_TYPE, FACTORY,  "getServiceReferenceUndefinedTypeConstRef2", "const Test::Servicereference&");
	}
	
	@Test
	public void returnParamWithComplexTypeByValueUndefinedTypeConstRef2NotVirtual(){
		doTest(COMPLEX_TYPE, FACTORY,  "getServiceReferenceUndefinedTypeRef2NotVirtual", "Test::Servicereference&");
	}
	
	@Test
	public void returnParamWithComplexTypegetServiceReferenceSharedPtr(){
		doTest(COMPLEX_TYPE, FACTORY,  "getServiceReferenceSharedPtr", "boost::shared_ptr<Test::Servicereference>");
	}
	
	@Test
	public void returnParamWithComplexTypegetServiceReferenceSharedPtrConst(){
		doTest(COMPLEX_TYPE, FACTORY,  "getServiceReferenceSharedPtrConst", "const boost::shared_ptr<Test::Servicereference>");
	}
	
	@Test
	public void returnParamWithComplexTypegetServiceReferenceSharedPtrRef(){
		doTest(COMPLEX_TYPE, FACTORY,  "getServiceReferenceSharedPtrRef", "boost::shared_ptr<Test::Servicereference>&");
	}
	
	@Test
	public void returnParamWithComplexTypegetServiceReferenceTemplate(){
		doTest(COMPLEX_TYPE, FACTORY,  "GetMax", "myType");
	}
	
	@Test
	public void returnParamWithComplexTypegetServiceReferenceTemplateRef(){
		doTest(COMPLEX_TYPE, FACTORY,  "GetMaxRef", "myType&");
	}
	
	@Test
	public void returnParamWithComplexTypegetServiceReferenceTemplateConstRef(){
		doTest(COMPLEX_TYPE, FACTORY,  "GetMaxConstRef", "const myType&");
	}
	
	@Test
	public void returnParamWithComplexTypegetServiceReferenceTemplateConstRefSharedPtr(){
		doTest(COMPLEX_TYPE, FACTORY,  "GetMaxConstRefSharedPtr", "const std::vector<myType>&");
	}
	
	

}
