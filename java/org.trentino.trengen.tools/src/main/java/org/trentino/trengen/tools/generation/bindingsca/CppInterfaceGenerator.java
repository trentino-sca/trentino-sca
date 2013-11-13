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
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.log4j.Logger;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.tools.bindingsca.TIDL2CppInterface;
import org.trentino.trengen.tools.bindingsca.TIDLParseException;
import org.trentino.trengen.tools.bindingsca.TIDLType;
import org.trentino.trengen.tools.generation.TrengenGenerator;
import org.trentino.trengen.tools.scavalidation.CommandLineOptions;
import org.trentino.trengen.tools.scavalidation.DirectoryScanner;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.tools.trengen.TrengenCommand;
import org.trentino.trengen.tools.trengen.Util;

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
	/**
	 * This function generates cpp interface file for sca binding
	 * @throws TIDLParseException
	 */
	public static  void generateCPPInterface(String tidlFilePath, String include, String outDir) throws TIDLParseException {
		logger.info("CPPInterface file is being generated... " + tidlFilePath + " directory is used during generation.");
		File tdilFile = new File(tidlFilePath);
		if(!(tdilFile.exists()))
		{
			logger.error(tidlFilePath + " does not exist! Please give correct path...");
			return;
		}
		List<File> tidlPropertyFiles = new ArrayList<File>();
		List<File> javaFiles = new ArrayList<File>();
		if(tdilFile.isFile() && tidlFilePath.endsWith(".tidl.properties"))
		{
			tidlPropertyFiles.add(tdilFile);
		}
		else if(tdilFile.isFile() && tidlFilePath.endsWith(".java"))
		{
			javaFiles.add(tdilFile);
		}
		else
		{
			List<File> sp = new ArrayList<File>();
			sp.add(tdilFile);
			tidlPropertyFiles = DirectoryScanner.SearchArtifacts(sp, "tidl.properties");
		}

		if(tidlPropertyFiles.isEmpty() && javaFiles.isEmpty())
		{
			logger.error("No .tidl.properties file is found in " + tidlFilePath);
			return;
		}
		for (File tidlFile : tidlPropertyFiles)
		{
			String pathToJavaFile = Util.readTidlPropertiesFile(tidlFile);
			String pathToTidl = Util.getTidlFilePath(tidlFile, pathToJavaFile);

			// an outdir is expected in TidlToCPPInterface converter. if it is
			// null, use the current path.
			if(outDir == null)
			{
				outDir = pathToTidl;
			}

			if(pathToTidl != null && pathToJavaFile != null)
			{
				pathToJavaFile = new File(pathToTidl, pathToJavaFile).getAbsolutePath();
			}
			else
			{
				logger.error("Path to Java file is null");
				return;
			}
			logger.info("Path to java file " + pathToJavaFile);

			File javaFile = new File(pathToJavaFile);
			if(!javaFile.exists())
			{
				logger.error(pathToJavaFile + " does not exist! Please give correct path...");
				return;
			}

			generateCPPInterfaceFromJavaFile(include, javaFile, tidlFile, outDir);

		}

		for (File javaFile : javaFiles)
		{
			generateCPPInterfaceFromJavaFile(include, javaFile, null, outDir);
		}
	}

	private static  void generateCPPInterfaceFromJavaFile(String include, File javaFile, File tidl, String outDir) throws TIDLParseException {
		// CPP interface generation
		TIDL2CppInterface converter = new TIDL2CppInterface();

		File outDirFile = null;
		if(outDir == null)
		{
			outDir = javaFile.getParent();
		}
		outDirFile = new File(outDir);
		List<String> includes = new ArrayList<String>();

		if(include != null && !"".equals(include))
		{
			includes.add(include);
		}

		if(javaFile != null && outDirFile != null)
		{
			converter.createCppInterface(javaFile, tidl, outDirFile, includes);
		}
	}


}
