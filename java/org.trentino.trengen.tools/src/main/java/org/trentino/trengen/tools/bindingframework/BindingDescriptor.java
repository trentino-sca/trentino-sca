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
package org.trentino.trengen.tools.bindingframework;

import java.util.List;

import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentTypeReference;
import org.trentino.trengen.tools.scavalidation.ComponentReferenceWrapper;

/**
 * @author z002ttbb
 */
public interface BindingDescriptor {

	/**
	 * the name used bythe default address property in the fake service
	 */
	String	TRENTINO_INTERNAL_ADRESS_PROPERTY_DO_NOT_USE_THIS_NAME	= "_Trentino_internal_adress_property_do_not_use_this_name_";

	/**
	 * @return the binding ID of this binding. e.g binding.sca for the default
	 *         binding
	 */
	String getBindingId();

	/**
	 * @param contract
	 * @return true if this binding considere this reference to refer to a
	 *         remote service. The binding introspect the reference and deduce
	 *         if it refers to a remote service. This method has to be
	 *         implemented by the default binding
	 */
	boolean isRemote(ComponentReferenceWrapper contract);

	/**
	 * @param contract
	 * @return
	 */
	boolean isRemote(ComponentTypeReference contract);

	/**
	 * @param ref
	 * @return
	 */
	List<Component> getComponentsByReference(ComponentReferenceWrapper ref);

}
