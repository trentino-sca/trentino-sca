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
project(BasicCalculatorWithLifeCycle)
set (PName BasicCalculatorWithLifeCycle)
##############################################################################
# 									MACROS									 #
##############################################################################

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
COMMAND ${CMAKE_COMMAND} -E chdir ${installDir}Gen_Build cmake -G "Visual Studio 10" ../${installDir}Gen
#now install the application: on windows, call msbuild on linux call make
COMMAND ${CMAKE_COMMAND} -E chdir ${installDir}Gen_Build ${GEN_INSTALL_COMMAND}
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/../
VERBATIM
)	
endmacro(MY_CREATE_VALIDATE_GENERATE_INSTALL_TARGET)

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
FILE (GLOB ${PName}_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)

FILE (GLOB ${PName}_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB ${PName}_SCA_COMPONENT_TYPES *.componentType)
FILE (GLOB ${PName}_SOURCE_FILES *.cpp)
SET(${PName}_SCA_FILES ${${PName}_SCA_FILES} ${${PName}_SCA_COMPONENT_TYPES})
FILE(GLOB ${PName}_EXPORTED_HEADERS *Impl.h *Impl.inl)  
#libs
set( ${PName}_THIRD_PARTY_LIBS 
     )
	 
set( ${PName}_CUSTOM_LIBS 
     )
	 
set( ${PName}_SOURCE_FILES ${${PName}_SOURCE_FILES}
						  ${${PName}_HEADER_FILES} ${${PName}_SCA_FILES})

if (WIN32)
	add_definitions(-DBASICCALCULATOR_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${${PName}_SCA_FILES})
endif()

include_directories()

add_library(${PName} SHARED ${${PName}_SOURCE_FILES})
set(Trentino${PName}_INSTALL_DIR ${PName})
set_target_properties(${PName} PROPERTIES OUTPUT_NAME ${PName})
install(TARGETS ${PName} ${DLL_TARGET_KIND} DESTINATION ${Trentino${PName}_INSTALL_DIR})
install(DIRECTORY META-INF services DESTINATION ${Trentino${PName}_INSTALL_DIR})
install(FILES ${${PName}_EXPORTED_HEADERS} ${${PName}_SCA_COMPONENT_TYPES} DESTINATION ${Trentino${PName}_INSTALL_DIR})


##############################################################################
#                           CUSTOM TARGET FOR VALIDATING AND GENERATING CODE BY TRENGEN#
##############################################################################
MY_CREATE_VALIDATE_GENERATE_INSTALL_TARGET(${PName})