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

package org.trentino.trengen.tools.scavalidation.utils;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipException;
import java.util.zip.ZipFile;

import org.apache.log4j.Logger;

/**
 * This class provides an unzip utility. SCA requires that all runtimes MUST
 * support the ZIP packaging format for contributions [ASM12006].
 */
public class UnZipUtil {

	protected static final Logger	logger	= Logger.getLogger(UnZipUtil.class);
	public static final int	      BUFFER	= 2048;

	private UnZipUtil () {
	}

	/**
	 * Function taking a path to the zip and extracts it to a folder which has
	 * the same name with the zip file
	 */
	public static boolean extractFolder(String zipFile) {
		boolean ret = true;
		try
		{
			logger.info("Zip file name : " + zipFile);

			File file = new File(zipFile);

			ZipFile zip = new ZipFile(file);
			int dotZipSize = ".zip".length();
			String newPath = zipFile.substring(0, zipFile.length() - dotZipSize);

			new File(newPath).mkdir();
			Enumeration<?> zipFileEntries = zip.entries();

			// Process each entry
			while (zipFileEntries.hasMoreElements())
			{
				// grab a zip file entry
				ZipEntry entry = (ZipEntry) zipFileEntries.nextElement();
				String currentEntry = entry.getName();
				File destFile = new File(newPath, currentEntry);
				// destFile = new File(newPath, destFile.getName());
				File destinationParent = destFile.getParentFile();

				// create the parent directory structure if needed
				destinationParent.mkdirs();

				if(!entry.isDirectory())
				{
					BufferedInputStream is = new BufferedInputStream(zip.getInputStream(entry));
					int currentByte;
					// establish buffer for writing file
					byte[] data = new byte[BUFFER];

					// write the current file to disk
					FileOutputStream fos = new FileOutputStream(destFile);
					BufferedOutputStream dest = new BufferedOutputStream(fos, BUFFER);

					// read and write until last byte is encountered
					while ((currentByte = is.read(data, 0, BUFFER)) != -1)
					{
						dest.write(data, 0, currentByte);
					}
					dest.flush();
					dest.close();
					is.close();
				}

				if(currentEntry.endsWith(".zip"))
				{
					extractFolder(destFile.getAbsolutePath());
				}
			}

		} catch (ZipException e)
		{
			logger.error("An error occured while unzipping");
			ret = false;
		} catch (IOException e)
		{
			logger.error("Zip File could not be found");
			ret = false;
		}

		return ret;
	}

	/**
	 * USAGE: public static final void main(String[] args) throws ZipException,
	 * IOException { extractFolder("c://trentino_sample_project.zip"); }
	 */

}