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

# - this macro expects the variables
#   Runtime_SOURCE_FILES,
#   Runtime_CUSTOM_LIBS,
#   Runtime_THIRD_PARTY_LIBS
#   to be defined before the call
# - this macro expects the variables 
#	${subdirectory}_SOURCE_FILES, 
#	${varPrefix}_CUSTOM_LIBS and,
#	${varPrefix}_THIRD_PARTY_LIBS 
#	to be defined after the call to include()  
macro(MY_INCLUDE_SUBDIRECTORY subdirectory)
	set(varPrefix "Runtime")
	include(${subdirectory}/CMakeLists.txt)
	set(${varPrefix}_SOURCE_FILES ${${varPrefix}_SOURCE_FILES} ${${subdirectory}_SOURCE_FILES})
	set(${varPrefix}_CUSTOM_LIBS ${${varPrefix}_CUSTOM_LIBS} ${${subdirectory}_CUSTOM_LIBS})
	set(${varPrefix}_THIRD_PARTY_LIBS ${${varPrefix}_THIRD_PARTY_LIBS} ${${subdirectory}_THIRD_PARTY_LIBS})	 
endmacro(MY_INCLUDE_SUBDIRECTORY subdirectory)

#source/header files
set ( Runtime_COMMON_FILES
	  TrentinoManagementInterface.h)

set(Runtime_PUBLIC_FILES
	TrentinoManagementInterface.h
	Core/TrentinoCore.h
	Core/TrentinoCoreContributionLoadingSCAModelLoader.h
	Core/TrentinoCoreContributionInfo.h
	Core/TrentinoCoreContributionInfoMacros.h
	Core/TrentinoCoreRuntimeAPI.h
	Core/TrentinoCoreRuntimeAPI.inl
   Core/TrentinoCoreBootstrappingExplicitLinkingInterface.h
	Invocation/TrentinoInvocation.h
	Invocation/TrentinoInvocationGen.h
	Invocation/TrentinoInvocationInvocationContext.h
	Invocation/TrentinoInvocationInvocationContext.inl
	Invocation/TrentinoInvocationInvocationData.h
	Invocation/TrentinoInvocationInvocationData.inl
	Invocation/TrentinoInvocationInvokerBase.h
	ReflectionRuntime/TrentinoReflectionDataMethod.h
	ReflectionRuntime/TrentinoReflectionDataObject.h	
	ReflectionRuntime/TrentinoReflectionHelpersListType.h
	ReflectionRuntime/TrentinoReflectionHelpersListType.inl
	ReflectionRuntime/TrentinoReflectionHelpersListWrapper.h
	ReflectionRuntime/TrentinoReflectionHelpersListWrapper.inl
	ReflectionRuntime/TrentinoReflectionHelpersVariant.h
	ReflectionRuntime/TrentinoReflectionHelpersVariant.inl
	ReflectionRuntime/TrentinoReflectionIncludes.h
	ReflectionRuntime/TrentinoReflectionRegistration.h
	ReflectionRuntime/TrentinoReflectionDataRegistry.h
	RuntimeModel/TrentinoRuntimeModel.h
	RuntimeModel/TrentinoRuntimeModelWireable.h
	RuntimeModel/TrentinoRuntimeModelServiceBase.h
	RuntimeModel/TrentinoRuntimeModelWireBase.h
	RuntimeModel/TrentinoRuntimeModelErrorCode.h
	ServiceRegistry/ServiceRegistry.h
	XML/TrentinoXMLSchema.h
	XML/TrentinoXMLSchemaQName.h
	XML/TrentinoXMLSchemaQName.inl
	Binding/TrentinoBindingBindingHelperBase.h)

#work around since that OASIS namespace use only lower cases, but Trentino use Upper case internally (see Oasis instead of oasis)
set(Runtime_PUBLIC_OASIS
	Oasis/sca/ServiceReference.h
	Oasis/sca/ServiceReference.inl
	Oasis/sca/ServiceProxy.h
	Oasis/sca/ServiceProxy.inl
	Oasis/sca/SCAException.h
	Oasis/sca/SCAException.inl
	Oasis/sca/RefCountingPointer.h
    Oasis/sca/RefCountingPointer.inl
	Oasis/sca/DomainContext.h
	Oasis/sca/ComponentContext.h
	Oasis/sca/ComponentContext.inl
)

FILE(GLOB SCAModel_PUBLIC_FILES SCAModel/*.h SCAModel/*.inl)

#libs
set( Runtime_THIRD_PARTY_LIBS 
     ${loggingLib}
	 Boost_FILESYSTEM_LIBRARY
	 Boost_SYSTEM_LIBRARY
	 Boost_THREAD_LIBRARY
	 Boost_DATE_TIME_LIBRARY)
	 
set( Runtime_CUSTOM_LIBS     	
	 Utils )

set(Runtime_SOURCE_FILES ${Runtime_SOURCE_FILES} 
						 ${Runtime_COMMON_FILES} 
						 ${Runtime_EXAMPLESETUP_FILES}
						 ${Runtime_PUBLIC_FILES}
						 ${SCAModel_PUBLIC_FILES})


MY_INCLUDE_SUBDIRECTORY(Core)
MY_INCLUDE_SUBDIRECTORY(Invocation)
MY_INCLUDE_SUBDIRECTORY(ReflectionRuntime)
MY_INCLUDE_SUBDIRECTORY(RuntimeModel)
MY_INCLUDE_SUBDIRECTORY(SCAModel)
MY_INCLUDE_SUBDIRECTORY(XML)
MY_INCLUDE_SUBDIRECTORY(Binding)
MY_INCLUDE_SUBDIRECTORY(ServiceRegistry)
MY_INCLUDE_SUBDIRECTORY(Oasis)
MY_INCLUDE_SUBDIRECTORY(Discovery)
if(MSVC_IDE)									
	source_group("[Common]" FILES ${Runtime_COMMON_FILES})
	source_group("[Common]\\[Example Setup]" FILES ${Runtime_EXAMPLESETUP_FILES})
	#source_group("[Public]" FILES ${Runtime_PUBLIC_FILES})
	#source_group("[Public]\\[SCAModel]" FILES ${SCAModel_PUBLIC_FILES})
endif()

if(MSVC)
	add_definitions(/EHa)
endif()

if(TRENTINO_LOGGING)
	include_directories(${Log4cplus_INCLUDE_DIRS}
						${Boost_INCLUDE_DIRS}
					    #used to include golbal
						${CMAKE_SOURCE_DIR}/src
                 # ${OpenSlp_INCLUDE_DIRS}
						)
else()
	include_directories(
						${Boost_INCLUDE_DIRS}
						#used to include golbal
						${CMAKE_SOURCE_DIR}/src
                  #${OpenSlp_INCLUDE_DIRS}
						)
endif()

add_library(Runtime SHARED ${Runtime_SOURCE_FILES})

set_target_properties(Runtime PROPERTIES OUTPUT_NAME TrentinoRuntime)
target_link_libraries(Runtime ${Runtime_CUSTOM_LIBS})
MY_LINK_THIRD_PARTY_LIBRARIES(Runtime ${Runtime_THIRD_PARTY_LIBS} )


install( TARGETS Runtime 
		 RUNTIME DESTINATION ${TARGET_DLL_DIR}
		 LIBRARY DESTINATION ${TARGET_LIB_DIR}
		 ARCHIVE DESTINATION ${TARGET_LIB_DIR} )

install(FILES ${SCAModel_PUBLIC_FILES} DESTINATION ${TARGET_INCLUDE_DIR}/Runtime/SCAModel)
foreach(filePath ${Runtime_PUBLIC_FILES})
	get_filename_component(relativePath ${filePath} PATH)
	install(FILES ${filePath} DESTINATION ${TARGET_INCLUDE_DIR}/Runtime/${relativePath})
endforeach()

foreach(filePath ${Runtime_PUBLIC_OASIS})
	get_filename_component(relativePath ${filePath} PATH)
	install(FILES ${filePath} DESTINATION ${TARGET_INCLUDE_DIR}/oasis/sca)
endforeach()

if(CPPCHECK_GENERATE)
add_cppcheck(Runtime ${Runtime_SOURCE_FILES})                     
endif()

if(VERA_GENERATE)
add_vera(Runtime ${Runtime_SOURCE_FILES})                     
endif()
 
