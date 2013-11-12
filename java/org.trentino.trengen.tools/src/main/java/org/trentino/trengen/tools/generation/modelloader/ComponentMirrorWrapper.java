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

import javax.xml.namespace.NamespaceContext;

import org.trentino.trengen.scamodelmirror.Component;
import org.trentino.trengen.scamodelmirror.ComponentType;

/*
 * This class is not actively used for now.
 * It was referred from the compositeMirrorWrapper (still in the code but commented out)
 * This was perceived to be required for component componentType association but intead
 * we have managed it by keeping the static variable names.
 */
public class ComponentMirrorWrapper {

	private Component	           scaModelComponent;
	private ComponentType	       scaModelComponentType;
	private CompositeMirrorWrapper	parentCompositeWrapper;
	private NamespaceContext	   namespaceContextComponentType;

	public Component getScaModelComponent() {
		return scaModelComponent;
	}

	public void setScaModelComponent(Component scaModelComponent) {
		this.scaModelComponent = scaModelComponent;
	}

	public ComponentType getScaModelComponentType() {
		return scaModelComponentType;
	}

	public void setScaModelComponentType(ComponentType scaModelComponentType) {
		this.scaModelComponentType = scaModelComponentType;
	}

	public void setParentCompositeWrapper(CompositeMirrorWrapper compositeWrapper) {
		parentCompositeWrapper = compositeWrapper;

	}

	public CompositeMirrorWrapper getParentCompositeWrapper() {
		return parentCompositeWrapper;

	}

	public NamespaceContext getNamespaceContextComponentType() {
		return namespaceContextComponentType;
	}

	public void setNamespaceContextComponentType(NamespaceContext namespaceContextComponentType) {
		this.namespaceContextComponentType = namespaceContextComponentType;
	}

}
