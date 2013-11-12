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

import org.apache.log4j.Logger;
import org.trentino.trengen.sca.model.CPPImplementation;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.Composite;

/**
 * The class for handling composite-related Conformance items in the SCA and CPP
 * Spec
 */
public class ConformanceManagerComposite {

	protected static final Logger	logger	= Logger.getLogger(ConformanceManagerComposite.class);

	private ConformanceManagerComposite () {
	}

	public static boolean check_CI50001_forOneComposite(Composite composite) {
		int size = composite.getRequiresOrPolicySetAttachmentOrService().size();
		ArrayList<String> componentNames = new ArrayList<String>();
		Component component = new Component();
		for (int index = 0; index < size; index++)
		{
			if(composite.getRequiresOrPolicySetAttachmentOrService().get(index).getClass().equals(Component.class))
			{
				component = ((Component) composite.getRequiresOrPolicySetAttachmentOrService().get(index));
				String componentName = component.getName();
				for (int i = 0; i < componentNames.size(); i++)
				{
					if(componentName.equals(componentNames.get(i)))
					{
						logger.error(ConformanceManagerConstants.CI_ASM50001_VIOLATED);
						return false;
					}
				}
				componentNames.add(componentName);
			}
		}
		return true;
	}

	/**
	 * [ASM50001]: The name attribute of a <component/> child element of a
	 * <composite/> MUST be unique amongst the component elements of that
	 * <composite/>.
	 */
	public static boolean check_CI50001_forOneContribution(ContributionTypeWrapper contribution) {
		int size = contribution.getListCompositeWrapper().size();
		for (int index = 0; index < size; index++)
		{
			CompositeWrapper composite = contribution.getListCompositeWrapper().get(index);
			if(!check_CI50001_forOneComposite(composite.getComposite()))
			{
				logger.error(ConformanceManagerConstants.CI_ASM50001_VIOLATED);
				return false;
			}
		}
		return true;
	}

	public static boolean check_CI20010_forOneComposite(Composite composite) {
		int size = composite.getRequiresOrPolicySetAttachmentOrService().size();
		Component component = new Component();
		for (int index = 0; index < size; index++)
		{
			ArrayList<String> functionNames = new ArrayList<String>();
			if(composite.getRequiresOrPolicySetAttachmentOrService().get(index).getClass().equals(Component.class))
			{
				component = ((Component) composite.getRequiresOrPolicySetAttachmentOrService().get(index));
				if(component.getImplementation().getValue() == null
				        || !component.getImplementation().getValue().getClass().equals(CPPImplementation.class))
				{
					return true;
				}
				int implementationSize = ((CPPImplementation) component.getImplementation().getValue()).getFunction().size();
				for (int j = 0; j < implementationSize; j++)
				{
					String functionName = ((CPPImplementation) component.getImplementation().getValue()).getFunction().get(j).getName();
					for (int i = 0; i < functionNames.size(); i++)
					{
						if(functionName.equals(functionNames.get(i)))
						{
							logger.error(ConformanceManagerConstants.CI_CPP20010_VIOLATED);
							return false;
						}
					}
					functionNames.add(functionName);
				}
			}
		}
		return true;
	}

	/**
	 * [CPP20010]:The name attribute of a <function/> child element of a
	 * <implementation.cpp/> MUST be unique amongst the <function/> elements of
	 * that <implementation.cpp/>.
	 */
	public static boolean check_CI20010_forOneContribution(ContributionTypeWrapper contribution) {
		int size = contribution.getListCompositeWrapper().size();
		for (int index = 0; index < size; index++)
		{
			CompositeWrapper composite = contribution.getListCompositeWrapper().get(index);
			if(!check_CI20010_forOneComposite(composite.getComposite()))
			{
				logger.error(ConformanceManagerConstants.CI_CPP20010_VIOLATED);
				return false;
			}
		}
		return true;
	}
}
