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
package org.trentino.trengen.tools.trengen;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Properties;
import java.util.regex.Pattern;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.xml.DOMConfigurator;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.sca.model.CPPImplementation;
import org.trentino.trengen.sca.model.CPPInterface;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.Implementation;
import org.trentino.trengen.tools.bindingframework.BindingCodeGeneratorData;
import org.trentino.trengen.tools.bindingframework.BindingCodeGeneratorManager;
import org.trentino.trengen.tools.bindingsca.TIDL2CppInterface;
import org.trentino.trengen.tools.bindingsca.TIDLParseException;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.generation.CPPModelProvider;
import org.trentino.trengen.tools.generation.cmake.CMakeGenerator;
import org.trentino.trengen.tools.generation.cmake.ContextCmake;
import org.trentino.trengen.tools.generation.configfile.ConfigFileGenerator;
import org.trentino.trengen.tools.generation.configfile.ContextConf;
import org.trentino.trengen.tools.generation.modelloader.ModelLoaderGenerator;
import org.trentino.trengen.tools.generation.modelloader.SCAModelToSCAMirrorModelConverter;
import org.trentino.trengen.tools.generation.proxieswrappers.ContextProxiesWrappers;
import org.trentino.trengen.tools.generation.proxieswrappers.ProxyGenerator;
import org.trentino.trengen.tools.generation.reflection.ContextReflection;
import org.trentino.trengen.tools.scavalidation.CommandLineOptions;
import org.trentino.trengen.tools.scavalidation.ComponentWrapper;
import org.trentino.trengen.tools.scavalidation.ConformanceManagerCppImplArtifactsEclipseCDT;
import org.trentino.trengen.tools.scavalidation.ContributionTypeWrapper;
import org.trentino.trengen.tools.scavalidation.ContributionVisitor;
import org.trentino.trengen.tools.scavalidation.DirectoryScanner;
import org.trentino.trengen.tools.scavalidation.IConformanceManagerCppImpArtifacts;
import org.trentino.trengen.tools.scavalidation.ScaValidationManager;
import org.trentino.trengen.tools.scavalidation.utils.UnZipUtil;

public class Trengen {

	private static final String	          GEN	                    = "Gen";
	private  List<File>	          scaValidationFolder	    = new ArrayList<File>();
	private  File	                  contributionFolder;
	private  String	              outDir;
	protected static final Logger	      logger	                = Logger.getLogger(Trengen.class);
	public   static Properties	      properties	            = null;

	private  ContributionTypeWrapper	contributionTypeWrapper	= null;
	private  boolean	              targetComponentExists;

	public static final int	              CAPITALIZE_NUMBER	        = 32;
	
	private final CommandLineOptions options;
	
	private static Trengen instance;
	private  Throwable lastException;
	private static final String regex = "(\\d)+\\.(\\d)+\\.(\\d)+(\\.\\w+)?";
	private static final Pattern pattern = Pattern.compile(regex);
	
	public static void initInstance(String... args) throws Exception{
		if(args ==null){
			instance =null;
		}
		instance = new Trengen(args);
	}
	
	public static Trengen getInstance(){
		if(instance ==null){
			throw new IllegalArgumentException("Trengen is not initialized. Call init first");
		}
		return instance;
	}

	public static List<File> getScaValidationFolder() {
		return getInstance().scaValidationFolder;
	}

	public  File getContributionFolder() {
		return contributionFolder;
	}

	private  String getGenerationProjectNameFolder() {
		return getApplicationNameLowerCase() + GEN;
	}

	private  String getGenerationProjectNameFolderUpperCase() {
		return getApplicationNameUpperCase() + "GEN";
	}

	private  String getApplicationNameLowerCase() {
		String appName = contributionFolder.getAbsolutePath();
		int lastSlash = appName.lastIndexOf("\\");
		appName = appName.substring(lastSlash + 1);

		return appName;
	}

	public  String getApplicationNameUpperCase() {
		String appName = getApplicationNameLowerCase();

		String upperAppName = "";
		for (int i = 0; i < appName.length(); i++)
		{
			upperAppName += Util.toUpper(appName.charAt(i));
		}
		return upperAppName;
	}

	public  void setScaValidationFolder(File aFolder) {
		if(scaValidationFolder != null)
		{
			scaValidationFolder.clear();
			contributionFolder = aFolder;
			scaValidationFolder.add(aFolder);
		}
	}

	public Trengen (String[] args) throws Exception {
		options = new CommandLineOptions(args);
	}

	public static void main(String[] args) {
		try
		{
			 initInstance(args);
			 
			if(!getInstance().doMain(args))
			{
				doExit(null);
			}
		} catch (ValidationException e)
		{
			logger.error(getInstance().stringValueOf(e));
			doExit(e);
			
		} catch (IllegalStateException e)
		{
			logger.error(e.getMessage());
			doExit(e);
		} catch (TIDLParseException e)
		{
			logger.error(e.getMessage());
			doExit(e);
		}

		catch (Exception e)
		{
			logger.error("Unexpected error occurred while running the Trengen tool. The Java exception is below.", e);
			doExit(e);
		}
	}

	/**
     * 
     */
    private static void doExit(Throwable t) {
	    getInstance().lastException = t;
	    String disable = Trengen.getOption("-disable_exit");
	    boolean enEx = disable==null|| disable.length()==0 || !Boolean.parseBoolean(disable);
	    if(enEx){
	    	System.exit(1);
	    }
    	
    }

	/**
	 * @param e
	 * @return The string representation of the Validation exception
	 */
	public  String stringValueOf(ValidationException e) {
		final StringBuilder res = new StringBuilder("--------------------------------------------------------\n");
		if(!e.getExceptions().isEmpty()){
			for(ValidationException ex : e.getExceptions()){
				res.append(stringValueOf(ex)).append("\n");
			}
		}
		
		for(String msg : e.getMessages()){
			res.append(msg);
		}
		
		if(e.getContributionTypeWrapper() != null && contributionTypeWrapper == null)
		{
			contributionTypeWrapper = (ContributionTypeWrapper) e.getContributionTypeWrapper();
		} 
		boolean refFound =false;
		for (final Object obj : Collections.asLifoQueue(e.getEntityQueue()))
		{
			if(obj instanceof ComponentReference && !refFound)
			{
				final ComponentReference ref = (ComponentReference) obj;
				res.append("\nReference name: ").append(ref.getName());
				refFound =true;
			}

			else if(obj instanceof ComponentWrapper)
			{
				printCompWrapper(res, (ComponentWrapper) obj);
			}
			else if(obj instanceof CPPInterface)
			{
				CPPInterface itf = (CPPInterface) obj;
				res.append("\nInterface: ").append(itf.getClazz()).append(" Location: ").append(itf.getHeader());
			}
			else if(obj instanceof ComponentType)
			{
				ContributionVisitor visitor = new ContributionVisitor() {
					@Override
					public void visit(ComponentWrapper compWrapper) {
						if(obj.equals(compWrapper.getScaModelComponentType()))
						{
							printCompWrapper(res, compWrapper);
						}
					}
				};
				if(contributionTypeWrapper != null)
				{
					contributionTypeWrapper.accept(visitor);
				}
			}
		}
		return res.toString();
	}

	private static void printCompWrapper(final StringBuilder res, ComponentWrapper ref) {
		Component comp = ref.getScaModelComponent();
		if(comp != null)
			res.append("\nComponent name: ").append(comp.getName());

		ComponentType compType = ref.getScaModelComponentType();
		if(compType != null)
		{
			res.append("\nComponent type file:").append(ref.getScaModelComponentTypeFile());
		}
	}

	// -----------------------------------
	private  boolean doMain(String[] args) throws Exception {
		


		 

		// Check and access the input SCA composite directory
		String tidlFile = (String) options.getOption("gencppitf");
		String inc = (String) options.getOption("inc");
		String contributionPath = (String) options.getOption("cont");
		String help = (String) options.getOption("h");
		if(help==null){
			help = (String) options.getOption("help");
		}
		if(help!=null){
			printUsage();
			return true;
		}

		if(contributionPath != null && contributionPath.equals("."))
		{
			String currentDir = new File(".").getAbsolutePath();
			contributionPath = currentDir.substring(0, currentDir.length() - 1);
		}

		/*
		 * BUG 754: cmake uses cygdrive prefix, so Trengen receives command line parameter '-cont /cygdrive/C/...' to build tests and fails.
		 */
		if(contributionPath != null)
		{
			boolean isCygwinPath = contributionPath.startsWith("/cygdrive/") || contributionPath.startsWith("\\cygdrive\\");
			if (isCygwinPath == true)
			{
				contributionPath = contributionPath.replace("\\cygdrive\\", "");
				contributionPath = contributionPath.replace("/cygdrive/", "");

				int indexOfFirstSep = contributionPath.indexOf("\\");
				if (indexOfFirstSep == 0)
					indexOfFirstSep = contributionPath.indexOf("/");
				
				String driveName = contributionPath.substring(0, indexOfFirstSep);
				driveName += ":";
				
				contributionPath = driveName + contributionPath.substring(indexOfFirstSep);
			}
		}

		outDir = (String) options.getOption("outdir");
		String debugOrRelease = (String) options.getOption("d");
		String verbose = (String) options.getOption("v");
		String runtimeDir = (String) options.getOption("rtdir");
		String installPath = (String) options.getOption("install_dir");
		String libDirs = (String) options.getOption("libdirs");
		String libPath = (String) options.getOption("lib");
		String includeDirs = (String) options.getOption("includedirs");
		String rootFolder = (String) options.getOption("rootdir");
		// String parser = (String) CommandLineOptions
		// .getOption("parserEclipseCDT");
		String genCmake = (String) options.getOption("generateCMake");


		// debug or release
		if(debugOrRelease == null)
		{
			debugOrRelease = "r";
		}
		else if(!(debugOrRelease.trim().equals("r") || debugOrRelease.trim().equals("d")))
		{
			logger.error("Please provide a correct log option. Use -d for debug\n");
			printUsage();
			return false;
		}

		if(debugOrRelease.equals("d"))
		{
			// load the log configuration file for debug
			DOMConfigurator.configure(ConfigLoader.LOG_CONFIG_XML_DEBUG);
		}
		else
		{
			// load the log configuration file for release
			DOMConfigurator.configure(ConfigLoader.LOG_CONFIG_XML);
		}

		// verbose for enabling INFO LOGS
		if(verbose != null && verbose.equals("v"))
		{
			Logger.getRootLogger().setLevel(Level.INFO);

		}
		else
		{
			Logger.getRootLogger().setLevel(Level.WARN);

		}

		if(tidlFile != null)
		{
			generateCPPInterface(tidlFile, inc);
			return true;
		}
		
		// check runtime directory
		if(runtimeDir != null && runtimeDir.trim().length() > 0)
		{
			if(runtimeDir.endsWith(File.separator))
			{
				runtimeDir = runtimeDir.substring(0, runtimeDir.length() - 1);
			}
			File rtDir = new File(runtimeDir);
			if(!rtDir.exists() || !rtDir.isDirectory())
			{
				logger.error("Specified runtime directory " + runtimeDir + " does not exists or is not a directory.");
				return false;
			}
		}
		else
		{
			runtimeDir = new File(".").getAbsolutePath();
		}

		IConformanceManagerCppImpArtifacts conformanceManagerCppImplArtifacts;
		conformanceManagerCppImplArtifacts = new ConformanceManagerCppImplArtifactsEclipseCDT();

		if(null == contributionPath)
		{
			logger.error("Please provide a SCA composite directory name as a \"cont\" option.");
			printUsage();
			return false;
		}
		contributionFolder = new File(contributionPath);
		scaValidationFolder.add(contributionFolder);
		if(rootFolder != null)
		{
			String[] paths = rootFolder.split("[;,]");
			for (String path : paths)
			{
				scaValidationFolder.add(new File(path));
			}
		}

		if(isContributionAFile())
		{
			if(contributionPath.endsWith(".zip"))
			{
				if(!UnZipUtil.extractFolder(contributionFolder.getAbsolutePath()))
				{
					logger.error("Contribution can be specified either with a directory path or with a valid zip file");
					return false;
				}
				else
				{
					String unzippedDirName = contributionPath.substring(0, contributionPath.lastIndexOf('.'));
					scaValidationFolder.get(0).delete();
					scaValidationFolder.add(new File(unzippedDirName));
				}
			}
			else
			{
				// BUG #491: User should be forced to use " " for paths and
				// files; because there may be
				// some white spaces in the paths.
				logger.error("Source should be either a DIRECTORY or a valid ZIP file. You may be using some spaces in the "
				        + "contribution path. PLEASE USE \" \" FOR THE PATHS.");
				return false;
			}

		}

		ImportExport.scanImportedContributions((String) options.getOption("ec"));
		ScaValidationManager scaValidationManager = new ScaValidationManager(conformanceManagerCppImplArtifacts);
		contributionTypeWrapper = scaValidationManager.validate(scaValidationFolder, contributionFolder);
		if(contributionTypeWrapper == null)
		{
			return false;
		}

		if(outDir == null)
		{
			outDir = new File(contributionFolder.getParentFile(), contributionFolder.getName() + GEN).getAbsolutePath();
		}

		RemoteServiceModelCreator creator = new RemoteServiceModelCreator();
		creator.createRemoteServices(contributionTypeWrapper);
		SCAModelToSCAMirrorModelConverter converter = new SCAModelToSCAMirrorModelConverter(new CPPModelProvider(conformanceManagerCppImplArtifacts));

		converter.initialize();
		File generationDirectory = new File(outDir);
		String contributionName = contributionFolder.getName();
		if(contributionName != null)
		{
			contributionName = contributionName.replace(' ', '_');
			contributionName = contributionName.replace('.', '_');
			contributionName = contributionName.replace('-', '_');
			contributionName = contributionName.replace('+', '_');
		}
		ContextProxiesWrappers contextProxyWrapper = new ContextProxiesWrappers(converter, contributionName);
		contextProxyWrapper.setOutputDir(generationDirectory);
		ContextCmake contextCMake = new ContextCmake(converter);
		ContextReflection contextReflection = new ContextReflection(converter);
		prepareContextCMake(runtimeDir, installPath, libPath, includeDirs, libDirs, contextCMake, generationDirectory);

		BindingCodeGeneratorData data = new BindingCodeGeneratorData(contributionTypeWrapper, contextProxyWrapper, contextCMake, generationDirectory,
		        contributionName);
		data.setConverter(converter);
		data.setContextReflection(contextReflection);
        contextProxyWrapper.setContextReflection(contextReflection);
		// CPP Interface generation is not part of this process, it is
		// generated before the implementation, so it is part of the Source
		// project
		// generateCPPInterface(Trengen.getScaValidationFolder().getAbsolutePath());

		BindingCodeGeneratorManager manager = new BindingCodeGeneratorManager(data);
		if(!manager.generateBindingCode())
		{
			throw new IllegalStateException("Error during binding code generate. see error description in previous output");
		}

		generateConfigFile(generationDirectory);
		generateModelLoader(converter, generationDirectory, contributionName);

		if(genCmake == null || Boolean.parseBoolean(genCmake)!=false)
		{
			generateCMakeFile(contextCMake);
		}

		generateProxyAndWrappers(contextProxyWrapper);
		logger.info("Generation output is ready under: " + outDir);
		return true;
	}

	private  boolean isContributionAFile() {
		return scaValidationFolder.size() == 1 && scaValidationFolder.get(0).isFile();
	}

	private  void generateConfigFile(File generationDirectory) throws TrengenException {
		logger.info("sca-contribution.conf is being generated...");
		ContextConf contextConf = new ContextConf();
		contributionTypeWrapper.accept(contextConf.getVisitor());
		ConfigFileGenerator configGen = new ConfigFileGenerator(contextConf);
		contextConf.setOutputDir(generationDirectory);
		configGen.generate();
		logger.info("sca-contribution.conf generated");
	}

	private  void generateProxyAndWrappers(ContextProxiesWrappers contextProxyWrapper) throws TrengenException {
		logger.info("TrentinoGenProxiesWrappers.cpp is being generated...");

		ProxyGenerator generatorProxyWrapper = new ProxyGenerator(contextProxyWrapper);
		generatorProxyWrapper.generate();
	}



	private  void generateModelLoader(SCAModelToSCAMirrorModelConverter converter, File generationDirectory, String contributionName)
	        throws TrengenException {
		logger.info("TrentinoGenModelLoader.cpp is being generated...");
		ContextProxiesWrappers contextModelLoader = new ContextProxiesWrappers(converter, contributionName);
		contextModelLoader.setOutputDir(generationDirectory);
		ModelLoaderGenerator generatorModelLoader = new ModelLoaderGenerator(contextModelLoader);
		generatorModelLoader.generate();
	}

	private  void generateCMakeFile(ContextCmake contextCMake) throws TrengenException {

		logger.info("CMakeLists.txt is being generated...");
		CMakeGenerator generatorCMake = new CMakeGenerator(contextCMake);
		generatorCMake.generate();
	}

	private  void prepareContextCMake(String runtimeDir, String installPath, String libPath, String includeDirs, String libDirsExpanded,
	        final ContextCmake contextCMake, File generationDirectory) {
		contextCMake.setTrentinoRuntimeDir(runtimeDir);
		String generationProjName = getGenerationProjectNameFolder();
		String generationProjNameUpperCase = getGenerationProjectNameFolderUpperCase();
		String contributionDir = contributionFolder.getAbsolutePath();
		// generated code CMAKE Default install path
		if(installPath == null)
		{
			installPath = new File(contributionDir).getParentFile().getAbsolutePath();
		}
		contextCMake.setGenerationProjectName(generationProjName);
		contextCMake.setDefaultInstallPath(installPath);
		contextCMake.setInstallDir(new File(contributionDir).getName());
		contextCMake.setContributionDir(contributionDir);
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

	/**
	 * This function generates cpp interface file for sca binding
	 * @throws TIDLParseException
	 */
	private  void generateCPPInterface(String tidlFilePath, String include) throws TIDLParseException {
		logger.info("CPPInterface file is being generated... " + tidlFilePath + " directory is used during generation.");
		File tdilFile = new File(tidlFilePath);
		if(!(tdilFile.exists()))
		{
			logger.error(tidlFilePath + " does not exist! Please give correct path...");
			return;
		}
		List<File> tidlPropertyFiles = new ArrayList<File>();
		List<File> javaFiles = new ArrayList<File>();
		if(tdilFile.isFile() && tidlFilePath.endsWith(".tidl.properties"))
		{
			tidlPropertyFiles.add(tdilFile);
		}
		else if(tdilFile.isFile() && tidlFilePath.endsWith(".java"))
		{
			javaFiles.add(tdilFile);
		}
		else
		{
			List<File> sp = new ArrayList<File>();
			sp.add(tdilFile);
			tidlPropertyFiles = DirectoryScanner.SearchArtifacts(sp, "tidl.properties");
		}

		if(tidlPropertyFiles.isEmpty() && javaFiles.isEmpty())
		{
			logger.error("No .tidl.properties file is found in " + tidlFilePath);
			return;
		}
		for (File tidlFile : tidlPropertyFiles)
		{
			String pathToJavaFile = Util.readTidlPropertiesFile(tidlFile);
			String pathToTidl = Util.getTidlFilePath(tidlFile, pathToJavaFile);

			// an outdir is expected in TidlToCPPInterface converter. if it is
			// null, use the current path.
			if(outDir == null)
			{
				outDir = pathToTidl;
			}

			if(pathToTidl != null && pathToJavaFile != null)
			{
				pathToJavaFile = new File(pathToTidl, pathToJavaFile).getAbsolutePath();
			}
			else
			{
				logger.error("Path to Java file is null");
				return;
			}
			logger.info("Path to java file " + pathToJavaFile);

			File javaFile = new File(pathToJavaFile);
			if(!javaFile.exists())
			{
				logger.error(pathToJavaFile + " does not exist! Please give correct path...");
				return;
			}

			generateCPPInterfaceFromJavaFile(include, javaFile, tidlFile);

		}

		for (File javaFile : javaFiles)
		{
			generateCPPInterfaceFromJavaFile(include, javaFile, null);
		}
	}

	private  void generateCPPInterfaceFromJavaFile(String include, File javaFile, File tidl) throws TIDLParseException {
		// CPP interface generation
		TIDL2CppInterface converter = new TIDL2CppInterface();

		File outDirFile = null;
		if(outDir == null)
		{
			outDir = javaFile.getParent();
		}
		outDirFile = new File(outDir);
		List<String> includes = new ArrayList<String>();

		if(include != null && !"".equals(include))
		{
			includes.add(include);
		}

		if(javaFile != null && outDirFile != null)
		{
			converter.createCppInterface(javaFile, tidl, outDirFile, includes);
		}
	}


	/**
	 * Provide a hint to the user on how to call this class
	 * @return
	 */
	public void printUsage() {
		options.printUsage();
	}

	/**
     * @return
     */
    public static ContributionTypeWrapper getContributionTypeWrapper() {
	    return getInstance().contributionTypeWrapper;
    }

	/**
     * @return
     */
    public static String getOutDir() {
	    return getInstance().outDir;
    }

	/**
     * @return
     */
    public static Properties getProperties() {
    	if(properties ==null){
    		properties = new Properties();
    		String fileName = ConfigLoader.TRENGEN_CONFIG.toString().replace("file:", "");
    		File configFile = new File(fileName);

    		if(configFile.exists())
    		{
    			InputStream is;
                try
                {
	                is = new FileInputStream(fileName);
	    			properties.load(is);
                } catch (Exception e)
                {
	               throw new IllegalArgumentException(e);
                }

    		}
    	}
	    return properties;
    }

	/**
     * @return
     */
    public boolean isTargetComponentExists() {
	    
	    return targetComponentExists;
    }



	/**
     * @param string
     * @return
     */
    public static String getOption(String key) {
	    return (String) getInstance().options.getOption(key);
    }

	public void setTargetComponentExists(boolean targetComponentExists) {
    	this.targetComponentExists = targetComponentExists;
    }

	/**
     * @param ctw
     */
    public void setContributionTypeWrapper(ContributionTypeWrapper ctw) {
	   this.contributionTypeWrapper = ctw;
	    
    }

	public Throwable getLastException() {
    	return lastException;
    }

}
