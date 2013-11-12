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
package org.trentino.trengen.tools.generation.bindingsca;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.apache.log4j.Logger;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.tools.bindingsca.TIDLType;
import org.trentino.trengen.tools.generation.TrengenGenerator;
import org.trentino.trengen.tools.scavalidation.CommandLineOptions;
import org.trentino.trengen.tools.trengen.Trengen;

import freemarker.template.Configuration;
import freemarker.template.Template;

/**
 * ModelLoaderGenerator is used to generate the model loader c++ class according
 * to the arguments of the generate function.
 */
public class CppInterfaceGenerator extends TrengenGenerator {
	protected static final Logger	logger	= Logger.getLogger(CppInterfaceGenerator.class);

	public CppInterfaceGenerator (ContextCppInterface context) {
		super(context);
	}

	/**
	 * This fucntion passes the base doWrite function the template generating
	 * the model loader c++ calls( "ModelLoader_cpp.ftl") output stream to write
	 * the generated c++ code context and the root map hosting the arguments of
	 * 'generate' function to be used by the template.
	 * Template traces the compositeWrapper list and contribution Type and
	 * componentType list and component and componentType association list
	 * separately(see the template for details)
	 */
	@Override
	public boolean generate() throws TrengenException {
		Configuration config = configure();
		Template cppTp = null;
		Template cppImplTp = null;

		try
		{
			cppTp = config.getTemplate("CppInterface.ftl");
			cppImplTp = config.getTemplate("CppInterface.cpp.ftl");
		} catch (IOException e)
		{
			throw new IllegalStateException("cannot create template");
		}

		ContextCppInterface context = (ContextCppInterface) this.context;
		File outputDir = context.getOutputDir();
		if(!outputDir.exists())
		{
			outputDir.mkdirs();
		}

		String prefix = context.getFileName();
		String fileName = prefix + ".h";
		FileOutputStream fos;
		try
		{
			fos = new FileOutputStream(new File(outputDir, fileName));
		} catch (FileNotFoundException e)
		{
			logger.error(new File(outputDir, fileName) + " could not be generated...", e);
			return false;
		}
		boolean inline = !Boolean.valueOf(String.valueOf(Trengen.getOption("-no_inline"))) ;
		if(inline && !context.canInlineCppImplementation()){
			throw new ValidationException("Cannot use inline when complex data structure are fields of other data structure");
		}
		Map<String, java.lang.Object> root = new HashMap<String, java.lang.Object>();
		root.put("context", context);
		root.put("tmapper", new CppTypeMapper());
		root.put("inline", inline);
		doWrite(root, context, cppTp, fos);
         

		// BUG #528: This if-case is added because a .cpp file should not be
		// generated if there are
		// not any declared structures
		boolean needsCppFile = false;
		for(TIDLType t  : context.getTidlInterfaceModel().getEnclosedClasses()){
			if(!t.isEnumeration()){
				needsCppFile = true;
				break;
			}
		}
		if(needsCppFile && !inline)
		{
			fileName =prefix + ".cpp";
			try
			{
				fos = new FileOutputStream(new File(outputDir, fileName));
			} catch (FileNotFoundException e)
			{
				logger.error(new File(outputDir, fileName) + " could not be generated...", e);
				return false;
			}
			doWrite(root, context, cppImplTp, fos);
		}
		return true;
	}

}
