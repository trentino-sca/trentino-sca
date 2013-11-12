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
cmake_minimum_required(VERSION 2.6)
project(HelloWorldRemote)

set(PNAME HelloWorldRemote)
##############################################################################
# 									MACROS									 #
##############################################################################

execute_process(COMMAND $ENV{TRENTINO_HOME}/bin/trengen	-gencppitf ${CMAKE_CURRENT_SOURCE_DIR}/TrentinoExampleHelloWorldRemoteHelloWorld.tidl.properties
				WORKING_DIRECTOR ${CMAKE_CURRENT_SOURCE_DIR}
				RESULT_VARIABLE return_code
				OUTPUT_VARIABLE output 
				ERROR_VARIABLE err
				OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_STRIP_TRAILING_WHITESPACE)
				
if(NOT(${return_code} EQUAL 0))
	message(SEND_ERROR "Error: CPP Interface could not be generated")
	message(SEND_ERROR ${err} )
endif()

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
FILE (GLOB ${PNAME}_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)

FILE (GLOB ${PNAME}_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB ${PNAME}_BINDING_SCA_FILES *.tidl.properties *.java)

FILE (GLOB ${PNAME}_SCA_COMPONENT_TYPES *.componentType )
FILE (GLOB ${PNAME}_SOURCE_FILES *.cpp services/*.cpp)
SET(${PNAME}_SCA_FILES ${${PNAME}_SCA_FILES} ${${PNAME}_SCA_COMPONENT_TYPES})
FILE(GLOB ${PNAME}_EXPORTED_HEADERS *.h *.inl)  
#libs
set( ${PNAME}_THIRD_PARTY_LIBS 
     )
	 
set( ${PNAME}_CUSTOM_LIBS 
     )
	 
set( ${PNAME}_SOURCE_FILES ${${PNAME}_SOURCE_FILES}
						  ${${PNAME}_HEADER_FILES} ${${PNAME}_SCA_FILES})

if (WIN32)
	add_definitions(-DHELLOWORLDREMOTE_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${${PNAME}_SCA_FILES})
endif()

include_directories(${SCAAPI_INCLUDE_DIRS} ${BOOST_INCLUDE_DIRS})

add_library(${PNAME} SHARED ${${PNAME}_SOURCE_FILES})
set(${PNAME}_INSTALL_DIR ${PNAME})
set_target_properties(${PNAME} PROPERTIES OUTPUT_NAME ${PNAME})
install(TARGETS ${PNAME} RUNTIME DESTINATION ${${PNAME}_INSTALL_DIR}
                         LIBRARY DESTINATION ${${PNAME}_INSTALL_DIR}
						 ARCHIVE DESTINATION ${${PNAME}_INSTALL_DIR})
install(DIRECTORY META-INF DESTINATION ${${PNAME}_INSTALL_DIR})
install(FILES ${${PNAME}_EXPORTED_HEADERS} ${${PNAME}_BINDING_SCA_FILES} ${${PNAME}_SCA_COMPONENT_TYPES} DESTINATION ${${PNAME}_INSTALL_DIR})



##############################################################################
#                           CUSTOM TARGET FOR VALIDATING AND GENERATING CODE BY TRENGEN#
##############################################################################
MY_CREATE_VALIDATE_GENERATE_INSTALL_TARGET(${${PNAME}_INSTALL_DIR} )