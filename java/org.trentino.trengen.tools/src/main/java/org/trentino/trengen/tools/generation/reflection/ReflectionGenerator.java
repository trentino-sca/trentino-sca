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
package org.trentino.trengen.tools.generation.reflection;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.trentino.trengen.TrengenException;
import org.trentino.trengen.tools.generation.TrengenGenerator;

import freemarker.template.Configuration;
import freemarker.template.Template;

/**
 * This is the generator class of reflection code
 */
public class ReflectionGenerator extends TrengenGenerator {

	public ReflectionGenerator (ContextReflection context) {
		super(context);
	}

	@Override
	public boolean generate() throws TrengenException {
		Configuration config = configure();
		Template cppReflx = null;

		try
		{
			cppReflx = config.getTemplate("ReflectionGenerator_cpp.ftl");
		} catch (IOException e)
		{
			throw new IllegalStateException("cannot create template");
		}

		File outputDir = context.getOutputDir();
		if(!outputDir.exists())
		{
			outputDir.mkdirs();
		}
		String fileName = "TrentinoGenReflx";

		FileOutputStream fos;
		try
		{
			fos = new FileOutputStream(new File(outputDir, fileName + ".cpp"));
		} catch (FileNotFoundException e)
		{
			throw new TrengenException(e);
		}

		Map<String, java.lang.Object> root = new HashMap<String, java.lang.Object>();
		root.put("reflectionObjectList", ((ContextReflection) context).getReflectionObjects());
		root.put("mapper", new CppTypeMapperForPropertyTypes());
		root.put("includesList", ((ContextReflection) context).getReflexIncludes());
		doWrite(root, context, cppReflx, fos);

		return true;
	}

}
