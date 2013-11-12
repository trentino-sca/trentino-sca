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
/*
 * refactored simultaneously.
 * Reviewed on 04.05.2012:
 * parameter of the getLogger() function is edited.
 * main() function is deleted; because unit tests are written.
 * throw exception is deleted; instead logger is used.
 * "BufferedReader in = new BufferedReader(new InputStreamReader(yc.getInputStream()));" is deleted; in never used!
 * "URI.create(fileUri)" is changed to "new URI(fileUri)"
 */

package org.trentino.trengen.tools.scavalidation.utils;

import java.io.File;
import java.net.InetSocketAddress;
import java.net.Proxy;
import java.net.SocketAddress;
import java.net.URI;
import java.net.URL;
import java.net.URLConnection;

import org.apache.log4j.Logger;
import org.trentino.trengen.tools.scavalidation.DirectoryScanner;
import org.trentino.trengen.tools.trengen.Trengen;

public class FileURIChecker {
	protected static final Logger	logger	= Logger.getLogger(FileURIChecker.class);
	private static Proxy	      proxy	   = null;

	private FileURIChecker () {
	}

	/**
	 * This function reads the proxy config from the trengen.config file and
	 * prepares the proxy member
	 */
	private static boolean PrepareProxy() {
		String proxyIp = Trengen.getProperties().getProperty("proxy.address.ip");
		String proxyHost = Trengen.getProperties().getProperty("proxy.address.host");
		int proxyPort = 0;
		if((proxyIp != null) || (proxyHost != null))
		{
			String proxyPortString = Trengen.getProperties().getProperty("proxy.port");

			try
			{
				proxyPort = Integer.parseInt(proxyPortString);
			} catch (NumberFormatException e)
			{
				logger.error("Proxy port given in the trengen.config is not a valid port.");
				return false;
			}
		}
		SocketAddress addr = null;

		if(proxyIp != null) // proxy ip exists, proxy ip has the highest
		                    // priority
		{
			addr = new InetSocketAddress(proxyIp, proxyPort);

			proxy = new Proxy(Proxy.Type.HTTP, addr);
		}
		else if(proxyHost != null) // proxy ip does not exist but proxy host
		                           // exist
		{
			addr = new InetSocketAddress(proxyHost, proxyPort);
			proxy = new Proxy(Proxy.Type.HTTP, addr);
		}
		else
		{
			proxy = Proxy.NO_PROXY;
		}
		return true;
	}

	/**
	 * This is the entry point for to check out the dereferancability of the
	 * file attribute of the property
	 */
	public static boolean isDereferancableURI(String fileUri) {
		if(fileUri == null)
		{
			logger.error("Given Uri is null");
			return false;
		}

		if(fileUri.startsWith("http") || fileUri.startsWith("https") || fileUri.startsWith("ftp"))
		{
			return checkForRemoteUri(fileUri);
		}
		else if(fileUri.charAt(1) == ':')// this is an absolute path
		{
			return checkForAbsoluteUri(fileUri);
		}
		else
		{
			return checkForRelativeUri(fileUri);
		}
	}

	/**
	 * This checks out the remote uris (starting with https, http, ftp...etc)
	 */
	private static boolean checkForRemoteUri(String fileUri) {
		if(!PrepareProxy())
		{
			return false;
		}

		try
		{
			URI uri = new URI(fileUri);
			// avoid null pointer exception
			if(uri.getHost() == null)
			{
				logger.error("no hostname");
				return false;
			}

			URL url = uri.toURL();

			URLConnection yc = url.openConnection(proxy);
			yc.connect();
		} catch (Throwable e)
		{
			logger.error("Wrong proxy setting or file URI is not derefererancable URI: " + fileUri);
			return false;
		}
		return true;

	}

	/**
	 * This checks out the uri relative to the contribution dir
	 */
	private static boolean checkForRelativeUri(String fileURI) {
		File fileFound = DirectoryScanner.searchArtifactFullPath(fileURI);
		if(fileFound == null)
		{
			logger.warn("Given file attribute for the property is not dereferancable.  " + fileURI);
			return false;
		}
		return true;
	}

	/**
	 * this function checks out the absolute uris
	 */
	private static boolean checkForAbsoluteUri(String fileURI) {
		File file = new File(fileURI);
		if(!file.exists())
		{
			logger.error("Given file attribute for the property is not dereferancable.  " + fileURI);
			return false;
		}
		return true;

	}
}
