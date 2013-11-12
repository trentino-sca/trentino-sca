# ***********************************************************************************
# Trentino - A C++ based lightweight, non-invasive SCA runtime.
# Copyright (C) Siemens AG, 2012
# All Rights Reserved
# http://trentino.sourceforge.net/
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
# ***********************************************************************************
project([Public])

set(ALL_PUBLIC_UTILS_FILES
	./../Utils/TrentinoUtilsTypeName.h
	./../Utils/TrentinoUtilsTypeName.inl
	./../Utils/TrentinoUtilsTypeNameBase.h
	./../Utils/TrentinoUtilsTypeNameBase.inl
	)
	
set(ALL_PUBLIC_RUNTIME_FILES	
	./../Runtime/TrentinoManagementInterface.h
	./../Runtime/Core/TrentinoCore.h
	./../Runtime/Core/TrentinoCoreContributionInfo.h
	./../Runtime/Core/TrentinoCoreContributionInfoMacros.h
	./../Runtime/Core/TrentinoCoreContributionLoadingSCAModelLoader.h
	./../Runtime/Core/TrentinoCoreRuntimeAPI.h
	./../Runtime/Core/TrentinoCoreRuntimeAPI.inl
	./../Runtime/Core/TrentinoCoreBootstrappingExplicitLinkingInterface.h
	./../Runtime/Invocation/TrentinoInvocation.h
	./../Runtime/Invocation/TrentinoInvocationInvocationContext.h
	./../Runtime/Invocation/TrentinoInvocationInvocationContext.inl
	./../Runtime/Invocation/TrentinoInvocationInvocationData.h
	./../Runtime/Invocation/TrentinoInvocationInvocationData.inl
	./../Runtime/Invocation/TrentinoInvocationInvokerBase.h
	./../Runtime/Invocation/TrentinoInvocationServiceInvocationWrapperBase.h
	./../Runtime/ReflectionRuntime/TrentinoReflectionDataMethod.h
	./../Runtime/ReflectionRuntime/TrentinoReflectionDataObject.h	
	./../Runtime/ReflectionRuntime/TrentinoReflectionHelpersListType.h
	./../Runtime/ReflectionRuntime/TrentinoReflectionHelpersListType.inl
	./../Runtime/ReflectionRuntime/TrentinoReflectionHelpersListWrapper.h
	./../Runtime/ReflectionRuntime/TrentinoReflectionHelpersListWrapper.inl
	./../Runtime/ReflectionRuntime/TrentinoReflectionHelpersVariant.h
	./../Runtime/ReflectionRuntime/TrentinoReflectionHelpersVariant.inl
	./../Runtime/ReflectionRuntime/TrentinoReflectionIncludes.h
	./../Runtime/ReflectionRuntime/TrentinoReflectionRegistration.h
	./../Runtime/ReflectionRuntime/TrentinoReflectionDataRegistry.h
	./../Runtime/RuntimeModel/TrentinoRuntimeModel.h
	./../Runtime/RuntimeModel/TrentinoRuntimeModelWireable.h
	./../Runtime/RuntimeModel/TrentinoRuntimeModelServiceBase.h
	./../Runtime/RuntimeModel/TrentinoRuntimeModelWireBase.h
	./../Runtime/RuntimeModel/TrentinoRuntimeModelErrorCode.h
	./../Runtime/ServiceRegistry/ServiceRegistry.h
	./../Runtime/XML/TrentinoXMLSchema.h
	./../Runtime/XML/TrentinoXMLSchemaQName.h
	./../Runtime/XML/TrentinoXMLSchemaQName.inl
	./../Runtime/Binding/TrentinoBinding.h
	./../Runtime/Binding/TrentinoBindingBindingHelperBase.h
	./../Runtime/Oasis/sca/ServiceReference.h
	./../Runtime/Oasis/sca/ServiceProxy.h
	./../Runtime/Oasis/sca/SCAException.h
	./../Runtime/Oasis/sca/RefCountingPointer.h
	./../Runtime/Oasis/sca/DomainContext.h
	./../Runtime/Oasis/sca/ComponentContext.h
	)

	
FILE(GLOB ALL_PUBLIC_SCAModel_FILES ./../Runtime/SCAModel/*.h ./../Runtime/SCAModel/*.inl)
	
set(ALL_PUBLIC_FILES 	
	${ALL_PUBLIC_UTILS_FILES} 
	${ALL_PUBLIC_RUNTIME_FILES}
	${ALL_PUBLIC_SCAModel_FILES}
	)
	
	source_group("[Includes]" FILES ${MUST_INCLUDE_FILE})
	source_group("[Includes]\\[Utils]" FILES ${ALL_PUBLIC_UTILS_FILES})
	source_group("[Includes]\\[Runtime]" FILES ${ALL_PUBLIC_RUNTIME_FILES})
	source_group("[Includes]\\[SCAModel]" FILES ${ALL_PUBLIC_SCAModel_FILES})
		
	add_custom_target([Public] SOURCES ${ALL_PUBLIC_FILES})

