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
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.URI;
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
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.Contract;
import org.trentino.trengen.sca.model.SCABinding;
import org.trentino.trengen.tools.bindingframework.BindingCodeGenerator;
import org.trentino.trengen.tools.bindingframework.BindingCodeGeneratorData;
import org.trentino.trengen.tools.bindingframework.BindingDescriptor;
import org.trentino.trengen.tools.bindingsca.TIDL2Protobuf;
import org.trentino.trengen.tools.bindingsca.TIDLParseException;
import org.trentino.trengen.tools.generation.TrengenGenerator;
import org.trentino.trengen.tools.generation.cmake.ContextCmake;
import org.trentino.trengen.tools.generation.modelloader.SCAModelToSCAMirrorModelConverter;
import org.trentino.trengen.tools.generation.proxieswrappers.ContextProxiesWrappers;
import org.trentino.trengen.tools.generation.proxieswrappers.ReferenceServiceInterface;
import org.trentino.trengen.tools.protobuf.CppFileGenerationWithProtoc;
import org.trentino.trengen.tools.scavalidation.DirectoryScanner;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.tools.trengen.Util;

import freemarker.template.Configuration;
import freemarker.template.Template;

/**
 * @author z002ttbb
 */
public class BindingSCACodeGenerator extends TrengenGenerator implements BindingCodeGenerator {

	protected static final Logger	        logger	                      = Logger.getLogger(BindingSCACodeGenerator.class);
	private List<String>	                beanUtilFileHeaderNames	      = new ArrayList<String>();
	private ContextProxiesWrappers	        generalProxiesWrappersContext	= null;
	private BindingSCADescriptor	        bindingDescriptor	          = new BindingSCADescriptor();
	TIDL2Protobuf	                        converter	                  = new TIDL2Protobuf();
	private List<ReferenceServiceInterface>	remotableReferences;
	private BindingCodeGeneratorData	    data;
	List<ReferenceServiceInterface>	        remotableServices;
	List<ContextCppInterface>	            remotableServicesContexts;
	Set<ContextCppInterface>	            remotableRefenencesContexts;

	/**
	 * @param context
	 */
	public BindingSCACodeGenerator () {
		super(null);
	}

	/*
	 * (non-Javadoc)
	 * @see
	 * org.trentino.trengen.tools.bindingframework.BindingCodeGenerator#generate
	 * (org.trentino.trengen.tools.scavalidation.ContributionTypeWrapper,
	 * org.trentino
	 * .trengen.tools.generation.modelloader.SCAModelToSCAMirrorModelConverter,
	 * java.io.File, java.lang.String)
	 */
	@Override
	public boolean generate(BindingCodeGeneratorData data) throws TrengenException {
		this.data = data;
		generalProxiesWrappersContext = data.getContextProxyWrapper();
		remotableServices = new ArrayList<ReferenceServiceInterface>();
		remotableServicesContexts = new ArrayList<ContextCppInterface>();

		remotableReferences = new ArrayList<ReferenceServiceInterface>();
		remotableRefenencesContexts = new TreeSet<ContextCppInterface>();

		getRemotableServices();
		getRemotableReferences();

		if(remotableReferences.isEmpty() && remotableServices.isEmpty())
		{
			return true;
		}

		fillPortAndURLs();

		File generationDirectory = data.getGenerationDirectory();
		prepareContextCMake(data);

		this.context = new ContextSCABinding(generalProxiesWrappersContext.getContributionName());

		this.context.setOutputDir(generationDirectory);

		if(!remotableServices.isEmpty())
		{
			generalProxiesWrappersContext.getDeclaredBindings().add("binding.sca");
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

		// First the proto files are created since they will be referred from
		// the sca binding helpers then
		if(!generateProtoFiles())
		{
			return false;
		}
		this.data = data;

		// register the binding helper to Contribution
		if(generalProxiesWrappersContext.hasRemotableServices())
		{
			for (ContextCppInterface ctx : ((ContextSCABinding) context).getProtoBufContexts())
			{
				generalProxiesWrappersContext.registerBindingHelper(ctx);
			}
		}
		if(!generate())
		{
			return false;
		}

		CppFileGenerationWithProtoc cppFileGenerationWithProtoc = new CppFileGenerationWithProtoc();
		if(!cppFileGenerationWithProtoc.generateProtocFiles())
		{
			return false;
		}

		return true;
	}

	/**
     * 
     */
	private void fillPortAndURLs() {
		for (ReferenceServiceInterface obj : remotableReferences)
		{
			boolean filled = false;
			Contract contract = obj.getContract();
			for (JAXBElement<? extends Binding> binding : contract.getBinding())
			{
				filled |= fillTheBindingRelatedStuff(binding.getValue(), obj);
			}
			if(!filled)
			{
				if(contract instanceof ComponentReference)
				{

					List<String> uri2 = ((ComponentReference) contract).getTarget();
				}

			}
		}

	}

	private boolean fillTheBindingRelatedStuff(Binding binding, ReferenceServiceInterface refServiceInterface) {
		if(binding instanceof SCABinding)
		{
			SCABinding scaBinding = (SCABinding) binding;

			String uri2 = scaBinding.getUri();
			fillPortAndURL(refServiceInterface, uri2);
			return true;
		}
		return false;
	}

	private void fillPortAndURL(ReferenceServiceInterface refServiceInterface, String uri2) {
		URI uri = URI.create(uri2);
		String host = uri.getHost();
		int port = uri.getPort();

		refServiceInterface.setPort(port);
		refServiceInterface.setHost(host);
	}

	private void prepareContextCMake(BindingCodeGeneratorData data) {
		ContextCmake contextCmake = data.getContextCMake();

    	// binding specific link directories

		// binding specific libraries

		contextCmake.getLibraries().add("TrentinoBindingSCA");
		contextCmake.getLibraries().add("TrentinoBindingSCAClient");
		contextCmake.getLibraries().add("TrentinoBindingCompactSoap");
	}

	/**
	 * @param contextProxiesWrappers
	 * @param data2
	 */
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
			List<JAXBElement<? extends Binding>> binding = contract.getBinding();
			if(binding == null || binding.isEmpty())
			{
				remotableServices.add(service);
				continue;
			}
			for (JAXBElement<? extends Binding> x : binding)
			{
				if(x.isNil())
				{
					continue;
				}
				Binding b = x.getValue();
				if(b instanceof SCABinding)
				{
					remotableServices.add(service);
				}
			}
		}

	}


	/**
	 * @param contextProxiesWrappers
	 * @param data
	 * @return
	 */
	private void getRemotableReferences() {
		SCAModelToSCAMirrorModelConverter converter = data.getConverter();
		for (ReferenceServiceInterface ref : converter.getReferenceInterfaces())
		{
			boolean isRem = bindingDescriptor.isRemoteReference(ref);
			if(isRem)
			{
				remotableReferences.add(ref);
			}
		}
	}

	/**
	 * validate model before binding code generation.
	 * @throws TIDLParseException
	 */
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

	/**
	 * @throws TIDLParseException
	 */
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

	/**
	 * Validate that port and host are available for remotable references.
	 * @throws TIDLParseException
	 */
	private boolean validateThatPortAndHostAreAvailableForRemotableReferences() throws TIDLParseException {
		File od = new File(Trengen.getOutDir());
		for (ReferenceServiceInterface referenceServiceInterface : remotableReferences)
		{
			// if not specified, it returns -1.
			Integer port = referenceServiceInterface.getPortInt();
			if(port <= 0)
			{
				logger.error("Port value is undefined or invalid for reference " + referenceServiceInterface.getInterfaceClassName());
				return false;
			}

			if(referenceServiceInterface.getHost() == null)
			{
				logger.error("Host value is undefined or invalid for reference " + referenceServiceInterface.getInterfaceClassName());
				return false;
			}

			Contract contract = referenceServiceInterface.getContract();
			if(contract == null)
			{
				throw new IllegalArgumentException("contract is null in a ReferenceServiceInterface");
			}

			CPPInterface cppInterface = referenceServiceInterface.getCppInterface();
			ContextCppInterface ctx = createInterfaceContext(cppInterface, od, referenceServiceInterface);
			remotableRefenencesContexts.add(ctx);
		}
		return true;
	}

	public boolean generateProtoFiles() {

		logger.info("CPPInterface file is being generated... ");
		for (ContextCppInterface ctx : remotableServicesContexts)
		{
			converter.generate(ctx);
			generalProxiesWrappersContext.addCppInterfaceFile(ctx.getFileName() + ".h");
			((ContextSCABinding) (this.context)).addContextProtoBuf(ctx);
		}

		for (ContextCppInterface ctx : remotableRefenencesContexts)
		{
			converter.generate(ctx);
			generalProxiesWrappersContext.addCppInterfaceFile(ctx.getFileName() + ".h");
			((ContextSCABinding) (this.context)).addContextProtoBuf(ctx);
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

	/*
	 * (non-Javadoc)
	 * @see org.trentino.trengen.tools.generation.TrengenGenerator#generate()
	 */
	@Override
	public boolean generate() throws TrengenException {

		logger.info("TrentinoGenSCABindingHelpers.h and " + "TrentinoGenSCABindingHelpers.cpp are being generated...");
		Configuration config = configure();
		Template templateBindingHelperCpp = null;
		Template templateBindingHelperHeader = null;

		Template templateBindingProxyCpp = null;
		Template templateBindingProxyHeader = null;

		try
		{
			templateBindingHelperCpp = config.getTemplate("SCABindingHelpers.cpp.ftl");
			templateBindingHelperHeader = config.getTemplate("SCABindingHelpers.h.ftl");

			templateBindingProxyCpp = config.getTemplate("BindingProxy_cpp.ftl");
			templateBindingProxyHeader = config.getTemplate("BindingProxy_h.ftl");
		} catch (IOException e)
		{
			throw new IllegalStateException("cannot create template");
		}
		File outputDir = context.getOutputDir();
		if(!outputDir.exists())
		{
			outputDir.mkdirs();
		}
		String contributionName = ((ContextSCABinding) context).getContributionName();
		FileOutputStream fosBindingHelperCpp;
		FileOutputStream fosBindingHelperHeader;

		FileOutputStream fosBindingProxyCpp;
		FileOutputStream fosBindingProxyHeader;
		try
		{
			if(generalProxiesWrappersContext.hasRemotableServices())
			{
				fosBindingHelperCpp = new FileOutputStream(new File(outputDir, "TrentinoGenSCABindingHelpers.cpp"));
				fosBindingHelperHeader = new FileOutputStream(new File(outputDir, "TrentinoGenSCABindingHelpers.h"));

				Map<String, java.lang.Object> root = new HashMap<String, java.lang.Object>();
				root.put("beanHeaders", beanUtilFileHeaderNames);
				root.put("context", this.context);
				root.put("tmapper", new CppTypeMapper());
				root.put("contributionName", contributionName);
				doWrite(root, context, templateBindingHelperCpp, fosBindingHelperCpp);
				doWrite(root, context, templateBindingHelperHeader, fosBindingHelperHeader);
				logger.info("Binding helpers are generated for remote services.");
			}
			if(!remotableReferences.isEmpty())
			{
				File bindingProxyHeaderFile = new File(outputDir, "TrentinoGenBindingProxy.h");
				this.data.getContextReflection().getReflexIncludes().add(bindingProxyHeaderFile.getName());
				fosBindingProxyHeader = new FileOutputStream(bindingProxyHeaderFile);
				fosBindingProxyCpp = new FileOutputStream(new File(outputDir, "TrentinoGenBindingProxy.cpp"));

				Map<String, java.lang.Object> rootForBindingProxy = new HashMap<String, java.lang.Object>();
				rootForBindingProxy.put("context", generalProxiesWrappersContext);
				rootForBindingProxy.put("remotableReferences", remotableRefenencesContexts);
				rootForBindingProxy.put("contextBiningSCA", context);
				rootForBindingProxy.put("hasBeanUtil", hasBeanUtil((ContextSCABinding) context));
				TIDLContextFunctionInterfaceFunctionMapper functionMapper = new TIDLContextFunctionInterfaceFunctionMapper(
				        ((ContextSCABinding) (this.context)).getProtoBufContexts());
				rootForBindingProxy.put("functionMapper", functionMapper);
				doWrite(rootForBindingProxy, generalProxiesWrappersContext, templateBindingProxyHeader, fosBindingProxyHeader);
				doWrite(rootForBindingProxy, generalProxiesWrappersContext, templateBindingProxyCpp, fosBindingProxyCpp);
				logger.info("Binding proxies are generated for remote references.");
			}
		} catch (FileNotFoundException e)
		{
			throw new TrengenException(e);
		}

		return true;
	}

	/**
	 * @param context
	 * @return
	 */
	private Boolean hasBeanUtil(ContextSCABinding context) {
		for (ContextCppInterface cp : context.getProtoBufContexts())
		{
			if(cp.hasBeanUtils())
			{
				return true;
			}
		}

		return false;
	}

	/*
	 * (non-Javadoc)
	 * @see org.trentino.trengen.tools.bindingframework.BindingCodeGenerator#
	 * getBindingDescriptor()
	 */
	@Override
	public BindingDescriptor getBindingDescriptor() {
		return bindingDescriptor;
	}

}
