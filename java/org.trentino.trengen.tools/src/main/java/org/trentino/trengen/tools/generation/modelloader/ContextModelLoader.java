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
package org.trentino.trengen.tools.generation.modelloader;

import java.io.File;
import java.util.List;

import org.trentino.trengen.scamodelmirror.ComponentType;
import org.trentino.trengen.scamodelmirror.ContributionType;
import org.trentino.trengen.tools.generation.Context;

/**
 * contains input data needed by the generator.
 * @deprecated @use ContextProxiesWrappers instead
 */
@Deprecated()
public class ContextModelLoader extends Context {
	SCAModelToSCAMirrorModelConverter	converter;

	public ContextModelLoader (SCAModelToSCAMirrorModelConverter c) {
		converter = c;
	}

	public List<CompositeMirrorWrapper> getCompositeMirrorWrapperList() {
		return converter.getCompositeMirrorWrapperList();
	}

	public ContributionType getContribution() {
		return converter.getContributionType();
	}

	public List<ComponentType> getListComponentType() {
		return converter.getMirrorComponentTypeList();
	}

	public List<ComponentComponentTypeAssociation> getComponentcomponentTypeAssocList() {
		return converter.getAssociations();
	}

	public String getApplicationName() {
		return converter.getApplicationName();
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
}
