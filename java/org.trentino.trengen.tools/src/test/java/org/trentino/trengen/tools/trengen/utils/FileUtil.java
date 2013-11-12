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
package org.trentino.trengen.tools.trengen.utils;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

public final class FileUtil {
	private FileUtil () {
	}

	public static boolean areFilesSame(final File file1, final File file2) throws java.io.IOException {
		String s1 = "";
		String s3 = "";
		String y = "";
		String z = "";
		BufferedReader bfr = new BufferedReader(new FileReader(file1));
		BufferedReader bfr1 = new BufferedReader(new FileReader(file2));
		while ((z = bfr1.readLine()) != null)
		{
			s3 += z;
		}
		while ((y = bfr.readLine()) != null)
		{
			s1 += y;
		}
		System.out.println();
		System.out.println(s3);
		System.out.println();
		System.out.println(s1);
		if(s3.equals(s1))
		{
			System.out.println("Content of generated and reference files are same");
			return true;
		}
		else
		{
			System.out.println("Content of generated and reference files are not same");
			return false;
		}
	}
}
