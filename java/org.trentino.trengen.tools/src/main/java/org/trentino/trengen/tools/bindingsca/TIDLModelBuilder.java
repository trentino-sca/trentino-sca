package org.trentino.trengen.tools.bindingsca;

import static javax.lang.model.SourceVersion.RELEASE_6;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.annotation.processing.AbstractProcessor;
import javax.annotation.processing.RoundEnvironment;
import javax.annotation.processing.SupportedAnnotationTypes;
import javax.annotation.processing.SupportedSourceVersion;
import javax.lang.model.element.Element;
import javax.lang.model.element.ElementKind;
import javax.lang.model.element.ExecutableElement;
import javax.lang.model.element.Name;
import javax.lang.model.element.TypeElement;
import javax.lang.model.element.VariableElement;
import javax.lang.model.type.DeclaredType;
import javax.lang.model.type.TypeKind;
import javax.lang.model.type.TypeMirror;
import javax.tools.Diagnostic.Kind;

import org.apache.log4j.Logger;
import org.trentino.tidl.InOut;
import org.trentino.tidl.Out;
import org.trentino.tidl.TException;
import org.trentino.tidl.TInterface;
import org.trentino.tidl.TStruct;
import org.trentino.tidl.TType;

@SupportedSourceVersion(RELEASE_6)
@SupportedAnnotationTypes("*")
public class TIDLModelBuilder extends AbstractProcessor {
	protected static final Logger	 logger	                                     = Logger.getLogger(TIDLModelBuilder.class);

	private static final Boolean	 ALLOW_OTHER_PROCESSORS_TO_CLAIM_ANNOTATIONS	= Boolean.FALSE;

	private List<TIDLInterfaceModel>	tidlInterfaceModel	                     = new ArrayList<TIDLInterfaceModel>();
	private Set<TypeElement>	     classesToProcess	                         = new HashSet<TypeElement>();
	private Set<TypeElement>	     exceptionsToProcess	                     = new HashSet<TypeElement>();
	private Set<TypeElement>	     interfacesToProcess	                     = new HashSet<TypeElement>();
	private Map<String, TIDLType>	 classes	                                 = new HashMap<String, TIDLType>();
	private Map<String, TIDLType>	 simpleTypes	                             = new HashMap<String, TIDLType>();

	@Override
	public boolean process(Set<? extends TypeElement> annotations, RoundEnvironment roundEnvironment) {
		if(roundEnvironment.processingOver())
		{
			createTIDLModel();
			return ALLOW_OTHER_PROCESSORS_TO_CLAIM_ANNOTATIONS;

		}

		Set<? extends Element> elements = roundEnvironment.getRootElements();

		for (Element element : elements)
		{
			logger.info("Processing " + element.toString());
			collectModelInfos(element);
		}

		return ALLOW_OTHER_PROCESSORS_TO_CLAIM_ANNOTATIONS;
	}

	private void createTIDLModel() {
		for (TypeElement elem : interfacesToProcess)
		{
			TIDLInterfaceModel interfaceModel = new TIDLInterfaceModel();
			interfaceModel.setName(elem.getSimpleName().toString());
			interfaceModel.setQualifiedName(elem.getQualifiedName().toString());
			interfaceModel.setTypeElement(elem);
			tidlInterfaceModel.add(interfaceModel);
		}
		for (TIDLInterfaceModel model : tidlInterfaceModel)
		{
			TypeElement elem = model.getTypeElement();
			List<? extends Element> fields = elem.getEnclosedElements();
			for (Element field : fields)
			{
				parseClasses(field, model);
			}
			//First sca all classes before scanning methods, so that the order is preserver as much as possible
			for (Element field : fields)
			{
				parseFunctions(field, model);
			}
		}

	}

	/**
	 * @param field2
	 * @param model2
	 */
	private void parseClasses(Element field, TIDLInterfaceModel model) {
		if(field.getKind() != ElementKind.CLASS && field.getKind() != ElementKind.ENUM)
		{
			return;
		}

		TypeElement aType = (TypeElement) field;
		TIDLType t = getTIDLType(aType);
		model.getEnclosedClasses().add(t);
		t.setDirectlyEnclosedinModel(true);
	}

	private void parseFunctions(Element field, TIDLInterfaceModel model) {
		if(field.getKind() != ElementKind.METHOD)
		{
			return;
		}

		ExecutableElement method = (ExecutableElement) field;
		TIDLFunctionModel functionModel = new TIDLFunctionModel();
		functionModel.setTypeElement(method);
		functionModel.setName(method.getSimpleName().toString());
		createArguments(functionModel);
		createException(functionModel);
		int id=0;
		for(TIDLFunctionModel f : model.getFunctions()){
			if(f.getName().equals(functionModel.getName())){
				id++;
			}
		}
		String methodId = functionModel.getName();
		methodId+=(id!=0)?id:"";
		functionModel.setMethodId(methodId);
		if(model.getFunctions().contains(functionModel))
		{
			processingEnv.getMessager().printMessage(Kind.ERROR,
			        "Method overloading not supported.\nMethod:" + functionModel.getName() + "\nIn class " + model.getQualifiedName());
		}
		model.getFunctions().add(functionModel);
	}

	/**
	 * @param functionModel
	 */
	private void createException(TIDLFunctionModel functionModel) {
		ExecutableElement method = functionModel.getTypeElement();
		List<? extends TypeMirror> throwns = method.getThrownTypes();
		for (TypeMirror thrown : throwns)
		{
			TIDLExceptionModel exceptionModel = new TIDLExceptionModel();
			TypeElement thrownType = (TypeElement) ((DeclaredType) thrown).asElement();
			exceptionModel.setTypeElement(thrownType);
			TIDLType type = getTIDLType(thrownType);
			exceptionModel.setName(thrownType.getSimpleName().toString());
			exceptionModel.setType(type);
			functionModel.getExceptions().add(exceptionModel);
		}
	}

	/**
	 * @param functionModel
	 */
	private void createArguments(TIDLFunctionModel functionModel) {
		ExecutableElement method = functionModel.getTypeElement();
		List<? extends VariableElement> params = method.getParameters();
		for (VariableElement param : params)
		{
			TIDLParameterModel parameterModel = new TIDLParameterModel();

			parameterModel.setTypeElement(param);
			parameterModel.setName(param.getSimpleName().toString());
			functionModel.getArguments().add(parameterModel);
			// arguments
			if(param.getAnnotation(Out.class) != null)
			{
				parameterModel.setHasOut(true);
			}
			if(param.getAnnotation(InOut.class) != null)
			{
				parameterModel.setHasInOut(true);
			}
			TypeMirror paramType = param.asType();
			TIDLType typeObj = getParameterType(paramType);
			parameterModel.setType(typeObj);

		}

		// return type
		TypeMirror paramType = method.getReturnType();
		TypeKind kind = paramType.getKind();
		if(kind == TypeKind.VOID)
		{
			functionModel.setReturnType(TIDLType.VOID);
			return;
		}
		TIDLType typeObj = getParameterType(paramType);
		functionModel.setReturnType(typeObj);

	}

	private TIDLType getParameterType(TypeMirror paramType) {
		TypeKind kind = paramType.getKind();
		if(kind == TypeKind.ERROR)
		{
			return TIDLType.NULLVALUE;
		}
		if(kind != TypeKind.DECLARED)
		{
			processingEnv.getMessager().printMessage(Kind.ERROR,
			        "Only Trentino types are supported. The following type is not supported :" + paramType);
			return null;
		}
		DeclaredType declaredType = (DeclaredType) paramType;
		TypeElement theType = (TypeElement) declaredType.asElement();
		TIDLType typeObj = getTIDLType(theType);
		return typeObj;
	}

	/**
	 * @param theType
	 * @return
	 */
	private TIDLType getTIDLType(TypeElement theType) {
		String qname = theType.getQualifiedName().toString();
		if(classes.containsKey(qname))
		{
			return classes.get(qname);
		}
		if(simpleTypes.containsKey(qname))
		{
			return simpleTypes.get(qname);
		}

		TIDLType struct = new TIDLType();
		struct.setQualifiedName(qname);
		struct.setName(theType.getSimpleName().toString());
		struct.setTypeElement(theType);
		Element elem = theType.getEnclosingElement();
		if(elem != null && elem instanceof TypeElement)
		{
			TypeElement parent = (TypeElement) elem;
			String pQName = parent.getQualifiedName().toString();
			boolean isEnclosed = classes.containsKey(pQName);
			isEnclosed |= interfacesToProcess.contains(parent);
			if(isEnclosed)
			{
				struct.setEnclosed(true);
			}

		}
		if(struct.isComplexType())
		{
			classes.put(qname, struct);
			if(theType.getKind() == ElementKind.ENUM)
			{
				createEnumFields(struct);
				struct.setEnumeration(true);
			}
			else
			{
				createStructFields(struct);
			}

		}
		else
		{
			simpleTypes.put(qname, struct);
		}
		return struct;
	}

	/**
	 * @param struct
	 */
	private void createEnumFields(TIDLType struct) {
		if(!struct.isComplexType())
		{
			return;
		}
		TypeElement typeElement = struct.getTypeElement();
		List<? extends Element> fields = typeElement.getEnclosedElements();
		for (Element field : fields)
		{
			if(field.getKind() == ElementKind.CONSTRUCTOR)
			{
				continue;
			}
			if(field.getKind() == ElementKind.METHOD)
			{
				if("values".equals(field.getSimpleName().toString()))
				{
					continue;
				}
				if("valueOf".equals(field.getSimpleName().toString()))
				{
					continue;
				}
			}
			if(field.getKind() != ElementKind.ENUM_CONSTANT)
			{
				Name qualifiedName = typeElement.getQualifiedName();
				Name simpleName = field.getSimpleName();
				String format = "Only enum constants are allowed in TIDL enumeration " + qualifiedName + ". element " + simpleName + ".";
				processingEnv.getMessager().printMessage(Kind.ERROR, format);
				return;
			}
			// we are using a field
			VariableElement param = (VariableElement) field;
			TIDLFieldModel fieldModel = new TIDLFieldModel();
			fieldModel.setTypeElement(param);
			fieldModel.setName(param.getSimpleName().toString());
			struct.getFields().add(fieldModel);
			TypeMirror paramType = param.asType();
			TIDLType typeObj = getParameterType(paramType);
			fieldModel.setType(typeObj);
		}

	}

	/**
	 * @param struct
	 */
	private void createStructFields(TIDLType struct) {
		if(!struct.isComplexType())
		{
			return;
		}
		TypeElement typeElement = struct.getTypeElement();
		List<? extends Element> fields = typeElement.getEnclosedElements();
		for (Element field : fields)
		{
			if(field.getKind() == ElementKind.CONSTRUCTOR)
			{
				continue;
			}
			if(field.getKind() == ElementKind.CLASS || field.getKind() == ElementKind.ENUM)
			{

				TIDLType child = getTIDLType((TypeElement) ((DeclaredType) field.asType()).asElement());
				struct.getEnclosedClasses().add(child);
				child.setEnclosingClass(struct);
				continue;
			}
			if(field.getKind() != ElementKind.FIELD)
			{
				Name qualifiedName = typeElement.getQualifiedName();
				Name simpleName = field.getSimpleName();
				String format = "Only fields are allowed in structure " + qualifiedName + ". element " + simpleName + ".";
				processingEnv.getMessager().printMessage(Kind.ERROR, format);
				return;
			}
			// we are using a field
			VariableElement param = (VariableElement) field;
			TIDLFieldModel fieldModel = new TIDLFieldModel();
			fieldModel.setTypeElement(param);
			fieldModel.setName(param.getSimpleName().toString());
			struct.getFields().add(fieldModel);
			TypeMirror paramType = param.asType();
			TIDLType typeObj = getParameterType(paramType);
			fieldModel.setType(typeObj);
		}
	}

	private void collectModelInfos(Element element) {
		ElementKind kind = element.getKind();
		if(kind.isClass() || kind == ElementKind.INTERFACE)
		{
			TypeElement typeElement = (TypeElement) element;
			boolean ok = (kind == ElementKind.INTERFACE) && isImplementing(typeElement, TInterface.class.getName());
			if(ok)
			{
				interfacesToProcess.add(typeElement);
				return;
			}
			ok = isException(typeElement);
			if(ok)
			{
				exceptionsToProcess.add(typeElement);
				return;
			}
			ok = isTStruct(typeElement);
			ok |= (kind == ElementKind.ENUM) && isImplementing(typeElement, TType.class.getName());
			if(ok)
			{
				classesToProcess.add(typeElement);
			}
			else if(!isImplementing(typeElement, TType.class.getName()))
			{
				// if not a field then it is unknown
				processingEnv.getMessager().printMessage(Kind.ERROR, "Unknown type " + typeElement.getSimpleName());
			}
		}

	}

	/**
	 * @param typeElement
	 * @return
	 */
	private boolean isException(TypeElement element) {
		ElementKind kind = element.getKind();
		if(!kind.isClass())
		{
			return false;
		}
		TypeMirror mirror = element.getSuperclass();
		if(mirror == null)
		{
			return false;
		}
		if(mirror.getKind() != TypeKind.DECLARED)
		{
			return false;
		}
		DeclaredType itftype = (DeclaredType) mirror;
		TypeElement itf = (TypeElement) itftype.asElement();
		String name = itf.getQualifiedName().toString();
		if("java.lang.Object".equals(name))
		{
			return false;
		}
		if(TException.class.getName().equals(name))
		{
			return true;
		}
		if(isException(itf))
		{
			return true;
		}

		return false;
	}

	private boolean isTStruct(TypeElement element) {
		ElementKind kind = element.getKind();
		if(!kind.isClass())
		{
			return false;
		}
		TypeMirror mirror = element.getSuperclass();
		if(mirror == null)
		{
			return false;
		}

		if(mirror.getKind() != TypeKind.DECLARED)
		{
			return false;
		}
		DeclaredType itftype = (DeclaredType) mirror;
		TypeElement itf = (TypeElement) itftype.asElement();
		String name = itf.getQualifiedName().toString();
		if("java.lang.Object".equals(name))
		{
			return false;
		}
		if(TStruct.class.getName().equals(name))
		{
			return true;
		}
		if(isTStruct(itf))
		{
			return true;
		}

		return false;
	}

	private boolean isImplementing(TypeElement element, String className) {
		List<? extends TypeMirror> itfs = element.getInterfaces();
		if(itfs == null || itfs.isEmpty())
		{
			return false;
		}
		for (TypeMirror mirror : itfs)
		{
			if(mirror.getKind() != TypeKind.DECLARED)
			{
				continue;
			}
			DeclaredType itftype = (DeclaredType) mirror;
			TypeElement itf = (TypeElement) itftype.asElement();
			String name = itf.getQualifiedName().toString();
			if("java.lang.Object".equals(name))
			{
				continue;
			}
			if(className.equals(name))
			{
				return true;
			}
			if(isImplementing(itf, className))
			{
				return true;
			}

		}
		return false;
	}

	public List<TIDLInterfaceModel> getTIDLInterfaceModel() {
		return tidlInterfaceModel;
	}
}