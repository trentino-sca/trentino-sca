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
package org.trentino.trengen.tools.bindingframework;

import java.util.ArrayList;
import java.util.List;
import java.util.ServiceLoader;

import javax.xml.bind.JAXBElement;

import org.apache.log4j.Logger;
import org.trentino.trengen.sca.model.Binding;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentTypeReference;
import org.trentino.trengen.tools.scavalidation.ComponentReferenceWrapper;

/**
 * @author z002ttbb
 */
public class BindingManager {

	private static final String	  BINDING_SCA	= "binding.sca";
	private static final String	  BINDING_IPC	= "binding.ipc";
	protected static final Logger	logger	  = Logger.getLogger(BindingManager.class);

	/**
	 * @param contract
	 * @return
	 */
	public boolean isRemotable(ComponentReferenceWrapper contract) 
	{
		ServiceLoader<BindingCodeGenerator> generators = ServiceLoader.load(BindingCodeGenerator.class);
		
		for (BindingCodeGenerator generator : generators)
		{
			BindingDescriptor desc = generator.getBindingDescriptor();
			return desc.isRemote(contract);

		}
		return false;
		//BindingDescriptor defaultDescriptor = getDefaultBindingDescriptor();
		//return defaultDescriptor.isRemote(contract);
	}
	
	// obsolete not used any more: contract should be checked for remotability agains all available generators
	private BindingDescriptor getDefaultBindingDescriptor() {
		ServiceLoader<BindingCodeGenerator> generators = ServiceLoader.load(BindingCodeGenerator.class);
		
		for (BindingCodeGenerator generator : generators)
		{
			BindingDescriptor desc = generator.getBindingDescriptor();
			
			String nedir = generator.getBindingDescriptor().getBindingId();
			if(BINDING_SCA.equals(desc.getBindingId()) || BINDING_IPC.equals(desc.getBindingId()))
			{
				return desc;
			}
		}
		throw new IllegalStateException("default binding not found");
	}

	/**
	 * @param contract
	 * @return
	 */
	public boolean isRemotable(ComponentTypeReference contract) 
	{
		ServiceLoader<BindingCodeGenerator> generators = ServiceLoader.load(BindingCodeGenerator.class);
		
		for (BindingCodeGenerator generator : generators)
		{
			BindingDescriptor desc = generator.getBindingDescriptor();
			return desc.isRemote(contract);

		}
		return false;
		
		//BindingDescriptor defaultDescriptor = getDefaultBindingDescriptor();
		//return defaultDescriptor.isRemote(contract);
	}

	/**
	 * @param ref
	 * @return
	 */
	public List<Component> getComponentsByReference(ComponentReferenceWrapper ref) {
		List<Component> comps = new ArrayList<Component>();
		ServiceLoader<BindingCodeGenerator> generators = ServiceLoader.load(BindingCodeGenerator.class);
		for (BindingCodeGenerator generator : generators)
		{
			BindingDescriptor desc = generator.getBindingDescriptor();
			comps.addAll(desc.getComponentsByReference(ref));
		}
		return comps;
	}

}
