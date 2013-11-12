package org.trentino.trengen.cpp.parser.eclipse;

import java.util.Collections;
import java.util.Deque;
import java.util.LinkedList;

import org.eclipse.cdt.core.dom.ast.ASTVisitor;
import org.eclipse.cdt.core.dom.ast.IASTASMDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTArrayModifier;
import org.eclipse.cdt.core.dom.ast.IASTComment;
import org.eclipse.cdt.core.dom.ast.IASTDeclSpecifier;
import org.eclipse.cdt.core.dom.ast.IASTDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTDeclarator;
import org.eclipse.cdt.core.dom.ast.IASTEnumerationSpecifier.IASTEnumerator;
import org.eclipse.cdt.core.dom.ast.IASTExpression;
import org.eclipse.cdt.core.dom.ast.IASTFunctionDeclarator;
import org.eclipse.cdt.core.dom.ast.IASTFunctionDefinition;
import org.eclipse.cdt.core.dom.ast.IASTInitializer;
import org.eclipse.cdt.core.dom.ast.IASTName;
import org.eclipse.cdt.core.dom.ast.IASTNamedTypeSpecifier;
import org.eclipse.cdt.core.dom.ast.IASTNode;
import org.eclipse.cdt.core.dom.ast.IASTNodeLocation;
import org.eclipse.cdt.core.dom.ast.IASTParameterDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTPointerOperator;
import org.eclipse.cdt.core.dom.ast.IASTProblem;
import org.eclipse.cdt.core.dom.ast.IASTSimpleDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTStatement;
import org.eclipse.cdt.core.dom.ast.IASTTranslationUnit;
import org.eclipse.cdt.core.dom.ast.IASTTypeId;
import org.eclipse.cdt.core.dom.ast.IBinding;
import org.eclipse.cdt.core.dom.ast.c.ICASTDesignator;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTCapture;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTCompositeTypeSpecifier;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTNamespaceDefinition;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTQualifiedName;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTTemplateParameter;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTVisibilityLabel;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTCompositeTypeSpecifier.ICPPASTBaseSpecifier;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPBinding;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPClassType;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPMethod;
import org.eclipse.cdt.internal.core.dom.parser.ASTAmbiguousNode;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTCompositeTypeSpecifier;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTFunctionDeclarator;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTFunctionDefinition;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTName;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTNamedTypeSpecifier;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTNamespaceDefinition;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTSimpleDeclSpecifier;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTSimpleDeclaration;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPMethod;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPParameter;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPQualifierType;
import org.trentino.trengen.cpp.model.ClassMethod;
import org.trentino.trengen.cpp.model.ClassMethodArgument;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.cpp.model.HeaderFile;
import org.eclipse.cdt.core.dom.ast.ASTTypeUtil;

public class EclipseASTVisitor extends ASTVisitor {
	// utily used to get fully qualified types out of bindings
	ASTTypeUtil	                astUtil	                   = new ASTTypeUtil();
	private HeaderFile	        headerFile	               = null;

	// used to keep the current visibility label
	private String	            currentVisibility	       = "";
	private String	            currentNamespace	       = "";
	private boolean	            namespaceDefEnd	           = false;

	private ClassModel	        currentClassModel	       = null;
	private ClassMethod	        currentClassMethod	       = null;
	private ClassMethodArgument	currentClassMethodArgument	= null;
	private int enclosingClassDeep =-1;
	private Deque<String> leaveFlagDecleratorClassQueue = new LinkedList<String>();

	enum VISITOR_STATE {
		ANY, INCLASS, INMETHOD, INPARAMETER;
	}

	VISITOR_STATE	visitorState	              = VISITOR_STATE.ANY;

	//private String	leaveFlagDecleratorClass	  = null;
	private String	leaveFlagDeclerationFunction	= null;	       // to mark the end of method
	private String	leaveFlagParameterDeclaration	= null;

	public EclipseASTVisitor (HeaderFile headerFile) {
		this.headerFile = headerFile;

		this.shouldVisitStatements = false;
		this.shouldVisitDeclarations = false;
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
		this.shouldVisitExpressions = false;
		this.shouldVisitImplicitNameAlternates = true;
		this.shouldVisitImplicitNames = true;
		this.shouldVisitInitializers = true;
		this.shouldVisitNames = true;
		this.shouldVisitNamespaces = false;
		this.shouldVisitParameterDeclarations = true;
		this.shouldVisitPointerOperators = true;
		this.shouldVisitProblems = true;
		this.shouldVisitStatements = false;
		this.shouldVisitTemplateParameters = false;
		this.shouldVisitTranslationUnit = false;
		this.shouldVisitTypeIds = true;
	}

	// namespace definition is hit
	public int visit(ICPPASTNamespaceDefinition stmt) {
		// System.out.println("Visiting ICPPASTNamespaceDefinition: " + stmt.getRawSignature());
		if(namespaceDefEnd)
		{
			currentNamespace = "";
			namespaceDefEnd = false;
		}
		if(currentNamespace.equals(""))
		{
			currentNamespace = ((CPPASTNamespaceDefinition) stmt).getName().toString();
		}
		else
		{
			currentNamespace = currentNamespace + "::" + ((CPPASTNamespaceDefinition) stmt).getName().toString();
		}
		return PROCESS_CONTINUE;
	}

	// This function swicthes the state to INPARAMETER if the visitor is already in the INMETHOD state
	// To be able to recognize the the end of all parameter related nodes a leaveFlag is set to be
	// catched at the leave of IASTParameterDeclaration
	public int visit(IASTParameterDeclaration parameterDeclaration) {
		if(visitorState == VISITOR_STATE.INMETHOD)
		{
			// System.out.println("Visiting IASTParameterDeclaration: " + parameterDeclaration.getRawSignature());
			// System.out.println("New param");
			visitorState = VISITOR_STATE.INPARAMETER;
			currentClassMethodArgument = new ClassMethodArgument("", "");
			IASTDeclSpecifier declSpecifier = parameterDeclaration.getDeclSpecifier();

			String parameterType = declSpecifier.toString();
			leaveFlagParameterDeclaration = parameterDeclaration.getRawSignature();
			currentClassMethodArgument.setType(parameterType);

		}
		return PROCESS_CONTINUE;
	}

	// This function is for managing the return and parameter types of functions depending on the current state
	public int visit(IASTPointerOperator ptrOperator) {
		// System.out.println("Visiting IASTPointerOperator: " + ptrOperator.getRawSignature());
		// managing the pointers is required both for the parameter types and for the return types of the methods
		// but for methods it came more handy to handle it in the checkforMethod method.
		// To implement it similarly for the parameters we need to get the child declarator of the parameterdeclarator in the visit of
		// parameter declerator
		// This way it is easier
		switch (visitorState)
		{
			case INPARAMETER:
			{
				String parameterType = currentClassMethodArgument.getType() + ptrOperator.getRawSignature().trim();
				currentClassMethodArgument.setType(parameterType);
				// System.out.println(parameterType);
			}
		}
		return PROCESS_CONTINUE;
	}

	// This function is to capture the base class if the visitor is already in the INCLASS state
	public int visit(ICPPASTBaseSpecifier baseSpecifier) {
		// System.out.println("Visiting ICPPASTBaseSpecifier: " + baseSpecifier.getRawSignature());
		if(visitorState == VISITOR_STATE.INCLASS)
		{
			currentClassModel.getBaseClasses().add(getBaseClassQualifiedName(baseSpecifier));
		}
		return PROCESS_CONTINUE;
	}

	private String getBaseClassQualifiedName(ICPPASTBaseSpecifier baseSpecifier) {
		IASTName name = baseSpecifier.getName();
		if(name instanceof ICPPASTQualifiedName){
			 return name.toString();
		}
		//The name is not qualified, then the namespace is the namespace of the current class
		String res =currentNamespace!=null&&currentNamespace.length()>0?currentNamespace+"::":"";
	    return res+name.toString();
    }

	// In this function if we try to capture the current visibility label
	public int visit(IASTDeclaration decl) {
		// System.out.println("Visiting IASTDeclaration: " + decl.getRawSignature());
		if(decl instanceof ICPPASTVisibilityLabel)
		{
			String visibility = decl.getRawSignature();
			int lenOfVisibility = visibility.length();
			currentVisibility = visibility.substring(0, lenOfVisibility - 1);
		}
		return PROCESS_CONTINUE;
	}

	// In this function depending on the binding name we check out if the name belongs to a class,
	// function or parameter declaration.
	// Checker methods determine if the name belongs to a declaration of interest
	// based on the parent attribute of the name and the current state
	public int visit(IASTName name) {
		// System.out.println("Visiting IASTName: " + name.getRawSignature());
		IBinding bind = name.resolveBinding();
		
		if(bind instanceof ICPPClassType)
		{
			CheckForClassModel(name);
		}
		if(enclosingClassDeep <=0)
		{
			if(bind instanceof ICPPMethod && !((ICPPMethod) bind).isDestructor())
			{
				CheckForMethod(name);

			}
			else if(bind instanceof CPPParameter)
			{
				CheckForParameter(name);
			}
		}
	

		return PROCESS_CONTINUE;
	}

	// checks and if valid works on the currentParameter
	private void CheckForParameter(IASTName name) {
		if(visitorState != VISITOR_STATE.INPARAMETER)
		{
			return;
		}
		String parameterName = name.toString();
		currentClassMethodArgument.setName(parameterName);
		// String parameterType = null;
		// IBinding bind = name.resolveBinding();
		//
		// if(bind instanceof ICPPBinding)
		// {
		// ICPPBinding cppBinding = (ICPPBinding) bind;
		// if(cppBinding != null)
		// {
		// parameterName = ASTTypeUtil.getQualifiedName((ICPPBinding) bind);
		// }
		// }
		// int lastIndexOfClassName = parameterType.lastIndexOf("::" + parameterName);
		// if(lastIndexOfClassName == -1)
		// {
		// parameterType = "";
		// }
		// else
		// {
		// parameterType = parameterType.substring(0, lastIndexOfClassName);
		// }
		// if(name.getParent() instanceof CPPASTDeclarator)
		// {
		// CPPASTDeclarator parentOfParameterName = (CPPASTDeclarator)name.getParent();
		//
		// if(parentOfParameterName.getParent() instanceof IASTParameterDeclaration)
		// {
		// IASTParameterDeclaration parentFunctionDecleratorOfFunction = (IASTParameterDeclaration)parentOfParameterName.getParent();
		// leaveFlagParameterDeclaration = parentFunctionDecleratorOfFunction.getRawSignature();
		// String parameterType2 = parentFunctionDecleratorOfFunction.getDeclSpecifier().toString();
		// }
		// }

		//
		// for(ICPPASTParameterDeclaration parameterDecleration : parametersOfFunction)
		// {
		// if(parameterDecleration.getDeclarator().getName().toString() == name.toString())
		// {
		// argument = new ClassMethodArgument(parameterName, nameSpaceOfParameter);
		// try
		// {
		// String typeOfParam = parameterDecleration.getSyntax().toString();
		// }
		// catch (ExpansionOverlapsBoundaryException e){
		// e.printStackTrace();
		// }
		// //argument = new ClassMethodArgument(name.toString(), typeOfParam);
		// }
		// }
		// }
	}
	
	private String handleReturnType (String returnType, boolean isConst, CPPASTFunctionDeclarator parentFunctionDecleratorOfFunction)
	{
		if(isConst)
		{
			returnType = "const " + returnType;
		}
		for (IASTPointerOperator pointerOperator : parentFunctionDecleratorOfFunction.getPointerOperators())
		{
			returnType = returnType + pointerOperator.getRawSignature().trim();
		}
		return returnType;
	}
	// This function is to populate the classModule with the methods
	private void CheckForMethod(IASTName name) {
		String functionName = name.toString();
		String returnType = null;

		if(name.getParent() instanceof CPPASTFunctionDeclarator)
		{
			CPPASTFunctionDeclarator parentFunctionDecleratorOfFunction = (CPPASTFunctionDeclarator) name.getParent();

			leaveFlagDeclerationFunction = parentFunctionDecleratorOfFunction.getParent().getRawSignature();
			// leaveFlagDeclerationFunction = parentFunctionDecleratorOfFunction.getRawSignature();
			boolean isPureVirtual = parentFunctionDecleratorOfFunction.isPureVirtual();
			IASTDeclSpecifier  returnTypeSpecifier = getReturnTypeSpecifyer(parentFunctionDecleratorOfFunction);
			boolean isConst = returnTypeSpecifier.isConst();
			returnType = getReturnType(returnTypeSpecifier);
			returnType = handleReturnType(returnType, isConst, parentFunctionDecleratorOfFunction);
			if(visitorState == VISITOR_STATE.INCLASS)
			{
				visitorState = VISITOR_STATE.INMETHOD;
				currentClassMethod = new ClassMethod("", "");
				currentClassMethod.setReturnType(returnType);
				currentClassMethod.setPureVirtual(isPureVirtual);
				currentClassMethod.setName(functionName);
				currentClassMethod.setAccess(currentVisibility);
				//System.out.println("Begin of function from IASTName: " + name.getRawSignature());
			}
		}
	}

	/**
     * @param returnTypeSpecifier
     * @return
     */
    private String getReturnType(IASTDeclSpecifier returnTypeSpecifier) {
	   if(returnTypeSpecifier instanceof IASTNamedTypeSpecifier ){
		   return ((IASTNamedTypeSpecifier)returnTypeSpecifier).getName().toString();
	   }
	   return returnTypeSpecifier.toString();
    }

	/**
     * @param parentFunctionDecleratorOfFunction
     * @return
     */
    private IASTDeclSpecifier getReturnTypeSpecifyer(CPPASTFunctionDeclarator parentFunctionDecleratorOfFunction) {
    	 IASTNode parent = parentFunctionDecleratorOfFunction.getParent();
    	 if(parent instanceof IASTSimpleDeclaration){
    		 return ((IASTSimpleDeclaration)parent).getDeclSpecifier();
    	 }
    	 if(parent instanceof IASTFunctionDefinition){
    		 return ((IASTFunctionDefinition)parent).getDeclSpecifier();
    	 }
	     throw new IllegalStateException("Cannot parse source code. please contact support");
    }

	private void CheckForClassModel(IASTName name) {
		String nameSpaceOfClass = null;
		String className = name.toString();

		IBinding bind = name.resolveBinding();

		if(bind instanceof ICPPBinding)
		{
			ICPPBinding cppBinding = (ICPPBinding) bind;
			if(cppBinding != null)
			{
				nameSpaceOfClass = ASTTypeUtil.getQualifiedName((ICPPBinding) bind);
			}
		}

		int lastIndexOfClassName = -1;
		if(nameSpaceOfClass != null)
		{
			lastIndexOfClassName = nameSpaceOfClass.lastIndexOf("::" + className);
		}
		if(lastIndexOfClassName == -1)
		{
			nameSpaceOfClass = "";
		}
		else
		{
			nameSpaceOfClass = nameSpaceOfClass.substring(0, lastIndexOfClassName);
		}

		if(name.getParent() instanceof CPPASTCompositeTypeSpecifier)
		{
			CPPASTCompositeTypeSpecifier parentCompositeTypeSpecifierOfClass = (CPPASTCompositeTypeSpecifier) name.getParent();

			// ICPPASTBaseSpecifier[] bases = parentCompositeTypeSpecifierOfClass.getBaseSpecifiers();
			// List<String> baseClassesOfClassModel = currentClassModel.getBaseClasses();
			// for (ICPPASTBaseSpecifier base : bases)
			// {
			// baseClassesOfClassModel.add(base.getName().toString());
			// }
			//
			// headerFile.getClasses().add(currentClassModel);
			enclosingClassDeep++;
			leaveFlagDecleratorClassQueue.addFirst(parentCompositeTypeSpecifierOfClass.getRawSignature());
			if(visitorState == VISITOR_STATE.ANY && enclosingClassDeep <=0)
			{
				visitorState = VISITOR_STATE.INCLASS;
				currentClassModel = new ClassModel();
				currentClassModel.setClassName(className);
				currentClassModel.setNamespace(nameSpaceOfClass);
				// System.out.println("Begin of class from IASTName: " + name.getRawSignature());
			}
		}
	}

	// ====================================================================================
	// Visitors below are not used actively but shouldn't be deleted also
	// since we can need them any time to capture the overall structure of AST tree
	// ====================================================================================
	public int visit(IASTStatement stmt) { // lots more
		                                   // System.out.println("Visiting stmt: " + stmt.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(ICPPASTVisibilityLabel decl) {
		// System.out.println("Visiting visibilityLabel: " + decl.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(IASTFunctionDefinition decl) {
		// System.out.println("Visiting funcDef: " + decl.getRawSignature());
		// IASTFunctionDeclarator f = decl.getDeclarator();
		// visit(f);
		return PROCESS_CONTINUE;
	}

	public int visit(IASTFunctionDeclarator decl) {
		// System.out.println("Visiting funcDecl: " + decl.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(IASTASMDeclaration decl) {
		// System.out.println("Visiting ssmDecl: " + decl.getRawSignature());
		return PROCESS_CONTINUE;
	}

	// implements IASTSimpleDeclaration
	public int visit(IASTSimpleDeclaration decl) {
		// System.out.println("Visiting simpleDecl: "+decl.getRawSignature());
		// IASTDeclarator[] decls = decl.getDeclarators();
		// for (IASTDeclarator d : decls)
		// visit(d);
		return PROCESS_CONTINUE;
	}

	// visit methods
	public int visit(IASTTranslationUnit tu) {
		// System.out.println("Visiting IASTTranslationUnit: "+tu.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(IASTInitializer initializer) {
		// System.out.println("Visiting IASTInitializer: " + initializer.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(IASTDeclarator declarator) {
		// System.out.println("Visiting IASTDeclarator: " + declarator.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(IASTDeclSpecifier declSpec) {
		// System.out.println("Visiting IASTDeclSpecifier: " + declSpec.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(IASTArrayModifier arrayModifier) {
		// System.out.println("Visiting IASTArrayModifier: " + arrayModifier.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(IASTExpression expression) {
		// System.out.println("Visiting IASTExpression: " + expression.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(IASTTypeId typeId) {
		// System.out.println("Visiting IASTTypeId: " + typeId.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(IASTEnumerator enumerator) {
		// System.out.println("Visiting IASTEnumerator: " + enumerator.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(IASTProblem problem) {
		// System.out.println("Visiting IASTProblem: " + problem.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(ICPPASTTemplateParameter templateParameter) {
		// System.out.println("Visiting ICPPASTTemplateParameter: " + templateParameter.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(ICPPASTCapture capture) {
		// System.out.println("Visiting ICPPASTCapture: " + capture.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int visit(ICASTDesignator designator) {
		// System.out.println("Visiting ICASTDesignator: " + designator.getRawSignature());
		return PROCESS_CONTINUE;
	}

	// ====================================================================================
	// LEAVEs
	// ====================================================================================
	public int leave(IASTDeclaration declaration) {
		// System.out.println("Leave IASTDeclaration: " +declaration.getRawSignature());
		// end of a new function declaration
		if(visitorState == VISITOR_STATE.INMETHOD && leaveFlagDeclerationFunction != null
		        && leaveFlagDeclerationFunction.equals(declaration.getRawSignature()))
		{
			// System.out.println("End of method: " + currentClassMethod.getName() + " with the following");
			// System.out.println("Leave IASTDeclaration: " + declaration.getRawSignature());
			currentClassModel.getMethods().add(currentClassMethod);
			currentClassMethod = null;
			visitorState = VISITOR_STATE.INCLASS;
		}
		return PROCESS_CONTINUE;
	}

	public int leave(IASTParameterDeclaration parameterDeclaration) {
		// System.out.println("Leave IASTParameterDeclaration: " +parameterDeclaration.getRawSignature());
		if(visitorState == VISITOR_STATE.INPARAMETER && leaveFlagParameterDeclaration != null
		        && leaveFlagParameterDeclaration.equals(parameterDeclaration.getRawSignature()))
		{
			// System.out.println("End of arg: " + currentClassMethodArgument.getName());
			currentClassMethod.getArguments().add(currentClassMethodArgument);
			currentClassMethodArgument = null;
			visitorState = VISITOR_STATE.INMETHOD;
		}
		return PROCESS_CONTINUE;
	}

	public int leave(IASTDeclSpecifier declSpec) {
		// System.out.println("Leave IASTDeclSpecifier: " +declSpec.getRawSignature());
		// end of current classModel
		if(leaveFlagDecleratorClassQueue.isEmpty()){
			return PROCESS_CONTINUE;
		}
		String val = leaveFlagDecleratorClassQueue.getFirst();
		if(val != null && val.equals(declSpec.getRawSignature()))
		{
			// System.out.println("End of class: " + currentClassModel.getClazzName() + "with the following");
			// System.out.println("Leave IASTDeclSpecifier: " + declSpec.getRawSignature());
			enclosingClassDeep--;
			leaveFlagDecleratorClassQueue.pollFirst();
			if(enclosingClassDeep<=0 && visitorState == VISITOR_STATE.INCLASS){
				headerFile.getClasses().add(currentClassModel);
				currentClassModel = null;
				visitorState = VISITOR_STATE.ANY;
			}
			
		}
		return PROCESS_CONTINUE;
	}

	// ====================================================================================
	// Leaves below are not used actively but shouldn't be deleted also
	// since we can need them any time to capture the overall structure of AST tree
	// ====================================================================================
	// leave methods
	public int leave(IASTTranslationUnit tu) {
		// System.out.println("Leave IASTTranslationUnit: " );
		return PROCESS_CONTINUE;
	}

	public int leave(IASTName name) {
		// System.out.println("Leave IASTName: " +name.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int leave(IASTInitializer initializer) {
		return PROCESS_CONTINUE;
	}

	public int leave(IASTDeclarator declarator) {
		// System.out.println("Leave IASTDeclarator: " +declarator.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int leave(IASTArrayModifier arrayModifier) {
		return PROCESS_CONTINUE;
	}

	public int leave(IASTPointerOperator ptrOperator) {
		// System.out.println("Leave IASTPointerOperator: " +ptrOperator.getRawSignature());
		return PROCESS_CONTINUE;
	}

	public int leave(IASTExpression expression) {
		return PROCESS_CONTINUE;
	}

	public int leave(IASTStatement statement) {
		return PROCESS_CONTINUE;
	}

	public int leave(IASTTypeId typeId) {
		return PROCESS_CONTINUE;
	}

	public int leave(IASTEnumerator enumerator) {
		return PROCESS_CONTINUE;
	}

	public int leave(IASTProblem problem) {
		return PROCESS_CONTINUE;
	}

	public int leave(ICPPASTBaseSpecifier baseSpecifier) {
		return PROCESS_CONTINUE;
	}

	public int leave(ICPPASTNamespaceDefinition namespaceDefinition) {
		// System.out.println("Leave ICPPASTNamespaceDefinition: " +namespaceDefinition.getRawSignature());
		namespaceDefEnd = true;
		return PROCESS_CONTINUE;
	}

	public int leave(ICPPASTTemplateParameter templateParameter) {
		return PROCESS_CONTINUE;
	}

	public int leave(ICPPASTCapture capture) {
		return PROCESS_CONTINUE;
	}

	public int leave(ICASTDesignator designator) {
		return PROCESS_CONTINUE;
	}

	/**
	 * @deprecated use {@link IASTTranslationUnit#getComments()}, instead.
	 */
	@Deprecated
	public int visit(IASTComment comment) {
		return PROCESS_CONTINUE;
	}

	/**
	 * @deprecated use {@link IASTTranslationUnit#getComments()}, instead.
	 */
	@Deprecated
	public int leave(IASTComment comment) {
		return PROCESS_CONTINUE;
	}

	/**
	 * For internal use, only. When {@link ASTVisitor#shouldVisitAmbiguousNodes} is set to true, the visitor will be called for ambiguous nodes.
	 * However,
	 * the children of an ambiguous will not be traversed.
	 * @nooverride This method is not intended to be re-implemented or extended
	 *             by clients.
	 * @noreference This method is not intended to be referenced by clients.
	 */
	public int visit(ASTAmbiguousNode astAmbiguousNode) {
		return PROCESS_CONTINUE;
	}
}
