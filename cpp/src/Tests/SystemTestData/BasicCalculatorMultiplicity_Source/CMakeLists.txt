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
project(BasicCalculatorMultiplicity)

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
FILE (GLOB BasicCalculatorMultiplicity_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)

FILE (GLOB BasicCalculatorMultiplicity_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB BasicCalculatorMultiplicity_SCA_COMPONENT_TYPES *.componentType)
FILE (GLOB BasicCalculatorMultiplicity_SOURCE_FILES *.cpp)
SET(BasicCalculatorMultiplicity_SCA_FILES ${BasicCalculatorMultiplicity_SCA_FILES} ${BasicCalculatorMultiplicity_SCA_COMPONENT_TYPES})
FILE(GLOB BasicCalculatorMultiplicity_EXPORTED_HEADERS *Impl.h *Impl.inl)  
#libs
set( BasicCalculatorMultiplicity_THIRD_PARTY_LIBS 
     )
	 
set( BasicCalculatorMultiplicity_CUSTOM_LIBS 
     )
	 
set( BasicCalculatorMultiplicity_SOURCE_FILES ${BasicCalculatorMultiplicity_SOURCE_FILES}
						  ${BasicCalculatorMultiplicity_HEADER_FILES} ${BasicCalculatorMultiplicity_SCA_FILES})

if (WIN32)
	add_definitions(-DBASICCALCULATOR_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${BasicCalculatorMultiplicity_SCA_FILES})
endif()

include_directories(${SCAAPI_INCLUDE_DIRS})

add_library(BasicCalculatorMultiplicity SHARED ${BasicCalculatorMultiplicity_SOURCE_FILES})
set(TrentinoBasicCalculatorMultiplicity_INSTALL_DIR BasicCalculatorMultiplicity)
set_target_properties(BasicCalculatorMultiplicity PROPERTIES OUTPUT_NAME BasicCalculatorMultiplicity)
install(TARGETS BasicCalculatorMultiplicity ${DLL_TARGET_KIND} DESTINATION ${TrentinoBasicCalculatorMultiplicity_INSTALL_DIR})
install(DIRECTORY META-INF services DESTINATION ${TrentinoBasicCalculatorMultiplicity_INSTALL_DIR})
install(FILES ${BasicCalculatorMultiplicity_EXPORTED_HEADERS} ${BasicCalculatorMultiplicity_SCA_COMPONENT_TYPES} DESTINATION ${TrentinoBasicCalculatorMultiplicity_INSTALL_DIR})