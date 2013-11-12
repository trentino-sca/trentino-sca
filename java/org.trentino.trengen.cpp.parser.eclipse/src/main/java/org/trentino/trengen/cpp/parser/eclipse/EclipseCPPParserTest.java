package org.trentino.trengen.cpp.parser.eclipse;

import org.trentino.trengen.cpp.model.HeaderFile;

public final class EclipseCPPParserTest {
	private EclipseCPPParserTest () {
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String filename = args[0];

		EclipseCPPParser eclipseCPPParser = new EclipseCPPParser(null,null);
		HeaderFile headerfile = eclipseCPPParser.parse(filename);

		System.out.println(headerfile.getName());
	}

}
