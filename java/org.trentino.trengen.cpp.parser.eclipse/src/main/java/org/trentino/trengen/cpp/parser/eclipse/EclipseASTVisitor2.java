package org.trentino.trengen.cpp.parser.eclipse;

import java.util.List;

import org.eclipse.cdt.core.dom.IName;
import org.eclipse.cdt.core.dom.ast.ASTTypeUtil;
import org.eclipse.cdt.core.dom.ast.ASTVisitor;
import org.eclipse.cdt.core.dom.ast.IASTDeclSpecifier;
import org.eclipse.cdt.core.dom.ast.IASTDeclarator;
import org.eclipse.cdt.core.dom.ast.IASTFunctionDefinition;
import org.eclipse.cdt.core.dom.ast.IASTName;
import org.eclipse.cdt.core.dom.ast.IASTNode;
import org.eclipse.cdt.core.dom.ast.IASTPointerOperator;
import org.eclipse.cdt.core.dom.ast.IASTSimpleDeclaration;
import org.eclipse.cdt.core.dom.ast.IASTTranslationUnit;
import org.eclipse.cdt.core.dom.ast.IBinding;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTCompositeTypeSpecifier;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTFunctionDeclarator;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPASTParameterDeclaration;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPBase;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPBinding;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPClassType;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPConstructor;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPMember;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPMethod;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPParameter;
import org.eclipse.cdt.core.dom.ast.cpp.ICPPSpecialization;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTCompositeTypeSpecifier;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTDeclarator;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPASTQualifiedName;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPMethod;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPMethodTemplate;
import org.eclipse.cdt.internal.core.dom.parser.cpp.CPPParameter;
import org.trentino.trengen.cpp.model.ClassMethod;
import org.trentino.trengen.cpp.model.ClassMethodArgument;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.cpp.model.HeaderFile;

public class EclipseASTVisitor2 extends ASTVisitor {
	// utily used to get fully qualified types out of bindings
	ASTTypeUtil	       astUtil	   = new ASTTypeUtil();
	private HeaderFile	headerFile	= null;

	public EclipseASTVisitor2 (HeaderFile headerFile) {
		this.headerFile = headerFile;
		this.shouldVisitDeclSpecifiers = true;
		this.shouldVisitTranslationUnit = true;
	}

	@Override
	public int visit(IASTDeclSpecifier declSpec) {
		if(declSpec instanceof CPPASTCompositeTypeSpecifier)
		{
			// types.add((CPPASTCompositeTypeSpecifier) declSpec);
			ClassModel model = createClassModel((CPPASTCompositeTypeSpecifier) declSpec);
			if(model != null)
				headerFile.getClasses().add(model);
		}
		return PROCESS_SKIP;
	}

	/**
	 * @param declSpec
	 * @return
	 */
	private ClassModel createClassModel(ICPPASTCompositeTypeSpecifier declSpec) {
		IASTName name = declSpec.getName();
		String nameSpaceOfClass = null;
		String className = name.toString();

		IBinding bind = name.resolveBinding();
		if(!(bind instanceof ICPPClassType))
		{
			return null;
		}

		ICPPClassType cppBinding = (ICPPClassType) bind;
		if(cppBinding != null)
		{
			nameSpaceOfClass = ASTTypeUtil.getQualifiedName((ICPPBinding) bind);
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
		ClassModel currentClassModel = new ClassModel();
		currentClassModel.setClassName(className);
		currentClassModel.setNamespace(nameSpaceOfClass);
		createMethods(currentClassModel, cppBinding);
		ICPPBase[] bases = cppBinding.getBases();
		if(bases == null || bases.length == 0)
		{
			return currentClassModel;
		}
		for (ICPPBase base : bases)
		{
			if(base == null)
			{
				continue;
			}
			String bclassName = getBaseClassName(base);
			currentClassModel.getBaseClasses().add(bclassName);
		}
		return currentClassModel;
	}

	private String getBaseClassName(ICPPBase base) {
		IName name = base.getBaseClassSpecifierName();
		if(name != null && name instanceof CPPASTQualifiedName)
		{
			return name.toString();
		}
		return ASTTypeUtil.getQualifiedName((ICPPBinding) base.getBaseClass());
	}

	/**
	 * @param currentClassModel
	 * @param cppBinding
	 */
	private void createMethods(ClassModel currentClassModel, ICPPClassType cppBinding) {
		ICPPMethod[] methods = cppBinding.getAllDeclaredMethods();
		if(methods == null)
		{
			return;
		}
		for (ICPPMethod method : methods)
		{
			if(method == null || (method instanceof ICPPConstructor) || method.isDestructor())
			{
				continue;
			}
			if(method instanceof ICPPSpecialization)
			{
				// Specialization are not handled by Trentino.
				continue;
			}
			createMethod(currentClassModel, method);
		}

	}

	/**
	 * @param currentClassModel
	 * @param method
	 */
	private void createMethod(ClassModel currentClassModel, ICPPMethod method) {

		String name = method.getName();
		if(currentClassModel.getClassName().equals(name))
		{
			// The parser sometimes take a constructor as a function.
			// function with the same name as the class are supposed to be constructor
			return;
		}

		String returnType = getReturnType(method);

		ClassMethod cm = new ClassMethod(name, returnType);
		cm.setAccess(getAccess(method.getVisibility()));
		cm.setPureVirtual(method.isPureVirtual());

		if(method.getParameters() != null)
		{
			for (ICPPParameter param : method.getParameters())
			{
				createParam(cm, param);
			}
		}
		
		List<ClassMethod> methods = currentClassModel.getMethods();
		if(!methods.contains(cm))
		{
			methods.add(cm);
		}
	}

	/**
	 * @param method
	 * @return
	 */
	private String getReturnType(ICPPMethod method) {
		IASTNode delc = null;
		if(method instanceof CPPMethod)
		{
			CPPMethod meth = (CPPMethod) method;
			delc = meth.getDefinition();
			if(delc == null)
			{
				IASTDeclarator[] fdeclarations = meth.getDeclarations();
				for (IASTDeclarator d : fdeclarations)
				{
					if(d instanceof ICPPASTFunctionDeclarator)
					{
						delc = d;
						break;
					}
				}
			}
		}

		if(method instanceof CPPMethodTemplate)
		{
			CPPMethodTemplate meth = (CPPMethodTemplate) method;
			delc = meth.getDefinition();
			if(delc != null && !(delc instanceof ICPPASTFunctionDeclarator) && !(delc instanceof ICPPASTCompositeTypeSpecifier))
			{
				delc = delc.getParent();
			}
			if(delc == null)
			{
				IASTNode[] fdeclarations = meth.getDeclarations();
				if(fdeclarations.length > 0)
				{
					delc = fdeclarations[0].getParent();
				}
			}
		}

		if(delc instanceof ICPPASTFunctionDeclarator)
		{
			ICPPASTFunctionDeclarator parentFunctionDecleratorOfFunction = (ICPPASTFunctionDeclarator) delc;
			IASTDeclSpecifier returnTypeSpecifier = getReturnTypeSpecifyer(parentFunctionDecleratorOfFunction);
			boolean isConst = returnTypeSpecifier.isConst();
			String retType = getReturnType(returnTypeSpecifier);
			retType = handleReturnType(retType, isConst, parentFunctionDecleratorOfFunction);
			return retType;
		}

		// this should not happens
		throw new IllegalStateException("Cannot recognize return type for method " + method.getName());
	}

	/**
	 * @param returnTypeSpecifier
	 * @return
	 */
	private String getReturnType(IASTDeclSpecifier returnTypeSpecifier) {
		/*
		 * if(returnTypeSpecifier instanceof IASTNamedTypeSpecifier)
		 * {
		 * return ((IASTNamedTypeSpecifier) returnTypeSpecifier).getName().toString();
		 * }
		 */
		return returnTypeSpecifier.toString();
	}

	/**
	 * @param parentFunctionDecleratorOfFunction
	 * @return
	 */
	private IASTDeclSpecifier getReturnTypeSpecifyer(ICPPASTFunctionDeclarator parentFunctionDecleratorOfFunction) {
		IASTNode parent = parentFunctionDecleratorOfFunction.getParent();
		if(parent instanceof IASTSimpleDeclaration)
		{
			return ((IASTSimpleDeclaration) parent).getDeclSpecifier();
		}
		if(parent instanceof IASTFunctionDefinition)
		{
			return ((IASTFunctionDefinition) parent).getDeclSpecifier();
		}
		throw new IllegalStateException("Cannot parse source code. please contact support");
	}

	private String handleReturnType(String returnType, boolean isConst, ICPPASTFunctionDeclarator parentFunctionDecleratorOfFunction) {
		/*
		 * if(isConst)
		 * {
		 * returnType = "const " + returnType;
		 * }
		 */
		for (IASTPointerOperator pointerOperator : parentFunctionDecleratorOfFunction.getPointerOperators())
		{
			returnType = returnType + pointerOperator.getRawSignature().trim();
		}
		return returnType;
	}

	/**
	 * @param visibility
	 * @return
	 */
	private String getAccess(int visibility) {
		if(visibility == ICPPMember.v_private)
		{
			return "private";
		}
		if(visibility == ICPPMember.v_protected)
		{
			return "protected";
		}
		return "public";
	}

	/**
	 * @param cm
	 * @param param
	 */
	private void createParam(ClassMethod cm, ICPPParameter param) {
		if(param == null)
		{
			return;
		}

		String name = param.getName();
		String type = null;
		String refName = "";
		// type not resolved, use parameter declaration
		IASTNode[] fDeclarations = ((CPPParameter) param).getDeclarations();
		if(fDeclarations != null && fDeclarations.length > 0)
		{
			IASTNode parent = fDeclarations[0].getParent();
			while (parent != null)
			{
				if(parent instanceof CPPASTDeclarator)
				{
					IASTPointerOperator[] pointers = ((CPPASTDeclarator) parent).getPointerOperators();
					for (IASTPointerOperator pointer : pointers)
					{
						refName += pointer.getRawSignature().trim();
					}
				}
				if(parent instanceof ICPPASTParameterDeclaration)
				{
					break;
				}
				parent = parent.getParent();
			}
			ICPPASTParameterDeclaration val = (ICPPASTParameterDeclaration) parent;
			type = val.getDeclSpecifier().toString();
		}

		ClassMethodArgument arg = new ClassMethodArgument(name, type + refName);
		cm.getArguments().add(arg);
	}

	TranslationUnitCollector	translationUnitCollector;

	public void settranslationUnitCollector(TranslationUnitCollector v) {
		translationUnitCollector = v;
	}

	// visit methods
	public int visit(IASTTranslationUnit tu) {
		if(translationUnitCollector != null)
		{
			translationUnitCollector.onTranslationUnitFound(tu);
		}
		return PROCESS_CONTINUE;
	}
}