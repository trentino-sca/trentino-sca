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

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.trentino.trengen.scamodelmirror.Composite;
import org.trentino.trengen.xml.schema.AnyURI;
import org.trentino.trengen.xml.schema.MirrorClass;
import org.trentino.trengen.xml.schema.MirrorField;
import org.trentino.trengen.xml.schema.NCName;
import org.trentino.trengen.xml.schema.Name;

/**
 * CompositeMirrorWrappers are used to be passed to the generate function of
 * ModelLoaderGenerator
 */
public class CompositeMirrorWrapper implements MirrorClass {

	protected Composite	mcomposite	= null;

	public Composite getComposite() {
		return mcomposite;
	}

	public void setComposite(Composite composite) {
		this.mcomposite = composite;
	}

	private void getFieldsRecursive(Class<?> givenClass, List<Field> listFields) {
		listFields.addAll(Arrays.asList(givenClass.getDeclaredFields()));
		if(givenClass.getSuperclass() != null)
		{
			getFieldsRecursive(givenClass.getSuperclass(), listFields);
		}
	}

	public List<MirrorField>	fields;

	@Override
	public List<MirrorField> getFields() {
		if(fields == null)
		{
			List<MirrorField> result = new ArrayList<MirrorField>();

			List<Field> listFields = new ArrayList<Field>();
			getFieldsRecursive(this.getClass(), listFields);

			try
			{
				for (Field field : listFields)
				{
					if(isFieldNullOrEmpty(field))
					{
						continue;
					}
					MirrorField mField = new MirrorField();
					mField.setArgument(field.getName());
					mField.setValue(field.get(this));
					mField.setName(getName());

					String strAccessorName = field.getName();
					strAccessorName = strAccessorName.substring(1);
					String firstLetter = strAccessorName.substring(0, 1);
					firstLetter = firstLetter.toLowerCase();
					strAccessorName = firstLetter + strAccessorName.substring(1);
					mField.setAccessor(strAccessorName);
					if(isSimple(field))
					{
						mField.setSimple(true);
					}
					else if(List.class.isAssignableFrom(field.getType()))
					{
						mField.setList(true);
						mField.setListItems(field.get(this));
						mField.setType(field.getGenericType());
					}
					else if(mField.isComplexNotList())
					{
						try
						{
							mField.setMirrorObject(field.get(this));
						} catch (IllegalArgumentException e)
						{
							continue;

						} catch (IllegalAccessException e)
						{
							continue;

						} catch (NullPointerException e)
						{
							continue;
						} catch (ExceptionInInitializerError e)
						{
							continue;
						} catch (Exception e)
						{
							e.printStackTrace();
							continue;
						}
						mField.setList(false);
						mField.setSimple(false);
					}
					else
					{

						throw new IllegalStateException("Unhandled case");
					}

					result.add(mField);
				}
			} catch (Exception e)
			{
				throw new IllegalStateException("This should never happen, it indicate an implementation error", e);

			}

			fields = result;
		}

		return fields;
	}

	private boolean isFieldNullOrEmpty(Field field) {
		java.lang.Object value;
		try
		{
			if(field == null)
			{
				return false;
			}
			value = field.get(this);
		} catch (IllegalArgumentException e)
		{
			return false;

		} catch (IllegalAccessException e)
		{
			return false;

		} catch (Exception e)
		{
			throw new IllegalStateException("This should never happen, it indicate an implementation error", e);
		}
		if(value == null)
		{

			return true;
		}
		if((value instanceof List) && ((List<?>) value).isEmpty())
		{
			return true;
		}
		return false;
	}

	private boolean isSimple(Field field) {
		Class<?> fType = field.getType();
		if(fType.isPrimitive())
		{
			return true;
		}
		Class<?>[] simpleClasses =
		{ String.class, AnyURI.class, Name.class, NCName.class };

		for (Class<?> simple : simpleClasses)
		{
			if(simple.equals(fType))
			{
				return true;
			}
		}
		return false;
	}

	public String getName() {
		try
		{
			Method method = this.getClass().getDeclaredMethod("name", (Class<?>) null);
			if(method == null)
			{
				method = this.getClass().getSuperclass().getDeclaredMethod("name", (Class<?>) null);
				if(method == null)
				{
					return mNameGen;
				}

			}
			return ((NCName) method.invoke(this, (Class<?>) null)).getNameStr();
		} catch (Exception e)
		{
			return mNameGen;
		}
	}

	public String getClassName() {
		return "CompositeWrapper";
	}

	public String	mNameGen	= "deneme";

	public void setNameGen(String nameGenToSet) {
		mNameGen = nameGenToSet;
	}

	public String getNameGen() {
		return mNameGen;
	}

	public java.lang.Object getFieldValue(Field field) {
		try
		{
			return field.get(this);
		} catch (Exception e)
		{
			throw new IllegalStateException(e);
		}
	}
}
