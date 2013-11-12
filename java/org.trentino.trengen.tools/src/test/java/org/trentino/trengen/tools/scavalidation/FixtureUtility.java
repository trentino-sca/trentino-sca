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

import static org.junit.Assert.assertNotNull;

import java.io.File;
import java.net.URL;

import javax.xml.namespace.NamespaceContext;

import org.trentino.trengen.cpp.model.HeaderFile;
import org.trentino.trengen.cpp.parser.eclipse.EclipseCPPParser;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentService;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.ComponentTypeReference;
import org.trentino.trengen.sca.model.Composite;
import org.trentino.trengen.sca.model.Reference;
import org.trentino.trengen.sca.model.Service;

public class FixtureUtility {

	public FixtureUtility () {

	}

	public final CompositeWrapper setFixtureUtility() {
		CompositeWrapper compositeWrapper = new CompositeWrapper();

		EclipseCPPParser parser = new EclipseCPPParser(null,null);

		String localCompositeString = ScaValidationLoaderClass.LOCAL_COMPOSITE.toString().replace("file:", "");
		Composite composite = (Composite) XmlParser.parseArtifact(ScaValidationLoaderClass.LOCAL_COMPOSITE);
		assertNotNull(composite);

		// namespace needs to be set to the compositeWrapper

		compositeWrapper.setNamespaceContext(getNameSpaceContextOfComposite(localCompositeString));

		compositeWrapper.setComposite(composite);

		int componentSize = 0;
		for (int i = 0; i < composite.getRequiresOrPolicySetAttachmentOrService().size(); i++)
		{
			if(composite.getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Component.class))
			{
				componentSize++;
				ComponentWrapper componentWrapper = new ComponentWrapper();
				componentWrapper.setScaModelComponent((Component) composite.getRequiresOrPolicySetAttachmentOrService().get(i));
				if(componentSize == 1)
				{
					ComponentType helloWorldComponentType = (ComponentType) XmlParser
					        .parseArtifact(ScaValidationLoaderClass.HELLOWORLD_COMPONENTTYPE);
					assertNotNull(helloWorldComponentType);
					componentWrapper.setScaModelComponentType(helloWorldComponentType);

					String helloWorldCppClassString = ScaValidationLoaderClass.HELLOWORLD_CPPHEADER.toString().replace("file:", "");
					HeaderFile headerFile = parser.parse(helloWorldCppClassString);
					componentWrapper.setComponentHeader(headerFile);
				}
				else if(componentSize == 2)
				{
					ComponentType clientComponentType = (ComponentType) XmlParser.parseArtifact(ScaValidationLoaderClass.CLIENT_COMPONENTTYPE);
					assertNotNull(clientComponentType);
					componentWrapper.setScaModelComponentType(clientComponentType);

					String clientCppClassString = ScaValidationLoaderClass.CLIENT_CPPHEADER.toString().replace("file:", "");
					HeaderFile headerFile = parser.parse(clientCppClassString);
					componentWrapper.setComponentHeader(headerFile);
				}

				componentWrapper.setParentCompositeWrapper(compositeWrapper);
				compositeWrapper.listComponentWrappers.add(componentWrapper);
			}
			else if(composite.getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Reference.class))
			{
				compositeWrapper.compositeReferences.add((Reference) composite.getRequiresOrPolicySetAttachmentOrService().get(i));
			}
			else if(composite.getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Service.class))
			{
				compositeWrapper.compositeServices.add((Service) composite.getRequiresOrPolicySetAttachmentOrService().get(i));
			}
		}

		return compositeWrapper;
	}

	private NamespaceContext getNameSpaceContextOfComposite(String localCompositeString) {

		String absolutePathForComposite = localCompositeString;
		if(absolutePathForComposite.startsWith("/") || absolutePathForComposite.startsWith("\\"))
		{
			absolutePathForComposite = absolutePathForComposite.substring(1);
		}
		absolutePathForComposite = absolutePathForComposite.replace('/', '\\');
		File compositeFile = new File(absolutePathForComposite);
		NamespaceContext namespaceContext = NameSpaceResolver.GetNamespaces(compositeFile);
		return namespaceContext;
	}

	public final CompositeWrapper setFixtureUtility(URL localCompositeString, URL helloWorldComponentString, URL clientComponentString) {
		CompositeWrapper compositeWrapper = new CompositeWrapper();

		EclipseCPPParser parser = new EclipseCPPParser(null,null);

		Composite composite = (Composite) XmlParser.parseArtifact(localCompositeString);
		assertNotNull(composite);

		compositeWrapper.setComposite(composite);

		int componentSize = 0;
		for (int i = 0; i < composite.getRequiresOrPolicySetAttachmentOrService().size(); i++)
		{
			if(composite.getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Component.class))
			{
				componentSize++;
				ComponentWrapper componentWrapper = new ComponentWrapper();
				Component component = (Component) composite.getRequiresOrPolicySetAttachmentOrService().get(i);
				componentWrapper.setScaModelComponent(component);

				for (int j = 0; j < component.getServiceOrReferenceOrProperty().size(); j++)
				{
					if(component.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentReference.class))
					{
						ComponentReference cr = (ComponentReference) component.getServiceOrReferenceOrProperty().get(j);
						compositeWrapper.componentReferences.put(component.getName() + "/" + cr.getName(), cr);
					}
					else if(component.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentService.class))
					{
						ComponentService cr = (ComponentService) component.getServiceOrReferenceOrProperty().get(j);
						compositeWrapper.putComponentService(component.getName() + "/" + cr.getName(), cr);
					}
				}

				if(componentSize == 1)
				{
					ComponentType helloWorldComponentType = (ComponentType) XmlParser.parseArtifact(helloWorldComponentString);
					assertNotNull(helloWorldComponentType);

					for (int j = 0; j < helloWorldComponentType.getServiceOrReferenceOrProperty().size(); j++)
					{
						if(helloWorldComponentType.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentTypeReference.class))
						{
							ComponentTypeReference cr = (ComponentTypeReference) helloWorldComponentType.getServiceOrReferenceOrProperty().get(j);
							compositeWrapper.componentTypeReferences.put(component.getName() + "/" + cr.getName(), cr);
						}
						else if(helloWorldComponentType.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentService.class))
						{
							ComponentService cr = (ComponentService) helloWorldComponentType.getServiceOrReferenceOrProperty().get(j);
							compositeWrapper.putComponentService(component.getName() + "/" + cr.getName(), cr);
						}
					}

					componentWrapper.setScaModelComponentType(helloWorldComponentType);

					String helloWorldCppClassString = ScaValidationLoaderClass.HELLOWORLD_CPPHEADER.toString().replace("file:", "");
					HeaderFile headerFile = parser.parse(helloWorldCppClassString);
					componentWrapper.setComponentHeader(headerFile);
				}
				else if(componentSize == 2)
				{
					ComponentType clientComponentType = (ComponentType) XmlParser.parseArtifact(clientComponentString);
					assertNotNull(clientComponentType);

					for (int j = 0; j < clientComponentType.getServiceOrReferenceOrProperty().size(); j++)
					{
						if(clientComponentType.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentTypeReference.class))
						{
							ComponentTypeReference cr = (ComponentTypeReference) clientComponentType.getServiceOrReferenceOrProperty().get(j);
							compositeWrapper.componentTypeReferences.put(component.getName() + "/" + cr.getName(), cr);
						}
						else if(clientComponentType.getServiceOrReferenceOrProperty().get(j).getClass().equals(ComponentService.class))
						{
							ComponentService cr = (ComponentService) clientComponentType.getServiceOrReferenceOrProperty().get(j);
							compositeWrapper.putComponentService(component.getName() + "/" + cr.getName(), cr);
						}
					}

					componentWrapper.setScaModelComponentType(clientComponentType);

					String clientCppClassString = ScaValidationLoaderClass.CLIENT_CPPHEADER.toString().replace("file:", "");
					HeaderFile headerFile = parser.parse(clientCppClassString);
					componentWrapper.setComponentHeader(headerFile);
				}

				componentWrapper.setParentCompositeWrapper(compositeWrapper);
				compositeWrapper.listComponentWrappers.add(componentWrapper);
			}
			else if(composite.getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Reference.class))
			{
				compositeWrapper.compositeReferences.add((Reference) composite.getRequiresOrPolicySetAttachmentOrService().get(i));
			}
			else if(composite.getRequiresOrPolicySetAttachmentOrService().get(i).getClass().equals(Service.class))
			{
				compositeWrapper.compositeServices.add((Service) composite.getRequiresOrPolicySetAttachmentOrService().get(i));
			}
		}

		return compositeWrapper;
	}

}
