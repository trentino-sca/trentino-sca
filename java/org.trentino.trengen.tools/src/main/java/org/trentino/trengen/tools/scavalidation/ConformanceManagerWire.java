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

import org.trentino.trengen.TIterable;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.Composite;

public class ConformanceManagerWire {
	/**
	 * [ASM50043] The default value of the @autowire attribute MUST be the value
	 * of the @autowire attribute on the component containing the reference, if
	 * present, or else the value of the @autowire attribute of the composite
	 * containing the component, if present, and if neither is present, then it
	 * is "false
	 */
	public boolean checkConformanceItems(CompositeWrapper compWrapper) {
		Composite composite = compWrapper.getComposite();
		TIterable<Component> components = TIterable.iterable(composite.getRequiresOrPolicySetAttachmentOrService(), Component.class);
		for (Component component : components)
		{
			TIterable<ComponentReference> compRefs = TIterable.iterable(component.getServiceOrReferenceOrProperty(), ComponentReference.class);
			for (ComponentReference compRef : compRefs)
			{

				if(compRef.isAutowire() == null)
				{
					if((component.isAutowire() != null) && component.isAutowire())
					{
						compRef.setAutowire(true);
					}
					else if(composite.isAutowire())
					{
						compRef.setAutowire(true);
					}
					else
					{
						compRef.setAutowire(false);
					}
				}
			}
		}
		return true;
	}
}
