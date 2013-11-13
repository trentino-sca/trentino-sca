package org.trentino.trengen.tools.generation.thrift;

import static org.trentino.trengen.tools.scavalidation.CommandLineOptions.opt;

import java.io.File;

import org.apache.commons.cli.OptionGroup;
import org.apache.commons.cli.Options;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.tools.scavalidation.CommandLineOptions;
import org.trentino.trengen.tools.trengen.TrengenCommand;

public class GenCompCommand implements TrengenCommand {

	@Override
	public boolean canExecute(CommandLineOptions options) {
		return options.hasOption("thrift_gen_comp");
	}

	@Override
	public boolean execute(CommandLineOptions options) throws Exception {
		ComponentGeneratorContext context = new ComponentGeneratorContext(options);
		String inputString = (String)options.getOption("input");
		File inputDir = new File(inputString);
		if(inputString == null){
			throw new ValidationException("input option is mandatory for command thrift_gen_comp");
		}
		String outDir = (String) options.getOption("outdir");

		if(outDir==null){
			outDir = inputDir.getAbsolutePath();
		}
		context.setOutputDir(new File(outDir));
		context.setInputDir(inputDir);
		context.setGenerateComposite(options.hasOption("gen_composite"));
		ComponentGenerator generator = new ComponentGenerator(context );
		return generator.generate();
	}

	@Override
	public void addOption(OptionGroup usage1,Options generalOptions) {
		usage1.addOption(opt(
				"thrift_gen_comp",
				false,
				"generate thrift component type files",
				"Command: For thrift services, generate the corresponding header file, component type file as well as skelleton implementation and a composite file."));

		generalOptions.addOption(opt(
				"input",
				true,
				"directory where generated component files will be stored",
				" If no output directory is specified, the input directory is also used as output directory."));
		
		generalOptions.addOption(opt(
				"gen_composite",
				true,
				"name of composite file",
				"generate a default composite file while generating thrift related component type files. Only used with thrift_gen_comp"));
		generalOptions.addOption(opt(
				"gen_composite_out_dir",
				true,
				"Directory",
				"directory where generated composite file will be stored, default value is the output directory. Only used with gen_composite"));
	}

}
