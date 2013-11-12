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
package org.trentino.trengen.tools.generation;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javax.swing.plaf.ListUI;

import org.apache.log4j.xml.DOMConfigurator;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.scavalidation.ContributionTypeWrapper;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.tools.trengen.TrentinoTest;
import org.trentino.trengen.tools.trengen.utils.TryCompileUtil;

/**
 * @author z002ttbb
 */
public class TrengenCodeCompilationTestUtil extends TrentinoTest {

	static File	 systemTestDataDir;
	List<File>	 includeDirs;

	static
	{
		DOMConfigurator.configure(ConfigLoader.LOG_CONFIG_XML_DEBUG);

		String source = System.getProperty("trentino.system.test.data.dir");
		if(source == null)
		{
			throw new IllegalStateException("Directory for Trentino System Test data not specified or does not exists");
		}
		File f = new File(source);
		if(!f.exists() || !f.isDirectory())
		{
			throw new IllegalStateException("Directory for Trentino System Test data does not exists or is not a directory " + source);
		}
		systemTestDataDir = f;

	}

	File	     generationDirectory;
	final String	contributionName;
	final String	contributionPath;

	public TrengenCodeCompilationTestUtil (String contributionName, String contributionPath, List<String> tidlPaths, String genitfInclude)
	        throws TrengenException, Exception {
		this.contributionName = contributionName;
		this.contributionPath = contributionPath;
		generationDirectory = new File("./target", contributionName).getCanonicalFile();
		if(generationDirectory.exists())
		{
			File[] files = generationDirectory.listFiles();
			if(files != null)
			{
				for (File f : files)
				{
					f.delete();
				}
			}
			generationDirectory.delete();
		}

		generationDirectory.mkdir();
		if(tidlPaths != null)
		{

			for (String tidlPath : tidlPaths)
			{
				File tidl = new File(getFile(contributionPath), tidlPath);
				if(genitfInclude == null)
				{
					trengenGenerate("-gencppitf", tidl.getCanonicalPath(), "-outdir", generationDirectory.getCanonicalPath());
				}
				else
				{
					trengenGenerate("-gencppitf", tidl.getCanonicalPath(), "-outdir", generationDirectory.getCanonicalPath(), "-inc", genitfInclude);
				}
			}

		}
		getContributionType(contributionPath, generationDirectory);
		includeDirs = createIncludeDirs();
	}

	private List<File> createIncludeDirs() throws IOException {
		File inc = getFile(contributionPath);
		File rt = new File(systemTestDataDir, "../../../src").getCanonicalFile();
		File thirdParty = new File(systemTestDataDir, "../../../3rdparty/x86_windows/vc10").getCanonicalFile();
		List<File> includeDirs = new ArrayList<File>();
		includeDirs.add(inc);
		includeDirs.add(new File(inc, "services"));
		includeDirs.add(new File(thirdParty, "protobuf-2.4.1/include"));
		includeDirs.add(new File(thirdParty, "boost_1_47/include"));
		includeDirs.add(rt);
		includeDirs.add(new File(rt, "BindingCompactSoap").getCanonicalFile());
		includeDirs.add(new File(rt, "BindingSCAClient").getCanonicalFile());
		return includeDirs;
	}

	private static void trengenGenerate(String... args) {
		
		Trengen.main(args);
	}

	public static void getContributionType(String contributionPath, File outDir) throws Exception {

		File file = getFile(contributionPath);
		trengenGenerate("-cont", file.getCanonicalPath(), "-outdir", outDir.getCanonicalPath(),"-disable_exit","true");
		Throwable lastExThrowable = Trengen.getInstance().getLastException();
		org.junit.Assert.assertNull(lastExThrowable);
	}

	public static File getFile(String contributionPath) {
		File file = new File(systemTestDataDir, contributionPath);
		if(!file.exists())
		{
			throw new IllegalStateException("Directory for Trentino System Test data does not exists or is not a directory " + file);
		}
		return file;
	}

	/**
	 * @param files
	 */
	public boolean compile(File[] files, List<String> macros) {
		return TryCompileUtil.tryCompile2(files, includeDirs, generationDirectory, macros);
	}

}
