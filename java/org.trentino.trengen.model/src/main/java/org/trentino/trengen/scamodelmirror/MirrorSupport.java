// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************
package org.trentino.trengen.scamodelmirror;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.trentino.trengen.xml.schema.AnyURI;
import org.trentino.trengen.xml.schema.MirrorClass;
import org.trentino.trengen.xml.schema.MirrorField;
import org.trentino.trengen.xml.schema.NCName;
import org.trentino.trengen.xml.schema.Name;
import org.trentino.trengen.xml.schema.QName;

/**
 * @author z002ttbb
 * 
 */
public class MirrorSupport implements MirrorClass {

	private final MirrorClass sourceObject;

	public MirrorSupport(MirrorClass so) {
		sourceObject = so;
	}

	private void getFieldsRecursive(Class givenClass, List<Field> listFields) {
		listFields.addAll(Arrays.asList(givenClass.getDeclaredFields()));
		if (givenClass.getSuperclass() != null) {
			getFieldsRecursive(givenClass.getSuperclass(), listFields);
		}
	}

	private List<MirrorField> fields;

	@Override
	public List<MirrorField> getFields() {

		if (fields == null) {
			List<MirrorField> result = new ArrayList<MirrorField>();

			List<Field> listFields = new ArrayList<Field>();
			getFieldsRecursive(sourceObject.getClass(), listFields);
			try {
				for (Field field : listFields) {
					if (isFieldNullOrEmpty(field)) {
						continue;
					}
					if(field.getName().equals("ms")){
						continue;
					}
					MirrorField mField = new MirrorField();
					mField.setArgument(field.getName());
					mField.setValue(getFieldValue(field));
					mField.setName(getName());

					String strAccessorName = field.getName();
					strAccessorName = strAccessorName.substring(1);
					String firstLetter = strAccessorName.substring(0, 1);
					firstLetter = firstLetter.toLowerCase();
					strAccessorName = firstLetter
							+ strAccessorName.substring(1);
					mField.setAccessor(strAccessorName);
					if (isSimple(field)) {
						mField.setSimple(true);
					} else if (List.class.isAssignableFrom(field.getType())) {
						mField.setList(true);
						mField.setListItems(getFieldValue(field));
						mField.setType(field.getGenericType());
					} else if (mField.isComplexNotList()) {
						try {
							mField.setMirrorObject(getFieldValue(field));
						} catch (IllegalArgumentException e) {
							continue;

						} catch (NullPointerException e) {
							continue;
						} catch (ExceptionInInitializerError e) {
							continue;
						} catch (Exception e) {
							e.printStackTrace();
							continue;
						}
						mField.setList(false);
						mField.setSimple(false);
						// System.out.println("Here5");
					} else {

						throw new IllegalStateException("Unhandled case");
					}

					result.add(mField);
					// System.out.println("Here6");

				}
			} catch (Exception e) {
				// System.out.println("Here7");
				throw new IllegalStateException(
						"This should never happens, it indicate an implementation error",
						e);

			}

			fields = result;
			// System.out.println("Finisheeeed");
		}

		return fields;
	}

	public java.lang.Object getFieldValue(Field field) {
		try {
			return sourceObject.getFieldValue(field);
		} catch (Exception e) {
			throw new IllegalStateException("Cannot acces method", e);
		}

	}

	private boolean isFieldNullOrEmpty(Field field) {
		java.lang.Object value;
		try {
			if (field == null) {
				return false;
			}
			value = getFieldValue(field);
		} catch (IllegalArgumentException e) {
			return false;

		} catch (Exception e) {
			throw new IllegalStateException(
					"This should never happens, it indicate an implementation error",
					e);
		}
		if (value == null) {

			return true;
		}

		if ((value instanceof List) && ((List) value).isEmpty()) {
			return true;
		}
		return false;
	}

	private boolean isSimple(Field field) {
		Class<?> fType = field.getType();
		if (fType.isPrimitive()) {
			return true;
		}
		Class[] simpleClasses = { String.class, AnyURI.class, Name.class,
				QName.class, NCName.class, Integer.class };

		for (Class simple : simpleClasses) {
			if (simple.equals(fType)) {
				return true;
			}
		}
		return false;
	}

	public String getNameGen() {
		return sourceObject.getNameGen();
	}

	public String getName() {
		try {
			Method method = sourceObject.getClass().getDeclaredMethod("name", null);
			if (method == null) {
				method = sourceObject.getClass().getSuperclass()
						.getDeclaredMethod("name", null);
				if (method == null) {
					return sourceObject.getNameGen();
				}

			}
			return ((NCName) method.invoke(sourceObject, null)).getNameStr();
		} catch (Exception e) {
			return sourceObject.getNameGen();
		}
	}

}
