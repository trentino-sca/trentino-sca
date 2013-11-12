package org.trentino.tools.bindingsca;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import org.apache.log4j.xml.DOMConfigurator;
import org.junit.Test;
import org.trentino.trengen.tools.bindingsca.TIDL2Protobuf;
import org.trentino.trengen.tools.bindingsca.TIDLParseException;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.generation.bindingsca.ContextCppInterface;
import org.trentino.trengen.tools.trengen.TrentinoTest;

public class TIDL2ProtobufTest extends TrentinoTest {
	static
	{
		DOMConfigurator.configure(ConfigLoader.LOG_CONFIG_XML_DEBUG);
	}

	@Test
	public void parse_Return_AModel_With_The_Name_BasicCalculator() {
		File tidl = new File("./src/test/resources/tidl/samples/BasicCalculator.java");
		List<String> generatedBeanHeaders = new ArrayList<String>();
		TIDL2Protobuf converter = new TIDL2Protobuf();
		File destDir = new File("./target");
		try
		{
			ContextCppInterface  ctx = converter.createContext(tidl, (File)null, destDir, generatedBeanHeaders,null);
			converter.generate(ctx);
		} catch (TIDLParseException e)
		{
			fail(e.getMessage());
		} catch (Exception e)
		{
			System.out.println("could not create CPP interface");
			e.printStackTrace();
		}
		File result = new File(destDir, "tidlsamplesBasicCalculatorRequest.proto");
		assertTrue(result.exists());
	}

}
