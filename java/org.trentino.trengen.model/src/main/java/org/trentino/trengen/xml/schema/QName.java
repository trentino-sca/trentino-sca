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

package org.trentino.trengen.xml.schema;

/**
 * This is the class that is the projection of QName
 */
public class QName {
	private String	qNameValue	= null;

	public QName (String localPartGiven, String nameSpaceGiven, String prefixGiven) {
		qNameValue = localPartGiven + "#" + nameSpaceGiven + "#" + prefixGiven;
	}

	@Override
	public String toString() {
		return qNameValue;
	}

	public String	mNameGen	= "QNameTrentinoGivenName";

	public void setNameGen(String nameGenToSet) {
		mNameGen = nameGenToSet;
	}

	public String getNameGen() {
		return mNameGen;
	}
	
	public static QName fromQName(javax.xml.namespace.QName qName){
		QName res = new QName(qName.getLocalPart(), qName.getNamespaceURI(), qName.getPrefix());
		return res;
	}
}
