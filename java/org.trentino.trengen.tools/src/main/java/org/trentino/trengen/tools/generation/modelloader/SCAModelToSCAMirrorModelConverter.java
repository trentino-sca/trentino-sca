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

package org.trentino.trengen.tools.generation.modelloader;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import javax.xml.bind.JAXBElement;

import org.apache.log4j.Logger;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.sca.model.Binding;
import org.trentino.trengen.sca.model.CPPFunction;
import org.trentino.trengen.sca.model.CPPImplementation;
import org.trentino.trengen.sca.model.CPPImplementationFunction;
import org.trentino.trengen.sca.model.CPPInterface;
import org.trentino.trengen.sca.model.Callback;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentService;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.ComponentTypeReference;
import org.trentino.trengen.sca.model.Composite;
import org.trentino.trengen.sca.model.Contract;
import org.trentino.trengen.sca.model.ContributionType;
import org.trentino.trengen.sca.model.DeployableType;
import org.trentino.trengen.sca.model.Documentation;
import org.trentino.trengen.sca.model.IPCBinding;
import org.trentino.trengen.sca.model.Implementation;
import org.trentino.trengen.sca.model.Include;
import org.trentino.trengen.sca.model.Interface;
import org.trentino.trengen.sca.model.Metadata;
import org.trentino.trengen.sca.model.MetadataStringAttribute;
import org.trentino.trengen.sca.model.PolicySetAttachment;
import org.trentino.trengen.sca.model.Property;
import org.trentino.trengen.sca.model.PropertyValue;
import org.trentino.trengen.sca.model.Reference;
import org.trentino.trengen.sca.model.Requires;
import org.trentino.trengen.sca.model.SCABinding;
import org.trentino.trengen.sca.model.SCAImplementation;
import org.trentino.trengen.sca.model.Service;
import org.trentino.trengen.sca.model.ValueType;
import org.trentino.trengen.sca.model.Wire;
import org.trentino.trengen.tools.generation.CPPModelProvider;
import org.trentino.trengen.tools.generation.proxieswrappers.ReferenceServiceInterface;
import org.trentino.trengen.tools.generation.reflection.PropertyReflx;
import org.trentino.trengen.tools.generation.reflection.ReflectionObject;
import org.trentino.trengen.tools.scavalidation.ComponentWrapper;
import org.trentino.trengen.tools.scavalidation.CompositeWrapper;
import org.trentino.trengen.tools.scavalidation.ConformanceManagerProperty;
import org.trentino.trengen.tools.scavalidation.ContributionTypeWrapper;
import org.trentino.trengen.tools.scavalidation.ContributionVisitor;
import org.trentino.trengen.tools.trengen.ImportExport;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.xml.schema.AnyURI;
import org.trentino.trengen.xml.schema.NCName;
import org.trentino.trengen.xml.schema.Name;
import org.trentino.trengen.xml.schema.QName;

/**
 * This class is the converter of sca model to sca mirror model.
 */
public class SCAModelToSCAMirrorModelConverter {

	// members
	// ---------------------------------------------------------------------------
	protected static final Logger	                                logger	                   = Logger.getLogger(SCAModelToSCAMirrorModelConverter.class);

	// this list keeps all composite mirror wrappers
	private List<CompositeMirrorWrapper>	                        compositeMirrorWrapperList	= new ArrayList<CompositeMirrorWrapper>();

	// this if for the mirror object of contributiontype
	private org.trentino.trengen.scamodelmirror.ContributionType	contributionType	       = new org.trentino.trengen.scamodelmirror.ContributionType();
	private String	                                                applicationName	           = new String();

	// this list is used for the reflection-code-generation
	private List<ReflectionObject>	                                reflectionObjects	       = new ArrayList<ReflectionObject>();

	// this list keeps the service interfaces in proxies-code-generation
	private List<ReferenceServiceInterface>	                        serviceInterfaces	       = new ArrayList<ReferenceServiceInterface>();
	private Set<ReferenceServiceInterface>                          remotableServices          = new HashSet<ReferenceServiceInterface>();

	// this list keeps the reference interfaces in wrappers-code-generation
	private List<ReferenceServiceInterface>	                        referenceInterfaces	       = new ArrayList<ReferenceServiceInterface>();

	// this is used for using directives.. will be supported soon!...
	private Map<String, Object>	                                    usingDirectivesMap	       = new HashMap<String, Object>();

	/**
	 * This list keeps the unique sca mirror model componenttype objects.
	 */
	private List<org.trentino.trengen.scamodelmirror.ComponentType>	mirrorComponentTypeList	   = new ArrayList<org.trentino.trengen.scamodelmirror.ComponentType>();

	/**
	 * This list keeps all component-componenttype relationships.
	 * ComponentComponentTypeAssociation class keeps 2 String objects for
	 * components and componentTypes.
	 */
	private List<ComponentComponentTypeAssociation>	                associations	           = new ArrayList<ComponentComponentTypeAssociation>();

	/**
	 * this map is for the unique names for the c++ variables, these variable
	 * names are used in setNameGen() function
	 */
	private final Map<String, Integer>	                            variableNames	           = new HashMap<String, Integer>();

	/**
	 * This map keeps the componenttype paths as key and their names as value.
	 * This is used for resource allocation and keeping only 1 instance for the
	 * multiple usage of the same componentType
	 */
	private final Map<String, String>	                            uniqueComponentTypePaths	= new HashMap<String, String>();
	private final TreeSet<String>	                                uniqueImplHeaders	       = new TreeSet<String>();

	private CPPModelProvider	                                    cppModelProvider;

	// constructor ---------------------------------------------------
	public SCAModelToSCAMirrorModelConverter (CPPModelProvider aCppModelProvider) {
		cppModelProvider = aCppModelProvider;
		applicationName = Trengen.getInstance().getApplicationNameUpperCase();
	}

	// initialize method ---------------------------------------------
	public void initialize() {
		ContributionVisitor visitor = new ContributionVisitor() {
			/* (non-Javadoc)
			 * @see org.trentino.trengen.tools.scavalidation.ContributionVisitor#visit(org.trentino.trengen.sca.model.ComponentReference)
			 */
			@Override
			public void visit(ComponentReference contract) {
			    handleHeader(contract.getInterface());
			}
			private void handleHeader(JAXBElement<? extends Interface> interface1) {
	            if(interface1==null || interface1.isNil()){
	            	return;
	            }
	            Interface itf = interface1.getValue();
	            if(itf instanceof CPPInterface){
	            	CPPInterface cpp = (CPPInterface) itf;
	            	String h1 = cpp.getHeader();
	            	if(h1!=null){
	            		cpp.setHeader(h1.replace("\\", "/"));
	            	}
	            	h1 = cpp.getCallbackHeader();
	            	if(h1!=null){
	            		cpp.setCallbackHeader(h1.replace("\\", "/"));
	            	}
	            }
	            
            }
			/* (non-Javadoc)
			 * @see org.trentino.trengen.tools.scavalidation.ContributionVisitor#visit(org.trentino.trengen.sca.model.Reference)
			 */
			@Override
			public void visit(Reference contract) {
				handleHeader(contract.getInterface());
			}
			
			/* (non-Javadoc)
			 * @see org.trentino.trengen.tools.scavalidation.ContributionVisitor#visit(org.trentino.trengen.sca.model.ComponentService)
			 */
			@Override
			public void visit(ComponentService contract) {
				handleHeader(contract.getInterface());
			}
			/* (non-Javadoc)
			 * @see org.trentino.trengen.tools.scavalidation.ContributionVisitor#visit(org.trentino.trengen.sca.model.Service)
			 */
			@Override
			public void visit(Service contract) {
				handleHeader(contract.getInterface());
			}
		};
		compositeMirrorWrapperList = this.convertAndGetCompositeWrappers(Trengen.getContributionTypeWrapper());
		contributionType = this.convertAndGetContributionType(Trengen.getContributionTypeWrapper());
		mirrorComponentTypeList = this.getUniqueCommponentTypeList(Trengen.getContributionTypeWrapper());
		associations = this.getAssociations();

	}

	// methods ---------------------------------------------------------
	public List<ReflectionObject> getReflectionObjects() {
		return reflectionObjects;
	}

	public List<CompositeMirrorWrapper> getCompositeMirrorWrapperList() {
		return compositeMirrorWrapperList;
	}

	public org.trentino.trengen.scamodelmirror.ContributionType getContributionType() {
		return contributionType;
	}

	public String getApplicationName() {
		return applicationName;
	}

	public List<org.trentino.trengen.scamodelmirror.ComponentType> getMirrorComponentTypeList() {
		return mirrorComponentTypeList;
	}

	/**
	 * This function returns the associations list
	 */
	public List<ComponentComponentTypeAssociation> getAssociations() {
		return associations;
	}

	/**
	 * This function creates a unique variable name. It checks if there is
	 * already a variable name in the map. If there is one, itincreases the
	 * count number in its value and returns name+value as a string.
	 */
	private String getUniqueVariableName(String name) {
		name = name.replace(":", "");
		name = name.replace(".", "");
		if(variableNames.containsKey(name))
		{
			int count = variableNames.get(name);
			count++;
			variableNames.put(name, count);
			return name + count;
		}
		else
		{
			variableNames.put(name, 1);
			return name;
		}
	}

	/**
	 * This function returns the reflection-reference list of a given
	 * componentType
	 */
	/*
	 * private List<org.trentino.trengen.tools.generation.reflection.Reference>
	 * getReferencesList(ComponentType compType) {
	 * List<org.trentino.trengen.tools.generation.reflection.Reference>
	 * references = new
	 * ArrayList<org.trentino.trengen.tools.generation.reflection.Reference>();
	 * for (int i = 0; i < compType.getServiceOrReferenceOrProperty().size();
	 * i++) {
	 * if(compType.getServiceOrReferenceOrProperty().get(i).getClass().equals
	 * (ComponentTypeReference.class)) { ComponentTypeReference compTypeRef =
	 * (ComponentTypeReference)
	 * compType.getServiceOrReferenceOrProperty().get(i);
	 * org.trentino.trengen.tools.generation.reflection.Reference ref = new
	 * org.trentino.trengen.tools.generation.reflection.Reference();
	 * if(compTypeRef
	 * .getInterface().getValue().getClass().equals(CPPInterface.class)) {
	 * CPPInterface cppInterface = (CPPInterface)
	 * compTypeRef.getInterface().getValue();
	 * ref.setReferenceInterfaceHeader(cppInterface.getHeader()); String
	 * className = ((CPPInterface)
	 * compTypeRef.getInterface().getValue()).getClazz();
	 * className = className.replace(" ", "");
	 * ref.setInterfaceClassNamespacesSemicolonSeperated(className);
	 * if(className.contains("::")) { int index = className.lastIndexOf("::");
	 * className = className.substring(index + 2); }
	 * ref.setReferenceInterfaceClass(className); }
	 * ref.setReferenceName(compTypeRef.getName());
	 * if(compTypeRef.getMultiplicity().equals("0..n") ||
	 * compTypeRef.getMultiplicity().equals("1..n")) {
	 * ref.setMultiplictyBiggerThanOne(true); } else {
	 * ref.setMultiplictyBiggerThanOne(false); } references.add(ref); } } return
	 * references; }
	 */

	/**
	 * This function returns the reflection-service list of a given
	 * componentType
	 */
	/*
	 * private List<org.trentino.trengen.tools.generation.reflection.Service>
	 * getServicesList(ComponentType compType) {
	 * List<org.trentino.trengen.tools.generation.reflection.Service> services =
	 * new
	 * ArrayList<org.trentino.trengen.tools.generation.reflection.Service>();
	 * for (int i = 0; i < compType.getServiceOrReferenceOrProperty().size();
	 * i++) {
	 * if(compType.getServiceOrReferenceOrProperty().get(i).getClass().equals
	 * (ComponentService.class)) { ComponentService compTypeService =
	 * (ComponentService) compType.getServiceOrReferenceOrProperty().get(i);
	 * org.trentino.trengen.tools.generation.reflection.Service service = new
	 * org.trentino.trengen.tools.generation.reflection.Service();
	 * if(compTypeService
	 * .getInterface().getValue().getClass().equals(CPPInterface.class)) {
	 * service.setServiceInterfaceHeader(((CPPInterface)
	 * compTypeService.getInterface().getValue()).getHeader()); String className
	 * = ((CPPInterface) compTypeService.getInterface().getValue()).getClazz();
	 * service.setServiceInterfaceClass(className); }
	 * service.setServiceName(compTypeService.getName()); services.add(service);
	 * } } return services; }
	 */

	/**
	 * handlePolicySets is an overloaded function for CPPFunction,
	 * CPPImplementationFunction, CPPInterface, CPPImplementation, Callback,
	 * Binding, Service, Reference, ComponentService, ComponentReference.
	 * Takes 2 arguments; one is reference for the SCA Model object and other is
	 * reference for the SCA Mirror Model objects. Converts the SCA Model
	 * PolicySets to SCA Mirror Model PolicySets.
	 */
	private void handlePolicySets(CPPFunction func, org.trentino.trengen.scamodelmirror.CPPFunction mirrorFunc) {
		if(null != func.getPolicySets())
		{
			List<javax.xml.namespace.QName> servicePsList = func.getPolicySets();
			for (javax.xml.namespace.QName ps : servicePsList)
			{
				mirrorFunc.policySets().add(new QName(ps.getLocalPart(), ps.getNamespaceURI(), ps.getPrefix())); // policy sets
			}
		}
	}

	/**
	 * handleRequiresOrPolicySetAttachment is an overloaded function for
	 * CPPFunction, CPPImplementationFunction, CPPInterface, CPPImplementation,
	 * Callback, Binding, Service, Reference, ComponentService,
	 * ComponentReference.
	 * Takes 2 arguments; one is reference for the SCA Model object and other is
	 * reference for the SCA Mirror Model objects. Converts the SCA Model
	 * Requires and PolicySetAttachments to SCA Mirror Model Requires and
	 * PolicySetAttachments.
	 */
	private void handleRequiresOrPolicySetAttachment(CPPFunction func, org.trentino.trengen.scamodelmirror.CPPFunction mirrorFunc,
	        String currentParentName) {
		if(null != func.getRequiresOrPolicySetAttachment())
		{
			for (int k = 0; k < func.getRequiresOrPolicySetAttachment().size(); k++)
			{
				if(func.getRequiresOrPolicySetAttachment().get(k).getClass().equals(Requires.class))
				{
					Requires require = (Requires) func.getRequiresOrPolicySetAttachment().get(k);

					org.trentino.trengen.scamodelmirror.Requires mirrorRequires = new org.trentino.trengen.scamodelmirror.Requires();
					mirrorRequires.setNameGen(getUniqueVariableName(currentParentName + "Requires"));

					if(null != require.getIntents())
					{
						List<javax.xml.namespace.QName> intentList = require.getIntents();
						for (javax.xml.namespace.QName intent : intentList)
						{
							mirrorRequires.intents().add(new QName(intent.getLocalPart(), intent.getNamespaceURI(), intent.getPrefix()));
						}
					}

					mirrorFunc.requiresElements().add(mirrorRequires); // requires
				}

				else if(func.getRequiresOrPolicySetAttachment().get(k).getClass().equals(PolicySetAttachment.class))
				{
					PolicySetAttachment psa = (PolicySetAttachment) func.getRequiresOrPolicySetAttachment().get(k);
					mirrorFunc.policySetAttachmentElements().add(convertPolicySetAttachment(psa, currentParentName)); // policy
					                                                                                                  // set
					                                                                                                  // attachments
				}
			}
		}
	}

	private void handlePolicySets(CPPImplementationFunction func, org.trentino.trengen.scamodelmirror.CPPImplementationFunction mirrorFunc) {
		if(null != func.getPolicySets())
		{
			List<javax.xml.namespace.QName> servicePsList = func.getPolicySets();
			for (javax.xml.namespace.QName ps : servicePsList)
			{
				mirrorFunc.policySets().add(new QName(ps.getLocalPart(), ps.getNamespaceURI(), ps.getPrefix())); // policy sets
			}
		}
	}

	private void handleRequiresOrPolicySetAttachment(CPPImplementationFunction func,
	        org.trentino.trengen.scamodelmirror.CPPImplementationFunction mirrorFunc, String currentParentName) {
		if(null != func.getRequiresOrPolicySetAttachment())
		{
			for (int k = 0; k < func.getRequiresOrPolicySetAttachment().size(); k++)
			{
				if(func.getRequiresOrPolicySetAttachment().get(k).getClass().equals(Requires.class))
				{
					Requires require = (Requires) func.getRequiresOrPolicySetAttachment().get(k);

					org.trentino.trengen.scamodelmirror.Requires mirrorRequires = new org.trentino.trengen.scamodelmirror.Requires();

					mirrorRequires.setNameGen(getUniqueVariableName(currentParentName + "Requires"));
					if(null != require.getIntents())
					{
						List<javax.xml.namespace.QName> intentList = require.getIntents();
						for (javax.xml.namespace.QName intent : intentList)
						{
							mirrorRequires.intents().add(new QName(intent.getLocalPart(), intent.getNamespaceURI(), intent.getPrefix()));
						}
					}

					mirrorFunc.requiresElements().add(mirrorRequires); // requires
				}

				else if(func.getRequiresOrPolicySetAttachment().get(k).getClass().equals(PolicySetAttachment.class))
				{
					PolicySetAttachment psa = (PolicySetAttachment) func.getRequiresOrPolicySetAttachment().get(k);
					mirrorFunc.policySetAttachmentElements().add(convertPolicySetAttachment(psa, currentParentName)); // policy
					                                                                                                  // set
					                                                                                                  // attachments
				}
			}
		}
	}

	private void handlePolicySets(CPPInterface cppInterface, org.trentino.trengen.scamodelmirror.CPPInterface mirrorCPPInterface) {
		if(null != cppInterface.getPolicySets())
		{
			List<javax.xml.namespace.QName> servicePsList = cppInterface.getPolicySets();
			for (javax.xml.namespace.QName ps : servicePsList)
			{
				mirrorCPPInterface.policySets().add(new QName(ps.getLocalPart(), ps.getNamespaceURI(), ps.getPrefix())); // policy sets
			}
		}
	}

	private void handleRequiresOrPolicySetAttachment(CPPInterface cppInterface, org.trentino.trengen.scamodelmirror.CPPInterface mirrorCPPInterface,
	        String currentParentName) {
		if(null != cppInterface.getRequiresOrPolicySetAttachment())
		{
			for (int k = 0; k < cppInterface.getRequiresOrPolicySetAttachment().size(); k++)
			{
				if(cppInterface.getRequiresOrPolicySetAttachment().get(k).getClass().equals(Requires.class))
				{
					Requires require = (Requires) cppInterface.getRequiresOrPolicySetAttachment().get(k);

					org.trentino.trengen.scamodelmirror.Requires mirrorRequires = new org.trentino.trengen.scamodelmirror.Requires();
					mirrorRequires.setNameGen(getUniqueVariableName(currentParentName + "Requires"));
					if(null != require.getIntents())
					{
						List<javax.xml.namespace.QName> intentList = require.getIntents();
						for (javax.xml.namespace.QName intent : intentList)
						{
							mirrorRequires.intents().add(new QName(intent.getLocalPart(), intent.getNamespaceURI(), intent.getPrefix()));
						}
					}

					mirrorCPPInterface.requiresElements().add(mirrorRequires); // requires
				}

				else if(cppInterface.getRequiresOrPolicySetAttachment().get(k).getClass().equals(PolicySetAttachment.class))
				{
					PolicySetAttachment psa = (PolicySetAttachment) cppInterface.getRequiresOrPolicySetAttachment().get(k);
					mirrorCPPInterface.policySetAttachmentElements().add(convertPolicySetAttachment(psa, currentParentName)); // policy
					                                                                                                          // set
					// attachments
				}
			}
		}
	}

	private void handlePolicySets(CPPImplementation cppImplementation, org.trentino.trengen.scamodelmirror.CPPImplementation mirrorCPPImplementation) {
		if(null != cppImplementation.getPolicySets())
		{
			List<javax.xml.namespace.QName> servicePsList = cppImplementation.getPolicySets();
			for (javax.xml.namespace.QName ps : servicePsList)
			{
				mirrorCPPImplementation.policySets().add(new QName(ps.getLocalPart(), ps.getNamespaceURI(), ps.getPrefix())); // policy sets
			}
		}
	}

	private void handleRequiresOrPolicySetAttachment(CPPImplementation cppImplementation,
	        org.trentino.trengen.scamodelmirror.CPPImplementation mirrorCPPImplementation, String currentParentName) {
		if(null != cppImplementation.getRequiresOrPolicySetAttachment())
		{
			for (int k = 0; k < cppImplementation.getRequiresOrPolicySetAttachment().size(); k++)
			{
				if(cppImplementation.getRequiresOrPolicySetAttachment().get(k).getClass().equals(Requires.class))
				{
					Requires require = (Requires) cppImplementation.getRequiresOrPolicySetAttachment().get(k);

					org.trentino.trengen.scamodelmirror.Requires mirrorRequires = new org.trentino.trengen.scamodelmirror.Requires();
					mirrorRequires.setNameGen(getUniqueVariableName(currentParentName + "Requires"));
					if(null != require.getIntents())
					{
						List<javax.xml.namespace.QName> intentList = require.getIntents();
						for (javax.xml.namespace.QName intent : intentList)
						{
							mirrorRequires.intents().add(new QName(intent.getLocalPart(), intent.getNamespaceURI(), intent.getPrefix()));
						}
					}

					mirrorCPPImplementation.requiresElements().add(mirrorRequires); // requires
				}

				else if(cppImplementation.getRequiresOrPolicySetAttachment().get(k).getClass().equals(PolicySetAttachment.class))
				{
					PolicySetAttachment psa = (PolicySetAttachment) cppImplementation.getRequiresOrPolicySetAttachment().get(k);
					mirrorCPPImplementation.policySetAttachmentElements().add(convertPolicySetAttachment(psa, currentParentName)); // policy
					                                                                                                               // set
					// attachments
				}
			}
		}
	}

	private void handlePolicySets(Callback callback, org.trentino.trengen.scamodelmirror.Callback mirrorCallback) {
		if(null != callback.getPolicySets())
		{
			List<javax.xml.namespace.QName> servicePsList = callback.getPolicySets();
			for (javax.xml.namespace.QName ps : servicePsList)
			{
				mirrorCallback.policySets().add(new QName(ps.getLocalPart(), ps.getNamespaceURI(), ps.getPrefix())); // policy sets
			}
		}
	}

	private void handleRequiresOrPolicySetAttachment(Callback callback, org.trentino.trengen.scamodelmirror.Callback mirrorCallback,
	        String currentParentName) {
		if(null != callback.getBindingOrRequiresOrPolicySetAttachment())
		{
			for (int j = 0; j < callback.getBindingOrRequiresOrPolicySetAttachment().size(); j++)
			{
				if(callback.getBindingOrRequiresOrPolicySetAttachment().get(j).getClass().equals(Binding.class))
				{
					JAXBElement<? extends Binding> b = (JAXBElement<? extends Binding>) callback.getBindingOrRequiresOrPolicySetAttachment().get(j);
					mirrorCallback.bindingElements().add(convertBinding(b));
				}

				else if(callback.getBindingOrRequiresOrPolicySetAttachment().get(j).getClass().equals(Requires.class))
				{
					Requires require = (Requires) callback.getBindingOrRequiresOrPolicySetAttachment().get(j);

					org.trentino.trengen.scamodelmirror.Requires mirrorRequires = new org.trentino.trengen.scamodelmirror.Requires();
					mirrorRequires.setNameGen(getUniqueVariableName(currentParentName + "Requires"));
					if(null != require.getIntents())
					{
						List<javax.xml.namespace.QName> intentList = require.getIntents();
						for (javax.xml.namespace.QName intent : intentList)
						{
							mirrorRequires.intents().add(new QName(intent.getLocalPart(), intent.getNamespaceURI(), intent.getPrefix()));
						}
					}

					mirrorCallback.requiresElements().add(mirrorRequires);
				}

				else if(callback.getBindingOrRequiresOrPolicySetAttachment().get(j).getClass().equals(PolicySetAttachment.class))
				{
					PolicySetAttachment psa = (PolicySetAttachment) callback.getBindingOrRequiresOrPolicySetAttachment().get(j);
					mirrorCallback.policySetAttachmentElements().add(convertPolicySetAttachment(psa, currentParentName));
				}
			}
		}
	}

	private void handlePolicySets(JAXBElement<? extends Binding> binding, org.trentino.trengen.scamodelmirror.Binding mirrorBinding) {
		if(null != binding.getValue().getPolicySets())
		{
			List<javax.xml.namespace.QName> psList = binding.getValue().getPolicySets();
			for (javax.xml.namespace.QName ps : psList)
			{
				mirrorBinding.policySets().add(new QName(ps.getLocalPart(), ps.getNamespaceURI(), ps.getPrefix()));
			}
		}
	}

	private void handleRequiresOrPolicySetAttachment(JAXBElement<? extends Binding> binding,
	        org.trentino.trengen.scamodelmirror.Binding mirrorBinding, String currentParentName) {
		if(null != binding.getValue().getPolicySetAttachment())
		{
			List<PolicySetAttachment> psaList = binding.getValue().getPolicySetAttachment();
			for (PolicySetAttachment psa : psaList)
			{
				mirrorBinding.policySetAttachmentElements().add(convertPolicySetAttachment(psa, currentParentName));
			}
		}

		if(null != binding.getValue().getRequires())
		{
			List<javax.xml.namespace.QName> requireList = binding.getValue().getRequires();
			for (javax.xml.namespace.QName require : requireList)
			{
				mirrorBinding.requires().add(new QName(require.getLocalPart(), require.getNamespaceURI(), require.getPrefix()));
			}
		}
	}

	private void handleSCARequires(JAXBElement<? extends Binding> binding, org.trentino.trengen.scamodelmirror.Binding mirrorBinding,
	        String currentParentName) {
		if(null != binding.getValue().getSCARequires())
		{
			List<Requires> scaRequireList = binding.getValue().getSCARequires();
			for (Requires require : scaRequireList)
			{
				org.trentino.trengen.scamodelmirror.Requires mirrorRequires = new org.trentino.trengen.scamodelmirror.Requires();
				mirrorRequires.setNameGen(getUniqueVariableName(currentParentName + "SCARequires"));
				if(null != require.getIntents())
				{
					List<javax.xml.namespace.QName> intentList = require.getIntents();
					for (javax.xml.namespace.QName intent : intentList)
					{
						mirrorRequires.intents().add(new QName(intent.getLocalPart(), intent.getNamespaceURI(), intent.getPrefix()));
					}
				}
				mirrorBinding.scaRequiresElements().add(mirrorRequires);
			}
		}
	}

	private void handlePolicySets(Service service, org.trentino.trengen.scamodelmirror.Service mirrorService) {
		if(null != service.getPolicySets())
		{
			List<javax.xml.namespace.QName> servicePsList = service.getPolicySets();
			for (javax.xml.namespace.QName ps : servicePsList)
			{
				mirrorService.policySets().add(new QName(ps.getLocalPart(), ps.getNamespaceURI(), ps.getPrefix())); // policy set
			}
		}
	}

	private void handleRequiresOrPolicySetAttachment(Service service, org.trentino.trengen.scamodelmirror.Service mirrorService,
	        String currentParentName) {
		if(null != service.getPolicySetAttachment())
		{
			List<PolicySetAttachment> psaList = service.getPolicySetAttachment();
			for (PolicySetAttachment psa : psaList)
			{
				mirrorService.policySetAttachmentElements().add(convertPolicySetAttachment(psa, currentParentName)); // policy
				                                                                                                     // set
				                                                                                                     // attachment
			}
		}

		if(null != service.getRequires())
		{
			List<javax.xml.namespace.QName> requireList = service.getRequires();
			for (javax.xml.namespace.QName require : requireList)
			{
				mirrorService.requires().add(new QName(require.getLocalPart(), require.getNamespaceURI(), require.getPrefix())); // requires
			}
		}
	}

	private void handleSCARequires(Service service, org.trentino.trengen.scamodelmirror.Service mirrorService, String currentParentName) {
		if(null != service.getSCARequires())
		{
			List<Requires> scaRequireList = service.getSCARequires();
			for (Requires require : scaRequireList)
			{
				org.trentino.trengen.scamodelmirror.Requires mirrorRequires = new org.trentino.trengen.scamodelmirror.Requires();
				mirrorRequires.setNameGen(getUniqueVariableName(currentParentName + "SCARequires"));
				if(null != require.getIntents())
				{
					List<javax.xml.namespace.QName> intentList = require.getIntents();
					for (javax.xml.namespace.QName intent : intentList)
					{
						mirrorRequires.intents().add(new QName(intent.getLocalPart(), intent.getNamespaceURI(), intent.getPrefix()));
					}
				}
				mirrorService.scaRequiresElements().add(mirrorRequires); // sca
				                                                         // requires
				                                                         // elements
			}
		}
	}

	private void handlePolicySets(Reference reference, org.trentino.trengen.scamodelmirror.Reference mirrorReference) {
		if(null != reference.getPolicySets())
		{
			List<javax.xml.namespace.QName> servicePsList = reference.getPolicySets();
			for (javax.xml.namespace.QName ps : servicePsList)
			{
				mirrorReference.policySets().add(new QName(ps.getLocalPart(), ps.getNamespaceURI(), ps.getPrefix())); // policy set
			}
		}
	}

	private void handleRequiresOrPolicySetAttachment(Reference reference, org.trentino.trengen.scamodelmirror.Reference mirrorReference,
	        String currentParentName) {
		if(null != reference.getPolicySetAttachment())
		{
			List<PolicySetAttachment> psaList = reference.getPolicySetAttachment();
			for (PolicySetAttachment psa : psaList)
			{
				mirrorReference.policySetAttachmentElements().add(convertPolicySetAttachment(psa, currentParentName)); // policy
				                                                                                                       // set
				                                                                                                       // attachment
			}
		}

		if(null != reference.getRequires())
		{
			List<javax.xml.namespace.QName> requireList = reference.getRequires();
			for (javax.xml.namespace.QName require : requireList)
			{
				mirrorReference.requires().add(new QName(require.getLocalPart(), require.getNamespaceURI(), require.getPrefix())); // requires
			}
		}
	}

	private void handleSCARequires(Reference reference, org.trentino.trengen.scamodelmirror.Reference mirrorReference, String currentParentName) {
		if(null != reference.getSCARequires())
		{
			List<Requires> scaRequireList = reference.getSCARequires();
			for (Requires require : scaRequireList)
			{
				org.trentino.trengen.scamodelmirror.Requires mirrorRequires = new org.trentino.trengen.scamodelmirror.Requires();
				mirrorRequires.setNameGen(getUniqueVariableName(currentParentName + "SCARequires"));
				if(null != require.getIntents())
				{
					List<javax.xml.namespace.QName> intentList = require.getIntents();
					for (javax.xml.namespace.QName intent : intentList)
					{
						mirrorRequires.intents().add(new QName(intent.getLocalPart(), intent.getNamespaceURI(), intent.getPrefix()));
					}
				}
				mirrorReference.scaRequiresElements().add(mirrorRequires); // sca
				                                                           // requires
				                                                           // elements
			}
		}
	}

	private void handlePolicySets(ComponentService service, org.trentino.trengen.scamodelmirror.ComponentService mirrorService) {
		if(null != service.getPolicySets())
		{
			List<javax.xml.namespace.QName> servicePsList = service.getPolicySets();
			for (javax.xml.namespace.QName ps : servicePsList)
			{
				mirrorService.policySets().add(new QName(ps.getLocalPart(), ps.getNamespaceURI(), ps.getPrefix())); // policy set
			}
		}
	}

	private void handleRequiresOrPolicySetAttachment(ComponentService service, org.trentino.trengen.scamodelmirror.ComponentService mirrorService,
	        String currentParentName) {
		if(null != service.getPolicySetAttachment())
		{
			List<PolicySetAttachment> psaList = service.getPolicySetAttachment();
			for (PolicySetAttachment psa : psaList)
			{
				mirrorService.policySetAttachmentElements().add(convertPolicySetAttachment(psa, currentParentName)); // policy
				                                                                                                     // set
				                                                                                                     // attachment
			}
		}

		if(null != service.getRequires())
		{
			List<javax.xml.namespace.QName> requireList = service.getRequires();
			for (javax.xml.namespace.QName require : requireList)
			{
				mirrorService.requires().add(new QName(require.getLocalPart(), require.getNamespaceURI(), require.getPrefix())); // requires
			}
		}
	}

	private void handleSCARequires(ComponentService service, org.trentino.trengen.scamodelmirror.ComponentService mirrorService,
	        String currentParentName) {
		if(null != service.getSCARequires())
		{
			List<Requires> scaRequireList = service.getSCARequires();
			for (Requires require : scaRequireList)
			{
				org.trentino.trengen.scamodelmirror.Requires mirrorRequires = new org.trentino.trengen.scamodelmirror.Requires();
				mirrorRequires.setNameGen(getUniqueVariableName(currentParentName + "SCARequires"));
				if(null != require.getIntents())
				{
					List<javax.xml.namespace.QName> intentList = require.getIntents();
					for (javax.xml.namespace.QName intent : intentList)
					{
						mirrorRequires.intents().add(new QName(intent.getLocalPart(), intent.getNamespaceURI(), intent.getPrefix()));
					}
				}
				mirrorService.scaRequiresElements().add(mirrorRequires); // sca
				                                                         // requires
				                                                         // elements
			}
		}
	}

	private void handlePolicySets(ComponentReference reference, org.trentino.trengen.scamodelmirror.ComponentReference mirrorReference) {
		if(null != reference.getPolicySets())
		{
			List<javax.xml.namespace.QName> servicePsList = reference.getPolicySets();
			for (javax.xml.namespace.QName ps : servicePsList)
			{
				mirrorReference.policySets().add(new QName(ps.getLocalPart(), ps.getNamespaceURI(), ps.getPrefix())); // policy set
			}
		}
	}

	private void handleSCARequires(ComponentReference reference, org.trentino.trengen.scamodelmirror.ComponentReference mirrorReference,
	        String currentParentName) {
		if(null != reference.getSCARequires())
		{
			List<Requires> scaRequireList = reference.getSCARequires();
			for (Requires require : scaRequireList)
			{
				org.trentino.trengen.scamodelmirror.Requires mirrorRequires = new org.trentino.trengen.scamodelmirror.Requires();
				mirrorRequires.setNameGen(getUniqueVariableName(currentParentName + "SCARequires"));
				if(null != require.getIntents())
				{
					List<javax.xml.namespace.QName> intentList = require.getIntents();
					for (javax.xml.namespace.QName intent : intentList)
					{
						mirrorRequires.intents().add(new QName(intent.getLocalPart(), intent.getNamespaceURI(), intent.getPrefix()));
					}
				}
				mirrorReference.scaRequiresElements().add(mirrorRequires); // sca
				                                                           // requires
				                                                           // elements
			}
		}
	}

	private void handleRequiresOrPolicySetAttachment(ComponentReference reference,
	        org.trentino.trengen.scamodelmirror.ComponentReference mirrorReference, String currentParentName) {
		if(null != reference.getPolicySetAttachment())
		{
			List<PolicySetAttachment> psaList = reference.getPolicySetAttachment();
			for (PolicySetAttachment psa : psaList)
			{
				mirrorReference.policySetAttachmentElements().add(convertPolicySetAttachment(psa, currentParentName)); // policy
				                                                                                                       // set
				                                                                                                       // attachment
			}
		}

		if(null != reference.getRequires())
		{
			List<javax.xml.namespace.QName> requireList = reference.getRequires();
			for (javax.xml.namespace.QName require : requireList)
			{
				mirrorReference.requires().add(new QName(require.getLocalPart(), require.getNamespaceURI(), require.getPrefix())); // requires
			}
		}
	}
	
	/**
	 * Metadata converter
	 */
	private org.trentino.trengen.scamodelmirror.Metadata convertMetadata(Metadata metadata, String currentParentName)
	{
		org.trentino.trengen.scamodelmirror.Metadata metaDataMirror = new org.trentino.trengen.scamodelmirror.Metadata();
		
		List<MetadataStringAttribute> metadataAtts = metadata.getStringAttributes();
		for (MetadataStringAttribute metadataAtt : metadataAtts)
		{
			org.trentino.trengen.scamodelmirror.MetadataStringAttribute metadataAttMirror = new org.trentino.trengen.scamodelmirror.MetadataStringAttribute();
			metadataAttMirror.setName(metadataAtt.getName());
			metadataAttMirror.setValue(metadataAtt.getValue());
			String currentmetadataAttNameGen = getUniqueVariableName(metadataAtt.getName() + "MetaDataAtt");
			metadataAttMirror.setNameGen(currentmetadataAttNameGen);
			metaDataMirror.stringAttributesElements().add(metadataAttMirror);
		}
		String currentmetadataNameGen = getUniqueVariableName(currentParentName + "MetaData");
		metaDataMirror.setNameGen(currentmetadataNameGen);
		return metaDataMirror;
	}

	/**
	 * This function is used for the conversion of an SCA Model CPPInterface to
	 * SCA Mirror Model CPPInterface
	 */
	private org.trentino.trengen.scamodelmirror.CPPInterface convertCPPInterface(CPPInterface cppInterface) {
		org.trentino.trengen.scamodelmirror.CPPInterface mirrorCppInterface = new org.trentino.trengen.scamodelmirror.CPPInterface();

		mirrorCppInterface.setHeader(cppInterface.getHeader().replace("\\", "/")); // header
		String currentCPPInterface = cppInterface.getHeader();
		if(currentCPPInterface.contains("/"))
		{
			int index = currentCPPInterface.lastIndexOf("/");
			currentCPPInterface = currentCPPInterface.substring(index + 1);
		}
		else if(currentCPPInterface.contains("\\"))
		{
			int index = currentCPPInterface.lastIndexOf("\\");
			currentCPPInterface = currentCPPInterface.substring(index + 1);
		}

		currentCPPInterface = getUniqueVariableName(currentCPPInterface + "Interface");
		mirrorCppInterface.setNameGen(currentCPPInterface);

		if(null != cppInterface.getClazz())
		{
			mirrorCppInterface.setClazz(new Name(cppInterface.getClazz())); // class
		}
		if(null != cppInterface.getCallbackClass())
		{
			mirrorCppInterface.setCallbackClass(new Name(cppInterface.getCallbackClass())); // callback class
		}
		if(null != cppInterface.getCallbackHeader())
		{
			mirrorCppInterface.setCallbackHeader(cppInterface.getCallbackHeader()); // callback header
		}
		if(null != cppInterface.isRemotable())
		{
			mirrorCppInterface.setRemotable(cppInterface.isRemotable()); // remotable
		}

		if(cppInterface.getFunction() != null)
		{
			List<CPPFunction> funtions = cppInterface.getFunction();
			for (int j = 0; j < funtions.size(); j++)
			{
				CPPFunction func = funtions.get(j);
				org.trentino.trengen.scamodelmirror.CPPFunction mirrorFunc = new org.trentino.trengen.scamodelmirror.CPPFunction();
				if(null != func.isExclude())
				{
					mirrorFunc.setExclude(func.isExclude());
				}
				if(null != func.isOneWay())
				{
					mirrorFunc.setOneWay(func.isOneWay());
				}
				if(null != func.getName())
				{
					mirrorFunc.setName(new NCName(func.getName()));
				}

				mirrorFunc.setNameGen(getUniqueVariableName(func.getName() + "Func"));

				handlePolicySets(func, mirrorFunc);
				handleRequiresOrPolicySetAttachment(func, mirrorFunc, func.getName());

				mirrorCppInterface.functionElements().add(mirrorFunc); // functionElements
			}
		}

		if(null != cppInterface.getCallbackFunction())
		{
			List<CPPFunction> callbackfuntions = cppInterface.getCallbackFunction();

			for (int j = 0; j < callbackfuntions.size(); j++)
			{
				CPPFunction func = callbackfuntions.get(j);
				org.trentino.trengen.scamodelmirror.CPPFunction mirrorFunc = new org.trentino.trengen.scamodelmirror.CPPFunction();
				if(null != func.isExclude())
				{
					mirrorFunc.setExclude(func.isExclude());
				}
				if(null != func.isOneWay())
				{
					mirrorFunc.setOneWay(func.isOneWay());
				}
				if(null != func.getName())
				{
					mirrorFunc.setName(new NCName(func.getName()));
				}

				mirrorFunc.setNameGen(getUniqueVariableName(func.getName() + "Func"));

				handlePolicySets(func, mirrorFunc);
				handleRequiresOrPolicySetAttachment(func, mirrorFunc, func.getName());

				mirrorCppInterface.callbackFunctionElements().add(mirrorFunc); // callback
				                                                               // functionElements
			}
		}

		if(null != cppInterface.getDocumentation())
		{
			List<Documentation> serviceDocList = cppInterface.getDocumentation();
			for (Documentation doc : serviceDocList)
			{
				mirrorCppInterface.documentationElements().add(convertDocumentation(doc, currentCPPInterface)); // documentation
			}
		}

		handlePolicySets(cppInterface, mirrorCppInterface);
		handleRequiresOrPolicySetAttachment(cppInterface, mirrorCppInterface, currentCPPInterface);

		return mirrorCppInterface;
	}

	/**
	 * This function is used for the conversion of an SCA Model
	 * CPPImplementation to SCA Mirror Model CPPImplementation
	 */
	private org.trentino.trengen.scamodelmirror.CPPImplementation convertCPPImplementation(CPPImplementation cppImplementation) {
		org.trentino.trengen.scamodelmirror.CPPImplementation mirrorCPPImplementation = new org.trentino.trengen.scamodelmirror.CPPImplementation();

		if(null != cppImplementation.isAllowsPassByReference())
		{
			mirrorCPPImplementation.setAllowsPassByReference(cppImplementation.isAllowsPassByReference());
		}
		if(null != cppImplementation.getComponentType())
		{
			mirrorCPPImplementation.setComponentType(cppImplementation.getComponentType());
		}
		if(null != cppImplementation.isEagerInit())
		{
			mirrorCPPImplementation.setEagerInit(cppImplementation.isEagerInit());
		}

		if(null != cppImplementation.getHeader())
		{
			mirrorCPPImplementation.setHeader(cppImplementation.getHeader().replace("\\", "/")); // header
		}
		mirrorCPPImplementation.setClazz(new Name(cppImplementation.getClazz())); // class
		String currentCPPVariableName = cppImplementation.getClazz();
		if(currentCPPVariableName.contains("::"))
		{
			int index = currentCPPVariableName.lastIndexOf("::");
			currentCPPVariableName = currentCPPVariableName.substring(index + 2);
		}
		currentCPPVariableName = getUniqueVariableName(currentCPPVariableName + "Implementation");
		mirrorCPPImplementation.setNameGen(currentCPPVariableName);

		if(null != cppImplementation.getLibrary())
		{
			mirrorCPPImplementation.setLibrary(new NCName(cppImplementation.getLibrary()));
		}
		String path = cppImplementation.getPath();
		if(null != path)
		{
			path = path.replace("\\", "/");
			mirrorCPPImplementation.setPath(path);
		}

		if(cppImplementation.getScope() != null)
		{
			org.trentino.trengen.scamodelmirror.CPPImplementationScope mirrorCPPImplementationScope = new org.trentino.trengen.scamodelmirror.CPPImplementationScope(
			        cppImplementation.getScope().value());
			mirrorCPPImplementationScope.setNameGen(getUniqueVariableName(currentCPPVariableName + "Scope"));
			mirrorCPPImplementation.setScope(mirrorCPPImplementationScope);
		}

		if(null != cppImplementation.getFunction())
		{
			List<CPPImplementationFunction> funtions = cppImplementation.getFunction();
			for (int j = 0; j < funtions.size(); j++)
			{
				CPPImplementationFunction func = funtions.get(j);
				org.trentino.trengen.scamodelmirror.CPPImplementationFunction mirrorFunc = new org.trentino.trengen.scamodelmirror.CPPImplementationFunction();
				mirrorFunc.setAllowsPassByReference(Boolean.TRUE.equals(func.isAllowsPassByReference()));

				if(null != func.getName())
				{
					mirrorFunc.setName(new NCName(func.getName()));
				}

				mirrorFunc.setNameGen(getUniqueVariableName(func.getName() + "Func"));
				mirrorFunc.setDestroy(Boolean.TRUE.equals(func.isDestroy()));
				mirrorFunc.setInit(Boolean.TRUE.equals(func.isInit()));

				handlePolicySets(func, mirrorFunc);
				handleRequiresOrPolicySetAttachment(func, mirrorFunc, func.getName());

				mirrorCPPImplementation.functionElements().add(mirrorFunc);
			}
		}

		if(null != cppImplementation.getDocumentation())
		{
			List<Documentation> serviceDocList = cppImplementation.getDocumentation();
			for (Documentation doc : serviceDocList)
			{
				mirrorCPPImplementation.documentationElements().add(convertDocumentation(doc, currentCPPVariableName)); // documentation
			}
		}

		handlePolicySets(cppImplementation, mirrorCPPImplementation);
		handleRequiresOrPolicySetAttachment(cppImplementation, mirrorCPPImplementation, currentCPPVariableName);

		return mirrorCPPImplementation;
	}

	/**
	 * This function is used for the conversion of an SCA Model
	 * SCAImplementation to SCA Mirror Model SCAImplementation
	 */
	private org.trentino.trengen.scamodelmirror.SCAImplementation convertImplementation(SCAImplementation cppImplementation) {
		org.trentino.trengen.scamodelmirror.SCAImplementation mirrorCPPImplementation = new org.trentino.trengen.scamodelmirror.SCAImplementation();

		javax.xml.namespace.QName cppImplementationQname = cppImplementation.getName();
		mirrorCPPImplementation.setName(new QName(cppImplementationQname.getLocalPart(), cppImplementationQname.getNamespaceURI(),
		        cppImplementationQname.getPrefix()));
		String uniqueVarName = getUniqueVariableName(cppImplementationQname.getLocalPart() + "Impl");
		mirrorCPPImplementation.setNameGen(uniqueVarName);
		if(null != cppImplementation.getDocumentation())
		{
			List<Documentation> serviceDocList = cppImplementation.getDocumentation();
			for (Documentation doc : serviceDocList)
			{
				mirrorCPPImplementation.documentationElements().add(convertDocumentation(doc, uniqueVarName)); // documentation
			}
		}

		return mirrorCPPImplementation;
	}

	/**
	 * This function is used for the conversion of an SCA Model
	 * PolicySetAttachment to SCA Mirror Model PolicySetAttachment
	 */
	private org.trentino.trengen.scamodelmirror.PolicySetAttachment convertPolicySetAttachment(PolicySetAttachment psa, String currentParentName) {
		org.trentino.trengen.scamodelmirror.PolicySetAttachment mirrorPsa = new org.trentino.trengen.scamodelmirror.PolicySetAttachment();
		if(psa.getName() != null)
		{
			javax.xml.namespace.QName psaQname = psa.getName();
			mirrorPsa.setName(new QName(psaQname.getLocalPart(), psaQname.getNamespaceURI(), psaQname.getPrefix()));
			mirrorPsa.setNameGen(getUniqueVariableName(psaQname.toString() + "PolicySetAtt"));
		}
		else
		{
			mirrorPsa.setNameGen(getUniqueVariableName(currentParentName + "PolicySetAtt"));
		}
		return mirrorPsa;
	}

	/**
	 * This function is used for the conversion of an SCA Model Documentation to
	 * SCA Mirror Model Documentation
	 */
	private org.trentino.trengen.scamodelmirror.Documentation convertDocumentation(Documentation doc, String currentParentName) {
		org.trentino.trengen.scamodelmirror.Documentation mirrorDocumentation = new org.trentino.trengen.scamodelmirror.Documentation();
		mirrorDocumentation.setNameGen(getUniqueVariableName(currentParentName + "Documentation"));
		if(null != doc.getLang())
		{
			mirrorDocumentation.setLang(doc.getLang());
		}
		return mirrorDocumentation;
	}

	/**
	 * This function is used for the conversion of an SCA Model Callback to SCA
	 * Mirror Model Callback
	 */
	private org.trentino.trengen.scamodelmirror.Callback convertCallback(Callback callback, String currentParentName) {
		org.trentino.trengen.scamodelmirror.Callback mirrorCallback = new org.trentino.trengen.scamodelmirror.Callback();
		mirrorCallback.setNameGen(getUniqueVariableName(currentParentName + "Callback"));

		handleRequiresOrPolicySetAttachment(callback, mirrorCallback, currentParentName + "Callback");
		handlePolicySets(callback, mirrorCallback);

		if(null != callback.getDocumentation())
		{
			List<Documentation> callbackDocList = callback.getDocumentation();
			for (Documentation doc : callbackDocList)
			{
				mirrorCallback.documentationElements().add(convertDocumentation(doc, currentParentName + "Callback"));
			}
		}

		return mirrorCallback;
	}

	/**
	 * This function is used for the conversion of an SCA Model Binding to SCA
	 * Mirror Model Binding
	 */
	private org.trentino.trengen.scamodelmirror.Binding convertBinding(JAXBElement<? extends Binding> binding) {
		Binding bindingTemp = binding.getValue();
		org.trentino.trengen.scamodelmirror.Binding mirrorBinding = null;
		if(bindingTemp.getClass().equals(SCABinding.class))
		{
			mirrorBinding = new org.trentino.trengen.scamodelmirror.SCABinding();
			SCABinding scaBinding = (SCABinding) bindingTemp;
			
			/*
			 * In order to handle default binding.sca without uri (for service discovery), we added this
			 * fake target in  returnNumberOfTargets() @ReferenceTarget.cpp while checking multiplicity.
			 * We deleted this fake target in order not to see this fake target in generated ModelLoader file.
			 * 
			 * TODO: port and uri members of ReferenceServiceInterface class should be avoided.
			 * But currently the validation is done during the generation for binding and its relying
			 * on these members.
			 * 
			 * We did not want to disturb the whole binding code structure.
			 * 08.05.2013: fake uri is kept, because runtime also needs it.
			 */
			//if (scaBinding.getUri().equals("tcp://localhost:1234//dontUseThisName_FakeTarget"))
			//{
			//	((org.trentino.trengen.scamodelmirror.SCABinding) mirrorBinding).setUri(null);
			//}
			
			//else if(scaBinding.getUri() != null)
			//{
				((org.trentino.trengen.scamodelmirror.SCABinding) mirrorBinding).setUri(new AnyURI(scaBinding.getUri()));
			//}
			
		}
		else if(bindingTemp.getClass().equals(IPCBinding.class))
		{
			mirrorBinding = new org.trentino.trengen.scamodelmirror.IPCBinding();
			IPCBinding ipcBinding = (IPCBinding) bindingTemp;
			if(ipcBinding.getUri() != null)
			{
				((org.trentino.trengen.scamodelmirror.IPCBinding) mirrorBinding).setUri(new AnyURI(ipcBinding.getUri()));
			}
		}
		else
		{
			mirrorBinding = new org.trentino.trengen.scamodelmirror.Binding();

			if(null != binding.getValue().getName())
			{
				mirrorBinding.setName(new NCName(binding.getValue().getName()));
			}

			if(null != binding.getValue().getUri())
			{
				mirrorBinding.setUri(new AnyURI(binding.getValue().getUri()));
			}
		}
		String bindingName = binding.getValue().getName() != null ? binding.getValue().getName() + "Binding" : "Binding";
		mirrorBinding.setNameGen(getUniqueVariableName(bindingName));

		handlePolicySets(binding, mirrorBinding);
		handleRequiresOrPolicySetAttachment(binding, mirrorBinding, bindingName);
		handleSCARequires(binding, mirrorBinding, bindingName);

		if(null != binding.getValue().getDocumentation())
		{
			List<Documentation> docList = binding.getValue().getDocumentation();
			for (Documentation doc : docList)
			{
				mirrorBinding.documentationElements().add(convertDocumentation(doc, bindingName));
			}
		}

		return mirrorBinding;
	}

	/**
	 * This function is used for the conversion of an SCA Model ContributionType
	 * to SCA Mirror Model ContributionType
	 */
	private org.trentino.trengen.scamodelmirror.ContributionType convertAndGetContributionType(ContributionTypeWrapper contributionWrapper) {
		if(contributionWrapper == null)
		{
			return null;
		}
		org.trentino.trengen.scamodelmirror.ContributionType mirrorContribution = new org.trentino.trengen.scamodelmirror.ContributionType();
		ContributionType contribution = contributionWrapper.getContributionType();

		String currentContributionName = getUniqueVariableName("Contribution");
		mirrorContribution.setNameGen(currentContributionName);

		List<Documentation> docList = contribution.getDocumentation();
		for (Documentation doc : docList)
		{
			mirrorContribution.documentationElements().add(convertDocumentation(doc, currentContributionName));
		}

		List<DeployableType> deployables = contribution.getDeployable();

		for (int i = 0; i < deployables.size(); i++)
		{
			DeployableType dp = deployables.get(i);
			org.trentino.trengen.scamodelmirror.DeployableType mirrorDp = new org.trentino.trengen.scamodelmirror.DeployableType();

			javax.xml.namespace.QName dpCompositeQname = dp.getComposite();
			mirrorDp.setComposite(new QName(dpCompositeQname.getLocalPart(), dpCompositeQname.getNamespaceURI(), dpCompositeQname.getPrefix()));
			String currentParentName = getUniqueVariableName("Deployable");
			mirrorDp.setNameGen(currentParentName);

			docList = dp.getDocumentation();
			for (Documentation doc : docList)
			{
				mirrorDp.documentationElements().add(convertDocumentation(doc, currentParentName));
			}

			mirrorContribution.deployableElements().add(mirrorDp);
		}
		
		ImportExport.convertImportsExportsToMirrorModel(contribution,mirrorContribution);

		return mirrorContribution;
	}
	
	

	/**
	 * This function is used for getting all the composite mirror wrapper
	 * objects from the ContributionTypeWrapper object.
	 */
	private List<CompositeMirrorWrapper> convertAndGetCompositeWrappers(ContributionTypeWrapper contributionWrapper) {
		List<CompositeMirrorWrapper> mirrorCompositeWrappers = new ArrayList<CompositeMirrorWrapper>();
		if(contributionWrapper == null)
		{
			return mirrorCompositeWrappers;
		}
		List<CompositeWrapper> composites = contributionWrapper.getListCompositeWrapper();

		for (CompositeWrapper compositeWrapper : composites)
		{
			CompositeMirrorWrapper compositeMirrorWrapper = new CompositeMirrorWrapper();
			Composite composite = compositeWrapper.getComposite();

			convertToServiceInterfaces(compositeWrapper.getComponentServices());

			// The reason why we convert compTypeReferences "firstly" is that if
			// the corresponding componentReference is specified,
			// it is overwritten by the compReference... According to the
			// Spec-page 29, line 875
			convertToServiceInterfaces(compositeWrapper.componentTypeReferences);

			Map<String, ComponentReference> compTypeReferences2 = compositeWrapper.componentReferences;
			convertToServiceInterfaces(compTypeReferences2);

			String uniqueVarName = getUniqueVariableName(composite.getName() + "Composite");
			org.trentino.trengen.scamodelmirror.Composite mirrorComposite = convertComposite(composite, uniqueVarName);

			for (ComponentWrapper componentWrapper : compositeWrapper.getListComponents())
			{
				Component component = componentWrapper.getScaModelComponent();
				ComponentType compType = componentWrapper.getScaModelComponentType();
				String uniqueComponentName = component.getName();
				uniqueComponentName = uniqueComponentName.replace(".", "");
				uniqueComponentName = getUniqueVariableName(uniqueComponentName + "Component");
				mirrorComposite.componentElements().add(convertComponent(component, uniqueComponentName, compType));

				JAXBElement<? extends Implementation> implementation = component.getImplementation();
				if(null != implementation && !implementation.isNil())
				{
					if(implementation.getValue().getClass().equals(CPPImplementation.class))
					{
						CPPImplementation cppImplementation = ((CPPImplementation) implementation.getValue());

						// we can guaranty uniqueness of the componentType just
						// by using the qulified class name
						// since we cannot have two classes with the sa,e
						// qualified name in the same compilation unit
						String className = cppImplementation.getClazz();

						String uniqueComponentTypeVarName = "";

						if(!uniqueComponentTypePaths.containsKey(className))
						{
							String varName = component.getName() + "CompType";
							uniqueComponentTypeVarName = getUniqueVariableName(varName);

							uniqueComponentTypePaths.put(className, uniqueComponentTypeVarName);
							org.trentino.trengen.scamodelmirror.ComponentType mirrorCompType = new org.trentino.trengen.scamodelmirror.ComponentType();
							mirrorCompType = convertComponentType(compType, uniqueComponentTypeVarName);
							mirrorComponentTypeList.add(mirrorCompType);

						}
						else
						{
							uniqueComponentTypeVarName = uniqueComponentTypePaths.get(className);
						}
						ComponentComponentTypeAssociation assoc = new ComponentComponentTypeAssociation(composite.getName() + "_"
						        + uniqueComponentName, uniqueComponentTypeVarName);
						associations.add(assoc);

						String implHeader = cppImplementation.getHeader().replace("\\", "/");

						if(!uniqueImplHeaders.contains(implHeader + "/" + className))
						{
							/**
							 * This for is for reflection
							 */
							ReflectionObject refObject = new ReflectionObject();
							refObject.setImplClassAsNamespace(className);

							String classNameTemp = className.replace("::", "_");
							refObject.setImplClass(classNameTemp);

							refObject.setImplHeader(implHeader);
							refObject.setImplementation(cppImplementation);
							populateReflectionObj(refObject, compType, component);

							reflectionObjects.add(refObject);
							uniqueImplHeaders.add(implHeader + "/" + className);
						}

					}
					else if(implementation.getValue().getClass().equals(SCAImplementation.class))
					{
						SCAImplementation compositeImplementation = (SCAImplementation) implementation.getValue();
						if(compositeImplementation != null)
						{
							String uniqueComponentTypeVarName = component.getName() + "CompTypeOfCompByImp";
							uniqueComponentTypeVarName = getUniqueVariableName(uniqueComponentTypeVarName);

							if(!uniqueComponentTypePaths.containsKey(uniqueComponentTypeVarName))
							{
								uniqueComponentTypePaths.put(uniqueComponentTypeVarName, uniqueComponentTypeVarName);
								org.trentino.trengen.scamodelmirror.ComponentType mirrorCompType = new org.trentino.trengen.scamodelmirror.ComponentType();
								mirrorCompType = convertComponentType(compType, uniqueComponentTypeVarName);
								mirrorComponentTypeList.add(mirrorCompType);
							}
							else
							{
								uniqueComponentTypeVarName = uniqueComponentTypePaths.get(uniqueComponentTypeVarName);
							}

							ComponentComponentTypeAssociation assoc = new ComponentComponentTypeAssociation(composite.getName() + "_"
							        + uniqueComponentName, uniqueComponentTypeVarName);
							associations.add(assoc);

						}
					}
				}

			}
			compositeMirrorWrapper.setNameGen(uniqueVarName + "Wrapper");
			compositeMirrorWrapper.setComposite(mirrorComposite);
			mirrorCompositeWrappers.add(compositeMirrorWrapper);
		}
		return mirrorCompositeWrappers;
	}

	/*
	 * private String resolveComponentTypePath(CPPImplementation cppImplementation) {
	 * String artifactName = cppImplementation.getClazz();
	 * if(artifactName.contains(":")) {
	 * int index = artifactName.lastIndexOf(":");
	 * artifactName = artifactName.substring(index + 1);
	 * }
	 * String componentName = artifactName + ".componentType";
	 * String componentTypePath = cppImplementation.getComponentType(); // path
	 * // to
	 * // the
	 * // componentType
	 * // file
	 * String componentTypePathResolved = componentTypePath;
	 * if((componentTypePath != null) && !componentTypePath.contains(".componentType")) {
	 * componentTypePathResolved = componentTypePath + "//" + componentName;
	 * }
	 * else {
	 * String artifactHeader = cppImplementation.getHeader();
	 * boolean hasRelativePath = false;
	 * if(artifactHeader.contains("/")) {
	 * int index = artifactHeader.lastIndexOf("/");
	 * artifactHeader = artifactHeader.substring(0, index + 1);
	 * hasRelativePath = true;
	 * }
	 * else if(artifactHeader.contains("\\")) {
	 * int index = artifactHeader.lastIndexOf("\\");
	 * artifactHeader = artifactHeader.substring(0, index + 1);
	 * hasRelativePath = true;
	 * }
	 * if(hasRelativePath) {
	 * componentName = artifactHeader + componentName;
	 * }
	 * componentTypePathResolved = componentName;
	 * }
	 * return componentTypePathResolved;
	 * }
	 */

	// this function fills out the reflection objecs used for reflection code
	// generation
	private void populateReflectionObj(ReflectionObject refObject, ComponentType compType, Component component) {
		for (int i = 0; i < compType.getServiceOrReferenceOrProperty().size(); i++)
		{
			if(compType.getServiceOrReferenceOrProperty().get(i).getClass().equals(ComponentTypeReference.class))
			{
				ComponentTypeReference compTypeRef = (ComponentTypeReference) compType.getServiceOrReferenceOrProperty().get(i);
				org.trentino.trengen.tools.generation.reflection.Reference ref = new org.trentino.trengen.tools.generation.reflection.Reference();
				if(compTypeRef.getInterface().getValue().getClass().equals(CPPInterface.class))
				{
					CPPInterface cppInterface = (CPPInterface) compTypeRef.getInterface().getValue();
					ref.setReferenceInterfaceHeader(cppInterface.getHeader());
					String className = ((CPPInterface) compTypeRef.getInterface().getValue()).getClazz();

					className = className.replace(" ", "");
					ref.setInterfaceClassNamespacesSemicolonSeperated(className);

					if(className.contains("::"))
					{
						int index = className.lastIndexOf("::");
						className = className.substring(index + 2);
					}
					ref.setReferenceInterfaceClass(className);
					ref.setNameGen(getUniqueVariableName(className ));
				}
				ref.setReferenceName(compTypeRef.getName());
				if(compTypeRef.getMultiplicity().equals("0..n") || compTypeRef.getMultiplicity().equals("1..n"))
				{
					ref.setMultiplictyBiggerThanOne(true);
				}
				else
				{
					ref.setMultiplictyBiggerThanOne(false);
				}

				refObject.getListReferences().add(ref);
			}
			else if(compType.getServiceOrReferenceOrProperty().get(i).getClass().equals(ComponentService.class))
			{
				ComponentService compTypeService = (ComponentService) compType.getServiceOrReferenceOrProperty().get(i);
				org.trentino.trengen.tools.generation.reflection.Service service = new org.trentino.trengen.tools.generation.reflection.Service();
				if(compTypeService.getInterface().getValue().getClass().equals(CPPInterface.class))
				{
					service.setServiceInterfaceHeader(((CPPInterface) compTypeService.getInterface().getValue()).getHeader());
					String className = ((CPPInterface) compTypeService.getInterface().getValue()).getClazz();
					service.setServiceInterfaceClass(className);
				}
				service.setServiceName(compTypeService.getName());
				refObject.getListServices().add(service);
			}
			else if(compType.getServiceOrReferenceOrProperty().get(i).getClass().equals(Property.class))
			{
				PropertyReflx propReflex = new PropertyReflx();
				Property compTypeProperty = (Property) compType.getServiceOrReferenceOrProperty().get(i);
				propReflex.setPropertyName(compTypeProperty.getName());
				javax.xml.namespace.QName typeCompType = compTypeProperty.getType();
				// javax.xml.namespace.QName elementCompType =
				// compTypeProperty.getElement();
				PropertyValue propertyValue = findMatchingPropertyValue(component, compTypeProperty.getName());
				// prepare the reflection property here to be able to use both
				// component and componentType properties
				if(typeCompType == null)
				{
					if(propertyValue != null && propertyValue.getType() != null)
					{
						propReflex.setType(propertyValue.getType().getLocalPart());
					}
				}
				else
				{
					propReflex.setType(typeCompType.getLocalPart());
				}
				if(compTypeProperty.isMany() == null)
				{
					propReflex.setIsMany(false);
				}
				else
				{
					propReflex.setIsMany(compTypeProperty.isMany());
				}

				refObject.getListProperties().add(propReflex);
			}
		}
	}

	private PropertyValue findMatchingPropertyValue(Component component, String propName) {
		if(component == null)
		{
			logger.error("component object given for property search is null");
			return null;
		}
		int size = component.getServiceOrReferenceOrProperty().size();

		for (int index = 0; index < size; index++)
		{
			if(component.getServiceOrReferenceOrProperty().get(index).getClass().equals(PropertyValue.class))
			{
				PropertyValue propValue = (PropertyValue) component.getServiceOrReferenceOrProperty().get(index);

				String propertyName = propValue.getName();
				if(!propName.equals(propertyName))
				{
					continue;
				}
				return propValue;
			}
		}
		return null;
	}

	private Property findMatchingProperty(ComponentType component, String propName) {
		if(component == null)
		{
			logger.error("component object given for property search is null");
			return null;
		}
		int size = component.getServiceOrReferenceOrProperty().size();

		for (int index = 0; index < size; index++)
		{
			if(component.getServiceOrReferenceOrProperty().get(index).getClass().equals(Property.class))
			{
				Property propValue = (Property) component.getServiceOrReferenceOrProperty().get(index);

				String propertyName = propValue.getName();
				if(!propName.equals(propertyName))
				{
					continue;
				}
				return propValue;
			}
		}
		return null;
	}

	/**
	 * This function is used for collecting services and references into
	 * referenceInterfaces and serviceInterfaces Lists. It takes a Contract and
	 * according to its type (service || reference) it is differentiated.
	 */
	private void convertToServiceInterfaces(Map<String, ? extends Contract> objects) {
		for (Map.Entry<String, ? extends Contract> entry : objects.entrySet())
		{
			Contract entity = entry.getValue();
			JAXBElement<? extends Interface> interface1 = entity.getInterface();
			if(interface1 ==null || interface1.isNil()){
				continue;
			}
			Interface value = interface1.getValue();
			if(entity instanceof ComponentService || entity instanceof ComponentReference)
			{
				if(!(value instanceof CPPInterface))
				{
                  continue;
				}

				ClassModel model = cppModelProvider.getClassModel(entity);
				ReferenceServiceInterface refServiceInterface = new ReferenceServiceInterface(model, entity);
				if(Boolean.TRUE.equals(value.isRemotable()) && (entity instanceof ComponentService) && !((ComponentService)entity).isRemote()){
					remotableServices.add(refServiceInterface);
				}
				if(entity instanceof ComponentService){
				serviceInterfaces.add(refServiceInterface);
				}
				else if ( entity instanceof ComponentReference){
					referenceInterfaces.add(refServiceInterface);
				}
			}
		}
	}



	/**
	 * This function returns the list of mirror ComponentType objects (each
	 * object is unique) The list was populates in the
	 * convertAndGetCompositeWrappers() function.
	 */
	public List<org.trentino.trengen.scamodelmirror.ComponentType> getUniqueCommponentTypeList(ContributionTypeWrapper contributionWrapper) {
		return mirrorComponentTypeList;
	}

	/**
	 * This function converts the Sca Model Composite object to SCA Mirror Model
	 * Composite Object. It takes its uniqueVarName from
	 * convertAndGetCompositeWrappers() function and called from there.
	 * uniqueVarName is used for the unique component_names and their component
	 * type names in Associations Map.
	 */
	private org.trentino.trengen.scamodelmirror.Composite convertComposite(Composite composite, String uniqueVarName) {
		org.trentino.trengen.scamodelmirror.Composite mirrorComposite = new org.trentino.trengen.scamodelmirror.Composite();
		if(composite != null)
		{
			mirrorComposite.setAutowire(composite.isAutowire());
			mirrorComposite.setLocal(composite.isLocal());
			String currentCompositeName = composite.getName();
			mirrorComposite.setName(new NCName(currentCompositeName));

			mirrorComposite.setNameGen(uniqueVarName);

			if(null != composite.getTargetNamespace())
			{
				mirrorComposite.setTargetNamespace(new AnyURI(composite.getTargetNamespace()));
			}

			if(null != composite.getDocumentation())
			{
				List<Documentation> docList = composite.getDocumentation();
				for (Documentation doc : docList)
				{
					mirrorComposite.documentationElements().add(convertDocumentation(doc, currentCompositeName));
				}
			}

			if(null != composite.getInclude())
			{
				List<Include> includes = composite.getInclude();
				for (Include inc : includes)
				{
					org.trentino.trengen.scamodelmirror.Include mirrorInc = new org.trentino.trengen.scamodelmirror.Include();
					String incName = (inc.getName() != null ? inc.getName().getLocalPart() + "Include" : currentCompositeName + "Include");
					mirrorInc.setNameGen(getUniqueVariableName(incName));
					if(null != inc.getName())
					{
						javax.xml.namespace.QName incQname = inc.getName();
						mirrorInc.setName(new QName(incQname.getLocalPart(), incQname.getNamespaceURI(), incQname.getPrefix()));
					}
					if(null != inc.getDocumentation())
					{
						List<Documentation> incList = inc.getDocumentation();
						for (Documentation doc : incList)
						{
							mirrorInc.documentationElements().add(convertDocumentation(doc, incName));
						}
					}

					mirrorComposite.includeElements().add(mirrorInc);
				}
			}

			if(null != composite.getPolicySets())
			{
				List<javax.xml.namespace.QName> psList = composite.getPolicySets();
				for (javax.xml.namespace.QName ps : psList)
				{
					mirrorComposite.policySets().add(new QName(ps.getLocalPart(), ps.getNamespaceURI(), ps.getPrefix()));
				}
			}

			if(composite.getRequiresOrPolicySetAttachmentOrService() != null)
			{
				for (int i = 0; i < composite.getRequiresOrPolicySetAttachmentOrService().size(); i++)
				{
					if(composite.getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Service.class))
					{
						Service service = (Service) composite.getRequiresOrPolicySetAttachmentOrService().get(i);
						org.trentino.trengen.scamodelmirror.Service mirrorService = new org.trentino.trengen.scamodelmirror.Service();

						String currentServiceName = service.getName();
						mirrorService.setName(new NCName(currentServiceName));
						mirrorService.setNameGen(getUniqueVariableName(currentServiceName + "Service"));
						if(null != composite)
						{
							mirrorService.setPromote(new AnyURI(service.getPromote()));
						}
						
						if (null != service.getMetadata())
						{
							mirrorService.setMetadata(convertMetadata(service.getMetadata(), currentServiceName));
						}

						if(service.getInterface() != null)
						{
							mirrorService.setInterface(convertCPPInterface((CPPInterface) service.getInterface().getValue())); // interface
						}

						if(null != service.getBinding())
						{
							for (int j = 0; j < service.getBinding().size(); j++)
							{
								JAXBElement<? extends Binding> binding = service.getBinding().get(j);
								mirrorService.bindingElements().add(convertBinding(binding)); // binding
								                                                              // elements
							}
						}

						if(null != service.getCallback())
						{
							mirrorService.setCallback(convertCallback(service.getCallback(), currentServiceName)); // callback
						}

						if(null != service.getDocumentation())
						{
							List<Documentation> serviceDocList = service.getDocumentation();
							for (Documentation doc : serviceDocList)
							{
								mirrorService.documentationElements().add(convertDocumentation(doc, currentServiceName));
							}
						}

						handlePolicySets(service, mirrorService);
						handleRequiresOrPolicySetAttachment(service, mirrorService, currentServiceName);
						handleSCARequires(service, mirrorService, currentServiceName);

						mirrorComposite.serviceElements().add(mirrorService);
					}
					else if(composite.getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Reference.class))
					{
						Reference reference = (Reference) composite.getRequiresOrPolicySetAttachmentOrService().get(i);
						org.trentino.trengen.scamodelmirror.Reference mirrorReference = new org.trentino.trengen.scamodelmirror.Reference();

						String currentRefName = reference.getName();
						mirrorReference.setName(new NCName(currentRefName));
						mirrorReference.setNameGen(getUniqueVariableName(currentRefName + "Reference"));
						if(null != reference.getPromote())
						{
							List<String> promotes = reference.getPromote();
							for (String promote : promotes)
							{
								mirrorReference.promotes().add(promote);
							}
						}

						if(null != reference.getTarget())
						{
							List<String> targets = reference.getTarget();
							for (String target : targets)
							{
								mirrorReference.targets().add(target);
							}
						}

						if(null != reference.getMultiplicity())
						{
							mirrorReference.setMultiplicity(reference.getMultiplicity());
						}
						mirrorReference.setWiredByImpl(reference.isWiredByImpl());
						
						if (null != reference.getMetadata())
						{
							mirrorReference.setMetadata(convertMetadata(reference.getMetadata(), currentRefName));
						}
						
						if(null != reference.getInterface())
						{
							mirrorReference.setInterface(convertCPPInterface((CPPInterface) reference.getInterface().getValue())); // interface
						}

						if(null != reference.getBinding())
						{
							for (int j = 0; j < reference.getBinding().size(); j++)
							{
								JAXBElement<? extends Binding> binding = reference.getBinding().get(j);
								mirrorReference.bindingElements().add(convertBinding(binding)); // binding
								                                                                // elements
							}
						}

						if(null != reference.getCallback())
						{
							mirrorReference.setCallback(convertCallback(reference.getCallback(), currentRefName)); // callback
						}

						if(null != reference.getDocumentation())
						{
							List<Documentation> serviceDocList = reference.getDocumentation();
							for (Documentation doc : serviceDocList)
							{
								mirrorReference.documentationElements().add(convertDocumentation(doc, currentRefName));
							}
						}

						handlePolicySets(reference, mirrorReference);
						handleRequiresOrPolicySetAttachment(reference, mirrorReference, currentRefName);
						handleSCARequires(reference, mirrorReference, currentRefName);

						mirrorComposite.referenceElements().add(mirrorReference);
					}
					else if(composite.getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Property.class))
					{
						Property property = (Property) composite.getRequiresOrPolicySetAttachmentOrService().get(i);

						mirrorComposite.propertyElements().add(convertProperty(property));
					}
					else if(composite.getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(PolicySetAttachment.class))
					{
						PolicySetAttachment psa = (PolicySetAttachment) composite.getRequiresOrPolicySetAttachmentOrService().get(i);
						mirrorComposite.policySetAttachmentElements().add(convertPolicySetAttachment(psa, currentCompositeName));
					}

					else if(composite.getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Requires.class))
					{
						Requires req = (Requires) composite.getRequiresOrPolicySetAttachmentOrService().get(i);
						org.trentino.trengen.scamodelmirror.Requires mirrorRequires = new org.trentino.trengen.scamodelmirror.Requires();
						mirrorRequires.setNameGen(getUniqueVariableName(currentCompositeName + "Requires"));
						if(null != req.getIntents())
						{
							List<javax.xml.namespace.QName> reqIntents = req.getIntents();
							for (javax.xml.namespace.QName require : reqIntents)
							{
								mirrorRequires.intents().add(new QName(require.getLocalPart(), require.getNamespaceURI(), require.getPrefix()));
							}
							mirrorComposite.requiresElements().add(mirrorRequires);
						}
					}

					else if(composite.getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Wire.class))
					{
						Wire wire = (Wire) composite.getRequiresOrPolicySetAttachmentOrService().get(i);
						org.trentino.trengen.scamodelmirror.Wire mirrorWire = new org.trentino.trengen.scamodelmirror.Wire();

						mirrorWire.setReplace(wire.isReplace());
						if(null != wire.getSource())
						{
							mirrorWire.setSource(new AnyURI(wire.getSource()));
						}
						if(null != wire.getTarget())
						{
							mirrorWire.setTarget(new AnyURI(wire.getTarget()));
						}

						String wireName = currentCompositeName + "_Wire";
						mirrorWire.setNameGen(getUniqueVariableName(wireName));

						if(null != wire.getDocumentation())
						{
							List<Documentation> serviceDocList = wire.getDocumentation();
							for (Documentation doc : serviceDocList)
							{
								mirrorWire.documentationElements().add(convertDocumentation(doc, wireName));
							}
						}

						mirrorComposite.wireElements().add(mirrorWire);
					}
				}
			}
		}
		return mirrorComposite;
	}

	/**
	 * This function converts the SCA Model ComponentService to SCA Mirror Model
	 * ComponentService.
	 */
	private org.trentino.trengen.scamodelmirror.ComponentService convertComponentService(ComponentService service) {
		org.trentino.trengen.scamodelmirror.ComponentService mirrorComponentService = new org.trentino.trengen.scamodelmirror.ComponentService();

		String currentCompService = service.getName();
		mirrorComponentService.setName(new NCName(currentCompService));
		mirrorComponentService.setNameGen(getUniqueVariableName(currentCompService + "ComponentService"));

		if(null != service.getInterface())
		{
			mirrorComponentService.setInterface(convertCPPInterface((CPPInterface) service.getInterface().getValue())); // interface
		}

		if(null != service.getBinding())
		{
			for (int j = 0; j < service.getBinding().size(); j++)
			{
				JAXBElement<? extends Binding> binding = service.getBinding().get(j);
				mirrorComponentService.bindingElements().add(convertBinding(binding)); // binding elements
			}
		}
		
		mirrorComponentService.setRemote(service.isRemote());
		
		if (null != service.getMetadata())
		{
			mirrorComponentService.setMetadata(convertMetadata(service.getMetadata(), currentCompService));
		}

		if(null != service.getCallback())
		{
			mirrorComponentService.setCallback(convertCallback(service.getCallback(), currentCompService)); // callback
		}

		if(null != service.getDocumentation())
		{
			List<Documentation> serviceDocList = service.getDocumentation();
			for (Documentation doc : serviceDocList)
			{
				mirrorComponentService.documentationElements().add(convertDocumentation(doc, currentCompService));
			}
		}

		handlePolicySets(service, mirrorComponentService);
		handleRequiresOrPolicySetAttachment(service, mirrorComponentService, currentCompService);
		handleSCARequires(service, mirrorComponentService, currentCompService);

		return mirrorComponentService;
	}

	/**
	 * This function converts the SCA Model ComponentReference to SCA Mirror
	 * Model ComponentReference.
	 */
	private org.trentino.trengen.scamodelmirror.ComponentReference convertComponentReference(ComponentReference reference) {

		org.trentino.trengen.scamodelmirror.ComponentReference mirrorComponentReference = new org.trentino.trengen.scamodelmirror.ComponentReference();

		String currentRefName = reference.getName();
		mirrorComponentReference.setName(new NCName(currentRefName));
		mirrorComponentReference.setNameGen(getUniqueVariableName(currentRefName + "ComponentRef"));
		if(null != reference.getInterface())
		{
			mirrorComponentReference.setInterface(convertCPPInterface((CPPInterface) reference.getInterface().getValue())); // interface
		}

		if(null != reference.getBinding())
		{
			for (int j = 0; j < reference.getBinding().size(); j++)
			{
				JAXBElement<? extends Binding> binding = reference.getBinding().get(j);
				mirrorComponentReference.bindingElements().add(convertBinding(binding)); // binding elements
			}
		}

		if (null != reference.getMetadata())
		{
			mirrorComponentReference.setMetadata(convertMetadata(reference.getMetadata(), currentRefName));
		}
		
		if(null != reference.getCallback())
		{
			mirrorComponentReference.setCallback(convertCallback(reference.getCallback(), currentRefName)); // callback
		}

		if(null != reference.getDocumentation())
		{
			List<Documentation> serviceDocList = reference.getDocumentation();
			for (Documentation doc : serviceDocList)
			{
				mirrorComponentReference.documentationElements().add(convertDocumentation(doc, currentRefName));
			}
		}
		if(null != reference.getTarget())
		{
			List<String> targets = reference.getTarget();
			for (String target : targets)
			{
				mirrorComponentReference.targets().add(target);
			}
		}

		if(null != reference.isAutowire())
		{
			mirrorComponentReference.setAutowire(reference.isAutowire());
		}
		if(null != reference.getMultiplicity())
		{
			mirrorComponentReference.setMultiplicity(reference.getMultiplicity());
		}
		mirrorComponentReference.setNonOverridable(reference.isNonOverridable());
		mirrorComponentReference.setWiredByImpl(reference.isWiredByImpl());

		handlePolicySets(reference, mirrorComponentReference);
		handleRequiresOrPolicySetAttachment(reference, mirrorComponentReference, currentRefName);
		handleSCARequires(reference, mirrorComponentReference, currentRefName);
		return mirrorComponentReference;
	}

	/**
	 * This function converts the SCA Model ComponentTypeReference to SCA Mirror
	 * Model ComponentTypeReference.
	 */
	private org.trentino.trengen.scamodelmirror.ComponentTypeReference convertComponentReference(ComponentTypeReference reference) {

		org.trentino.trengen.scamodelmirror.ComponentTypeReference mirrorComponentReference = new org.trentino.trengen.scamodelmirror.ComponentTypeReference();

		String currentRefName = reference.getName();
		mirrorComponentReference.setName(new NCName(currentRefName));
		mirrorComponentReference.setNameGen(getUniqueVariableName(currentRefName + "ComponentTypeRef"));
		if(null != reference.getInterface())
		{
			mirrorComponentReference.setInterface(convertCPPInterface((CPPInterface) reference.getInterface().getValue())); // interface
		}

		if(null != reference.getBinding())
		{
			for (int j = 0; j < reference.getBinding().size(); j++)
			{
				JAXBElement<? extends Binding> binding = reference.getBinding().get(j);
				mirrorComponentReference.bindingElements().add(convertBinding(binding)); // binding elements
			}
		}
		
		if (null != reference.getMetadata())
		{
			mirrorComponentReference.setMetadata(convertMetadata(reference.getMetadata(), currentRefName));
		}

		if(null != reference.getCallback())
		{
			mirrorComponentReference.setCallback(convertCallback(reference.getCallback(), currentRefName)); // callback
		}

		if(null != reference.getDocumentation())
		{
			List<Documentation> serviceDocList = reference.getDocumentation();
			for (Documentation doc : serviceDocList)
			{
				mirrorComponentReference.documentationElements().add(convertDocumentation(doc, currentRefName));
			}
		}

		if(null != reference.getTarget())
		{
			List<String> targets = reference.getTarget();
			for (String target : targets)
			{
				mirrorComponentReference.targets().add(target);
			}
		}

		if(null != reference.isAutowire())
		{
			mirrorComponentReference.setAutowire(reference.isAutowire());
		}
		if(null != reference.getMultiplicity())
		{
			mirrorComponentReference.setMultiplicity(reference.getMultiplicity());
		}
		mirrorComponentReference.setNonOverridable(reference.isNonOverridable());
		mirrorComponentReference.setWiredByImpl(reference.isWiredByImpl());

		handlePolicySets(reference, mirrorComponentReference);
		handleRequiresOrPolicySetAttachment(reference, mirrorComponentReference, currentRefName);
		handleSCARequires(reference, mirrorComponentReference, currentRefName);
		return mirrorComponentReference;
	}

	/**
	 * This function converts the SCA Model PropertyValue to to SCA Mirror Model
	 * PropertyValue.
	 */
	private org.trentino.trengen.scamodelmirror.PropertyValue convertComponentProperty(PropertyValue property, Property correspondingProperty) {

		org.trentino.trengen.scamodelmirror.PropertyValue mirrorPropertyValue = new org.trentino.trengen.scamodelmirror.PropertyValue();

		String propName = property.getName();
		mirrorPropertyValue.setName(new NCName(propName));
		mirrorPropertyValue.setNameGen(getUniqueVariableName(propName + "Property"));
		if(null != property.getSource())
		{
			mirrorPropertyValue.setSource(property.getSource());
		}
		if(null != property.getType())
		{
			javax.xml.namespace.QName propertyTypeQname = property.getType();
			mirrorPropertyValue.setType(new QName(propertyTypeQname.getLocalPart(), propertyTypeQname.getNamespaceURI(), propertyTypeQname
			        .getPrefix()));
		}
		if(null != property.getFile())
		{
			mirrorPropertyValue.setFile(new AnyURI(property.getFile()));
		}
		// BUG 563: If many is not specified, it takes the value defined by the
		// component type of the implementation used by the component.
		if(property.isMany() == null)
		{
			if(correspondingProperty.isMany() == null)
			{
				mirrorPropertyValue.setMany(false);
			}
			else
			{
				mirrorPropertyValue.setMany(correspondingProperty.isMany());
			}
		}
		else
		{
			mirrorPropertyValue.setMany(property.isMany());
		}

		if(null != property.getValue())
		{
			mirrorPropertyValue.setValue(property.getValue());
		}
		if(null != property.getElement())
		{
			javax.xml.namespace.QName propertyElementQname = property.getElement();
			mirrorPropertyValue.setElement(new QName(propertyElementQname.getLocalPart(), propertyElementQname.getNamespaceURI(),
			        propertyElementQname.getPrefix()));
		}
		// property value setting (not with @value attribute)
		List<Object> listContent = new ArrayList<Object>();
		listContent = property.getContent();
		int sizeContent = listContent.size();

		for (int i = 0; i < sizeContent; i++)
		{
			Object propChildObj = listContent.get(i);

			if(propChildObj.getClass().equals(JAXBElement.class))
			{
				JAXBElement<?> valueType = ((JAXBElement<?>) propChildObj);
				ValueType valueType2 = (ValueType) valueType.getValue();
				int sizeValueElementContent = valueType2.getContent().size();
				for (int j = 0; j < sizeValueElementContent; j++)
				{
					mirrorPropertyValue.content().add(valueType2.getContent().get(0).toString().trim());
				}
				continue;
			}
			String strChecForWS = propChildObj.toString();
			if(!ConformanceManagerProperty.isWSpace(strChecForWS))
			{
				mirrorPropertyValue.content().add(strChecForWS.trim());
			}
		}
		// end property value setting
		return mirrorPropertyValue;
	}

	/**
	 * This function converts the SCA Model Property to SCA Mirror Model
	 * Property.
	 */
	private org.trentino.trengen.scamodelmirror.Property convertProperty(Property property) {
		org.trentino.trengen.scamodelmirror.Property mirrorProperty = new org.trentino.trengen.scamodelmirror.Property();

		String propertyName = property.getName();
		mirrorProperty.setName(new NCName(propertyName));
		mirrorProperty.setNameGen(getUniqueVariableName(propertyName + "Property"));

		if(null != property.getType())
		{
			javax.xml.namespace.QName propertyTypeQname = property.getType();
			mirrorProperty.setType(new QName(propertyTypeQname.getLocalPart(), propertyTypeQname.getNamespaceURI(), propertyTypeQname.getPrefix()));
		}

		if(property.isMany() == null)
		{
			mirrorProperty.setMany(false);
		}
		else
		{
			mirrorProperty.setMany(property.isMany());
		}

		if(null != property.getValue())
		{
			mirrorProperty.setValue(property.getValue());
		}
		if(null != property.getElement())
		{
			javax.xml.namespace.QName propertyElementQname = property.getElement();
			mirrorProperty.setElement(new QName(propertyElementQname.getLocalPart(), propertyElementQname.getNamespaceURI(), propertyElementQname
			        .getPrefix()));
		}
		mirrorProperty.setMustSupply(property.isMustSupply());
		// property value setting (not with @value attribute)
		List<Object> listContent = new ArrayList<Object>();
		listContent = property.getContent();
		int sizeContent = listContent.size();

		for (int i = 0; i < sizeContent; i++)
		{
			Object propChildObj = listContent.get(i);

			if(propChildObj.getClass().equals(JAXBElement.class))
			{
				JAXBElement<?> valueType = ((JAXBElement<?>) propChildObj);
				ValueType valueType2 = (ValueType) valueType.getValue();
				int sizeValueElementContent = valueType2.getContent().size();
				for (int j = 0; j < sizeValueElementContent; j++)
				{
					mirrorProperty.content().add(valueType2.getContent().get(j).toString().trim());
					// mirrorProperty.content().add(valueType2.toString());
				}
				continue;
			}
			String strChecForWS = propChildObj.toString();
			if(!ConformanceManagerProperty.isWSpace(strChecForWS))
			{
				mirrorProperty.content().add(strChecForWS.trim());
			}
		}
		// end property value setting
		return mirrorProperty;
	}

	/**
	 * This function converts the SCA Model Component to SCA Mirror Model
	 * Component.
	 */
	private org.trentino.trengen.scamodelmirror.Component convertComponent(Component component, String uniqueComponentName,
	        ComponentType correspondingComponentType) {
		org.trentino.trengen.scamodelmirror.Component mirrorComponent = new org.trentino.trengen.scamodelmirror.Component();

		String componentName = component.getName();
		mirrorComponent.setName(new NCName(componentName));
		mirrorComponent.setNameGen(uniqueComponentName);

		Boolean autowire = component.isAutowire();
		mirrorComponent.setAutowire(autowire != null ? autowire : false);

		JAXBElement<? extends Implementation> implementation = component.getImplementation();
		if(null != implementation)
		{
			Implementation value = implementation.getValue();
			if(CPPImplementation.class.equals(value.getClass()))
			{
				mirrorComponent.setImplementation(convertCPPImplementation((CPPImplementation) value));
			}
			else if(implementation.getValue().getClass().equals(SCAImplementation.class))
			{
				mirrorComponent.setImplementation(convertImplementation((SCAImplementation) value));
			}
		}

		if(null != component.getDocumentation())
		{
			List<Documentation> serviceDocList = component.getDocumentation();
			for (Documentation doc : serviceDocList)
			{
				mirrorComponent.documentationElements().add(convertDocumentation(doc, componentName));
			}
		}

		if(null != component.getPolicySets())
		{
			List<javax.xml.namespace.QName> servicePsList = component.getPolicySets();
			for (javax.xml.namespace.QName ps : servicePsList)
			{
				mirrorComponent.policySets().add(new QName(ps.getLocalPart(), ps.getNamespaceURI(), ps.getPrefix())); // policy set
			}
		}

		// Not for sure....
		if(null != component.getRequires())
		{
			List<javax.xml.namespace.QName> requireList = component.getRequires();
			for (javax.xml.namespace.QName require : requireList)
			{
				org.trentino.trengen.scamodelmirror.Requires mirrorRequires = new org.trentino.trengen.scamodelmirror.Requires();
				mirrorRequires.setNameGen(getUniqueVariableName(componentName + "Requires"));
				mirrorRequires.intents().add(new QName(require.getLocalPart(), require.getNamespaceURI(), require.getPrefix()));
				mirrorComponent.requiresElements().add(mirrorRequires);
			}
		}

		if(null != component.getServiceOrReferenceOrProperty())
		{
			for (int i = 0; i < component.getServiceOrReferenceOrProperty().size(); i++)
			{
				if(component.getServiceOrReferenceOrProperty().get(i).getClass().equals(ComponentService.class))
				{
					ComponentService service = (ComponentService) component.getServiceOrReferenceOrProperty().get(i);
					mirrorComponent.serviceElements().add(convertComponentService(service));
				}
				else if(component.getServiceOrReferenceOrProperty().get(i).getClass().equals(ComponentReference.class))
				{
					ComponentReference reference = (ComponentReference) component.getServiceOrReferenceOrProperty().get(i);
					mirrorComponent.referenceElements().add(convertComponentReference(reference));
				}
				else if(component.getServiceOrReferenceOrProperty().get(i).getClass().equals(PropertyValue.class))
				{
					PropertyValue property = (PropertyValue) component.getServiceOrReferenceOrProperty().get(i);

					Property correspondingProperty = findMatchingProperty(correspondingComponentType, property.getName());

					mirrorComponent.propertyElements().add(convertComponentProperty(property, correspondingProperty));
				}
			}
		}
		return mirrorComponent;
	}

	/**
	 * This function converts the SCA Model ComponentType to SCA Mirror Model
	 * ComponentType.
	 */
	private org.trentino.trengen.scamodelmirror.ComponentType convertComponentType(ComponentType component, String uniqueVarName) {
		org.trentino.trengen.scamodelmirror.ComponentType mirrorComponent = new org.trentino.trengen.scamodelmirror.ComponentType();

		mirrorComponent.setNameGen(uniqueVarName);

		if(null != component.getImplementation())
		{
			mirrorComponent.setImplementation(convertCPPImplementation((CPPImplementation) component.getImplementation().getValue()));
		}

		if(null != component.getDocumentation())
		{
			List<Documentation> serviceDocList = component.getDocumentation();
			for (Documentation doc : serviceDocList)
			{
				mirrorComponent.documentationElements().add(convertDocumentation(doc, uniqueVarName));
			}
		}

		for (int i = 0; i < component.getServiceOrReferenceOrProperty().size(); i++)
		{
			if(component.getServiceOrReferenceOrProperty().get(i).getClass().equals(ComponentService.class))
			{
				ComponentService service = (ComponentService) component.getServiceOrReferenceOrProperty().get(i);
				mirrorComponent.serviceElements().add(convertComponentService(service));
			}
			else if(component.getServiceOrReferenceOrProperty().get(i).getClass().equals(ComponentTypeReference.class))
			{
				ComponentTypeReference reference = (ComponentTypeReference) component.getServiceOrReferenceOrProperty().get(i);
				mirrorComponent.referenceElements().add(convertComponentReference(reference));
			}
			else if(component.getServiceOrReferenceOrProperty().get(i).getClass().equals(Property.class))
			{
				Property property = (Property) component.getServiceOrReferenceOrProperty().get(i);
				mirrorComponent.propertyElements().add(convertProperty(property));
			}
		}
		return mirrorComponent;
	}

	public List<ReferenceServiceInterface> getServiceInterfaces() {
		return serviceInterfaces;
	}

	public List<ReferenceServiceInterface> getReferenceInterfaces() {
		return referenceInterfaces;
	}

	public Map<String, Object> getUsingDirectivesMap() {
		return usingDirectivesMap;
	}

	/**
     * @return
     */
    public Set<ReferenceServiceInterface> getRemotableServices() {
	    return remotableServices;
    }

}
