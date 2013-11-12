// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************
package org.trentino.trengen.tools.trengen.utils;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.URL;
import java.util.List;

import org.apache.log4j.Logger;
import org.trentino.trengen.tools.samples.SamplesClassLoader;

/**
 * @author z002ttbb
 *         Utility class used to try compile a given source file witout linking
 *         This is usefull to make sure that generated code can compile,
 *         and that all header files are resolved in generated code
 */
public class TryCompileUtil {

	protected static Logger	logger	= Logger.getLogger(TryCompileUtil.class);
	static File	            cmakeFile;
	static
	{
		URL resource = SamplesClassLoader.class.getResource("CMakeLists.txt");
		String cmake = resource.getFile();
		cmakeFile = new File(cmake);
	}

	public static boolean tryCompile(File srcFile, List<File> includeDirs, File outputDir) {
		ProcessBuilder pb = null;
		try
		{

			String src = "-DSRC=" + srcFile.getAbsolutePath();
			String incl = "-DINCL=";
			for (File inclF : includeDirs)
			{
				incl += inclF.getAbsolutePath() + ";";
			}
			pb = new ProcessBuilder("cmake", "-DFB=1", src, incl, cmakeFile.getParentFile().getAbsolutePath());
			pb.redirectErrorStream(true);
			pb.directory(outputDir);
			Process p = pb.start();
			OutputStream stdin = null;
			InputStream stdout = null;
			InputStream stderr = null;
			try
			{
				stdin = p.getOutputStream();
				stdout = p.getInputStream();
				stderr = p.getErrorStream();
				String line;
				StringBuffer buffer = new StringBuffer();
				BufferedReader bufferedStderr = new BufferedReader(new InputStreamReader(stderr));
				while ((line = bufferedStderr.readLine()) != null)
				{
					buffer.append(line).append("\n");
				}
				bufferedStderr.close();

				BufferedReader bufferedStdout = new BufferedReader(new InputStreamReader(stdout));
			
				while ((line = bufferedStdout.readLine()) != null)
				{
					buffer.append(line).append("\n");
				}
                
				logger.info(buffer.toString());
				p.waitFor();

				int val = p.exitValue();
				if(val != 0)
				{
					return false;
				}
			} catch (InterruptedException e)
			{
				logger.error("Trengen could not run the protoc compiler!...");
				return false;
			} finally
			{
				if(stdin != null)
					stdin.close();
				if(stderr != null)
					stderr.close();
				if(stdout != null)
					stdout.close();
			}
		} catch (IOException e)
		{
			logger.error("Trengen could not run the protoc compiler!...");
			return false;
		}
		return true;
	}
	
	public static boolean tryCompile2(File[] srcFiles, List<File> includeDirs, File outputDir,List<String> macros) {
		if(!isWindows()){
			//Only used in windows environment
			return true;
		}
		ProcessBuilder pb = null;
		try
		{

            if(isWindows()){
            	pb = getWindowsPB(srcFiles, outputDir.getCanonicalFile(), includeDirs, macros);
            }
            else {
            	throw new IllegalStateException("Not implemented for linux");
            }
			
			Process p = pb.start();
			OutputStream stdin = null;
			InputStream stdout = null;
			InputStream stderr = null;
			try
			{
				stdin = p.getOutputStream();
				stdout = p.getInputStream();
				stderr = p.getErrorStream();
				String line;
				StringBuffer buffer = new StringBuffer();
				BufferedReader bufferedStderr = new BufferedReader(new InputStreamReader(stderr));
				while ((line = bufferedStderr.readLine()) != null)
				{
					buffer.append(line).append("\n");
				}
				bufferedStderr.close();

				BufferedReader bufferedStdout = new BufferedReader(new InputStreamReader(stdout));
			
				while ((line = bufferedStdout.readLine()) != null)
				{
					buffer.append(line).append("\n");
				}
                
				logger.info(buffer.toString());
				p.waitFor();

				int val = p.exitValue();
				if(val != 0)
				{
					logger.error(buffer.toString());
					return false;
				}
			} catch (InterruptedException e)
			{
				logger.error("Trengen could not run the protoc compiler!...");
				return false;
			} finally
			{
				if(stdin != null)
					stdin.close();
				if(stderr != null)
					stderr.close();
				if(stdout != null)
					stdout.close();
			}
		} catch (IOException e)
		{
			return false;
		}
		return true;
	}

	private static ProcessBuilder getWindowsPB(File[] srcFiles, File outputDir,List<File> includeDirs,List<String> macros) {
		String incl = "";
		for (File inclF : includeDirs)
		{
			incl += "/I"+inclF.getAbsolutePath() + " ";
		}
		String programFiles = System.getenv("VCINSTALLDIR");
		if(programFiles==null){
			programFiles ="C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC";

		}
		if(!new File(programFiles).exists()){
			throw new IllegalStateException("Visual studio directory not found. Please make sure that environment variable VCINSTALLDIR is set." +
					"\ne.g: VCINSTALLDIR=C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC");
		}
		String vcvarall = new File(programFiles,"vcvarsall.bat").getAbsolutePath();
		StringBuffer cmd = new StringBuffer();
		cmd.append("call ").append("\"").append(vcvarall).append("\"").append("\n");
		cmd.append("cl /c /w /EHsc /D WIN32 ");
		if(macros!=null){
			for(String m: macros){
				cmd.append(m).append(" ");
			}
		}
		cmd.append(" ").append(incl).append(" ");
		for(File f : srcFiles){
			cmd.append(f.getAbsolutePath()).append(" ");
		}
		cmd.append("\n");
		File batFile = new File(outputDir,"compile.bat");
		if(batFile.exists()){
			batFile.delete();
		}
		batFile.deleteOnExit();
		FileOutputStream fos = null;
		try
        {
			fos = new FileOutputStream(batFile);
	        fos.write(cmd.toString().getBytes());
        } catch (IOException e)
        {
	        // TODO Auto-generated catch block
	        e.printStackTrace();
        }finally{
        	if(fos!=null){
        		try
                {
	                fos.close();
                } catch (IOException e)
                {
	                e.printStackTrace();
                }
        	}
        	
        }
		
		
	    ProcessBuilder pb;
	    pb = new ProcessBuilder("cmd","/c",batFile.getAbsolutePath());
	    pb.redirectErrorStream(true);
	    pb.directory(outputDir);
	    return pb;
    }
	
	private static String OS = null;
	   public static String getOsName()
	   {
	      if(OS == null) { OS = System.getProperty("os.name"); }
	      return OS;
	   }
	   public static boolean isWindows()
	   {
	      return getOsName().startsWith("Windows");
	   }

}
