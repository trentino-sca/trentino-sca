#**********************************************************************************
# Trentino - A C++ based lightweight, non-invasive SCA runtime.
# Copyright 2012 by Siemens AG. All rights reserved.
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
#**********************************************************************************
cmake_minimum_required(VERSION 2.6)
project(PreferenceService)

set(PNAME PreferenceService)
set(${PNAME}_INSTALL_DIR ${PNAME})


if(MSVC90)
	set(3rdpartyDirSuffix x86_windows/vc9)
	elseif(MSVC10)
		set(3rdpartyDirSuffix x86_windows/vc10)
	elseif(CYGWIN)
		set(3rdpartyDirSuffix x86_cygwin)
		execute_process(COMMAND chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party.sh)
		execute_process(COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party.sh ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR})
	else(NOT WIN32)
		set(3rdpartyDirSuffix x86_linux)
		execute_process(COMMAND chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party.sh)
		execute_process(COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party.sh ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR})
	endif()
	
	set(TRENTINO_THIRD_PARTY_DIR ../../../3rdparty/${3rdpartyDirSuffix})


#----------------------------------
# MY_LINK_THIRD_PARTY_LIBRARIES 
#----------------------------------
#The libs to be linked to are expected to be passed as additional arguments after 'target'.
#This arguments have to be uncomplete variable names representing the libs
#The macro will append '_DEBUG' respectively '_RELEASE' to the passed arguments
#in order to produce real variable names that are expected to contain the real lib names.
#EXAMPLE: 
#The call MY_LINK_THIRD_PARTY_LIBRARIES(main Boost_FILESYSTEM_LIBRARY) expects the variables
#'Boost_FILESYSTEM_LIBRARY_DEBUG' (if build type is debug) respectively 
#'Boost_FILESYSTEM_LIBRARY_RELEASE' (if build type is release) to be defined
#----------------------------

macro(MY_CREATE_VALIDATE_GENERATE_INSTALL_TARGET installDir)
if (WIN32)
	set(GEN_INSTALL_COMMAND msbuild INSTALL.vcxproj)
else()
	set(GEN_INSTALL_COMMAND make install)
endif()
add_custom_target([Trengen_Validate_Generate_Install]
COMMAND $ENV{TRENTINO_HOME}/bin/Trengen	-cont ${installDir}
#create a build folder for the generated code
COMMAND ${CMAKE_COMMAND} -E make_directory ${installDir}Gen_Build
COMMAND ${CMAKE_COMMAND} -E make_directory ${installDir}Gen
#build the project using cmake
COMMAND ${CMAKE_COMMAND} -E chdir ${installDir}Gen_Build cmake ../${installDir}Gen
#now install the application: on windows, call msbuild on linux call make
COMMAND ${CMAKE_COMMAND} -E chdir ${installDir}Gen_Build ${GEN_INSTALL_COMMAND}
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/../
VERBATIM
)	

endmacro(MY_CREATE_VALIDATE_GENERATE_INSTALL_TARGET)

##############################################################################

set (DEFAULT_INSTALL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
   set (CMAKE_INSTALL_PREFIX ${DEFAULT_INSTALL_PATH} CACHE STRING "Install path" FORCE)
endif()

##############################################################################
# 								COMPILER OPTIONS  							 #
##############################################################################
if(MSVC)
	add_definitions(-DUNICODE -D_UNICODE)
	add_definitions(/W4)
else()
	add_definitions(-Wall -pedantic)
endif()

##############################################################################
# 							   OUTPUT CONFIGURATION						     #
##############################################################################
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}${CMAKE_SYSTEM_NAME})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}${CMAKE_SYSTEM_NAME})

set(SCAAPI_INCLUDE_DIRS $ENV{TRENTINO_HOME}/include)

#source and header files
FILE (GLOB PreferenceService_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)

FILE (GLOB PreferenceService_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB PreferenceService_SCA_COMPONENT_TYPES *.componentType)
FILE (GLOB PreferenceService_SOURCE_FILES *.cpp)
SET(PreferenceService_SCA_FILES ${PreferenceService_SCA_FILES} ${PreferenceService_SCA_COMPONENT_TYPES})
FILE(GLOB PreferenceService_EXPORTED_HEADERS *Impl.h *Impl.inl)  
#libs
set( PreferenceService_THIRD_PARTY_LIBS 
     PocoFoundationd
     )
	 
set( PreferenceService_CUSTOM_LIBS 
     )
	 
set( PreferenceService_SOURCE_FILES ${PreferenceService_SOURCE_FILES}
						  ${PreferenceService_HEADER_FILES} ${PreferenceService_SCA_FILES})

if (WIN32)
	add_definitions(-DPREFERENCESERVICE_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${PreferenceService_SCA_FILES})
endif()

set(IS_BUILD_TYPE_DEBUG TRUE)
set(IS_BUILD_TYPE_RELEASE TRUE)
if(MSVC_IDE)
	list(FIND CMAKE_CONFIGURATION_TYPES Debug CONF_TYPE)
	if(CONF_TYPE EQUAL -1)
		set(IS_BUILD_TYPE_DEBUG FALSE)
		else()
		set(IS_BUILD_TYPE_RELEASE FALSE)
	endif()

	list(FIND CMAKE_CONFIGURATION_TYPES Release CONF_TYPE)
	list(FIND CMAKE_CONFIGURATION_TYPES RelWithDebInfo CONF_TYPE2)
	list(FIND CMAKE_CONFIGURATION_TYPES MinSizeRel CONF_TYPE3)
	if(CONF_TYPE EQUAL -1 AND CONF_TYPE2 EQUAL -1 AND CONF_TYPE3 EQUAL -1  )
		set(IS_BUILD_TYPE_RELEASE FALSE)
	endif()
else()
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(IS_BUILD_TYPE_RELEASE FALSE)
	else()
		set(IS_BUILD_TYPE_DEBUG FALSE)
	endif()
endif(MSVC_IDE)

if(IS_BUILD_TYPE_DEBUG)
	set(LINK_DIRECTORIES ${TRENTINO_THIRD_PARTY_DIR}/poco/lib/debug) 
endif()
if(IS_BUILD_TYPE_RELEASE)
	set(LINK_DIRECTORIES ${TRENTINO_THIRD_PARTY_DIR}/poco/lib/release) 
endif()
include_directories($ENV{TRENTINO_HOME}/include ${TRENTINO_THIRD_PARTY_DIR}/poco/include ${TRENTINO_THIRD_PARTY_DIR}/boost_1_47/include)
link_directories(${LINK_DIRECTORIES} $ENV{TRENTINO_HOME}/bin)

add_library(PreferenceService SHARED ${PreferenceService_SOURCE_FILES})
set(TrentinoPreferenceService_INSTALL_DIR PreferenceService)
set_target_properties(PreferenceService PROPERTIES OUTPUT_NAME PreferenceService)
install(TARGETS PreferenceService ${DLL_TARGET_KIND} DESTINATION ${TrentinoPreferenceService_INSTALL_DIR}/bin ARCHIVE DESTINATION ${TrentinoPreferenceService_INSTALL_DIR}/lib)
install(DIRECTORY META-INF services DESTINATION ${TrentinoPreferenceService_INSTALL_DIR})
install(FILES ${PreferenceService_EXPORTED_HEADERS} ${PreferenceService_SCA_COMPONENT_TYPES} DESTINATION ${TrentinoPreferenceService_INSTALL_DIR})
FILE (GLOB DEPENDENCY_FILES ${LINK_DIRECTORIES}/*.dll)
#install(FILES ${LINK_DIRECTORIES}/*.dll DESTINATION ${TrentinoPreferenceService_INSTALL_DIR}/bin)
install(FILES ${DEPENDENCY_FILES} DESTINATION ${TrentinoPreferenceService_INSTALL_DIR}/bin)
##############################################################################
#                           CUSTOM TARGET FOR VALIDATING AND GENERATING CODE BY TRENGEN 
##############################################################################
MY_CREATE_VALIDATE_GENERATE_INSTALL_TARGET(${${PNAME}_INSTALL_DIR} )