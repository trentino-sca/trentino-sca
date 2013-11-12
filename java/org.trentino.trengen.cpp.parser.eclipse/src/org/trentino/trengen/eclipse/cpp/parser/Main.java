// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
// http://trentino.sourceforge.net/
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
// **********************************************************************************

package org.trentino.trengen.eclipse.cpp.parser;

import org.eclipse.cdt.core.dom.ICodeReaderFactory;
import org.eclipse.cdt.core.dom.ast.IASTTranslationUnit;
import org.eclipse.cdt.core.dom.parser.IScannerExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.ISourceCodeParser;
import org.eclipse.cdt.core.dom.parser.c.GCCScannerExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.cpp.ANSICPPParserExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.cpp.GPPParserExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.cpp.GPPScannerExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.cpp.ICPPParserExtensionConfiguration;
import org.eclipse.cdt.core.parser.AbstractParserLogService;
import org.eclipse.cdt.core.parser.CodeReader;
import org.eclipse.cdt.core.parser.FileContent;
import org.eclipse.cdt.core.parser.IParserLogService;
import org.eclipse.cdt.core.parser.IScanner;
import org.eclipse.cdt.core.parser.IScannerInfo;
import org.eclipse.cdt.core.parser.IncludeFileContentProvider;
import org.eclipse.cdt.core.parser.ParserLanguage;
import org.eclipse.cdt.core.parser.ParserMode;
import org.eclipse.cdt.core.parser.ParserUtil;
import org.eclipse.cdt.core.parser.ScannerInfo;
import org.eclipse.cdt.core.parser.util.ASTPrinter;
import org.eclipse.cdt.internal.core.dom.NullCodeReaderFactory;
import org.eclipse.cdt.internal.core.dom.SavedCodeReaderFactory;
import org.eclipse.cdt.internal.core.dom.parser.cpp.GNUCPPSourceParser;
import org.eclipse.cdt.internal.core.indexer.StandaloneIndexerFallbackReaderFactory;
import org.eclipse.cdt.internal.core.model.DebugLogConstants;
import org.eclipse.cdt.internal.core.parser.ParserLogService;
import org.eclipse.cdt.internal.core.parser.scanner.CPreprocessor;

public class Main {

	protected static final GCCScannerExtensionConfiguration C_GNU_SCANNER_EXTENSION = GCCScannerExtensionConfiguration
			.getInstance();
	protected static final GPPScannerExtensionConfiguration CPP_GNU_SCANNER_EXTENSION = GPPScannerExtensionConfiguration
			.getInstance();
	private static final String[] dialects = { "C99", //$NON-NLS-1$
			"C++98", //$NON-NLS-1$
			"GNUC", //$NON-NLS-1$
			"GNUC++" //$NON-NLS-1$
	};

	/**
	 * @param args
	 */
	public static void main(String[] args) {
   String filename = args[0];
   IASTTranslationUnit unit = getTranslationUnit(filename, dialects[1]);
   System.out.println(unit);
   ASTPrinter.print(unit);
	}

	public static IASTTranslationUnit getTranslationUnit(String filename, String dialect)
		 {
		IParserLogService scannerLogService = new AbstractParserLogService() {
			@Override
			public void traceLog(String message) {
				System.out.println("[TRACE]"+message);
			}
			@Override
			public void errorLog(String message) {
				System.out.println("[ERROR]"+message);;
			}
		};
		IScannerInfo scanInfo = new ScannerInfo();
		ICPPParserExtensionConfiguration config =null;
		ICodeReaderFactory fileCreator = new StandaloneIndexerFallbackReaderFactory();
		CodeReader reader = fileCreator.createCodeReaderForTranslationUnit(filename);
		if (reader == null)
			return null;
		IScanner scanner = null;
		ISourceCodeParser parser = null;
		boolean[] isSource = { false };

		{
			if (dialect.equals(dialects[1]) || dialect.equals(dialects[3]))
				scanner = createScanner(reader, scanInfo,
						ParserMode.COMPLETE_PARSE, ParserLanguage.CPP,
						scannerLogService,
						CPP_GNU_SCANNER_EXTENSION, fileCreator);
			else
				throw new IllegalArgumentException("Unsupported dialect");

			if (dialect.equals(dialects[1])) {
				 config = new ANSICPPParserExtensionConfiguration();

			}

			else if (dialect.equals(dialects[3])) {
				 config = new GPPParserExtensionConfiguration();
			}
			parser = new GNUCPPSourceParser(scanner, ParserMode.COMPLETE_PARSE,
					scannerLogService, config);
		}
		// Parse
		if (parser != null) {
			IASTTranslationUnit ast = parser.parse();
			ast.setIsHeaderUnit(!isSource[0]);
			return ast;
		}
		return null;
	}

	private static IScanner createScanner(CodeReader reader,
			IScannerInfo scanInfo, ParserMode mode, ParserLanguage lang,
			IParserLogService log, IScannerExtensionConfiguration scanConfig,
			ICodeReaderFactory fileCreator) {
		return new CPreprocessor(FileContent.adapt(reader), scanInfo, lang,
				log, scanConfig, IncludeFileContentProvider.adapt(fileCreator));
	}

}
