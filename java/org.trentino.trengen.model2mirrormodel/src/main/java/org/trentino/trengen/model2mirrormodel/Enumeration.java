/************************************************************************************
 * // Trentino - A C++ based lightweight, non-invasive SCA runtime.
 * // Copyright (C) Siemens AG, 2012
 * // All Rights Reserved
 * // http://trentino.sourceforge.net/
 * //
 * // This library is free software; you can redistribute it and/or
 * // modify it under the terms of the GNU Lesser General Public
 * // License as published by the Free Software Foundation; either
 * // version 2.1 of the License, or (at your option) any later version.
 * //
 * // This library is distributed in the hope that it will be useful,
 * // but WITHOUT ANY WARRANTY; without even the implied warranty of
 * // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * // Lesser General Public License for more details.
 * //
 * // You should have received a copy of the GNU Lesser General Public
 * // License along with this library; if not, write to the Free Software
 * // Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * //
 *********************************************************************************/

package org.trentino.trengen.model2mirrormodel;

import java.util.Iterator;
import java.util.ArrayList;

public class Enumeration {
	/**
	 * The name of the enumaration
	 */
	private String	          name;

	/**
	 * The strings in the enumeration
	 */
	private ArrayList<String>	strings;

	public Enumeration (String name) {
		this.setName(name);
		this.strings = new ArrayList<String>();
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getName() {
		return name;
	}

	public void addString(String value) {
		if(value == null || strings.contains(value))
		{
			return;
		}
		strings.add(value);
	}

	public Iterator<String> iterator() {
		return strings.iterator();
	}
}
