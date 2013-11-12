package org.trentino.trengen.tools.generation.modelloader;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.trentino.trengen.TrengenException;
import org.trentino.trengen.tools.generation.TrengenGenerator;
import org.trentino.trengen.tools.generation.proxieswrappers.ContextProxiesWrappers;

import freemarker.template.Configuration;
import freemarker.template.Template;

/**
 * ModelLoaderGenerator is used to generate the model loader c++ class according
 * to the arguments of the generate function.
 */
public class ModelLoaderGenerator extends TrengenGenerator {

	public ModelLoaderGenerator (ContextProxiesWrappers context) {
		super(context);
	}

	/**
	 * This fucntion passes the base doWrite function the template generating
	 * the model loader c++ calls( "ModelLoader_cpp.ftl") output stream to write
	 * the generated c++ code context and the root map hosting the arguments of
	 * 'generate' function to be used by the template.
	 * Template traces the compositeWrapper list and contribution Type and
	 * componentType list and component and componentType association list
	 * separately(see the template for details)
	 */
	@Override
	public boolean generate() throws TrengenException {
		Configuration config = configure();
		Template cppTp = null;

		try
		{
			cppTp = config.getTemplate("ModelLoader_cpp.ftl");
			// headerTp = config.getTemplate("ModelLoader_h.ftl");
		} catch (IOException e)
		{
			throw new IllegalStateException("cannot create template");
		}

		File outputDir = context.getOutputDir();
		if(!outputDir.exists())
		{
			outputDir.mkdirs();
		}
		String fileName = "TrentinoGenModelLoader";

		FileOutputStream fos;
		try
		{
			fos = new FileOutputStream(new File(outputDir, fileName + ".cpp"));
		} catch (FileNotFoundException e)
		{
			throw new TrengenException(e);
		}

		Map<String, java.lang.Object> root = new HashMap<String, java.lang.Object>();
		String contributionName = ((ContextProxiesWrappers) context).getContributionName();
		root.put("contributionName", contributionName);
		root.put("mirrorObjectList", ((ContextProxiesWrappers) context).getCompositeMirrorWrapperList());
		root.put("mirrorContribution", ((ContextProxiesWrappers) context).getContribution());
		root.put("mirrorComponentTypeList", ((ContextProxiesWrappers) context).getListComponentType());
		root.put("componentTypeComponentAssocList", ((ContextProxiesWrappers) context).getComponentcomponentTypeAssocList());
		root.put("applicationName", ((ContextProxiesWrappers) context).getApplicationName());

		doWrite(root, context, cppTp, fos);
		return true;
	}

}
