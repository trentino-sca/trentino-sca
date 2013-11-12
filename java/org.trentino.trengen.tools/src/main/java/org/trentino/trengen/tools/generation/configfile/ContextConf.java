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
package org.trentino.trengen.tools.generation.configfile;

import java.io.File;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import javax.xml.bind.JAXBElement;
import javax.xml.namespace.QName;

import org.trentino.trengen.sca.model.CPPImplementation;
import org.trentino.trengen.sca.model.CPPImport;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ContributionType;
import org.trentino.trengen.sca.model.Implementation;
import org.trentino.trengen.sca.model.Import;
import org.trentino.trengen.tools.generation.Context;
import org.trentino.trengen.tools.scavalidation.ComponentWrapper;
import org.trentino.trengen.tools.scavalidation.ContributionVisitor;
import org.trentino.trengen.tools.trengen.Trengen;

/**
 * Contains input needed to generated sca model comfiguration file. It contains
 * a list of all the libraries referencec by a contribution
 */
public class ContextConf extends Context {

	private File	      outputDir;
	Set<String>	          paths	           = new HashSet<String>();
	protected Set<String>	dllDirectories	= null;
	ContributionVisitor	  visitor	       = new ContributionVisitor() {
		                                       public void visit(ContributionType contributionType) {
		                                    	   ContextConf.this.setContributionVersion(contributionType.getVersion());
			                                       List<JAXBElement<? extends Import>> imports = contributionType.getImportBase();
			                                       if(imports == null || imports.isEmpty())
			                                       {
				                                       return;
			                                       }
			                                       for (JAXBElement<? extends Import> imp : imports)
			                                       {
				                                       if(imp.isNil() || !(imp.getValue() instanceof CPPImport))
				                                       {
					                                       continue;
				                                       }
				                                       CPPImport impValue = (CPPImport) imp.getValue();
				                                       QName name = impValue.getName();
				                                       String localName = name != null ? name.getLocalPart() : "";
				                                       if("dll-directory".equalsIgnoreCase(localName))
				                                       {
					                                       String location = impValue.getLocation();
					                                       if(location != null)
					                                       {
						                                       ContextConf.this.dllDirectories.add(location);
					                                       }

				                                       }
			                                       }
		                                       }

		                                       public void visit(ComponentWrapper compWrapper) {
			                                       if(compWrapper == null)
			                                       {
				                                       return;
			                                       }
			                                       Component comp = compWrapper.getScaModelComponent();
			                                       if(comp == null)
			                                       {
				                                       return;
			                                       }
			                                       JAXBElement<? extends Implementation> impl = comp.getImplementation();
			                                       if(impl == null)
			                                       {
				                                       return;
			                                       }
			                                       Implementation implValue = impl.getValue();
			                                       if(implValue == null)
			                                       {
				                                       return;
			                                       }
			                                       if(!(implValue instanceof CPPImplementation))
			                                       {
				                                       return;
			                                       }
			                                       CPPImplementation cppImpl = (CPPImplementation) implValue;
			                                       String lib = cppImpl.getLibrary();
			                                       String path = cppImpl.getPath();
			                                       if(path == null)
			                                       {
				                                       path = ".";
			                                       }
			                                       if(!path.endsWith("/") && !path.endsWith("\\"))
			                                       {
				                                       lib = "/" + lib;
			                                       }
			                                       path += lib;
			                                       if(path != null && path.equals("./META-INF/sca-contribution"))
			                                       {
				                                       return;
			                                       }
			                                       ContextConf.this.paths.add(path.trim());
		                                       }
	                                       };
	private String contributionVersion;


	public File getOutputDir() {
		return outputDir;
	}

	public void setOutputDir(File aOutputDir) {
		outputDir = aOutputDir;
	}

	public Set<String> getPaths() {
		return paths;
	}

	public ContributionVisitor getVisitor() {
		if(dllDirectories == null)
		{
			dllDirectories = new HashSet<String>();
		}
		return visitor;
	}

	public Set<String> getDllDirectories() {
		if(dllDirectories == null)
		{
			dllDirectories = new HashSet<String>();
			Trengen.getContributionTypeWrapper().accept(visitor);
		}
		return dllDirectories;
	}
	
	/**
	 * get the version of this contribution
	 * @return
	 */
	public String getContributionVersion(){
		if(contributionVersion==null||"".equals(contributionVersion)){
			return "0.0.0";
		}
		return contributionVersion;
	}
	
	private void setContributionVersion(String contributionVersion) {
		if(contributionVersion==null){
			contributionVersion="0.0.0";
		}
		this.contributionVersion = contributionVersion;
	}


}
