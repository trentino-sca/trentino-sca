package org.trentino.trengen.tools.generation.thrift;

import java.io.File;
import java.io.FileFilter;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.log4j.Logger;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.cpp.model.HeaderFile;
import org.trentino.trengen.cpp.parser.eclipse.EclipseCPPParser;
import org.trentino.trengen.tools.generation.TrengenGenerator;
import org.trentino.trengen.tools.templates.ThriftTemplateLoaderClass;

import freemarker.template.Configuration;
import freemarker.template.DefaultObjectWrapper;
import freemarker.template.Template;

/**
 * Generate component Implementation and component type based on Service
 * interface
 * 
 * @author z002ttbb
 * 
 */
public class ComponentGenerator extends TrengenGenerator {
	protected static Logger log = Logger.getLogger(ComponentGenerator.class);
	private static EclipseCPPParser eclipseCPPParser = new EclipseCPPParser(
			null, null);

	public ComponentGenerator(ComponentGeneratorContext context) {
		super(context);
	}

	private List<ClassModel> services;

	public void init() throws TrengenException {
		List<HeaderFile> headers = getHeaderFiles();
		List<ClassModel> services = getServices(headers);
		this.services = services;
	}

	private List<ClassModel> getServices(List<HeaderFile> headers) {
		List<ClassModel> services = new ArrayList<ClassModel>();
		for (HeaderFile h : headers) {
			String serviceName = new File(h.getName()).getName();
			serviceName = serviceName.substring(0, serviceName.length() - 2)
					+ "If";
			boolean found = false;
			for (ClassModel c : h.getClasses()) {
				String clazzName = c.getClassName();
				if (clazzName.endsWith(serviceName)) {
					services.add(c);
					found = true;
					break;
				}
			}
			if (!found)
				throw new ValidationException(
						"Class not found in Service header file: "
								+ serviceName);
		}
		return services;
	}

	private List<HeaderFile> getHeaderFiles() {
		List<HeaderFile> result = new ArrayList<HeaderFile>();
		ComponentGeneratorContext context = (ComponentGeneratorContext) this.context;
		File inputDir = context.getInputDir();
		FileFilter filter = new FileFilter() {

			@Override
			public boolean accept(File file) {
				return file.getName().endsWith("Service.h");
			}
		};
		File[] serviceFiles = inputDir.listFiles(filter);

		for (File f : serviceFiles) {
			String absolutePath = f.getAbsolutePath();
			log.info("Parsing file: " + absolutePath);
			HeaderFile hf = eclipseCPPParser.parse(absolutePath);
			if (hf != null) {
				result.add(hf);
			}
		}
		return result;
	}

	@Override
	public boolean generate() throws TrengenException {
		init();
		ComponentGeneratorContext context = (ComponentGeneratorContext) this.context;
		Configuration config = configure();
		Template headerTp = null;
		Template cppTp = null;
		Template componentType = null;
		Template composite = null;
		try {
			cppTp = config.getTemplate("component_cpp_file.ftl");
			headerTp = config.getTemplate("component_header_file.ftl");
			componentType = config.getTemplate("component_type_file.ftl");
			composite = config.getTemplate("composite.ftl");
		} catch (IOException e) {
			throw new IllegalStateException("cannot create template");
		}

		File outputDir = context.getOutputDir();
		if (!outputDir.exists()) {
			outputDir.mkdirs();
		}

		for (ClassModel service : services) {
			String componentName = context.getComponentHeaderFileName(service);
			String headerFileName = componentName + ".h";
			String compTypeFile = componentName + ".componentType";
			String className = service.getClassName();
			String serviceHeaderFileName = className.substring(0,
					className.length() - 2);
			String serviceName = serviceHeaderFileName;
			FileOutputStream headerFos;
			FileOutputStream cppFos;
			FileOutputStream compTypeFos;
			boolean cppExists = false;
			boolean headerExists = false;
			boolean compTyteExists = false;
			try {
				File headerFile = new File(outputDir, headerFileName);
				headerExists = headerFile.exists();

				headerFos = new FileOutputStream(headerFile);
				File cppFile = new File(outputDir, componentName + ".cpp");
				cppExists = cppFile.exists();

				cppFos = new FileOutputStream(cppFile);

				File compTypeF = new File(outputDir, compTypeFile);
				compTyteExists = compTypeF.exists();
				compTypeFos = new FileOutputStream(compTypeF);

			} catch (FileNotFoundException e) {
				throw new TrengenException(e);
			}

			Map<String, java.lang.Object> root = new HashMap<String, java.lang.Object>();

			root.put("serviceHeaderFileName", serviceHeaderFileName + ".h");
			root.put("componentName", componentName);

			root.put("serviceName", serviceName);
			root.put("service", service);
			root.put("context", context);
			if(!compTyteExists){
			doWrite(root, context, componentType, compTypeFos);				
			}

			if (!headerExists) {
				doWrite(root, context, headerTp, headerFos);
			}
			if (!cppExists) {
				// Do not overwrite existing Cpp file
				doWrite(root, context, cppTp, cppFos);
			}

		}

		if (!context.getOptions().hasOption("gen_composite")) {
			return true;
		}

		String compositeFile = (String) context.getOptions().getOption(
				"gen_composite");
		FileOutputStream compositeFos;
		if (context.getOptions().hasOption("gen_composite_out_dir")) {
			outputDir = new File((String) context.getOptions().getOption(
					"gen_composite_out_dir"));
			if (!outputDir.exists()) {
				outputDir.mkdir();
			}
		}
		try {

			File compositeF = new File(outputDir, compositeFile + ".composite");
			if (compositeF.exists()) {
				// if composite file already exists, do not regenerate or modify
				// it
				return true;
			}
			compositeFos = new FileOutputStream(compositeF);

		} catch (FileNotFoundException e) {
			throw new TrengenException(e);
		}

		Map<String, java.lang.Object> root = new HashMap<String, java.lang.Object>();
		root.put("services", services);
		root.put("context", context);
		root.put("ApplicationName", compositeFile);
		doWrite(root, context, composite, compositeFos);
		return true;
	}

	protected static Configuration configure() {
		cfg = new Configuration();
		cfg.setClassForTemplateLoading(ThriftTemplateLoaderClass.class, "");
		cfg.setObjectWrapper(new DefaultObjectWrapper());
		return cfg;
	}
}
