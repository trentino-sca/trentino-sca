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
package org.trentino.trengen.tools.generation.cmake;

import java.io.File;
import java.util.HashSet;
import java.util.Set;

import org.trentino.trengen.sca.model.CPPImplementation;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.Implementation;
import org.trentino.trengen.tools.generation.Context;
import org.trentino.trengen.tools.generation.modelloader.SCAModelToSCAMirrorModelConverter;
import org.trentino.trengen.tools.scavalidation.ContributionTypeWrapper;
import org.trentino.trengen.tools.scavalidation.ContributionVisitor;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.tools.trengen.Util;

/**
 * contains input data needed by the generator
 */
public class ContextCmake extends Context {
	SCAModelToSCAMirrorModelConverter	converter;
	private String	                  generationProjectName;
	private String	                  trentinoRuntimeDir;
	private String	                  defaultInstallPath;
	private String	                  contributionDir;
	private String	                  contributionLibName;
	private Set<String>	              includeDirs	  = new HashSet<String>();
	private Set<String>	              linkDirectories	= new HashSet<String>();
	private Set<String>	              libraries	      = new HashSet<String>();
	private String	                  installDir;
	private String	                  generationProjNameUpperCase;
	private Set<String>	              externalDirs;

	public String getInstallDir() {
		return installDir;
	}

	public void setInstallDir(String installDir) {
		this.installDir = installDir;
	}

	public Set<String> getIncludeDirs() {
		return includeDirs;
	}

	public void setIncludeDirs(String includeDirs) {
		if(includeDirs == null)
		{
			return;
		}
		String temp = includeDirs.replace('\\', '/');
		String[] parts = temp.split("[;,]");
		if(parts != null)
		{
			for (String part : parts)
			{
				this.includeDirs.add(new File(part).getAbsolutePath().replace("\\", "/"));
			}
		}
	}


	public void setLinkDirectories(String contributionLibDirs) {
		
		if(contributionLibDirs == null)
		{
			return;
		}
		String temp = contributionLibDirs.replace('\\', '/');
		String[] parts = temp.split("[;,]");
		if(parts != null)
		{
			for (String part : parts)
			{
				this.linkDirectories.add(new File(part).getAbsolutePath().replace("\\", "/"));
			}
		}
	}

	public String getContributionLibName() {
		return contributionLibName;
	}

	public void setContributionLibName(String contributionLibName) {
		this.contributionLibName = contributionLibName;
	}

	public String getContributionDir() {
		return contributionDir;
	}

	public void setContributionDir(String contributionDir) {
		this.contributionDir = contributionDir.replace('\\', '/');
	}

	public String getDefaultInstallPath() {
		return defaultInstallPath;
	}

	public void setDefaultInstallPath(String defaultInstallPath) {
		this.defaultInstallPath = defaultInstallPath.replace('\\', '/');
	}

	public String getTrentinoRuntimeDir() {
		return trentinoRuntimeDir;
	}

	public void setTrentinoRuntimeDir(String trentinoRuntimeDir) {
		this.trentinoRuntimeDir = trentinoRuntimeDir.replace('\\', '/');
	}

	public ContextCmake (SCAModelToSCAMirrorModelConverter c) {
		converter = c;
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

	public String getGenerationProjectName() {
		return generationProjectName;

	}

	public void setGenerationProjectName(String generationProjectName) {
		this.generationProjectName = generationProjectName;
	}

	public void setGenerationProjectNameUpperCase(String generationProjNameUC) {
		this.generationProjNameUpperCase = generationProjNameUC;

	}

	public String getGenerationProjectNameUpperCase() {
		return this.generationProjNameUpperCase;

	}

	/**
	 * @return
	 */
	public Set<String> getLinkDirectories() {
		return linkDirectories;
	}

	public Set<String> getLibraries() {
		return libraries;
	}

	public Set<String> getExternalDirs() {
		if(externalDirs == null)
		{
			externalDirs = new HashSet<String>();
			String dirs = Trengen.getOption("external_src_dir");
			if(dirs !=null && dirs.length()>0){
				String[] parts = dirs.split("[;,]");
				for(String p : parts){
					externalDirs.add(p.replace("\\", "/"));
				}
			}
		}
		return externalDirs;
	}

	/**
	 * @param libPath
	 */
	public void addLibs(String libPath) {
		String libs ="";
		if(libPath == null)
		{
			return ;
		}
		String[] parts = libPath.split("[;,]");

		for(String part: parts){
			libs+=" "+part;
		}

		String[] libsarray = libs.split("[ ]");
		String [] prefixes ={"optimized","debug"};
		String currentPrefix="";
		for (String lib : libsarray)
		{
			
			boolean found = false;
			for(String pre: prefixes){
				if(pre.equalsIgnoreCase(lib.trim())){
					currentPrefix=pre+";";
					found =true;
					break;
				}
			}
			if(found){
				continue;
			}
			
			getLibraries().add(currentPrefix+lib.trim());
			currentPrefix="";
		}
		
	}
	public static  void prepareContextCMake(String runtimeDir, String installPath, 
			String libPath, String includeDirs, String libDirsExpanded,
	        final ContextCmake contextCMake, File generationDirectory,
	        ContributionTypeWrapper	contributionTypeWrapper) {
		contextCMake.setTrentinoRuntimeDir(runtimeDir);
		String generationProjName =contextCMake. getGenerationProjectNameFolder();
		String generationProjNameUpperCase =contextCMake. getGenerationProjectNameFolderUpperCase();
		String contributionDir = new File(contextCMake.contributionDir).getAbsolutePath();
		// generated code CMAKE Default install path
		if(installPath == null)
		{
			installPath = new File(contributionDir).getParentFile().getAbsolutePath();
		}
		contextCMake.setGenerationProjectName(generationProjName);
		contextCMake.setDefaultInstallPath(installPath);
		contextCMake.setInstallDir(new File(contributionDir).getName());
		contextCMake.addLibs(libPath);
		contextCMake.setGenerationProjectNameUpperCase(generationProjNameUpperCase);
        ContributionVisitor contributionVisitor = new ContributionVisitor() {
        	@Override
        	public void visit(Component obj) {
        	 Implementation impl =	obj.getImplementation().getValue();
        	 if(impl instanceof CPPImplementation){
        		 CPPImplementation cppImpl = (CPPImplementation) impl;
        		 String library = cppImpl.getLibrary();
        		 if(library==null ||"".equals(library) ||"sca-contribution".equals(library)){
        			 return;
        		 }
				contextCMake.getLibraries().add(library);
        		 String path =cppImpl.getPath();
        		 if(path!=null){
        			contextCMake.getLinkDirectories().add(path); 
        		 }
        		 
        	 }
        		
        	}
		};
		contributionTypeWrapper.accept(contributionVisitor );		

		contextCMake.setLinkDirectories(libDirsExpanded);
		contextCMake.setIncludeDirs(includeDirs);

		contextCMake.setOutputDir(generationDirectory);

	}
	
	private  String getGenerationProjectNameFolder() {
		return Trengen.getInstance().getApplicationNameLowerCase() + "Gen";
	}

	private  String getGenerationProjectNameFolderUpperCase() {
		return Trengen.getInstance(). getApplicationNameUpperCase() + "GEN";
	}
}
