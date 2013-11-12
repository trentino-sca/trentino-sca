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

import java.util.Set;

import javax.lang.model.type.TypeKind;

/**
 * utility class.
 */
public final class BuilderUtil {

	private BuilderUtil () {
	}

	/**
	 * Check if a class is in a set.
	 * @param classes
	 * @param name
	 * @return
	 */
	public static boolean isClassInTheSet(Set<ClassInfo> classes, String name) {
		ClassInfo inf = getClassInfoByClassName(name, classes);
		return inf != null;
	}

	/**
	 * @param typeName
	 * @param classes
	 * @return
	 */
	public static ClassInfo getClassInfoByClassName(String typeName, Set<ClassInfo> classes) {
		if(typeName == null)
		{
			throw new IllegalArgumentException("typeName cannot be null");
		}
		for (ClassInfo info : classes)
		{
			if(typeName.equals(info.getName()))
			{
				return info;
			}
		}
		return null;
	}

	public static String getPrimitiveTypeByKind(TypeKind kind) {

		switch (kind)
		{
			case BOOLEAN:
				return Boolean.class.getSimpleName();
			case BYTE:
				return Byte.class.getSimpleName();
			case SHORT:
				return Short.class.getSimpleName();
			case CHAR:
				return "char";
			case DOUBLE:
				return Double.class.getSimpleName();
			case LONG:
				return Long.class.getSimpleName();
			case FLOAT:
				return Float.class.getSimpleName();
			case INT:
				return Integer.class.getSimpleName();

			default:
				break;
		}
		throw new IllegalArgumentException("Type must be primivite type");

	}

}
