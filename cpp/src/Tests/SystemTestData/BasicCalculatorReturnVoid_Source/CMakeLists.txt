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
project(BasicCalculatorReturnVoid)

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
FILE (GLOB BasicCalculatorReturnVoid_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)

FILE (GLOB BasicCalculatorReturnVoid_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB BasicCalculatorReturnVoid_SCA_COMPONENT_TYPES *.componentType)
FILE (GLOB BasicCalculatorReturnVoid_SOURCE_FILES *.cpp)
SET(BasicCalculatorReturnVoid_SCA_FILES ${BasicCalculatorReturnVoid_SCA_FILES} ${BasicCalculatorReturnVoid_SCA_COMPONENT_TYPES})
FILE(GLOB BasicCalculatorReturnVoid_EXPORTED_HEADERS *Impl.h *Impl.inl)  
#libs
set( BasicCalculatorReturnVoid_THIRD_PARTY_LIBS 
     )
	 
set( BasicCalculatorReturnVoid_CUSTOM_LIBS 
     )
	 
set( BasicCalculatorReturnVoid_SOURCE_FILES ${BasicCalculatorReturnVoid_SOURCE_FILES}
						  ${BasicCalculatorReturnVoid_HEADER_FILES} ${BasicCalculatorReturnVoid_SCA_FILES})

if (WIN32)
	add_definitions(-DBASICCALCULATORRETURNVOID_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${BasicCalculatorReturnVoid_SCA_FILES})
endif()

include_directories(${SCAAPI_INCLUDE_DIRS})
include_directories(D:/TrentinoInstallations/trentino_x86_windows_0.2-pa/include/3rdparty/sca_api)

add_library(BasicCalculatorReturnVoid SHARED ${BasicCalculatorReturnVoid_SOURCE_FILES})
set(TrentinoBasicCalculatorReturnVoid_INSTALL_DIR BasicCalculatorReturnVoid)
set_target_properties(BasicCalculatorReturnVoid PROPERTIES OUTPUT_NAME BasicCalculatorReturnVoid)
install(TARGETS BasicCalculatorReturnVoid ${DLL_TARGET_KIND} DESTINATION ${TrentinoBasicCalculatorReturnVoid_INSTALL_DIR})
install(DIRECTORY META-INF services DESTINATION ${TrentinoBasicCalculatorReturnVoid_INSTALL_DIR})
install(FILES ${BasicCalculatorReturnVoid_EXPORTED_HEADERS} ${BasicCalculatorReturnVoid_SCA_COMPONENT_TYPES} DESTINATION ${TrentinoBasicCalculatorReturnVoid_INSTALL_DIR})