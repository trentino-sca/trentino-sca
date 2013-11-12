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

import org.trentino.trengen.TrengenException;
import org.trentino.trengen.tools.generation.TrengenGenerator;

import freemarker.template.Configuration;
import freemarker.template.Template;

/**
 * ModelLoaderGenerator is used to generate the model loader c++ class according
 * to the arguments of the generate function.
 */
public class ProtobufGenerator extends TrengenGenerator {

	public ProtobufGenerator (ContextCppInterface contextProtoBuf) {
		super(contextProtoBuf);
	}

	/**
	 * This function passes the base doWrite function the template generating
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
		Template reqTp = null;
		Template respTp = null;
		Template typeTp = null;
		// Template proxyTp=null;
		Template beanUtilsTp = null;
		Template beanUtilsTpImpl = null;
		Template ccFiledAllInOneTp = null;
		Template ccFiledAllInOnehpp = null;
		try
		{
			reqTp = config.getTemplate("BindingSCARequest.ftl");
			respTp = config.getTemplate("BindingSCAResponse.ftl");
			typeTp = config.getTemplate("BindingSCATypes.ftl");
			// proxyTp = config.getTemplate("BindingSCAProxy.ftl");
			beanUtilsTp = config.getTemplate("BindingSCABeanUtils.ftl");
			beanUtilsTpImpl = config.getTemplate("BindingSCABeanUtilsImpl.ftl");
			ccFiledAllInOneTp = config.getTemplate("BindingSCAProtoAllInOne.ftl");
			ccFiledAllInOnehpp = config.getTemplate("BindingSCAProtoAllInOne_hpp.ftl");
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

		Map<String, java.lang.Object> root = new HashMap<String, java.lang.Object>();
		root.put("context", context);
		root.put("tmapper", new ProtobufTypeMapper(context.getTidlInterfaceModel()));
		String className = context.getTidlInterfaceModel().getQualifiedName().replace(".", "");
		String typesFilename = className+ "Types.proto";
		root.put("typesFilename", typesFilename);

		String fileName = className + "Request.proto";
		FileOutputStream fos;
		try
		{
			fos = new FileOutputStream(new File(outputDir, fileName));
		} catch (FileNotFoundException e)
		{
			throw new TrengenException(e);
		}

		doWrite(root, context, reqTp, fos);

		fileName = className + "Response.proto";
		try
		{
			fos = new FileOutputStream(new File(outputDir, fileName));
		} catch (FileNotFoundException e)
		{
			throw new TrengenException(e);
		}
		doWrite(root, context, respTp, fos);
		fileName = typesFilename;
		try
		{
			fos = new FileOutputStream(new File(outputDir, fileName));
		} catch (FileNotFoundException e)
		{
			throw new TrengenException(e);
		}
		doWrite(root, context, typeTp, fos);
		root.put("tmapper", new CppTypeMapper());
		root.put("pbtmapper", new ProtobufTypeMapper(context.getTidlInterfaceModel()));

		/*
		 * fileName =context.getFileName()+"Mapper.h";
		 * try { fos = new FileOutputStream(new File(outputDir, fileName)); }
		 * catch (FileNotFoundException e) { throw new TrengenException(e); }
		 * doWrite(root, context, proxyTp, fos);
		 */

		// BUG 539: if there are not any declared types, do not create a
		// beanutils.cpp
		if(context.hasBeanUtils())
		{
			fileName = className + "BeanUtils.h";
			try
			{
				fos = new FileOutputStream(new File(outputDir, fileName));
			} catch (FileNotFoundException e)
			{
				throw new TrengenException(e);
			}
			doWrite(root, context, beanUtilsTp, fos);

			fileName = className + "BeanUtils.cpp";
			try
			{
				fos = new FileOutputStream(new File(outputDir, fileName));
			} catch (FileNotFoundException e)
			{
				throw new TrengenException(e);
			}
			doWrite(root, context, beanUtilsTpImpl, fos);
		}

		fileName = className + "ProbobufMessages.cpp";
		try
		{
			fos = new FileOutputStream(new File(outputDir, fileName));
		} catch (FileNotFoundException e)
		{
			throw new TrengenException(e);
		}
		doWrite(root, context, ccFiledAllInOneTp, fos);

		fileName = className + "ProbobufMessages.h";
		try
		{
			fos = new FileOutputStream(new File(outputDir, fileName));
		} catch (FileNotFoundException e)
		{
			throw new TrengenException(e);
		}
		doWrite(root, context, ccFiledAllInOnehpp, fos);
		return true;
	}

}
