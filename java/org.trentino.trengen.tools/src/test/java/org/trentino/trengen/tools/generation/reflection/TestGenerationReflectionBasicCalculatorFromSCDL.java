package org.trentino.trengen.tools.generation.reflection;

import java.io.File;
import java.io.IOException;

import org.apache.log4j.Logger;
import org.junit.Test;
import org.trentino.trengen.TrengenException;
import org.trentino.trengen.tools.generation.CPPModelProvider;
import org.trentino.trengen.tools.generation.modelloader.SCAModelToSCAMirrorModelConverter;
import org.trentino.trengen.tools.samples.SamplesClassLoader;
import org.trentino.trengen.tools.scavalidation.ConformanceManagerCppImplArtifactsEclipseCDT;
import org.trentino.trengen.tools.scavalidation.ContributionTypeWrapper;
import org.trentino.trengen.tools.scavalidation.ScaValidationManager;
import org.trentino.trengen.tools.trengen.Trengen;
import org.trentino.trengen.tools.trengen.TrentinoTest;

public class TestGenerationReflectionBasicCalculatorFromSCDL extends TrentinoTest {

	protected static final Logger	                            logger	                                  = Logger.getLogger(TestGenerationReflectionBasicCalculatorFromSCDL.class);
	private static ConformanceManagerCppImplArtifactsEclipseCDT	conformanceManagerCppImplArtifactsEclipse	= new ConformanceManagerCppImplArtifactsEclipseCDT();

	@Test()
	public void dummyTest() throws IOException, Exception {
		System.out.println(SamplesClassLoader.BASICCALCULATOR_CONTRIBUTION);
		File outputDir = new File(".\\target\\exampleReflection");
		outputDir.mkdirs();
		File[] files = outputDir.listFiles();
		for (File f : files)
		{
			f.delete();
		}
		ContributionTypeWrapper createContributonTypeWrapper = createContributonTypeWrapper();
		Trengen.getInstance().setContributionTypeWrapper(createContributonTypeWrapper);
		ConformanceManagerCppImplArtifactsEclipseCDT conformanceManagerCppImplArtifactsEclipse = new ConformanceManagerCppImplArtifactsEclipseCDT();
		SCAModelToSCAMirrorModelConverter converter = new SCAModelToSCAMirrorModelConverter(new CPPModelProvider(
		        conformanceManagerCppImplArtifactsEclipse));
		ContextReflection context = new ContextReflection(converter);
		context.setOutputDir(outputDir);
		ReflectionGenerator gen = new ReflectionGenerator(context);

		gen.generate();

	}

	private ContributionTypeWrapper createContributonTypeWrapper() throws IOException, Exception {
		Trengen.initInstance("-cont", new File(SamplesClassLoader.BASICCALCULATOR_CONTRIBUTION_STRING).getCanonicalPath());
		Trengen.getInstance().setScaValidationFolder(new File(SamplesClassLoader.BASICCALCULATOR_CONTRIBUTION_STRING));
		// Trengen.setContributionFolder(new File(SamplesClassLoader.BASICCALCULATOR_CONTRIBUTION_STRING));

		ScaValidationManager scaValidationManager = new ScaValidationManager(conformanceManagerCppImplArtifactsEclipse);
		// public static ContributionTypeWrapper contributionTypeWrapper = new
		// ContributionTypeWrapper();
		ContributionTypeWrapper contributionTypeWrapper = null;
		try
		{
			contributionTypeWrapper = scaValidationManager.validate(Trengen.getScaValidationFolder(), Trengen.getScaValidationFolder().get(0));
		} catch (Exception e)
		{
			e.printStackTrace();
		}
		return contributionTypeWrapper;
	}
}
