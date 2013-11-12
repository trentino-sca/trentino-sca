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
project(BasicPrinterClient)
##############################################################################
# 									MACROS									 #
##############################################################################

execute_process(COMMAND $ENV{TRENTINO_HOME}/bin/trengen	-gencppitf ${CMAKE_CURRENT_SOURCE_DIR}/services/TrentinoExampleBasicPrinterClient.tidl.properties  -inc BasicPrinterClientGlobal.h
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
FILE (GLOB BasicPrinterClient_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)

FILE (GLOB BasicPrinterClient_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB BasicPrinterClient_SCA_COMPONENT_TYPES *.componentType)
FILE (GLOB BasicPrinterClient_SOURCE_FILES *.cpp services/*.cpp)
SET(BasicPrinterClient_SCA_FILES ${BasicPrinterClient_SCA_FILES} ${BasicPrinterClient_SCA_COMPONENT_TYPES})
FILE(GLOB BasicPrinterClient_EXPORTED_HEADERS *Impl.h *Impl.inl)  
#libs
set( BasicPrinterClient_THIRD_PARTY_LIBS 
     )
	 
set( BasicPrinterClient_CUSTOM_LIBS 
     )
	 
set( BasicPrinterClient_SOURCE_FILES ${BasicPrinterClient_SOURCE_FILES}
						  ${BasicPrinterClient_HEADER_FILES} ${BasicPrinterClient_SCA_FILES})

if (WIN32)
	add_definitions(-DBasicPrinterClient_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${BasicPrinterClient_SCA_FILES})
endif()

include_directories(${SCAAPI_INCLUDE_DIRS} ${BOOST_INCLUDE_DIRS})

add_library(BasicPrinterClient SHARED ${BasicPrinterClient_SOURCE_FILES})
set(TrentinoBasicPrinterClient_INSTALL_DIR BasicPrinterClient)
set_target_properties(BasicPrinterClient PROPERTIES OUTPUT_NAME BasicPrinterClient)
install(TARGETS BasicPrinterClient ${DLL_TARGET_KIND} DESTINATION ${TrentinoBasicPrinterClient_INSTALL_DIR})
install(DIRECTORY META-INF services DESTINATION ${TrentinoBasicPrinterClient_INSTALL_DIR})
install(FILES ${BasicPrinterClient_EXPORTED_HEADERS} ${BasicPrinterClient_SCA_COMPONENT_TYPES} DESTINATION ${TrentinoBasicPrinterClient_INSTALL_DIR})


##############################################################################
#                           CUSTOM TARGET FOR VALIDATING AND GENERATING CODE BY TRENGEN#
##############################################################################
MY_CREATE_VALIDATE_GENERATE_INSTALL_TARGET(BasicPrinterClient)