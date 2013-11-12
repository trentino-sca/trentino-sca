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
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import org.trentino.trengen.tools.bindingsca.TIDLInterfaceModel;
import org.trentino.trengen.tools.generation.Context;

/**
 * @author z002ttbb
 */
public class ContextSCABinding extends Context {

	private Set<ContextCppInterface>	listContextProtoBuf	= new TreeSet<ContextCppInterface>();
	private String	                  contributionName;
	private Set<String>	              itfUsing	            = null;

	public ContextSCABinding (String contributionName) {
		this.contributionName = contributionName;
	}

	public String getContributionName() {
		return contributionName;
	}

	public void addContextProtoBuf(ContextCppInterface ctxProtoBuf) {
		if(!listContextProtoBuf.contains(ctxProtoBuf)){
			listContextProtoBuf.add(ctxProtoBuf);	
		}
	}

	public Set<ContextCppInterface> getProtoBufContexts() {
		return listContextProtoBuf;
	}

	private File	outputDir;

	@Override
	public File getOutputDir() {
		return outputDir;
	}

	@Override
	public void setOutputDir(File outputDir) {
		this.outputDir = outputDir;
	}

	public Set<String> getItfUsing() {
		if(itfUsing == null)
		{
			itfUsing = new HashSet<String>();
			for(ContextCppInterface itf : listContextProtoBuf){
				TIDLInterfaceModel model=itf.getTidlInterfaceModel();
				itfUsing.add(model.getNamespace().replace(".", "::"));
			}
		}
		return itfUsing;
	}

}
