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

import javax.swing.text.StyledEditorKit.ItalicAction;

import org.eclipse.cdt.core.dom.ICodeReaderFactory;
import org.eclipse.cdt.core.dom.ast.ASTVisitor;
import org.eclipse.cdt.core.dom.ast.IASTASMDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTArrayModifier;
import org.eclipse.cdt.core.dom.ast.IASTDeclSpecifier;
import org.eclipse.cdt.core.dom.ast.IASTDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTDeclarator;
import org.eclipse.cdt.core.dom.ast.IASTExpression;
import org.eclipse.cdt.core.dom.ast.IASTFunctionDefinition;
import org.eclipse.cdt.core.dom.ast.IASTInitializer;
import org.eclipse.cdt.core.dom.ast.IASTName;
import org.eclipse.cdt.core.dom.ast.IASTNode;
import org.eclipse.cdt.core.dom.ast.IASTParameterDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTPointerOperator;
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorIncludeStatement;
import org.eclipse.cdt.core.dom.ast.IASTPreprocessorStatement;
import org.eclipse.cdt.core.dom.ast.IASTProblem;
import org.eclipse.cdt.core.dom.ast.IASTSimpleDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTStatement;
import org.eclipse.cdt.core.dom.ast.IASTTranslationUnit;
import org.eclipse.cdt.core.dom.ast.IASTTypeId;
import org.eclipse.cdt.core.dom.ast.IASTEnumerationSpecifier.IASTEnumerator;
import org.eclipse.cdt.core.dom.ast.IBinding;
import org.eclipse.cdt.core.dom.ast.c.ICASTDesignator;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTCapture;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTNamespaceAlias;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTNamespaceDefinition;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTTemplateParameter;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier;
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
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTCompositeTypeSpecifier;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTSimpleDeclaration;
import org.eclipse.cdt.internal.core.dom.parser.cpp.GNUCPPSourceParser;
import org.eclipse.cdt.internal.core.indexer.StandaloneIndexerFallbackReaderFactory;
import org.eclipse.cdt.internal.core.model.DebugLogConstants;
import org.eclipse.cdt.internal.core.parser.ParserLogService;
import org.eclipse.cdt.internal.core.parser.scanner.CPreprocessor;
import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IWorkspaceRoot;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.FileLocator;
import org.eclipse.core.runtime.IPath;
import org.eclipse.core.runtime.Path;


public class MainAnk3 {

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
	 * @throws CoreException 
	 * @throws URISyntaxException 
	 */
	public static void main(String[] args) throws CoreException, URISyntaxException 
	{
		String filename = args[0];
		IASTTranslationUnit unit = getASTTranslationUnit(filename, dialects[1]);
		
		IASTDeclaration[] decls = unit.getDeclarations();
		System.out.println("Classes:");
		for (IASTDeclaration decl : decls) 
		{
			System.out.println(decl.getClass().getName());
		}
		walkAstTU(unit);
//		IASTNode[] nodes = unit.getChildren();
//		for(int i =0; i < nodes.length ; i++)
//		{
//			System.out.println(nodes[i].getRawSignature());
//		}
//		ITranslationUnit tu = (ITranslationUnit)unit.getAdapter(ITranslationUnit.class);
		//walkITU(tu);
		
		
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
		//String tuName = tu.getElementName();
		//System.out.println("ITranslationUnit name: " + tu.getRawSignature());
		MyASTVisitor3 myVisitor = new MyASTVisitor3();
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
class MyASTVisitor3 extends ASTVisitor
{
	public MyASTVisitor3()
	{
		this.shouldVisitStatements=true; // lots more
		this.shouldVisitDeclarations=true;
		this.shouldVisitNames = true;
		this.shouldVisitDeclarators =  true;
		this.shouldVisitDeclSpecifiers = true;
		this.shouldVisitExpressions = true;
		this.shouldVisitNamespaces = true;
		this.shouldVisitParameterDeclarations = true;
		this.shouldVisitTranslationUnit = true;
	}
	public int visit(IASTStatement stmt) 
	{ // lots more
		System.out.println("Visiting stmt: "+stmt.getRawSignature());
		return PROCESS_CONTINUE;
	}
	public int visit(IASTDeclaration decl) 
	{
		
		if(decl instanceof IASTFunctionDefinition)
		{
			System.out.println("Visiting IASTFunctionDefinition" + decl.getRawSignature());
		}
		else
		if(decl instanceof IASTSimpleDeclaration)
		{
			System.out.println("sssssssssssssssssssssssssssssssssssssssssssssssss");
			//System.out.println("Visiting decl: "+decl.getRawSignature());
		}
		else
		{
			System.out.println("Visiting decl: "+decl.getRawSignature());
		}
		return PROCESS_CONTINUE;
	}

	
	// visit methods
		public int visit(IASTTranslationUnit tu) {
			//System.out.println("Visiting IASTTranslationUnit: "+tu.getRawSignature());
			return PROCESS_CONTINUE;
		}

		public int visit(IASTName name) 
		{
			System.out.println("Visiting IASTName: "+name.toString());
			IBinding binding =  name.getBinding();
			if(binding != null)
			{
				System.out.println("Visiting IASTName binding : "+name.getBinding().toString());
			}
			return PROCESS_CONTINUE;
		}

		public int visit(IASTInitializer initializer) {
			System.out.println("Visiting initializer: "+initializer.getRawSignature());
			return PROCESS_CONTINUE;
		}

		public int visit(IASTParameterDeclaration parameterDeclaration) {
			System.out.println("Visiting parameterDeclaration: "+parameterDeclaration.getRawSignature());
			return PROCESS_CONTINUE;
		}

		public int visit(IASTDeclarator declarator) {
			System.out.println("Visiting declarator: "+declarator.getRawSignature());
			return PROCESS_CONTINUE;
		}

		public int visit(IASTDeclSpecifier declSpec) {
			System.out.println("Visiting declSpec: "+declSpec.toString());
			return PROCESS_CONTINUE;
		}

		/**
		 * @since 5.1
		 */
		public int visit(IASTArrayModifier arrayModifier) {
			System.out.println("Visiting arrayModifier: "+arrayModifier.getRawSignature());
			return PROCESS_CONTINUE;
		}

		/**
		 * @since 5.1
		 */
		public int visit(IASTPointerOperator ptrOperator) {
			System.out.println("Visiting ptrOperator: "+ptrOperator.getRawSignature());
			return PROCESS_CONTINUE;
		}

		public int visit(IASTExpression expression) {
			System.out.println("Visiting expression: "+expression.getRawSignature());
			return PROCESS_CONTINUE;
		}

		public int visit(IASTTypeId typeId) {
			System.out.println("Visiting typeId: "+typeId.getRawSignature());
			return PROCESS_CONTINUE;
		}

		public int visit(IASTEnumerator enumerator) {
			System.out.println("Visiting enumerator: "+enumerator.getRawSignature());
			return PROCESS_CONTINUE;
		}
		
		public int visit( IASTProblem problem ){
			System.out.println("Visiting problem: "+problem.getRawSignature());
			return PROCESS_CONTINUE;
		}
		
		/**
		 * @since 5.3
		 */
		public int visit(ICPPASTBaseSpecifier baseSpecifier) {
			System.out.println("Visiting baseSpecifier: "+baseSpecifier.getRawSignature());
			return PROCESS_CONTINUE;
		}

		/**
		 * @since 5.3
		 */
		public int visit(ICPPASTNamespaceDefinition namespaceDefinition) {
			System.out.println("Visiting namespaceDefinition: "+namespaceDefinition.getName().toString());
			return PROCESS_CONTINUE;
		}

		/**
		 * @since 5.3
		 */
		public int visit(ICPPASTTemplateParameter templateParameter) {
			System.out.println("Visiting templateParameter: "+templateParameter.getRawSignature());
			return PROCESS_CONTINUE;
		}

		/**
		 * @since 5.3
		 */
		public int visit(ICPPASTCapture capture) {
			System.out.println("Visiting capture: "+capture.getRawSignature());
			return PROCESS_CONTINUE;
		}

		/**
		 * @since 5.3
		 */
		public int visit(ICASTDesignator designator) {
			System.out.println("Visiting designator: "+designator.getRawSignature());
			return PROCESS_CONTINUE;
		}
//	public int visit(ICElement element) 
//	{
//		boolean visitChildren = true;
//		System.out.println("Visiting: " +element.getElementName());
//		return PROCESS_CONTINUE;
//	}
}


class MyElementVisitor implements ICElementVisitor
{
	public MyElementVisitor()
	{

	}

	
    public boolean visit(ICElement element) throws CoreException
    {
		boolean visitChildren = true;
		System.out.println("Visiting: " + element.getElementName());
		return visitChildren;
    }

}