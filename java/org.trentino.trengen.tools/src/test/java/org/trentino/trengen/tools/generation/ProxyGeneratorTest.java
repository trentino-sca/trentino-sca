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

package org.trentino.trengen.tools.generation;

import java.io.File;

import org.trentino.trengen.TrengenException;
import org.trentino.trengen.cpp.model.ClassMember;
import org.trentino.trengen.cpp.model.ClassMethod;
import org.trentino.trengen.cpp.model.ClassMethodArgument;
import org.trentino.trengen.cpp.model.ImplementationHeaderClass;
import org.trentino.trengen.tools.generation.modelloader.SCAModelToSCAMirrorModelConverter;
import org.trentino.trengen.tools.generation.proxieswrappers.ContextProxiesWrappers;
import org.trentino.trengen.tools.generation.proxieswrappers.ProxyGenerator;
import org.trentino.trengen.tools.scavalidation.ConformanceManagerCppImplArtifactsEclipseCDT;
import org.trentino.trengen.tools.trengen.TrentinoTest;

public class ProxyGeneratorTest extends TrentinoTest {
	private static ConformanceManagerCppImplArtifactsEclipseCDT	conformanceManagerCppImplArtifacts	= new ConformanceManagerCppImplArtifactsEclipseCDT();

	// @Test
	public void test() {
		SCAModelToSCAMirrorModelConverter converter = new SCAModelToSCAMirrorModelConverter(new CPPModelProvider(conformanceManagerCppImplArtifacts));
		ContextProxiesWrappers context = new ContextProxiesWrappers(converter, "BasicCalculator");
		context.setOutputDir(new File(".", "proxygen"));
		ImplementationHeaderClass ihClass = new ImplementationHeaderClass();
		ihClass.setClassName("Calculator");
		ihClass.setNamespace("org.examples.trentino");
		ihClass.setComponentType(true);
		ClassMember member = new ClassMember();
		ihClass.getMembers().add(member);

		ClassMethod method = new ClassMethod("foo", "int");
		ihClass.getMethods().add(method);
		ClassMethod method2 = new ClassMethod("bar", "std::string");
		ihClass.getMethods().add(method2);
		for (int i = 0; i < 3; i++)
		{
			ClassMethodArgument argi = new ClassMethodArgument("arg" + i, "float");
			method2.getArguments().add(argi);
		}

		ProxyGenerator gen = new ProxyGenerator(context);
		try
		{
			gen.generate();
		} catch (TrengenException e)
		{
			e.printStackTrace();
		}
	}

}
