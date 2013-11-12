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

import java.util.ArrayList;
import java.util.List;

import javax.xml.bind.JAXBElement;

import org.trentino.trengen.sca.model.Binding;
import org.trentino.trengen.sca.model.Interface;
import org.trentino.trengen.sca.model.Reference;

public class CompositeReferenceWrapper {
	public CompositeReferenceWrapper (Reference compositeReference, CompositeWrapper composite) {
		this.compositeReference = compositeReference;
		this.composite = composite;
		if(composite == null || compositeReference == null)
		{
			throw new IllegalStateException("Inconsistent model. composite of composite reference not defined for composite reference wrapper");
		}
	}

	// the composite reference
	private Reference	                    compositeReference;
	private CompositeWrapper	            composite;
	// the component reference that is beeing propmoted
	private List<ComponentReferenceWrapper>	compoenentReferences	= new ArrayList<ComponentReferenceWrapper>();

	public Reference getCompositeReference() {
		return compositeReference;
	}

	public void setCompositeReference(Reference compositeReference) {
		this.compositeReference = compositeReference;
	}

	public List<ComponentReferenceWrapper> getComponentReferences() {
		return compoenentReferences;
	}

	public CompositeWrapper getComposite() {
		return composite;
	}

	public void setComposite(CompositeWrapper composite) {
		this.composite = composite;
	}

	/**
	 * @return
	 */
	public String getCompositeName() {
		return composite.getCompositeName();
	}

	/**
	 * @return
	 */
	public JAXBElement<? extends Interface> getInterface() {
		JAXBElement<? extends Interface> itfElem = compositeReference.getInterface();
		if(itfElem == null || itfElem.isNil())
		{
			// find the interface in the component reference
			if(getComponentReferences().size() == 0)
			{
				throw new IllegalStateException("Service reference should have at least on component reference it promotes");
			}
			ComponentReferenceWrapper cref = getComponentReferences().get(0);
			itfElem = cref.getInterface();

		}
		return itfElem;
	}

	/**
	 * @return
	 */
	public String getName() {
		return compositeReference.getName();
	}

	/**
	 * @return
	 */
	public List<JAXBElement<? extends Binding>> getBinding() {
		List<JAXBElement<? extends Binding>> res = compositeReference.getBinding();
		if(res.size() == 0)
		{
			// then get the binding from component being promoted. But this only
			// valid if only one component is beeing promoted
			if(compoenentReferences.size() != 1)
			{
				return res;
			}
			ComponentReferenceWrapper val = compoenentReferences.get(0);
			return val.getBinding();

		}
		return res;
	}

}