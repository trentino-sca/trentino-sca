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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
// **********************************************************************************
package org.trentino.trengen.tools.scavalidation;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

import org.apache.log4j.Logger;
import org.trentino.trengen.TIterable;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.cpp.model.ClassMethod;
import org.trentino.trengen.cpp.model.ClassMethodArgument;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.cpp.model.HeaderFile;
import org.trentino.trengen.sca.model.CPPImplementation;
import org.trentino.trengen.sca.model.CPPInterface;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentReference;
import org.trentino.trengen.sca.model.ComponentService;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.ComponentTypeReference;
import org.trentino.trengen.sca.model.Composite;
import org.trentino.trengen.sca.model.Property;
import org.trentino.trengen.sca.model.PropertyValue;
import org.trentino.trengen.sca.model.Reference;
import org.trentino.trengen.sca.model.Service;
import org.trentino.trengen.sca.model.Wire;
import org.trentino.trengen.tools.trengen.Trengen;

public class ConformanceManager {

	protected static final Logger	               logger	                              = Logger.getLogger(ConformanceManagerProperty.class);

	private ConformanceManagerProperty	           conformanceManagerProperty	          = null;

	private ConformanceManagerWire	               conformanceManagerWire	              = null;
	private IConformanceManagerCppImpArtifacts	   conformanceManagerCppImplArtifacts	  = null;

	private ConformanceManager4ReferenceAndService	conformanceManager4ServicesReferences	= null;
	private CompositeWrapper	                   compositeWrapper;
	private boolean	                               isCompositeByImp;

	public ConformanceManager (IConformanceManagerCppImpArtifacts confManagerCppImplArtifacts, CompositeWrapper compositeWrapper,
	        boolean isCompositeByImp) {
		conformanceManagerCppImplArtifacts = confManagerCppImplArtifacts;
		this.compositeWrapper = compositeWrapper;
		this.isCompositeByImp = isCompositeByImp;
		if(compositeWrapper == null)
		{
			throw new ValidationException("Composite wrapper is null");
		}
		conformanceManagerProperty = new ConformanceManagerProperty(compositeWrapper);

		conformanceManagerWire = new ConformanceManagerWire();

		conformanceManager4ServicesReferences = new ConformanceManager4ReferenceAndService(compositeWrapper, conformanceManagerCppImplArtifacts);
	}

	/**
	 * @param compositeWrap
	 * @return
	 */
	public boolean checkSpecs() {

		Composite composite = compositeWrapper.getComposite();
		if(composite == null)
		{
			throw new ValidationException("Composite object is null");
		}
		logger.info("Validating properties of Composite: " + composite.getName());

		if(!traceComposite(compositeWrapper))
		{
			return false;
		}

		if(!traceComponentWrappers(compositeWrapper))
		{
			return false;
		}

		// The order is important! Do not change!
		// 1. It checks for wires and populates related target objects
		// 2. It checks for the targets of component level and componenttype
		// level references.
		// Populates the component-level targets according to corresponding
		// component-type level reference
		// 3. It checks for promotions. Populates the composite level references
		// according to promotions.
		// 4. It checks for tatgets of composite level references
		// 5. It checks for composite level service promotions
		if(!conformanceManager4ServicesReferences.checkForWires()
		        || !conformanceManager4ServicesReferences.checkForComponentTypeAndComponentReferenceTargets()
		        || !conformanceManager4ServicesReferences.checkAllReferencePromotions()
		        || !conformanceManager4ServicesReferences.checkForCompositeReferenceTargets()
		        || !conformanceManager4ServicesReferences.checkAllServicePromotions())
		{
			return false;
		}
		Set<ComponentWrapper> compWrappers = conformanceManager4ServicesReferences.getComponentWrappers();
		List<ValidationException> exs = new ArrayList<ValidationException>();
		for (ComponentWrapper compWrapper : compWrappers)
		{
			try{
				if(!validateInjectionMethods(compWrapper))
				{
					return false;
				}
			}catch (ValidationException e) {
				e.setLastEntity(compWrapper);
				exs.add(e);
			}
			
		}
		
		if(!exs.isEmpty()){
			ValidationException e  =  new ValidationException();
			e.addExceptions(exs);
			throw e;
		}
		if(!conformanceManagerWire.checkConformanceItems(compositeWrapper))
		{
			return false;
		}
		if(isCompositeByImp)
		{
			if(!conformanceManager4ServicesReferences.check_ASM60033())
			{
				return false;
			}
		}
		return true;
	}

	/**
	 * This function checks out the references in the component type and
	 * searches if the setter methods are available within the implementation
	 * header REMARK!!! All the references in components are also in the
	 * corresponding componentType files. Checking only the componentType
	 * references makes sense because componentType files may have more
	 * references than components. references in componentType files are base
	 * class of the corresponding references in component.
	 */
	private boolean validateInjectionMethods(ComponentWrapper compWrapper) {
		ComponentType scaModelComponentType = compWrapper.getScaModelComponentType();
		String functionName = "";
		if(compWrapper.isCompositeByImpl() == true)
			return true;

		HeaderFile headerFile = compWrapper.getComponentHeader();
		int size = scaModelComponentType.getServiceOrReferenceOrProperty().size();
		for (int index = 0; index < size; index++)
		{
			Object object = scaModelComponentType.getServiceOrReferenceOrProperty().get(index);
			if(object.getClass().equals(ComponentTypeReference.class))
			{
				int doesSetterExist = 0;
				ClassMethod setterMethod = null;
				CPPInterface refInterface = null;
				String className = null;
				String headerFilePath = null;
				ComponentTypeReference cs = (ComponentTypeReference) object;

				String refName = cs.getName();
				functionName = "set" + refName;
				boolean isMultiple = (cs.getMultiplicity().equals("0..n") || cs.getMultiplicity().equals("1..n")) ? true : false;
				for (ClassModel model : headerFile.getClasses())
				{
					List<ClassMethod> methods = model.getMethods();
					for (ClassMethod method : methods)
					{
						if(method.getName().trim().equals(functionName.trim()))
						{
							refInterface = (CPPInterface) cs.getInterface().getValue();
							className = refInterface.getClazz();
							className = Trimclass(className);
							headerFilePath = refInterface.getHeader();

							setterMethod = method;
							doesSetterExist++;
						}
					}
				}
				if(doesSetterExist == 0)
				{
					throw new ValidationException("Setter method with name " + functionName
					        + " for dependency injection not found in Cpp headerfile " + headerFile.getName() + ".");
				}
				else if(doesSetterExist > 1)
				{
					throw new ValidationException("There are more than 1 setter methods with name " + functionName + " in Cpp headerfile "
					        + headerFile.getName() + ". There should be only 1 setter method so that overloaded setter methods are not allowed.");
				}
				else
				{
					List<ClassMethodArgument> arguments = setterMethod.getArguments();
					if(arguments.size() > 1)
					{
						throw new ValidationException("There are more than 1 argument for setter method(" + functionName + ") in header file "
						        + headerFile.getName());
					}

					String argType = arguments.get(0).getType();
					boolean isList = argType.contains("list") && argType.contains("<") && argType.contains(">");
					argType = arguments.get(0).getTrimmedType();
					argType = Trimclass(argType);

					if(true == isMultiple)
					{
						if(false == isList)
						{
							throw new ValidationException("Although multiplicity for componenttype reference \"" + cs.getName()
							        + "\" is either 0..n or 1..n; its setter method(" + functionName
							        + ") has not an input argument of type std::list. In " + headerFile.getName());
						}

						if(!className.equals(argType))
						{
							throw new ValidationException("Argument in the setter function should be the same class with" + className + " in "
							        + functionName + "() function.");
						}
					}
					else
					{
						if(true == isList)
						{
							throw new ValidationException("Although multiplicity for componenttype reference \"" + cs.getName()
							        + "\" is not neither 0..n nor 1..n; its setter method(" + functionName
							        + ") has an input argument of type std::list. In " + headerFile.getName());
						}

						String fullHeaderPath = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(), headerFilePath);
						if(fullHeaderPath == null)
						{
							throw new ValidationException("Interface header is missing for reference:" + cs.getName());
						}
						HeaderFile headerFileReference = conformanceManagerCppImplArtifacts.GetHeaderFile(fullHeaderPath);
						if(!((argType.equals(className)) || IsBaseFirstOfSecond(className, argType, headerFileReference)))
						{
							throw new ValidationException(String.format(
							        "In header file %s,\n argument in the setter function %s should be the same class or derived from %s",
							        headerFile.toString(), functionName, className));
						}
					}
				}
			}
		}

		return true;
	}

	private String Trimclass(String className) {
		if(className.contains("::"))
		{
			int index = className.lastIndexOf(":");
			className = className.substring(index + 1, className.length());
		}
		className = className.replace("*", "");
		className = className.replace("&", "");
		className = className.replace("<", "");
		className = className.replace(">", "");
		return className;
	}

	private boolean IsBaseFirstOfSecond(String firstClass, String secondClass, HeaderFile headerFileOfSecond) {
		List<String> baseClassesOfSecondClass = new ArrayList<String>();
		for (int i = 0; i < headerFileOfSecond.getClasses().size(); i++)
		{
			// Find the second class in the second header
			ClassModel classModel = headerFileOfSecond.getClasses().get(i);
			String className = classModel.getClazzName();
			if(className.equals(secondClass.trim()))
			{
				baseClassesOfSecondClass = classModel.getBaseClasses();
				break;
			}
		}
		// first if the name of the base classes of the second class mathes the
		// first class
		for (int i = 0; i < baseClassesOfSecondClass.size(); i++)
		{
			if(baseClassesOfSecondClass.get(i).trim().equals(firstClass.trim()))
			{
				return true;
			}
		}
		// second recursively search for the base classes of the base classes of
		// the second class for a match
		// After switching to eclipse CDT parser no need to explicitly check the
		// included files(see part commented out below)
		// but instead we should keep recursively checking for the base class of
		// of the secondclass
		for (int i = 0; i < baseClassesOfSecondClass.size(); i++)
		{
			String baseClassName = baseClassesOfSecondClass.get(i);
			if(IsBaseFirstOfSecond(firstClass, baseClassName, headerFileOfSecond))
			{
				return true;
			}
		}
		return false;
	}

	/**
	 * This function traces all composite level services,referemces,wires and
	 * properties
	 */
	private boolean traceComposite(CompositeWrapper compositeWrapper) {
		if(compositeWrapper == null)
		{
			logger.error("Given compositeWrap is null");
			return false;
		}
		Composite composite = compositeWrapper.getComposite();
		if(composite == null)
		{
			logger.error("Composite object is null");
			return false;
		}
		logger.info("Validating properties of Composite: " + composite.getName());
		List<ValidationException> exs = new ArrayList<ValidationException>();

		for (Object obj : composite.getRequiresOrPolicySetAttachmentOrService())
		{
			try
			{

				if(obj instanceof Property)
				{
					Property propertyComposite = (Property) obj;
					if(!conformanceManagerProperty.OnNewPropertyOfComposite(propertyComposite))
					{
						return false;
					}

				}
				else if(obj instanceof Reference)
				{
					Reference reference = (Reference) obj;
					if(!conformanceManager4ServicesReferences.OnNewReferenceOfComposite(reference))
					{
						return false;
					}
				}

				else if(obj instanceof Service)
				{
					Service service = (Service) obj;
					if(!conformanceManager4ServicesReferences.OnNewServiceOfComposite(service))
					{
						return false;
					}
				}

				else if(obj instanceof Wire)
				{
					Wire wire = (Wire) obj;
					if(!conformanceManager4ServicesReferences.OnNewWireOfComposite(wire))
					{
						return false;
					}
				}
				else if(obj instanceof Component)
				{
					Component component = (Component) obj;
					if(!conformanceManager4ServicesReferences.OnNewComponentOfComposite(component))
					{
						return false;
					}
					if(!conformanceManager4ServicesReferences.onNewComponentTypeOfComposite(component))
					{
						return false;
					}
				}
			} catch (ValidationException e)
			{
				e.setLastEntity(obj);
				exs.add(e);
			}

		}
		if(!exs.isEmpty())
		{
			ValidationException e = new ValidationException();
			e.addExceptions(exs);
			throw e;
		}
		return true;
	}

	/**
	 * This function through the componentTypes within the componentWrapper,
	 * Afterwards it goues through the components of the cmponentWrapper(this
	 * tracing couldn't be avoided since it is require to check out from the
	 * component level for some specifications)
	 */
	private boolean traceComponentWrappers(CompositeWrapper compositeWrapper) {
		if(!conformanceManager4ServicesReferences.checkInterfaces()){
			return false;
		}
		List<ValidationException> exs = new ArrayList<ValidationException>();
		for (ComponentWrapper componentWrapper : compositeWrapper.listComponentWrappers)
		{

			ComponentType currentComponentType = componentWrapper.getScaModelComponentType();
			try
			{
				if(!doTraceComponentWrappers(componentWrapper, currentComponentType))
				{
					return false;
				}
			} catch (ValidationException e)
			{
				e.setLastEntity(componentWrapper);
				exs.add(e);
			}

		}
		if(!exs.isEmpty())
		{
			ValidationException e = new ValidationException();
			e.addExceptions(exs);
			throw e;
		}
		return true;
	}

	private boolean doTraceComponentWrappers(ComponentWrapper componentWrapper, ComponentType currentComponentType) {
		if(currentComponentType == null)
		{
			throw new ValidationException("componentType object is null");
		}

		Component component = componentWrapper.getScaModelComponent();
		String currentComponentName = component.getName();
		CPPImplementation cppImplementation = null;
		if(component.getImplementation() != null)
		{
			if(component.getImplementation().getValue().getClass().equals(CPPImplementation.class))
			{
				cppImplementation = (CPPImplementation) component.getImplementation().getValue();
			}
		}

		ArrayList<String> refNames = new ArrayList<String>();
		ArrayList<String> serviceNames = new ArrayList<String>();

		// component Wrapper is used to set the current component,
		// componenttype etc at the relevant conformance manager
		conformanceManagerProperty.setComponentWrapper(componentWrapper);

		// go through the services, references and properties of the
		// componentType
		List<ValidationException> execptions = new ArrayList<ValidationException>();
		for (Object obj : currentComponentType.getServiceOrReferenceOrProperty())
		{
			try
			{
				if(obj instanceof Property)
				{
					Property currentProperty = (Property) obj;
					if(!conformanceManagerProperty.checkComponentTypeProperty(currentProperty))
					{
						ValidationException validationException = new ValidationException("Component properties not valid");
						throw validationException;
					}
				}
				else if(obj instanceof ComponentTypeReference)
				{
					ComponentTypeReference ref = (ComponentTypeReference) obj;
					mergeComponentTypeReference(ref,component);
					if(!conformanceManager4ServicesReferences.checkForComponentTypeReference(ref, component, refNames,componentWrapper))
					{
						ValidationException validationException = new ValidationException("Component type not valid");
						throw validationException;
					}
				}
				else if(obj instanceof ComponentService)
				{
					ComponentService cs = (ComponentService) obj;
					if(!conformanceManager4ServicesReferences.checkForComponentTypeService(cs, component, serviceNames, cppImplementation))
					{
						ValidationException validationException = new ValidationException("Service or reference not valid");
						throw validationException;
					}

				}
			} catch (ValidationException e)
			{
				e.setLastEntity(obj);
				execptions.add(e);
			}

		}

		if(!execptions.isEmpty())
		{
			ValidationException ex = new ValidationException();
			ex.addExceptions(execptions);
			throw ex;
		}
		serviceNames.clear();
		refNames.clear();

		// go through the services, references and properties of the
		// component
		for (Object obj : component.getServiceOrReferenceOrProperty())
		{
			try
			{
				if(obj instanceof PropertyValue)
				{
					PropertyValue currentPropValue = (PropertyValue) obj;
					if(!conformanceManagerProperty.checkComponentProperty(currentPropValue))
					{
						return false;
					}

				}
				else if(obj instanceof ComponentService)
				{
					ComponentService compService = (ComponentService) obj;
					if(!conformanceManager4ServicesReferences.checkForComponentService(compService, currentComponentType, serviceNames,
					        currentComponentName))
					{
						return false;
					}
				}
				else if(obj instanceof ComponentReference)
				{
					ComponentReference compRef = (ComponentReference) obj;
					if(!conformanceManager4ServicesReferences.checkForComponentReference(compRef, currentComponentType, refNames,
					        currentComponentName))
					{
						return false;
					}
				}
			} catch (ValidationException e)
			{
				e.setLastEntity(obj);
				execptions.add(e);
			}

		}
		
		if(!execptions.isEmpty())
		{
			ValidationException ex = new ValidationException();
			ex.addExceptions(execptions);
			throw ex;
		}
		return true;
	}

	private void mergeComponentTypeReference(ComponentTypeReference ref,
			Component component) {
		TIterable<ComponentReference> refs = TIterable.iterable(component.getServiceOrReferenceOrProperty(), ComponentReference.class);
		for(ComponentReference r : refs){
			if(r.getName()!=null && r.getName().equals(ref.getName())){
				//Then merge targets
				if(!r.getTarget().isEmpty()){
					ref.getTarget().clear();
					ref.getTarget().addAll(r.getTarget());
				}
			}
			
		}
		
	}
}
