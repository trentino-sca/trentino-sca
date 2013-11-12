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
package org.trentino.trengen.tools.generation.reflection;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import org.trentino.trengen.tools.generation.Context;
import org.trentino.trengen.tools.generation.modelloader.SCAModelToSCAMirrorModelConverter;
import org.trentino.trengen.tools.scavalidation.DirectoryScanner;
import org.trentino.trengen.tools.trengen.Trengen;

/**
 * contains input data needed by the generator
 */
public class ContextReflection extends Context {
	SCAModelToSCAMirrorModelConverter	converter;

	public ContextReflection (SCAModelToSCAMirrorModelConverter c) {
		converter = c;
	}

	public List<ReflectionObject> getReflectionObjects() {
		return converter.getReflectionObjects();
	}

	private File	     outputDir;
	private List<String>	reflexIncludes;

	@Override
	public File getOutputDir() {
		return outputDir;
	}
	
	@Override
	public void setOutputDir(File outputDir) {
		this.outputDir = outputDir;
	}

	public List<String> getReflexIncludes() {
		if(reflexIncludes == null)
		{
			reflexIncludes = new ArrayList<String>();
			for (ReflectionObject obj : converter.getReflectionObjects())
			{
				String toBeIncluded =  obj.getImplHeader().toString();//DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), obj.getImplHeader().toString());
				if(toBeIncluded == null)
				{
					continue;
				}
				// toBeIncluded =
				// toBeIncluded.replace(Trengen.getScaValidationFolder().getAbsolutePath(),
				// "");
				toBeIncluded = toBeIncluded.replace("\\", "/");
				// toBeIncluded = "../" + Trengen.getApplicationNameLowerCase()
				// + toBeIncluded;
				reflexIncludes.add(toBeIncluded);
			}
		}

		return reflexIncludes;
	}

}
