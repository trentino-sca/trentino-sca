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

import java.io.File;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.xml.bind.JAXBElement;
import javax.xml.namespace.NamespaceContext;
import javax.xml.namespace.QName;

import org.apache.log4j.Logger;
import org.trentino.trengen.ValidationException;
import org.trentino.trengen.cpp.model.ClassModel;
import org.trentino.trengen.cpp.model.HeaderFile;
import org.trentino.trengen.sca.model.CPPImplementation;
import org.trentino.trengen.sca.model.Component;
import org.trentino.trengen.sca.model.ComponentType;
import org.trentino.trengen.sca.model.Composite;
import org.trentino.trengen.sca.model.ContributionType;
import org.trentino.trengen.sca.model.DeployableType;
import org.trentino.trengen.sca.model.Implementation;
import org.trentino.trengen.sca.model.Include;
import org.trentino.trengen.sca.model.SCAImplementation;
import org.trentino.trengen.tools.trengen.ImportExport;
import org.trentino.trengen.tools.trengen.Trengen;

public class ScaValidationManager {
	protected static final Logger	            logger	                          = Logger.getLogger(ScaValidationManager.class);
	private final Map<String, CompositeWrapper>	compositeMap	                  = new HashMap<String, CompositeWrapper>();
	private IConformanceManagerCppImpArtifacts	conformanceManagerCppImplArtifacts;

	private Map<String, Boolean>	            compositesIfThereAreNoDeployables	= new HashMap<String, Boolean>();

	// This is the member that will be accessed by the conformanceManager
	private ContributionTypeWrapper	            contributionTypeWrapper	          = new ContributionTypeWrapper();

	private String	                            currentCompositeName	          = "";

	public ScaValidationManager (IConformanceManagerCppImpArtifacts confManagerCppImplArtifacts) {
		conformanceManagerCppImplArtifacts = confManagerCppImplArtifacts;
	}

	/**
	 * This function traces all the composites within the contribution resolves
	 * the composite names decodedNamespaceURL:compositeName Later on when the
	 * composites need to be located for composite inclusion or for composite
	 * used as component impl, we check out this map
	 * @param soruceDir
	 *            : Contribution directory
	 * @param contributionDir
	 */
	private boolean traceAllTheComposites(List<File> soruceDir, File contributionDir) {
		List<File> dirForComposites = new ArrayList<File>();
		dirForComposites.add(contributionDir);
		List<File> compositeFiles = DirectoryScanner.SearchArtifacts(dirForComposites, "composite");
		for (int i = 0; i < compositeFiles.size(); i++)
		{
			CompositeWrapper compositeWrapper = new CompositeWrapper();
			String nameCompositeFile = compositeFiles.get(i).getName();
			compositeWrapper.setCompositeFileName(nameCompositeFile);
			logger.info("XSD validating composite file: " + nameCompositeFile);
			if(!XsdValidator.validateArtifact(compositeFiles.get(i)))
			{
				logger.error("Composite: " + nameCompositeFile + " couldn't been validated!");
				compositeWrapper.setXSDValidationStat(false);
				return false;
			}
			else
			{
				compositeWrapper.setXSDValidationStat(true);
			}

			// XML parsing the composite file
			logger.info("XML parsing composite: " + nameCompositeFile);

			Composite composite = (Composite) XmlParser.parseArtifact(getURLByFile(compositeFiles.get(i)));
			compositeWrapper.setComposite(composite);
			NamespaceContext namespaceContext = NameSpaceResolver.GetNamespaces(compositeFiles.get(i));
			compositeWrapper.setNamespaceContext(namespaceContext);
			String compositeName = composite.getName();
			String targetNameSpace = composite.getTargetNamespace();
			String fullyQualifiedCompositeName = targetNameSpace + ":" + compositeName;
			compositeMap.put(fullyQualifiedCompositeName, compositeWrapper);

			checkIfBaseComposite(composite, fullyQualifiedCompositeName, compositeWrapper.getNamespaceContext());
		}
		return true;
	}

	/**
	 * TFS item 482: If there are no deployables, all the composites should be
	 * reflected to model. So the base composites (which contains others) are
	 * collected in compositesIfThereAreNoDeployables map.
	 */
	private void checkIfBaseComposite(Composite composite, String fullyQualifiedCompositeName, NamespaceContext namespace) {
		if(!compositesIfThereAreNoDeployables.containsKey(fullyQualifiedCompositeName))
		{
			compositesIfThereAreNoDeployables.put(fullyQualifiedCompositeName, true);
		}

		List<Object> objectsInComposite = composite.getRequiresOrPolicySetAttachmentOrService();
		for (int i = 0; i < objectsInComposite.size(); i++)
		{
			if(objectsInComposite.get(i).getClass().equals(Component.class))
			{
				Component component = (Component) objectsInComposite.get(i);
				if(component.getImplementation().getValue().getClass().equals(SCAImplementation.class))
				{
					SCAImplementation compositeImplementation = (SCAImplementation) component.getImplementation().getValue();
					if(compositeImplementation != null)
					{
						QName compositeImplName = compositeImplementation.getName();
						String keyToSearchComposite = null;
						if(compositeImplName.getPrefix().isEmpty())
						{
							keyToSearchComposite = composite.getTargetNamespace() + ":" + compositeImplName.getLocalPart();
						}
						else
						{
							keyToSearchComposite = findKeyforCompsositeSearch(compositeImplementation.getName(), namespace);
						}
						compositesIfThereAreNoDeployables.put(keyToSearchComposite, false);
					}
				}
			}
		}
	}

	private static URL getURLByFile(File file) {
		try
		{
			return file.toURI().toURL();
		} catch (Exception e)
		{
			throw new IllegalStateException("cannot parse URL from file", e);
		}
	}

	/**
	 * This function is the main entrance point for the validation checks the
	 * sequence is as the following -Find out teh specified contribution -xsd
	 * validate the contribution -xml parse the contribution -analyse the
	 * contribution for the composite -for each composite create a composite
	 * wrapper -xsd validate each composite file -analyse the namespaces of the
	 * composite and set the namespaces to the compositeWrapper -xml parse the
	 * composite files -manage the composite inclusion (use the outcoming merged
	 * composite(xsd validated and xml parsed] from now on) -analyse each
	 * composite file to detect components for the components with cpp
	 * implementation -according to the components find out componentType files
	 * -xsd parse componentType files -xml parse componentType files for the
	 * components with implementation.composite -validate the referred composite
	 * used as component impl -create the sca.componentType for the composite
	 * used as component implementation -create componentWrapper class -assoc
	 * the sca.component instance to the component wrapper -assoc the
	 * sca.componentType instance (outcome of xml parsing of componentType or
	 * the componentType generated for the composite used as component
	 * implementation) to the component wrapper -analyse the namespaces of the
	 * componentType and set the namespaces to the componentWrapper -validate
	 * the componentWrapper with ConformanceManagerCppImplArtifacts for cpp impl
	 * artifacts -add the componentWrapper to the ComponentWrapper list of the
	 * compositeWrapper -check if the headers given in the services and
	 * reference of composites are available -Validate the composite wrapper
	 * with ConformanceManagerProperty against property related specification
	 * -Validate the composite wrapper with
	 * ConformanceManager4ReferenceAndService against
	 * service/reference/wiring/bindin related specification
	 */
	public ContributionTypeWrapper validate(List<File> sourceDir, File contributionDir) throws Exception {
		try
		{
			return doValidation(sourceDir, contributionDir);
		} catch (ValidationException e)
		{
			if(contributionTypeWrapper != null)
			{
				e.setContributionTypeWrapper(contributionTypeWrapper);
				throw e;
			}
		}
		return contributionTypeWrapper;

	}

	private ContributionTypeWrapper doValidation(List<File> soruceDir, File contributionDir) throws Exception {
		if(!traceAllTheComposites(soruceDir, contributionDir))
		{
			return null;
		}
		File contributionFile = new File(contributionDir, "META-INF/sca-contribution.xml");
		if(!contributionFile.exists() || !contributionFile.isFile())
		{
			String message = "A contribution file does not exists in the contribution directory.\n it should be located at:"
			        + contributionFile.getPath();
			throw new ValidationException(message);
		}

		String contributionFileName = contributionFile.getName();

		// XSD parsing of the contribution file
		logger.info("XSD validating contribution file: " + contributionFileName);
		if(!XsdValidator.validateArtifact(contributionFile))
		{
			logger.error(ConformanceManagerConstants.CI_ASM12027_VIOLATED);
			logger.error(ConformanceManagerConstants.CI_CPP110003_VIOLATED);
			return null;
		}

		// XML parsing the contribution file
		logger.info("XML parsing contribution: " + contributionFileName);

		ContributionType contributionType = (ContributionType) XmlParser.parseArtifact(contributionFile.toURI().toURL());
		if(contributionType == null)
		{
			return null;
		}
		
        ImportExport.scanImportedDirectories(contributionType);
		contributionTypeWrapper.setContributionType(contributionType);
		if(!ConformanceManagerContribution.check_CI60001_forOneContribution(contributionTypeWrapper))
		{
			return contributionTypeWrapper;
		}
		// getDeployable give the composite list
		NamespaceContext namespaceContextForContribution = NameSpaceResolver.GetNamespaces(contributionFile);
		List<DeployableType> listDeployable = contributionTypeWrapper.getContributionType().getDeployable();

		// If there are no deployables, all the composites should be
		// reflected to model. So the base composites (which contains
		// others)
		// are collected in compositesIfThereAreNoDeployables map.
		if(listDeployable.isEmpty())
		{
			for (Map.Entry<String, Boolean> entry : compositesIfThereAreNoDeployables.entrySet())
			{
				String key = entry.getKey();
				Boolean value = entry.getValue();
				if(value == false)
				{
					continue;
				}

				CompositeWrapper compositeWrapper = validateComposite2(key, null);
				if(compositeWrapper != null)
				{
					compositeWrapper.setCompositeByImpl(false);
					contributionTypeWrapper.getListCompositeWrapper().add(compositeWrapper);
				}
				else
					return null;

			}
		}
		else
		{
			for (DeployableType deptype : listDeployable)
			{
				QName currentComposite = deptype.getComposite();
				currentCompositeName = currentComposite.getLocalPart();
				String keyForCompositeSearch = findKeyforCompsositeSearch(currentComposite, namespaceContextForContribution);

				if(!compositeMap.containsKey(keyForCompositeSearch))
				{
					// BUG 552: a user can decide do add deployable
					// composites after the contribution is loaded. So no
					// error should be raised.
					logger.warn("There is no matching .composite file for the composite: " + keyForCompositeSearch);
					continue;
				}

				CompositeWrapper compositeWrapper = validateComposite2(keyForCompositeSearch, null);
				if(compositeWrapper != null)
				{
					compositeWrapper.setCompositeByImpl(false);
					contributionTypeWrapper.getListCompositeWrapper().add(compositeWrapper);
				}
				else
					return null;

			}
		}

		return contributionTypeWrapper;
	}

	private boolean checkSpecsRecursively(CompositeWrapper compositeWrapper) {
		if(!hasSomeImplComponent(compositeWrapper))
		{
			ConformanceManager conformanceManager = new ConformanceManager(conformanceManagerCppImplArtifacts, compositeWrapper, false);
			if(!conformanceManager.checkSpecs())
			{
				return false;
			}

		}

		else
		{
			for (ComponentWrapper componentWrapper : compositeWrapper.listComponentWrappers)

			{
				if(componentWrapper.isCompositeByImpl())
				{
					if(!checkSpecsRecursively(componentWrapper.getCorrespondingCompositeImpl()))
					{
						return false;
					}
				}
			}
			ConformanceManager conformanceManager = new ConformanceManager(conformanceManagerCppImplArtifacts, compositeWrapper, false);
			if(!conformanceManager.checkSpecs())
			{
				return false;
			}
		}

		return true;

	}

	private boolean hasSomeImplComponent(CompositeWrapper compositeWrapper) {
		for (ComponentWrapper componentWrapper : compositeWrapper.listComponentWrappers)
		{
			if(componentWrapper.isCompositeByImpl())
			{
				return true;
			}
		}
		return false;

	}

	private static String findKeyforCompsositeSearch(QName compositeName, NamespaceContext namespaceContextForContribution) {
		String prefix = compositeName.getPrefix();
		String namespaceURI = namespaceContextForContribution.getNamespaceURI(prefix);
		String searchKey = null;
		if(namespaceURI == null)
		{
			searchKey = ":" + compositeName.getLocalPart();
		}
		else
		{
			searchKey = namespaceURI + ":" + compositeName.getLocalPart();
		}
		return searchKey;
	}

	private boolean setMatchingComponentType(Component component, ComponentWrapper componentWrapper, String targetNamespace,
	        ContributionTypeWrapper contributionTypeWrapper, CompositeWrapper parentCompositeWrapper) {
		NamespaceContext ns = parentCompositeWrapper.getNamespaceContext();
		String componentName = component.getName();
		String compositeName = parentCompositeWrapper.getCompositeName();
		Implementation impl = component.getImplementation().getValue();
		if(impl instanceof CPPImplementation)
		{
			if(searchMatchingComponentTypeOfCppImpl(component, componentWrapper, compositeName) == null)
			{
				return false;
			}
			ComponentType componentType = componentWrapper.getScaModelComponentType();
			if(!(ConformanceManagerComponent.check_CI20007(componentType) && ConformanceManagerComponent.check_CI20008(componentType)))
			{
				ValidationException validationException = new ValidationException(
				        "ComponentType couldn't be processed for the cpp implementation of the component: " + componentName);
				validationException.setLastEntity(componentType);
				throw validationException;
			}

			HeaderFile hf = findHeaderFile(componentType.getImplementation());
			if(hf != null)
			{
				componentWrapper.setComponentHeader(hf);
			}
			else
			{
				hf = findHeaderFile(componentWrapper.getScaModelComponent().getImplementation());
				if(hf != null)
					componentWrapper.setComponentHeader(hf);
			}
			componentWrapper.setCompositeByImpl(false);
			return true;

		}
		// For composite used as component implementation SCAImplementation is
		// used
		else if(impl instanceof SCAImplementation)
		{
			SCAImplementation compositeImplementation = (SCAImplementation) component.getImplementation().getValue();
			if(compositeImplementation != null)
			{
				// String compositeName =
				// compositeImplementation.getName().getLocalPart();
				QName compositeImplName = compositeImplementation.getName();
				String keyToSearchComposite = null;
				if(compositeImplName.getPrefix().isEmpty())
				{
					keyToSearchComposite = targetNamespace + ":" + compositeImplName.getLocalPart();
				}
				else
				{
					keyToSearchComposite = findKeyforCompsositeSearch(compositeImplementation.getName(), ns);
				}

				CompositeAsComponentImpHandler copositeByImpl = new CompositeAsComponentImpHandler(this);
				ComponentType componentType = copositeByImpl.searchMatchingComponentTypeOfCompositeImpl(keyToSearchComposite, ns,
				        contributionTypeWrapper, parentCompositeWrapper);
				if(componentType != null)
				{
					componentWrapper.setScaModelComponentType(componentType);
					componentWrapper.setCompositeByImpl(true);
					componentWrapper.setCorrespondingCompositeImpl(copositeByImpl.getCompositeWrapper());
					return true;
				}

				ValidationException validationException = new ValidationException(
				        "ComponentType couldn't be processed for the implementation of the component: " + componentName);
				validationException.setLastEntity(component);
				validationException.setLastEntity(componentType);
				throw validationException;
			}
		}
		ValidationException validationException = new ValidationException("Implementation given in component is not recognized. Component name: "
		        + componentName);
		validationException.setLastEntity(component);
		throw validationException;
	}

	private int getTotalCorrespondingComponentTypes(List<File> directoryToBeSearched, String className) {
		int count = 0;
		List<File> headerFiles = DirectoryScanner.SearchArtifacts(directoryToBeSearched, "h");
		List<File> headerFilesHpp = DirectoryScanner.SearchArtifacts(directoryToBeSearched, "hpp");
		for (File hppFile : headerFilesHpp)
		{
			headerFiles.add(hppFile);
		}
		for (File hFile : headerFiles)
		{
			HeaderFile headerFile = conformanceManagerCppImplArtifacts.GetHeaderFile(hFile.getAbsolutePath());
			List<ClassModel> classes = headerFile.getClasses();
			for (ClassModel classSingle : classes)
			{
				String classModelName = classSingle.getClassName();
				if(classModelName.contains("::"))
				{
					int index = classModelName.lastIndexOf("::");
					classModelName = classModelName.substring(index + 2);

					if(classModelName.equals(className))
					{
						count++;
					}
				}
				else if(classModelName.equals(className))
				{
					count++;
				}
			}
		}
		return count;
	}

	/*
	 * Searches for the componentType file according to the attributes of the
	 * implementation child element of the component
	 */
	private ComponentType searchMatchingComponentTypeOfCppImpl(Component component, ComponentWrapper componentWrapper, String parentCompositeName) {
		CPPImplementation cppImplementation = ((CPPImplementation) component.getImplementation().getValue());
		String artifactName = cppImplementation.getClazz();
		if(artifactName.contains(":"))
		{
			int index = artifactName.lastIndexOf(":");
			artifactName = artifactName.substring(index + 1);
		}
		String className = artifactName;
		String componentName = artifactName + ".componentType";

		// path to the componentType file
		String componentTypePath = cppImplementation.getComponentType();

		File componentFile = null;

		if(componentTypePath != null)
		{
			if(componentTypePath.contains(".componentType"))
			{
				componentFile = DirectoryScanner.searchArtifactFullPath(componentTypePath);
			}
			else
			{
				componentFile = DirectoryScanner.searchArtifactFullPath(componentTypePath + "//" + componentName);
			}
		}
		else
		{
			String artifactHeader = cppImplementation.getHeader();

			// if(hasRelativePath)
			// {
			List<String> hearderFullpath = DirectoryScanner.makeHeaderAttributeFullPathList(Trengen.getScaValidationFolder(), artifactHeader);
			if(hearderFullpath.isEmpty())
			{
				throw new ValidationException("Header file does not exists:" + cppImplementation.getHeader()
				        + "\nMake sure that the relative path is correct");
			}
			for (String path : hearderFullpath)
			{
				File parentDir = new File(path).getParentFile();
				File compTypef = new File(parentDir, componentName);
				if(compTypef.exists())
				{
					// Check that the header file has the class
					HeaderFile headerFile = conformanceManagerCppImplArtifacts.GetHeaderFile(path);
					if(headerFile == null)
					{
						throw new ValidationException("Header file does not exists:" + cppImplementation.getHeader()
						        + "\nMake sure that the relative path is correct");
					}
					List<ClassModel> classes = headerFile.getClasses();
					boolean found = false;
					for (ClassModel c : classes)
					{
						if(c.getFullQualifiedClassName().equals(cppImplementation.getClazz()))
						{
							found = true;
							break;
						}
					}
					if(!found)
					{
						String format = "The component type '%s' has defined a class '%s' in header file '%s', but the class cannot be found in the header file.\nMake sure that your path and classname are correct ";
						throw new ValidationException(String.format(format, compTypef.getPath(), cppImplementation.getClazz(),
						        cppImplementation.getHeader()));
					}
					componentFile = compTypef;
				}
			}
			//
			//
			//
			// List<File> hearderFullpathDir = new ArrayList<File>();
			// hearderFullpathDir.add(new File(hearderFullpath));
			// if(getTotalCorrespondingComponentTypes(hearderFullpathDir, className) > 1)
			// {
			// throw new ValidationException(
			// "There are more than 1 classes with the same name. Please provide a @componentType value for component: "
			// + component.getName() + " @" + currentCompositeName);
			// }
			// componentName = artifactHeader + componentName;
			// }
			// else
			// {
			// if(getTotalCorrespondingComponentTypes(Trengen.getScaValidationFolder(), className) > 1)
			// {
			// throw new ValidationException(
			// "There are more than 1 classes with the same name. Please provide a @componentType value for component: "
			// + component.getName() + " @" + currentCompositeName);
			// }
			// }

			// componentFile = DirectoryScanner.searchArtifactFullPath(componentName);
		}

		// XSD validation of the ComponentType file
		logger.info("XSD validating componentType file: " + componentName);
		if(componentFile == null)
		{
			throw new ValidationException(ConformanceManagerConstants.CI_ASM40001_VIOLATED + "\n" + ConformanceManagerConstants.CI_CPP20009_VIOLATED
			        + "There is no matching .componentType file for the component: " + componentName + " of composite: " + parentCompositeName);
		}

		if(!XsdValidator.validateArtifact(componentFile))
		{
			throw new ValidationException(ConformanceManagerConstants.CI_CPP110002_VIOLATED + "\nFile: " + componentFile.getName());
		}

		// // XML parsing of the componentType file
		logger.info("XML parsing componentType file: " + componentName);

		ComponentType componentType = (ComponentType) XmlParser.parseArtifact(getURLByFile(componentFile));

		NamespaceContext namespaceContextComponentType = NameSpaceResolver.GetNamespaces(componentFile);
		componentWrapper.setNamespaceContextComponentType(namespaceContextComponentType);
		componentWrapper.setScaModelComponentType(componentType);
		componentWrapper.setScaModelComponentTypeFile(componentFile);
		HeaderFile hf = findHeaderFile(componentType.getImplementation());
		if(hf != null)
		{
			componentWrapper.setComponentHeader(hf);
		}
		else
		{
			hf = findHeaderFile(componentWrapper.getScaModelComponent().getImplementation());
			if(hf != null)
				componentWrapper.setComponentHeader(hf);
		}
		if(!conformanceManagerCppImplArtifacts.checkCPPArtifactsImplementation(componentWrapper, componentFile))
		{
			return null;
		}
		return componentType;

	}

	private HeaderFile findHeaderFile(JAXBElement<? extends Implementation> jaxbElement) {
		if(jaxbElement == null || jaxbElement.isNil())
		{
			return null;
		}
		Implementation impl = jaxbElement.getValue();
		if(impl instanceof CPPImplementation)
		{
			CPPImplementation cppImplementation = (CPPImplementation) impl;
			String fullHeaderPathFirstHeader = DirectoryScanner.makeHeaderAttributeFullPath(Trengen.getScaValidationFolder(),
			        cppImplementation.getHeader());
			if(fullHeaderPathFirstHeader == null)
			{
				return null;
			}
			HeaderFile firstHeader = conformanceManagerCppImplArtifacts.GetHeaderFile(fullHeaderPathFirstHeader);
			return firstHeader;
		}

		return null;
	}

	// public static CompositeWrapper ValidateComposite(String compositeName,
	// boolean isCompositeByImp)
	// {
	// String compositeFileName = compositeName + ".composite";
	// File compositeFile = DirectoryScanner.SearchArtifact(compositeFileName);
	// if(compositeFile == null)
	// {
	// logger.error("There is no matching .composite file for the composite: " +
	// compositeName + " of contribution: ");
	// if(isCompositeByImp)
	// {
	// logger.error(ConformanceManagerConstants.CI_ASM60030_VIOLATED);
	// }
	// return null;
	// }
	//
	// logger.info("XSD validating composite file: " + compositeFileName);
	// if(!XsdValidator.validateArtifact(compositeFile))
	// {
	// logger.error(ConformanceManagerConstants.CI_ASM13001_VIOLATED +
	// " Composite: " + compositeFileName);
	// logger.error(ConformanceManagerConstants.CI_CPP110001_VIOLATED +
	// " Composite: " + compositeFileName);
	// return null;
	// }
	//
	// // XML parsing the composite file
	// logger.info("XML parsing composite: " + compositeFileName);
	//
	// CompositeWrapper compositeWrapper = new CompositeWrapper();
	// Composite composite = (Composite)
	// XmlParser.parseArtifact(compositeFile.getAbsolutePath());
	// NamespaceContext namespaceContext =
	// NameSpaceResolver.GetNamespaces(compositeFile);
	// compositeWrapper.setNamespaceContext(namespaceContext);
	//
	// if(composite == null)
	// {
	// return null;
	// }
	//
	// CompositeIncluder ci = new CompositeIncluder();
	// Composite compositeWithInclusions = ci.includer(composite);
	// if(compositeWithInclusions == null)
	// {
	// return null;
	// }
	//
	// compositeWrapper.setComposite(compositeWithInclusions);
	//
	// // Go through the components in the composite
	// logger.info("Tracing the components of composite: " + compositeFileName);
	//
	// if(ConformanceManagerComposite.check_CI50001_forOneComposite(compositeWithInclusions)
	// &&
	// ConformanceManagerComposite.check_CI20010_forOneComposite(compositeWithInclusions))
	// {
	// int sizeOfComponentElements =
	// compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().size();
	// for (int index = 0; index < sizeOfComponentElements; index++)
	// {
	// if(compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(index).getClass().equals(Component.class))
	// {
	// Component component = (Component)
	// compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService().get(index);
	//
	// ComponentWrapper componentWrapper = new ComponentWrapper();
	// componentWrapper.setScaModelComponent(component);
	// componentWrapper.setParentCompositeWrapper(compositeWrapper);
	//
	// if(!setMatchingComponentType(component,
	// componentWrapper,compositeWrapper.getNamespaceContext(),composite.getTargetNamespace()))
	// {
	// return null;
	// }
	// compositeWrapper.listComponentWrappers.add(componentWrapper);
	// }
	// }
	//
	// if(!ConformanceManager.CheckSpecs(compositeWrapper, isCompositeByImp))
	// {
	// return null;
	// }
	//
	// }
	// return compositeWrapper;
	// }

	private boolean containsComponentWrapper(CompositeWrapper compositeWrapper, ComponentWrapper componentWrapper) {
		Set<ComponentWrapper> compWrappers = compositeWrapper.listComponentWrappers;
		for (ComponentWrapper cw : compWrappers)
		{
			if(cw.getScaModelComponent().getName().equals(componentWrapper.getScaModelComponent().getName()))
			{
				return true;
			}
		}
		return false;
	}

	/**
	 * This function gets the key to search for the CompositeWrapper(composite)
	 * within the compositeMap.
	 * @param compositeSearchKey
	 * @param isCompositeByImp
	 * @return
	 */
	public CompositeWrapper validateComposite2(String compositeSearchKey, CompositeWrapper parentCompositeWrapper) {
		CompositeWrapper compositeWrapper = compositeMap.get(compositeSearchKey);
		if(compositeWrapper == null)
		{
			logger.error("compositeWrapper is null for composite: " + compositeSearchKey);
			return null;
		}
		// contributionTypeWrapper.listCompositeWrappers.add(compositeWrapper); --> this is done in doValidation()
		String cmpName = compositeWrapper.getCompositeName();
		String cmpFn = compositeWrapper.getCompositeFileName();

		compositeWrapper.setCompositeByImpl(true);
		compositeWrapper.parent = parentCompositeWrapper;

		if(!compositeWrapper.getXSDValidationStat())
		{
			ValidationException exception = new ValidationException();

			String format = "%s  Composite File name: %s  compositeName: %s";
			exception.addMessage(String.format(format, ConformanceManagerConstants.CI_ASM13001_VIOLATED, cmpFn, cmpName));
			exception.addMessage(String.format(format, ConformanceManagerConstants.CI_CPP110001_VIOLATED, cmpFn, cmpName));
			exception.setLastEntity(compositeWrapper);
			throw exception;
		}

		Composite compositeWithInclusions = resolveInclusions(compositeWrapper);
		if(compositeWithInclusions == null)
		{
			return null;
		}

		compositeWrapper.setComposite(compositeWithInclusions);

		// Go through the components in the composite
		logger.info("Tracing the components of composite: " + cmpFn);

		// fill out the componentWrappers of the composite
		if(!(ConformanceManagerComposite.check_CI50001_forOneComposite(compositeWithInclusions) && ConformanceManagerComposite
		        .check_CI20010_forOneComposite(compositeWithInclusions)))
		{
			return compositeWrapper;
		}
		
		ValidationException ex2 = new ValidationException();
		for (Object object : compositeWrapper.getComposite().getRequiresOrPolicySetAttachmentOrService())
		{
			if(object instanceof Component)
			{
				Component component = (Component) object;

				ComponentWrapper componentWrapper = new ComponentWrapper();
				componentWrapper.setScaModelComponent(component);
				componentWrapper.setParentCompositeWrapper(compositeWrapper);
				if(!containsComponentWrapper(compositeWrapper, componentWrapper))
				{
					compositeWrapper.listComponentWrappers.add(componentWrapper);
				}
				try
				{
					if(!setMatchingComponentType(component, componentWrapper, compositeWithInclusions.getTargetNamespace(), contributionTypeWrapper,
					        compositeWrapper))
					{
						return null;
					}
				} catch (ValidationException e)
				{
					e.setLastEntity(componentWrapper);
					ex2.getExceptions().add(e);
				}

			}
		}
		if(ex2.getExceptions().size()!=0){
			throw ex2;
		}
		if(!checkSpecsRecursively(compositeWrapper))
		{
			return null;
		}

		return compositeWrapper;
	}

	/**
	 * A recursive method for composite inclusion
	 * @param comp
	 * @return an object of Composite type Handles ASM60041: If the included
	 *         composite has the value true for the attribute @local then the
	 *         including composite MUST have the same value for the @local
	 *         attribute, else it is an error.
	 */
	private Composite resolveInclusions(final CompositeWrapper compositeWrapper) {

		Composite composite = compositeWrapper.getComposite();
		NamespaceContext ns = compositeWrapper.getNamespaceContext();
		// Composite composite = comp;
		for (Include include : composite.getInclude())
		{
			QName compositeName = include.getName();
			String keyToSearchComposite = null;
			if(compositeName.getPrefix().isEmpty())
			{
				keyToSearchComposite = composite.getTargetNamespace() + ":" + compositeName.getLocalPart();
			}
			else
			{
				keyToSearchComposite = ScaValidationManager.findKeyforCompsositeSearch(compositeName, ns);
			}
			if(!compositeMap.containsKey(keyToSearchComposite))
			{
				return null;
			}
			CompositeWrapper compositeWrapperOfCompositeIncluded = compositeMap.get(keyToSearchComposite);
			Composite compositeIncluded = compositeWrapperOfCompositeIncluded.getComposite();
			if(compositeIncluded == null)
			{
				continue;
			}

			if(!compositeIncluded.isAutowire() && composite.isAutowire())
			{
				throw new ValidationException(ConformanceManagerConstants.CI_ASM60041_VIOLATED);
			}

			for (Object object : compositeIncluded.getRequiresOrPolicySetAttachmentOrService())
			{
				composite.getRequiresOrPolicySetAttachmentOrService().add(object);
			}
			resolveInclusions(compositeWrapperOfCompositeIncluded);
		}
		return composite;
	}

}