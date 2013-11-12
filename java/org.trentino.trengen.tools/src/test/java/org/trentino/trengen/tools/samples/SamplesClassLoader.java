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
package org.trentino.trengen.tools.samples;

import java.net.URL;

public final class SamplesClassLoader {
	private SamplesClassLoader () {
	}

	public static URL	 BASICCALCULATOR_CONTRIBUTION	                              = SamplesClassLoader.class.getResource("basiccalculator");
	public static String	BASICCALCULATOR_CONTRIBUTION_STRING	                      = BASICCALCULATOR_CONTRIBUTION.toString().replace("file:", "");

	// used for the integration test of trengen (from the model loader
	// perspective) with sampleContribution (see under resources)
	public static URL	 SAMPLE_CONTRIBUTION	                                      = SamplesClassLoader.class.getResource("SampleContribution");
	public static URL	 SAMPLE_CONTRIBUTION_NOT_VALID	                              = SamplesClassLoader.class
	                                                                                          .getResource("SampleContributionNotValid");
	public static URL	 SAMPLE_CONTRIBUTION_REFERENCE_MODEL_LOADER	                  = SamplesClassLoader.class
	                                                                                          .getResource("modelloader/TrentinoGenModelLoader_SampleContribution.cpp");

	// used for the integration test of trengen (from the model loader
	// perspective) with sampleContribution_compositeByImpl (see under
	// resources)
	public static URL	 SAMPLE_CONTRIBUTION_COMPOSITE_BY_IMPL	                      = SamplesClassLoader.class
	                                                                                          .getResource("SampleContributionCompositeByImpl");
	public static URL	 SAMPLE_CONTRIBUTION_COMPOSITE_BY_IMPL_REFERENCE_MODEL_LOADER	= SamplesClassLoader.class
	                                                                                          .getResource("modelloader/TrentinoGenModelLoader_SampleContribution_CompositeByImplementation.cpp");

	// used for the integration test of trengen (from the model loader
	// perspective) with ScaReferenceExample (see under resources)
	public static URL	 SCA_REFERENCE_EXAMPLE	                                      = SamplesClassLoader.class.getResource("SCAReferenceExample");
	public static URL	 SCA_REFERENCE_EXAMPLE_REFERENCE_MODEL_LOADER	              = SamplesClassLoader.class
	                                                                                          .getResource("modelloader/TrentinoGenModelLoader_SCAReferenceExample.cpp");
}
