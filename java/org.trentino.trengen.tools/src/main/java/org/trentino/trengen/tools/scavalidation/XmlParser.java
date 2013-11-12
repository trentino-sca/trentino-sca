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

import java.io.IOException;
import java.net.URL;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBElement;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;

import org.apache.log4j.Logger;

/**
 * This class provides a function which unmarshalls an instance document into a
 * Java content tree and access data contained within it.
 */

public final class XmlParser {
	protected static final Logger	logger	= Logger.getLogger(XmlParser.class);

	private XmlParser () {

	}

	/**
	 * Function taking a String and returning an Object. This object can then be
	 * casted to Composite, ComponentType and ContributionType.
	 */
	public static Object parseArtifact(URL xmlFile) {
		try
		{

			JAXBContext jc = JAXBContext.newInstance("org.trentino.trengen.sca.model");

			Unmarshaller u = jc.createUnmarshaller();

			JAXBElement<?> poElement = (JAXBElement<?>) u.unmarshal(xmlFile.openStream());

			Object artifact = poElement.getValue();

			return artifact;
		} catch (JAXBException je)
		{
			logger.error("JAXBExpection occured in parsing " + xmlFile);
			return null;
		} catch (IOException ioe)
		{
			logger.error(xmlFile + " could not be found");
			return null;
		}
	}
}
