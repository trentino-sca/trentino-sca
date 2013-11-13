# ***********************************************************************************
# Trentino - A C++ based lightweight, non-invasive SCA runtime.
# Copyright (C) Siemens AG, 2012
# All Rights Copy
# http://trentino.sourceforge.net/TARGET_TRENTINO_DIR
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; opensl
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

cmake_minimum_required(VERSION 2.8.4)
project(BindingThrift)

set(TRENTINO_RUNTIME_DIR $ENV{TRENTINO_HOME})

##############################################################################
#                                Project Include
##############################################################################



##############################################################################
#                                CMAKE OPTIONS                               #
##############################################################################
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

##############################################################################
#                               CUSTOM OPTIONS                               #
##############################################################################

set (DEFAULT_INSTALL_PATH ${PROJECT_SOURCE_DIR}/../../../../Binaries)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
   set (CMAKE_INSTALL_PREFIX ${DEFAULT_INSTALL_PATH} CACHE STRING "Install path" FORCE)
endif()
		
	if(MSVC90)
		set(3rdpartyDirSuffix x86_windows/vc9)
	elseif(MSVC10)
		set(3rdpartyDirSuffix x86_windows/vc10)
	elseif(CYGWIN)
		set(3rdpartyDirSuffix x86_cygwin)
	else(NOT WIN32)
		set(3rdpartyDirSuffix x86_linux)
	endif()
set(TRENTINO_SOURCE_DIR ${PROJECT_SOURCE_DIR}/..)
set(TRENTINO_THIRD_PARTY_DIR ../../../3rdparty/${3rdpartyDirSuffix} CACHE PATH  
			"path to the directory containing third party artifacts" )

set(TRENTINO_THIRD_PARTY_SRC_DIR ../../../3rdparty/src CACHE PATH  
			"path to the directory containing third party source code" )		
set (THRIFT_INCLUDE_DIR ${TRENTINO_THIRD_PARTY_SRC_DIR}/thrift-0.9.1/lib/cpp/src)

set (MYBoost_INCLUDE_DIRS ${TRENTINO_THIRD_PARTY_DIR}/boost_1_47/include)
set (MYBoost_LIB_DIRS ${TRENTINO_THIRD_PARTY_DIR}/boost_1_47/lib/$(Configuration))
			
if(WIN32)
	set(TRENTINO_WIN32_WINNT "0x0502" CACHE STRING 
		"possible values: 0x0500 (Win 2000), 0x0501 (Win XP), 0x0600 (Win Vista), 0x0502 (Win Server 2003), 0x0601 (Win 7)")
endif()

option(TRENTINO_TESTING "build test projects?" ON)

#Enable CTests testing
if(TRENTINO_TESTING)
    ENABLE_TESTING()
endif()

##############################################################################
# 								COMPILER OPTIONS  							 #
##############################################################################
if(MSVC)
	add_definitions(/W4)
	add_definitions(/wd4251)
	add_definitions(/wd4275)
else()
	add_definitions(-Wall -pedantic -Wno-variadic-macros -Wno-unknown-pragmas -Wno-long-long)
endif()

#add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DBOOST_ALL_DYN_LINK)



##############################################################################
# 							   OUTPUT CONFIGURATION						     #
##############################################################################
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}${CMAKE_SYSTEM_NAME})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}${CMAKE_SYSTEM_NAME})

##############################################################################
#                           PROJECT SUBDIRECTORIES                           #
##############################################################################
add_subdirectory(server)
add_subdirectory(thrift)
if(WIN32)
	add_definitions(-DTHRIFTBINDING_EXPORTS)
endif()

set(S_TARGET_ROOT_DIR ${TRENTINO_RUNTIME_DIR}/Bindings/Thrift)
install(DIRECTORY META-INF DESTINATION ${S_TARGET_ROOT_DIR})
install(DIRECTORY conf DESTINATION ${S_TARGET_ROOT_DIR})