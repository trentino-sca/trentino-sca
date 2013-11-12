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
import java.util.LinkedList;
import java.util.List;
import javax.xml.bind.JAXBElement;
import javax.xml.namespace.NamespaceContext;
import javax.xml.namespace.QName;

import org.apache.log4j.Logger;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.Composite;
import org.trentino.trengen.sca.model.Property;
import org.trentino.trengen.sca.model.PropertyValue;
import org.trentino.trengen.sca.model.ValueType;
import org.trentino.trengen.tools.scavalidation.utils.FileURIChecker;

/**
 * this is the class hosting the property related specifications of the
 * SCAAMv1.1
 */
public class ConformanceManagerProperty {
	// members set by the setter method called by the conformanceManager
	private ComponentWrapper	          currentCompWrapper	     = null;
	private String	                      currentComponentName	     = null;
	private ComponentType	              currentComponentType	     = null;
	private Component	                  currentComponent	         = null;

	// members cleared by the setter method
	ArrayList<String>	          propertyNamesComponentType	= new ArrayList<String>();	                       // for
	                                                                                                               // unuiquenes
	                                                                                                               // of
	                                                                                                               // property
	                                                                                                               // names
	                                                                                                               // in
	                                                                                                               // componentType
	ArrayList<String>	          propertyNamesComponent	 = new ArrayList<String>();	                       // for
	                                                                                                               // unuiquenes
	                                                                                                               // of
	                                                                                                               // property
	                                                                                                               // names
	                                                                                                               // in
	                                                                                                               // component
	List<String>	              propertyNamesComposite	 = new ArrayList<String>();	                       // for
	                                                                                                               // unuiquenes
	                                                                                                               // of
	                                                                                                               // property
	                                                                                                               // names in
	                                                                                                               // component

	// just to be able to raise good log commands from child functions
	// these members are maintained by checkComponentProperty and
	// checkComponentTypeProperty functions
	PropertyValue	              currentPropValue	         = null;
	Property	                  currentProperty	         = null;
	String	                      currentPropertyName	     = null;

	// member to be able to access the namespace context of the composite
	CompositeWrapper	          compositeWrapper	         = null;

	// this member is required to raise good logs in case of invalidity once
	// OnNewPropertyOfComposite is called
	String	                      currentCompositeName	     = null;

	// this is the list used to check out the source attribute of the component
	// properties
	ArrayList<Property>	          compositeProperties	     = new ArrayList<Property>();

	// Used several times within the stack of checkComponentTypeProperty
	// function
	String	                      currentType	             = null;

	protected static final Logger	logger	                 = Logger.getLogger(ConformanceManagerProperty.class);

	public ConformanceManagerProperty (CompositeWrapper compositeWrap) {
		compositeWrapper = compositeWrap;
		if(compositeWrap == null)
		{
			throw new ValidationException("Given compositeWrap is null");
		}
		Composite composite = compositeWrapper.getComposite();
		if(composite != null)
		{
			logger.info("Validating properties of Composite: " + composite.getName());
			currentCompositeName = composite.getName();
			return;
		}
		throw new ValidationException("Composite object is null");

	}

	/**
	 * We need this setter method to be used from the generic ConformanceManager
	 * to set the component related info.
	 */
	public void setComponentWrapper(ComponentWrapper componentWrapper) {
		propertyNamesComponentType.clear();
		propertyNamesComponent.clear();
		propertyNamesComposite.clear();

		currentCompWrapper = componentWrapper;
		currentComponentName = currentCompWrapper.getScaModelComponent().getName();
		currentComponent = currentCompWrapper.getScaModelComponent();
		currentComponentType = currentCompWrapper.getScaModelComponentType();

	}

	/**
	 * This is the function where the checks are originated from the
	 * componentType properties. Matching component property is also found and
	 * specifications regarding the componentType properties and regarding the
	 * relationship bw componentType prop and component prop are analaysed here.
	 */

	public boolean checkComponentTypeProperty(Property propertyComponentType) {
		currentProperty = propertyComponentType;
		currentPropertyName = currentProperty.getName();

		if(!check_ASM40010(currentProperty))
		{
			return false;
		}

		String ownerOfProperty = " Component Type for: " + currentComponentName;
		if(!CheckValues(currentProperty, ownerOfProperty))
		{
			return false;
		}

		currentPropValue = findMatchingPropertyValue(currentComponent, currentPropertyName);

		QName typeCompType = propertyComponentType.getType();
		QName elementCompType = propertyComponentType.getElement();

		if((typeCompType == null) && (elementCompType == null))
		{
			throw new ValidationException("Either @type attribute or @element attribute is required " + " Property: " + currentPropertyName + " Component name: "
			        + currentComponentName + " CompositeName: " + currentCompositeName);
		}

		if(elementCompType != null)
		{
			throw new ValidationException("Currently Trentino only supports XSD basic types. No @element attribute should be used for the property: "
			        + currentPropertyName + "Component name: " + currentComponentName + " CompositeName: " + currentCompositeName);
		}

		if(currentPropValue != null) // TODO propvalue can be null if the
		                             // default value is given in the
		                             // comptype
		{
			if(!check_ASM50035(currentPropValue))
			{
				return false;
			}

			if(!checkTypeCompatibilityComponentTypeComponent(currentProperty, currentPropValue))
			{
				return false;
			}

			if(!checkValuesComponent(currentPropValue))
			{
				return false;
			}
		}
		else if(currentProperty.isMustSupply())
		{
			// if there is no matching PropertyValue element in the component
			// raise error
			throw new ValidationException(ConformanceManagerConstants.CI_ASM40011_VIOLATED + "no matchin component property for Property name: " + currentPropertyName
			        + " Component: " + currentComponentName + " CompositeName: " + currentCompositeName);
		}

		if(propertyNamesComponentType.contains(currentPropertyName))
		{
			throw new ValidationException(ConformanceManagerConstants.CI_ASM40005_VIOLATED + " Property name: " + currentPropertyName
			        + " ComponentType of component: " + currentComponentName + " CompositeName: " + currentCompositeName);
		}

		propertyNamesComponentType.add(currentPropertyName);

		return true;
	}

	/**
	 * This fucntion chekcs out the ASM50035 for the propertyValue of the
	 * Component
	 * @param propertyValue
	 * @return
	 */
	private boolean check_ASM50035(PropertyValue propertyValue) {
		if((propertyValue.getType() != null) && (propertyValue.getElement() != null))
		{
			throw new ValidationException(ConformanceManagerConstants.CI_ASM50035_VIOLATED + " for Property: " + currentPropertyName + "Component name: "
			        + currentComponentName + " CompositeName: " + currentCompositeName);
		}
		return true;
	}

	/**
	 * This functions checks out ASM40010 for the property of ComponentType
	 */
	private boolean check_ASM40010(Property property) {
		if((property.getType() != null) && (property.getElement() != null))
		{
			throw new ValidationException(ConformanceManagerConstants.CI_ASM40010_VIOLATED + "for Property: " + currentPropertyName
			        + " of ComponentType of component: " + currentComponentName + " CompositeName: " + currentCompositeName);
		}
		return true;
	}

	/**
	 * Searches for the matching property(arg2) of componenttype in the matching
	 * component(arg one) Called by checpProperties working on componentWrapper
	 */
	private PropertyValue findMatchingPropertyValue(Component component, String propName) {
		if(component == null)
		{
			throw new ValidationException("component object given for property search is null");
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

	/**
	 * Searches for the matching propertyValue(with name arg2) of component in
	 * the matching componentType(arg one) called from:
	 * check_SpecsSpecificToComponent This function(loop) is required to check
	 * out ASM50037
	 */
	private Property findMatchingProperty(ComponentType componentType, String propName) {
		if(componentType == null)
		{
			throw new ValidationException("componentType object given for property search is null");
		}

		int size = componentType.getServiceOrReferenceOrProperty().size();

		for (int index = 0; index < size; index++)
		{
			if(componentType.getServiceOrReferenceOrProperty().get(index).getClass().equals(Property.class))
			{
				Property prop = (Property) componentType.getServiceOrReferenceOrProperty().get(index);

				String propertyName = prop.getName();
				if(!propName.equals(propertyName))
				{
					continue;
				}
				return prop;
			}
		}
		return null;

	}

	/**
	 * This function checks out the specs specific to the component / or the
	 * specs that are defined from the component perspective. It has been
	 * considered to get rid of this for loop but since we have to go through
	 * all component properties seperately to check out ASM50037, we kept it as
	 * a seperate function. Called by checkProperties working on
	 * componentWrapper
	 */
	public boolean checkComponentProperty(PropertyValue currentPropVal) {
		currentPropValue = currentPropVal;
		currentPropertyName = currentPropValue.getName();
		currentProperty = findMatchingProperty(currentComponentType, currentPropertyName);

		// creating the property structure required for reflection code
		// generation
		// CreateReflectionProperty(currentProperty, currentPropVal);

		if((currentProperty == null))
		{
			// no matching property in the componenttype file
			String message ="A property is used in the component but not declared in the component type file.\nComponent : "+currentComponentName;
			message+="\n";
			message += ConformanceManagerConstants.CI_ASM50037_VIOLATED + "Property name: " + currentPropertyName + " Component name: "
			        + currentComponentName + " CompositeName: " + currentCompositeName;
			throw new ValidationException(message);
		}

		if(propertyNamesComponent.contains(currentPropertyName))
		{
			throw new ValidationException(ConformanceManagerConstants.CI_ASM50031_VIOLATED + " Component name: " + currentComponentName + " CompositeName: "
			        + currentCompositeName);
		}

		String fileURI = currentPropValue.getFile();
		if(fileURI != null)
		{
			if(!FileURIChecker.isDereferancableURI(fileURI))
			{
				logger.warn(ConformanceManagerConstants.CI_ASM50045_VIOLATED + " URI: " + fileURI + "Property name: " + currentPropertyName
				        + " Component name: " + currentComponentName + " CompositeName: " + currentCompositeName);
			}
		}

		String source = currentPropValue.getSource();
		if(!checkSource(source))
		{
			return false;
		}

		propertyNamesComponent.add(currentPropertyName);

		return true;
	}

	/**
	 * checks out the validity of the @source attribute of the PropertyValue
	 * child element of the component property Called by the
	 * check_SpecsSpecificToComponent
	 */
	private boolean checkSource(String source) {
		if(source != null)
		{
			if(!source.startsWith("$"))
			{
				throw new ValidationException("Source attribute: " + source + " does not start with '$' Property: " + currentPropertyName + " Component: "
				        + currentComponentName + " CompositeName: " + currentCompositeName);
			}
			CharSequence seq = "/";
			if(source.contains(seq))
			{
				throw new ValidationException("Currently only simle XSD types are supported '/' char shouldn't exits in source attribute");
			}
			String sourceTrimmed = source.substring(1);
			if(!checkCompositeForProperty(sourceTrimmed))
			{
				throw new ValidationException("There is no matching property in the Composite for source attribute value: " + sourceTrimmed);
			}
		}
		return true;
	}

	/**
	 * Checks specification regarding the compatibility of property and
	 * propertyValue types Called by the checkProperties(componentWrapper) works
	 * on both the component and componentType
	 */
	private boolean checkTypeCompatibilityComponentTypeComponent(Property prop, PropertyValue propertyComponent) {
		QName typeCompType = prop.getType();
		QName typeComp = propertyComponent.getType();
		QName elementCompType = prop.getElement();
		QName elementComponent = propertyComponent.getElement();
		if(typeCompType != null)
		{
			currentType = typeCompType.getLocalPart();
		}

		if((typeCompType == null) && (elementCompType == null))
		{
			throw new ValidationException("Either @type attribute or @element attribute is required " + " Property: " + currentPropertyName + " Component name: "
			        + currentComponentName + " CompositeName: " + currentCompositeName);
		}
		if((typeCompType != null) && (elementCompType != null) || (typeCompType != null) && (elementComponent != null) || (typeComp != null)
		        && (elementComponent != null) || (typeComp != null) && (elementCompType != null))
		{
			throw new ValidationException(ConformanceManagerConstants.CI_ASM40010_VIOLATED + "for Property: " + currentPropertyName
			        + " of ComponentType of component: " + currentComponentName + " CompositeName: " + currentCompositeName);
		}

		NamespaceContext nsContextComponenttype = currentCompWrapper.getNamespaceContextComponentType();
		NamespaceContext nsContextComposite = compositeWrapper.getNamespaceContext();
		if(nsContextComposite == null)
		{
			throw new ValidationException("NamespaceContext is null for composite: " + currentCompositeName);
		}
		if(nsContextComponenttype == null)
		{
			// if the current component is a compositeByImpl, it has not any
			// componentTypes, instead it has composites.
			if(!currentCompWrapper.isCompositeByImpl())
			{
				throw new ValidationException("NamespaceContext is null for componenttype of component: " + currentComponentName);
			}
			else
			{
				nsContextComponenttype = currentCompWrapper.getCorrespondingCompositeImpl().getNamespaceContext();
				if(nsContextComponenttype == null)
				{
					throw new ValidationException("NamespaceContext is null for componenttype of component: " + currentComponentName);
				}
			}
		}
		if(typeCompType != null)
		{
			if(!isNamespaceForXSDBasicTypes(nsContextComponenttype, typeCompType.getPrefix()))
			{
				throw new ValidationException(ConformanceManagerConstants.CI_ASM40007_VIOLATED + " Property: " + currentPropertyName + "Component name: "
				        + currentComponentName + " CompositeName: " + currentCompositeName);
			}

			if(!isPrimitiveXSDType(typeCompType.getLocalPart()))
			{
				throw new ValidationException("Type is not an XSD basic type " + " Property: " + currentPropertyName + " Component name: " + currentComponentName
				        + " CompositeName: " + currentCompositeName);
			}

			if((typeComp != null) && (typeCompType != null) && (typeCompType != typeComp))
			{
				if(!typeComp.getLocalPart().equals(typeCompType.getLocalPart()))
				{
					throw new ValidationException(ConformanceManagerConstants.CI_ASM50036_VIOLATED + " Property: " + currentPropertyName + " Component name: "
					        + currentComponentName + " CompositeName: " + currentCompositeName);
				}

				String nameSpaceURI4TypeComp = (typeComp.getPrefix() != "") ? nsContextComposite.getNamespaceURI(typeComp.getPrefix())
				        : nsContextComposite.getNamespaceURI("xmlns");

				String nameSpaceURI4TypeCompType = (typeComp.getPrefix() != "") ? nsContextComponenttype.getNamespaceURI(typeCompType.getPrefix())
				        : nsContextComponenttype.getNamespaceURI("xmlns");

				if((nameSpaceURI4TypeComp != null) && !nameSpaceURI4TypeComp.equals(nameSpaceURI4TypeCompType))
				{
					throw new ValidationException(ConformanceManagerConstants.CI_ASM50036_VIOLATED + " Property: " + currentPropertyName + " Component name: "
					        + currentComponentName + " CompositeName: " + currentCompositeName);
				}
			}
		}

		return true;
	}

	/**
	 * This function validates the value related specs of propertyValue of
	 * component and property of component Called by the
	 * checkProperties(componentWrapper)
	 */
	private boolean checkValuesComponent(PropertyValue propValue) {
		List<Object> listContent = new LinkedList<Object>();
		listContent = propValue.getContent();
		int sizeContent = listContent.size();
		int countNonValueChildElement = 0;
		int countValueChildElementCount = 0;

		List<String> valueElements = new ArrayList<String>();
		for (int i = 0; i < sizeContent; i++)
		{
			Object propChildObj = listContent.get(i);

			if(propChildObj.getClass().equals(JAXBElement.class))
			{
				countValueChildElementCount++;
				JAXBElement<?> valueType = (JAXBElement<?>) propChildObj;
				ValueType valueType2 = (ValueType) valueType.getValue();
				int sizeValueElementContent = valueType2.getContent().size();
				if(sizeValueElementContent != 1)
				{
					throw new ValidationException("There should be exactly one content(Currently Trentino supports simple XSD types only) within the value child element"
					        + " Property Name: "
					        + currentPropertyName
					        + " Component name: "
					        + currentComponentName
					        + " CompositeName: "
					        + currentCompositeName);
				}
				valueElements.add(valueType2.getContent().get(0).toString());
				continue;
			}
			String strChecForWS = propChildObj.toString();
			if(!isWSpace(strChecForWS))
			{
				countNonValueChildElement++;
				continue;
			}
		}
		// -------------------
		// if there is matching PropertyValue element in the component exist but
		// no value is defined raise error
		// [ASM40011] is checked out and called by checpProperties working on
		// componentWrapper
		if(currentProperty.isMustSupply() && (currentPropValue.getValue() == null) && (countValueChildElementCount == 0)
		        && (countNonValueChildElement == 0) && (currentPropValue.getSource() == null) && (currentPropValue.getFile() == null))
		{
			throw new ValidationException(ConformanceManagerConstants.CI_ASM40011_VIOLATED + " Property name: " + currentPropertyName + " Component: "
			        + currentComponentName + " CompositeName: " + currentCompositeName);
		}

		if(!checkValueType())
		{
			return false;
		}

		// ASM50029
		if(((currentPropValue.getElement() == null) && (currentProperty.getElement() == null)) && (countNonValueChildElement > 0))
		{
			throw new ValidationException(ConformanceManagerConstants.CI_ASM50029_VIOLATED + " Property Name: " + currentPropertyName + " Component name: "
			        + currentComponentName + " CompositeName: " + currentCompositeName);
		}

		if((countValueChildElementCount > 1) && propValue.isMany() != null && !propValue.isMany() && currentProperty.isMany() != null
		        && !currentProperty.isMany())
		{
			throw new ValidationException(ConformanceManagerConstants.CI_ASM50032_VIOLATED + " Property Name: " + currentPropertyName + " Component name: "
			        + currentComponentName + " CompositeName: " + currentCompositeName);
		}
		String value = propValue.getValue();
		if((value != null) && (countValueChildElementCount > 0))
		{
			throw new ValidationException(ConformanceManagerConstants.CI_ASM50033_VIOLATED + "Component name: " + currentComponentName + " CompositeName: "
			        + currentCompositeName);
		}
		// if(((value != null) || (countValueChildElementCount > 0)) &&
		// (propValue.getSource() != null))
		// {
		// logger.warn("Source attribute exists together with any other value specifier Property: "
		// + currentPropertyName
		// + " Component name: " + currentComponentName + " CompositeName: " +
		// currentCompositeName);
		// }
		if(value != null)
		{
			if(((countValueChildElementCount > 0) && (propValue.getElement() != null))
			        || ((countValueChildElementCount > 0) && (propValue.getType() == null) && (currentProperty.getType() == null)))
			{
				throw new ValidationException("With value child attribute only @type attribute is allowed.  " + " Property Name: " + currentPropertyName
				        + " Component name: " + currentComponentName + " CompositeName: " + currentCompositeName);
			}
			if(!checkValueTypeCompatibility(value, currentType))
			{
				return false;
			}
		}
		if(((countValueChildElementCount > 0) && (propValue.getElement() != null))
		        || ((countValueChildElementCount > 0) && ((propValue.getType() == null) && (currentProperty.getType() == null))))
		{
			throw new ValidationException("With value child elements only @type attribute is allowed." + " Property Name: " + currentPropertyName
			        + " Component name: " + currentComponentName + " CompositeName: " + currentCompositeName);
		}
		for (int i = 0; i < valueElements.size(); i++)
		{
			if(!checkValueTypeCompatibility(valueElements.get(i), currentType))
			{
				return false;
			}
		}

		return true;
	}

	/**
	 * Check for the default values independently within the composite level
	 * properties and componentType level properties For componentType
	 * properties called by the checkProperties(componentWrapper) For composite
	 * properties called by TracePropertiesOfComposite
	 */
	private boolean CheckValues(Property propertyCompositeOrComponentType, String ownerOfProperty) {
		QName typeQname = propertyCompositeOrComponentType.getType();
		String currentTypeCompositeOrComponentType = null;
		if(typeQname != null)
		{
			currentTypeCompositeOrComponentType = typeQname.getLocalPart();
		}
		List<Object> listContent = new ArrayList<Object>();
		String propertyNameCompositeOrComponentType = propertyCompositeOrComponentType.getName();
		listContent = propertyCompositeOrComponentType.getContent();
		int sizeContent = listContent.size();
		// int countNonValueChildElementComposite = 0;
		int countValueChildElementCountComposite = 0;

		List<String> valueElements = new ArrayList<String>();
		for (int i = 0; i < sizeContent; i++)
		{
			Object propChildObj = listContent.get(i);

			if(propChildObj.getClass().equals(JAXBElement.class))
			{
				countValueChildElementCountComposite++;
				JAXBElement<?> valueType = ((JAXBElement<?>) propChildObj);
				ValueType valueType2 = (ValueType) valueType.getValue();
				int sizeValueElementContent = valueType2.getContent().size();
				if(sizeValueElementContent != 1)
				{
					throw new ValidationException("There should be exactly one content(Currently Trentino supports simple XSD types only) within the value child element"
					        + " Property Name: " + propertyCompositeOrComponentType.getName() + ownerOfProperty);
				}
				valueElements.add(valueType2.getContent().get(0).toString());
				continue;
			}
			/*
			 * String strChecForWS = propChildObj.toString();
			 * if(!isWSpace(strChecForWS)) {
			 * countNonValueChildElementComposite++;
			 * continue;
			 * }
			 */
		}

		// Why is this part commented out??
		/*
		 * if((propertyCompositeOrComponentType.getElement() == null) && (countNonValueChildElementComposite > 0)) {
		 * // logger.error("Property values that are not embedded in value child element without @element "
		 * // + " Property Name: " +
		 * // propertyNameCompositeOrComponentType + OwnerOfProperty);
		 * // return false;
		 * }
		 */

		if((countValueChildElementCountComposite > 1) && propertyCompositeOrComponentType.isMany() != null
		        && !propertyCompositeOrComponentType.isMany())
		{
			throw new ValidationException("Multiple value child elemenst is not allowed without having @many attribute is set TRUE " + " Property Name: "
			        + propertyNameCompositeOrComponentType + ownerOfProperty);
		}
		String value = propertyCompositeOrComponentType.getValue();
		if((value != null) && (countValueChildElementCountComposite > 0))
		{
			throw new ValidationException("@value attribute and value child elements cannot exist together" + " Property Name: "
			        + propertyNameCompositeOrComponentType + ownerOfProperty);
		}
		if(value != null)
		{
			if(currentTypeCompositeOrComponentType == null)
			{
				throw new ValidationException("Once @value attribute us uset @type attrbute shoudl be available " + " Property Name: "
				        + propertyNameCompositeOrComponentType + ownerOfProperty);
			}
			if(!checkValueTypeCompatibility(value, currentTypeCompositeOrComponentType))
			{
				return false;
			}
		}

		if((countValueChildElementCountComposite > 0) && (propertyCompositeOrComponentType.getElement() != null))
		{
			throw new ValidationException("Value child elements and @element attribute cannot coexist " + " Property Name: " + propertyNameCompositeOrComponentType
			        + ownerOfProperty);
		}
		for (int i = 0; i < valueElements.size(); i++)
		{
			if(!checkValueTypeCompatibility(valueElements.get(i), currentTypeCompositeOrComponentType))
			{
				return false;
			}
		}
		return true;
	}

	private boolean checkValueType() {
		String value = currentPropValue.getValue();
		if(value != null)
		{
			// type should be queried from the componenttype since it is
			// mandatory and its compatibility with propvalue of component is
			// also checked
			// in an CI
			QName typeQName = currentProperty.getType();
			if(typeQName == null)
			{
				throw new ValidationException(ConformanceManagerConstants.CI_ASM50027_VIOLATED + " Property name: " + currentPropertyName + " Component: "
				        + currentComponentName + " CompositeName: " + currentCompositeName);
			}
			String type = typeQName.getLocalPart();
			if(type == null)
			{
				String message = "Once the value attribute is set for Property name: " + currentPropValue.getName() + " type attribute should be defined";
				ValidationException validationException = new ValidationException(message);
				validationException.addMessage(ConformanceManagerConstants.CI_ASM50027_VIOLATED + " Property name: " + currentPropertyName + " Component: "
				        + currentComponentName + " CompositeName: " + currentCompositeName);
				throw validationException;
			}

			if(!isPrimitiveXSDType(typeQName.getLocalPart()))
			{
				ValidationException validationException = new ValidationException("Type is not an XSD basic type for Property name: " + currentPropValue.getName());
				validationException.addMessage(ConformanceManagerConstants.CI_ASM50027_VIOLATED + " Property name: " + currentPropertyName + " Component: "
				        + currentComponentName + " CompositeName: " + currentCompositeName);
				throw validationException;

			}

		}
		return true;
	}

	/**
	 * Is this string all whitespace?
	 */
	public static boolean isWSpace(String s) {
		for (int i = 0; i < s.length(); i++)
		{
			if(!Character.isWhitespace(s.charAt(i)))
			{
				return false;
			}
		}
		return true;
	}

	/**
	 * Checks out if the Uri of the namespace prefixx is matching to the xpec of
	 * XSD basic types
	 */
	private boolean isNamespaceForXSDBasicTypes(NamespaceContext ns, String prefix) {
		if(ns == null)
		{
			throw new ValidationException("NamespaceContext is null for Property: " + currentPropertyName);
		}
		String namespaceURI = null;
		if(prefix != "")
		{
			namespaceURI = ns.getNamespaceURI(prefix);
		}
		else
		{
			namespaceURI = ns.getNamespaceURI("xmlns");
		}
		// String namespaceURI = (prefix != null) ? ns.getNamespaceURI(prefix):
		// ns.getNamespaceURI("xmlns");
		if(namespaceURI == null)
		{
			throw new ValidationException("There is no matching namespace defined for the prefix: " + prefix + " Property: " + currentPropertyName);
		}
		if(!namespaceURI.equals("http://www.w3.org/2001/XMLSchema"))
		{
			throw new ValidationException("Property types only from the http://www.w3.org/2001/XMLSchema namespace are supported. check out the namespace prefix. Property: "
			        + currentPropertyName);
		}
		return true;
	}

	/**
	 * checks out of the given local part matches the defined basic xsd types
	 */
	private boolean isPrimitiveXSDType(String localPart) {
		if(localPart == "anyType")
		{
			throw new ValidationException("anyType is not currently supported as a Property type");
		}
		else
		{
			boolean result = XSDSchemaTypes.IsXSDBuiltinType(localPart);
			if(!result)
			{
				throw new ValidationException("Property type must macth to XSD schema types specified at  Table 9-1 SCA Clinet and Implementation Model for C++ Specification V1.1");
			}
			return result;
		}
	}

	/**
	 * currently this function is only a place holder no exact value type
	 * compatibility check is implemented
	 */
	private boolean checkValueTypeCompatibility(String value, String type) {
		if(type == null)
		{
			throw new ValidationException("Type type is null for Property: " + currentProperty + " Component: " + currentComponentName + " CompositeName: "
			        + currentCompositeName);
		}
		if(value == null)
		{
			throw new ValidationException("Type value is null for Property: " + currentProperty + " Component: " + currentComponentName + " CompositeName: "
			        + currentCompositeName);
		}
		if(!XSDSchemaTypes.IsCompatible(value, type))
		{
			throw new ValidationException("Value is not matching the XSD basic type: " + type + "for Property: " + currentProperty + " Component: "
			        + currentComponentName + " CompositeName: " + currentCompositeName);
		}
		return true;
	}

	/**
	 * @param propertyComposite
	 * @return
	 */
	public boolean OnNewPropertyOfComposite(Property propertyComposite) {
		String propertyName = propertyComposite.getName();

		if(propertyNamesComposite.contains(propertyName))
		{
			throw new ValidationException(ConformanceManagerConstants.CI_ASM60014_VIOLATED + "Property: " + propertyName + " Composite name: " + currentCompositeName);
		}

		if((propertyComposite.getType() != null) && (propertyComposite.getElement() != null))
		{
			throw new ValidationException(ConformanceManagerConstants.CI_ASM60040_VIOLATED + "Property: " + propertyName + " Composite name: " + currentCompositeName);
		}

		propertyNamesComposite.add(propertyName);
		compositeProperties.add(propertyComposite);

		String ownerOfProperty = " Composite name: " + currentCompositeName;
		currentPropertyName = propertyName + "@" + ownerOfProperty;
		QName typeCompositeProperty = propertyComposite.getType();
		if(!CheckValues(propertyComposite, ownerOfProperty))
		{
			return false;
		}
		if(typeCompositeProperty != null)
		{
			// first check out if the Uri of the namespace prefixx is matching
			// to the xpec of XSD basic types
			if(!isNamespaceForXSDBasicTypes(compositeWrapper.getNamespaceContext(), typeCompositeProperty.getPrefix()))
			{
				throw new ValidationException(ConformanceManagerConstants.CI_ASM40007_VIOLATED + " Property: " + propertyName + " Composite name: "
				        + currentCompositeName);
			}

			if(!isPrimitiveXSDType(typeCompositeProperty.getLocalPart()))
			{
				throw new ValidationException("Property type error. " + " Property: " + propertyName + " Compoiste name: " + currentCompositeName);
			}
		}
		return true;
	}

	/**
	 * Checks out if the @source attribute defined by the component property has
	 * a matching property at the composite level
	 */
	private boolean checkCompositeForProperty(String sourceTrimmed) {
		for (int i = 0; i < compositeProperties.size(); i++)
		{
			Property propertyComposite = compositeProperties.get(i);
			if(propertyComposite.getName().equals(sourceTrimmed))
			{
				if(currentPropValue.getType() != null)
				{
					if(!checkTypeCompatibilityCompositeComponentProperties(currentPropValue, propertyComposite))
					{
						return false;
					}
					return true;
				}
				else if(currentProperty.getType() != null)
				{
					if(!checkTypeCompatibilityCompositeComponentTypeProperties(currentProperty, propertyComposite))
					{
						return false;
					}
				}
				else
				{
					throw new ValidationException("no type is given for property: " + currentPropertyName + " component: " + currentComponentName + " CompositeName: "
					        + currentCompositeName);
				}
				return true;
			}

		}

		return false;

	}

	/**
	 * This is the function that is used while checking out the compatibility of
	 * the types of the composite properties with the componentType properties.
	 * Such a check is required once the @soruce attribute is used for the
	 * PropertyValue of the component to check out if the type/element used at
	 * the soruced property of the composite really matches with the
	 * type/element componentType property (if the type/element is not defined
	 * in the component property but in the componentType)
	 */
	private boolean checkTypeCompatibilityCompositeComponentTypeProperties(Property propComponentType, Property propertyComposite) {
		QName typeCompType = propComponentType.getType();
		QName typeComposite = propertyComposite.getType();
		QName elementCompType = propComponentType.getElement();
		QName elementComposite = propertyComposite.getElement();

		NamespaceContext nsContextComponenttype = currentCompWrapper.getNamespaceContextComponentType();
		if(nsContextComponenttype == null)
		{
			throw new ValidationException("NamespaceContext is null for componenttype: " + currentComponentName + " CompositeName: " + currentCompositeName);
		}
		NamespaceContext nsContextComposite = compositeWrapper.getNamespaceContext();
		if(nsContextComposite == null)
		{
			throw new ValidationException("NamespaceContext is null for composite: " + currentCompositeName);
		}
		if(typeCompType != null)
		{
			// it is enough to check the local part of only one of the
			// properties
			// since the local part is already checked out above
			if(!isPrimitiveXSDType(typeCompType.getLocalPart()))
			{
				throw new ValidationException("Type is not an XSD basic type " + " Property: " + currentPropertyName + " Component name: " + currentComponentName
				        + " CompositeName: " + currentCompositeName);
			}

			if(!isNamespaceForXSDBasicTypes(nsContextComponenttype, typeCompType.getPrefix()))
			{
				throw new ValidationException("Namespace is not matchin the ns for XSD basic types for componentType Property: " + currentPropertyName
				        + "Component name: " + currentComponentName + " CompositeName: " + currentCompositeName);
			}
			if((typeCompType != null) && (typeCompType != typeComposite))
			{
				if(typeComposite == null)
				{
					throw new ValidationException("@type attr is required for the sourced compoiste property. property: " + currentPropertyName + " component: "
					        + currentComponentName + " CompositeName: " + currentCompositeName);
				}
				if(!typeCompType.getLocalPart().equals(typeComposite.getLocalPart()))
				{
					throw new ValidationException("local parts of @type attribute does not match for property: " + currentPropertyName + " component: "
					        + currentComponentName + " CompositeName: " + currentCompositeName);
				}
				String nameSpaceURI4TypeComp = (typeComposite.getPrefix() != "") ? nsContextComposite.getNamespaceURI(typeComposite.getPrefix())
				        : nsContextComposite.getNamespaceURI("xmlns");

				String nameSpaceURI4TypeCompType = (typeCompType.getPrefix() != "") ? nsContextComponenttype
				        .getNamespaceURI(typeCompType.getPrefix()) : nsContextComponenttype.getNamespaceURI("xmlns");

				if(!nameSpaceURI4TypeComp.equals(nameSpaceURI4TypeCompType))
				{
					throw new ValidationException("due to @soruce attribute usage namespace URIs do need to match for propert: " + currentPropertyName
					        + " component: " + currentComponentName + " CompositeName: " + currentCompositeName);
				}
			}
		}
		if((elementCompType != null) && (elementCompType != elementComposite))
		{
			if(elementComposite == null)
			{
				throw new ValidationException("@element attr is required for the sourced compoiste property. property: " + currentPropertyName + " component: "
				        + currentComponentName + " CompositeName: " + currentCompositeName);
			}
			logger.error("Currently Trentino only supports XSD basic types. No @element attribute should be used(check-out @soruce attribute) for the property: "
			        + currentPropertyName);
			
			if(!elementCompType.getLocalPart().equals(elementComposite.getLocalPart()))
			{
				throw new ValidationException("local parts of @element attribute does not match(Check out @source att) for property: " + currentPropertyName
				        + " component: " + currentComponentName + " CompositeName: " + currentCompositeName);
			}
			String nameSpaceURI4TypeComp = nsContextComposite.getNamespaceURI(elementComposite.getPrefix());

			String nameSpaceURI4TypeCompType = nsContextComponenttype.getNamespaceURI(elementCompType.getPrefix());

			if(!nameSpaceURI4TypeComp.equals(nameSpaceURI4TypeCompType))
			{
				throw new ValidationException("due to @soruce attribute usage namespace URIs do need to match for propert: " + currentPropertyName + " component: "
				        + currentComponentName + " CompositeName: " + currentCompositeName);
			}
		}
		return true;
	}

	/**
	 * This is the function that is used while checking out the compatibility of
	 * the types of the composite properties with the component properties. Such
	 * a check is required once the @soruce attribute is used for the
	 * PropertyValue of the component to check out if the type/element used at
	 * teh soruced property of teh composite really matches with the
	 * type/element component property
	 */
	private boolean checkTypeCompatibilityCompositeComponentProperties(PropertyValue propComponent, Property propertyComposite) {
		QName typeCompType = propComponent.getType();
		QName typeComposite = propertyComposite.getType();
		QName elementCompType = propComponent.getElement();
		QName elementComposite = propertyComposite.getElement();

		NamespaceContext nsContextComposite = compositeWrapper.getNamespaceContext();
		if(nsContextComposite == null)
		{
			throw new ValidationException("NamespaceContext is null for composite: " + currentCompositeName);
		}

		if((typeCompType != null) && (typeCompType != typeComposite))
		{
			if(typeComposite == null)
			{
				throw new ValidationException("@type attr is required for the sourced compoiste property. property: " + currentPropertyName + " component: "
				        + currentComponentName + " CompositeName: " + currentCompositeName);
			}
			if(!typeCompType.getLocalPart().equals(typeComposite.getLocalPart()))
			{
				throw new ValidationException("local parts of @type attribute does not match(check out @soruce attribute) for property: " + currentPropertyName
				        + " component: " + currentComponentName + " CompositeName: " + currentCompositeName);
			}

			String nameSpaceURI4TypeComp = (typeComposite.getPrefix() != "") ? nsContextComposite.getNamespaceURI(typeComposite.getPrefix())
			        : nsContextComposite.getNamespaceURI("xmlns");

			String nameSpaceURI4TypeCompType = (typeCompType.getPrefix() != "") ? nsContextComposite.getNamespaceURI(typeCompType.getPrefix())
			        : nsContextComposite.getNamespaceURI("xmlns");

			if(!nameSpaceURI4TypeComp.equals(nameSpaceURI4TypeCompType))
			{
				throw new ValidationException("due to @soruce attribute usage namespace URIs do need to match for propert: " + currentPropertyName + " component: "
				        + currentComponentName + " CompositeName: " + currentCompositeName);
			}

			// it is enough to check the local part of only one of the
			// properties
			// since the local part is already checked out above
			if(!isPrimitiveXSDType(typeCompType.getLocalPart()))
			{
				throw new ValidationException("Type is not an XSD basic type " + " Property: " + currentPropertyName + " Component name: " + currentComponentName
				        + " CompositeName: " + currentCompositeName);
			}

			if(!isNamespaceForXSDBasicTypes(nsContextComposite, typeComposite.getPrefix()))
			{
				throw new ValidationException("Namespace is not matchin the ns for XSD basic types for Property: " + currentPropertyName + " Component name: "
				        + currentComponentName + " CompositeName: " + currentCompositeName);
			}

			if(!isNamespaceForXSDBasicTypes(nsContextComposite, typeCompType.getPrefix()))
			{
				throw new ValidationException("Namespace is not matchin the ns for XSD basic types for componentType Property: " + currentPropertyName
				        + "Component name: " + currentComponentName + " CompositeName: " + currentCompositeName);
			}
		}

		if((elementCompType != null) && (elementCompType != elementComposite))
		{

			logger.error("Currently Trentino only supports XSD basic types. No @element attribute should be used(check-out @soruce attribute) for the property: "
			        + currentPropertyName);

			if(elementComposite == null)
			{
				throw new ValidationException("No @element attr is set for the sourced compoiste property. property: " + currentPropertyName + " component: "
				        + currentComponentName + " CompositeName: " + currentCompositeName);
			}

			if(!elementCompType.getLocalPart().equals(elementComposite.getLocalPart()))
			{
				throw new ValidationException("local parts of @element attribute does not match(Check out @source att) for property: " + currentPropertyName
				        + " component: " + currentComponentName + " CompositeName: " + currentCompositeName);
			}

			String nameSpaceURI4TypeComp = nsContextComposite.getNamespaceURI(elementComposite.getPrefix());

			String nameSpaceURI4TypeCompType = nsContextComposite.getNamespaceURI(elementCompType.getPrefix());

			if(!nameSpaceURI4TypeComp.equals(nameSpaceURI4TypeCompType))
			{
				throw new ValidationException("due to @soruce attribute usage namespace URIs do need to match for propert: " + currentPropertyName + " component: "
				        + currentComponentName + " CompositeName: " + currentCompositeName);
			}
		}
		return true;
	}
}
