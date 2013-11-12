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

package org.trentino.trengen.model2mirrormodel.marshal;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.apache.log4j.Logger;
import org.trentino.trengen.model2mirrormodel.ClassInfo;
import org.trentino.trengen.model2mirrormodel.Context;

import freemarker.template.Configuration;
import freemarker.template.Template;

/**
 * @author z002ttbb, Muge, IPEK
 *         Writer class for the SCa Model Mirror
 */
public class SCAModelMirrorWriter extends TrengenWriter {

	public SCAModelMirrorWriter (Context context) {
		super(context);
	}

	protected static final Logger	logger	= Logger.getLogger(SCAModelMirrorWriter.class);

	@Override
	public void generate() {
		logger.debug("\n\n\n GENERATION OF SCA MODEL MIRROR START \n\n\n");
		Configuration config = configure();
		Template javaClass = null;
		Template javaEnum = null;
		try
		{
			javaClass = config.getTemplate("SCAModelMirror.java.ftl");
			javaEnum = config.getTemplate("SCAModelMirror.enum.ftl");
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

		String packageName = "org.trentino.trengen.scamodelmirror";
		String outputPath = packageName.replace('.', File.separatorChar);
		outputDir = new File(outputDir, outputPath);
		if(!outputDir.exists())
		{
			outputDir.mkdirs();
		}

		Map<String, Object> root = new HashMap<String, Object>();
		root.put("context", context);
		root.put("packageName", packageName);
		for (ClassInfo info : context.getClasses())
		{
			if("Enum".equals(info.getName()))
			{
				logger.error("\n\n\n ENUM Found. This should not happens, "
				        + "it is a hint for an internal bUg in the Processor. Please make sure that the code processor works well \n\n\n");
				continue;
			}

			Template temp = info.isEnum() ? javaEnum : javaClass;
			String fileName = getFileName(info);
			root.put("classInfo", info);
			writeSingleFile(outputDir, root, temp, fileName + ".java");
		}
		// copy required files
		copyrequiredFiles(outputDir);
	}

	private void copyrequiredFiles(File outputDir) {

	}

	private String getFileName(ClassInfo info) {
		return info.getName();
	}

}
