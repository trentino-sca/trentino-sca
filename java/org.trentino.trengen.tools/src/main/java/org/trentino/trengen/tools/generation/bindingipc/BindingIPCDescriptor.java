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

import java.net.URI;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.List;

import javax.xml.bind.JAXBElement;
import javax.xml.namespace.QName;

import org.apache.log4j.Logger;
import org.trentino.trengen.sca.model.Binding;
import org.trentino.trengen.sca.model.CPPImplementation;
import org.trentino.trengen.sca.model.CPPImplementationScope;
import org.trentino.trengen.sca.model.CPPInterface;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentTypeReference;
import org.trentino.trengen.sca.model.Contract;
import org.trentino.trengen.sca.model.IPCBinding;
import org.trentino.trengen.sca.model.Interface;
import org.trentino.trengen.sca.model.ObjectFactory;
import org.trentino.trengen.sca.model.PropertyValue;
import org.trentino.trengen.tools.bindingframework.BindingDescriptor;
import org.trentino.trengen.tools.generation.proxieswrappers.ReferenceServiceInterface;
import org.trentino.trengen.tools.scavalidation.ComponentReferenceWrapper;
import org.trentino.trengen.tools.scavalidation.ContributionVisitor;
import org.trentino.trengen.tools.trengen.Trengen;

public class BindingIPCDescriptor implements BindingDescriptor {

	protected static final Logger	        logger	                      = Logger.getLogger(BindingIPCDescriptor.class);
	private static final String[]	BINGING_SCA_SCHEMES	=
	                                                    { "tcp" };

	private ObjectFactory	      factory	            = new ObjectFactory();

	/*
	 * (non-Javadoc)
	 * @see
	 * org.trentino.trengen.tools.bindingframework.BindingDescriptor#getBindingId
	 * ()
	 */
	@Override
	public String getBindingId() {
		return "binding.ipc";
	}

	public boolean isRemote(ComponentReferenceWrapper contract) {
		if(contract == null)
		{
			return false;
		}

		List<JAXBElement<? extends Binding>> bindings = contract.getBinding();
		if(isRemote(bindings,null))
		{
			return true;
		}
		List<String> targets = contract.getComponentReference().getTarget();
		return isRemoteTarget(targets,null);
	}
	
	public boolean isRemoteReference (ReferenceServiceInterface ref){
		Contract componentReference = ref.getContract();
		if(!(componentReference instanceof ComponentReference)){
			return false;
		}
		
			ComponentReferenceWrapper wrapper = getCompRefWrapperByCompRef(componentReference);

			List<JAXBElement<? extends Binding>> bindings = wrapper.getBinding();
			if(isRemote(bindings, ref))
			{
				return true;
			}
			List<String> targets = wrapper.getComponentReference().getTarget();
			return isRemoteTarget(targets, ref);
		
	}
	
	/**
	 * @param componentReference
	 * @return
	 */
	private ComponentReferenceWrapper getCompRefWrapperByCompRef(final Contract componentReference) {
		final ComponentReferenceWrapper[] res = new ComponentReferenceWrapper[1];
		ContributionVisitor contributionVisitor = new ContributionVisitor() {
			public void visit(ComponentReferenceWrapper contract) {
				if(contract.getComponentReference().equals(componentReference))
				{
					res[0] = contract;
				}
			}
		};
		Trengen.getContributionTypeWrapper().accept(contributionVisitor);
		return res[0];
	}

	/*
	 * (non-Javadoc)
	 * @see org.trentino.trengen.tools.bindingframework.BindingDescriptor#
	 * getComponentsByReference
	 * (org.trentino.trengen.tools.scavalidation.CompositeReferenceWrapper)
	 */
	@Override
	public List<Component> getComponentsByReference(ComponentReferenceWrapper ref) {
		List<Component> res = new ArrayList<Component>();
		if(!isRemote(ref))
		{
			return res;
		}
		// for each target attribute, a component is created.
		createComponentsFromTargets(res, ref);
		if(res.size() == 0)
		{
			createComponentsFromBindings(res, ref);
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 * @see
	 * org.trentino.trengen.tools.bindingframework.BindingDescriptor#isRemote
	 * (org.trentino.trengen.sca.model.Reference)
	 */
	@Override
	public boolean isRemote(ComponentTypeReference contract) {
		List<JAXBElement<? extends Binding>> bindings = contract.getBinding();
		if(isRemote(bindings,null))
		{
			return true;
		}
		List<String> targets = contract.getTarget();
		return isRemoteTarget(targets,null);
	}

	/**
	 * @param bindings
	 * @return true if the following list of bindings define an SCA binding
	 */
	private boolean isRemote(List<JAXBElement<? extends Binding>> bindings, ReferenceServiceInterface ref) {
		for (JAXBElement<? extends Binding> b : bindings)
		{
			if(b == null || b.isNil())
			{
				continue;
			}
			Binding val = b.getValue();
			if(val instanceof IPCBinding)
			{
				return true;
			}
		}
		return false;
	}

	private boolean isRemoteTarget(List<String> targets,ReferenceServiceInterface ref) {
		if(targets.size() == 0)
		{
			return false;
		}
		for (String target : targets)
		{
			boolean remote = isRemote(target,ref);
			if(remote)
			{
				return true;
			}
		}
		return false;
	}

	private boolean isRemote(String target, ReferenceServiceInterface ref) {
		try
		{
			URI uri = new URI(target);
			String scheme = uri.getScheme();
			for (String aScheme : BINGING_SCA_SCHEMES)
			{
				if(aScheme.equals(scheme))
				{
					if(ref!=null){
						fillPortAndURL(ref, target);
					}
					return true;
				}
			}
		} catch (URISyntaxException e)
		{
			return false;
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
	
	/**
	 * gets the name of the Implementation class.
	 * @param ref
	 * @return
	 */
	private String getImplClassByRef(ComponentReferenceWrapper ref) {
		JAXBElement<? extends Interface> itfElem = ref.getInterface();
		CPPInterface itf = (CPPInterface) itfElem.getValue();
		String clazz = itf.getClazz();
		clazz = clazz.replaceAll("::", "_");
		return clazz + "BindingProxy";
	}

	/**
	 * @param res
	 * @param ref
	 */
	private void createComponentsFromBindings(List<Component> res, ComponentReferenceWrapper ref) {
		List<JAXBElement<? extends Binding>> bindings = ref.getBinding();
		List<String> targets = new ArrayList<String>();
		for (JAXBElement<? extends Binding> b : bindings)
		{
			if(b == null || b.isNil())
			{
				continue;
			}
			Binding val = b.getValue();
			if(val instanceof IPCBinding)
			{
				String uri = val.getUri();
				if(uri == null)
				{
					throw new IllegalStateException("binding ipc has no uri defined");
				}
				targets.add(uri);
			}
		}
		createComponentsFromURIList(res, ref, targets);

	}

	/**
	 * @param res
	 * @param ref
	 */
	private void createComponentsFromTargets(List<Component> res, ComponentReferenceWrapper ref) {
		List<String> targets = ref.getComponentReference().getTarget();
		createComponentsFromURIList(res, ref, targets);

	}

	private void createComponentsFromURIList(List<Component> res, ComponentReferenceWrapper ref, List<String> targets) {
		// Only one component implementation needed
		CPPImplementation impl = new CPPImplementation();
		impl.setHeader("TrentinoGenBindingProxy.h");
		String clazz = getImplClassByRef(ref);
		impl.setClazz(clazz);
		impl.setAllowsPassByReference(false);
		impl.setLibrary("sca-contribution");
		impl.setEagerInit(false);
		impl.setPath("./META-INF");
		impl.setScope(CPPImplementationScope.COMPOSITE);
		for (String target : targets)
		{
			if(!isRemote(target,null))
			{
				continue;
			}
			Component comp = new Component();
			comp.setImplementation(factory.createImplementationCpp(impl));
			// create the address property
			PropertyValue prop = new PropertyValue();
			prop.setMany(false);
			prop.setType(new QName("string"));
			prop.setName(BindingDescriptor.TRENTINO_INTERNAL_ADRESS_PROPERTY_DO_NOT_USE_THIS_NAME);
			prop.setValue(target);
			comp.getServiceOrReferenceOrProperty().add(prop);
			res.add(comp);
		}
	}

}
