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
import java.util.List;
import java.util.Set;

import javax.lang.model.element.ElementKind;
import javax.lang.model.element.Modifier;
import javax.lang.model.element.TypeElement;
import javax.lang.model.element.VariableElement;
import javax.lang.model.type.DeclaredType;
import javax.lang.model.type.NoType;
import javax.lang.model.type.TypeMirror;
import javax.lang.model.util.ElementFilter;
import javax.xml.bind.annotation.XmlAttribute;

import org.apache.log4j.Logger;

/**
 * Read the java model elements and gerenates corresponding ClassInfo model
 * based on.
 */
public class ClassInfoBuilder implements Serializable {

	private static final long	  serialVersionUID	= 1L;
	protected static final Logger	logger	       = Logger.getLogger(ClassInfoBuilder.class);

	private Context	              context;
	private FieldInfoBuilder	  fieldBuilder;

	public ClassInfoBuilder (Context context) {
		this.context = context;
		fieldBuilder = new FieldInfoBuilder(context);
	}

	/**
	 * Create class infos and put the result in a Set. recurse on Super classes.
	 * @param entity
	 * @param processed
	 * @param classes
	 */
	public void createClassInfos(TypeElement entity, Set<ClassInfo> classes) {
		logger.debug("##################################################################\n");
		logger.debug("createClassInfos entity: " + entity.getSimpleName());
		if(!entity.getKind().isClass())
		{
			return;
		}
		if(entity.getSimpleName() == null)
		{
			throw new IllegalStateException("Entity name should not be null");
		}

		String name = entity.getSimpleName().toString();
		boolean created = BuilderUtil.isClassInTheSet(classes, name);
		if(created)
		{
			logger.debug("Class allreday created: " + name);
			return;
		}
		// Init the class info
		ClassInfo inf = new ClassInfo(name);
		if(entity.getKind() == ElementKind.ENUM)
		{
			inf.setEnum(true);
		}
		classes.add(inf);
		setAbstractIfAbstract(inf, entity);
		// Create the Supertype
		if(entity.getSuperclass() != null && !(entity.getSuperclass() instanceof NoType))
		{
			createClassSuperClass(entity, classes, inf);
		}

		// Create the fields
		List<VariableElement> fields = ElementFilter.fieldsIn(entity.getEnclosedElements());

		if(fields == null || fields.isEmpty())
		{
			logger.debug("No fields found for entity: " + name);
			return;
		}

		logger.debug("Creating fields for class: " + name);
		for (VariableElement field : fields)
		{
			// serialVersionUID is not used
			if("serialVersionUID".equals(field.getSimpleName().toString()))
			{
				continue;
			}
			if(inf.isEnum() && field.getKind() != ElementKind.ENUM_CONSTANT)
			{
				logger.debug("Non enum constant not handled for enum types");
				continue;
			}
			List<FieldInfo> fInfos = fieldBuilder.createFieldInfo(field, classes);
			if(fInfos != null)
			{
				if(isAttribute(field) && fInfos.size() == 1)
				{
					fInfos.get(0).setAttribute(true);
				}
				inf.getFieldInfos().addAll(fInfos);
			}
		}
	}

	/**
	 * Set the class abstract if the entity is abstract.
	 * @param inf
	 * @param entity
	 */
	private void setAbstractIfAbstract(ClassInfo inf, TypeElement entity) {
		Set<Modifier> modifiers = entity.getModifiers();
		if(modifiers == null || modifiers.isEmpty() || !modifiers.contains(Modifier.ABSTRACT))
		{
			return;
		}
		inf.setAbstractClass(true);
	}

	/**
	 * return true if the given field is an attribute.
	 * @param field
	 * @return
	 */
	private boolean isAttribute(VariableElement field) {
		return field.getAnnotation(XmlAttribute.class) != null;
	}

	/**
	 * Create the super class for a given class.
	 * @param entity
	 * @param classes
	 * @param inf
	 */
	public void createClassSuperClass(TypeElement entity, Set<ClassInfo> classes, ClassInfo inf) {
		logger.debug("superclass for entity: " + entity.getSimpleName());
		TypeMirror supClsMir = entity.getSuperclass();
		DeclaredType decSuperType = (DeclaredType) supClsMir;
		TypeElement asElement = (TypeElement) decSuperType.asElement();
		String typeName = asElement.getSimpleName().toString();

		ClassInfo supCls = BuilderUtil.getClassInfoByClassName(typeName, classes);
		if(supCls == null)
		{
			createClassInfos(asElement, classes);
		}
		supCls = BuilderUtil.getClassInfoByClassName(typeName, classes);
		if(supCls == null)
		{
			throw new IllegalStateException("Super class should have been constructed. Check if the class hierachy is consistent.");
		}
		logger.debug("superclass for entity: " + entity.getSimpleName() + " is: " + supCls.getName());
		inf.setSuperClass(supCls);
	}

}
