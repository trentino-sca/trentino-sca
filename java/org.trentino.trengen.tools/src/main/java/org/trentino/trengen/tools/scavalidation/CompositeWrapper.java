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

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.xml.bind.JAXBElement;
import javax.xml.namespace.NamespaceContext;

import org.trentino.trengen.ValidationException;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentService;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.ComponentTypeReference;
import org.trentino.trengen.sca.model.Composite;
import org.trentino.trengen.sca.model.Implementation;
import org.trentino.trengen.sca.model.Property;
import org.trentino.trengen.sca.model.PropertyValue;
import org.trentino.trengen.sca.model.Reference;
import org.trentino.trengen.sca.model.Service;
import org.trentino.trengen.sca.model.Wire;

/**
 * This class is for wrapping the composite to be able to keep members that are
 * not part of the xsd model
 */
public class CompositeWrapper {
	public Map<String, ComponentReference>	   componentReferences	    = new HashMap<String, ComponentReference>();	 // this
	                                                                                                                     // map
	                                                                                                                     // keeps
	                                                                                                                     // component/reference_name
	// as key, component-level reference as value.
	public Map<String, ComponentTypeReference>	componentTypeReferences	= new HashMap<String, ComponentTypeReference>(); // this
	                                                                                                                     // map
	                                                                                                                     // keeps
	                                                                                                                     // component/reference_name
	// as key, componentType-level reference as value.
	private Map<String, ComponentService>	   componentServices	    = new HashMap<String, ComponentService>();	     // this
	                                                                                                                     // map
	                                                                                                                     // keeps
	                                                                                                                     // component/service_name
	                                                                                                                     // as
	                                                                                                                     // key,
	// this list keeps composite level references
	public ArrayList<Reference>	               compositeReferences	    = new ArrayList<Reference>();
	// this list keeps composite level services
	public ArrayList<Service>	               compositeServices	    = new ArrayList<Service>();	                 // this
	                                                                                                                     // list
	                                                                                                                     // keeps
	                                                                                                                     // composite
	// level services

	public ArrayList<Wire>	                   wires	                = new ArrayList<Wire>();	                     // this list keeps
	                                                                                                                     // wires in
	                                                                                                                     // the composite

	protected Composite	                       composite	            = null;
	private NamespaceContext	               namespaceContext	        = null;
	private String	                           compositeName	        = null;
	private boolean	                           xsdValidationStat	    = true;
	private String	                           compositeFileName	    = null;

	protected Set<ComponentWrapper>	       listComponentWrappers	= new HashSet<ComponentWrapper>();
	public CompositeWrapper	                   parent	                = null;
	private boolean	                           isCompositeByImpl	    = false;
	private List<CompositeReferenceWrapper>	   compositeReferenceWrappers;

	public boolean isCompositeByImpl() {
		return isCompositeByImpl;
	}

	public void setCompositeByImpl(boolean isCompositeByImpl) {
		this.isCompositeByImpl = isCompositeByImpl;
	}

	public Composite getComposite() {
		return composite;
	}

	public void setComposite(Composite composite) {
		this.composite = composite;

		String compositeName = composite.getName();
		setCompositeName(compositeName);

	}

	public Set<ComponentWrapper> getListComponents() {
		return listComponentWrappers;
	}

	
	public void setNamespaceContext(NamespaceContext namespaceContext) {
		this.namespaceContext = namespaceContext;
	}

	public NamespaceContext getNamespaceContext() {
		return namespaceContext;
	}

	public void setCompositeName(String compName) {
		compositeName = compName;
	}

	public String getCompositeName() {
		return compositeName;
	}

	public void setXSDValidationStat(boolean b) {
		xsdValidationStat = b;
	}

	public boolean getXSDValidationStat() {
		return xsdValidationStat;
	}

	public String getCompositeFileName() {
		return compositeFileName;
	}

	public void setCompositeFileName(String fileNameComposite) {
		compositeFileName = fileNameComposite;
	}

	
	public boolean putComponentService(String key, ComponentService value){
		if(value==null){
			return false;
		}
		ComponentService old = componentServices.get(key);
		if(old ==null){
			componentServices.put(key, value);
			return true;
		}
		return old == value;
	}
	/**
	 * create a list of all references used in this composite
	 * @return
	 */
	public List<CompositeReferenceWrapper> getCompositeReferenceWrappers() {
		if(compositeReferenceWrappers == null)
		{
			compositeReferenceWrappers = new ArrayList<CompositeReferenceWrapper>();
			for (Reference ref : compositeReferences)
			{
				CompositeReferenceWrapper wrapper = new CompositeReferenceWrapper(ref, this);
				wrapper.setCompositeReference(ref);
				compositeReferenceWrappers.add(wrapper);
				List<String> promotes = ref.getPromote();
				if(promotes.isEmpty())
				{
					continue;
				}
				for (String promote : promotes)
				{
					String separator = "/";
					int idex = promote.indexOf(separator);
					String compName = promote;
					String refName = null;
					if(idex > 0)
					{
						compName = promote.substring(0, idex);
						refName = promote.substring(idex + 1);
					}
					for (ComponentWrapper compWrapper : getListComponents())
					{
						Component comp = compWrapper.getScaModelComponent();
						if(!comp.getName().equals(compName))
						{
							continue;
						}
						// component found, now look for references
						if(compWrapper.getComponentReferences().isEmpty())
						{
							String msg = "Composite reference promote an unexisting component reference: composite: "+ getCompositeName()+". Component: "+compName+". Reference: " + refName+".";
							throw new IllegalStateException(msg);
						}
						if(refName == null)
						{
							// then it should be only one reference in the
							// Component
							if(compWrapper.getComponentReferences().size() > 1)
							{
								String msg = "In composite "+getCompositeName()+", reference "+refName+" promotes a reference from component "+compName+","
								        + " without giving the explicit name" + " of the component reference. Reference name should be provided if"
								        + " there are more that one references in the component ";
								throw new IllegalStateException(msg);
							}
							wrapper.getComponentReferences().addAll(compWrapper.getComponentReferences());

						}
						for (ComponentReferenceWrapper crWrapper : compWrapper.getComponentReferences())
						{
							if(refName.equals(crWrapper.getName()))
							{
								wrapper.getComponentReferences().add(crWrapper);
							}
						}
					}
				}
			}
		}
		return compositeReferenceWrappers;
	}

	/**
     * @return
     */
    public Map<String, ComponentService> getComponentServices() {
	    return componentServices;
    }

	/**
     * @param contributionVisitor
     */
    public void accept(ContributionVisitor contributionVisitor) {
	    contributionVisitor.visit(this);
	    Composite composite = this.getComposite();
	    acceptComposite(contributionVisitor, composite);
	    for (ComponentWrapper compWrapper : this.getListComponents())
	    {
	    	acceptComponentWrapper(contributionVisitor, compWrapper);
	    }
	    
    }
    
	private void acceptComposite(ContributionVisitor contributionVisitor, Composite composite) {
		if(composite == null)
		{
			return;
		}
		List<Object> objs = composite.getRequiresOrPolicySetAttachmentOrService();
		acceptListOfObjects(contributionVisitor, objs);
		contributionVisitor.visit(composite);
	}

	private void acceptComponentWrapper(ContributionVisitor contributionVisitor, ComponentWrapper compWrapper) {
		ComponentType scaModelComponentType = compWrapper.getScaModelComponentType();
		acceptComponentType(contributionVisitor, scaModelComponentType);

		acceptComponent(contributionVisitor, compWrapper.getScaModelComponent());
		for (ComponentReferenceWrapper contract : compWrapper.getComponentReferences())
		{
			contributionVisitor.visit(contract);
		}
		contributionVisitor.visit(compWrapper);
	}
	
	private void acceptComponentType(ContributionVisitor contributionVisitor, ComponentType scaModelComponentType) {
		if(scaModelComponentType == null)
		{
			return;
		}
		contributionVisitor.visit(scaModelComponentType);
		acceptListOfObjects(contributionVisitor, scaModelComponentType.getServiceOrReferenceOrProperty());
		acceptImplementation(contributionVisitor, scaModelComponentType.getImplementation());
	}
	

	/**
	 * @param contributionVisitor
	 * @param scaModelComponent
	 */
	private void acceptComponent(ContributionVisitor contributionVisitor, Component scaModelComponent) {
		if(scaModelComponent == null)
		{
			return;
		}
		contributionVisitor.visit(scaModelComponent);
		acceptListOfObjects(contributionVisitor, scaModelComponent.getServiceOrReferenceOrProperty());
		acceptImplementation(contributionVisitor, scaModelComponent.getImplementation());
	}


	/**
	 * @param contributionVisitor
	 * @param implementation
	 */
	private void acceptImplementation(ContributionVisitor contributionVisitor, JAXBElement<? extends Implementation> implementation) {
		if(implementation != null && !implementation.isNil())
		{
			contributionVisitor.visit(implementation.getValue());
		}

	}

	private void acceptListOfObjects(ContributionVisitor contributionVisitor, List<Object> objs) {
		for (Object obj : objs)
		{
			if(obj instanceof Service)
			{
				contributionVisitor.visit((Service) obj);
			}
			else if(obj instanceof Reference)
			{
				contributionVisitor.visit((Reference) obj);
			}
			else if(obj instanceof ComponentReference)
			{
				contributionVisitor.visit((ComponentReference) obj);
			}
			else if(obj instanceof ComponentTypeReference)
			{
				contributionVisitor.visit((ComponentTypeReference) obj);
			}
			else if(obj instanceof ComponentService)
			{
				contributionVisitor.visit((ComponentService) obj);
			}
			else if(obj instanceof Property)
			{
				contributionVisitor.visit((Property) obj);
			}
			else if(obj instanceof Component)
			{
				acceptComponent(contributionVisitor, (Component) obj);
			}
			else if(obj instanceof Wire)
			{
				contributionVisitor.visit((Wire) obj);
			}
			else if(obj instanceof PropertyValue)
			{
				contributionVisitor.visit((PropertyValue) obj);
			}
		}
	}
}
