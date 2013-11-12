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

/**
 * The class for handling contributionType-related Conformance items in the SCA
 * and CPP Spec
 */
public class ConformanceManagerContribution {

	protected static final Logger	logger	= Logger.getLogger(ConformanceManagerContribution.class);

	private ConformanceManagerContribution () {
	}

	/**
	 * [ASM60001]: A composite name attribute value MUST be unique within the
	 * namespace of the composite.
	 */
	public static boolean check_CI60001_forOneContribution(ContributionTypeWrapper contributionTypeWrapper) {
		boolean ret = true;

		int size = contributionTypeWrapper.getContributionType().getDeployable().size();
		ArrayList<String> compositeNames = new ArrayList<String>();

		for (int index = 0; index < size; index++)
		{
			String compositeName = contributionTypeWrapper.getContributionType().getDeployable().get(index).getComposite().getLocalPart();
			for (int i = 0; i < compositeNames.size(); i++)
			{
				if(compositeName.equals(compositeNames.get(i)))
				{
					ret = false;
				}
			}
			compositeNames.add(compositeName);
		}
		if(!ret)
		{
			logger.error(ConformanceManagerConstants.CI_ASM60001_VIOLATED);
		}

		return ret;
	}
}
