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


cmake_minimum_required(VERSION 2.8)
project(LocalCallDataExchangeGen)

set (DEFAULT_INSTALL_PATH I:/Trentino/trentino/DEV/cpp/src/Tests/TestData)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
   set (CMAKE_INSTALL_PREFIX I:/Trentino/trentino/DEV/cpp/src/Tests/TestData CACHE STRING "Install path" FORCE)
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
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}${CMAKE_SYSTEM_NAME} )
set(Contribution_Dir I:/Trentino/trentino/DEV/cpp/src/Tests/TestData/LocalCallDataExchange)
set(Include_Dir I:/Trentino/trentino/DEV/cpp/src/Tests/TestData/LocalCallDataExchange)
set(TRENTINO_RUNTIME_DIR I:/Trentino/trentino/Binaries/trentino_x86_windows_0.2-pa)
set(Include_Dir, )

#header files
FILE(GLOB LocalCallDataExchangeGenHEADER_FILES *.h *.inl)	  

#source files
FILE(GLOB LocalCallDataExchangeGenSOURCE_FILES *.cpp)	  

set ( LocalCallDataExchangeGenSOURCE_FILES
	  ${LocalCallDataExchangeGenHEADER_FILES} ${LocalCallDataExchangeGenSOURCE_FILES})  


	  
#libs
set( LocalCallDataExchangeGenTHIRD_PARTY_LIBS
     TrentinoRuntime LocalCallDataExchange
     )
	 
set( LocalCallDataExchangeGenCUSTOM_LIBS )


if (WIN32)
	add_definitions(-DLOCALCALLDATAEXCHANGEGEN_EXPORTS)
endif()

include_directories(${TRENTINO_RUNTIME_DIR}/include ${Contribution_Dir} ${Contribution_Dir}/services ${Contribution_Dir}/include ${Include_Dir})
link_directories(I:/Trentino/trentino/Binaries/trentino_x86_windows_0.2-pa/lib I:/Trentino/trentino/DEV/cpp/src/Tests/TestData/LocalCallDataExchange I:/Trentino/trentino/DEV/cpp/src/Tests/TestData/LocalCallDataExchange/lib )

add_library(LocalCallDataExchangeGen SHARED ${LocalCallDataExchangeGenSOURCE_FILES})
set_target_properties(LocalCallDataExchangeGen PROPERTIES OUTPUT_NAME sca-contribution)

set(target_location "")
set(target_path "")
#set(target_file_name "")
get_target_property(target_location LocalCallDataExchangeGen LOCATION)

get_filename_component(target_path ${target_location} PATH)
set(new_path ${target_path}/LocalCallDataExchangeGen/META-INF)
#get_filename_component(target_file_name ${target_location}
add_custom_command( TARGET LocalCallDataExchangeGen POST_BUILD
					COMMAND  ${CMAKE_COMMAND} -E make_directory ${new_path}
					COMMAND ${CMAKE_COMMAND} -E copy ${target_location} ${new_path} 
					VERBATIM)

target_link_libraries(LocalCallDataExchangeGen ${LocalCallDataExchangeGenCUSTOM_LIBS})
target_link_libraries(LocalCallDataExchangeGen ${LocalCallDataExchangeGenTHIRD_PARTY_LIBS})
set(MY_GEN_INSTALL_DIR LocalCallDataExchange)
install(TARGETS LocalCallDataExchangeGen  ${DLL_TARGET_KIND} DESTINATION ${MY_GEN_INSTALL_DIR}/META-INF ARCHIVE DESTINATION ${TARGET_LIB_DIR})