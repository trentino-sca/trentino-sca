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

FILE(GLOB BindingSCAClientTest_HEADER_FILES *.h)
FILE(GLOB BindingSCAClientTest_SOURCE_FILES *.cpp)

#header files
#set ( BindingSCAClientTest_HEADER_FILES	  TrentinoBindingSCAClientTest.h)
	  
#source files
#set ( BindingSCAClientTest_SOURCE_FILES      main.cpp	  TrentinoBindingSCAClientTest.cpp)
	  
#libs
set( BindingSCAClientTest_THIRD_PARTY_LIBS 
	 Protobuf_LIBRARY
	 GTest_LIBRARY
	 GMock_LIBRARY
	 Boost_THREAD_LIBRARY
	 )
	 
set(BindingSCAClientTest_CUSTOM_LIBS 
     BindingSCAClient)
	 
	 
if(MSVC_IDE)
	set(BindingSCAClientTest_SOURCE_FILES ${BindingSCAClientTest_SOURCE_FILES} ${BindingSCAClientTest_HEADER_FILES})	
endif()

if(MSVC_IDE)									
	source_group("[Testdata Binaries]" FILES ${BindingSCAClientTest_TEST_BIN_FILES})
    source_group("[Testdata Message descriptions]" FILES  ${BindingSCAClientTest_TEST_MESSAGES_FILES})
endif()
	 
#include_directories(BEFORE ${CppUnit_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS} ${Log4plus_INCLUDE_DIRS} 
					${GMock_INCLUDE_DIRS} ${GTest_INCLUDE_DIRS} ${Protobuf_INCLUDE_DIRS})

add_executable(BindingSCAClientTest ${BindingSCAClientTest_SOURCE_FILES} ${BindingSCAClientTest_TEST_BIN_FILES} ${BindingSCAClientTest_TEST_MESSAGES_FILES})
MY_LINK_THIRD_PARTY_LIBRARIES(BindingSCAClientTest ${BindingSCAClientTest_THIRD_PARTY_LIBS})
add_dependencies(BindingSCAClientTest GGMOCKTEST)
target_link_libraries(BindingSCAClientTest ${BindingSCAClientTest_CUSTOM_LIBS})

if(TRENTINO_TESTING) 
   install(TARGETS BindingSCAClientTest ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "BindingSCAClientTest")
endif()
set_target_properties(BindingSCAClientTest PROPERTIES FOLDER "Tests")
