package org.trentino.trengen.tools.bindingsca;

import java.io.File;
import java.util.List;

import org.trentino.trengen.TrengenException;
import org.trentino.trengen.tools.generation.bindingsca.ContextCppInterface;
import org.trentino.trengen.tools.generation.bindingsca.ProtobufGenerator;
import org.trentino.trengen.tools.generation.proxieswrappers.ReferenceServiceInterface;

public class TIDL2Protobuf {

	private TIDL2CppInterfaceModel	tIDL2CppInterfaceModel	= new TIDL2CppInterfaceModel();

	public void generate(ContextCppInterface contextProtoBuf) {
		ProtobufGenerator gen = new ProtobufGenerator(contextProtoBuf);
		try
		{
			gen.generate();
		} catch (TrengenException e)
		{
			throw new IllegalStateException(e);
		}
	}

	public ContextCppInterface createContext(File javaFile, File tidl, File outputDir, List<String> beanUtilFileHeaderNames, ReferenceServiceInterface service)
	        throws TIDLParseException {
		List<TIDLInterfaceModel> models = tIDL2CppInterfaceModel.parse(javaFile);
		// now generate
		String javaFilePrefix = javaFile.getName();
		javaFilePrefix = javaFilePrefix.substring(0, javaFilePrefix.lastIndexOf("."));
		for (TIDLInterfaceModel model : models)
		{
			if(model.getName().equals(javaFilePrefix))
			{
				ContextCppInterface contextProtoBuf = new ContextCppInterface(model, tidl, javaFile);
				contextProtoBuf.setOutputDir(outputDir);
				contextProtoBuf.setTidlInterfaceModel(model);
				contextProtoBuf.setTidlPropertiesFile(tidl);
				contextProtoBuf.setReferenceServiceInterface(service);

				// Keep the list of generated bean header files to be able to use them
				// from the binding helpers
				// BUG 539: if there are not any declared types, do not create a
				// beanutils.cpp
				if(contextProtoBuf.hasBeanUtils())
				{
					String fileName = contextProtoBuf.getNameGeneratedFile()+ "BeanUtils.h";
					beanUtilFileHeaderNames.add(fileName);
				}
				return contextProtoBuf;
			}
		}

		return null;
	}


}
