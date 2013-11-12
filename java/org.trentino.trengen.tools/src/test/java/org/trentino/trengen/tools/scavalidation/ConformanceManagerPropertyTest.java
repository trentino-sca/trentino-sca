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

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

import javax.xml.bind.JAXBElement;
import javax.xml.namespace.NamespaceContext;
import javax.xml.namespace.QName;

import org.apache.log4j.Logger;
import org.apache.log4j.xml.DOMConfigurator;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.Property;
import org.trentino.trengen.sca.model.PropertyValue;
import org.trentino.trengen.sca.model.ValueType;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.trengen.TrentinoTest;

public class ConformanceManagerPropertyTest extends TrentinoTest {

	protected static final Logger	          logger	                   = Logger.getLogger(ConformanceManager4ReferenceAndServiceTest.class);
	private static CompositeWrapper	          compositeWrapper	           = null;
	private static ConformanceManagerProperty	conformanceManagerProperty	= null;
	private Property	                      property	                   = null;
	private PropertyValue	                  propertyValue	               = null;

	/*
	 * Sample Property fixture <property name="complexFoo" type="xsd:string">
	 * <value> 234 </value> </property>
	 */
	@BeforeClass
	public static void setUpBeforeClass() {
		FixtureUtility fu = new FixtureUtility();
		compositeWrapper = fu.setFixtureUtility();
		conformanceManagerProperty = new ConformanceManagerProperty(compositeWrapper);
		ComponentWrapper mockComponenWrapper = new ComponentWrapper();
		mockComponenWrapper.setNamespaceContextComponentType(compositeWrapper.getNamespaceContext());
		Component mockComponent = new Component();
		ComponentType mockComponentType = new ComponentType();
		mockComponent.setName("TestComponent");
		mockComponenWrapper.setScaModelComponent(mockComponent);
		mockComponenWrapper.setScaModelComponentType(mockComponentType);
		conformanceManagerProperty.setComponentWrapper(mockComponenWrapper);
	}

	@Before
	public void initProperty() {
		property = new Property();
		QName type = new QName(null, "string", "xsd");
		property.setName("TestProperty");
		property.setType(type);
		property.setMany(false);
		property.setMustSupply(false);
		ValueType valueType = new ValueType();
		valueType.getContent().add("123");
		QName qName = new QName(null, "string", "xsd");
		JAXBElement<ValueType> propChildObj = new JAXBElement<ValueType>(qName, ValueType.class, valueType);
		property.getContent().add(propChildObj);

		propertyValue = new PropertyValue();
		propertyValue.setName("TestPropertyValue");
		propertyValue.setType(type);
		propertyValue.setMany(false);
		ValueType valueTypePropertyValue = new ValueType();
		valueTypePropertyValue.getContent().add("123");
		QName qNamePropertyValue = new QName(null, "string", "xsd");
		JAXBElement<ValueType> propChildObjPropertyValue = new JAXBElement<ValueType>(qNamePropertyValue, ValueType.class, valueTypePropertyValue);
		propertyValue.getContent().add(propChildObjPropertyValue);
		setCurrentPropertyPropertyValue(property, propertyValue);
	}

	private static void setCurrentPropertyPropertyValue(final Property p, final PropertyValue pValue) {
		try
		{
			Field prop = ConformanceManagerProperty.class.getDeclaredField("currentProperty");
			prop.setAccessible(true);
			prop.set(conformanceManagerProperty, p);

			Field propValue = ConformanceManagerProperty.class.getDeclaredField("currentPropValue");
			propValue.setAccessible(true);
			propValue.set(conformanceManagerProperty, pValue);
		} catch (Exception ex)
		{
			return;
		}

	}

	// ________________________ Tests for checkComponentTypeProperty(public)
	// ____________________
	// following called functions are tested explicitly: checkValues,
	// checkValuesComponent, findMatchingPropertyValue,
	// @Test
	// public void testcheckComponentTypeProperty()
	// {
	// conformanceManagerProperty.setComponentWrapper()
	// boolean result =
	// conformanceManagerProperty.checkComponentTypeProperty(property);
	// assertTrue(result);
	// }
	@Test
	public void testmustsupply() {
		try
		{
			property.setMustSupply(true);
			setCurrentPropertyPropertyValue(property, null);

			boolean result = conformanceManagerProperty.checkComponentTypeProperty(property);

			property.setMustSupply(false);
			assertFalse(result);
		} catch (Exception e)
		{
			return;
		}

	}

	@Test(expected = ValidationException.class)
	public void testmustsupply_NoValSpecified() {
		try
		{
			property.setMustSupply(true);
			PropertyValue mockPropValue = new PropertyValue();
			mockPropValue.setSource(null);
			mockPropValue.setValue(null);

			setCurrentPropertyPropertyValue(property, mockPropValue);
			boolean result = conformanceManagerProperty.checkComponentTypeProperty(property);

			assertFalse(result);
		} finally
		{
			// reset the changed fixture property
			property.setMustSupply(false);
			setCurrentPropertyPropertyValue(property, propertyValue);
		}

	}

	// ________________________ Tests for check_ASM40010(private)
	@Test(expected = ValidationException.class)
	public final void testcheckASM40010() throws Throwable {
		Method method = ConformanceManagerProperty.class.getDeclaredMethod("check_ASM40010", Property.class);
		method.setAccessible(true);

		// add an extra element to the fixture Property
		QName typeOrElement = new QName(null, "extraElement", "xsd");

		property.setElement(typeOrElement);
		boolean result;

		result = (Boolean) method.invoke(conformanceManagerProperty, property);

		// reset the fixture
		property.setElement(null);

		assertFalse(result);
	}

	// _______________________ Tests for checkValues (private)

	private Method getMethodcheckValues() throws NoSuchMethodException {
		Method method = ConformanceManagerProperty.class.getDeclaredMethod("CheckValues", Property.class, String.class);
		method.setAccessible(true);
		return method;
	}

	@Test(expected = ValidationException.class)
	public final void testCheckValues() throws Throwable {
		List<Object> listContent = new ArrayList<Object>();
		listContent = property.getContent();
		int sizeContent = listContent.size();

		ValueType valueType = null;
		for (int i = 0; i < sizeContent; i++)
		{
			Object propChildObj = listContent.get(i);

			if(propChildObj.getClass().equals(JAXBElement.class))
			{
				JAXBElement<?> valueTypeJaxBElement = ((JAXBElement<?>) propChildObj);
				valueType = (ValueType) valueTypeJaxBElement.getValue();
				valueType.getContent().add("Violating value Type");
				break;
			}
		}

		Method method = getMethodcheckValues();
		boolean result;
		try
		{
			result = (Boolean) method.invoke(conformanceManagerProperty, property, "Trengen Automated Test");
		} catch (InvocationTargetException e)
		{
			throw e.getTargetException();
		}

		// reset the changed fixture property
		if(valueType != null)
		{
			property.getContent().remove(valueType);
		}

		assertFalse(result);
	}

	// _______________________ Tests for findMatchingPropertyValue
	// prepare the inputs in a way the given component has a propertyValue named
	// propertyName
	@Test
	public final void testfindMatchingPropertyValue_NoMatching() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		// prepare the inputs in a way the given componentType has a property
		// named propertyName
		Component comp = new Component();
		String propertyName = null;

		Method method = ConformanceManagerProperty.class.getDeclaredMethod("findMatchingPropertyValue", Component.class, String.class);
		method.setAccessible(true);
		Property outputProperty = (Property) method.invoke(conformanceManagerProperty, comp, propertyName);

		assertNull(outputProperty);
	}

	// ________________________ Tests for check_ASM50035(private)
	@Test(expected = ValidationException.class)
	public final void testcheck_ASM50035() throws Throwable {
		Method method = ConformanceManagerProperty.class.getDeclaredMethod("check_ASM50035", PropertyValue.class);
		method.setAccessible(true);

		// add an extra element to the fixture Property
		QName typeOrElement = new QName(null, "extraElement", "xsd");

		propertyValue.setElement(typeOrElement);
		boolean result = doInvokeOnProperryValue(method);

		// reset the fixture
		propertyValue.setElement(null);
		assertFalse(result);
	}

	private Boolean doInvokeOnProperryValue(Method method) throws Throwable {
		try
		{
			return (Boolean) method.invoke(conformanceManagerProperty, propertyValue);
		} catch (InvocationTargetException e)
		{
			throw e.getTargetException();
		}
	}

	// _______________________ Tests
	// checkTypeCompatibilityComponentTypeComponent

	private Method getMethodcheckTypeCompatibilityComponentTypeComponent() throws NoSuchMethodException {
		Method method = ConformanceManagerProperty.class.getDeclaredMethod("checkTypeCompatibilityComponentTypeComponent", Property.class,
		        PropertyValue.class);
		method.setAccessible(true);
		return method;
	}

	@Test(expected = ValidationException.class)
	public final void testcheckTypeCompatibilityComponentTypeComponent() throws NoSuchMethodException, IllegalAccessException,
	        InvocationTargetException {
		// prepare the data
		property.setElement(null);
		property.setType(null);

		Method method = getMethodcheckTypeCompatibilityComponentTypeComponent();
		boolean result = (Boolean) method.invoke(conformanceManagerProperty, property, propertyValue);

		// reset the changed fixture property
		QName type = new QName(null, "string", "xsd");
		property.setType(type);

		assertFalse(result);
	}

	@Test(expected = ValidationException.class)
	public final void testcheckTypeCompatibilityComponentTypeComponent_PropPropValCompareLocals() throws NoSuchMethodException,
	        IllegalAccessException, InvocationTargetException {
		// prepare the data
		QName typeForProp = new QName(null, "string", "xsd");
		QName typeForPropVal = new QName(null, "integer", "xsd");
		property.setType(typeForProp);
		propertyValue.setType(typeForPropVal);

		Method method = getMethodcheckTypeCompatibilityComponentTypeComponent();
		boolean result = (Boolean) method.invoke(conformanceManagerProperty, property, propertyValue);

		// reset the changed fixture property
		propertyValue.setType(typeForProp);

		assertFalse(result);
	}

	@Test(expected = ValidationException.class)
	public final void testcheckTypeCompatibilityComponentTypeComponent_PropPropValCompareURIs() throws NoSuchMethodException, IllegalAccessException,
	        InvocationTargetException {
		// prepare the data (propertyValue and property includes types with the
		// same local part but not same URIs)
		QName typeForPropVal = new QName(null, "string", "xsd2");
		propertyValue.setType(typeForPropVal);

		Method method = getMethodcheckTypeCompatibilityComponentTypeComponent();
		boolean result = (Boolean) method.invoke(conformanceManagerProperty, property, propertyValue);

		// reset the changed fixture property
		typeForPropVal = new QName(null, "string", "xsd");
		propertyValue.setType(typeForPropVal);

		assertFalse(result);
	}

	// ________________________ Tests for checkValuesComponent(private)

	private Method getMethodcheckValuesComponent() throws NoSuchMethodException {
		Method method = ConformanceManagerProperty.class.getDeclaredMethod("checkValuesComponent", PropertyValue.class);
		method.setAccessible(true);
		return method;
	}

	@Test(expected = ValidationException.class)
	public final void testCheckValuesComponent() throws Throwable {
		// prepare the Property to include more than one value elements within
		// the value child element of component properties
		// so far such a Property should return false since it is not supported
		// yet
		List<Object> listContent = new ArrayList<Object>();
		listContent = propertyValue.getContent();
		int sizeContent = listContent.size();

		ValueType valueType = null;
		for (int i = 0; i < sizeContent; i++)
		{
			Object propChildObj = listContent.get(i);

			if(propChildObj.getClass().equals(JAXBElement.class))
			{
				JAXBElement<?> valueTypeJaxBElement = ((JAXBElement<?>) propChildObj);
				valueType = (ValueType) valueTypeJaxBElement.getValue();
				valueType.getContent().add("Violating value Type");
				break;
			}
		}

		/*
		 * Property mock = EasyMock.createMock(Property.class);
		 * EasyMock.expect(mock.getType()).andReturn(qName);
		 * EasyMock.replay(mock); QName qName2 = mock.getType();
		 */

		Method method = getMethodcheckValuesComponent();
		boolean result = doInvokeOnProperryValue(method);
		// reset the changed fixture property
		if(valueType != null)
		{
			propertyValue.getContent().remove(valueType);
		}
		assertFalse(result);
	}

	// prepare the inputs in a way the given component has a propertyValue named
	// propertyName
	@Test
	public final void testfindMatchingPropertyValueNoMatching() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		// prepare the inputs in a way the given component has a propertyValue
		// named propertyName
		ComponentType compType = new ComponentType();
		String propertyName = null;

		Method method = ConformanceManagerProperty.class.getDeclaredMethod("findMatchingProperty", ComponentType.class, String.class);
		method.setAccessible(true);
		Property outputProperty = (Property) method.invoke(conformanceManagerProperty, compType, propertyName);

		assertNull(outputProperty);
	}

	// _______________________________ Test for checkValueType
	@Test
	public final void testcheckValueType() {
		// prepare the data set to work on
		propertyValue.setValue("123");
		property.setType(null);
		setCurrentPropertyPropertyValue(property, propertyValue);

		try
		{
			Method method = ConformanceManagerProperty.class.getDeclaredMethod("checkValueType");
			method.setAccessible(true);
			boolean result = (Boolean) method.invoke(conformanceManagerProperty);

			assertFalse(result);
		} catch (Exception ex)
		{
			return;
		}

	}

	// _______________________________ checkValueTypeCompatibility
	// no need to test

	// ********************************************************************
	// ______________________ Tests for checkComponentProperty (public)
	// tested explicitly with a correct sample and implicitly by testing all the
	// private sub functions with faulty datasets
	// @Test
	// public void testcheckComponentProperty()
	// {
	// boolean result =
	// conformanceManagerProperty.checkComponentProperty(propertyValue);
	// assertTrue(result);
	// }

	// _______________________ Tests for findMatchingProperty(private)
	// prepare the inputs in a way the given componentType does not have any
	// property named propertyName
	// @Test
	// public void testfindMatchingProperty_MatchingExists() throws
	// SecurityException, NoSuchMethodException, IllegalArgumentException,
	// IllegalAccessException, InvocationTargetException
	// {
	// //prepare the inputs in a way the given componentType does not have any
	// property named propertyName
	// ComponentType compType = null;
	// String propertyName = null;
	//
	// Method method =
	// ConformanceManagerProperty.class.getDeclaredMethod("findMatchingProperty",
	// String.class);
	// method.setAccessible(true);
	// Property outputProperty = (Property)
	// method.invoke(conformanceManagerProperty, compType, propertyName);
	//
	// assertNotNull(outputProperty);
	// }

	// test private method: findMatchingPropertyValue
	// prepare the inputs in a way the given component has a propertyValue named
	// propertyName
	@Test
	public final void testfindMatchingProperty_NoMatching() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		// prepare the inputs in a way the given componentType has a property
		// named propertyName
		ComponentType compType = new ComponentType();
		String propertyName = null;

		Method method = ConformanceManagerProperty.class.getDeclaredMethod("findMatchingProperty", ComponentType.class, String.class);
		method.setAccessible(true);
		Property outputProperty = (Property) method.invoke(conformanceManagerProperty, compType, propertyName);

		assertNull(outputProperty);
	}

	// _______________________ Tests checkSource (private)
	// not tested

	// _______________________ Tests for isWhiteSpaceYes
	@Test
	public final void testisWhiteSpaceYes() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Method method = ConformanceManagerProperty.class.getDeclaredMethod("isWSpace", String.class);
		method.setAccessible(true);
		boolean result = (Boolean) method.invoke(conformanceManagerProperty, "    ");
		assertTrue(result);
	}

	@Test
	public final void testisWhiteSpaceNo() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Method method = ConformanceManagerProperty.class.getDeclaredMethod("isWSpace", String.class);
		method.setAccessible(true);
		boolean result = (Boolean) method.invoke(conformanceManagerProperty, "  sdf  ");
		assertFalse(result);
	}

	// _______________________ Tests for
	// isNamespaceForXSDBasicTypesMatchingPrefix
	private Method getMethodisNamespaceForXSDBasicTypes() throws NoSuchMethodException {
		Method method = ConformanceManagerProperty.class.getDeclaredMethod("isNamespaceForXSDBasicTypes", NamespaceContext.class, String.class);
		method.setAccessible(true);
		return method;
	}

	@Test
	public final void testisNamespaceForXSDBasicTypesMatchingPrefix() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		NamespaceContext ns = compositeWrapper.getNamespaceContext();
		Method method = getMethodisNamespaceForXSDBasicTypes();
		boolean result = (Boolean) method.invoke(conformanceManagerProperty, ns, "xsd");
		assertTrue(result);
	}

	@Test(expected = ValidationException.class)
	public final void testisNamespaceForXSDBasicTypesNoMatchingPrefix() throws NoSuchMethodException, IllegalAccessException,
	        InvocationTargetException {
		NamespaceContext ns = compositeWrapper.getNamespaceContext();
		Method method = getMethodisNamespaceForXSDBasicTypes();
		boolean result = (Boolean) method.invoke(conformanceManagerProperty, ns, "xsdXXX");
	}

	@Test(expected = ValidationException.class)
	public final void testisNamespaceForXSDBasicTypesNullNamespace() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		NamespaceContext ns = null;
		Method method = getMethodisNamespaceForXSDBasicTypes();
		boolean result = (Boolean) method.invoke(conformanceManagerProperty, ns, "    ");
		assertFalse(result);
	}

	@Test(expected = ValidationException.class)
	public final void testisNamespaceForXSDBasicTypesNullPrefix() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		NamespaceContext ns = compositeWrapper.getNamespaceContext();
		Method method = getMethodisNamespaceForXSDBasicTypes();
		boolean result = (Boolean) method.invoke(conformanceManagerProperty, ns, null);
		assertFalse(result);
	}

	// _______________________ Tests for isPrimitiveXSDTypeNo

	private Method getMethodisPrimitiveXSDType() throws NoSuchMethodException {
		Method method = ConformanceManagerProperty.class.getDeclaredMethod("isPrimitiveXSDType", String.class);
		method.setAccessible(true);
		return method;
	}

	@Test(expected = ValidationException.class)
	public void testisPrimitiveXSDTypeNo() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Method method = getMethodisPrimitiveXSDType();
		boolean result = (Boolean) method.invoke(conformanceManagerProperty, "xyz");
		assertFalse(result);
	}

	@Test
	public void testisPrimitiveXSDType() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		Method method = getMethodisPrimitiveXSDType();
		boolean result = (Boolean) method.invoke(conformanceManagerProperty, "string");
		assertTrue(result);
	}

	// _______________________ Tests for
	// OnNewPropertyOfCompositeTwoSameNamedProperties

	@Test(expected = ValidationException.class)
	public void testOnNewPropertyOfCompositeTwoSameNamedProperties() {
		Property property = new Property();
		property.setName("NameMadeUp");
		ConformanceManagerProperty conformanceManagerProperty = new ConformanceManagerProperty(compositeWrapper);
		conformanceManagerProperty.OnNewPropertyOfComposite(property);
		boolean result = conformanceManagerProperty.OnNewPropertyOfComposite(property);
		assertFalse(result);
	}

	@Test
	public void testOnNewPropertyOfComposite2NewProperties() {
		Property property = new Property();
		property.setName("NameMadeUp");
		ConformanceManagerProperty conformanceManagerProperty = new ConformanceManagerProperty(compositeWrapper);
		conformanceManagerProperty.OnNewPropertyOfComposite(property);
		property.setName("NameMadeUp2");
		boolean result = conformanceManagerProperty.OnNewPropertyOfComposite(property);
		assertTrue(result);
	}
}
