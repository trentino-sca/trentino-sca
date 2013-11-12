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

import org.trentino.trengen.sca.model.ContributionType;
import org.trentino.trengen.sca.model.Reference;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentService;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.Composite;
import org.trentino.trengen.sca.model.Implementation;
import org.trentino.trengen.sca.model.Property;
import org.trentino.trengen.sca.model.PropertyValue;
import org.trentino.trengen.sca.model.Service;
import org.trentino.trengen.sca.model.Wire;

public abstract class ContributionVisitor {
	
	public void visit(ContributionType contributionType) {
		
	}
	
	public void visit(CompositeWrapper element) {
	}

	public void visit(ComponentWrapper compWrapper) {
	}

	public void visit(Service contract) {
	}

	public void visit(Reference contract) {
	}

	public void visit(ComponentReference contract) {
	}

	public void visit(ComponentService contract) {
	}

	public void visit(Composite composite) {
	}

	public void visit(Component obj) {
	}

	public void visit(Property obj) {
	}

	public void visit(ComponentType scaModelComponentType) {
	}

	public void visit(Wire obj) {
	}

	public void visit(Implementation value) {
	}

	public void visit(PropertyValue obj) {
	}

	public void visit(ComponentReferenceWrapper contract) {
	}
}