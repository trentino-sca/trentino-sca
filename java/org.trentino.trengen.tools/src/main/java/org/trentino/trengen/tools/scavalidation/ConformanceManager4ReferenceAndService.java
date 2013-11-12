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

import java.net.URI;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.xml.bind.JAXBElement;
import javax.xml.namespace.QName;

import org.trentino.trengen.TIterable;
import org.trentino.trengen.ValidationException;
import org.apache.log4j.Logger;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.cpp.model.HeaderFile;
import org.trentino.trengen.sca.model.Binding;
import org.trentino.trengen.sca.model.CPPImplementation;
import org.trentino.trengen.sca.model.CPPInterface;
import org.trentino.trengen.sca.model.Callback;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentService;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.ComponentTypeReference;
import org.trentino.trengen.sca.model.Composite;
import org.trentino.trengen.sca.model.Contract;
import org.trentino.trengen.sca.model.Interface;
import org.trentino.trengen.sca.model.Metadata;
import org.trentino.trengen.sca.model.MetadataStringAttribute;
import org.trentino.trengen.sca.model.Reference;
import org.trentino.trengen.sca.model.SCABinding;
import org.trentino.trengen.sca.model.Service;
import org.trentino.trengen.sca.model.Wire;
import org.trentino.trengen.tools.trengen.Trengen;

/**
 * Service, reference, wires and bindings related conformance items
 * implementation
 */
public class ConformanceManager4ReferenceAndService {
	protected static final Logger	                   logger	                  = Logger.getLogger(ConformanceManager4ReferenceAndService.class);

	private CompositeWrapper	                       currentCompositeWrapper;
	private Composite	                               currentComposite;
	private String	                                   currentCompositeName;
	private Set<ComponentWrapper>	                   componentWrappers;
	private IConformanceManagerCppImpArtifacts	       conformanceManagerCppImpArtifacts;

	// for checking if the composite services' names are uniques
	public final ArrayList<String>	                   serviceNames	              = new ArrayList<String>();

	// for checking if the composite references' names are uniques
	private final ArrayList<String>	                   referenceNames	          = new ArrayList<String>();

	private final Map<ComponentTypeReference, Boolean>	componentTypeRefRelated	  = new HashMap<ComponentTypeReference, Boolean>();

	private Map<String, ReferenceTarget>	           compReferencesTargets	  = new HashMap<String, ReferenceTarget>();
	private Map<String, ReferenceTarget>	           compTypeReferencesTargets	= new HashMap<String, ReferenceTarget>();
	private Map<String, ReferenceTarget>	           compositeReferencesTargets	= new HashMap<String, ReferenceTarget>();

	private Map<String, ComponentReference>	           compReferences	          = new HashMap<String, ComponentReference>();
	private Map<String, ComponentTypeReference>	       compTypeReferences	      = new HashMap<String, ComponentTypeReference>();
	private Map<String, Reference>	                   compositeReferences	      = new HashMap<String, Reference>();

	public static final int	                           THREE_ENTRIES	          = 3;
	public static final int	                           TWO_ENTRIES	              = 2;
	public static final int	                           ONE_ENTRIES	              = 1;

	public Set<ComponentWrapper> getComponentWrappers() {
		return componentWrappers;
	}

	public ConformanceManager4ReferenceAndService (CompositeWrapper compWrapper, IConformanceManagerCppImpArtifacts confManagerCppImplArtifacts) {
		currentCompositeWrapper = compWrapper;
		currentComposite = compWrapper.getComposite();
		currentCompositeName = currentComposite.getName();
		componentWrappers = compWrapper.getListComponents();
		conformanceManagerCppImpArtifacts = confManagerCppImplArtifacts;
	}

	// -------------------------------------------------------------------------------------------------
	// this part is populating the componentWrapper...
	public boolean OnNewServiceOfComposite(Service service) {
		if(service.getInterface() != null)
		{
			if(!checkCPPArtifactsAndCallBackHeader(service, true))
			{
				return false;
			}
		}
		currentCompositeWrapper.compositeServices.add(service);
		if(!check_ASM60003(service) || !(check_ASM90002(service)))
		{
			return false;
		}
		return true;
	}

	public boolean OnNewReferenceOfComposite(Reference reference) {
		if(reference.getInterface() != null)
		{
			if(!checkCPPArtifactsAndCallBackHeader(reference, false))
			{
				return false;
			}
		}

		if(!check_ASM50026(reference))
		{
			return false;
		}

		if(!check_ASM60006(reference, referenceNames) || !(check_ASM90002(reference)))
		{
			return false;
		}

		currentCompositeWrapper.compositeReferences.add(reference);
		populateReferenceTargetObjects(reference, currentComposite);

		return true;
	}

	private boolean hasThisMetadataStringAttribute(Metadata metadata, MetadataStringAttribute att) {
		List<MetadataStringAttribute> atts = metadata.getStringAttributes();
		for (MetadataStringAttribute a : atts)
		{
			if(a.getName().equals(att.getName()))
				return true;
		}
		return false;
	}

	/**
	 * put metadatas in componenttype services into component services (merging)
	 */
	private void mergeMetaDatas(ComponentService compTypeService, ComponentService compService) {
		Metadata metadata = null;
		if(compService.getMetadata() != null)
		{
			metadata = compService.getMetadata();
			List<MetadataStringAttribute> atts = compTypeService.getMetadata().getStringAttributes();
			for (MetadataStringAttribute att : atts)
			{
				if(!hasThisMetadataStringAttribute(metadata, att))
				{
					metadata.getStringAttributes().add(att);
				}
			}
		}
		else
		{
			metadata = new Metadata();
			List<MetadataStringAttribute> atts = compTypeService.getMetadata().getStringAttributes();
			for (MetadataStringAttribute att : atts)
			{
				if(!hasThisMetadataStringAttribute(metadata, att))
				{
					metadata.getStringAttributes().add(att);
				}
			}
			compService.setMetadata(metadata);
		}
	}

	/**
	 * put metadatas in component services into composite services (merging)
	 */
	private void mergeMetaDatas(ComponentService compService, Service compositeService) {
		Metadata metadata = null;
		if(compositeService.getMetadata() != null)
		{
			metadata = compositeService.getMetadata();
			List<MetadataStringAttribute> atts = compService.getMetadata().getStringAttributes();
			for (MetadataStringAttribute att : atts)
			{
				if(!hasThisMetadataStringAttribute(metadata, att))
				{
					metadata.getStringAttributes().add(att);
				}
			}
		}
		else
		{
			metadata = new Metadata();
			List<MetadataStringAttribute> atts = compService.getMetadata().getStringAttributes();
			for (MetadataStringAttribute att : atts)
			{
				if(!hasThisMetadataStringAttribute(metadata, att))
				{
					metadata.getStringAttributes().add(att);
				}
			}
			compositeService.setMetadata(metadata);
		}
	}

	/**
	 * put metadatas in component services into composite services (merging)
	 */
	private void mergeMetaDatas(ComponentReference compRef, Reference compositeRef) {
		Metadata metadata = null;
		if(compositeRef.getMetadata() != null)
		{
			metadata = compositeRef.getMetadata();
			List<MetadataStringAttribute> atts = compRef.getMetadata().getStringAttributes();
			for (MetadataStringAttribute att : atts)
			{
				if(!hasThisMetadataStringAttribute(metadata, att))
				{
					metadata.getStringAttributes().add(att);
				}
			}
		}
		else
		{
			metadata = new Metadata();
			List<MetadataStringAttribute> atts = compRef.getMetadata().getStringAttributes();
			for (MetadataStringAttribute att : atts)
			{
				if(!hasThisMetadataStringAttribute(metadata, att))
				{
					metadata.getStringAttributes().add(att);
				}
			}
			compositeRef.setMetadata(metadata);
		}
	}

	private void mergeMetaDatas(ComponentTypeReference compTypeRef, ComponentReference compRef) {
		Metadata metadata = null;
		if(compRef.getMetadata() != null)
		{
			metadata = compRef.getMetadata();
			List<MetadataStringAttribute> atts = compTypeRef.getMetadata().getStringAttributes();
			for (MetadataStringAttribute att : atts)
			{
				if(!hasThisMetadataStringAttribute(metadata, att))
				{
					metadata.getStringAttributes().add(att);
				}
			}
		}
		else
		{
			metadata = new Metadata();
			List<MetadataStringAttribute> atts = compTypeRef.getMetadata().getStringAttributes();
			for (MetadataStringAttribute att : atts)
			{
				if(!hasThisMetadataStringAttribute(metadata, att))
				{
					metadata.getStringAttributes().add(att);
				}
			}
			compRef.setMetadata(metadata);
		}
	}

	/**
	 * [ASM90005] For a binding.sca of a component service, the uri attribute
	 * MUST NOT be present.
	 */
	private boolean OnNewServiceOfComponent(ComponentService s, Component component) {
		if(s.getInterface() != null)
		{
			if(!checkCPPArtifactsAndCallBackHeader(s, true))
			{
				return false;
			}
		}
		if(!(check_ASM90002(s)))
		{
			return false;
		}
		for (JAXBElement<? extends Binding> binding : s.getBinding())
		{
			if(binding.getDeclaredType().equals(SCABinding.class))
			{
				SCABinding scaBinding = (SCABinding) binding.getValue();
				if(scaBinding.getUri() != null)
				{
					logger.error(ConformanceManagerConstants.CI_ASM90005_VIOLATED + " for component service:" + s.getName() + " in "
							+ component.getName() + "@" + currentCompositeName);
					return false;
				}
			}
		}
		String serviceName = component.getName() + "/" + s.getName();
		return currentCompositeWrapper.putComponentService(serviceName, s);
	}

	private boolean OnNewServiceOfComponentType(ComponentService service, String currentComponentName) {
		String serviceName = currentComponentName + "/" + service.getName();
		boolean exists = false;
		ComponentService value = null;
		for (Map.Entry<String, ComponentService> entry : currentCompositeWrapper.getComponentServices().entrySet())
		{
			String key = entry.getKey();
			value = entry.getValue();
			if(key.equals(serviceName))
			{
				exists = true;
				// merging metadata
				if(service.getMetadata() != null)
				{
					mergeMetaDatas(service, value);
				}

				if(value.getInterface() == null)
				{
					if(service.getInterface() == null)
					{
						logger.error("Inteface is not specified for both component-level and componentType-level reference: " + value.getName());
						return false;
					}
					else
					{
						value.setInterface(service.getInterface());
						if(!currentCompositeWrapper.putComponentService(serviceName, value))
							;
					}
				}

				if(service.getInterface() == null && value.getInterface() != null)
					service.setInterface(value.getInterface());

				return true;
			}
		}
		if((service.getInterface() == null && value != null && value.getInterface() == null) || (service.getInterface() == null && value == null))
		{
			logger.error("Inteface is not specified for both component-level and componentType-level service: " + serviceName);
			return false;
		}
		if(!exists)
		{
			if(service.getInterface() == null && value != null && value.getInterface() != null)
				service.setInterface(value.getInterface());
			return currentCompositeWrapper.putComponentService(serviceName, service);
		}
		return true;
	}

	private boolean onNewReferenceOfComponentType(ComponentTypeReference ref, Component parentComponent) {
		if(ref.getInterface() != null)
		{
			if(!checkCPPArtifactsAndCallBackHeader(ref, false))
			{
				return false;
			}
		}
		if(!(check_ASM90002(ref)))
		{
			return false;
		}

		populateReferenceTargetObjects(ref, parentComponent, currentComposite);

		String referenceName = parentComponent.getName() + "/" + ref.getName();
		ComponentReference value = null;
		boolean exists = false;
		for (Map.Entry<String, ComponentReference> entry : currentCompositeWrapper.componentReferences.entrySet())
		{
			String key = entry.getKey();
			value = entry.getValue();
			if(key.equals(referenceName))
			{
				exists = true;
				// merging metadata
				if(ref.getMetadata() != null)
				{
					mergeMetaDatas(ref, value);
				}

				if(value.getInterface() == null)
				{
					if(ref.getInterface() == null)
					{
						throw new ValidationException("Inteface is not specified for both component-level and componentType-level reference: "
								+ referenceName, value);
					}
					else
					{
						value.setInterface(ref.getInterface());
						currentCompositeWrapper.componentReferences.put(referenceName, value);
					}
				}

				if(ref.getInterface() == null && value.getInterface() != null)
					ref.setInterface(value.getInterface());

				if(value.isAutowire() == null)
				{
					if(ref.isAutowire() != null)
					{
						value.setAutowire(ref.isAutowire());
						currentCompositeWrapper.componentReferences.put(referenceName, value);
					}
				}
				int valSize = value.getBinding().size();
				int refSize = ref.getBinding().size();
				if (valSize==0 && refSize>0)
				{
					for (int i=0; i<ref.getBinding().size(); i++)
					{
						Binding bindingTemp = ref.getBinding().get(i).getValue();
						if(bindingTemp.getClass().equals(SCABinding.class))
						{
							if (bindingTemp.getUri()== null)
								ref.getBinding().get(i).getValue().setUri("tcp://localhost:1234//dontUseThisName_FakeTarget");
						}

						value.getBinding().add((JAXBElement<? extends Binding>) ref.getBinding().get(i));
						currentCompositeWrapper.componentReferences.put(referenceName, value);
					}
				}
				return true;
			}
		}
		if((ref.getInterface() == null && value != null && value.getInterface() == null) || (ref.getInterface() == null && value == null))
		{
			logger.error("Inteface is not specified for both component-level and componentType-level reference: " + value.getName());
			return false;
		}
		if(!exists)
		{
			if(ref.getInterface() == null && value != null && value.getInterface() != null)
				ref.setInterface(value.getInterface());
			currentCompositeWrapper.componentTypeReferences.put(referenceName, ref);
		}

		return true;

	}

	private boolean OnNewReferenceOfComponent(ComponentReference s, Component parentComponent) {
		if(s.getInterface() != null)
		{
			if(!checkCPPArtifactsAndCallBackHeader(s, false))
			{
				return false;
			}
		}
		if(!(check_ASM90002(s)))
		{
			return false;
		}

		populateReferenceTargetObjects(s, parentComponent, currentComposite);

		String componentReferenceName = parentComponent.getName() + "/" + s.getName();
		currentCompositeWrapper.componentReferences.put(componentReferenceName, s);
		return true;
	}

	public boolean OnNewComponentOfComposite(Component component) {
		int compContent = component.getServiceOrReferenceOrProperty().size();
		for (int j = 0; j < compContent; j++)
		{
			if(component.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentService.class))
			{
				ComponentService s = (ComponentService) component.getServiceOrReferenceOrProperty().get(j);
				if(!OnNewServiceOfComponent(s, component))
				{
					return false;
				}
			}

			else if(component.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentReference.class))
			{
				ComponentReference ref = (ComponentReference) component.getServiceOrReferenceOrProperty().get(j);
				if(!OnNewReferenceOfComponent(ref, component))
				{
					return false;
				}
			}
		}

		return true;
	}

	public boolean onNewComponentTypeOfComposite(Component component) {
		ComponentWrapper wrapper = getCorrespondingComponentWrapper(component);

		if(wrapper == null)
		{
			return false;
		}
		ComponentType componentType = wrapper.getScaModelComponentType();

		for (Object obj : componentType.getServiceOrReferenceOrProperty())
		{
			try
			{
				if(obj instanceof ComponentService)
				{
					ComponentService s = (ComponentService) obj;
					if(!OnNewServiceOfComponentType(s, component.getName()))
					{
						return false;
					}
				}

				else if(obj instanceof ComponentTypeReference)
				{
					ComponentTypeReference ref = (ComponentTypeReference) obj;
					if(!onNewReferenceOfComponentType(ref, component))
					{
						return false;
					}
				}
			} catch (ValidationException e)
			{
				e.setLastEntity(obj);
				e.setLastEntity(wrapper);
				throw e;
			}

		}

		return true;
	}

	private ComponentWrapper getCorrespondingComponentWrapper(Component component) {
		for (ComponentWrapper comp : componentWrappers)
		{
			if(comp.getScaModelComponent().getName().equals(component.getName()))
			{
				return comp;
			}
		}
		return null;
	}

	public boolean OnNewWireOfComposite(Wire wire) {
		currentCompositeWrapper.wires.add(wire);
		return true;
	}

	// end of populating the compositeWrapper...
	// -------------------------------------------------------------------------------------------------

	// --- populate referenceTarget objects
	private void populateReferenceTargetObjects(ComponentReference componentReference, Component parentComponent, Composite parentComposite) {
		ReferenceTarget referenceTargetObject = new ReferenceTarget(componentReference.getName(), parentComponent.getName(),
				parentComposite.getName());
		if(componentReference.isAutowire() == null)
		{
			if(parentComponent.isAutowire() == null)
			{
				referenceTargetObject.setAutoWire(parentComposite.isAutowire());
			}
			else
			{
				referenceTargetObject.setAutoWire(parentComponent.isAutowire());
			}
		}
		else
		{
			referenceTargetObject.setAutoWire(componentReference.isAutowire());
		}

		referenceTargetObject.setWiredByImpl(componentReference.isWiredByImpl());

		List<String> targets = componentReference.getTarget();
		for (String target : targets)
		{
			referenceTargetObject.getTargetsInTargetAttribute().add(target);
		}

		if(componentReference.getBinding().size() != 0)
		{
			for (JAXBElement<? extends Binding> binding : componentReference.getBinding())
			{
				Binding bindingTemp = binding.getValue();
				if(bindingTemp.getUri() != null)
				{
					referenceTargetObject.getUrisInUriAttribute().add(bindingTemp.getUri());
				}

			}
		}

		String refName = parentComponent.getName() + "/" + componentReference.getName();
		compReferences.put(refName, componentReference);
		compReferencesTargets.put(refName, referenceTargetObject);
	}

	private void populateReferenceTargetObjects(ComponentTypeReference componentTypeReference, Component parentComponent, Composite parentComposite) {
		ReferenceTarget referenceTargetObject = new ReferenceTarget(componentTypeReference.getName(), parentComponent.getName(),
				parentComposite.getName());
		if(componentTypeReference.isAutowire() == null)
		{
			if(parentComponent.isAutowire() == null)
			{
				referenceTargetObject.setAutoWire(parentComposite.isAutowire());
			}
			else
			{
				referenceTargetObject.setAutoWire(parentComponent.isAutowire());
			}
		}
		else
		{
			referenceTargetObject.setAutoWire(componentTypeReference.isAutowire());
		}

		referenceTargetObject.setWiredByImpl(componentTypeReference.isWiredByImpl());

		List<String> targets = componentTypeReference.getTarget();
		for (String target : targets)
		{
			referenceTargetObject.getTargetsInTargetAttribute().add(target);
		}

		if(componentTypeReference.getBinding().size() != 0)
		{
			for (JAXBElement<? extends Binding> binding : componentTypeReference.getBinding())
			{
				Binding bindingTemp = binding.getValue();
				if(bindingTemp.getUri() != null)
				{
					referenceTargetObject.getUrisInUriAttribute().add(bindingTemp.getUri());
				}
			}
		}

		String refName = parentComponent.getName() + "/" + componentTypeReference.getName();
		compTypeReferences.put(refName, componentTypeReference);
		compTypeReferencesTargets.put(refName, referenceTargetObject);
	}

	private void populateReferenceTargetObjects(Reference compositeReference, Composite parentComposite) {
		ReferenceTarget referenceTargetObject = new ReferenceTarget(compositeReference.getName(), "", parentComposite.getName());

		referenceTargetObject.setWiredByImpl(compositeReference.isWiredByImpl());

		List<String> targets = compositeReference.getTarget();
		for (String target : targets)
		{
			referenceTargetObject.getTargetsInTargetAttribute().add(target);
		}

		if(compositeReference.getBinding().size() != 0)
		{
			for (JAXBElement<? extends Binding> binding : compositeReference.getBinding())
			{
				Binding bindingTemp = binding.getValue();
				if(bindingTemp.getUri() != null)
				{
					referenceTargetObject.getUrisInUriAttribute().add(bindingTemp.getUri());
				}
			}
		}

		String refName = compositeReference.getName();
		compositeReferences.put(refName, compositeReference);
		compositeReferencesTargets.put(refName, referenceTargetObject);
	}

	// end of populating referenceTarget objects

	/**
	 * [ASM40004] The name attribute of a <reference/> child element of a
	 * <componentType/> MUST be unique amongst the reference elements of that
	 * <componentType/>.
	 */
	private boolean check_ASM40004(ComponentTypeReference cr, ArrayList<String> referenceNames, String parentCompName) {
		String referenceName = cr.getName();

		for (int i = 0; i < referenceNames.size(); i++)
		{
			if(referenceName.equals(referenceNames.get(i)))
			{
				logger.error(ConformanceManagerConstants.CI_ASM40004_VIOLATED + " for componentType Reference:" + referenceName + " in "
						+ parentCompName + "@" + currentCompositeName);
				return false;
			}
		}
		referenceNames.add(referenceName);

		return true;
	}

	/**
	 * [ASM60003] The name of a composite <service/> element MUST be unique
	 * across all the composite services in the composite.
	 */
	private boolean check_ASM60003(Service service) {
		String serviceName = service.getName();

		for (int i = 0; i < serviceNames.size(); i++)
		{
			if(serviceName.equals(serviceNames.get(i)))
			{
				logger.error(ConformanceManagerConstants.CI_ASM60003_VIOLATED + " for Composite Service:" + serviceName + " @" + currentCompositeName);
				return false;
			}
		}
		serviceNames.add(serviceName);

		return true;
	}

	/**
	 * [ASM60006] The name of a composite <reference/> element MUST be unique
	 * across all the composite references in the composite.
	 */
	private boolean check_ASM60006(Reference reference, ArrayList<String> referenceNames) {
		String referenceName = reference.getName();

		for (int i = 0; i < referenceNames.size(); i++)
		{
			if(referenceName.equals(referenceNames.get(i)))
			{
				logger.error(ConformanceManagerConstants.CI_ASM60006_VIOLATED + " for composite Reference:" + referenceName + " @"
						+ currentCompositeName);
				return false;
			}
		}
		referenceNames.add(referenceName);

		return true;
	}

	/**
	 * @param compositeReference
	 *            : this reference's promoted references will be found.
	 * @param componentReferences
	 *            (@out param) : String is for the name of the reference like
	 *            componentName/compReferenceName, ComponentReference is for the
	 *            corresponding component reference. -> will be populated in
	 *            this function
	 * @return : number of promoted references
	 */
	private boolean returnPromotedReferences(String refName, String singlePromote, Map<String, ComponentReference> promotedReferences) {
		String[] prPath = singlePromote.split("/");
		int count = 0;

		for (Map.Entry<String, ComponentReference> entry : currentCompositeWrapper.componentReferences.entrySet())
		{
			String key = entry.getKey();
			ComponentReference value = entry.getValue();
			String[] keyPath = key.split("/");
			if(((prPath.length == ONE_ENTRIES) && keyPath[0].equals(prPath[0]))
					|| ((prPath.length == TWO_ENTRIES) && keyPath[0].equals(prPath[0]) && keyPath[1].equals(prPath[1])))
			{
				promotedReferences.put(key, value);
				count++;
			}
		}

		if((prPath.length == ONE_ENTRIES) && (count > ONE_ENTRIES))
		{
			logger.error(ConformanceManagerConstants.CI_ASM60007_VIOLATED + " for composite reference:" + refName + " @" + currentCompositeName);
			return false;
		}

		count = 0;

		for (Map.Entry<String, ComponentTypeReference> entry : currentCompositeWrapper.componentTypeReferences.entrySet())
		{
			String key = entry.getKey();
			ComponentTypeReference value = entry.getValue();
			String[] keyPath = key.split("/");
			if(((prPath.length == ONE_ENTRIES) && keyPath[0].equals(prPath[0]))
					|| ((prPath.length == TWO_ENTRIES) && keyPath[0].equals(prPath[0]) && keyPath[1].equals(prPath[1])))
			{
				promotedReferences.put(key, value);
				componentTypeRefRelated.put(value, true);
				count++;
			}
		}
		if((prPath.length == ONE_ENTRIES) && (count > ONE_ENTRIES))
		{
			logger.error(ConformanceManagerConstants.CI_ASM60007_VIOLATED + " for composite reference:" + refName + " @" + currentCompositeName);
			return false;
		}
		return true;
	}

	/**
	 * [ASM50039] A reference with multiplicity 0..1 MUST have no more than one
	 * target service defined.
	 */
	private boolean check_ASM50039(ComponentReference cr, ReferenceTarget refTargetObj, String currentComponentName) {
		if(cr.getMultiplicity().equals("0..1") && (refTargetObj.returnNumberOfTargets(cr) > 1))
		{
			logger.error(ConformanceManagerConstants.CI_ASM50039_VIOLATED + " for component reference:" + cr.getName() + " in "
					+ currentComponentName + "@" + currentCompositeName);
			refTargetObj.printMsg();
			return false;
		}
		return true;
	}

	/*
	 * private boolean check_ASM50039(ComponentTypeReference cr, ReferenceTarget refTargetObj, String currentComponentName) {
	 * if(cr.getMultiplicity().equals("0..1") && (refTargetObj.returnNumberOfTargets() > 1))
	 * {
	 * logger.error(ConformanceManagerConstants.CI_ASM50039_VIOLATED + " for componentType reference:" + cr.getName() + " in "
	 * + currentComponentName + "@" + currentCompositeName);
	 * refTargetObj.printMsg();
	 * return false;
	 * }
	 * return true;
	 * }
	 */

	private boolean check_ASM50039(Reference cr, ReferenceTarget refTargetObj) {
		if(cr.getMultiplicity().equals("0..1") && (refTargetObj.returnNumberOfTargets(cr) > 1))
		{
			logger.error(ConformanceManagerConstants.CI_ASM50039_VIOLATED + " for composite reference:" + cr.getName() + "@" + currentCompositeName);
			refTargetObj.printMsg();
			return false;
		}
		return true;
	}

	/**
	 * [ASM50040] A reference with multiplicity 1..1 MUST have exactly one
	 * target service defined
	 */
	private boolean check_ASM50040(ComponentReference cr, ReferenceTarget refTargetObj, String currentComponentName) {
		if(cr.getMultiplicity().equals("1..1") && (refTargetObj.returnNumberOfTargets(cr) != 1))
		{
			logger.error(ConformanceManagerConstants.CI_ASM50040_VIOLATED + " for component reference:" + cr.getName() + " in "
					+ currentComponentName + "@" + currentCompositeName);
			refTargetObj.printMsg();
			return false;
		}
		return true;
	}

	/*
	 * private boolean check_ASM50040(ComponentTypeReference cr, ReferenceTarget refTargetObj, String currentComponentName) {
	 * if(cr.getMultiplicity().equals("1..1") && (refTargetObj.returnNumberOfTargets() != 1))
	 * {
	 * logger.error(ConformanceManagerConstants.CI_ASM50040_VIOLATED + " for componentType reference:" + cr.getName() + " in "
	 * + currentComponentName + "@" + currentCompositeName);
	 * refTargetObj.printMsg();
	 * return false;
	 * }
	 * return true;
	 * }
	 */

	private boolean check_ASM50040(Reference cr, ReferenceTarget refTargetObj) {
		if(cr.getMultiplicity().equals("1..1") && (refTargetObj.returnNumberOfTargets(cr) != 1))
		{
			logger.error(ConformanceManagerConstants.CI_ASM50040_VIOLATED + " for composite reference:" + cr.getName() + "@" + currentCompositeName);
			refTargetObj.printMsg();
			return false;
		}
		return true;
	}

	/**
	 * [ASM50041]A reference with multiplicity 1..n MUST have at least one
	 * target service defined
	 */
	private boolean check_ASM50041(ComponentReference cr, ReferenceTarget refTargetObj, String currentComponentName) {
		if(cr.getMultiplicity().equals("1..n") && (refTargetObj.returnNumberOfTargets(cr) < 1))
		{
			logger.error(ConformanceManagerConstants.CI_ASM50041_VIOLATED + " for component reference:" + cr.getName() + " in "
					+ currentComponentName + "@" + currentCompositeName);
			refTargetObj.printMsg();
			return false;
		}
		return true;
	}

	/*
	 * private boolean check_ASM50041(ComponentTypeReference cr, ReferenceTarget refTargetObj, String currentComponentName) {
	 * if(cr.getMultiplicity().equals("1..n") && (refTargetObj.returnNumberOfTargets() < 1))
	 * {
	 * logger.error(ConformanceManagerConstants.CI_ASM50041_VIOLATED + " for componentType reference:" + cr.getName() + " in "
	 * + currentComponentName + "@" + currentCompositeName);
	 * refTargetObj.printMsg();
	 * return false;
	 * }
	 * return true;
	 * }
	 */

	private boolean check_ASM50041(Reference cr, ReferenceTarget refTargetObj) {
		if(cr.getMultiplicity().equals("1..n") && (refTargetObj.returnNumberOfTargets(cr) < 1))
		{
			logger.error(ConformanceManagerConstants.CI_ASM50041_VIOLATED + " for composite-level reference:" + cr.getName() + "@"
					+ currentCompositeName);
			refTargetObj.printMsg();
			return false;
		}
		return true;
	}

	/**
	 * [ASM50042] If a component reference has multiplicity 0..1 or 1..1 and
	 * nonOverridable==true, then the component reference MUST NOT be promoted
	 * by any composite reference.
	 * [ASM60007] Each of the URIs declared by a composite reference's promote
	 * attribute MUST identify a component reference within the composite.
	 * [ASM60008] the interfaces of the component references promoted by a
	 * composite reference MUST be the same, or if the composite reference
	 * itself declares an interface then each of the component reference
	 * interfaces MUST be a compatible subset of the composite reference
	 * interface.
	 * [ASM60012] If a composite reference has an interface specified, it MUST
	 * provide an interface which is the same or which is a compatible superset
	 * of the interface(s) declared by the promoted component reference(s).
	 * [ASM60009] the intents declared on a composite reference and on the
	 * component references which it promotes MUST NOT be mutually exclusive.
	 * [ASM60010] If any intents in the set which apply to a composite reference
	 * are mutually exclusive then the SCA runtime MUST raise an error.
	 * [ASM60011] The multiplicity of a composite reference MUST be equal to or
	 * further restrict the multiplicity of each of the component references
	 * that it promotes, with the exception that the multiplicity of the
	 * composite reference does not have to require a target if there is already
	 * a target on the component reference. This means that a component
	 * reference with multiplicity 1..1 and a target can be promoted by a
	 * composite reference with multiplicity 0..1, and a component reference
	 * with multiplicity 1..n and one or more targets can be promoted by a
	 * composite reference with multiplicity 0..n or 0..1.
	 * [ASM60035] All the component references promoted by a single composite
	 * reference MUST have the same value for wiredByImpl.
	 * [ASM60036] If the wiredByImpl attribute is not specified on the composite
	 * reference, the default value is "true." if all of the promoted component
	 * references have a wiredByImpl value of "true.", and the default value is
	 * "false" if all the promoted component references have a wiredByImpl value
	 * of "false". If the wiredByImpl attribute is specified, its value MUST be
	 * "true." if all of the promoted component references have a wiredByImpl
	 * value of "true.", and its value MUST be "false" if all the promoted
	 * component references have a wiredByImpl value of "false".
	 * @throws ValidationException
	 */
	private boolean checkForSingleCompositeReference(Reference reference) throws ValidationException {
		ReferenceTarget refTarget = null;
		for (Map.Entry<String, ReferenceTarget> entry2 : compositeReferencesTargets.entrySet())
		{
			if(reference.getName().equals(entry2.getKey()))
			{
				refTarget = entry2.getValue();
				break;
			}
		}
		Map<String, ComponentReference> promotedReferences = new HashMap<String, ComponentReference>();
		List<String> promotes = reference.getPromote();

		for (String pr : promotes)
		{
			if(!returnPromotedReferences(reference.getName(), pr, promotedReferences))
			{
				return false;
			}
		}
		if(promotedReferences.size() > 0)
		{
			boolean wiredByImpl = reference.isWiredByImpl();

			for (Map.Entry<String, ComponentReference> entry : promotedReferences.entrySet())
			{
				boolean exist = false;
				ComponentReference ref = entry.getValue();

				if(ref.getMetadata() != null)
				{
					mergeMetaDatas(ref, reference);
				}

				String refName = entry.getKey();

				for (Map.Entry<String, ReferenceTarget> entry2 : compReferencesTargets.entrySet())
				{
					if(entry2.getKey().equals(refName))
					{
						ReferenceTarget refTargetObjSmall = entry2.getValue();
						ReferenceTarget.returnReferenceTargetAfterPromotion(refTarget, refTargetObjSmall);
						exist = true;
					}
				}

				if(exist == false)
				{
					for (Map.Entry<String, ReferenceTarget> entry2 : compTypeReferencesTargets.entrySet())
					{
						if(entry2.getKey().equals(refName))
						{
							ReferenceTarget refTargetObjSmall = entry2.getValue();
							ReferenceTarget.returnReferenceTargetAfterPromotion(refTarget, refTargetObjSmall);
						}
					}
				}

				wiredByImpl = ref.isWiredByImpl();

				if(ref.isWiredByImpl() != wiredByImpl)
				{
					logger.error(ConformanceManagerConstants.CI_ASM60035_VIOLATED + " for composite reference:" + reference.getName() + " @"
							+ currentCompositeName);
					return false;
				}

				if((ref.getMultiplicity().equals("0..1") || ref.getMultiplicity().equals("1..1")) && (ref.isNonOverridable() == true))
				{
					logger.error(ConformanceManagerConstants.CI_ASM50042_VIOLATED + " for component reference:" + ref.getName() + "@"
							+ currentCompositeName);
					return false;
				}
				/*
				 * This part does not work. Moreover it is omitted for the first
				 * iteration. We don't support policies!!!
				 * System.out.println(reference.getSCARequires());
				 * System.out.println
				 * (componentReferences.get(promotedRefName).getSCARequires());
				 * if(!(reference.getRequires().equals(componentReferences.get(
				 * promotedRefName).getRequires())||
				 * reference.getRequires().contains
				 * (componentReferences.get(promotedRefName).getRequires()))) {
				 * logger.error(ConformanceManagerConstants.CI_ASM60009_VIOLATED
				 * + " for composite reference:" + reference.getName()); return
				 * false; }
				 */
				if(!isEqualOrFurtherRestrict(ref.getMultiplicity(), reference.getMultiplicity()))
				{
					logger.error(ConformanceManagerConstants.CI_ASM60011_VIOLATED + " for composite reference:" + reference.getName() + " @"
							+ currentCompositeName);
					return false;
				}
				if((reference.getInterface() != null) && (ref.getInterface() != null))
				{
					CPPInterface compositeInterface = (CPPInterface) reference.getInterface().getValue();
					CPPInterface componentInterface = (CPPInterface) ref.getInterface().getValue();
					if(!(conformanceManagerCppImpArtifacts.isSame(componentInterface, compositeInterface) || conformanceManagerCppImpArtifacts
							.isSubset(componentInterface, compositeInterface)))
					{
						logger.error(ConformanceManagerConstants.CI_ASM60008_VIOLATED + " for " + componentInterface.getHeader() + " and "
								+ compositeInterface.getHeader() + "@" + currentCompositeName);
						return false;
					}
					if(!(conformanceManagerCppImpArtifacts.isCallbackSame(componentInterface, compositeInterface) || conformanceManagerCppImpArtifacts
							.isCallbackSubset(componentInterface, compositeInterface)))
					{
						logger.error(ConformanceManagerConstants.CI_ASM60008_VIOLATED + " for " + componentInterface.getHeader() + " and "
								+ compositeInterface.getHeader() + "@" + currentCompositeName);
						return false;
					}
				}
				if(ref.isWiredByImpl())
				{
					logger.warn(ConformanceManagerConstants.CI_ASM50013_VIOLATED + " for component reference:" + ref.getName() + "@"
							+ currentCompositeName + ". It is promoted even though its wiredByImpl is set true.");
				}
				else if((ref.isAutowire() != null) && ref.isAutowire())
				{
					logger.warn(ConformanceManagerConstants.CI_ASM50014_VIOLATED + " for component reference:" + ref.getName() + "@"
							+ currentCompositeName + ". It is promoted even though its autowire is set true.");
				}
			}

			if(!check_ASM50039(reference, refTarget ) || !check_ASM50040(reference, refTarget) || !check_ASM50041(reference, refTarget))
			{
				return false;
			}
			if ( refTarget.isHasJustDefaultBinding())
			{
				logger.warn("\n\n\nWARNING!!! Reference " + reference.getName() + " in composite " + currentCompositeName + " is remotable. Please remember to ENABLE SERVICE DISCOVERY in Trentino runtime...\n\n\n");
			}

			refTarget.check_ASM50010_ASM50014_ASM40006_ASM50013();

			if(reference.isWiredByImpl() != wiredByImpl)
			{
				logger.error(ConformanceManagerConstants.CI_ASM60036_VIOLATED + " for composite reference:" + reference.getName() + " @"
						+ currentCompositeName);
				return false;
			}

		}
		else
		{
			logger.error(ConformanceManagerConstants.CI_ASM60007_VIOLATED + " for composite reference:" + reference.getName() + " @"
					+ currentCompositeName);
			return false;
		}
		return true;
	}

	public boolean checkAllReferencePromotions() {
		for (int i = 0; i < currentCompositeWrapper.compositeReferences.size(); i++)
		{
			Reference reference = currentCompositeWrapper.compositeReferences.get(i);
			try
			{
				if(!checkForSingleCompositeReference(reference))
				{
					// error code is given in the function
					return false;
				}
			} catch (ValidationException e)
			{
				e.setLastEntity(reference);
				throw e;
			}
		}
		return true;
	}

	/**
	 * [ASM60004] A composite <service/> element's promote attribute MUST
	 * identify one of the component services within that composite.
	 * [ASM60005] If a composite service interface is specified it MUST be the
	 * same or a compatible subset of the interface provided by the promoted
	 * component service.
	 */
	public boolean checkAllServicePromotions() {

		for (int i = 0; i < currentCompositeWrapper.compositeServices.size(); i++)
		{
			Service service = currentCompositeWrapper.compositeServices.get(i);

			List<ComponentService> promotedServices = new ArrayList<ComponentService>();
			String key = "";
			ComponentService value = new ComponentService();
			String promote = service.getPromote();

			int count = 0;
			String[] prPath = promote.split("/");
			for (Map.Entry<String, ComponentService> entry : currentCompositeWrapper.getComponentServices().entrySet())
			{
				key = entry.getKey();
				value = entry.getValue();
				String[] keyPath = key.split("/");
				if(((prPath.length == ONE_ENTRIES) && keyPath[0].equals(prPath[0]))
						|| ((prPath.length == TWO_ENTRIES) && keyPath[0].equals(prPath[0]) && keyPath[1].equals(prPath[1])))
				{
					promotedServices.add(value);
					count++;
				}
			}
			if(((prPath.length == ONE_ENTRIES) && (count > ONE_ENTRIES)) || !(promotedServices.size() > 0))
			{
				logger.error(ConformanceManagerConstants.CI_ASM60004_VIOLATED + " for composite service:" + service.getName() + " @"
						+ currentCompositeName);
				return false;
			}

			if((service.getInterface() != null) && (promotedServices.get(0).getInterface() != null))
			{
				CPPInterface compositeInterface = (CPPInterface) service.getInterface().getValue();
				CPPInterface componentInterface = (CPPInterface) promotedServices.get(0).getInterface().getValue();
				if(!(conformanceManagerCppImpArtifacts.isSame(compositeInterface, componentInterface) || conformanceManagerCppImpArtifacts.isSubset(
						compositeInterface, componentInterface)))
				{
					logger.error(ConformanceManagerConstants.CI_ASM60005_VIOLATED + " for " + compositeInterface.getHeader() + " and "
							+ componentInterface.getHeader() + "@" + currentCompositeName);
					return false;
				}
				if(!(conformanceManagerCppImpArtifacts.isCallbackSame(compositeInterface, componentInterface) || conformanceManagerCppImpArtifacts
						.isCallbackSubset(compositeInterface, componentInterface)))
				{
					logger.error(ConformanceManagerConstants.CI_ASM60005_VIOLATED + " for " + compositeInterface.getHeader() + " and "
							+ componentInterface.getHeader() + "@" + currentCompositeName);
					return false;
				}
			}

			if(promotedServices.get(0).getMetadata() != null)
			{
				mergeMetaDatas(promotedServices.get(0), service);
			}
		}
		return true;
	}

	private boolean validateUri(String uriString) {
		try
		{
			new URI(uriString);
		} catch (URISyntaxException e)
		{
			logger.error("This URI is malformed: " + uriString);
			return false;
		}
		return true;
	}

	/**
	 * [ASM50026] If a reference has a value specified for one or more target
	 * services in its target attribute, there MUST NOT be any child <binding/>
	 * elements declared for that reference.
	 */
	private boolean check_ASM50026(ComponentReference cr, String currentComponentName) {
		if(cr.getBinding().size() != 0)
		{
			for (JAXBElement<? extends Binding> binding : cr.getBinding())
			{
				Binding bindingTemp = binding.getValue();
				if(! bindingTemp.getClass().equals(SCABinding.class))
				{
					boolean isRemotable = false;
					if(cr.getInterface().getValue().isRemotable() != null && cr.getInterface().getValue().isRemotable() == true)
					{
						isRemotable = true;
					}
					if(isRemotable == true && bindingTemp.getUri() == null)
					{
						logger.error("Uri attribute of binding.sca should be specified for component reference " + cr.getName() + " in "
								+ currentComponentName + "@" + currentCompositeName);
						return false;
					}
				}
				
				if(bindingTemp.getUri() != null && !validateUri(bindingTemp.getUri()))
				{
					return false;
				}
			}
		}
		if((cr.getTarget().size() >= 1) && (cr.getBinding().size() > 0))
		{
			logger.error(ConformanceManagerConstants.CI_ASM50026_VIOLATED + " for component reference:" + cr.getName() + " in "
					+ currentComponentName + "@" + currentCompositeName);
			return false;
		}
		return true;
	}

	/**
	 * [ASM50026] If a reference has a value specified for one or more target
	 * services in its target attribute, there MUST NOT be any child <binding/>
	 * elements declared for that reference.
	 */
	private boolean check_ASM50026(ComponentTypeReference cr, String currentComponentName) {
		if(cr.getBinding().size() != 0)
		{
			for (JAXBElement<? extends Binding> binding : cr.getBinding())
			{
				Binding bindingTemp = binding.getValue();
				if(! bindingTemp.getClass().equals(SCABinding.class))
				{
					boolean isRemotable = false;
					if(cr.getInterface().getValue().isRemotable() != null && cr.getInterface().getValue().isRemotable() == true)
					{
						isRemotable = true;
					}
					if(isRemotable == true && bindingTemp.getUri() == null)
					{
						logger.error("Uri attribute of binding.sca should be specified for componenttype reference " + cr.getName() + " in "
								+ currentComponentName + "@" + currentCompositeName);
						return false;
					}
				}
				
				if(bindingTemp.getUri() != null && !validateUri(bindingTemp.getUri()))
				{
					return false;
				}
			}
		}
		if((cr.getTarget().size() >= 1) && (cr.getBinding().size() > 0))
		{
			logger.error(ConformanceManagerConstants.CI_ASM50026_VIOLATED + " for componentType reference:" + cr.getName() + " in "
					+ currentComponentName + "@" + currentCompositeName);
			return false;
		}
		return true;
	}

	/**
	 * [ASM50026] If a reference has a value specified for one or more target
	 * services in its target attribute, there MUST NOT be any child <binding/>
	 * elements declared for that reference.
	 */
	private boolean check_ASM50026(Reference cr) {
		if(cr.getBinding().size() != 0)
		{
			for (JAXBElement<? extends Binding> binding : cr.getBinding())
			{
				Binding bindingTemp = binding.getValue();
				if(! bindingTemp.getClass().equals(SCABinding.class))
				{
					boolean isRemotable = false;
					if(cr.getInterface().getValue().isRemotable() != null && cr.getInterface().getValue().isRemotable() == true)
					{
						isRemotable = true;
					}
					if(isRemotable == true && bindingTemp.getUri() == null)
					{
						logger.error("Uri attribute of binding.sca should be specified for composite reference " + cr.getName() + 
								"@" + currentCompositeName);
						return false;
					}
				}
				
				if(bindingTemp.getUri() != null && !validateUri(bindingTemp.getUri()))
				{
					return false;
				}
			}
			
		}
		if((cr.getTarget().size() >= 1) && (cr.getBinding().size() > 0))
		{
			logger.error(ConformanceManagerConstants.CI_ASM50026_VIOLATED + " for composite reference:" + cr.getName() + " @" + currentCompositeName);
			return false;
		}
		return true;
	}

	/**
	 * [ASM40003] The name attribute of a <service/> child element of a
	 * <componentType/> MUST be unique amongst the service elements of that
	 * <componentType/>. [ASM50002]: The name attribute of a service element of
	 * a <component/> MUST be unique amongst the service elements of that
	 * <component/>
	 */
	private boolean check_ASM50002_ASM40003(ComponentService cs, ArrayList<String> serviceNames) {
		String serviceName = cs.getName();
		for (int i = 0; i < serviceNames.size(); i++)
		{
			if(serviceName.equals(serviceNames.get(i)))
			{
				return false;
			}
		}
		serviceNames.add(serviceName);
		return true;
	}

	public boolean checkInterfaces() {
		final ValidationException ex = new ValidationException();
		ContributionVisitor visitor = new ContributionVisitor() {
			/*
			 * (non-Javadoc)
			 * @see org.trentino.trengen.tools.scavalidation.ContributionVisitor#visit(org.trentino.trengen.sca.model.ComponentService)
			 */
			@Override
			public void visit(ComponentWrapper wrapper) {
				ComponentType type = wrapper.getScaModelComponentType();
				TIterable<Contract> services = TIterable.iterable(type.getServiceOrReferenceOrProperty(), Contract.class);
				for (Contract serv : services)
				{
					checkContract(ex, wrapper, serv);
				}
			}

			private void checkContract(final ValidationException ex, ComponentWrapper wrapper, Contract serv) {
				if(serv.getInterface() == null || serv.getInterface().isNil())
				{
					return;
				}
				Interface itf = serv.getInterface().getValue();
				boolean found = false;
				if(itf instanceof CPPInterface)
				{
					CPPInterface cppitf = (CPPInterface) itf;
					String header = cppitf.getHeader();
					String cn = cppitf.getClazz();
					String headerAbs = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), header);
					if(headerAbs ==null){
						
						String msg = "Cannot find location of header file '%s' defined in interface of contract '%s'";
						ValidationException err = new ValidationException(String.format(msg, header,serv.getName()));
						return;
					}
					HeaderFile headerFile = conformanceManagerCppImpArtifacts.GetHeaderFile(headerAbs);
					for (ClassModel clazz : headerFile.getClasses())
					{
						String clazzName = clazz.getFullQualifiedClassName();
						if(clazzName.equals(cn))
						{
							found = true;
						}
					}
					if(!found)
					{
						String msg = "CPP interface '%s' not found in header file '%s'.\n" + "Component type file: %s";
						ValidationException ex2 = new ValidationException(String.format(msg, cn,header,wrapper.getScaModelComponentTypeFile().getAbsoluteFile()));
						ex.getExceptions().add(ex2);
					}
				}
			}

		};
		currentCompositeWrapper.accept(visitor);
		if(ex.getExceptions().size()>0){
			throw ex;
		}
		return true;
	}

	private boolean isEqualOrFurtherRestrict(String firstMult, String secondMult) // second
	// is
	// composite
	// reference
	{
		if(firstMult.equals(secondMult))
		{
			return true;
		}
		else
		{
			if(secondMult.equals("1..1") && !firstMult.equals("0..1"))
			{
				return false;
			}
			else if(firstMult.equals("1..n") && !(secondMult.equals("0..n") || secondMult.equals("0..1")))
			{
				return false;
			}
		}
		return true;
	}

	/**
	 * [ASM60043] The interface declared by the target of a wire MUST be a
	 * compatible superset of the interface declared by the source of the wire.
	 * [ASM60047] If there is no component service with name corresponding to
	 * <service-name>, the SCA runtime MUST raise an error. [ASM60048] If
	 * <service-name> is not present, the target component MUST have one and
	 * only one service with an interface that is a compatible superset of the
	 * wire source?s interface and satisfies the policy requirements of the wire
	 * source, and the SCA runtime MUST use this service for the wire.
	 * [ASM60049] If <binding-name> is present, the <binding/> subelement of the
	 * target service with name corresponding to <binding-name> MUST be used for
	 * the wire. [ASM60050] If there is no <binding/> subelement of the target
	 * service with name corresponding to <binding-name>, the SCA runtime MUST
	 * raise an error. [ASM50034] If any <wire/> element with its replace
	 * attribute set to "true." has a particular reference specified in its
	 * source attribute, the value of the target attribute for that reference
	 * MUST be ignored and MUST NOT be used to define target services for that
	 * reference.
	 */
	public boolean checkForWires() {
		for (int i = 0; i < currentCompositeWrapper.wires.size(); i++)
		{
			Wire wire = currentCompositeWrapper.wires.get(i);
			String source = wire.getSource().trim(); // get from component
			// references
			// source related stuff
			if(source.contains(" "))
			{
				throw new ValidationException("There are more than 1 source in the wire: " + source + " @" + currentCompositeName);
			}

			if(source != null)
			{
				String[] sourceList = source.split("/");
				String sourceComponent = sourceList[0];
				String sourceRef = "";
				if(sourceList.length == TWO_ENTRIES)
				{
					sourceRef = sourceList[1];
				}

				String target = wire.getTarget().trim();

				if(target.contains(" "))
				{
					throw new ValidationException("There are more than 1 target in the wire: " + target + " @" + currentCompositeName);
				}

				// target related stuff
				if(target != null)
				{
					String[] targetList = target.split("/");
					String targetComponent = targetList[0];
					String targetService = "";
					String targetBinding = "";
					if(targetList.length == THREE_ENTRIES)
					{
						targetService = targetList[1];
						targetBinding = targetList[2];
					}
					else if(targetList.length == TWO_ENTRIES)
					{
						targetService = targetList[1];
					}

					ComponentReference compRef = new ComponentReference();
					ComponentService[] compService = new ComponentService[1];
					boolean[] targetComponentExists =
						{ false };
					if(!isComponentInThisComposite(compRef, sourceComponent, sourceRef, currentCompositeWrapper))
					{
						throw new ValidationException(ConformanceManagerConstants.CI_ASM60047_VIOLATED + " for " + sourceComponent + "/" + sourceRef
								+ "@" + currentCompositeName);
					}
					else if(!isComponentInThisComposite(compService, targetComponent, targetService, targetBinding, currentCompositeWrapper,
							targetComponentExists) || compService[0] == null)
					{
						if(!targetComponentExists[0])
						{
							logger.warn(ConformanceManagerConstants.CI_ASM60047_VIOLATED + " for " + targetComponent + "/" + targetService + "@"
									+ currentCompositeName);
						}
						else
						{
							throw new ValidationException(ConformanceManagerConstants.CI_ASM60047_VIOLATED + " for " + targetComponent + "/"
									+ targetService + "@" + currentCompositeName);
						}
					}
					//

					if(currentCompositeWrapper.componentReferences.get(sourceComponent + "/" + sourceRef) != null)
					{
						ReferenceTarget refTargetObj = compReferencesTargets.get(sourceComponent + "/" + sourceRef);
						if(!ReferenceTarget.isInList(targetComponent + "/" + targetService + "/" + targetBinding, refTargetObj.getWireSources()))
						{
							refTargetObj.getWireSources().add(targetComponent + "/" + targetService + "/" + targetBinding);
						}
						compReferencesTargets.put(sourceComponent + "/" + sourceRef, refTargetObj);
					}

					if(currentCompositeWrapper.componentTypeReferences.get(sourceComponent + "/" + sourceRef) != null)
					{
						ReferenceTarget refTargetObj = compTypeReferencesTargets.get(sourceComponent + "/" + sourceRef);
						if(!ReferenceTarget.isInList(targetComponent + "/" + targetService + "/" + targetBinding, refTargetObj.getWireSources()))
						{
							refTargetObj.getWireSources().add(targetComponent + "/" + targetService + "/" + targetBinding);
						}
						compTypeReferencesTargets.put(sourceComponent + "/" + sourceRef, refTargetObj);
					}
					//
					if(wire.isReplace() && (target != null) && (compRef.getTarget().size() > 0))
					{
						logger.warn(ConformanceManagerConstants.CI_ASM50034_VIOLATED + " for wire @" + currentCompositeName);
					}

					if((compRef.getInterface() != null) && (compService[0].getInterface() != null))
					{
						CPPInterface cppRef = (CPPInterface) compRef.getInterface().getValue();
						CPPInterface cppService = (CPPInterface) compService[0].getInterface().getValue();

						if(!conformanceManagerCppImpArtifacts.isSame(cppRef, cppService)
								&& !conformanceManagerCppImpArtifacts.isSubset(cppRef, cppService))
						{
							throw new ValidationException(ConformanceManagerConstants.CI_ASM60043_VIOLATED + " for " + cppRef.getHeader() + " and "
									+ cppService.getHeader() + " in the wire @" + currentCompositeName);
						}
						if(!conformanceManagerCppImpArtifacts.isCallbackSame(cppRef, cppService)
								&& !conformanceManagerCppImpArtifacts.isCallbackSubset(cppRef, cppService))
						{
							throw new ValidationException(ConformanceManagerConstants.CI_ASM60043_VIOLATED + " for " + cppRef.getHeader() + " and "
									+ cppService.getCallbackHeader() + " in the wire @" + currentCompositeName);
						}
					}
				}
			}
		}
		return true;
	}

	private void importTargetsFromCorrespondingComponentTypeReference(String uniqueRefName, ReferenceTarget refTargetObjComponent) {
		for (Map.Entry<String, ReferenceTarget> entry2 : compTypeReferencesTargets.entrySet())
		{
			if(entry2.getKey().equals(uniqueRefName))
			{
				ReferenceTarget refTargetObjComponentType = entry2.getValue();
				ReferenceTarget.importTargetsFromCorrespondingComponentTypeReference(refTargetObjComponent, refTargetObjComponentType);
			}
		}
	}

	/**
	 * 4.3.1 Specifying the Target Service(s) for a Reference A reference
	 * defines zero or more target services that satisfy the reference. The
	 * target service(s) can be defined in the following ways: 1. Through a
	 * value specified in the @target attribute of the reference element 2.
	 * Through a target URI specified in the @uri attribute of a binding element
	 * which is a child of the reference element 3. Through the setting of one
	 * or more values for binding-specific attributes and/or child elements of a
	 * binding element that is a child of the reference element 4. Through the
	 * specification of @autowire="true" for the reference (or through
	 * inheritance of that value from the component or composite containing the
	 * reference) 5. Through the specification of @wiredByImpl="true" for the
	 * reference 6. Through the promotion of a component reference by a
	 * composite reference of the composite containing the component (the target
	 * service is then identified by the configuration of the composite
	 * reference) 7. Through the presence of a <wire/> element which has the
	 * reference specified in its @source attribute. Combinations of these
	 * different methods are allowed, and the following rules MUST be observed:
	 * If @wiredByImpl="true", other methods of specifying the target service
	 * MUST NOT be used. [ASM50013]If @autowire="true", the autowire procedure
	 * MUST only be used if no target is identified by any of the other ways
	 * listed above. It is not an error if @autowire="true" and a target is also
	 * defined through some other means, however in this case the autowire
	 * procedure MUST NOT be used. [ASM50014] �?� If a reference has a value
	 * specified for one or more target services in its @target attribute, there
	 * MUST NOT be any child <binding/> elements declared for that reference.
	 * [ASM50026] If a binding element has a value specified for a target
	 * service using its @uri attribute, the binding element MUST NOT identify
	 * target services using binding specific attributes or elements. [ASM50015]
	 * �?� It is possible that a particular binding type uses more than a simple
	 * URI for the address of a target service. In cases where a reference
	 * element has a binding subelement that uses more than simple URI, the @uri
	 * attribute of the binding element MUST NOT be used to identify the target
	 * service - in this case binding specific attributes and/or child elements
	 * MUST be used. [ASM50016] �?� If any <wire/> element with its @replace
	 * attribute set to "true" has a particular reference specified in its @source
	 * attribute, the value of the @target attribute for that reference MUST be
	 * ignored and MUST NOT be used to define target services for that
	 * reference. [ASM50034]
	 * @return
	 */
	public boolean checkForComponentTypeAndComponentReferenceTargets() {

		for (Map.Entry<String, ReferenceTarget> entry : compTypeReferencesTargets.entrySet())
		{

			ReferenceTarget refTargetObj = entry.getValue();
			String refName = entry.getKey();
			int index = refName.lastIndexOf("/");
			String currentComponentName = refName.substring(0, index);
			for (Map.Entry<String, ComponentTypeReference> entry2 : compTypeReferences.entrySet())
			{
				ComponentTypeReference cr = entry2.getValue();
				if(entry2.getKey().equals(refName))
				{
					if(!check_ASM50026(cr, currentComponentName))
					{
						return false;
					}
					refTargetObj.check_ASM50010_ASM50014_ASM40006_ASM50013();
				}
			}
		}

		for (Map.Entry<String, ReferenceTarget> entry : compReferencesTargets.entrySet())
		{

			ReferenceTarget refTargetObj = entry.getValue();
			String refName = entry.getKey();
			int index = refName.lastIndexOf("/");
			String currentComponentName = refName.substring(0, index);
			importTargetsFromCorrespondingComponentTypeReference(refName, refTargetObj);
			for (Map.Entry<String, ComponentReference> entry2 : compReferences.entrySet())
			{
				ComponentReference cr = entry2.getValue();
				if(entry2.getKey().equals(refName))
				{
					if(!check_ASM50026(cr, currentComponentName) || !check_ASM50039(cr, refTargetObj, currentComponentName)
							|| !check_ASM50040(cr, refTargetObj, currentComponentName) || !check_ASM50041(cr, refTargetObj, currentComponentName))
					{
						return false;
					}
					if (refTargetObj.isHasJustDefaultBinding())
					{
						logger.warn("\n\n\nWARNING!!! Reference " + cr.getName() + " in composite " + currentCompositeName + " is remotable. Please remember to ENABLE SERVICE DISCOVERY in Trentino runtime...\n\n\n");
					}
					
					refTargetObj.check_ASM50010_ASM50014_ASM40006_ASM50013();
				}
			}
		}
		return true;
	}

	public boolean checkForCompositeReferenceTargets() {
		for (int i = 0; i < currentCompositeWrapper.compositeReferences.size(); i++)
		{
			Reference cr = currentCompositeWrapper.compositeReferences.get(i);

			List<String> targets = cr.getTarget();

			// target related stuff
			for (String target : targets)
			{
				String[] targetList = target.split("/");
				String targetComponent = targetList[0];
				String targetService = "";
				String targetBinding = "";
				if(targetList.length == THREE_ENTRIES)
				{
					targetService = targetList[1];
					targetBinding = targetList[2];
				}
				else if(targetList.length == TWO_ENTRIES)
				{
					targetService = targetList[1];
				}

				ComponentService[] compService = new ComponentService[1];
				boolean[] targetComponentExists =
					{ false };
				// Not being able to find a matching target should not be an
				// error according to "Understanding SCA chapter:9"
				// A warning is raised and returned true stopping further checks
				// (in checkForCompositeReferenceTargets)
				if(!isComponentInThisComposite(compService, targetComponent, targetService, targetBinding, currentCompositeWrapper,
						targetComponentExists) || compService[0] == null)
				{
					if(!targetComponentExists[0])
					{
						logger.warn(ConformanceManagerConstants.CI_ASM60047_VIOLATED + " for " + targetComponent + "/" + targetService + "@"
								+ currentCompositeName);
					}
					else
					{
						throw new ValidationException(ConformanceManagerConstants.CI_ASM60047_VIOLATED + " for " + targetComponent + "/"
								+ targetService + "@" + currentCompositeName);
					}
				}

				if((cr.getInterface() != null) && (compService[0].getInterface() != null))
				{
					CPPInterface cppRef = (CPPInterface) cr.getInterface().getValue();
					CPPInterface cppService = (CPPInterface) compService[0].getInterface().getValue();

					if(!conformanceManagerCppImpArtifacts.isSame(cppRef, cppService)
							&& !conformanceManagerCppImpArtifacts.isSubset(cppRef, cppService))
					{
						throw new ValidationException(ConformanceManagerConstants.CI_ASM60043_VIOLATED + " for " + cppRef.getHeader() + " and "
								+ cppService.getHeader() + "@" + currentCompositeName);
					}
					if(!conformanceManagerCppImpArtifacts.isCallbackSame(cppRef, cppService)
							&& !conformanceManagerCppImpArtifacts.isCallbackSubset(cppRef, cppService))
					{
						throw new ValidationException(ConformanceManagerConstants.CI_ASM60043_VIOLATED + " for " + cppRef.getHeader() + " and "
								+ cppService.getCallbackHeader() + "@" + currentCompositeName);
					}
				}
			}
		}
		return true;
	}

	private boolean isComponentInThisComposite(ComponentService[] compService, String targetComponent, String targetService, String targetBinding,
			CompositeWrapper compWrapper, boolean[] targetComponentExists) {
		targetComponentExists[0] = false;
		boolean targetServiceExists = false;
		boolean isCompositeByImpl = false;
		TIterable<Component> components = TIterable.iterable(compWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService(), Component.class);
		for (Component component : components)
		{
			if(component.getName().equals(targetComponent))
			{
				targetComponentExists[0] = true;
				if(targetService.equals(""))
				{
					int serviceCount = 0;
					for (Map.Entry<String, ComponentService> entry : compWrapper.getComponentServices().entrySet())
					{
						String key = entry.getKey();
						ComponentService value = entry.getValue();
						String[] keyList = key.split("/");
						if(keyList[0].equals(targetComponent))
						{
							compService[0] = value;
							targetService = keyList[1];
							targetServiceExists = true;
							serviceCount++;
						}
					}

					if(serviceCount > 1)
					{
						logger.error(ConformanceManagerConstants.CI_ASM60048_VIOLATED + " for " + targetComponent + "/" + targetService + "@"
								+ currentCompositeName);
						return false;
					}
				}

				if((targetBinding != "")) // if(!compService.getBinding().contains(targetBinding))
				{
					boolean exist = false;
					for (JAXBElement<? extends Binding> binding : compService[0].getBinding())
					{
						if(binding.getValue().getUri() != null && binding.getValue().getUri().equals(targetBinding))
						{
							exist = true;
							break;
						}
					}
					if(exist == false)
					{
						logger.error(ConformanceManagerConstants.CI_ASM60050_VIOLATED + " for " + targetComponent + "/" + targetService + "@"
								+ currentCompositeName);
						return false;
					}
				}

				if(!targetServiceExists)
				{
					compService[0] = compWrapper.getComponentServices().get(targetComponent + "/" + targetService);
				}

				if(compService[0] != null)
				{
					return true;
				}
				if(!targetComponentExists[0])
				{
					return true;
				}
				return false;
			}
		}

		isCompositeByImpl = compWrapper.isCompositeByImpl();
		if(isCompositeByImpl)
		{
			CompositeWrapper compositeWrapper = compWrapper.parent;
			if(compositeWrapper != null
					&& isComponentInThisComposite(compService, targetComponent, targetService, targetBinding, compositeWrapper, targetComponentExists))
			{
				return true;
			}
		}
		return false;
	}

	private boolean isComponentInThisComposite(ComponentReference compRef, String sourceComponent, String sourceRef, CompositeWrapper compWrapper) {
		boolean isCompositeByImpl = false;
		for (int i = 0; i < compWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().size(); i++)
		{
			if(compWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Component.class))
			{
				Component component = (Component) compWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(i);
				if(component.getName().equals(sourceComponent))
				{
					if(sourceRef.equals(""))
					{
						int refCount = 0;
						for (Map.Entry<String, ComponentReference> entry : compWrapper.componentReferences.entrySet())
						{
							String key = entry.getKey();
							ComponentReference value = entry.getValue();
							String[] keyList = key.split("/");
							if(keyList[0].equals(sourceComponent))
							{
								compRef = value;
								sourceRef = keyList[1];
								refCount++;
							}
						}
						if(refCount > 1)
						{
							logger.error(ConformanceManagerConstants.CI_ASM60048_VIOLATED + " for the source in the wire @" + currentCompositeName);
							return false;
						}
					}

					compRef = currentCompositeWrapper.componentReferences.get(sourceComponent + "/" + sourceRef);
					if(compRef == null)
					{
						if(sourceRef.equals(""))
						{
							int refCount = 0;
							for (Map.Entry<String, ComponentTypeReference> entry : compWrapper.componentTypeReferences.entrySet())
							{
								String key = entry.getKey();
								ComponentTypeReference value = entry.getValue();
								String[] keyList = key.split("/");
								if(keyList[0].equals(sourceComponent))
								{
									compRef = value;
									componentTypeRefRelated.put(value, true);
									sourceRef = keyList[1];
									refCount++;
								}
							}

							if(refCount > 1)
							{
								logger.error(ConformanceManagerConstants.CI_ASM60048_VIOLATED + " for the source in the wire @"
										+ currentCompositeName);
								return false;
							}
						}
					}
					if(compRef == null)
					{
						compRef = currentCompositeWrapper.componentTypeReferences.get(sourceComponent + "/" + sourceRef);
					}
					if(compRef != null)
					{
						return true;
					}
					return false;
				}
			}
		}

		isCompositeByImpl = compWrapper.isCompositeByImpl();
		if(isCompositeByImpl)
		{
			CompositeWrapper compositeWrapper = compWrapper.parent;
			if(compositeWrapper != null && isComponentInThisComposite(compRef, sourceComponent, sourceRef, compositeWrapper))
			{
				return true;
			}
		}
		return false;
	}

	/**
	 * ASM90002] When a service or reference has multiple bindings, all
	 * noncallback bindings of the service or reference MUST have unique names,
	 * and all callback bindings of the service or reference MUST have unique
	 * names.
	 */
	private boolean check_ASM90002(Object service) {
		Callback callback = new Callback();
		if(((Contract) service).getCallback() != null)
		{
			callback = ((Contract) service).getCallback();
		}

		List<String> bindingNames = new ArrayList<String>();

		for (int i = 0; i < callback.getBindingOrRequiresOrPolicySetAttachment().size(); i++)
		{
			JAXBElement<?> element = (JAXBElement<?>) callback.getBindingOrRequiresOrPolicySetAttachment().get(i);
			if(element.getDeclaredType().equals(SCABinding.class))
			{
				for (int j = 0; j < bindingNames.size(); j++)
				{
					if(((SCABinding) element.getValue()).getName().equals(bindingNames.get(j)))
					{
						logger.error(ConformanceManagerConstants.CI_ASM90002_VIOLATED + " for " + ((Contract) service).getName() + "(type: "
								+ service.getClass() + ") @ " + currentCompositeName);
						return false;
					}
				}
				bindingNames.add(((SCABinding) element.getValue()).getName());
			}
		}

		bindingNames.clear();
		for (int i = 0; i < ((Contract) service).getBinding().size(); i++)
		{
			Binding binding = ((Contract) service).getBinding().get(i).getValue();
			for (int j = 0; j < bindingNames.size(); j++)
			{
				if(binding.getName().equals(bindingNames.get(j)))
				{
					logger.error(ConformanceManagerConstants.CI_ASM90002_VIOLATED + " for " + ((Contract) service).getName() + "(type: "
							+ service.getClass() + ") @ " + currentCompositeName);
					return false;
				}
			}
			bindingNames.add(binding.getName());
		}
		return true;
	}

	public boolean checkForComponentTypeService(ComponentService cs, Component currentComponent, ArrayList<String> serviceNames,
			CPPImplementation cppImplementation) {
		String currentComponentName = currentComponent.getName();
		if(cs.getInterface() != null)
		{
			CPPInterface serviceInterface = (CPPInterface) cs.getInterface().getValue();

			if(!checkCPPArtifactsAndCallBackHeader(cs, true))
			{
				return false;
			}
			if(cppImplementation != null)
			{
				if(!conformanceManagerCppImpArtifacts.checkInterfaceImplCompatibility(serviceInterface, cppImplementation, currentComponentName))
				{
					return false;
				}
			}
		}

		if(!check_ASM50002_ASM40003(cs, serviceNames) || !(check_ASM90002(cs)))
		{
			throw new ValidationException(ConformanceManagerConstants.CI_ASM40003_VIOLATED + " for componentType service:" + cs.getName() + " in "
					+ currentComponentName + "@" + currentCompositeName);
		}
		return true;
	}

	public boolean checkForComponentTypeReference(ComponentTypeReference ref, Component currentComponent, ArrayList<String> refNames, ComponentWrapper componentWrapper) {
		String currentComponentName = currentComponent.getName();

		if(ref.getInterface() != null)
		{
			if(!checkCPPArtifactsAndCallBackHeader(ref, false))
			{
				return false;
			}
		}

		if((ref.getTarget()==null || ref.getTarget().size()==0) && ref.getBinding().size()==0){
			boolean found = false;
			String name = ref.getName();
			//then make sure that the component has a target
			TIterable<ComponentReference> refs = TIterable.iterable(currentComponent.getServiceOrReferenceOrProperty(), ComponentReference.class);
			for(ComponentReference el : refs){

				if(el.getName().equals(name)){
					found = true;
					break;
				}
			}
			if(!found){
				logger.warn("Reference is defined in component type but no target is defined\nReference:"+name
						+"\nPlease configure reference in the component "
			+currentComponentName+" in the composite "+currentCompositeName);
			}
		}
		
		if(!check_ASM40004(ref, refNames, currentComponentName) || !(check_ASM90002(ref)))
		{
			return false;
		}

		if(ref.getTarget() != null)
		{
			List<String> targets = ref.getTarget();

			// target related stuff
			for (String target : targets)
			{
				String[] targetList = target.split("/");
				String targetComponent = targetList[0];
				String targetService = "";
				String targetBinding = "";
				if(targetList.length == THREE_ENTRIES)
				{
					targetService = targetList[1];
					targetBinding = targetList[2];
				}
				else if(targetList.length == TWO_ENTRIES)
				{
					targetService = targetList[1];
				}

				ComponentService[] compService = new ComponentService[1];
				boolean[] targetComponentExists =
					{ false };
				if(!isComponentInThisComposite(compService, targetComponent, targetService, targetBinding, currentCompositeWrapper,
						targetComponentExists))
				{
					if(!targetComponentExists[0])
					{
						logger.warn(String.format("Component with name '%s' is referenced as target in componenttype file '%s' but does not exists in composite '%s'",targetComponent,componentWrapper.getScaModelComponentTypeFile().getPath(),currentCompositeName));
					    continue;
					}
					else
					{
						logger.error(ConformanceManagerConstants.CI_ASM60047_VIOLATED + " for " + targetComponent + "/" + targetService + "@"
								+ currentCompositeName);
						return false;
					}
				}
				
                if(compService[0] ==null){
                	throw new ValidationException(String.format("Service '%s' is referenced by reference '%s' in component type file '%s' but does not exists in composite '%s'",target,ref.getName(),componentWrapper.getScaModelComponentTypeFile().getPath(),currentCompositeName));
                }
				if((ref.getInterface() != null) && (compService[0].getInterface() != null))
				{
					CPPInterface cppRef = (CPPInterface) ref.getInterface().getValue();
					CPPInterface cppService = (CPPInterface) compService[0].getInterface().getValue();

					if(!conformanceManagerCppImpArtifacts.isSame(cppRef, cppService)
							&& !conformanceManagerCppImpArtifacts.isSubset(cppRef, cppService))
					{
						logger.error(ConformanceManagerConstants.CI_ASM60043_VIOLATED + " for " + cppRef.getHeader() + " and "
								+ cppService.getHeader() + "@" + currentCompositeName);
						return false;
					}
					if(!conformanceManagerCppImpArtifacts.isCallbackSame(cppRef, cppService)
							&& !conformanceManagerCppImpArtifacts.isCallbackSubset(cppRef, cppService))
					{
						logger.error(ConformanceManagerConstants.CI_ASM60043_VIOLATED + " for " + cppRef.getHeader() + " and "
								+ cppService.getCallbackHeader() + "@" + currentCompositeName);
						return false;
					}
				}
			}
		}
		return true;
	}

	/**
	 * [ASM50002]: The name attribute of a service element of a <component/>
	 * MUST be unique amongst the service elements of that <component/>
	 * [ASM50003]: The name attribute of a service element of a <component/>
	 * MUST match the name attribute of a service element of the componentType
	 * of the <implementation/> child element of the component.
	 * [ASM50004]: If an interface is declared for a component service, the
	 * interface MUST provide a compatible subset of the interface declared for
	 * the equivalent service in the componentType of the implementation.
	 */
	public boolean checkForComponentService(ComponentService compService, ComponentType currentComponentType, ArrayList<String> serviceNames,
			String currentComponentName) {

		if(!check_ASM50002_ASM40003(compService, serviceNames))
		{
			logger.error(ConformanceManagerConstants.CI_ASM50002_VIOLATED + " for component service:" + compService.getName() + " in "
					+ currentComponentName + "@" + currentCompositeName);
			return false;
		}
		boolean exists = false;
		for (int k = 0; k < currentComponentType.getServiceOrReferenceOrProperty().size(); k++)
		{
			if(currentComponentType.getServiceOrReferenceOrProperty().get(k).getClass().equals(ComponentService.class))
			{
				ComponentService compTypeService = (ComponentService) currentComponentType.getServiceOrReferenceOrProperty().get(k);
				if(compTypeService.getName().equals(compService.getName()))
				{
					exists = true;
					if((compService.getInterface() != null) && (compTypeService.getInterface() != null))
					{
						CPPInterface compInterface = (CPPInterface) compService.getInterface().getValue();
						CPPInterface compTypeInterface = (CPPInterface) compTypeService.getInterface().getValue();
						if(!conformanceManagerCppImpArtifacts.isSame(compInterface, compTypeInterface)
								&& !conformanceManagerCppImpArtifacts.isSubset(compInterface, compTypeInterface))
						{
							logger.error(ConformanceManagerConstants.CI_ASM50004_VIOLATED + " for " + compInterface.getHeader() + " and "
									+ compTypeInterface.getHeader() + " in " + currentComponentName + "@" + currentCompositeName);
							return false;
						}
						if(!conformanceManagerCppImpArtifacts.isCallbackSame(compInterface, compTypeInterface)
								&& !conformanceManagerCppImpArtifacts.isCallbackSubset(compInterface, compTypeInterface))
						{
							logger.error(ConformanceManagerConstants.CI_ASM50004_VIOLATED + " for " + compInterface.getCallbackHeader() + " and "
									+ compTypeInterface.getCallbackHeader());
							return false;
						}
					}
				}
			}
			if(exists)
			{
				break;
			}
		}

		if(!exists)
		{
			logger.error(ConformanceManagerConstants.CI_ASM50003_VIOLATED + " for component service:" + compService.getName() + " in "
					+ currentComponentName + "@" + currentCompositeName);
			return false;
		}
		return true;
	}

	/**
	 * [ASM50007]: The name attribute of a reference element of a <component/>
	 * MUST be unique amongst the reference elements of that <component/>
	 * [ASM50008]: The name attribute of a reference element of a <component/>
	 * MUST match the name attribute of a reference element of the componentType
	 * of the <implementation/> child element of the component.
	 * [ASM50009]: The value of multiplicity for a component reference MUST only
	 * be equal or further restrict any value for the multiplicity of the
	 * reference with the same name in the componentType of the implementation,
	 * where further restriction means 0..n to 0..1 or 1..n to 1..1.
	 * [ASM50011]: If an interface is declared for a component reference, the
	 * interface MUST provide a compatible superset of the interface declared
	 * for the equivalent reference in the componentType of the implementation.
	 */
	public boolean checkForComponentReference(ComponentReference compRef, ComponentType currentComponentType, ArrayList<String> refNames,
			String currentComponentName) {
		String refName = compRef.getName();
		for (String ref : refNames)
		{
			if(refName.equals(ref))
			{
				String msg = "[ASM50007] Duplicated reference name " + ref + "\nComposite: " + currentCompositeName;
				throw new ValidationException(msg);
			}
		}
		refNames.add(refName);

		boolean exists = false;
		TIterable<ComponentTypeReference> ctrefs = TIterable.iterable(currentComponentType.getServiceOrReferenceOrProperty(),
				ComponentTypeReference.class);
		for (ComponentTypeReference compTypeRef : ctrefs)
		{
			if(compTypeRef.getName().equals(compRef.getName()))
			{
				if(!isEqualOrFurtherRestrict(compRef.getMultiplicity(), compTypeRef.getMultiplicity()))
				{
					throw new ValidationException(ConformanceManagerConstants.CI_ASM50009_VIOLATED + " for componentType Reference:"
							+ compTypeRef.getName() + " in " + currentComponentName + "@" + currentCompositeName);
				}
				exists = true;
				if(compRef.getInterface() == null || compTypeRef.getInterface() == null)
				{
					continue;
				}
				CPPInterface compInterface = (CPPInterface) compRef.getInterface().getValue();
				CPPInterface compTypeInterface = (CPPInterface) compTypeRef.getInterface().getValue();
				if(!conformanceManagerCppImpArtifacts.isSame(compTypeInterface, compInterface)
						&& !conformanceManagerCppImpArtifacts.isSubset(compTypeInterface, compInterface))
				{
					throw new ValidationException(ConformanceManagerConstants.CI_ASM50011_VIOLATED + " for " + compInterface.getHeader() + " and "
							+ compTypeInterface.getHeader() + " in " + currentComponentName + "@" + currentCompositeName);
				}
				if(!conformanceManagerCppImpArtifacts.isCallbackSame(compTypeInterface, compInterface)
						&& !conformanceManagerCppImpArtifacts.isCallbackSubset(compTypeInterface, compInterface))
				{
					throw new ValidationException(ConformanceManagerConstants.CI_ASM50011_VIOLATED + " for " + compInterface.getHeader() + " and "
							+ compTypeInterface.getHeader() + " in " + currentComponentName + "@" + currentCompositeName);
				}

			}
			// if one of the wiredByImpl in component and componentType is
			// true, other should also be considered as true.
			if(compRef.isWiredByImpl())
			{
				compTypeRef.setWiredByImpl(true);
			}
			if(compTypeRef.isWiredByImpl())
			{
				compRef.setWiredByImpl(true);
			}
			if(exists)
			{
				break;
			}
		}

		if(!exists)
		{
			String msg = "[ASM50008] Reference with name '%s' is defined in component '%s', but not defined in the corresponding component type file.\nComposite: %s";
			throw new ValidationException(String.format(msg, refName, currentComponentName, currentCompositeName));
		}

		if(compRef.getTarget() != null)
		{
			List<String> targets = compRef.getTarget();

			// target related stuff
			for (String target : targets)
			{
				String[] targetList = target.split("/");
				String targetComponent = targetList[0];
				String targetService = "";
				String targetBinding = "";
				if(targetList.length == THREE_ENTRIES)
				{
					targetService = targetList[1];
					targetBinding = targetList[2];
				}
				else if(targetList.length == TWO_ENTRIES)
				{
					targetService = targetList[1];
				}

				ComponentService[] compService = new ComponentService[1];
				boolean[] targetComponentExists =
					{ false };
				if(!isComponentInThisComposite(compService, targetComponent, targetService, targetBinding, currentCompositeWrapper,
						targetComponentExists))
				{
					if(!targetComponentExists[0])
					{
						logger.warn(ConformanceManagerConstants.CI_ASM60047_VIOLATED + " for " + targetComponent + "/" + targetService + "@"
								+ currentCompositeName);
					}
					else
					{
						ValidationException validationException = new ValidationException();
						String msg = "target '%s' does not exists. Component part '%s' %s found.";
						validationException.addMessage(String.format(msg, target, targetComponent, targetComponentExists[0] ? "" : "not"));
						validationException.setLastEntity(compRef);
						validationException.setLastEntity(currentComponentType);
						throw validationException;
					}
				}

				if((compRef.getInterface() != null) && (compService[0].getInterface() != null))
				{
					CPPInterface cppRef = (CPPInterface) compRef.getInterface().getValue();
					CPPInterface cppService = (CPPInterface) compService[0].getInterface().getValue();

					if(!conformanceManagerCppImpArtifacts.isSame(cppRef, cppService)
							&& !conformanceManagerCppImpArtifacts.isSubset(cppRef, cppService))
					{
						String msg = "The reference '%s' in component '%s' is incompatible with target service '%s' in component '%s'.\n"
								+ "Reference classname is '%s' \n" + "      defined in header file '%s'\n" + "Target service classname is '%s'\n"
								+ "      defined in header file '%s'";
						msg = String.format(msg, refName, currentComponentName, targetService, targetComponent, cppRef.getClazz(),
								cppRef.getHeader(), cppService.getClazz(), cppService.getHeader());
						throw new ValidationException(msg);
					}
					if(!conformanceManagerCppImpArtifacts.isCallbackSame(cppRef, cppService)
							&& !conformanceManagerCppImpArtifacts.isCallbackSubset(cppRef, cppService))
					{
						throw new ValidationException(ConformanceManagerConstants.CI_ASM60043_VIOLATED + " for " + cppRef.getHeader() + " and "
								+ cppService.getCallbackHeader() + "@" + currentCompositeName);
					}
				}
			}
		}
		return true;
	}

	private boolean checkCPPArtifactsAndCallBackHeader(Object s, boolean isService) {

		CPPInterface serviceInterface = (CPPInterface) ((Contract) s).getInterface().getValue();
		try
		{
			if(!conformanceManagerCppImpArtifacts.checkCPPInterfaceArtifactExistence(serviceInterface, isService))
			{
			}
			if(!conformanceManagerCppImpArtifacts.checkCallBackHeader(serviceInterface))
			{
				return false;
			}
			return true;
		} catch (ValidationException e)
		{
			e.setLastEntity(serviceInterface);
			e.setLastEntity(s);
			throw e;
		}

	}

	public boolean check_ASM60033() {
		for (Map.Entry<ComponentTypeReference, Boolean> entryType : componentTypeRefRelated.entrySet())
		{
			ComponentTypeReference key = entryType.getKey();
			Boolean value = entryType.getValue();

			if(key.getMultiplicity().equals("1..1") || key.getMultiplicity().equals("1..n"))
			{
				if(value == false)
				{
					return false;
				}
			}
		}
		return true;
	}
}
