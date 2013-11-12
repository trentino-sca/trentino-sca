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
cmake_minimum_required(VERSION 2.8)
project(DiscoveryTestServer)
##############################################################################
# 									MACROS									 #
##############################################################################

execute_process(COMMAND $ENV{TRENTINO_HOME}/bin/trengen	-gencppitf ${CMAKE_CURRENT_SOURCE_DIR}/services/DiscoveryTestServer.tidl.properties  -inc DiscoveryTestServerGlobal.h
				WORKING_DIRECTOR ${CMAKE_CURRENT_SOURCE_DIR}
				RESULT_VARIABLE return_code
				OUTPUT_VARIABLE output 
				ERROR_VARIABLE err
				OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_STRIP_TRAILING_WHITESPACE)
				
if(NOT(${return_code} EQUAL 0))
	message(SEND_ERROR "Error: CPP Interface could not be generated")
	message(SEND_ERROR ${err}
	)
endif()

#----------------------------------
# MY_CREATE_VALIDATE_GENERATE_INSTALL_TARGET 
#----------------------------------
macro(MY_CREATE_VALIDATE_GENERATE_INSTALL_TARGET installDir)
if (WIN32)
	set(GEN_INSTALL_COMMAND msbuild INSTALL.vcxproj)
else()
	set(GEN_INSTALL_COMMAND make install)
endif()
add_custom_target([Trengen_Validate_Generate_Install]
COMMAND Trengen	-cont ${installDir}
#create a build folder for the generated code
COMMAND ${CMAKE_COMMAND} -E make_directory ${installDir}Gen_Build
#build the project using cmake
COMMAND ${CMAKE_COMMAND} -E chdir ${installDir}Gen_Build cmake ../${installDir}Gen
#now install the application: on windows, call msbuild on linux call make
COMMAND ${CMAKE_COMMAND} -E chdir ${installDir}Gen_Build ${GEN_INSTALL_COMMAND}
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/../
VERBATIM
)	
endmacro(MY_CREATE_VALIDATE_GENERATE_INSTALL_TARGET)

set (TRENTINO_RUNTIME_DIR $ENV{TRENTINO_HOME})
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



set(SCAAPI_INCLUDE_DIRS ${TRENTINO_RUNTIME_DIR}/include)
set(BOOST_INCLUDE_DIRS ${TRENTINO_RUNTIME_DIR}/include)
#source and header files
FILE (GLOB DiscoveryTestServer_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)

FILE (GLOB DiscoveryTestServer_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB DiscoveryTestServer_SCA_COMPONENT_TYPES *.componentType)
FILE (GLOB DiscoveryTestServer_SOURCE_FILES *.cpp services/*.cpp)
SET(DiscoveryTestServer_SCA_FILES ${DiscoveryTestServer_SCA_FILES} ${DiscoveryTestServer_SCA_COMPONENT_TYPES})
FILE(GLOB DiscoveryTestServer_EXPORTED_HEADERS *Impl.h *Impl.inl *Impl2.h *Impl2.inl)  
#libs
set( DiscoveryTestServer_THIRD_PARTY_LIBS 
     )
	 
set( DiscoveryTestServer_CUSTOM_LIBS 
     )
	 
set( DiscoveryTestServer_SOURCE_FILES ${DiscoveryTestServer_SOURCE_FILES}
						  ${DiscoveryTestServer_HEADER_FILES} ${DiscoveryTestServer_SCA_FILES})

if (WIN32)
	add_definitions(-DDISCOVERYTESTSERVER_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${DiscoveryTestServer_SCA_FILES})
endif()

include_directories(${SCAAPI_INCLUDE_DIRS} ${BOOST_INCLUDE_DIRS})

add_library(DiscoveryTestServer SHARED ${DiscoveryTestServer_SOURCE_FILES})
set(TrentinoDiscoveryTestServer_INSTALL_DIR DiscoveryTestServer)
set_target_properties(DiscoveryTestServer PROPERTIES OUTPUT_NAME DiscoveryTestServer)
install(TARGETS DiscoveryTestServer ${DLL_TARGET_KIND} DESTINATION ${TrentinoDiscoveryTestServer_INSTALL_DIR})
install(DIRECTORY META-INF services DESTINATION ${TrentinoDiscoveryTestServer_INSTALL_DIR})
install(FILES ${DiscoveryTestServer_EXPORTED_HEADERS} ${DiscoveryTestServer_SCA_COMPONENT_TYPES} DESTINATION ${TrentinoDiscoveryTestServer_INSTALL_DIR})


##############################################################################
#                           CUSTOM TARGET FOR VALIDATING AND GENERATING CODE BY TRENGEN#
##############################################################################
MY_CREATE_VALIDATE_GENERATE_INSTALL_TARGET(DiscoveryTestServer)