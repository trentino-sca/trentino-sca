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

package org.trentino.trengen.tools.scavalidation;

import java.io.File;
import java.io.FileFilter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.xml.namespace.QName;

import org.apache.log4j.Logger;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.sca.model.CPPExport;
import org.trentino.trengen.sca.model.CPPImport;
import org.trentino.trengen.tools.trengen.OSValidator;
import org.trentino.trengen.tools.trengen.Trengen;

public class DirectoryScanner {

	protected static final Logger	logger	    = Logger.getLogger(DirectoryScanner.class);
	static List<File>	          artifactFiles	= new ArrayList<File>();
	private static Map<String,CPPImport> importedDirs = new HashMap<String, CPPImport>();
	private static List<CPPExport> exportedDirs = new ArrayList<CPPExport>();
	private DirectoryScanner () {
	}


    
    private static String resolveImportedPath(String path){
    	if(path==null){
    		return null;
    	}
    	int index = path.indexOf(":");
    	if(index <=0){
    		return path;
    	}
    	String name = path.substring(0,index);
    	CPPImport f = importedDirs.get(name);
    	if(f ==null){
    		throw new ValidationException("imported symbol does not exists. " +name+
    				"\nSee path: "+path);
    	}
    	File location = getLocationForImport(f);
    	if(location==null){
        		throw new ValidationException("imported symbol is not exported by another contribution. " +name+
        				"\nSee path: "+path+"\nVersion: "+f.getVersion());
    	}
    	File f2 = new File(location,path.substring(index+1));
    	return f2.getAbsolutePath();
    }

	private static File getLocationForImport(CPPImport f) {
		if(f==null){
			return null;
		}
		String location = f.getLocation();

		CPPExport export =null;
		for(CPPExport entry: exportedDirs){
			QName qName = entry.getName();
			String prefix = qName.getPrefix();
			String val = (prefix!=null? prefix+":":"")+qName.getLocalPart();
			if(val.equals(location)){
				
				boolean eq= versionEquals(f.getVersion(),entry.getVersion());
				
				if(!eq){
					logger.warn(String.format("Version mismatch for imported name '%s'. Required version '%s'. Found version '%s'. Skipping found name.", location,f.getVersion(),entry.getVersion()));
					continue;
				}
				export = entry;
			}
		}

		if(export==null){
			//Then resolve the location as a path.
			// First as an absolute path
			File lf = new File(location);
			if(lf.exists()){
				return lf;
			}
			//otherwise, resolve it as a file relative to root directory
			lf = new File(Trengen.getInstance().getContributionFolder(),location);
			if(lf.exists()){
				return lf;
			}
			return null;
		}
		return new File(export.getPath());
	}



	private static boolean versionEquals(String version, String version2) {
		if(version==null){
			return version ==version2;
		}
		return version.equals(version2);
	}



	public static String makeHeaderAttributeFullPath(List<File> givenPaths, String relativePath) {
		relativePath = resolveImportedPath(relativePath);
		if(relativePath==null){
			return null;
		}
		
		if(new File(relativePath).isAbsolute()){
			return relativePath;
		}
		
		for (File givenPath : givenPaths)
		{
			String res = makeHeaderAttributeFullPath(givenPath, relativePath);
			if(res != null)
			{
				return res;
			}
		}
		return null;
	}
	
	public static List<String> makeHeaderAttributeFullPathList(List<File> givenPaths, String relativePath) {
		relativePath = resolveImportedPath(relativePath);
		List<String> resList = new ArrayList<String>();
		if(relativePath==null){
			return resList;
		}
		if(new File(relativePath).isAbsolute()){
			resList.add(relativePath);
			return resList;
		}
		for (File givenPath : givenPaths)
		{
			String res = makeHeaderAttributeFullPath(givenPath, relativePath);
			if(res != null)
			{
				resList.add(res);
			}
		}
		return resList;
	}

	private static String makeHeaderAttributeFullPath(File givenPath, String relativePath) {
		if(!givenPath.exists())
		{
			logger.error("\nFile (" + givenPath.getAbsolutePath() + ") is missing\n");
			return null;
		}
		if(OSValidator.isUnix())
		{
			relativePath = relativePath.replace("\\", "/");
			if(relativePath.startsWith("."))
			{
				relativePath = relativePath.substring(1);
			}
			if(relativePath.startsWith("/"))
			{
				relativePath = relativePath.substring(1);
			}
		}

		File headerFile = new File(givenPath, relativePath);
		if(headerFile == null || !headerFile.exists())
		{
			// do not log error. Error should be logged by caller. There are
			// some calles for whoch this is not an error
			return null;
		}

		String fullAbsoluteHeaderPath = null;
		try
		{
			fullAbsoluteHeaderPath = headerFile.getCanonicalPath();
		} catch (IOException e)
		{
			logger.error("Header file (" + headerFile.getPath()
			        + ") canonical path error. Be sure that you are giving correct relative paths in SCDLs");
			return null;
		}
		return fullAbsoluteHeaderPath;
	}

	// ----------------------------------------------------------
	public static File searchArtifactFullPath(String artifactName) {
		String fullAbsoluteHeaderPath = makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), artifactName);
		if(fullAbsoluteHeaderPath == null)
		{
			return null;
		}
		File file = new File(fullAbsoluteHeaderPath);
		return file;

	}


	// -------------------------------------------------------------
	/**
	 * Tries to locate all the artifacts within the whole contribution tree with
	 * the given extension (used only for the composites)
	 */
	public static List<File> SearchArtifacts(List<File> dirs,final String extension) {
		List<File> compositeFiles = new ArrayList<File>();
		if(extension == null)
		{
			return compositeFiles;
		}
		
		final List<FileFilter> filterHolder = new ArrayList<FileFilter>();
		final List<File> accepted = compositeFiles;
		final String lowerCaseExtension = extension.toLowerCase();
		final FileFilter filter = new FileFilter() {

			Set<File> visited = new HashSet<File>();
			@Override
			public boolean accept(File pathname) {
				if(visited.contains(pathname)){
				   return false;
				}
				visited.add(pathname);
				if(pathname.isDirectory()){
					pathname.listFiles(filterHolder.get(0));
					return false;
				}
				
			
				if(pathname.isFile() && pathname.getName().toLowerCase().endsWith(lowerCaseExtension)){
					accepted.add(pathname);
					return true;
				}
				return false;
			}
		};
		filterHolder.add(filter);
		for (File searchPath : dirs)
		{
			searchPath.listFiles(filter);
		}
		
		return compositeFiles;
	}



	public static File searchLibraryInTheWholeContribution(final String libFullName) {
		List<File> libraryFiles = DirectoryScanner.SearchArtifacts(Trengen.getScaValidationFolder(), "dll");
		if(libraryFiles.size() == 0)
		{
			libraryFiles = DirectoryScanner.SearchArtifacts(Trengen.getScaValidationFolder(), "so");
			if(libraryFiles.size() == 0)
			{
				return null;
			}
		}

		for (int i = 0; i < libraryFiles.size(); i++)
		{
			if(libraryFiles.get(i).getName().equals(libFullName))
			{
				return libraryFiles.get(i);
			}
		}
		return null;
	}

	/**
	 * add a Name exported by a contribution
	 * @param cpp: CPPExport
	 * @param f: sca-contribution.xml of the exporting file
	 */
	public static void addExportedName(CPPExport cpp, File f) {
		logger.info("Adding exported name "+cpp.getName()+"\n Path "+f);
		String path = cpp.getPath();
		File file = new File(path);
		if(!file.isAbsolute()){
			//File is relative to the contribution directory
			file = new File(f.getParentFile().getParent(),path);
		}
		cpp.setPath(file.getAbsolutePath());
		exportedDirs.add(cpp);
	}

	public static void addImportedName(CPPImport cpp) {
		importedDirs.put(cpp.getName().getLocalPart(), cpp);
		
	}
}
