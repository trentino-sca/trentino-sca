/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/* @version $Rev: 452643 $ $Date: 2006-10-03 22:54:11 +0100 (Tue, 03 Oct 2006) $ */

/*
 * Branched from the original class that was also contributed to the
 * org.apache.axis.tools.common package.
 */
package org.trentino.trengen.tools.scavalidation;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Map;
import java.util.Properties;
import java.util.Scanner;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.OptionBuilder;
import org.apache.commons.cli.OptionGroup;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;
import org.apache.commons.cli.PosixParser;
import org.trentino.trengen.ValidationException;

/**
 * Command line options passed to a tool's main program. All command line
 * options should begin with a dash "-". Some command line options take a value
 * which is the next parameter after the option. Others do not.
 */
public class CommandLineOptions {

	private CommandLine cmd;

	private Options options;

	/**
	 * @param args
	 * @throws ValidationException
	 */
	public CommandLineOptions(String... args) throws ValidationException {
		options = createOptions();
		set(args);
	}

	private void construct(String... args) throws ValidationException {
		CommandLineParser parser = new PosixParser();
		try {
			cmd = parser.parse(options, args);
		} catch (ParseException exp) {
			System.err.println(exp.getMessage());
			printUsage();
			throw new ValidationException();
		}
	}

	/**
	 * 
	 */
	private Options createOptions() {
		Options options = new Options();

		options.addOption(opt(
				"outdir",
				true,
				"output_directory",
				"If provided it specifies the output directory for the Trengen generated code. Default is <input_directory>Gen."));
		OptionGroup usage1 = new OptionGroup();

		usage1.addOption(opt(
				"cont",
				true,
				"contribution_directory>|<zip_file_of_contribution_directory_tree",
				"specifies the root directory of SCA contribution, can be a zip file or a path"));
		usage1.addOption(OptionBuilder.withArgName("file").hasArg(true)
				.withDescription("Read options from a configuration file")
				.withLongOpt("config_file").create("cf"));
		usage1.addOption(new Option("h", "help", false, "print this message"));
		usage1.addOption(opt(
				"gencppitf",
				true,
				"a directory, a path to .java or .tidl.properties file",
				"generate C++ interface from a given interface definition file.\n The java file based model or a tidl configuration file containing "
						+ "the path of the java based model. If the path is a directory, then all *.tidl.properties files in the given directory will be processed."));

		options.addOption(opt(
				"rootdir",
				true,
				"root directory",
				"alternative root directory used for searching header files and component types. Does not apply to composites."));
		options.addOption(opt(
				"lib",
				true,
				"library names",
				"Library names (not path) of the service/component implementations. Names are separated by ';' or ','. Default is the contribution name."));
		options.addOption(opt(
				"libdirs",
				true,
				"directory*",
				"comma or semicolon separated list of directories, where libraries containing the service/component implementations are located. Default is <contribution> and <contribution>/lib."));
		options.addOption(opt(
				"includedirs",
				true,
				"directory*",
				"comma or semicolon separated list of directories, service and component header files are located. Default are <root>, <root>/services"));
		options.addOption(opt("exclude", true, "directory pattern",
				"comma or semicolon separated list of directory to be excluded. e.g '*/boost/*"));
		options.addOption(opt("d", false, null, "Trengen runs in debug mode"));
		options.addOption(opt("v", false, null,
				"If provided, Trengen shows info logs."));
		options.addOption(opt(
				"rtdir",
				true,
				"<runtime_directory*>",
				"specifies the location of the Trentino Runtime. Optional since Trengen tries to resolve the runtime path automatically.\n"));
		options.addOption(opt(
				"install_dir",
				true,
				"contribution_installation_directory*",
				"Optional. Trengen generates a "
						+ "Cmake file for the generated code. It requires the location where binaries will be installed as result of a Cmake install. "
						+ "Default value is the 'META-INF' of the <contribution_directory>"));

		options.addOption(opt(
				"ec",
				true,
				"directory list",
				"Comma or semi colomn separated list of paths to contributions that are imported by this contribution. Use this when this contribution import another one using the <import.cpp> tag in sca-contribution.xml"));

		options.addOption(opt(
				"inc",
				true,
				"header file name",
				"name of an optional header file to be included in the generated c++ header file."));
		options.addOption(opt(
				"no_inline",
				true,
				"true|false",
				"default false: true if the generated code should not be inline. In that case a cpp file is generated (only) for complex types"));

		options.addOption(opt("disable_exit", false, null,
				"disable exiting when Trengen is finished. USED for Development purpose only"));
		options.addOption(opt("generateCMake", true, "true|false",
				"Generate CMake file, default to true"));

		Option property = OptionBuilder
				.withArgName("property=value")
				.hasArgs(2)
				.withValueSeparator()
				.withDescription(
						"use value for given property. Only used together with 'cf' option")
				.create("D");
		options.addOption(property);

		options.addOptionGroup(usage1);
		return options;
	}

	private static Option opt(String name, boolean hasArg, String argName,
			String desc) {
		if (argName != null) {
			return OptionBuilder.withArgName(argName).hasArg(hasArg)
					.withDescription(desc).create(name);
		}
		return new Option(name, desc);
	}

	public void reset() {
		cmd = null;
	}

	/**
	 * Initializes the options based on the args passed to main
	 * 
	 * @throws ValidationException
	 */
	public void set(String[] args) throws ValidationException {

		CommandLineParser parser = new PosixParser();
		CommandLine firstRunCmd = null;
		Options firstRunOptions = createOptions();
		try {
			firstRunCmd = parser.parse(firstRunOptions, args);
		} catch (ParseException e) {
			System.err.println(e.getMessage());
			printUsage();
			throw new ValidationException();
		}

		if (firstRunCmd.hasOption("cf")) {
			String fileName = firstRunCmd.getOptionValue("cf");
			Properties props = firstRunCmd.getOptionProperties("D");
			args = parseConfigFile(fileName, props);
		}

		construct(args);
	}

	/**
	 * @param fileName
	 * @param props2
	 * @return
	 */
	private String[] parseConfigFile(String fileName, Properties variables) {
		PropertiesEx props = new PropertiesEx();
		FileInputStream fis = null;
		try {
			fis= new FileInputStream(fileName);
			props.load(fis);
			ArrayList<String> options = new ArrayList<String>();
            detectVariablesAndReplaceWithEnvironmentVariables(props);
			replaceVariablesWithValues(props, variables);
			for (Map.Entry<Object, Object> kv : props.entrySet()) {
				options.add("-"+String.valueOf(kv.getKey()));
				Object value = kv.getValue();
				if (value != null && !"".equals(value)) {
					options.add(String.valueOf(value));
				}
			}
			String[] res = new String[options.size()];
			for (int i = 0; i < res.length; i++) {
				res[i] = options.get(i);
			}
			return res;
		} catch (FileNotFoundException e) {
			throw new ValidationException("Input file was not found: "
					+ e.getMessage());
		} catch (IOException e) {
			throw new ValidationException("Cannot read input file: "
					+ e.getMessage());
		}
	}

	/**
	 * @param props
	 */
	private void detectVariablesAndReplaceWithEnvironmentVariables(
			PropertiesEx props) {
//		for (Object var : props.values()) {
//			if(var==null ||"".equals(var)){
//				continue;
//			}
//			String str = (String) var;
//			String regex="${";
//		}
		
	}

	/**
	 * @param properties
	 * @param variables
	 */
	private void replaceVariablesWithValues(Properties properties,
			Properties variables) {
		for (Map.Entry<Object, Object> var : variables.entrySet()) {
			String strKey = "${" + var.getKey() + "}";
			String varValue = String.valueOf(var.getValue());
			for (Map.Entry<Object, Object> prop : properties.entrySet()) {
				Object value = prop.getValue();
				if (value == null) {
					continue;
				}
				String strValue = String.valueOf(value);
				strValue =strValue.replace(strKey, varValue);
				prop.setValue(strValue);
			}
		}

	}

	public Object getOption(String key) {
		if (key != null && key.startsWith("-")) {
			key = key.substring(1);
		}
		return cmd.getOptionValue(key);
		// return pairs.get(key);
	}

	public void printUsage() {
		HelpFormatter formatter = new HelpFormatter();
		formatter.printHelp("Trengen usage", options);
	}
	
	 static class PropertiesEx extends Properties {
	    public void load(FileInputStream fis) throws IOException {
	        Scanner in = new Scanner(fis);
	        ByteArrayOutputStream out = new ByteArrayOutputStream();

	        while(in.hasNext()) {
	            out.write(in.nextLine().replace("\\","\\\\").getBytes());
	            out.write("\n".getBytes());
	        }

	        InputStream is = new ByteArrayInputStream(out.toByteArray());
	        super.load(is);
	    }
	}
}