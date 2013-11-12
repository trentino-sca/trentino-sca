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

package org.trentino.trengen.cpp.model;

/**
 * @author z002ttbb
 *         1.8.2.5. @Property Annotation on a service implementation class data
 *         member to define a property of the service. Format: //
 * @Property(name=�propertyName�, type=�typeQName� // default=�defaultValue�,
 *                                required=�true�)
 *                                where
 *                                � name (optional)
 *                                specifies the name of the property. If name is
 *                                not specified the property name is taken from
 *                                the name of the following data member. � type
 *                                (optional) specifies the type of the property.
 *                                If not specified the type of the property is
 *                                based on the C++ mapping of the type of the
 *                                following data member to an xsd type as
 *                                defined in the appendix C++ to WSDL Mapping.
 *                                If the data member is an array, then the
 *                                property is many-valued. � required (optional)
 *                                specifies whether a value must be set in the
 *                                component definition for this property.
 *                                Default is false � default (optional)
 *                                specifies a default value and is only needed
 *                                if required is false,
 */
public class Property {

	private String	name , type , propertyDefault;
	private boolean	required;

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public String getPropertyDefault() {
		return propertyDefault;
	}

	public void setPropertyDefault(String propertyDefault) {
		this.propertyDefault = propertyDefault;
	}

	public boolean isRequired() {
		return required;
	}

	public void setRequired(boolean required) {
		this.required = required;
	}

}
