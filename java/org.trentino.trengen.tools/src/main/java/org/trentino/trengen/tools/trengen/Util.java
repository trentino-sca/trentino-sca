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
package org.trentino.trengen.tools.trengen;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;

/**
 * @author z002ttbb
 *
 */
public class Util {

	public static String getTidlFilePath(File tidlPropertiesFile, String pathToJavaFile) {
    	String pathToTidl = null;
    	// search the corresponding java file relative to the tidl file...
    	int index = 0;
    	String tidlFileAbsPath = tidlPropertiesFile.getAbsolutePath();
    	if(tidlFileAbsPath.contains("/"))
    	{
    		index = tidlFileAbsPath.lastIndexOf("/");
    		pathToTidl = tidlFileAbsPath.substring(0, index);
    	}
    	else if(tidlFileAbsPath.contains("\\"))
    	{
    		index = tidlFileAbsPath.lastIndexOf("\\");
    		pathToTidl = tidlFileAbsPath.substring(0, index + 1);
    	}
    
    	return pathToTidl;
    }

	public static String readTidlPropertiesFile(File tidlPropertiesFile) {
    	// System.out.println(tidlPropertiesFile);
    	String pathToJavaFile = null;
    
    	// read inside of the tidl file
    	try
    	{
    		FileInputStream fstream = new FileInputStream(tidlPropertiesFile);
    		DataInputStream in = new DataInputStream(fstream);
    		BufferedReader br = new BufferedReader(new InputStreamReader(in));
    		String strLine;
    		while ((strLine = br.readLine()) != null)
    		{
    			pathToJavaFile = strLine.replace("interface=./", "");
    			pathToJavaFile = pathToJavaFile.replace("interface=.\\", "");
    			pathToJavaFile = pathToJavaFile.trim();
    		}
    		in.close();
    	} catch (Exception e)
    	{
    		System.err.println("Error: " + e.getMessage());
    	}
    	return pathToJavaFile;
    }

	public static char toUpper(char x) {
    	char upper = x;
    
    	if((x >= 'a') && (x <= 'z'))
    	{
    		upper = (char) (x - Trengen.CAPITALIZE_NUMBER);
    	
    	}
    	return upper;
    }

	public static ClassLoader getPluginClassLoader(String pluginsDir) throws MalformedURLException {
			File dependencyDirectory = (pluginsDir!=null) ? new File(pluginsDir): new File("pluggins");
			if(!dependencyDirectory.exists()){
				return Thread.currentThread().getContextClassLoader();
			}
			File[] files = dependencyDirectory.listFiles();
			ArrayList<URL> urls = new ArrayList<URL>();
			for (File file: files) {
			    if (file.getName().endsWith(".jar") || file.isDirectory()) {
			    urls.add(file.toURI().toURL());
			    }
			}
			
		 URL[] urlArray = new URL[urls.size()];
		 int i=0;
		 for(URL url : urls){
			 urlArray[i++]=url;
		 }
         URLClassLoader classLoader = new URLClassLoader(urlArray, Thread.currentThread().getContextClassLoader());
         return classLoader;
	}

}
