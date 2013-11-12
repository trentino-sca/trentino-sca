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
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import javax.xml.XMLConstants;
import javax.xml.namespace.NamespaceContext;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathFactory;

import org.apache.log4j.Logger;
import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class NameSpaceResolver implements NamespaceContext {
	protected static final Logger	  logger	   = Logger.getLogger(ScaValidationManager.class);

	private static final String	      DEFAULT_NS	= "DEFAULT";
	private final Map<String, String>	prefix2Uri	= new HashMap<String, String>();
	private final Map<String, String>	uri2Prefix	= new HashMap<String, String>();

	public static int	              COMMENT_NODE	= 8;
	public static int	              ELEMENT_NODE	= 1;

	/**
	 * This constructor parses the document and stores all namespaces it can
	 * find. If toplevelOnly is true, only namespaces in the root are used.
	 * @param document
	 *            source document
	 * @param toplevelOnly
	 *            restriction of the search to enhance performance
	 */
	public NameSpaceResolver (Document document, boolean toplevelOnly) {
		NodeList nodeList = document.getChildNodes();
		Node node = null;
		for (int i = 0; i < nodeList.getLength(); i++)
		{
			node = nodeList.item(i);
			if(node.getNodeType() != ELEMENT_NODE)
			{
				continue;
			}
			else
			{
				break;
			}

		}
		if(node == null)
		{
			return;
		}

		examineNode(node, toplevelOnly);
		// System.out.println("The list of the cached namespaces:");
		// for (String key : prefix2Uri.keySet())
		// {
		// // System.out.println("prefix " + key + ": uri " +
		// prefix2Uri.get(key));
		// }
	}

	/**
	 * A single node is read, the namespace attributes are extracted and stored.
	 * @param node
	 *            to examine
	 * @param attributesOnly
	 *            , if true no recursion happens
	 */
	private void examineNode(Node node, boolean attributesOnly) {
		NamedNodeMap attributes = node.getAttributes();
		for (int i = 0; i < attributes.getLength(); i++)
		{
			Node attribute = attributes.item(i);
			storeAttribute((Attr) attribute);
		}

		if(!attributesOnly)
		{
			NodeList chields = node.getChildNodes();
			for (int i = 0; i < chields.getLength(); i++)
			{
				Node chield = chields.item(i);
				if(chield.getNodeType() == Node.ELEMENT_NODE)
				{
					examineNode(chield, false);
				}
			}
		}
	}

	/**
	 * This method looks at an attribute and stores it, if it is a namespace
	 * attribute.
	 * @param attribute
	 *            to examine
	 */
	private void storeAttribute(Attr attribute) {
		// examine the attributes in namespace xmlns
		// if((attribute.getNamespaceURI() != null) &&
		// attribute.getNamespaceURI().equals(XMLConstants.XMLNS_ATTRIBUTE_NS_URI))

		String name = attribute.getName();
		int xmlnsSize = "xmlns".length();
		if(name.startsWith("xmlns") && name.regionMatches(xmlnsSize, ":", 0, 1))
		{
			// Default namespace xmlns="uri goes here"
			// The defined prefixes are stored here
			String namespaceName = attribute.getName();
			putInCache(namespaceName.substring(xmlnsSize + 1), attribute.getNodeValue());
		}
		else if(name.equals("xmlns"))
		{
			putInCache(attribute.getName(), attribute.getNodeValue());
		}

	}

	private void putInCache(String prefix, String uri) {
		prefix2Uri.put(prefix, uri);
		uri2Prefix.put(uri, prefix);
	}

	/**
	 * This method is called by XPath. It returns the default namespace, if the
	 * prefix is null or "".
	 * @param prefix
	 *            to search for
	 * @return uri
	 */
	@Override
	public String getNamespaceURI(String prefix) {
		if((prefix == null) || prefix.equals(XMLConstants.DEFAULT_NS_PREFIX))
		{
			return prefix2Uri.get(DEFAULT_NS);
		}
		else
		{
			return prefix2Uri.get(prefix);
		}
	}

	/**
	 * This method is not needed in this context, but can be implemented in a
	 * similar way.
	 */
	@Override
	public String getPrefix(String namespaceURI) {
		return uri2Prefix.get(namespaceURI);
	}

	@Override
	public Iterator<?> getPrefixes(String namespaceURI) {
		// Not implemented
		return null;
	}

	/**
	 * @param compositeFile
	 */
	public static NamespaceContext GetNamespaces(File compositeFile) {
		// XsdValidator xsdValidator = new XsdValidator();
		// if(!xsdValidator.validateArtifact(compositeFile,
		// ArtifactTypeConstants.XSD_SCHEMA))
		// {
		// logger.error(ConformanceManagerConstants.CI_ASM12027_VIOLATED + " = "
		// + ConformanceManagerConstants.CI_CPP110003_VIOLATED);
		//
		// }

		try
		{
			// File file = new File("D:\\Atolye\\books.xml");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(compositeFile);
			doc.getDocumentElement().normalize();

			XPath xPath = XPathFactory.newInstance().newXPath();
			NameSpaceResolver nsResolver = new NameSpaceResolver(doc, true);
			xPath.setNamespaceContext(nsResolver);
			// String pre = //nsResolver.getPrefix("");
			// pre = nsResolver.getNamespaceURI("");

			// NameSpaceResolver namespaceResolver = new NameSpaceResolver(doc,
			// true);
			// namespaceResolver.

			return xPath.getNamespaceContext();

		} catch (Exception e)
		{
			logger.error("Error while reolving namespaces");
			return null;
		}

	}
}
