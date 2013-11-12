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

package org.trentino.trengen.model2mirrormodel;

import static javax.lang.model.SourceVersion.RELEASE_6;

import java.io.File;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import javax.annotation.processing.AbstractProcessor;
import javax.annotation.processing.ProcessingEnvironment;
import javax.annotation.processing.RoundEnvironment;
import javax.annotation.processing.SupportedAnnotationTypes;
import javax.annotation.processing.SupportedSourceVersion;
import javax.lang.model.element.AnnotationMirror;
import javax.lang.model.element.Element;
import javax.lang.model.element.TypeElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Logger;
import org.trentino.trengen.model2mirrormodel.marshal.SCAModelMirrorWriter;
import org.trentino.trengen.model2mirrormodel.marshal.SCAModelWriter;

/**
 * Annotation processor used to generated C++ and Protobuf model files based on
 * the Java representatation of an XSD schema.
 * @author z002ttbb
 */
@SupportedAnnotationTypes("*")
@SupportedSourceVersion(RELEASE_6)
public class ModelGenerator extends AbstractProcessor {

	private static final String	  ORG_TRENTINO_TRENGEN_SCAMODELMIRROR_CONTRACT_JAVA	= "org/trentino/trengen/scamodelmirror/Contract.java";
	protected static final Logger	logger	                                        = Logger.getLogger(ModelGenerator.class);
	private static final Boolean	ALLOW_OTHER_PROCESSORS_TO_CLAIM_ANNOTATIONS	    = Boolean.FALSE;

	private static String	      JAXB_POJO_ANN	                                    = XmlType.class.getName();
	private static String	      JAXB_POJO_ANN2	                                = XmlRootElement.class.getName();

	static
	{
		// Initialize log4j
		BasicConfigurator.configure();
	}

	private Context	              context;

	/**
	 * {@inheritDoc}
	 */
	@Override
	public synchronized void init(ProcessingEnvironment processingEnv) {
		super.init(processingEnv);
		context = new Context(processingEnv);

	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public boolean process(Set<? extends TypeElement> annotations, RoundEnvironment roundEnvironment) {
		logger.debug("\n\n\n#######################Start processing.\n\n\n##################################################");
		logger.debug("\n\n\n#######################Output Dir:" + context.getOutputDir());
		// FIXME Quik fix to reduce processing time. and duplicate processing
		if(context.getOutputDir() != null && context.getOutputDir().exists())
		{
			File f = new File(context.getOutputDir(), ORG_TRENTINO_TRENGEN_SCAMODELMIRROR_CONTRACT_JAVA);
			if(f.exists())
			{
				logger.debug("\n\n\nFiles allready generated, skipping annotation processing\n\n\n");
				return ALLOW_OTHER_PROCESSORS_TO_CLAIM_ANNOTATIONS;
			}
			else
			{
				logger.debug("\n\n\nWriting annotations based of file" + f.getAbsolutePath() + "\n\n\n");
			}
		}
		if(roundEnvironment.processingOver())
		{
			createClasses();
			logger.debug("Finished processing. END");
			return ALLOW_OTHER_PROCESSORS_TO_CLAIM_ANNOTATIONS;

		}

		if(!hostJAXBAnnotations(annotations))
		{

			System.out.println("Current processing round does not contain jaxb pojos");

			return ALLOW_OTHER_PROCESSORS_TO_CLAIM_ANNOTATIONS;

		}

		Set<? extends Element> elements = roundEnvironment.getRootElements();

		for (Element element : elements)
		{
			logger.info("Processing " + element.toString());
			handleRootElementAnnotationMirrors(element);
		}

		return ALLOW_OTHER_PROCESSORS_TO_CLAIM_ANNOTATIONS;
	}

	/**
	 * genetate the classes. For this purpose, first a model is created based on
	 * the JAXB representation of the XSD
	 */
	private void createClasses() {
		Set<ClassInfo> classes = new TreeSet<ClassInfo>();
		ClassInfoBuilder builder = new ClassInfoBuilder(context);
		for (TypeElement entity : context.getPojosToProcess().values())
		{
			builder.createClassInfos(entity, classes);
		}
		logger.debug("Number of classes found: " + classes.size() + " classes");
		ClassInfo enumClass = null;
		for (ClassInfo inf : classes)
		{
			if("Enum".equals(inf.getName()))
			{
				enumClass = inf;
				break;
			}
		}
		if(enumClass != null)
		{
			classes.remove(enumClass);
		}
		context.setClasses(classes);
		SCAModelWriter writer = new SCAModelWriter(context);
		writer.generate();
		SCAModelMirrorWriter mirrorWriter = new SCAModelMirrorWriter(context);
		mirrorWriter.generate();
	}

	/**
	 * save all needed annotations in a context object. So that they can be
	 * processed later on.
	 * @param element
	 */
	private void handleRootElementAnnotationMirrors(final Element element) {

		List<? extends AnnotationMirror> annotationMirrors;
		annotationMirrors = element.getAnnotationMirrors();

		for (AnnotationMirror mirror : annotationMirrors)
		{

			final String annotationType = mirror.getAnnotationType().toString();

			if(element.getKind().isClass())
			{
				TypeElement elem = (TypeElement) element;
				if(annotationType.equals(JAXB_POJO_ANN))
				{
					context.getPojosToProcess().put(elem.getSimpleName().toString(), elem);
				}
			}
		}

	}

	/**
	 * Check if the set of elements host the researched Java annotations. JAXB
	 * annotations are searched.
	 * @param annotations
	 * @return
	 */
	private boolean hostJAXBAnnotations(Set<? extends TypeElement> annotations) {

		for (TypeElement type : annotations)
		{

			final String typeName = type.getQualifiedName().toString();

			if(typeName.equals(JAXB_POJO_ANN) || typeName.equals(JAXB_POJO_ANN2))
			{

				return true;
			}
		}
		return false;
	}

}
