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
package org.trentino.trengen.tools.generation;

import java.util.ArrayList;
import java.util.List;

import org.trentino.trengen.sca.model.CPPImplementation;
import org.trentino.trengen.sca.model.CPPImplementationFunction;
import org.trentino.trengen.sca.model.Implementation;

/**
 * @author z002ttbb Utility class to read datas from a Component type
 */
public class ImplementationUtils {

	private ImplementationUtils () {
	}

	/**
	 * return the list of all CPP implementation functions associated with a
	 * component type.
	 * @param impl
	 * @return
	 */
	public static List<CPPImplementationFunction> getListCPPImplementationFunction(Implementation impl) {
		if(impl != null && (impl instanceof CPPImplementation))
		{
			CPPImplementation cppImpl = (CPPImplementation) impl;
			return cppImpl.getFunction();
		}
		return new ArrayList<CPPImplementationFunction>();
	}

}
