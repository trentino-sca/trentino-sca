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

import java.io.File;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

import javax.swing.text.StyledEditorKit.ItalicAction;

import org.eclipse.cdt.core.dom.ICodeReaderFactory;
import org.eclipse.cdt.core.dom.ast.ASTVisitor;
import org.eclipse.cdt.core.dom.ast.ExpansionOverlapsBoundaryException;
import org.eclipse.cdt.core.dom.ast.IASTASMDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTDeclSpecifier;
import org.eclipse.cdt.core.dom.ast.IASTDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTDeclarator;
import org.eclipse.cdt.core.dom.ast.IASTFunctionDeclarator;
import org.eclipse.cdt.core.dom.ast.IASTFunctionDefinition;
import org.eclipse.cdt.core.dom.ast.IASTMacroExpansion;
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorIncludeStatement;
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorMacroDefinition;
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorMacroExpansion;
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorStatement;
import org.eclipse.cdt.core.dom.ast.IASTSimpleDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTStatement;
import org.eclipse.cdt.core.dom.ast.IASTTranslationUnit;
import org.eclipse.cdt.core.dom.ast.IASTTranslationUnit.IDependencyTree.IASTInclusionNode;
import org.eclipse.cdt.core.dom.ast.c.ICASTTypedefNameSpecifier;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTNamespaceAlias;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTNamespaceDefinition;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTParameterDeclaration;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTVisibilityLabel;
import org.eclipse.cdt.core.dom.parser.IScannerExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.ISourceCodeParser;
import org.eclipse.cdt.core.dom.parser.c.GCCScannerExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.cpp.ANSICPPParserExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.cpp.GPPParserExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.cpp.GPPScannerExtensionConfiguration;
import org.eclipse.cdt.core.dom.parser.cpp.ICPPParserExtensionConfiguration;
import org.eclipse.cdt.core.model.CoreModelUtil;
import org.eclipse.cdt.core.model.ICElement;
import org.eclipse.cdt.core.model.ICElementVisitor;
import org.eclipse.cdt.core.model.IDeclaration;
import org.eclipse.cdt.core.model.ITranslationUnit;
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
import org.eclipse.cdt.internal.core.dom.parser.ASTInternal;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTCompositeTypeSpecifier;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTDeclarator;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTFunctionDeclarator;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTFunctionDefinition;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTName;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTNamespaceAlias;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTNamespaceDefinition;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTParameterDeclaration;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTSimpleDeclaration;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTUsingDeclaration;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTUsingDirective;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTVisibilityLabel;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPNamespace;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPUsingDirective;
import org.eclipse.cdt.internal.core.dom.parser.cpp.GNUCPPSourceParser;
import org.eclipse.cdt.internal.core.indexer.StandaloneIndexerFallbackReaderFactory;
import org.eclipse.cdt.internal.core.model.DebugLogConstants;
import org.eclipse.cdt.internal.core.parser.ParserLogService;
import org.eclipse.cdt.internal.core.parser.scanner.CPreprocessor;
import org.eclipse.cdt.internal.core.pdom.dom.cpp.CPPFindBinding.CPPBindingBTreeComparator;
import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IWorkspaceRoot;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.FileLocator;
import org.eclipse.core.runtime.IPath;
import org.eclipse.core.runtime.Path;


public class MainAnk2 {

	protected static final GCCScannerExtensionConfiguration C_GNU_SCANNER_EXTENSION = GCCScannerExtensionConfiguration
			.getInstance();
	protected static final GPPScannerExtensionConfiguration CPP_GNU_SCANNER_EXTENSION = GPPScannerExtensionConfiguration
			.getInstance();
	private static final String[] dialects = { "C99", //$NON-NLS-1$
			"C++98", //$NON-NLS-1$
			"GNUC", //$NON-NLS-1$
			"GNUC++" //$NON-NLS-1$
	};

	public static String currentLabel = "";
	public static String currentNamespace = "";
	public static boolean classPassed = false;
	public static List<CPPASTNamespaceAlias> namespaces = new ArrayList<CPPASTNamespaceAlias>();
	/**
	 * @param args
	 * @throws CoreException 
	 * @throws URISyntaxException 
	 */
	public static void main(String[] args) throws CoreException, URISyntaxException 
	{
		String filename = "C:\\TrentinoContributions\\BasicCalculator_Source\\services\\TrentinoExampleBasicCalculatorCalculator.h";
		IASTTranslationUnit unit = getASTTranslationUnit(filename, dialects[1]);
		

		/*System.out.println("Classes:");
		for (IASTDeclaration decl : decls) 
		{
			CPPASTNamespaceDefinition def = (CPPASTNamespaceDefinition) decl;
			System.out.println("#" + def.getRawSignature() + "#");
			IASTDeclaration[] decs = def.getDeclarations();
			for(IASTDeclaration d : decs)
				System.out.println("***" + d.toString() + "***");
		}*/
		ITranslationUnit tu = (ITranslationUnit)unit.getAdapter(ITranslationUnit.class);
		walkAstTU(unit);
		
		//ITranslationUnit tu = getTranslationUnit(filename);
		//walkITU(tu);
		//walkITU_AST(unit);
//		if (unit instanceof IASTTranslationUnit) 
//		{
//			IASTPreprocessorStatement[] preStats = ((IASTTranslationUnit)unit).getAllPreprocessorStatements();
//			if (preStats != null) 
//			{
//				for (IASTPreprocessorStatement stat : preStats)
//				{
//					ASTPrinter.print(stat);
//				}
//			}
//		}
//		if (unit instanceof IASTTranslationUnit) 
//		{
//			IASTPreprocessorIncludeStatement[] includes = ((IASTTranslationUnit)unit).getIncludeDirectives();
//			if (includes != null) 
//			{
//				for (IASTPreprocessorStatement include : includes)
//				{
//					System.out.println(include.getClass().getName());
//				}
//			}
//		}
		//System.out.println(unit);
		//ASTPrinter.print(unit);
	}

//	private static ITranslationUnit getTranslationUnit(String fileName) throws CoreException, URISyntaxException
//    {
////		URL fileUrl = FileLocator.toFileURL(new URL(fileName));  
////		IPath p = new Path(fileName);
////		IWorkspaceRoot.getFileForLocation(p); 
//		
////		IPath location = new Path(name);
////		IFile file = project.getFile(location.lastSegment());
//
////	    File f = new File(fileName);
////		String p = f.getAbsolutePath();
////		IPath path = new Path(p);
////		IFile iFile = ResourcesPlugin.getFile(path);
////		fileName = fileName.replace("\\","/");
////		URI locationURI = new URI(fileName);
////		
//		ITranslationUnit tu =getTranslationUnit(fileName);
//		return tu;
//		
//    }

	public static IASTTranslationUnit getASTTranslationUnit(String filename,String dialect) {
		IParserLogService scannerLogService = new AbstractParserLogService() {
			@Override
			public void traceLog(String message) {
				System.out.println("[TRACE]" + message);
			}

			@Override
			public void errorLog(String message) {
				System.out.println("[ERROR]" + message);
				;
			}
		};
		IScannerInfo scanInfo = new ScannerInfo();
		ICPPParserExtensionConfiguration config = null;
		ICodeReaderFactory fileCreator = new StandaloneIndexerFallbackReaderFactory();
		CodeReader reader = fileCreator
				.createCodeReaderForTranslationUnit(filename);
		if (reader == null)
			return null;
		IScanner scanner = null;
		ISourceCodeParser parser = null;
		boolean[] isSource = { false };

		{
			if (dialect.equals(dialects[1]) || dialect.equals(dialects[3]))
				scanner = createScanner(reader, scanInfo,
						ParserMode.COMPLETE_PARSE, ParserLanguage.CPP,
						scannerLogService, CPP_GNU_SCANNER_EXTENSION,
						fileCreator);
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


	
	
	private static void walkAstTU(IASTTranslationUnit tu) throws CoreException 
	{
		MyASTVisitor2 myVisitor = new MyASTVisitor2();
		IASTPreprocessorMacroExpansion[] m = tu.getMacroExpansions();
		for( IASTPreprocessorMacroExpansion i: m)
		{
			System.out.println("Macrooo" + i.getMacroReference() +" " + i.getMacroDefinition().getExpansion());
			
		}
		IASTDeclaration[] usings = tu.getDeclarations();
		for (IASTDeclaration using : usings)
		{
			//System.out.println("using directives:" + using.getClass().getName());
			if (using instanceof CPPASTUsingDirective)
				System.out.println("using decleration:" + ((CPPASTUsingDirective)using).getRawSignature());
			else if (using instanceof CPPASTUsingDeclaration)
				System.out.println("using directives:" + ((CPPASTUsingDeclaration)using).getRawSignature());
			else if (using instanceof CPPASTNamespaceAlias)
			{
				namespaces.add(((CPPASTNamespaceAlias)using));
				System.out.println("using namespace alias:" + ((CPPASTNamespaceAlias)using).getRawSignature());
			}
				
				
				
		}
		IASTPreprocessorStatement[] macros= tu.getAllPreprocessorStatements();
		for (IASTPreprocessorStatement macro : macros)
		{
			
			if (macro.getClass().getName().equals("org.eclipse.cdt.internal.core.parser.scanner.ASTInclusionStatement"))
			{
				System.out.println("inclusion statement:" + macro.toString().replace("#include ", "").replace("\"",""));
			}
			
			
		}
		tu.accept(myVisitor);
	}
	
	private static void walkITU(ITranslationUnit tu) throws CoreException 
	{
		//String tuName = tu.getElementName();
		//System.out.println("ITranslationUnit name: " + tu.getRawSignature());
		MyElementVisitor myVisitor = new MyElementVisitor();
		tu.accept(myVisitor);
	}
	
}
class MyASTVisitor2 extends ASTVisitor
{
	public MyASTVisitor2()
	{
		this.shouldVisitStatements=true; // lots more
		this.shouldVisitDeclarations=true;
		this.shouldVisitAmbiguousNodes = true;
		this.shouldVisitArrayModifiers = true;
		this.shouldVisitBaseSpecifiers = true;
		this.shouldVisitCaptures = true;
		this.shouldVisitDeclarations = true;
		this.shouldVisitDeclarators = true;
		this.shouldVisitDeclSpecifiers = true;
		this.shouldVisitDesignators = true;
		this.shouldVisitEnumerators = true;
		this.shouldVisitExpressions = true;
		this.shouldVisitExpressions = true;
		this.shouldVisitImplicitNameAlternates = true;
		this.shouldVisitImplicitNames = true;
		this.shouldVisitInitializers = true;
		this.shouldVisitNames = true;
		this.shouldVisitNamespaces = true;
		this.shouldVisitParameterDeclarations = true;
		this.shouldVisitPointerOperators = true;
		this.shouldVisitProblems = true;
		this.shouldVisitStatements = true;
		this.shouldVisitTemplateParameters = true;
		this.shouldVisitTranslationUnit = true;
		this.shouldVisitTypeIds = true;
	}
	
	
	
	public int visit(ICPPASTNamespaceDefinition stmt) 
	{ // lots more
		if (MainAnk2.classPassed)
		{
			MainAnk2.currentNamespace = "";
			MainAnk2.classPassed = false;
		}
		if (MainAnk2.currentNamespace.equals(""))
			MainAnk2.currentNamespace = ((CPPASTNamespaceDefinition)stmt).getName().toString();
		else
			MainAnk2.currentNamespace = MainAnk2.currentNamespace + "::"+((CPPASTNamespaceDefinition)stmt).getName().toString();
		return PROCESS_CONTINUE;
	}
	public int visit(IASTStatement stmt) 
	{ // lots more
		System.out.println("Visiting stmt: "+stmt.getRawSignature());
		return PROCESS_CONTINUE;
	}
	public int visit(IASTDeclaration decl) 
	{
		//System.out.println("Visiting astDecl: "+decl.getRawSignature());
		if (decl instanceof CPPASTSimpleDeclaration)
		{
			CPPASTSimpleDeclaration d = (CPPASTSimpleDeclaration) decl;
			//System.out.println("Visiting SimplDecl: "+d.getRawSignature());
			
			
			if (d.getDeclSpecifier() instanceof CPPASTCompositeTypeSpecifier)
			{
				CPPASTCompositeTypeSpecifier decom = (CPPASTCompositeTypeSpecifier) d.getDeclSpecifier();
				ICPPASTBaseSpecifier[] bases = decom.getBaseSpecifiers();
				for (ICPPASTBaseSpecifier base : bases)
				{
					System.out.println("Visiting BaseClass: "+base.getName());
				}
				System.out.println("Visiting class name: "+decom.getName());
				MainAnk2.classPassed = true;
				System.out.println("Namespace: " + MainAnk2.currentNamespace);
			}
			
			IASTDeclarator[] declerators = d.getDeclarators();
			for (IASTDeclarator dec: declerators)
			{
				//System.out.println("Visiting declerator class: "+dec.getClass().getName());	
				if (dec instanceof CPPASTFunctionDeclarator)
				{
					CPPASTFunctionDeclarator decs = (CPPASTFunctionDeclarator) dec;
					ICPPASTParameterDeclaration[] params = decs.getParameters();
					for (ICPPASTParameterDeclaration param : params)
					{
						CPPASTParameterDeclaration param2 = (CPPASTParameterDeclaration) param;
						if (param2.getDeclSpecifier().getRawSignature().contains("::"))
						{
							boolean exists = false;
							for (CPPASTNamespaceAlias namespace: MainAnk2.namespaces)
							{
								int index= param2.getDeclSpecifier().getRawSignature().lastIndexOf("::");
								String namespaceOfParam = param2.getDeclSpecifier().getRawSignature().substring(0,index);
								if (namespaceOfParam.toString().equals(namespace.getAlias().toString()))
								{
									exists = true;
									System.out.println("Visiting param: "+param2.getDeclarator().getName() + " " + namespace.getMappingName());
									break;
								}
							}	
							if (exists ==false)
							{
								try {
									System.out.println("Visiting param: "+param2.getDeclarator().getName() + " " + param2.getSyntax());
								} catch (ExpansionOverlapsBoundaryException e) {
									e.printStackTrace();
								}
							}
						} else
							try {
								System.out.println("Visiting param: "+param2.getDeclarator().getName() + " " + param2.getSyntax());
							} catch (ExpansionOverlapsBoundaryException e) {
								e.printStackTrace();
							}
					}
					System.out.println("Visiting funcReturnType: "+d.getDeclSpecifier());

					System.out.println("Visiting Class Method name: " + decs.getName() + " " + MainAnk2.currentLabel );
					System.out.println("Class Method isPurevirtual: "+decs.isPureVirtual() );
				}
				else if (dec instanceof CPPASTDeclarator)
				{
					CPPASTDeclarator decs = (CPPASTDeclarator) dec;
					String memberName = decs.getName().toString();
					String memberFullName = decl.getRawSignature();
					int index = memberFullName.lastIndexOf(" ");
					String memberType = memberFullName.substring(0, index);
					System.out.println("Visiting Class Member: "+ memberName + " " + memberType + " " + MainAnk2.currentLabel);	
				}
			}
		}
		else if (decl instanceof CPPASTVisibilityLabel)
		{
			CPPASTVisibilityLabel d = (CPPASTVisibilityLabel) decl;
			//System.out.println("Visiting label: "+d.getRawSignature());
			MainAnk2.currentLabel = d.getRawSignature().substring(0, d.getLength() -1);
		}
		return PROCESS_CONTINUE;
	}
	
	public int visit(ICPPASTVisibilityLabel decl) 
	{
		System.out.println("Visiting visibilityLabel: "+decl.getRawSignature());
		return PROCESS_CONTINUE;
	}
	
	public int visit(IASTFunctionDefinition decl) 
	{
		System.out.println("Visiting funcDef: "+decl.getRawSignature());
		IASTFunctionDeclarator f = decl.getDeclarator();
		visit(f);
		return PROCESS_CONTINUE;
	}
	
	public int visit(IASTFunctionDeclarator decl) 
	{
		System.out.println("Visiting funcDecl: "+decl.getRawSignature());
		return PROCESS_CONTINUE;
	}
	
	public int visit(IASTASMDeclaration decl) 
	{
		System.out.println("Visiting ssmDecl: "+decl.getRawSignature());
		return PROCESS_CONTINUE;
	}
	//implements IASTSimpleDeclaration
	public int visit(IASTSimpleDeclaration decl) 
	{
		System.out.println("Visiting simpleDecl: "+decl.getRawSignature());
		IASTDeclarator[] decls = decl.getDeclarators();
		for (IASTDeclarator d : decls)
			visit(d);
		return PROCESS_CONTINUE;
	}

//	public int visit(ICElement element) 
//	{
//		boolean visitChildren = true;
//		System.out.println("Visiting: " +element.getElementName());
//		return PROCESS_CONTINUE;
//	}
}
