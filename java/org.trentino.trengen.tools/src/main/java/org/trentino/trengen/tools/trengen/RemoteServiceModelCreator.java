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
// Lesser General setre License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
// **********************************************************************************
package org.trentino.trengen.tools.trengen;

import java.io.File;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import javax.xml.bind.JAXBElement;
import javax.xml.namespace.QName;

import org.apache.log4j.Logger;
import org.trentino.trengen.sca.model.CPPInterface;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentService;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.ComponentTypeReference;
import org.trentino.trengen.sca.model.Composite;
import org.trentino.trengen.sca.model.Interface;
import org.trentino.trengen.sca.model.ObjectFactory;
import org.trentino.trengen.sca.model.Property;
import org.trentino.trengen.sca.model.Wire;
import org.trentino.trengen.tools.bindingframework.BindingDescriptor;
import org.trentino.trengen.tools.bindingframework.BindingManager;
import org.trentino.trengen.tools.scavalidation.ComponentReferenceWrapper;
import org.trentino.trengen.tools.scavalidation.ComponentWrapper;
import org.trentino.trengen.tools.scavalidation.CompositeWrapper;
import org.trentino.trengen.tools.scavalidation.ContributionTypeWrapper;
import org.trentino.trengen.tools.scavalidation.ContributionVisitor;
import org.trentino.trengen.tools.scavalidation.DirectoryScanner;

/**
 * @author z002ttbb
 */
public class RemoteServiceModelCreator {

	protected static final Logger	        logger	                         = Logger.getLogger(RemoteServiceModelCreator.class);
	private static final String	            _REMOTE_COMPONENT_NAME_SEPARATOR	= "_REMOTE_COMPONENT_NAME_SEPARATOR_";

	// List<CompositeReferenceWrapper> remotableReferences = new
	// ArrayList<CompositeReferenceWrapper>();
	// used to check later if the refernces have been promoted as composite
	// level
	private List<ComponentReferenceWrapper>	remotableComponentReferences	 = new ArrayList<ComponentReferenceWrapper>();
	private List<ComponentTypeReference>	remotableComponentTypeReferences	= new ArrayList<ComponentTypeReference>();

	BindingManager	                        bindingManager	                 = new BindingManager();

	Set<EqualsBox>	                        interfaces	                     = new HashSet<EqualsBox>();
	
	int fakeComponentCounter = 0;

	/**
	 * @param contributionTypeWrapper
	 */
	public void createRemoteServices(ContributionTypeWrapper contributionTypeWrapper) {
		// get all rreferences to remote services
		contributionTypeWrapper.accept(referenceVisitor);
		validateReferences();
		if(!hasRemoteServices())
		{
			return;
		}

		// we have references to remote services, therefore we create a fake
		// composite
		// that will hosts all remote services
		// create fake composite if remotablke services was found
		// fakeCompositeWrapper = new CompositeWrapper();
		// configureFakeCompositeWrapper(contributionTypeWrapper);

		// now we create component types for each interface defined
		createComponentTypes();

		// now we create components
		createComponents();
		// best place is to add the wire adding the fakecomponent
		// wireRemoteReferencesToFakeServices();
	}

	/**
	 * validate that all componenttype references are linked to components
	 * references, and that the component references are promoted at composite
	 * level
	 */
	private void validateReferences() {

		for (ComponentTypeReference ctRef : remotableComponentTypeReferences)
		{
			boolean valid = false;
			String ctRefName = ctRef.getName();
			for (ComponentReferenceWrapper cRefWr : remotableComponentReferences)
			{
				ComponentReference cRef = cRefWr.getComponentReference();
				String cRefName = cRef.getName();
				if(cRefName.equals(ctRefName))
				{
					valid = true;
				}
			}
			if(!valid)
			{
				String format = "Binding code will not be generated for component type reference "+ctRef.getName()+".\nReason: The component type reference is not declared at component level.\n"
				        + "Trentino assumes that a references to a remote services is allways declared in the component, even if allready declared in the component type.\n"
				        + "HOW TO FIX?: configure the reference "+ctRef.getName()+" in all components using the affected component type.";
				logger.warn(format);
			}
		}

	}

	/**
	 * Wire the remote references to th fake components
	 * @param composite
	 */
	private void wireRemoteReferencesToFakeServices(String source, String target, Composite composite) {
		Wire wireBwRemoteRefAndFakeService = new Wire();
		wireBwRemoteRefAndFakeService.setSource(source);
		wireBwRemoteRefAndFakeService.setTarget(target);
		composite.getRequiresOrPolicySetAttachmentOrService().add(wireBwRemoteRefAndFakeService);
	}

	private void createComponents() {
		for (ComponentReferenceWrapper ref : remotableComponentReferences)
		{
			List<Component> comps = bindingManager.getComponentsByReference(ref);
			
			for (Component comp : comps)
			{
				ComponentWrapper sourceComponentWrapper = ref.getComponent();
				CompositeWrapper compositeWrapper = sourceComponentWrapper.getParentCompositeWrapper();
				String compositeName = compositeWrapper.getCompositeName();
				String fakeComponentName = "N" + compositeName + "_" + System.currentTimeMillis() + "_" + _REMOTE_COMPONENT_NAME_SEPARATOR
				        + ref.getName() + "_" + fakeComponentCounter++;
				comp.setName(fakeComponentName);

				ComponentWrapper targetComponentWrapper = new ComponentWrapper();
				targetComponentWrapper.setParentCompositeWrapper(compositeWrapper);
				targetComponentWrapper.setScaModelComponent(comp);
				ComponentType componentType = getComponentType(ref);
				targetComponentWrapper.setScaModelComponentType(componentType);
				compositeWrapper.getListComponents().add(targetComponentWrapper);
				Composite composite = compositeWrapper.getComposite();

				// add component to this composite
				compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().add(comp);

				// reuse the component type service in the component
				ComponentService componentTypeService = targetComponentWrapper.getComponentTypeService();
				componentTypeService.setRemote(true); //muge
				componentTypeService.getInterface().getValue().setRemotable(false); //muge
				// add service to generated component
				comp.getServiceOrReferenceOrProperty().add(componentTypeService);
				compositeWrapper.putComponentService(componentTypeService.getName(), componentTypeService);
				// add the componentService to the wrapper, so that wrapper code
				// is generated

				String sourceRefName = ref.getComponentReference().getName();
				String sourceCompName = sourceComponentWrapper.getScaModelComponent().getName();
				String source = sourceCompName + "/" + sourceRefName;
				String target = fakeComponentName + "/" + componentTypeService.getName();
				wireRemoteReferencesToFakeServices(source, target, composite);
			}

		}

	}

	/**
	 * get a fake component type created for this real reference
	 * @param ref
	 * @return
	 */
	private ComponentType getComponentType(ComponentReferenceWrapper ref) {
		for (EqualsBox box : interfaces)
		{
			if(box.equals(ref.getInterface().getValue()))
			{
				return box.compType;
			}
		}
		throw new IllegalStateException("Could not retrieve fake component type for reference " + ref.getName());
	}

	/**
	 * create a component type for each different remote reference
	 */
	private void createComponentTypes() {
		createInterfacesSet(interfaces);
		// now iterate over the set of interfaces to create component types
		for (EqualsBox itfbox : interfaces)
		{
			CPPInterface itf = itfbox.anInterface;

			// create the service
			ComponentService service = new ComponentService();
			// this service represent a remote service
			service.setRemote(true);
			service.setName(getServiceName(itf));
			ObjectFactory factory = new ObjectFactory();
			// muge begin
			JAXBElement<CPPInterface> interfaceOfFakeService = factory.createInterfaceCpp(itf); 
			interfaceOfFakeService.getValue().setRemotable(false);
			// muge end
			service.setInterface(factory.createInterfaceCpp(itf));

			// create the address property
			Property prop = new Property();
			prop.setName(BindingDescriptor.TRENTINO_INTERNAL_ADRESS_PROPERTY_DO_NOT_USE_THIS_NAME);
			prop.setMany(false);
			prop.setType(new QName("string"));
			prop.setMustSupply(false);
			// prop.getContent().add("");

			ComponentType compType = new ComponentType();
			compType.getServiceOrReferenceOrProperty().add(service);
			compType.getServiceOrReferenceOrProperty().add(prop);
			itfbox.compType = compType;
		}
	}

	/**
	 * @param itf
	 * @return the name of the service
	 */
	private String getServiceName(CPPInterface itf) {
		String clazz = itf.getClazz();
		int index = clazz.lastIndexOf("::");
		if(index < 0)
		{
			return clazz;
		}
		return clazz.substring(index + 2);
	}

	private void createInterfacesSet(Set<EqualsBox> interfaces) {
		for (ComponentReferenceWrapper ref : remotableComponentReferences)
		{
			JAXBElement<? extends Interface> itfElem = ref.getInterface();
			addInterface(interfaces, itfElem);
		}
	}

	private void addInterface(Set<EqualsBox> interfaces, JAXBElement<? extends Interface> itfElem) {
		if(itfElem == null || itfElem.isNil())
		{
			return;
		}
		Interface value = itfElem.getValue();
		if(!(value instanceof CPPInterface))
		{
			return;
		}
		interfaces.add(new EqualsBox((CPPInterface) value));
	}

	private boolean hasRemoteServices() {
		return remotableComponentReferences.size() > 0;
	}

	private ContributionVisitor	referenceVisitor	= new ContributionVisitor() {
		                                             public void visit(ComponentReference contract) {
			                                             if(contract instanceof ComponentTypeReference)
			                                             {
				                                             if(isRemotable((ComponentTypeReference) contract))
				                                             {
					                                             remotableComponentTypeReferences.add((ComponentTypeReference) contract);
				                                             }
			                                             }

		                                             }

		                                             public void visit(ComponentReferenceWrapper contract) {
			                                             if(isRemotable(contract))
			                                             {
				                                             remotableComponentReferences.add(contract);
			                                             }
		                                             }
	                                             };

	/**
	 * @param crwrapper
	 * @return
	 */
	private boolean isRemotable(ComponentReferenceWrapper contract) {
		return bindingManager.isRemotable(contract);
	}

	private boolean isRemotable(ComponentTypeReference contract) {
		return bindingManager.isRemotable(contract);
	};

	/**
	 * @author z002ttbb
	 */
	private class EqualsBox {
		public ComponentType	compType;
		private CPPInterface	anInterface;

		public EqualsBox (CPPInterface anInterface) {
			this.anInterface = anInterface;
		}

		public boolean equals(Object o) {
			if(anInterface == null)
			{
				return false;
			}
			if(o == null)
			{
				return false;
			}
			if(!(o instanceof CPPInterface))
			{
				return false;
			}
			CPPInterface itf = (CPPInterface) o;

			if(itf.getClazz() != null)
			{
				boolean ok = itf.getClazz().equals(anInterface.getClazz());
				if(!ok)
				{
					return false;
				}
			}

			if(itf.getHeader() != null)
			{
				if(itf.getHeader().equals(anInterface.getHeader()))
				{
					return true;
				}
				// if still not true, then check using full path
				File fp1 = DirectoryScanner.searchArtifactFullPath(itf.getHeader());
				File fp2 = DirectoryScanner.searchArtifactFullPath(anInterface.getHeader());
				return fp1.equals(fp2);
			}
			// header cannot be null. it is required
			return false;
		}
	}

}
