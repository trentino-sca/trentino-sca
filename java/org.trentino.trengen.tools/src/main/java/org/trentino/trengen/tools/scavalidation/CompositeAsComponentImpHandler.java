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

import java.util.List;
import java.util.Map;

import javax.xml.bind.JAXBElement;
import javax.xml.namespace.NamespaceContext;
import javax.xml.namespace.QName;

import org.apache.log4j.Logger;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.sca.model.Binding;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentService;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.ComponentTypeReference;
import org.trentino.trengen.sca.model.Composite;
import org.trentino.trengen.sca.model.Interface;
import org.trentino.trengen.sca.model.Property;
import org.trentino.trengen.sca.model.Reference;
import org.trentino.trengen.sca.model.Service;

/**
 * This class manages the implementation.composite to validate the composites
 * used as component implementation and to create the appropriate componentType
 * for it.
 */
public class CompositeAsComponentImpHandler {
	protected static final Logger	logger	             = Logger.getLogger(CompositeAsComponentImpHandler.class);
	private CompositeWrapper	  compositeWrapper	     = null;
	private String	              compositeName	         = null;

	private ScaValidationManager	scaValidationManager	= null;

	public CompositeAsComponentImpHandler (ScaValidationManager valManager) {
		scaValidationManager = valManager;
	}

	public CompositeWrapper getCompositeWrapper() {
		return compositeWrapper;
	}

	/**
	 * This is the only public method of the class, it is goal is to validate
	 * the composite that is used as component imp and creates the componentType
	 * according to the composite used as impl
	 */
	public ComponentType searchMatchingComponentTypeOfCompositeImpl(String compositeSearchKey, NamespaceContext ns,
	        ContributionTypeWrapper contributionTypeWrapper, CompositeWrapper parentCompositeWrapper) {
		// we also need to validate the composite used as component
		// implementation

		compositeWrapper = scaValidationManager.validateComposite2(compositeSearchKey,parentCompositeWrapper);
		if(compositeWrapper == null)
		{
			ValidationException ex = new ValidationException();
			ex.addMessage("Error while generating the componentType of composite used as component");
			ex.addMessage("There is no matching composite for: " + compositeSearchKey);
			throw ex;
		}
		String compositeFileName = compositeWrapper.getCompositeFileName();
		compositeName = compositeWrapper.getCompositeName();
		logger.info("Creating the componentType for composite used as component implementation. composite File name: " + compositeFileName
		        + " Composite name: " + compositeName);

		return createComponentType(compositeWrapper);
	}

	/**
	 * Creates the componentType for the composite used as component
	 * implementation
	 */
	private ComponentType createComponentType(CompositeWrapper compositeWrapper) {
		ComponentType componentType = new ComponentType();
		Composite composite = compositeWrapper.getComposite();
		// Dead store to a local variable
		// String compositeName = composite.getName();

		/*
		 * FINDBUG: A value is checked here to see whether it is null, but this
		 * value can't be null because it was previously dereferenced and if it
		 * were null a null pointer exception would have occurred at the earlier
		 * dereference. Essentially, this code and the previous dereference
		 * disagree as to whether this value is allowed to be null. Either the
		 * check is redundant or the previous dereference is erroneous.
		 */
		/*
		 * if(composite == null) { logger.error(
		 * "Composite is null for composite used as component implementation. CompositeName: "
		 * + compositeName); return null; }
		 */

		int sizeOfComponentElements = composite.getRequiresOrPolicySetAttachmentOrService().size();
		for (int index = 0; index < sizeOfComponentElements; index++)
		{
			if(composite.getRequiresOrPolicySetAttachmentOrService().get(index).getClass().equals(Property.class))
			{
				Property propertyComposite = (Property) composite.getRequiresOrPolicySetAttachmentOrService().get(index);
				addPropertyToComponentType(componentType, propertyComposite);
			}
			else if(composite.getRequiresOrPolicySetAttachmentOrService().get(index).getClass().equals(Reference.class))
			{
				Reference referenceComposite = (Reference) composite.getRequiresOrPolicySetAttachmentOrService().get(index);
				addReferenceToComponentType(componentType, referenceComposite);
			}

			else if(composite.getRequiresOrPolicySetAttachmentOrService().get(index).getClass().equals(Service.class))
			{
				Service serviceComposite = (Service) composite.getRequiresOrPolicySetAttachmentOrService().get(index);
				addServiceToComponentType(componentType, serviceComposite);
			}
		}
		addImplementationToComponentType(componentType, composite);

		return componentType;
	}

	/**
	 * Project the properties of the componentType according to the composite
	 * used as component implementation
	 * @param componentType
	 * @param propertyComposite
	 */
	private void addPropertyToComponentType(ComponentType componentType, Property propertyComposite) {
		Property property = new Property();
		property.setName(propertyComposite.getName());
		property.setType(propertyComposite.getType());
		property.setElement(propertyComposite.getElement());
		if(propertyComposite.isMany() == null)
		{
			property.setMany(false);
		}
		else
		{
			property.setMany(propertyComposite.isMany());
		}
		property.setMustSupply(propertyComposite.isMustSupply());

		// Property of ComponentType does not include a requires and policySets
		// attribute according to the xsd and SCAAMv1.1
		// But section 5.5 says that policySets and Requires of componentType
		// property should be set according to the composit
		// set requires for reference
		// set policySets

		// default values are added here
		List<Object> contents = propertyComposite.getContent();
		for (Object content : contents)
		{
			property.getContent().add(content);
		}

		componentType.getServiceOrReferenceOrProperty().add(property);
	}

	/**
	 * Project the references of the componentType according to the composite
	 * used as component implementation
	 * @param componentType
	 * @param referenceComposite
	 */
	private void addReferenceToComponentType(ComponentType componentType, Reference referenceComposite) {
		ComponentTypeReference reference = new ComponentTypeReference();
		String refName = referenceComposite.getName();
		reference.setName(refName);

		// set requires for reference
		List<QName> requiresOfComposite = referenceComposite.getRequires();
		for (int i = 0; i < requiresOfComposite.size(); i++)
		{
			reference.getRequires().add(requiresOfComposite.get(i));
		}

		// set policySets
		List<QName> policySetOfComposite = referenceComposite.getPolicySets();
		for (int i = 0; i < policySetOfComposite.size(); i++)
		{
			reference.getPolicySets().add(policySetOfComposite.get(i));
		}

		// set the targets
		List<String> listTargetsOfComposite = referenceComposite.getTarget();
		for (int i = 0; i < listTargetsOfComposite.size(); i++)
		{
			reference.getTarget().add(listTargetsOfComposite.get(i));
		}

		reference.setWiredByImpl(referenceComposite.isWiredByImpl());
		reference.setMultiplicity(referenceComposite.getMultiplicity());

		JAXBElement<? extends Interface> interfaceComposite = referenceComposite.getInterface();
		if(interfaceComposite == null)
		{
			List<String> promotedReferences = referenceComposite.getPromote();
			for (int i = 0; i < promotedReferences.size(); i++)
			{
				interfaceComposite = findMatchingInterfaceOfReference(promotedReferences.get(i), refName);
				if(interfaceComposite == null)
				{
					logger.error("There is no matching interface(in the composite, component and componentType) for the promoted references of compoiste: "
					        + compositeName);
					continue;
				}
				else
				{
					reference.setInterface(interfaceComposite);
					break;
				}
			}
		}
		else
		{
			reference.setInterface(referenceComposite.getInterface());
		}
		reference.setCallback(referenceComposite.getCallback());

		// omit since not mentioned in sec 5.5
		// reference.setExtensions(referenceComposite.getExtensions());

		componentType.getServiceOrReferenceOrProperty().add(reference);
	}

	/**
	 * Project the services of the componentType according to the composite used
	 * as component implementation
	 * @param componentType
	 * @param serviceComposite
	 */
	private void addServiceToComponentType(ComponentType componentType, Service serviceComposite) {
		ComponentService service = new ComponentService();
		String serviceName = serviceComposite.getName();
		service.setName(serviceName);

		// set requires for reference
		List<QName> requiresOfComposite = serviceComposite.getRequires();
		for (int i = 0; i < requiresOfComposite.size(); i++)
		{
			service.getRequires().add(requiresOfComposite.get(i));
		}

		// set policySets
		List<QName> policySetOfComposite = serviceComposite.getPolicySets();
		for (int i = 0; i < policySetOfComposite.size(); i++)
		{
			service.getPolicySets().add(policySetOfComposite.get(i));
		}

		String promotedService = serviceComposite.getPromote();
		JAXBElement<? extends Interface> interfaceComposite = serviceComposite.getInterface();
		if(interfaceComposite == null)
		{
			interfaceComposite = findMatchingInterfaceOfService(promotedService, serviceName);
			if(interfaceComposite == null)
			{
				logger.error("There is no matching interface(in the composite, component and componentType) for the promoted references of compoiste: "
				        + compositeName);
			}
			service.setInterface(interfaceComposite);
		}
		else
		{
			service.setInterface(serviceComposite.getInterface());
		}

		// set binding
		serviceComposite.getBinding();
		List<JAXBElement<? extends Binding>> listBindingsOfComposite = serviceComposite.getBinding();
		for (int i = 0; i < listBindingsOfComposite.size(); i++)
		{
			JAXBElement<? extends Binding> element = listBindingsOfComposite.get(i);

			service.getBinding().add(element);
		}

		service.setCallback(serviceComposite.getCallback());

		// omit since not mentioned in sec 5.5
		// service.setExtensions(serviceComposite.getExtensions());

		componentType.getServiceOrReferenceOrProperty().add(service);
	}

	/**
	 * Project the implementation of the componentType according to the
	 * composite used as component implementation
	 * @param componentType
	 * @param composite
	 */
	private void addImplementationToComponentType(ComponentType componentType, Composite composite) {
		List<QName> policySetsOfComposite = composite.getPolicySets();
		int sizePoliciySets = policySetsOfComposite.size();
		for (int i = 0; i < sizePoliciySets; i++)
		{
			componentType.getImplementation().getValue().getPolicySets().add(policySetsOfComposite.get(i));
		}

		List<QName> requiresOfCompositeImpl = composite.getRequires();
		int sizeRequires = requiresOfCompositeImpl.size();
		for (int i = 0; i < sizeRequires; i++)
		{
			componentType.getImplementation().getValue().getRequires().add(policySetsOfComposite.get(i));
		}
	}

	/**
	 * This function finds out the interface of the promoted service. Called if
	 * there is no interface for the service at the composite level
	 * @param promotedString
	 * @return
	 */
	private JAXBElement<? extends Interface> findMatchingInterfaceOfService(String promotedString, String serviceName) {
		// maybe there is only one service of component so no need to explicitly
		// tell it while promoting
		// It is required to concat with the service name
		/*
		 * if(promotedString.indexOf('/') == -1) { promotedString =
		 * promotedString + "//" + serviceName; }
		 * ComponentService service = findPromotedService(promotedString);
		 * if(service == null) { return null; } else { return
		 * service.getInterface(); }
		 */
		String[] targetList = promotedString.split("/");
		String targetComponent = targetList[0];
		String targetService = "";

		if(targetList.length == 2)
		{
			targetService = targetList[1];
		}

		ComponentService compService = new ComponentService();

		if(targetService.equals(""))
		{
			int serviceCount = 0;
			String key = "";
			for (Map.Entry<String, ComponentService> entry : compositeWrapper.getComponentServices().entrySet())
			{
				key = entry.getKey();
				ComponentService value = entry.getValue();
				String[] keyList = key.split("/");
				if(keyList[0].equals(targetComponent))
				{
					compService = value;
					targetService = keyList[1];
					serviceCount++;
				}
			}

			if(serviceCount > 1)
			{
				logger.error("There are more than 1 interfaces found. There is something wrong for the composite service: " + serviceName);
				return null;
			}
		}

		compService = compositeWrapper.getComponentServices().get(targetComponent + "/" + targetService);
		if(compService == null)
		{
			logger.error("There is no matching interface(in the composite, component and componentType) for " + "the promoted services of composite");
			return null;
		}
		else
		{
			return compService.getInterface();
		}
	}

	/**
	 * Searches for the promoted service within the Component and ComponentType
	 * services that are analyzed during the validation of the composite used as
	 * component implementation (kept in the compositeWrapper)
	 * @param promotedService
	 * @return
	 */
	/*
	 * private ComponentService findPromotedService(String promotedService) {
	 * if(compositeWrapper.componentServices.containsKey(promotedService)) {
	 * return compositeWrapper.componentServices.get(promotedService); } else {
	 * return null; } }
	 */

	/**
	 * This function finds out the interface of the promoted reference. Called
	 * if there is no interface for the reference at the composite level
	 * @param promotedReference
	 * @return
	 */
	private JAXBElement<? extends Interface> findMatchingInterfaceOfReference(String promotedReference, String refName) {
		// maybe there is only one reference of component so no need to
		// explicitly tell it while promoting
		// It is required to concat with the ref name
		/*
		 * if(promotedReference.indexOf('/') == -1) { promotedReference =
		 * promotedReference + "//" + refName; }
		 * ComponentReference refenceComponent =
		 * findPromotedReference(promotedReference); if(refenceComponent ==
		 * null) { ComponentTypeReference referenceComponentType =
		 * findPromotedReferenceComponentType(promotedReference);
		 * if(referenceComponentType == null) { return null; } else { return
		 * referenceComponentType.getInterface(); } } else { return
		 * refenceComponent.getInterface(); }
		 */

		String[] targetList = promotedReference.split("/");
		String targetComponent = targetList[0];
		String targetReference = "";

		if(targetList.length == 2)
		{
			targetReference = targetList[1];
		}

		ComponentReference compReference = new ComponentReference();

		if(targetReference.equals(""))
		{
			int refCount = 0;
			String key = "";
			for (Map.Entry<String, ComponentReference> entry : compositeWrapper.componentReferences.entrySet())
			{
				key = entry.getKey();
				ComponentReference value = entry.getValue();
				String[] keyList = key.split("/");
				if(keyList[0].equals(targetComponent))
				{
					compReference = value;
					targetReference = keyList[1];
					refCount++;
				}
			}

			if(refCount > 1)
			{
				logger.error("There are more than 1 interfaces found. There is something wrong for the composite reference: " + refName);
				return null;
			}
		}

		compReference = compositeWrapper.componentReferences.get(targetComponent + "/" + targetReference);
		if(compReference == null)
		{
			ComponentTypeReference compTypeReference = new ComponentTypeReference();

			if(targetReference.equals(""))
			{
				int refCount = 0;
				String key = "";
				for (Map.Entry<String, ComponentTypeReference> entry : compositeWrapper.componentTypeReferences.entrySet())
				{
					key = entry.getKey();
					ComponentTypeReference value = entry.getValue();
					String[] keyList = key.split("/");
					if(keyList[0].equals(targetComponent))
					{
						compTypeReference = value;
						targetReference = keyList[1];
						refCount++;
					}
				}

				if(refCount > 1)
				{
					logger.error("There are more than 1 interfaces found. There is something wrong for the composite service: " + refName);
					return null;
				}
			}

			compTypeReference = compositeWrapper.componentTypeReferences.get(targetComponent + "/" + targetReference);
			if(compTypeReference == null)
			{
				logger.error("There is no matching interface(in the composite, component and componentType) for "
				        + "the promoted references of composite: " + refName);
				return null;
			}
			else
			{
				return compTypeReference.getInterface();
			}
		}
		else
		{
			return compReference.getInterface();
		}
	}

	/**
	 * Searches for the promoted reference within the ComponentType references
	 * that are analyzed during the validation of the composite used as
	 * component implementation (kept in the compositeWrapper)
	 * @param promotedReference
	 * @return
	 */
	/*
	 * private ComponentTypeReference findPromotedReferenceComponentType(String
	 * promotedReference) {
	 * if(compositeWrapper.componentTypeReferences.containsKey
	 * (promotedReference)) { return
	 * compositeWrapper.componentTypeReferences.get(promotedReference); } else {
	 * return null; } }
	 */

	/**
	 * Searches for the promoted reference within the Component references that
	 * are analyzed during the validation of the composite used as component
	 * implementation (kept in the compositeWrapper)
	 * @param promotedReference
	 * @return
	 */
	/*
	 * private ComponentReference findPromotedReference(String
	 * promotedReference) {
	 * if(compositeWrapper.componentReferences.containsKey(promotedReference)) {
	 * return compositeWrapper.componentReferences.get(promotedReference); }
	 * else { return null; } }
	 */
}
