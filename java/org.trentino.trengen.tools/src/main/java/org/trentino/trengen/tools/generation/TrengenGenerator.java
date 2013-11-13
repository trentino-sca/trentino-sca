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

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.Map;

import javax.annotation.processing.FilerException;

import org.apache.log4j.Logger;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.tools.templates.TemplateLoaderClass;

import freemarker.template.Configuration;
import freemarker.template.DefaultObjectWrapper;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public abstract class TrengenGenerator {
	protected static final Logger	logger	= Logger.getLogger(TrengenGenerator.class);

	protected static Configuration	cfg;
	protected Context	          context;

	public TrengenGenerator (Context context) {
		this.context = context;
	}

	public abstract boolean generate() throws TrengenException;

	protected static Configuration configure() {
		cfg = new Configuration();
		cfg.setClassForTemplateLoading(TemplateLoaderClass.class, "");
		cfg.setObjectWrapper(new DefaultObjectWrapper());
		return cfg;
	}

	protected static void doWrite(Map<String, Object> root, Context context, Template tp, OutputStream os) {
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

}
