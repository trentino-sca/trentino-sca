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

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import javax.xml.namespace.NamespaceContext;

// import org.trentino.trengen.cpp.model.HeaderFile;
import org.trentino.trengen.cpp.model.HeaderFile;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentService;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.ComponentTypeReference;

public class ComponentWrapper {
	public ComponentWrapper () {
	    super();
    }

	private Component	                    scaModelComponent;
	private ComponentType	                scaModelComponentType;
	private HeaderFile	                    componentHeader;
	private CompositeWrapper	            parentCompositeWrapper;
	private NamespaceContext	            namespaceContextComponentType;
	private boolean	                        isCompositeByImpl	       = false;
	private CompositeWrapper	            correspondingCompositeImpl	= null;
	private List<ComponentReferenceWrapper>	componentReferenceWrapper;
	private File scaModelComponentTypeFile;

	public CompositeWrapper getCorrespondingCompositeImpl() {
		return correspondingCompositeImpl;
	}

	public void setCorrespondingCompositeImpl(CompositeWrapper correspondingCompositeImpl) {
		this.correspondingCompositeImpl = correspondingCompositeImpl;
	}

	public boolean isCompositeByImpl() {
		return isCompositeByImpl;
	}

	public void setCompositeByImpl(boolean isCompositeByImpl) {
		this.isCompositeByImpl = isCompositeByImpl;
	}

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

	public HeaderFile getComponentHeader() {
		return componentHeader;
	}

	public void setComponentHeader(HeaderFile componentHeader) {
		this.componentHeader = componentHeader;
	}

	public void setParentCompositeWrapper(CompositeWrapper compositeWrapper) {
		parentCompositeWrapper = compositeWrapper;

	}

	public CompositeWrapper getParentCompositeWrapper() {
		return parentCompositeWrapper;

	}

	public NamespaceContext getNamespaceContextComponentType() {
		return namespaceContextComponentType;
	}

	public void setNamespaceContextComponentType(NamespaceContext namespaceContextComponentType) {
		this.namespaceContextComponentType = namespaceContextComponentType;
	}

	public List<ComponentReferenceWrapper> getComponentReferences() {
		if(componentReferenceWrapper == null)
		{
			componentReferenceWrapper = new ArrayList<ComponentReferenceWrapper>();
			for (Object ref : scaModelComponent.getServiceOrReferenceOrProperty())
			{
				if(ref instanceof ComponentReference)
				{
					ComponentReferenceWrapper wrapper = new ComponentReferenceWrapper();
					ComponentReference refCasted = (ComponentReference) ref;
					wrapper.setComponentReference(refCasted);
					componentReferenceWrapper.add(wrapper);
					// set the component type reference if existing
					if(scaModelComponentType ==null){
						continue;
					}
					for (Object ref2 : scaModelComponentType.getServiceOrReferenceOrProperty())
					{
						if(ref2 instanceof ComponentTypeReference)
						{
							ComponentTypeReference ref2Casted = (ComponentTypeReference) ref2;
							if(ref2Casted.getName().equals(refCasted.getName()))
							{
								wrapper.setComponentTypeReference(ref2Casted);
								wrapper.setComponent(this);
							}
						}
					}
				}
			}
		}
		return componentReferenceWrapper;
	}

	/**
	 * @return
	 */
	public ComponentService getComponentTypeService() {
		for (Object ref : scaModelComponentType.getServiceOrReferenceOrProperty())
		{
			if(ref instanceof ComponentService)
			{
				return (ComponentService) ref;
			}
		}
		return null;
	}

	/**
     * @param componentFile
     */
    public void setScaModelComponentTypeFile(File scaModelComponentTypeFile) {
    	this.scaModelComponentTypeFile = scaModelComponentTypeFile;    
    }

	public File getScaModelComponentTypeFile() {
    	return scaModelComponentTypeFile;
    }

}
