/************************************************************************************
 * // Trentino - A C++ based lightweight, non-invasive SCA runtime.
 * // Copyright (C) Siemens AG, 2012
 * // All Rights Reserved
 * // http://trentino.sourceforge.net/
 * //
 * // This library is free software; you can redistribute it and/or
 * // modify it under the terms of the GNU Lesser General Public
 * // License as published by the Free Software Foundation; either
 * // version 2.1 of the License, or (at your option) any later version.
 * //
 * // This library is distributed in the hope that it will be useful,
 * // but WITHOUT ANY WARRANTY; without even the implied warranty of
 * // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * // Lesser General Public License for more details.
 * //
 * // You should have received a copy of the GNU Lesser General Public
 * // License along with this library; if not, write to the Free Software
 * // Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * //
 *********************************************************************************/

package org.trentino.trengen.cpp.parser.eclipse;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.regex.Pattern;

import org.apache.log4j.Logger;
import org.eclipse.cdt.core.dom.ICodeReaderFactory;
import org.eclipse.cdt.core.dom.ast.DOMException;
import org.eclipse.cdt.core.dom.ast.IASTNode;
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorStatement;
import org.eclipse.cdt.core.dom.ast.IASTTranslationUnit;
import org.eclipse.cdt.core.dom.ast.IBinding;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTTranslationUnit;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPClassType;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPMethod;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPNamespace;
import org.eclipse.cdt.core.dom.parser.IScannerExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.ISourceCodeParser;
import org.eclipse.cdt.core.dom.parser.c.GCCScannerExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.cpp.ANSICPPParserExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.cpp.GPPParserExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.cpp.GPPScannerExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.cpp.ICPPParserExtensionConfiguration;
import org.eclipse.cdt.core.parser.AbstractParserLogService;
import org.eclipse.cdt.core.parser.CodeReader;
import org.eclipse.cdt.core.parser.ExtendedScannerInfo;
import org.eclipse.cdt.core.parser.FileContent;
import org.eclipse.cdt.core.parser.IParserLogService;
import org.eclipse.cdt.core.parser.IScanner;
import org.eclipse.cdt.core.parser.IScannerInfo;
import org.eclipse.cdt.core.parser.IncludeFileContentProvider;
import org.eclipse.cdt.core.parser.ParserLanguage;
import org.eclipse.cdt.core.parser.ParserMode;
import org.eclipse.cdt.core.parser.ScannerInfo;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTNamespaceAlias;
import org.eclipse.cdt.internal.core.dom.parser.cpp.GNUCPPSourceParser;
import org.eclipse.cdt.internal.core.indexer.StandaloneIndexerFallbackReaderFactory;
import org.eclipse.cdt.internal.core.parser.scanner.CPreprocessor;
import org.trentino.trengen.cpp.model.ClassMethod;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.cpp.model.CppParser;
import org.trentino.trengen.cpp.model.HeaderFile;
import org.trentino.trengen.cpp.model.IncludeFile;

public class EclipseCPPParser implements CppParser {

	protected static final Logger	                        logger	                  = Logger.getLogger(EclipseCPPParser.class);
	protected static final GCCScannerExtensionConfiguration	C_GNU_SCANNER_EXTENSION	  = GCCScannerExtensionConfiguration.getInstance();
	protected static final GPPScannerExtensionConfiguration	CPP_GNU_SCANNER_EXTENSION	= GPPScannerExtensionConfiguration.getInstance();
	private static final String[]	                        dialects	              =
	                                                                                  { "C99", //$NON-NLS-1$
	        "C++98", //$NON-NLS-1$
	        "GNUC", //$NON-NLS-1$
	        "GNUC++" //$NON-NLS-1$
	                                                                                  };
	private Map<String, String>	                            fMacroMap	              = new HashMap<String, String>();
	private String[]	                                    includePaths	          = {};
	private String[]	                                    excludeDirs	              = {};
	private TranslationUnitCollector collector = new TranslationUnitCollector();

	public EclipseCPPParser (Map<String, String> fMacroMap, String[] includePaths) {
		this(fMacroMap, includePaths, null);
	}

	public EclipseCPPParser (Map<String, String> fMacroMap, String[] includePaths, String[] excludePaths) {
		if(fMacroMap != null)
		{
			this.fMacroMap = fMacroMap;
		}
		if(includePaths != null)
		{
			this.includePaths = includePaths;
		}

		if(excludePaths != null)
		{
			this.excludeDirs = excludePaths;
		}
	}

	public static List<CPPASTNamespaceAlias>	namespaces	= new ArrayList<CPPASTNamespaceAlias>();

	public HeaderFile parse(String path) {
		String filename = path;
		// System.out.println("parsing----> " + path);
		ICPPASTTranslationUnit unit = (ICPPASTTranslationUnit) getASTTranslationUnit(filename, dialects[1]);

		if(unit == null)
		{
			String format = "CPP parser could not create translation unit for file " + filename
			        + ". Make sure that your contribution is correcty installed";
			throw new IllegalStateException(format);
		}

		HeaderFile headerFile = new HeaderFile();
		headerFile.setName(path);

		EclipseASTVisitor2 myVisitor = new EclipseASTVisitor2(headerFile);
		myVisitor.settranslationUnitCollector(collector);
		IASTPreprocessorStatement[] macros = unit.getAllPreprocessorStatements();

		List<IncludeFile> includedFiles = new ArrayList<IncludeFile>();
		for (IASTPreprocessorStatement macro : macros)
		{

			if(macro.getClass().getName().equals("org.eclipse.cdt.internal.core.parser.scanner.ASTInclusionStatement"))
			{
				String includedFilePath = macro.toString().replace("#include ", "").replace("\"", "");
				IncludeFile includedFile = new IncludeFile();
				includedFile.setPath(includedFilePath);
				includedFiles.add(includedFile);
				// System.out.println("inclusion statement:" + includedFilePath);
			}
		}// end of for populating the includion statements

		headerFile.setIncludedFile(includedFiles);
		unit.accept(myVisitor);
		return headerFile;
	}







	private IASTTranslationUnit getASTTranslationUnit(String filename, String dialect) {
		try
        {
	        String path = new File(filename).getCanonicalPath();
	        IASTTranslationUnit res = collector.getTranslationUnit(path);
	        if(res!=null){
	        	return res;
	        }
        } catch (IOException e)
        {
	       throw new IllegalArgumentException("Cannot create canonila file",e);
        }
		IParserLogService scannerLogService = new AbstractParserLogService() {
			@Override
			public void traceLog(String message) {
				// System.out.println("[TRACE]" + message);
			}

			@Override
			public void errorLog(String message) {
				// System.out.println("[ERROR]" + message);
			}
		};
		Set<String> incs = new HashSet<String>(Arrays.asList(includePaths));
		for(String ex : excludeDirs){
			if(ex ==null){
				continue;
			}
			String removeRegex = ex.replaceAll("\\*", ".*");
			removeRegex =removeRegex.replace("\\", "\\\\");
			Pattern removePattern = Pattern.compile(removeRegex);
			for(String inc : includePaths){
				if(removePattern.matcher(inc).matches()){
					incs.remove(inc);
				}
			}
		}
		
		String[] incArray = new String[incs.size()];
		int i=0;
		for(String v : incs){
			incArray[i]=v;
			i++;
		}
		IScannerInfo scanInfo = new ExtendedScannerInfo(fMacroMap, incArray);
		ICPPParserExtensionConfiguration config = null;
		ICodeReaderFactory fileCreator = new StandaloneIndexerFallbackReaderFactory();
		CodeReader reader = fileCreator.createCodeReaderForTranslationUnit(filename);
		if(reader == null)
		{
			return null;
		}
		IScanner scanner = null;
		ISourceCodeParser parser = null;
		boolean[] isSource =
		{ false };

		if(dialect.equals(dialects[1]) || dialect.equals(dialects[3]))
		{
			scanner = createScanner(reader, scanInfo, ParserMode.STRUCTURAL_PARSE, ParserLanguage.CPP, scannerLogService, CPP_GNU_SCANNER_EXTENSION,
			        fileCreator);
		}
		else
		{
			throw new IllegalArgumentException("Unsupported dialect");
		}

		if(dialect.equals(dialects[1]))
		{
			config = new ANSICPPParserExtensionConfiguration();

		}

		else if(dialect.equals(dialects[3]))
		{
			config = new GPPParserExtensionConfiguration();
		}
		parser = new GNUCPPSourceParser(scanner, ParserMode.STRUCTURAL_PARSE, scannerLogService, config);

		// Parse
		if(parser != null)
		{
			IASTTranslationUnit ast = parser.parse();

			ast.setIsHeaderUnit(!isSource[0]);
			return ast;
		}
		return null;
	}

	private IScanner createScanner(CodeReader reader, IScannerInfo scanInfo, ParserMode mode, ParserLanguage lang, IParserLogService log,
	        IScannerExtensionConfiguration scanConfig, ICodeReaderFactory fileCreator) {
		return new CPreprocessor(FileContent.adapt(reader), scanInfo, lang, log, scanConfig, IncludeFileContentProvider.adapt(fileCreator));
	}

}
