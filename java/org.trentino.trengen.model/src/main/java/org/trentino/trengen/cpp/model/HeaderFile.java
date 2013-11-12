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

package org.trentino.trengen.cpp.model;

import java.util.ArrayList;
import java.util.List;

// import com.sun.xml.internal.ws.wsdl.writer.UsingAddressing;

/**
 * @author z002ttbb
 */
public class HeaderFile {
	/**
	 * name of the header file
	 */
	private String	          name;

	private List<IncludeFile>	includedFile	= new ArrayList<IncludeFile>();

	private List<ClassModel>	classes	      = new ArrayList<ClassModel>();

	private List<String>	  usingDirectives	= new ArrayList<String>();

	public List<String> getUsingDirectives() {
		return usingDirectives;
	}

	public void setUsingDirectives(List<String> usingDirectives) {
		this.usingDirectives = usingDirectives;
	}

	public List<ClassModel> getClasses() {
		return classes;
	}

	public void setClasses(List<ClassModel> classes) {
		this.classes = classes;
	}

	public List<IncludeFile> getIncludedFile() {
		return includedFile;
	}

	public void setIncludedFile(List<IncludeFile> includedFile) {
		this.includedFile = includedFile;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
	

	@Override
	public String toString() {
		return name;
	}

}
