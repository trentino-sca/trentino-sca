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
project(BasicCalculatorRemoteStandAloneClient)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}${CMAKE_SYSTEM_NAME})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}${CMAKE_SYSTEM_NAME} )
add_definitions(-DSTAND_ALONE_CLIENT_EXPORT)
add_subdirectory(../BasicCalculatorRemoteClientGen ./ )

set(TRENTINO_RUNTIME_DIR $ENV{TRENTINO_HOME})
set(TRENTINO_LIB_DIR ${TRENTINO_RUNTIME_DIR}/lib)

set(MPName BasicCalculatorRemoteStandAloneClient)
#header files
FILE(GLOB ${MPName}HEADER_FILES *.h *.inl)	  

#source files
FILE(GLOB ${MPName}SOURCE_FILES *.cpp)

set (${MPName}SOURCE_FILES
	  ${${MPName}HEADER_FILES} ${${MPName}SOURCE_FILES})
set( ${MPName}_CUSTOM_LIBS
     BasicCalculatorRemoteClientGen)

include_directories(${BasicCalculatorRemoteClientGen_inc_dirs} ../BasicCalculatorRemoteClientGen ../../../../3rdparty/x86_windows/vc10/boost_1_44/include)
link_directories(${BasicCalculatorRemoteClientGen_link_dirs})
add_executable(${MPName} ${${MPName}SOURCE_FILES})
set_target_properties(${MPName} PROPERTIES OUTPUT_NAME ${MPName})
target_link_libraries(${MPName} ${${MPName}_CUSTOM_LIBS})
install(TARGETS ${MPName}  ${DLL_TARGET_KIND} DESTINATION ${MY_GEN_INSTALL_DIR}/META-INF ARCHIVE DESTINATION ${TARGET_LIB_DIR})

