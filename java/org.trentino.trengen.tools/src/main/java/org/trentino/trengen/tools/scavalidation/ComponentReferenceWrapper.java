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

import java.util.List;

import javax.xml.bind.JAXBElement;

import org.trentino.trengen.sca.model.Binding;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentTypeReference;
import org.trentino.trengen.sca.model.Interface;

public class ComponentReferenceWrapper {
	public ComponentReferenceWrapper () {
    }

	// the compoenent reference
	private ComponentReference	componentReference;
	// the component type reference being configured
	ComponentTypeReference	   componentTypeReference;
	private ComponentWrapper	component;

	public ComponentReference getComponentReference() {
		return componentReference;
	}

	public void setComponentReference(ComponentReference componentReference) {
		this.componentReference = componentReference;
	}

	public ComponentTypeReference getComponentTypeReference() {
		return componentTypeReference;
	}

	public void setComponentTypeReference(ComponentTypeReference componentTypeReference) {
		this.componentTypeReference = componentTypeReference;
	}

	/**
	 * @param componentWrapper
	 */
	public void setComponent(ComponentWrapper componentWrapper) {
		this.component = componentWrapper;

	}

	public ComponentWrapper getComponent() {
		return component;
	}

	/**
	 * @return
	 */
	public String getName() {
		return componentReference.getName();
	}

	/**
	 * @return
	 */
	public JAXBElement<? extends Interface> getInterface() {
		JAXBElement<? extends Interface> itfElem = componentReference.getInterface();
		if(itfElem == null || itfElem.isNil())
		{
			// find the interface in the component type reference
			itfElem = componentTypeReference.getInterface();

		}
		return itfElem;
	}

	/**
	 * @return
	 */
	public List<JAXBElement<? extends Binding>> getBinding() {
		List<JAXBElement<? extends Binding>> res = componentReference.getBinding();
		if(componentTypeReference!=null && componentTypeReference.getBinding()!=null){
				res.addAll(componentTypeReference.getBinding());	
		}

		return res;
	}
}