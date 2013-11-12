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
project(GUIDemo)

set(PNAME GUIDemo)
set(${PNAME}_INSTALL_DIR ${PNAME})
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
FILE (GLOB GUIDemo_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)

FILE (GLOB GUIDemo_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB GUIDemo_SCA_COMPONENT_TYPES *.componentType)
FILE (GLOB GUIDemo_SOURCE_FILES *.cpp)
SET(GUIDemo_SCA_FILES ${GUIDemo_SCA_FILES} ${GUIDemo_SCA_COMPONENT_TYPES})
FILE(GLOB GUIDemo_EXPORTED_HEADERS *Impl.h *Impl.inl)  
#libs
set( GUIDemo_THIRD_PARTY_LIBS 
	BThread_QT.lib     
)
	 
set( GUIDemo_CUSTOM_LIBS 
     )
	 
set( GUIDemo_SOURCE_FILES ${GUIDemo_SOURCE_FILES}
						  ${GUIDemo_HEADER_FILES} ${GUIDemo_SCA_FILES})

if (WIN32)
	add_definitions(-DGUIDEMO_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${GUIDemo_SCA_FILES})
endif()

set(LINK_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/ ${CMAKE_CURRENT_SOURCE_DIR}/../Bthread_QT/QTlib) #added by yaot 2013-06-02

include_directories(${SCAAPI_INCLUDE_DIRS})

link_directories(${LINK_DIRECTORIES} ${LIBRARY_OUTPUT_PATH})

add_library(GUIDemo SHARED ${GUIDemo_SOURCE_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME} ${GUIDemo_THIRD_PARTY_LIBS} ${GUIDemo_CUSTOM_LIBS})

set(TrentinoGUIDemo_INSTALL_DIR ${CMAKE_PROJECT_NAME})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${CMAKE_PROJECT_NAME})
install(TARGETS ${CMAKE_PROJECT_NAME} ${DLL_TARGET_KIND} DESTINATION ${TrentinoGUIDemo_INSTALL_DIR})
install(DIRECTORY META-INF services DESTINATION ${TrentinoGUIDemo_INSTALL_DIR})
install(FILES ${GUIDemo_EXPORTED_HEADERS} ${GUIDemo_SCA_COMPONENT_TYPES} DESTINATION ${TrentinoGUIDemo_INSTALL_DIR})
##############################################################################
#                           CUSTOM TARGET FOR VALIDATING AND GENERATING CODE BY TRENGEN 
##############################################################################
MY_CREATE_VALIDATE_GENERATE_INSTALL_TARGET(${${PNAME}_INSTALL_DIR} )