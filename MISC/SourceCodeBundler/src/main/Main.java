package main;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathConstants;
import javax.xml.xpath.XPathExpression;
import javax.xml.xpath.XPathFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class Main {

	static String M2_REPO = "C:\\Users\\z002ttbb\\.m2\\repository";

	/**
	 * @param args
	 * @throws Exception
	 */
	public static void main(String[] args) throws Exception {
		String[] classpathFiles = { 
				"I:\\Trentino\\trentino\\DEV\\java\\org.trentino.trengen.sxd2proto\\.classpath",  
				"I:\\Trentino\\trentino\\DEV\\java\\org.trentino.trengen.model\\.classpath", 
				"I:\\Trentino\\trentino\\DEV\\java\\org.trentino.trengen.cpp.parser\\.classpath",
				 "I:\\Trentino\\trentino\\DEV\\java\\org.trentino.trengen.tools\\.classpath"};
		File output = new File("I:\\Trentino\\trentino\\DEV\\java\\3rdparty-src");
		for (String classPathFile : classpathFiles) {
			copySoure(classPathFile, output);
		}

	}

	private static void copySoure(String classPathFile, File output)
			throws Exception {
		DocumentBuilderFactory domFactory = DocumentBuilderFactory
				.newInstance();
		domFactory.setNamespaceAware(true);
		DocumentBuilder builder = domFactory.newDocumentBuilder();
		Document doc = builder.parse(classPathFile);
		XPath xpath = XPathFactory.newInstance().newXPath();
		// XPath Query for showing all nodes value
		XPathExpression expr = xpath.compile("//@sourcepath");
		NodeList value = (NodeList) expr.evaluate(doc, XPathConstants.NODESET);
		int len = value.getLength();
		for (int i = 0; i < len; i++) {
			Node node = value.item(i);
			String sourcepath = node.getTextContent();
			if (sourcepath == null) {
				continue;
			}
			sourcepath = sourcepath.replace("M2_REPO", M2_REPO);
			copy(sourcepath, output);
		}
		System.out.print(value);

	}

	private static void copy(String sourcepath, File output) {
		File f = new File(sourcepath);
		File outFile = new File(output,f.getName());
        if(outFile.exists()){
        	return;
        }
		int available =0;
		try{
			FileInputStream fis = new FileInputStream(f);
			FileOutputStream fos = new FileOutputStream(outFile);
			while((available = fis.available())>0){
				byte[] bytes = new byte[available];
				fis.read(bytes);
				fos.write(bytes);
			}

		}catch (Exception e) {
			e.printStackTrace();
		}
	
	}

}
