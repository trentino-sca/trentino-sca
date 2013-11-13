package org.trentino.trengen.tools.generation.thrift;

import java.io.File;

import org.trentino.trengen.cpp.model.ClassMethod;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.tools.generation.Context;
import org.trentino.trengen.tools.scavalidation.CommandLineOptions;

public class ComponentGeneratorContext extends Context {

	private File outputDir;
	private File inputDir;
	private boolean generateComposite;
	private CommandLineOptions options;
	public CommandLineOptions getOptions() {
		return options;
	}

	public ComponentGeneratorContext(CommandLineOptions options) {
		this.options = options;
	}

	public void setGenerateComposite(boolean generateComposite) {
		this.generateComposite = generateComposite;
	}

	public void setInputDir(File inputDir) {
		this.inputDir = inputDir;
	}

	@Override
	public File getOutputDir() {
		return outputDir;
	}

	@Override
	public void setOutputDir(File outputDir) {
		this.outputDir = outputDir;

	}

	
	public File getInputDir(){
		return inputDir;
	}
	
	public String getComponentHeaderFileName(ClassModel service) {
		String clazzName = service.getClassName();
		clazzName = clazzName.substring(0,clazzName.length()-2);
		clazzName+="Impl";
		return clazzName;
	}
	
	boolean isGenerateComposite() {
		return generateComposite;
	}
	
	public String getReturn(ClassMethod method){
		if("void".equals(method.getReturnType())){
			return "";
		}
		if("bool".equals(method.getReturnType())){
			return "return false;";
		}
		
		if("int32_t".equals(method.getReturnType())){
			return "return 1;";
		}
		if("int64_t".equals(method.getReturnType())){
			return "return 1;";
		}
		if("double".equals(method.getReturnType())){
			return "return 1;";
		}
		return "// return value goes here";
	}

}
