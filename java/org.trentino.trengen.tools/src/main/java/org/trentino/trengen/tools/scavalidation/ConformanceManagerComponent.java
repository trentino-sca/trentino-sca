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
import java.util.HashSet;
import java.util.Set;

import org.apache.log4j.Logger;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.sca.model.CPPInterface;
import org.trentino.trengen.sca.model.ComponentService;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.ComponentTypeReference;

/**
 * The class for handling component-related Conformance items in the SCA and CPP
 * Spec
 */
public class ConformanceManagerComponent {

	protected static final Logger	logger	= Logger.getLogger(ConformanceManagerComponent.class);

	private ConformanceManagerComponent () {
	}

	/**
	 * [CPP20007]: The name attribute of a <function/> child element of a
	 * <interface.cpp/> MUST be unique amongst the <function/> elements of that
	 * <interface.cpp/>.
	 */
	public static boolean check_CI20007(ComponentType component) {
		int size = component.getServiceOrReferenceOrProperty().size();
		for (int index = 0; index < size; index++)
		{
			ArrayList<String> functionNames = new ArrayList<String>();
			if(component.getServiceOrReferenceOrProperty().get(index).getClass().equals(ComponentService.class))
			{
				ComponentService cs = (ComponentService) component.getServiceOrReferenceOrProperty().get(index);
				if(cs.getInterface() != null)
				{
					int interfaceSize = ((CPPInterface) cs.getInterface().getValue()).getFunction().size();
					for (int j = 0; j < interfaceSize; j++)
					{
						String functionName = ((CPPInterface) cs.getInterface().getValue()).getFunction().get(j).getName();
						for (int i = 0; i < functionNames.size(); i++)
						{
							if(functionName.equals(functionNames.get(i)))
							{
								logger.error(ConformanceManagerConstants.CI_CPP20007_VIOLATED);
								return false;
							}
						}
						functionNames.add(functionName);
					}
				}
			}
			else if(component.getServiceOrReferenceOrProperty().get(index).getClass().equals(ComponentTypeReference.class))
			{
				ComponentTypeReference cs = (ComponentTypeReference) component.getServiceOrReferenceOrProperty().get(index);
				if(cs.getInterface() != null)
				{
					int interfaceSize = ((CPPInterface) cs.getInterface().getValue()).getFunction().size();
					for (int j = 0; j < interfaceSize; j++)
					{
						String functionName = ((CPPInterface) cs.getInterface().getValue()).getFunction().get(j).getName();
						for (int i = 0; i < functionNames.size(); i++)
						{
							if(functionName.equals(functionNames.get(i)))
							{
								logger.error(ConformanceManagerConstants.CI_CPP20007_VIOLATED);
								return false;
							}
						}
						functionNames.add(functionName);
					}
				}
			}
		}
		return true;
	}

	/**
	 * [CPP20008]: The name attribute of a <callbackFunction/> child element of
	 * a <interface.cpp/> MUST be unique amongst the <callbackFunction/>
	 * elements of that <interface.cpp/>.
	 */
	public static boolean check_CI20008(ComponentType component) {
		for (Object obj : component.getServiceOrReferenceOrProperty())
		{
			doCheck_CI20008(obj);
		}

		return true;
	}

	private static void doCheck_CI20008(Object obj) {
	    Set<String> functionNames = new HashSet<String>();
	    if(obj instanceof ComponentService)
	    {
	    	ComponentService cs = (ComponentService) obj;
	    	if(cs.getInterface() == null)
	    	{
	    		return;
	    	}

	    	int interfaceSize = ((CPPInterface) cs.getInterface().getValue()).getCallbackFunction().size();
	    	for (int j = 0; j < interfaceSize; j++)
	    	{
	    		String functionName = ((CPPInterface) cs.getInterface().getValue()).getCallbackFunction().get(j).getName();
	    		if(functionNames.add(functionName))
	    		{
	    			throw new ValidationException(ConformanceManagerConstants.CI_CPP20008_VIOLATED + " Function name" + functionName);
	    		}
	    	}

	    }
	    else if(obj instanceof ComponentTypeReference)
	    {
	    	ComponentTypeReference cs = (ComponentTypeReference) obj;
	    	if(cs.getInterface() == null)
	    	{
	    		return;
	    	}

	    	int interfaceSize = ((CPPInterface) cs.getInterface().getValue()).getCallbackFunction().size();
	    	for (int j = 0; j < interfaceSize; j++)
	    	{
	    		String functionName = ((CPPInterface) cs.getInterface().getValue()).getCallbackFunction().get(j).getName();
	    		if(functionNames.add(functionName))
	    		{
	    			throw new ValidationException(ConformanceManagerConstants.CI_CPP20008_VIOLATED + " Function name" + functionName);
	    		}
	    	}
	    }
    }
}
