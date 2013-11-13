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
package org.trentino.trengen.tools.generation.bindingipc;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import javax.xml.bind.JAXBElement;

import org.apache.log4j.Logger;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.sca.model.Binding;
import org.trentino.trengen.sca.model.CPPInterface;
import org.trentino.trengen.sca.model.Contract;
import org.trentino.trengen.sca.model.IPCBinding;
import org.trentino.trengen.tools.bindingframework.BindingCodeGenerator;
import org.trentino.trengen.tools.bindingframework.BindingCodeGeneratorData;
import org.trentino.trengen.tools.bindingframework.BindingDescriptor;
import org.trentino.trengen.tools.bindingsca.TIDL2Protobuf;
import org.trentino.trengen.tools.bindingsca.TIDLParseException;
import org.trentino.trengen.tools.generation.TrengenGenerator;
import org.trentino.trengen.tools.generation.bindingsca.ContextCppInterface;
import org.trentino.trengen.tools.generation.bindingsca.CppTypeMapper;
import org.trentino.trengen.tools.generation.cmake.ContextCmake;
import org.trentino.trengen.tools.generation.modelloader.SCAModelToSCAMirrorModelConverter;
import org.trentino.trengen.tools.generation.proxieswrappers.ContextProxiesWrappers;
import org.trentino.trengen.tools.generation.proxieswrappers.ReferenceServiceInterface;
import org.trentino.trengen.tools.scavalidation.DirectoryScanner;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.tools.trengen.Util;

import freemarker.template.Configuration;
import freemarker.template.Template;

public class BindingIPCCodeGenerator extends TrengenGenerator implements BindingCodeGenerator {

	protected static final Logger	        logger	                      = Logger.getLogger(BindingIPCCodeGenerator.class);
	private List<String>	                beanUtilFileHeaderNames	      = new ArrayList<String>();
	private ContextProxiesWrappers	        generalProxiesWrappersContext	= null;
	private BindingIPCDescriptor	        bindingDescriptor	          = new BindingIPCDescriptor();
	TIDL2Protobuf	                        converter	                  = new TIDL2Protobuf();
	private List<ReferenceServiceInterface>	remotableReferences;
	private BindingCodeGeneratorData	    data;
	List<ReferenceServiceInterface>	        remotableServices;
	Set<ContextCppInterface>	            remotableServicesContexts;
	Set<ContextCppInterface>	            remotableReferencesContexts;

	public BindingIPCCodeGenerator () {
		super(null);
	}

	@Override
	public boolean generate(BindingCodeGeneratorData data) throws TrengenException {
		this.data = data;
		generalProxiesWrappersContext = data.getContextProxyWrapper();
		remotableServices = new ArrayList<ReferenceServiceInterface>();
		remotableServicesContexts = new TreeSet<ContextCppInterface>();
		remotableReferences = new ArrayList<ReferenceServiceInterface>();
		remotableReferencesContexts = new TreeSet<ContextCppInterface>();

		getRemotableServices();
		getRemotableReferences();

		if(remotableReferences.isEmpty() && remotableServices.isEmpty())
		{
			return true;
		}

		if(!fillPortAndURLs())
			return false;

		File generationDirectory = data.getGenerationDirectory();
		prepareContextCMake(data);

		this.context = new ContextIPCBinding(generalProxiesWrappersContext.getContributionName());

		this.context.setOutputDir(generationDirectory);

		if(!remotableServices.isEmpty() || !remotableReferences.isEmpty())
		{
			generalProxiesWrappersContext.getDeclaredBindings().add("binding.ipc");
		}

		try
		{
			if(!validate())
			{
				return false;
			}
		} catch (TIDLParseException e)
		{
			throw new TrengenException(e);
		}

		this.data = data;
		if(!generate())
		{
			return false;
		}

		return true;
	}

	private boolean fillPortAndURLs() {
		for (ReferenceServiceInterface obj : remotableReferences)
		{
			boolean filled = false;
			Contract contract = obj.getContract();
			for (JAXBElement<? extends Binding> binding : contract.getBinding())
			{
				filled = fillTheBindingRelatedStuff(binding.getValue(), obj);
			}
			if(!filled)
				return false;
		}
		return true;

	}

	private boolean fillTheBindingRelatedStuff(Binding binding, ReferenceServiceInterface refServiceInterface) {
		if(binding instanceof IPCBinding)
		{
			IPCBinding scaBinding = (IPCBinding) binding;

			String uri = scaBinding.getUri();
			if(checkIPCuri(refServiceInterface, uri))
				return true;
		}
		return false;
	}

	/**
	 * Sample: <binding.ipc uri="ipc:3178//BasicCalculatorImpl/BasicCalculator"/>
	 * This method validates the uri attribute of IPC Binding.
	 * @param refServiceInterface
	 * @param uri
	 * @return
	 */
	private boolean checkIPCuri(ReferenceServiceInterface refServiceInterface, String uri) {
		if(!uri.startsWith("ipc:"))
		{
			logger.error("uri( "+uri+" ) must start with 'ipc'. \n" );
			return false;
		}

		String uriTemp = uri.substring("ipc:".length(), uri.length());
		int index = uriTemp.indexOf("//");
		if (index == -1)
		{
			logger.error("uri( "+uri+" ) does not have a unique specifier. \n" );
			return false;
		}
		else
		{
			String memMapId = uriTemp.substring(0, index); 
			if(memMapId.equals("") || memMapId.equals(null))
			{
				logger.error("uri( "+uri+" ) does not have a unique specifier. \n" );
				return false;
			}
			String componentAndServiceStr = uriTemp.substring(index+2, uriTemp.length());
			int index2 = componentAndServiceStr.indexOf("/");
			if (index2 == -1)
			{
				logger.error("uri( "+uri+" ) does not have its target 'component/service'. \n" );
				return false;
			}
			else
			{
				//String componentStr = componentAndServiceStr.substring(0, index2); 
				String serviceStr = componentAndServiceStr.substring(index2+1, componentAndServiceStr.length());
				if(serviceStr.contains("/"))
				{
					logger.error("uri( "+uri+" ) should have 'component/service' tuple. It does not need anything else. \n" );
					return false;
				}
			}
		}

		return true;

	}

	private void prepareContextCMake(BindingCodeGeneratorData data) {
		ContextCmake contextCmake = data.getContextCMake();

		// Binding specific includes
		contextCmake.getIncludeDirs().add("${TRENTINO_RUNTIME_DIR}/include/${protobuf_folder_with_version}/include");

		/*if(!hasProtobufLib(contextCmake))
		{
			contextCmake.getLinkDirectories().add("${TRENTINO_PROTOBUF_LIB_DIR}");
			contextCmake.getLibraries().add("libprotobuf-lite");
		}*/
		// binding specific link directories

		// binding specific libraries

		contextCmake.getLibraries().add("TrentinoBindingIPC");
		contextCmake.getLibraries().add("TrentinoBindingIPCClient");
		contextCmake.getLibraries().add("TrentinoBindingCompactSoap");
	}

	private void getRemotableServices() {
		Set<ReferenceServiceInterface> services = generalProxiesWrappersContext.getRemotableServices();
		if(services.size() == 0)
		{
			return;
		}
		for (ReferenceServiceInterface service : services)
		{
			Contract contract = service.getContract();
			if(contract == null)
			{
				throw new IllegalArgumentException("contract is null in a ReferenceServiceInterface");
			}
			boolean hasIPCbinding = false;
			List<JAXBElement<? extends Binding>> bindings = contract.getBinding();
			for (JAXBElement<? extends Binding> binding : bindings)
			{
				Binding b = binding.getValue();
				if (b instanceof IPCBinding)
				{	
					hasIPCbinding=true;
					break;
				}
			}
			if (hasIPCbinding)
				remotableServices.add(service);
		}

	}

	/*private boolean hasProtobufLib(ContextCmake contextCmake) {
		Set<String> libs = contextCmake.getLibraries();
		for (String lib : libs)
		{
			if(lib.contains("libprotobuf"))
			{
				return true;
			}
		}
		return false;
	}*/

	private void getRemotableReferences() {
		SCAModelToSCAMirrorModelConverter converter = data.getConverter();
		for (ReferenceServiceInterface ref : converter.getReferenceInterfaces())
		{
			boolean isRem = bindingDescriptor.isRemoteReference(ref);
			Contract contract = ref.getContract();
			if(contract == null)
			{
				throw new IllegalArgumentException("contract is null in a ReferenceServiceInterface");
			}
			List<JAXBElement<? extends Binding>> bindings = contract.getBinding();

			for (JAXBElement<? extends Binding> binding : bindings)
			{
				if(binding.isNil())
				{
					continue;
				}
				Binding b =binding.getValue();
				if(b instanceof IPCBinding && isRem)
				{
					remotableReferences.add(ref);
				}
			}
		}
	}

	private boolean validate() throws TIDLParseException {
		if(!validateThatPortAndHostAreAvailableForRemotableReferences())
		{
			return false;
		}
		if(!validateThatRemotableServiceshasCorrespondingTIDLFiles())
		{
			return false;
		}
		return true;
	}

	private boolean validateThatRemotableServiceshasCorrespondingTIDLFiles() throws TIDLParseException {
		if(remotableServices.isEmpty())
		{
			return true;
		}
		File od = new File(Trengen.getOutDir());
		boolean found = false;
		for (ReferenceServiceInterface service : remotableServices)
		{
			Contract contract = service.getContract();
			if(contract == null)
			{
				throw new IllegalArgumentException("contract is null in a ReferenceServiceInterface");
			}
			found = true;
			CPPInterface cppInterface = service.getCppInterface();
			ContextCppInterface ctx = createInterfaceContext(cppInterface, od, service);
			remotableServicesContexts.add(ctx);

		}
		if(!found)
		{
			return false;
		}
		return true;

	}

	private boolean validateThatPortAndHostAreAvailableForRemotableReferences() throws TIDLParseException {
		File od = new File(Trengen.getOutDir());
		for (ReferenceServiceInterface referenceServiceInterface : remotableReferences)
		{
			Contract contract = referenceServiceInterface.getContract();
			if(contract == null)
			{
				throw new IllegalArgumentException("contract is null in a ReferenceServiceInterface");
			}

			CPPInterface cppInterface = referenceServiceInterface.getCppInterface();
			ContextCppInterface ctx = createInterfaceContext(cppInterface, od,referenceServiceInterface);
			remotableReferencesContexts.add(ctx);
		}
		return true;
	}

	ContextCppInterface createInterfaceContext(CPPInterface cppInterface, File od, ReferenceServiceInterface service) throws TIDLParseException {
		String header = cppInterface.getHeader();
		String headerFullpath = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), header);
		if(headerFullpath == null)
		{
			throw new IllegalArgumentException("header fullpath not found."
					+ " This error should have been catched by the Validation Engine. Please contact support: " + header);
		}

		File f = new File(headerFullpath);
		// The java file was not found. Now look for a tidl file
		String name = new File(headerFullpath).getName();
		name = name.substring(0, name.lastIndexOf("."));
		f = new File(f.getParentFile(), name + ".tidl.properties");
		if(f.exists())
		{
			// TIDL file found. check for the corresponding java file
			String pathToJavaFile = Util.readTidlPropertiesFile(f);
			String pathToTidl = Util.getTidlFilePath(f, pathToJavaFile);
			if(pathToTidl != null && pathToJavaFile != null)
			{
				pathToJavaFile = new File(pathToTidl, pathToJavaFile).getAbsolutePath();
			}
			File tidlFile = f;
			File javaFile = new File(pathToJavaFile);
			ContextCppInterface ctx = converter.createContext(javaFile, tidlFile, od, beanUtilFileHeaderNames, service);
			return ctx;
		}

		String clazz = cppInterface.getClazz();
		String[] parts = clazz.split("::");
		clazz = parts[parts.length - 1];

		// check for a java file with the same name as the service interface
		// If a such java file is found, then no TIDL file is required to describe the service.
		f = new File(headerFullpath).getParentFile();
		f = new File(f, clazz + ".java");
		if(f.exists())
		{
			ContextCppInterface ctx = converter.createContext(f, null, od, beanUtilFileHeaderNames, service);
			remotableServicesContexts.add(ctx);
			return ctx;
		}


		String format = "No interface description file found for remote interface '%s'.\n"
				+ "A '%s.tidl.properties' or '%s.java' class must be defined";

		throw new ValidationException(String.format(format, headerFullpath, name, clazz));

	}

	@Override
	public boolean generate() throws TrengenException {

		Configuration config = configure();

		File outputDir = context.getOutputDir();
		if(!outputDir.exists())
		{
			outputDir.mkdirs();
		}
		
		if(generalProxiesWrappersContext.hasRemotableServices()) // server
		{
			if (!createIPCHelperUtilFiles(config, outputDir, remotableServicesContexts))
				return false;
			
			if (!createIPCBindingHelperFiles (config, outputDir, remotableServicesContexts ))
				return false;

		}
		if(!remotableReferences.isEmpty()) // client
		{
			if (!createIPCHelperUtilFiles(config, outputDir,remotableReferencesContexts))
				return false;

		}

		return true;
	}

	private boolean createIPCHelperUtilFiles(Configuration config, File outputDir, Set<ContextCppInterface> context) {
		Template templateIpcUtil = null;
		Template templateIpcBeanUtilHeader = null;
		Template templateIpcBeanUtilimpl = null;

		try
		{
			templateIpcUtil = config.getTemplate("BindingIPCUtils.ftl");
			templateIpcBeanUtilHeader = config.getTemplate("BindingIPCBeanUtils_h.ftl");
			templateIpcBeanUtilimpl = config.getTemplate("BindingIPCBeanUtils_cpp.ftl");
		} catch (IOException e)
		{
			logger.error("cannot create template.");
			return false;
		}

		File ipcUtilHeaderFile = new File(outputDir, "TrentinoGenIPCUtils.h");
		FileOutputStream fosIpcUtilHeader = null;
		
		File ipcBeanUtilHeaderFile = new File(outputDir, "TrentinoGenIPCBeanUtils.h");
		FileOutputStream fosIpcBeanUtilHeader = null;
		
		File ipcBeanUtilImlpFile = new File(outputDir, "TrentinoGenIPCBeanUtils.cpp");
		FileOutputStream fosIpcBeanUtilImpl = null;
		try
		{
			fosIpcUtilHeader = new FileOutputStream(ipcUtilHeaderFile);
			fosIpcBeanUtilHeader = new FileOutputStream(ipcBeanUtilHeaderFile);
			fosIpcBeanUtilImpl = new FileOutputStream(ipcBeanUtilImlpFile);
		} catch (FileNotFoundException e)
		{
			logger.error(ipcUtilHeaderFile + " could not be found.");
			return false;
		}
		
		/*
		 * includes
		 */
		Set<String> includes = new HashSet<String>();
		for (ContextCppInterface ref : context)
		{
			String includeStr = ref.getReferenceServiceInterface().getInterfaceHeader();
			String toBeIncluded = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), includeStr);
			if(toBeIncluded == null)
			{
				continue;
			}
			toBeIncluded = toBeIncluded.replace("\\", "/");
			includes.add(toBeIncluded);
		}


		Map<String, java.lang.Object> rootForIPCBinding = new HashMap<String, java.lang.Object>();

		rootForIPCBinding.put("remotableReferences", context);
		rootForIPCBinding.put("includes", includes);
		rootForIPCBinding.put("tmapper", new CppTypeMapper());
		doWrite(rootForIPCBinding, generalProxiesWrappersContext, templateIpcUtil, fosIpcUtilHeader);
		doWrite(rootForIPCBinding, generalProxiesWrappersContext, templateIpcBeanUtilHeader, fosIpcBeanUtilHeader);
		doWrite(rootForIPCBinding, generalProxiesWrappersContext, templateIpcBeanUtilimpl, fosIpcBeanUtilImpl);
		logger.info("IPC Utils are generated for remote references.");	   
		return true;
	}
	
	private boolean createIPCBindingHelperFiles(Configuration config, File outputDir, Set<ContextCppInterface> context) {
		Template templateIpcBindingHelperHeader = null;
		Template templateIpcBindingHelperImpl = null;

		try
		{
			templateIpcBindingHelperHeader = config.getTemplate("IPCBindingHelpers_h.ftl");
			templateIpcBindingHelperImpl = config.getTemplate("IPCBindingHelpers_cpp.ftl");
		} catch (IOException e)
		{
			logger.error("cannot create template.");
			return false;
		}

		File ipcBindingHelperHeaderFile = new File(outputDir, "TrentinoGenIPCBindingHelpers.h");
		File ipcBindingHelperImplFile = new File(outputDir, "TrentinoGenIPCBindingHelpers.cpp");
		FileOutputStream fosIpcBindingHelperHeader = null;
		FileOutputStream fosIpcBindingHelperImpl = null;
		try
		{
			fosIpcBindingHelperHeader = new FileOutputStream(ipcBindingHelperHeaderFile);
			fosIpcBindingHelperImpl = new FileOutputStream(ipcBindingHelperImplFile);
		} catch (FileNotFoundException e)
		{
			logger.error(ipcBindingHelperHeaderFile + " could not be found.");
			return false;
		}
		
		/*
		 * create ContextCPPInterfaces in context.......
		 */
		for (ContextCppInterface ctx : remotableServicesContexts)
		{
			((ContextIPCBinding) (this.context)).addContextProtoBuf(ctx);
		}

		for (ContextCppInterface ctx : remotableReferencesContexts)
		{
			((ContextIPCBinding) (this.context)).addContextProtoBuf(ctx);
		}

		Map<String, java.lang.Object> rootForIPCBinding = new HashMap<String, java.lang.Object>();

		rootForIPCBinding.put("remotableReferences", context);
		rootForIPCBinding.put("tmapper", new CppTypeMapper());
		rootForIPCBinding.put("context", this.context);
		String contributionName = generalProxiesWrappersContext.getContributionName();
		rootForIPCBinding.put("contributionName", contributionName);
		doWrite(rootForIPCBinding, generalProxiesWrappersContext, templateIpcBindingHelperHeader, fosIpcBindingHelperHeader);
		doWrite(rootForIPCBinding, generalProxiesWrappersContext, templateIpcBindingHelperImpl, fosIpcBindingHelperImpl);
		logger.info("IPC Binding helpers are generated for remote references.");	   
		return true;
	}
	
	@Override
	public BindingDescriptor getBindingDescriptor() {
		return bindingDescriptor;
	}
}
