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
package org.trentino.trengen.tools.bindingframework;

import java.io.File;

import org.trentino.trengen.tools.generation.cmake.ContextCmake;
import org.trentino.trengen.tools.generation.modelloader.SCAModelToSCAMirrorModelConverter;
import org.trentino.trengen.tools.generation.proxieswrappers.ContextProxiesWrappers;
import org.trentino.trengen.tools.generation.reflection.ContextReflection;
import org.trentino.trengen.tools.scavalidation.ContributionTypeWrapper;

/**
 * @author z002ttbb
 */
public class BindingCodeGeneratorData {

	private ContributionTypeWrapper	          contributionTypeWrapper;
	private ContextProxiesWrappers	          contextProxyWrapper;
	private ContextCmake	                  contextCMake;
	private File	                          generationDirectory;
	private String	                          contributionName;
	private SCAModelToSCAMirrorModelConverter	converter;
	private ContextReflection	              contextReflection;

	/**
	 * @param contributionTypeWrapper
	 * @param contextProxyWrapper
	 * @param contextCMake
	 * @param generationDirectory
	 * @param contributionName
	 */
	public BindingCodeGeneratorData (final ContributionTypeWrapper contributionTypeWrapper, final ContextProxiesWrappers contextProxyWrapper,
	        final ContextCmake contextCMake, final File generationDirectory, final String contributionName) {
		this.contributionTypeWrapper = contributionTypeWrapper;
		this.contextProxyWrapper = contextProxyWrapper;
		this.contextCMake = contextCMake;
		this.generationDirectory = generationDirectory;
		this.contributionName = contributionName;
	}

	public final ContributionTypeWrapper getContributionTypeWrapper() {
		return contributionTypeWrapper;
	}

	public final void setContributionTypeWrapper(final ContributionTypeWrapper contributionTypeWrapper) {
		this.contributionTypeWrapper = contributionTypeWrapper;
	}

	public final ContextProxiesWrappers getContextProxyWrapper() {
		return contextProxyWrapper;
	}

	public final void setContextProxyWrapper(final ContextProxiesWrappers contextProxyWrapper) {
		this.contextProxyWrapper = contextProxyWrapper;
	}

	public final ContextCmake getContextCMake() {
		return contextCMake;
	}

	public final void setContextCMake(final ContextCmake contextCMake) {
		this.contextCMake = contextCMake;
	}

	public final File getGenerationDirectory() {
		return generationDirectory;
	}

	public final void setGenerationDirectory(final File generationDirectory) {
		this.generationDirectory = generationDirectory;
	}

	public final String getContributionName() {
		return contributionName;
	}

	public final void setContributionName(final String contributionName) {
		this.contributionName = contributionName;
	}

	/**
	 * @param converter
	 */
	public final void setConverter(final SCAModelToSCAMirrorModelConverter converter) {
		this.converter = converter;

	}

	public final SCAModelToSCAMirrorModelConverter getConverter() {
		return converter;
	}

	/**
	 * @param contextReflection
	 */
	public final void setContextReflection(final ContextReflection contextReflection) {
		this.contextReflection = contextReflection;
	}

	public final ContextReflection getContextReflection() {
		return contextReflection;
	}

}
