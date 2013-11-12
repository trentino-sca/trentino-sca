// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************
package org.trentino.trengen.tools.bindingsca;

import java.util.Set;
import java.util.TreeSet;

/**
 * @author z002ttbb
 *
 */
public class TIDLTypeContainerSupport implements TIDLTypeContainer {

	private Set<TIDLType> enclosedClasses = new TreeSet<TIDLType>();
	/* (non-Javadoc)
	 * @see org.trentino.trengen.tools.bindingsca.TIDLTypeContainer#getEnclosedClasses()
	 */
	@Override
	public Set<TIDLType> getEnclosedClasses() {
		return enclosedClasses;
	}

}
