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

package org.trentino.trengen.cpp.model;

/**
 * @author z002ttbb
 */
public class InterfaceHeaderClass extends ClassModel {

	private boolean	interfaceAnn	= false;

	public boolean isInterfaceAnn() {
		return interfaceAnn;
	}

	public void setInterfaceAnn(boolean interfaceAnn) {
		this.interfaceAnn = interfaceAnn;
	}

	private boolean	 remotable	 = false;
	private Callback	callback	= null;

	public boolean isRemotable() {
		return remotable;
	}

	public void setRemotable(boolean remotable) {
		this.remotable = remotable;
	}

	public Callback getCallback() {
		return callback;
	}

	public void setCallback(Callback callback) {
		this.callback = callback;
	}

}
