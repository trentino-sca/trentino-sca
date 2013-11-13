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
package org.trentino.trengen.tools.generation.thrift;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

import javax.xml.bind.JAXBElement;

import org.apache.log4j.Logger;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.sca.model.Binding;
import org.trentino.trengen.sca.model.Contract;
import org.trentino.trengen.sca.model.ThriftBinding;

import org.trentino.trengen.tools.bindingframework.BindingCodeGenerator;
import org.trentino.trengen.tools.bindingframework.BindingCodeGeneratorData;
import org.trentino.trengen.tools.bindingframework.BindingDescriptor;
import org.trentino.trengen.tools.generation.TrengenGenerator;
import org.trentino.trengen.tools.generation.modelloader.SCAModelToSCAMirrorModelConverter;
import org.trentino.trengen.tools.generation.proxieswrappers.ContextProxiesWrappers;
import org.trentino.trengen.tools.generation.proxieswrappers.ReferenceServiceInterface;

public class CodeGenerator extends TrengenGenerator implements BindingCodeGenerator {

	protected static final Logger	        logger	                      = Logger.getLogger(CodeGenerator.class);
	
	private ContextProxiesWrappers	        generalProxiesWrappersContext	= null;
	private Descriptor	        bindingDescriptor	          = new Descriptor();

	private List<ReferenceServiceInterface>	remotableReferences;
	private BindingCodeGeneratorData	    data;
	List<ReferenceServiceInterface>	        remotableServices;


	public CodeGenerator () {
		super(null);
	}

	@Override
	public boolean generate(BindingCodeGeneratorData data) throws TrengenException {
		this.data = data;
		generalProxiesWrappersContext = data.getContextProxyWrapper();
		remotableServices = new ArrayList<ReferenceServiceInterface>();
		remotableReferences = new ArrayList<ReferenceServiceInterface>();
		getRemotableServices();
		getRemotableReferences();

		if(remotableReferences.isEmpty() && remotableServices.isEmpty())
		{
			return true;
		}

		
		return true;

		
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
			boolean hasThriftbinding = false;
			List<JAXBElement<? extends Binding>> bindings = contract.getBinding();
			for (JAXBElement<? extends Binding> binding : bindings)
			{
				Binding b = binding.getValue();
				if (b instanceof ThriftBinding)
				{	
					hasThriftbinding=true;
					break;
				}
			}
			if (hasThriftbinding)
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
				if(b instanceof ThriftBinding && isRem)
				{
					remotableReferences.add(ref);
				}
			}
		}
	}

	@Override
	public BindingDescriptor getBindingDescriptor() {
		return bindingDescriptor;
	}

	@Override
	public boolean generate() throws TrengenException {
		// TODO Auto-generated method stub
		return false;
	}
}
