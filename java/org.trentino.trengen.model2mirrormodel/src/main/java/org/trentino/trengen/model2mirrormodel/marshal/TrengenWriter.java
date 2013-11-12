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
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.Map;

import javax.annotation.processing.FilerException;

import org.apache.log4j.Logger;
import org.trentino.trengen.model2mirrormodel.Context;
import org.trentino.trengen.model2mirrormodel.template.TemplateLoaderClass;

import freemarker.template.Configuration;
import freemarker.template.DefaultObjectWrapper;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public abstract class TrengenWriter {

	protected static final Logger	logger	= Logger.getLogger(TrengenWriter.class);
	private static Configuration	cfg	   = null;
	protected Context	          context;

	public TrengenWriter (Context context) {
		this.context = context;
	}

	public abstract void generate();

	protected static Configuration configure() {
		if(cfg == null)
		{
			cfg = new Configuration();
			cfg.setClassForTemplateLoading(TemplateLoaderClass.class, "");
			cfg.setObjectWrapper(new DefaultObjectWrapper());

		}
		return cfg;
	}

	protected static void doWrite(Map<String, Object> root, Template tp, OutputStream os) {
		try
		{

			PrintWriter pw = new PrintWriter(os);
			tp.process(root, pw);
			pw.flush();
		}

		catch (FilerException filerEx)
		{
			logger.error("Problem with Processing Environment Filer: " + filerEx.getMessage());
			throw new IllegalStateException(filerEx);
		}

		catch (IOException ioEx)
		{
			throw new IllegalStateException(ioEx);

		} catch (TemplateException e)
		{
			e.printStackTrace();
			throw new IllegalStateException(e);
		} finally
		{
			if(os != null)
			{
				try
				{
					os.close();
				} catch (IOException e)
				{
					e.printStackTrace();
				}
			}
		}

	}

	/**
	 * @param outputDir
	 * @param root
	 * @param tp
	 * @param fileName
	 * @return
	 */
	public void writeSingleFile(File outputDir, Map<String, Object> root, Template tp, String fileName) {
		FileOutputStream fos;

		try
		{
			File file = new File(outputDir, fileName);
			fos = new FileOutputStream(file);
			// logger.debug("Writing to file" + file.getAbsolutePath());

		} catch (FileNotFoundException e)
		{
			throw new IllegalStateException("Cannot load file", e);
		}
		doWrite(root, tp, fos);
	}

}
