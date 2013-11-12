package org.trentino.trengen.tools.bindingsca;

import java.io.File;
import java.util.List;

import org.apache.log4j.Logger;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.tools.generation.bindingsca.ContextCppInterface;
import org.trentino.trengen.tools.generation.bindingsca.CppInterfaceGenerator;

public class TIDL2CppInterface {
	protected static final Logger	logger	               = Logger.getLogger(TIDL2CppInterface.class);
	private String	               cppInterfaceFileName	   = null;

	private TIDL2CppInterfaceModel	tIDL2CppInterfaceModel	= new TIDL2CppInterfaceModel();

	public void createCppInterface(File javaFile, File tidl, File outputDir, List<String> includes) throws TIDLParseException {
		if(javaFile ==null){
			throw new IllegalArgumentException("CPP interface generator. A java file is required");
		}
		
		logger.info("Generating CPP interface for file: " + javaFile.getPath() + "...");
		List<TIDLInterfaceModel> models = null;
			models = tIDL2CppInterfaceModel.parse(javaFile);
		ContextCppInterface context =null;
		// now generate
		String javaFilePrefix = javaFile.getName();
		javaFilePrefix = javaFilePrefix.substring(0, javaFilePrefix.lastIndexOf("."));
		for (TIDLInterfaceModel model : models)
		{
			if(model.getName().equals(javaFilePrefix))
			{
				context = new ContextCppInterface(model, tidl, javaFile);
				if(outputDir != null)
				{
					context.setOutputDir(outputDir);
				}
				if(includes != null)
				{
					context.getIncludes().addAll(includes);
				}
				if(model != null)
				{
					context.setTidlInterfaceModel(model);
					context.setTidlPropertiesFile(tidl);
					context.setJavaFile(javaFile);
				}
			}
		}
        if(context ==null){
        	throw new ValidationException("could not create model for file: "+javaFile);
        }
        
		CppInterfaceGenerator gen = new CppInterfaceGenerator(context);
		cppInterfaceFileName = context.getFileName();
		try
		{
			gen.generate();
		} catch (TrengenException e)
		{
			throw new IllegalStateException(e);
		}
		logger.info("Generation of Cpp interface " + cppInterfaceFileName + ".h under " + context.getOutputDir().getAbsolutePath()
		        + " directory was successfull");
	}

	public String getFileName() {
		return cppInterfaceFileName;
	}

}
