package org.trentino.tools.bindingsca;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import java.io.File;

import org.apache.log4j.xml.DOMConfigurator;
import org.junit.Before;
import org.junit.Test;
import org.trentino.trengen.cpp.model.ClassMethod;
import org.trentino.trengen.cpp.model.ClassMethodArgument;
import org.trentino.trengen.cpp.model.HeaderFile;
import org.trentino.trengen.cpp.parser.eclipse.EclipseCPPParser;
import org.trentino.trengen.tools.bindingsca.TIDL2CppInterface;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.tools.trengen.TrentinoTest;

public class TIDL2CppInterfaceTest extends TrentinoTest {

	private static File	systemTestDataDir;

	static EclipseCPPParser eclipseCPPParser = new EclipseCPPParser(null,null);
	
	TIDL2CppInterface	converter;

	static
	{
		try{
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
		}catch (Exception e) {
			e.printStackTrace();
		}
	

	}

	@Before
	public void init() {
		converter = new TIDL2CppInterface();
	}

	@Test
	public void parse_Return_AModel_With_The_Name_BasicCalculator() throws Exception {
		Trengen.initInstance();
		File tidl = new File("./src/test/resources/tidl/samples/BasicCalculator.java");
		File destDir = new File("./target");

		converter.createCppInterface(tidl, null, destDir, null);
		File result = new File(destDir, "BasicCalculator.h");
		assertTrue(result.exists());
	}

	@Test
	public void testHelloWordWithEnumGeneratedCodeHasExpectedMethod() throws Exception {
		Trengen.initInstance();
		File tidl = getFile("HelloWorldRemote/HelloWorldRemoteEnumClient_Source/HelloWorld.java");
		File destDir = new File("./target");
		File result = new File(destDir, "HelloWorld.h");
		if(result.exists()){
			result.delete();
		}
		converter.createCppInterface(tidl, null, destDir, null);
		assertTrue(result.exists());
		result.deleteOnExit();
		HeaderFile headerFile = HeaderUtil.getHeaderFile(result);
		assertNotNull(headerFile);
		ClassMethod  method = HeaderUtil.getMethod(headerFile, "Trentino::Example::HelloWorldRemote::HelloWorld", "hello");
		assertNotNull(method);
		assertEquals(2,method.getArguments().size());
		ClassMethodArgument arg2 = method.getArguments().get(1);
		assertEquals("const Trentino::Example::HelloWorldRemote::HelloWorld::MessageType&",arg2.getType());
	}

	public static File getFile(String contributionPath) {
		File file = new File(systemTestDataDir, contributionPath);
		if(!file.exists())
		{
			throw new IllegalStateException("Directory for Trentino System Test data does not exists or is not a directory " + file);
		}
		return file;
	}
	


}
