/************************************************************************************
 * // Trentino - A C++ based lightweight, non-invasive SCA runtime.
 * // Copyright (C) Siemens AG, 2012
 * // All Rights Reserved
 * // http://trentino.sourceforge.net/
 * //
 * // This library is free software; you can redistribute it and/or
 * // modify it under the terms of the GNU Lesser General Public
 * // License as published by the Free Software Foundation; either
 * // version 2.1 of the License, or (at your option) any later version.
 * //
 * // This library is distributed in the hope that it will be useful,
 * // but WITHOUT ANY WARRANTY; without even the implied warranty of
 * // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * // Lesser General Public License for more details.
 * //
 * // You should have received a copy of the GNU Lesser General Public
 * // License along with this library; if not, write to the Free Software
 * // Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * //
 *********************************************************************************/

package org.trentino.trengen.model2mirrormodel.marshal;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.apache.log4j.Logger;
import org.trentino.trengen.model2mirrormodel.ClassInfo;
import org.trentino.trengen.model2mirrormodel.Context;

import freemarker.template.Configuration;
import freemarker.template.Template;

public class SCAModelWriter extends TrengenWriter {

	protected static final Logger	logger	= Logger.getLogger(SCAModelWriter.class);

	public SCAModelWriter (Context context) {
		super(context);

	}

	@Override
	public void generate() {
		logger.debug("\n\n\n GENERATION OF SCA MODEL START \n\n\n");
		Configuration config = configure();
		Template header = null;
		Template enumheader = null;
		Template inl = null;
		Template enumInl = null;
		Template mainheader = null;
		Template cmakeListtxt;
		Template cppTemplate;
		// Template enumcppTemplate;
		Template modelFactoryCpp;
		Template modelFactoryH;
		try
		{
			header = config.getTemplate("SCAModel.hpp.ftl");
			enumheader = config.getTemplate("Enum.hpp.ftl");
			inl = config.getTemplate("SCAModel.inl.ftl");
			enumInl = config.getTemplate("Enuml.inl.ftl");
			mainheader = config.getTemplate("TrentinoSCAModel.hpp.ftl");
			cmakeListtxt = config.getTemplate("CMakeLists.txt.ftl");
			cppTemplate = config.getTemplate("SCAModel.cpp.ftl");
			// enumcppTemplate = config.getTemplate("Enum.cpp.ftl");

			modelFactoryCpp = config.getTemplate("TrentinoSCAModelFactory.cpp.ftl");
			modelFactoryH = config.getTemplate("TrentinoSCAModelFactory.h.ftl");
		} catch (IOException e)
		{
			logger.error(e);
			throw new IllegalStateException("cannot create template", e);
		}

		File outputDir = context.getOutputDir();
		if(outputDir == null)
		{
			outputDir = new File(".\\target\\generated-sources");
		}
		outputDir = new File(outputDir, "Trentino\\SCA\\Model");
		if(!outputDir.exists())
		{
			outputDir.mkdirs();
		}
		Map<String, Object> root = new HashMap<String, Object>();
		root.put("context", context);
		writeFileFromClasses(root, mainheader, outputDir, "TrentinoSCAModel.h");
		writeFileFromClasses(root, cmakeListtxt, outputDir, "CMakeLists.txt");
		writeFileFromClasses(root, modelFactoryCpp, outputDir, "TrentinoSCAModelFactory.cpp");
		writeFileFromClasses(root, modelFactoryH, outputDir, "TrentinoSCAModelFactory.h");
		writeFileFromClasses(root, cppTemplate, outputDir, "TrentinoSCAModel.cpp");
		for (ClassInfo info : context.getClasses())
		{
			if("Enum".equals(info.getName()))
			{
				logger.error("\n\n\n ENUM Found. This should not happens, "
				        + "it is a hint for an internal bUg in the Processor. Please make sure that the code processor works well \n\n\n");
				continue;
			}
			Template hTp = info.isEnum() ? enumheader : header;
			Template inlTtp = info.isEnum() ? enumInl : inl;
			// Template cppTp = info.isEnum() ? enumcppTemplate : cppTemplate;
			String fileName = getFileName(info);
			root.put("classInfo", info);
			writeSingleFile(outputDir, root, hTp, fileName + ".h");
			// writeSingleFile(outputDir, root, cppTp, fileName + ".cpp");
			if(info.hasAccessors())
			{
				writeSingleFile(outputDir, root, inlTtp, fileName + ".inl");
			}

		}

	}

	/**
	 * write the TrentinoSCAModel.h file.
	 * @param root
	 * @param mainheader
	 * @param outputDir
	 */
	private void writeFileFromClasses(Map<String, Object> root, Template mainheader, File outputDir, String fileName) {
		root.put("classes", context.getClasses());
		try
		{
			File file = new File(outputDir, fileName);
			FileOutputStream fos = new FileOutputStream(file);
			logger.debug("Writing to file" + file.getAbsolutePath());
			doWrite(root, mainheader, fos);

		} catch (FileNotFoundException e)
		{
			throw new IllegalStateException("Cannot load file", e);
		}
	}

	private String getFileName(ClassInfo info) {
		return "TrentinoSCAModel" + info.getName();
	}

}
