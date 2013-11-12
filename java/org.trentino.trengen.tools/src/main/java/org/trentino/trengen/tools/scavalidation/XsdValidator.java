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

import java.io.File;
import java.io.IOException;

import javax.xml.XMLConstants;
import javax.xml.transform.Source;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;

import org.apache.log4j.Logger;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.tools.xsdSchemas.XsdLoaderClass;
import org.xml.sax.SAXException;

/**
 * This file is used xsd validation of given files (of type .componentType,
 * .composite, sca-contribution.xml and sca-definitions.xml).
 */

public final class XsdValidator {

	protected static final Logger	logger	= Logger.getLogger(XsdValidator.class);

	private XsdValidator () {

	}

	/**
	 * A function taking 1 File and a String and returning a boolean. Used for
	 * xsd-validation of an xml-file. An xsd-file should also be given.
	 * Xsd-files can be seen in ArtifactTypeConstants.
	 */
	public static boolean validateArtifact(File xmlFile) {
		Source xmlfile = new StreamSource(xmlFile);
		SchemaFactory schemaFactory = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
		Schema schema = null;
		try
		{
			schema = schemaFactory.newSchema(XsdLoaderClass.ALL_XSD);
		} catch (SAXException e1)
		{
			logger.error("Schema could not be created");
		}
		Validator validator = schema.newValidator();
		try
		{
			validator.validate(xmlfile);
			logger.debug(xmlFile.getAbsoluteFile() + " is valid");
			return true;
		} catch (IOException e)
		{
			logger.error(xmlFile.getAbsolutePath() + " could not be found");
			return false;
		} catch (SAXException e)
		{
			String message = "XSD validation result: " + e.getLocalizedMessage() + " in file " + xmlFile.toString();
			throw new ValidationException(message);
		}
	}

	/**
	 * A function taking 2 strings and returning a boolean (overloaded version
	 * of the previous function). Used for xsd-validation of an xml-file. An
	 * xsd-file should also be given. Xsd-files can be seen in
	 * ArtifactTypeConstants.
	 */
	public static boolean validateArtifact(String xmlFile) {
		Source xmlfile = new StreamSource(xmlFile);
		SchemaFactory schemaFactory = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
		Schema schema = null;
		try
		{
			schema = schemaFactory.newSchema(XsdLoaderClass.ALL_XSD);
		} catch (SAXException e1)
		{
			logger.error("Schema could not be created");
		}
		Validator validator = schema.newValidator();
		try
		{
			validator.validate(xmlfile);
			logger.debug(xmlFile + " is valid");
			return true;
		} catch (IOException e)
		{
			logger.error(xmlFile + " could not be found");
			return false;
		} catch (SAXException e)
		{
			logger.error("XSD validation result: " + e.getLocalizedMessage());
			return false;
		}
	}

}
