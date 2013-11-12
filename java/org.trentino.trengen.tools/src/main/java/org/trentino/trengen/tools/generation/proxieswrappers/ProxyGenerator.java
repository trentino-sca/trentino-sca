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
package org.trentino.trengen.tools.generation.proxieswrappers;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.trentino.trengen.TrengenException;
import org.trentino.trengen.tools.generation.Context;
import org.trentino.trengen.tools.generation.TrengenGenerator;
import org.trentino.trengen.tools.generation.reflection.ContextReflection;
import org.trentino.trengen.tools.generation.reflection.CppTypeMapperForPropertyTypes;

import freemarker.template.Configuration;
import freemarker.template.Template;

/**
 * @author z002ttbb This generator create a cpp proxy class based on a model
 */
public class ProxyGenerator extends TrengenGenerator {

	public ProxyGenerator (Context context) {
		super(context);
	}

	@Override
	public boolean generate() throws TrengenException {
		Configuration config = configure();
		Template cppProxiesWrappers = null;
		Template hProxiesWrappers = null;
		Template hContributionInfo = null;
		Template cppContributionInfo = null;

		// String prefix = getPrefix();
		try
		{
			cppProxiesWrappers = config.getTemplate("ProxyGenerator_cpp.ftl");
			hProxiesWrappers = config.getTemplate("ProxyGenerator_h.ftl");
			// Contribution Info is the single entry point for the contribution
			// to query information
			hContributionInfo = config.getTemplate("ContributionInfo_h.ftl");
			cppContributionInfo = config.getTemplate("ContributionInfo_cpp.ftl");

		} catch (IOException e)
		{
			throw new IllegalStateException("cannot create template");
		}

		File outputDir = context.getOutputDir();
		if(!outputDir.exists())
		{
			outputDir.mkdirs();
		}

		String rootPrefix = ((ContextProxiesWrappers) context).getRootPrefix();
		FileOutputStream fosCpp;
		FileOutputStream fosH;

		FileOutputStream fosContInfoH;
		FileOutputStream fosContInfoCPP;

		String contributionName = ((ContextProxiesWrappers) context).getContributionName();
		try
		{
			fosCpp = new FileOutputStream(new File(outputDir, "TrentinoGenProxiesWrappers.cpp"));
			fosH = new FileOutputStream(new File(outputDir, "TrentinoGenProxiesWrappers.h"));

			fosContInfoH = new FileOutputStream(new File(outputDir, "TrentinoGenContributionInfo.h"));
			fosContInfoCPP = new FileOutputStream(new File(outputDir, "TrentinoGenContributionInfo.cpp"));

		} catch (FileNotFoundException e)
		{
			throw new TrengenException(e);
		}

		Map<String, java.lang.Object> root = new HashMap<String, java.lang.Object>();
		root.put("serviceInterfacesList", ((ContextProxiesWrappers) context).getServiceInterfaces());
		root.put("referenceInterfacesList", ((ContextProxiesWrappers) context).getReferenceInterfaces());
		root.put("includesList", ((ContextProxiesWrappers) context).getIncludes());
		root.put("usingList", ((ContextProxiesWrappers) context).getUsingList());
		root.put("headerFileName", "TrentinoGenProxiesWrappers");
		root.put("context", context);
		root.put("rootPrefix", rootPrefix);
		
		//Includes for reflection
		root.put("reflectionObjectList", ((ContextProxiesWrappers) context).getContextReflection().getReflectionObjects());
		root.put("mapper", new CppTypeMapperForPropertyTypes());
		root.put("includesList", ((ContextProxiesWrappers) context).getContextReflection().getReflexIncludes());
		
		// used by contributioninfo
		root.put("contributionName", contributionName);
		doWrite(root, context, cppProxiesWrappers, fosCpp);
		doWrite(root, context, hProxiesWrappers, fosH);
		doWrite(root, context, hContributionInfo, fosContInfoH);
		doWrite(root, context, cppContributionInfo, fosContInfoCPP);

		return true;
	}

	public boolean isNullOrEmpty(List<ReferenceServiceInterface> list) {
		return list == null || list.isEmpty();
	}

}
