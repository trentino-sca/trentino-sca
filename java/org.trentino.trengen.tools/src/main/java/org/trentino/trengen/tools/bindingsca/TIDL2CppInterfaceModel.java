package org.trentino.trengen.tools.bindingsca;

import java.io.File;
import java.io.FileFilter;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import javax.annotation.processing.AbstractProcessor;
import javax.tools.Diagnostic;
import javax.tools.DiagnosticCollector;
import javax.tools.JavaCompiler;
import javax.tools.JavaCompiler.CompilationTask;
import javax.tools.JavaFileObject;
import javax.tools.StandardJavaFileManager;
import javax.tools.ToolProvider;

import org.apache.log4j.Logger;

public class TIDL2CppInterfaceModel {
	protected static final Logger	logger	= Logger.getLogger(TIDL2CppInterfaceModel.class);

	public List<TIDLInterfaceModel> parse(File javaFile) throws TIDLParseException {
		File parent = javaFile.isDirectory() ?javaFile : javaFile.getParentFile();
		// get all java files in parent folder
		FileFilter filter = new FileFilter() {

			@Override
			public boolean accept(File pathname) {
				if(pathname.isFile() && pathname.getName().toLowerCase().endsWith(".java"))
				{
					return true;
				}
				return false;
			}
		};
		File[] files = parent.listFiles(filter);
		List<TIDLInterfaceModel> result = parse(files);

		// if only a file was give as argument, then only return one element
		if(javaFile.isDirectory())
		{
			return result;
		}
		String fileName = javaFile.getName();
		String itfName = fileName.substring(0, fileName.lastIndexOf("."));
		for (TIDLInterfaceModel model : result)
		{
			if(model.getName().endsWith(itfName))
			{
				ArrayList<TIDLInterfaceModel> endResult = new ArrayList<TIDLInterfaceModel>();
				endResult.add(model);
				return endResult;
			}
		}
		throw new TIDLParseException("Cannot find required interface in parsed model.");
	}

	private List<TIDLInterfaceModel> parse(File[] files) throws TIDLParseException {
		JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
		if(compiler == null)
		{
			compiler = getSystemJavaCompiler();
		}
		if(compiler == null)
		{

			throw new IllegalStateException(
			        "No java compiler found on your system. Please make sure that JDK 6 or higher is installed.\njava.home was: "
			                + System.getProperty("java.home") + "\nclass path: " + System.getProperty("java.class.path"));
		}
		// Get a new instance of the standard file manager implementation
		DiagnosticCollector<JavaFileObject> diagnostics = new DiagnosticCollector<JavaFileObject>();
		StandardJavaFileManager fileManager = compiler.getStandardFileManager(diagnostics, null, null);

		// Get the list of java file objects,
		Iterable<? extends JavaFileObject> compilationUnits1 = fileManager.getJavaFileObjects(files);
		List<String> optionList = new ArrayList<String>();
		// set compiler's classpath to be same as the runtime's
		File temp = new File(System.getProperty("user.dir"), "TEMP_TRENGEN" + System.nanoTime());
		while(temp.exists()){
			temp = new File(temp.getParentFile(),temp.getName()+"1");
		}
		if(!temp.exists())
		{
			temp.mkdirs();
		}
		temp.deleteOnExit();
		optionList.addAll(Arrays.asList("-classpath", System.getProperty("java.class.path"), "-d", temp.getAbsolutePath()));

		CompilationTask task = compiler.getTask(null, fileManager, diagnostics, optionList, null, compilationUnits1);

		// Create a list to hold annotation processors
		LinkedList<AbstractProcessor> processors = new LinkedList<AbstractProcessor>();
		// Add an annotation processor to the list
		TIDLModelBuilder modelbuilder = new TIDLModelBuilder();
		processors.add(modelbuilder);

		// Set the annotation processor to the compiler task
		task.setProcessors(processors);

		// Perform the compilation task.
		boolean result = task.call();
		List<Diagnostic<? extends JavaFileObject>> diagnosticObjs = diagnostics.getDiagnostics();
		for (Diagnostic<? extends JavaFileObject> d : diagnosticObjs)
		{
			if(d.getKind() == Diagnostic.Kind.ERROR)
			{
				logger.error(d);
			}
		}

		if(result == true)
		{
			logger.info("Model generation succeeded");
		}
		else
		{
			throw new TIDLParseException(
			        "Error occured while parsing input files.\nFor unresolved symbols errors, make sure that you included 'import org.trentino.tidl.*;' in each idl file");
		}
		deleteDir(temp);
		return modelbuilder.getTIDLInterfaceModel();
	}

	/**
	 * @param temp
	 */
	private void deleteDir(File temp) {
		if(temp.isDirectory())
		{
			File[] files = temp.listFiles();
			for (File file : files)
			{
				deleteDir(file);
			}
			temp.delete();
		}
		else
		{
			temp.delete();
		}
	}

	/**
	 * Gets the Java&trade; programming language compiler provided with this
	 * platform.
	 * @return the compiler provided with this platform or {@code null} if no
	 *         compiler is provided
	 */
	private static JavaCompiler getSystemJavaCompiler() {
		if(Lazy.compilerClass == null)
		{
			return null;
		}
		try
		{
			return Lazy.compilerClass.newInstance();
		} catch (Throwable e)
		{
			return null;
		}
	}

	/**
	 * This class will not be initialized until one of the above methods are
	 * called. This ensures that searching for the compiler does not affect
	 * platform start up.
	 */
	static class Lazy {
		private static final String		           defaultJavaCompilerName	= "com.sun.tools.javac.api.JavacTool";
		private static final String[]		       defaultToolsLocation		=
		                                                                   { "lib", "tools.jar" };
		static final Class<? extends JavaCompiler>	compilerClass;
		static
		{
			Class<? extends JavaCompiler> c = null;
			try
			{
				c = findClass().asSubclass(JavaCompiler.class);
			} catch (Throwable t)
			{
				// ignored
				logger.info("could not find java compiler");
			}
			compilerClass = c;
		}

		private static Class<?> findClass() throws MalformedURLException, ClassNotFoundException {
			try
			{
				return enableAsserts(Class.forName(defaultJavaCompilerName, false, null));
			} catch (ClassNotFoundException e)
			{
				// ignored, try looking else where
				logger.info("Default java compiler could not be found. Trengen will try to look somewhere else.");
			}

			Map<String, String> env = System.getenv();
			String javahomeDir = env.get("JAVA_HOME");
			File file = new File(javahomeDir);
			if(file.getName().equalsIgnoreCase("jre"))
			{
				file = file.getParentFile();
			}
			for (String name : defaultToolsLocation)
			{
				file = new File(file, name);
			}
			URL[] urls =
			{ file.toURI().toURL() };
			ClassLoader cl = URLClassLoader.newInstance(urls);
			cl.setPackageAssertionStatus("com.sun.tools.javac", true);
			return Class.forName(defaultJavaCompilerName, false, cl);
		}

		private static Class<?> enableAsserts(Class<?> cls) {
			try
			{
				ClassLoader loader = cls.getClassLoader();
				if(loader != null)
				{
					loader.setPackageAssertionStatus("com.sun.tools.javac", true);
				}
			} catch (SecurityException ex)
			{
				// ignored
				logger.info("Could not get the loader.");
			}
			return cls;
		}
	}

}
