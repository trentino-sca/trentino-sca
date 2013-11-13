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
cmake_minimum_required(VERSION 2.8.4)
project(ccp)


if(NOT DEFINED THRIFT_CPP_HEADER_DIR)
    message(SEND_ERROR "Thrift header directory not provided. Please provide it using option -D THRIFT_CPP_HEADER_DIR=<value> in CMake command")
else()
    message("Thrift header directory is: "${THRIFT_CPP_HEADER_DIR})
endif()


if(NOT DEFINED THRIFT_CPP_LIB_DIR)
    message(SEND_ERROR "Thrift library directory not provided. Please provide it using option -D THRIFT_CPP_LIB_DIR=<value> in CMake command")
else()
    message("Thrift library directory is: "${THRIFT_CPP_LIB_DIR})
endif()

if(NOT DEFINED BOOST_DIR)
    message(SEND_ERROR "Boost directory not provided. Please provide it using option -D BOOST_DIR=<value> in CMake command")
else()
    message("boost directory is: "${BOOST_DIR})
endif()	

set (DEFAULT_INSTALL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
   set (CMAKE_INSTALL_PREFIX ${DEFAULT_INSTALL_PATH} CACHE STRING "Install path" FORCE)
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
add_definitions(-DBOOST_LIB_DIAGNOSTIC=1)
#add_definitions(-DBOOST_ALL_NO_LIB=1)

##############################################################################
# 							   OUTPUT CONFIGURATION						     #
##############################################################################
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}${CMAKE_SYSTEM_NAME})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}${CMAKE_SYSTEM_NAME})

#source and header files
FILE(GLOB ccp_SERVICES_HEADERS services/gen-cpp/*.h)
FILE(GLOB ccp_IMPL_HEADERS impl/*.h)
SET (ccp_HEADER_FILES ${ccp_SERVICES_HEADERS} ${ccp_IMPL_HEADERS})

FILE (GLOB ccp_SCA_FILES impl/*.componentType META-INF/*.xml META-INF/*.composite META-INF/*.xml)
FILE (GLOB ccp_SCA_COMPONENT_TYPES *.componentType)
FILE (GLOB ccp_SOURCE_FILES impl/*.cpp services/gen-cpp/*.cpp)
FILE (GLOB ccp_SOURCE_FILES_TO_REMOVE  services/gen-cpp/*.skeleton.cpp)
list(REMOVE_ITEM ccp_SOURCE_FILES ${ccp_SOURCE_FILES_TO_REMOVE})
SET(ccp_SCA_FILES ${ccp_SCA_FILES} ${ccp_SCA_COMPONENT_TYPES})

#libs
set( ccp_THIRD_PARTY_LIBS 
     )
	 
set( ccp_CUSTOM_LIBS 
     )
	 
set( ccp_SOURCE_FILES ${ccp_SOURCE_FILES}
						  ${ccp_HEADER_FILES} ${ccp_SCA_FILES})

if (WIN32)
	add_definitions(-DCCP_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${ccp_SCA_FILES})
endif()

include_directories(${THRIFT_CPP_HEADER_DIR} ${BOOST_DIR}/include services/gen-cpp)
link_directories(${THRIFT_CPP_LIB_DIR} ${BOOST_DIR}/lib)
add_library(ccp SHARED ${ccp_SOURCE_FILES})
target_link_libraries(ccp libthrift 
optimized boost_system-vc100-mt-1_47 debug boost_thread-vc100-mt-gd-1_47)
# 
set(Trentinoccp_INSTALL_DIR ccp)
set_target_properties(ccp PROPERTIES OUTPUT_NAME ccp)
install(TARGETS ccp RUNTIME DESTINATION ${Trentinoccp_INSTALL_DIR}/bin
                    LIBRARY DESTINATION ${Trentinoccp_INSTALL_DIR}/lib)
install(DIRECTORY META-INF DESTINATION ${Trentinoccp_INSTALL_DIR})
install(FILES ${ccp_SERVICES_HEADERS} DESTINATION ${Trentinoccp_INSTALL_DIR}/services)
install(FILES ${ccp_IMPL_HEADERS} DESTINATION ${Trentinoccp_INSTALL_DIR}/impl)