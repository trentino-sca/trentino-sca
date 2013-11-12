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
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import org.trentino.trengen.scamodelmirror.ComponentType;
import org.trentino.trengen.scamodelmirror.ContributionType;
import org.trentino.trengen.tools.generation.Context;
import org.trentino.trengen.tools.generation.modelloader.ComponentComponentTypeAssociation;
import org.trentino.trengen.tools.generation.modelloader.CompositeMirrorWrapper;
import org.trentino.trengen.tools.generation.modelloader.SCAModelToSCAMirrorModelConverter;
import org.trentino.trengen.tools.generation.reflection.ContextReflection;
import org.trentino.trengen.tools.scavalidation.DirectoryScanner;
import org.trentino.trengen.tools.trengen.Trengen;

/**
 * contains input data needed by the generator
 */
public class ContextProxiesWrappers extends Context {
	private SCAModelToSCAMirrorModelConverter	converter;
	private Set<String>	                  usingDirectives;
	private Set<String>	                      declaredBindings	= new HashSet<String>();
	Set<String>	                          cppInterfaces	   = new HashSet<String>();
	private File	                          outputDir;
	private String	                          contributionName;
	private ContextReflection contextReflection;

	public ContextProxiesWrappers (SCAModelToSCAMirrorModelConverter c) {
		converter = c;
	}

	public SCAModelToSCAMirrorModelConverter converter() {
		return converter;
	}

	/**
	 * @param converter2
	 * @param name
	 */
	public ContextProxiesWrappers (SCAModelToSCAMirrorModelConverter converter2, String contributionName) {
		converter = converter2;
		if(contributionName != null)
		{
			contributionName = contributionName.replace(' ', '_');
			contributionName = contributionName.replace('.', '_');
			contributionName = contributionName.replace('-', '_');
			contributionName = contributionName.replace('+', '_');
			this.contributionName = contributionName;
		}
	}

	public Set<ReferenceServiceInterface> getServiceInterfaces() {
		return new TreeSet<ReferenceServiceInterface>(converter.getServiceInterfaces()) ;
	}

	public Set<ReferenceServiceInterface> getReferenceInterfaces() {
		return new TreeSet<ReferenceServiceInterface>(converter.getReferenceInterfaces());
	}

	public Set<String> getIncludes() {
		Map<String, Object> includesMap = new HashMap<String, Object>();
		Set<String> includes = new HashSet<String>();

		for (ReferenceServiceInterface obj : converter.getReferenceInterfaces())
		{

			String toBeIncluded = obj.getInterfaceHeader().toString();//DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), obj.getInterfaceHeader().toString());
			// toBeIncluded =
			// toBeIncluded.replace(Trengen.getScaValidationFolder().getAbsolutePath(),
			// "");
			if(toBeIncluded == null)
			{
				continue;
			}
			toBeIncluded = toBeIncluded.replace("\\", "/");
			// toBeIncluded = "../" + Trengen.getApplicationNameLowerCase() +
			// toBeIncluded;
			includes.add(toBeIncluded);
		}

		for (ReferenceServiceInterface obj : getServiceInterfaces())
		{
			String toBeIncluded = obj.getInterfaceHeader().toString();//DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), obj.getInterfaceHeader().toString());
			if(toBeIncluded == null)
			{
				continue;
			}
			// toBeIncluded =
			// toBeIncluded.replace(Trengen.getScaValidationFolder().getAbsolutePath(),
			// "");
			toBeIncluded = toBeIncluded.replace("\\", "/");
			// toBeIncluded = "../" + Trengen.getApplicationNameLowerCase() +
			// toBeIncluded;
			includes.add(toBeIncluded);
		}

		for (Map.Entry<String, Object> entryType : includesMap.entrySet())
		{
			String key = entryType.getKey();
			includes.add(key);
		}
		return includes;
	}

	public Set<String> getUsingDirectives() {
		if(usingDirectives == null)
		{
			usingDirectives = new HashSet<String>();
			for (Map.Entry<String, Object> entryType : converter.getUsingDirectivesMap().entrySet())
			{
				String key = entryType.getKey();
				usingDirectives.add(key);
			}
			for(ReferenceServiceInterface itf : converter.getReferenceInterfaces()){
				String namespace = itf.getNamespace();
				usingDirectives.add(namespace);
			}
			for(ReferenceServiceInterface itf : converter.getServiceInterfaces()){
				String namespace = itf.getNamespace();
				usingDirectives.add(namespace);
			}
		}

		return usingDirectives;
	}

	@Override
	public File getOutputDir() {
		return outputDir;
	}

	@Override
	public void setOutputDir(File outputDir) {
		this.outputDir = outputDir;
	}

	public Set<String> getUsingList() {
		Set<String> result = new HashSet<String>();
		if(getReferenceInterfaces() != null)
		{
			for (ReferenceServiceInterface ns : getReferenceInterfaces())
			{
				if(ns.getRawNameSpaceSemicolonSeparated() != null)
				{
					result.add(ns.getRawNameSpaceSemicolonSeparated());
				}
			}
		}
		if(getServiceInterfaces() != null)
		{
			for (ReferenceServiceInterface ns : getServiceInterfaces())
			{
				if(ns.getRawNameSpaceSemicolonSeparated() != null)
				{
					result.add(ns.getRawNameSpaceSemicolonSeparated());
				}
			}
		}

		return result;
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

	public String getContributionName() {
		return "Gen";
	}

	public void setContributionName(String contributionName) {
		this.contributionName = contributionName;
	}

	/**
	 * return a String representation of the output dir, where all special
	 * characters has been removed
	 * @return
	 */
	public String getRootPrefix() {
		String outputDir = this.getOutputDir().getName();
		outputDir = outputDir.replace(' ', '_');
		outputDir = outputDir.replace('.', '_');
		outputDir = outputDir.replace('-', '_');
		outputDir = outputDir.replace('+', '_');
		return outputDir;
	}

	public Set<ReferenceServiceInterface> getRemotableServices() {
		return converter.getRemotableServices();
	}


	public Set<String> getDeclaredBindings() {
		return declaredBindings;
	}

	public String getBindings() {
		String bindings = declaredBindings.toString();
		bindings = bindings.replace("[", "");
		bindings = bindings.replace("]", "");
		bindings = bindings.replace(" ", "");
		return bindings;
	}

	public void addCppInterfaceFile(String fileName) {
		cppInterfaces.add(fileName);
	}

	public Set<String> getCppInterfaces() {
		return cppInterfaces;
	}

	public boolean hasRemotableServices() {
		if(getRemotableServices().size() > 0)
		{
			return true;
		}
		return false;
	}

//	public boolean hasRemotableReferences() {
//		if(getRemotableReferences().size() > 0)
//		{
//			return true;
//		}
//		return false;
//	}
	
	public Set<String> getUsingDirectivesForProxies(){
		Set<String> res = new HashSet<String>();
		for(ReferenceServiceInterface itf : getReferenceInterfaces()){
			String ns = itf.getNamespace();
			res.add(ns);
		}
		return res;
	}

	public ContextReflection getContextReflection() {
    	return contextReflection;
    }

	public void setContextReflection(ContextReflection contextReflection) {
    	this.contextReflection = contextReflection;
    }
	
	Set<Object> bindingHelpers = new HashSet<Object>();
	public void registerBindingHelper(Object factory){
		if(factory!=null){bindingHelpers.add(factory);}
	}
	
	public int getNumberOfHelpers(){
		return bindingHelpers.size();
	}
	
	public List<InvokeInfo> getInvokeInfo(){
		List<InvokeInfo> res = new ArrayList<ContextProxiesWrappers.InvokeInfo>();
		for(int i=0; i< 10 ; i++){
			InvokeInfo inf = new InvokeInfo(i);
			res.add(inf);
		}
		return res;
	}
	
	public static  class InvokeInfo{
		private List<InvokeInfoArg> arguments = new ArrayList<ContextProxiesWrappers.InvokeInfoArg>();
		public InvokeInfo(int numberOfArgs){
			for(int i=0;i< numberOfArgs;i++){
				InvokeInfoArg a = new InvokeInfoArg(i);
				arguments.add(a);
			}
		}
		public List<InvokeInfoArg> getArguments(){
			return arguments;
		}
	}
	public static class InvokeInfoArg{

		private int i;

		public int getI() {
			return i;
		}

		public InvokeInfoArg(int i) {
			this.i = i;
		}}
}
