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
package org.trentino.trengen.tools.bindingframework;

import java.util.ServiceLoader;

import org.apache.log4j.Logger;
import org.trentino.trengen.TrengenException;

/**
 * @author Emeric Kwemou Manage all the bindings plugged in Trengen. A Binding
 *         must implement the BindingCodeGenerator Interface and the jar files
 *         implementing the binding must be available in the class path. The
 *         CodeGeneratorManager is based on the java Service Provider API
 */
public class BindingCodeGeneratorManager {

	protected static final Logger	 logger	= Logger.getLogger(BindingCodeGeneratorManager.class);
	private ClassLoader classLoader;
	private BindingCodeGeneratorData	data;

	/**
	 * @param data
	 */
	public BindingCodeGeneratorManager (BindingCodeGeneratorData data,	ClassLoader classLoader) {
		this.data = data;
		this.classLoader = classLoader;
	}

	/**
	 * Tell all the registered Binding plugins to generate their necessary code.
	 * @throws TrengenException
	 */
	public boolean generateBindingCode() throws TrengenException {
		ServiceLoader<BindingCodeGenerator> generators = ServiceLoader.load(BindingCodeGenerator.class, classLoader);
		for (BindingCodeGenerator generator : generators)
		{
			if(!generator.generate(data))
			{
				return false;
			}
		}
		return true;
	}

	public BindingCodeGeneratorData getData() {
		return data;
	}

	public void setData(BindingCodeGeneratorData data) {
		this.data = data;
	}
}
