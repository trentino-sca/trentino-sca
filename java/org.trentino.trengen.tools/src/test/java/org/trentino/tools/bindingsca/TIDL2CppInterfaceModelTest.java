package org.trentino.tools.bindingsca;

import java.io.File;
import java.util.List;

import org.apache.log4j.xml.DOMConfigurator;
import org.junit.Test;
import org.trentino.trengen.tools.bindingsca.TIDL2CppInterfaceModel;
import org.trentino.trengen.tools.bindingsca.TIDLInterfaceModel;
import org.trentino.trengen.tools.bindingsca.TIDLParseException;
import org.trentino.trengen.tools.configuration.ConfigLoader;
import org.trentino.trengen.tools.trengen.TrentinoTest;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;

public class TIDL2CppInterfaceModelTest extends TrentinoTest {
	static
	{
		DOMConfigurator.configure(ConfigLoader.LOG_CONFIG_XML_DEBUG);
	}

	@Test
	public void parse_Return_AModel_With_The_Name_BasicCalculator() {
		TIDL2CppInterfaceModel converter = new TIDL2CppInterfaceModel();
		File tidl = new File("./src/test/resources/tidl/samples/BasicCalculator.java");
		if(!tidl.exists())
		{
			System.out.println(tidl.getAbsolutePath());
			assertTrue(false);
		}
		List<TIDLInterfaceModel> models = null;
		try
		{
			models = converter.parse(tidl);
		} catch (TIDLParseException e)
		{
			e.printStackTrace();
		}
		assertNotNull("Model created", models);
		assertTrue(models.size() == 1);
		TIDLInterfaceModel model = models.get(0);
		assertEquals(model.getQualifiedName(), "tidl.samples.BasicCalculator");

	}

}
