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

package org.trentino.trengen.model2mirrormodel;

import java.io.Serializable;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.lang.model.element.TypeElement;
import javax.lang.model.element.VariableElement;
import javax.lang.model.type.DeclaredType;
import javax.lang.model.type.MirroredTypeException;
import javax.lang.model.type.TypeKind;
import javax.lang.model.type.TypeMirror;
import javax.lang.model.type.WildcardType;
import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAnyAttribute;
import javax.xml.bind.annotation.XmlAnyElement;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlElementRefs;
import javax.xml.bind.annotation.XmlElements;
import javax.xml.bind.annotation.XmlEnumValue;
import javax.xml.bind.annotation.XmlSchemaType;
import javax.xml.namespace.QName;

import org.apache.log4j.Logger;

/**
 * the builder class used to generated fields from a Java variable element type.
 * @author z002ttbb
 */
public class FieldInfoBuilder implements Serializable {

	private static final long	             serialVersionUID	                  = 3460569910632126376L;

	protected static final Logger	         logger	                              = Logger.getLogger(FieldInfoBuilder.class);

	private static final String	             LIST	                              = List.class.getSimpleName();
	private static final String	             JAXB_ELEMENT	                      = JAXBElement.class.getSimpleName();
	private static final Set<String>	     acceptedTypes	                      = new HashSet<String>();

	/**
	 * This map contains all the special Jaxb list fields having an
	 * XMLElementRef annotation with class=JaxBElement.class. For that fields,
	 * we have to found the concrete type asociated with the JaxBElement<T>.
	 */
	private static final Map<String, String>	UNSPECIFIED_TYPES_IN_JAXB_ELEMENT	= new HashMap<String, String>();

	static
	{
		// initialize JAXBElements whose type parameters are unknown
		UNSPECIFIED_TYPES_IN_JAXB_ELEMENT.put("org.trentino.trengen.sca.model.PolicySet#policySetReference", "PolicySetReference");
		UNSPECIFIED_TYPES_IN_JAXB_ELEMENT.put("org.trentino.trengen.sca.model.PolicySet#intentMap", "IntentMap");
		UNSPECIFIED_TYPES_IN_JAXB_ELEMENT.put("org.trentino.trengen.sca.model.OperatorContentType#All", "OperatorContentType");
		UNSPECIFIED_TYPES_IN_JAXB_ELEMENT.put("org.trentino.trengen.sca.model.OperatorContentType#ExactlyOne", "OperatorContentType");
		UNSPECIFIED_TYPES_IN_JAXB_ELEMENT.put("org.trentino.trengen.sca.model.Callback#binding", "Binding");
		
		UNSPECIFIED_TYPES_IN_JAXB_ELEMENT.put("org.trentino.trengen.sca.model.TDefinitions#bindingType", "BindingType");
		UNSPECIFIED_TYPES_IN_JAXB_ELEMENT.put("org.trentino.trengen.sca.model.TDefinitions#implementationType", "ImplementationType");
		UNSPECIFIED_TYPES_IN_JAXB_ELEMENT.put("org.trentino.trengen.sca.model.TDefinitions#policySet", "PolicySet");
		UNSPECIFIED_TYPES_IN_JAXB_ELEMENT.put("org.trentino.trengen.sca.model.TDefinitions#intent", "Intent");

		acceptedTypes.add(Boolean.class.getSimpleName());
		acceptedTypes.add(Byte.class.getSimpleName());
		acceptedTypes.add(Short.class.getSimpleName());
		acceptedTypes.add(Double.class.getSimpleName());
		acceptedTypes.add(Long.class.getSimpleName());
		acceptedTypes.add(Float.class.getSimpleName());
		acceptedTypes.add(Integer.class.getSimpleName());
		acceptedTypes.add(Character.class.getSimpleName());
		acceptedTypes.add(String.class.getSimpleName());
		acceptedTypes.add(Date.class.getSimpleName());
		acceptedTypes.add(QName.class.getSimpleName());
		acceptedTypes.add(BigInteger.class.getSimpleName());
	}

	private Context	                         context;

	public FieldInfoBuilder (Context context) {
		if(context == null)
		{
			throw new IllegalArgumentException("Context cannot be null");
		}
		this.context = context;
	}

	/**
	 * For a given {@link VariableElement}, create the list of mapping fields.
	 * @param field
	 * @param classes
	 * @return list of FieldInfos, associated with a given variable element
	 */
	public List<FieldInfo> createFieldInfo(VariableElement field, Set<ClassInfo> classes) {
		logger.debug("createFieldInfo field : " + field.getSimpleName());
		List<FieldInfo> result = new ArrayList<FieldInfo>();
		String fName = field.getSimpleName().toString();
		TypeKind tk = field.asType().getKind();
		if(tk.isPrimitive())
		{
			createFieldForPrimitiveType(result, fName, tk);
		}
		else if(tk.equals(TypeKind.DECLARED))
		{
			createFieldForDeclaredType(field, classes, result, fName);
		}
		return result;
	}

	/**
	 * @param field
	 * @param classes
	 * @param result
	 * @param fName
	 */
	private void createFieldForDeclaredType(VariableElement field, Set<ClassInfo> classes, List<FieldInfo> result, String fName) {
		// if this is xmlAny, and no XMLelements or XMLelementrefs, then
		// reject
		XmlAnyElement anyElem = field.getAnnotation(XmlAnyElement.class);
		XmlElementRefs refs = field.getAnnotation(XmlElementRefs.class);
		XmlElements elems = field.getAnnotation(XmlElements.class);
		XmlAnyAttribute anyAtt = field.getAnnotation(XmlAnyAttribute.class);
		if((anyAtt != null) && elems == null && refs == null)
		{
			logger.debug("## Skipping any element or attribute :" + field.getSimpleName());
			return;
		}

		TypeMirror m = field.asType();
		String typeName = getTypeNameByTypeMirror(m);
		if(anyElem != null && (elems == null && refs == null))
		{
			createFieldInfoForAnyElem(field, result);
		}
		// handle enum type
		if(handleEnumType(field, result, typeName))
		{
			return;
		}

		boolean ok = acceptedTypes.contains(typeName);
		if(ok && "String".equals(typeName))
		{
			typeName = typeNameForStrings(field, typeName);
		}
		ok |= BuilderUtil.isClassInTheSet(classes, typeName);
		ok |= ((context.getPojosToProcess().get(typeName)) != null);
		if(ok)
		{
			FieldInfo fieldInfo = new FieldInfo(fName, typeName);
			result.add(fieldInfo);
		}
		else if(LIST.equals(typeName))
		{
			createFieldInfoForList(field, result);
		}
		else if(JAXB_ELEMENT.equals(typeName))
		{
			DeclaredType type = (DeclaredType) m;
			// FIXME we assume that one value is available
			TypeMirror arg0 = type.getTypeArguments().get(0);
			FieldInfo fieldInfo = new FieldInfo(fName, getTypeNameByTypeMirror(arg0));
			result.add(fieldInfo);
			logger.error("creating FieldInfo:handled JAXBElement" + " Mirror: " + arg0 + " Argument class:" + arg0.getClass());
		}
		else
		{
			throw new IllegalStateException("creating FieldInfo:Type not handled " + typeName + " Mirror: " + m + " Mirror class:" + m.getClass());
		}
	}

	private String typeNameForStrings(VariableElement field, String typeName) {
		XmlSchemaType type = field.getAnnotation(XmlSchemaType.class);
		if(type == null)
		{
			return typeName;
		}
		String res = type.name();
		if(res == null || res.length() == 0)
		{
			return typeName;
		}

		if(Character.isLowerCase(res.charAt(0)))
		{
			res = Character.toUpperCase(res.charAt(0)) + res.substring(1);
		}
		return res;
	}

	/**
	 * create a field for an enum type if necessary. The created field is stored
	 * in the List<FieldInfo> object.
	 * @param field
	 * @param result
	 * @param typeName
	 * @return true if the field is an enum type of false if not
	 */
	public boolean handleEnumType(VariableElement field, List<FieldInfo> result, String typeName) {
		XmlEnumValue enumType = field.getAnnotation(XmlEnumValue.class);
		if(enumType != null)
		{
			FieldInfo fieldInfo = new FieldInfo(enumType.value(), typeName);
			result.add(fieldInfo);
			return true;
		}
		return false;
	}

	/**
	 * @param result
	 * @param fName
	 * @param tk
	 */
	private void createFieldForPrimitiveType(List<FieldInfo> result, String fName, TypeKind tk) {
		String typeName = BuilderUtil.getPrimitiveTypeByKind(tk);
		FieldInfo fieldInfo = new FieldInfo(fName, typeName);
		result.add(fieldInfo);
	}

	/**
	 * @param field
	 * @param result
	 */
	private void createFieldInfoForAnyElem(VariableElement field, List<FieldInfo> result) {
		FieldInfo fieldInfo = new FieldInfo("content", LIST, "String");
		result.add(fieldInfo);
		return;

	}

	/**
	 * Create a field info, if the field is a list. This methods handle {@link XmlElements} and {@link XmlElementRefs}.
	 * @param field
	 * @param result
	 *            : the list of fields to be updated.
	 */
	public void createFieldInfoForList(VariableElement field, List<FieldInfo> result) {
		logger.debug("createFieldInfoForList: field: " + field.getSimpleName() + "\n List: " + result);
		TypeMirror m = field.asType();
		String fName = field.getSimpleName().toString();
		// check if the type is an xml group
		XmlElements elements = field.getAnnotation(XmlElements.class);
		if(elements != null)
		{
			handleXmlElementsAnnotation(result, elements);
			return;
		}

		XmlElementRefs elementRefs = field.getAnnotation(XmlElementRefs.class);
		if(elementRefs != null)
		{
			handleXmlElementRefsAnnotation(field, result, elementRefs);
			return;
		}

		// not a group, then check to parameterized type
		DeclaredType dectype = (DeclaredType) m;
		List<? extends TypeMirror> args = dectype.getTypeArguments();
		if(args == null || args.isEmpty())
		{
			throw new IllegalStateException("List without type found. conversion impossible. " + dectype);
		}
		TypeMirror tm = args.get(0);
		String parameterTypeName = getTypeNameByTypeMirror(tm);
		// If parameter is JAXBElement, then extract the type parameter of the
		// JAXBElement
		parameterTypeName = getParameterNameForJAXBElement(parameterTypeName, tm);
		TypeElement elem = context.getPojosToProcess().get(parameterTypeName);
		if(acceptedTypes.contains(parameterTypeName) || elem != null)
		{
			FieldInfo fieldInfo = new FieldInfo(fName, LIST, parameterTypeName);
			result.add(fieldInfo);
			return;
		}
	}

	/**
	 * Handle an {@link XmlElementRefs} annotation.
	 * @param field
	 * @param result
	 * @param elementRefs
	 */
	private void handleXmlElementRefsAnnotation(VariableElement field, List<FieldInfo> result, XmlElementRefs elementRefs) {

		logger.debug("Handle XML REFS Annotation: field " + field.getSimpleName() + " Refs: " + elementRefs.toString());

		TypeElement clazz = (TypeElement) field.getEnclosingElement();
		String clazzName = clazz.getQualifiedName().toString();
		for (XmlElementRef xmlElem : elementRefs.value())
		{
			handleXmlElementRefAnnotation(result, clazzName, xmlElem);
		}
	}

	/**
	 * handle an unique {@link XmlElementRef} annotation.
	 * @param result
	 *            : contain the list of generated fields to be updated. by the
	 *            handler
	 * @param clazzName
	 *            : name of the class where the {@link XmlElementRef} is
	 *            declared. This parameter is used to handle special cases where
	 *            the type argument of a JAXB Element is unknown
	 * @param xmlElem
	 *            . The element to handle
	 */
	private void handleXmlElementRefAnnotation(List<FieldInfo> result, String clazzName, XmlElementRef xmlElem) {
		String typeName = null;
		try
		{
			typeName = xmlElem.type().getSimpleName();
		} catch (MirroredTypeException e)
		{
			typeName = getTypeNameByTypeMirror(e.getTypeMirror());
		}
		TypeElement elem = context.getPojosToProcess().get(typeName);
		if(acceptedTypes.contains(typeName) || elem != null)
		{
			FieldInfo fieldInfo = new FieldInfo(xmlElem.name(), LIST, typeName);
			result.add(fieldInfo);
		}
		else if(JAXB_ELEMENT.equals(typeName))
		{

			// this is a special case where we don't know the real
			// type of the parameter since JAXB is used. It will be handled
			// case by case
			typeName = getTypeNameByPropertyNameAndClassName(xmlElem.name(), clazzName);
			FieldInfo fieldInfo = new FieldInfo(xmlElem.name(), LIST, typeName);
			result.add(fieldInfo);

		}
	}

	private String getTypeNameByPropertyNameAndClassName(String fieldName, String className) {
		String path = className + "#" + fieldName;
		String res = UNSPECIFIED_TYPES_IN_JAXB_ELEMENT.get(path);
		if(res == null)
		{
			throw new IllegalArgumentException("Field with JAXB Element not handled: " + path);
		}
		return res;
	}

	private List<FieldInfo> handleXmlElementsAnnotation(List<FieldInfo> result, XmlElements elements) {
		logger.debug("#handleXmlElementsAnnotation ");
		for (XmlElement xmlElem : elements.value())
		{
			String typeName = null;
			try
			{
				typeName = xmlElem.type().getSimpleName();
			} catch (MirroredTypeException e)
			{
				typeName = getTypeNameByTypeMirror(e.getTypeMirror());
			}

			FieldInfo fieldInfo = new FieldInfo(xmlElem.name(), LIST, typeName);
			result.add(fieldInfo);
		}
		return result;
	}

	/**
	 * extract the name of the type Parameter in the JAXBElement, if necessary.
	 * @param parameterTypeName
	 * @param tm
	 * @return the new parametertype from JAXB type declaration or former given
	 *         parameter, if not JAXElement declaraion found
	 */
	private String getParameterNameForJAXBElement(String parameterTypeName, TypeMirror tm) {
		if(!JAXB_ELEMENT.equals(parameterTypeName))
		{
			return parameterTypeName;
		}
		DeclaredType dectype = (DeclaredType) tm;
		List<? extends TypeMirror> args = dectype.getTypeArguments();
		if(args == null || args.isEmpty())
		{
			throw new IllegalStateException("JAxbElement without type parameter found. Type cannot be parsed. " + dectype);
		}

		TypeMirror typeIntheJaxElement = args.get(0);
		return getTypeNameByTypeMirror(typeIntheJaxElement);
	}

	/**
	 * The method return the type name for a given mirror type. It only handles
	 * Declared types and type wildcards. For declared types, the name of the
	 * Type elemnt is returned For Wirdcard types, the type name of the
	 * (Declared Type) of the upper bound is returned.
	 * @param m
	 *            : the {@link TypeMirror} for which the typename is required.
	 * @return the type name or an exception if the given type mirror is not
	 *         handled.
	 */
	public String getTypeNameByTypeMirror(TypeMirror m) {
		if(m == null)
		{
			throw new IllegalStateException("mirror cannot be null");
		}
		logger.debug("getTypeNameByTypeMirror " + m);
		if(m.getKind() == TypeKind.DECLARED)
		{
			DeclaredType typeObj = (DeclaredType) m;
			TypeElement asElement = (TypeElement) typeObj.asElement();
			String typeName = asElement.getSimpleName().toString();
			logger.debug("return " + typeName);
			return typeName;
		}
		else if(m.getKind() == TypeKind.WILDCARD)
		{
			logger.error("getTypeNameByTypeMirror:Wildcard found" + m + " Class:" + m.getClass());
			if(m instanceof WildcardType)
			{
				logger.debug("Wildcard type found");
				WildcardType typeObj = (WildcardType) m;
				String typeName = getTypeNameByTypeMirror(typeObj.getExtendsBound());
				logger.debug("return " + typeName);
				return typeName;
			}
			else
			{
				throw new IllegalStateException("wildcard Type not supported");
			}
		}
		else
		{
			logger.error("getTypeNameByTypeMirror:Type not handled" + m + " Class:" + m.getClass());
			return null;
		}
	}

}
