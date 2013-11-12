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
project(BasicCalculator)

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



set(SCAAPI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../../../3rdparty/sca_api)
#source and header files
FILE (GLOB BasicCalculator_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)

FILE (GLOB BasicCalculator_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB BasicCalculator_SCA_COMPONENT_TYPES *.componentType)
FILE (GLOB BasicCalculator_SOURCE_FILES *.cpp)
SET(BasicCalculator_SCA_FILES ${BasicCalculator_SCA_FILES} ${BasicCalculator_SCA_COMPONENT_TYPES})
FILE(GLOB BasicCalculator_EXPORTED_HEADERS *Impl.h *Impl.inl)  
#libs
set( BasicCalculator_THIRD_PARTY_LIBS 
     )
	 
set( BasicCalculator_CUSTOM_LIBS 
     )
	 
set( BasicCalculator_SOURCE_FILES ${BasicCalculator_SOURCE_FILES}
						  ${BasicCalculator_HEADER_FILES} ${BasicCalculator_SCA_FILES})

if (WIN32)
	add_definitions(-DBASICCALCULATOR_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${BasicCalculator_SCA_FILES})
endif()

include_directories(${SCAAPI_INCLUDE_DIRS})

add_library(BasicCalculator SHARED ${BasicCalculator_SOURCE_FILES})
set(TrentinoBasicCalculator_INSTALL_DIR BasicCalculator)
set_target_properties(BasicCalculator PROPERTIES OUTPUT_NAME BasicCalculator)
install(TARGETS BasicCalculator ${DLL_TARGET_KIND} DESTINATION ${TrentinoBasicCalculator_INSTALL_DIR})
install(DIRECTORY META-INF services DESTINATION ${TrentinoBasicCalculator_INSTALL_DIR})
install(FILES ${BasicCalculator_EXPORTED_HEADERS} ${BasicCalculator_SCA_COMPONENT_TYPES} DESTINATION ${TrentinoBasicCalculator_INSTALL_DIR})