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

FILE(GLOB Mocks_HEADER_FILES *.h)
FILE(GLOB Mocks_SOURCE_FILES *.cpp)

  
#libs
set( Mocks_THIRD_PARTY_LIBS 
	 GTest_LIBRARY
	 GMock_LIBRARY
	 )
	 
set(Mocks_CUSTOM_LIBS 
    )
	 
	 
if(MSVC_IDE)
	set(Mocks_SOURCE_FILES ${Mocks_SOURCE_FILES} ${Mocks_HEADER_FILES})	
endif()

if(MSVC_IDE)									
	source_group("[Testdata Binaries]" FILES ${Mocks_TEST_BIN_FILES})
    source_group("[Testdata Message descriptions]" FILES  ${Mocks_TEST_MESSAGES_FILES})
endif()
	 
#include_directories(BEFORE ${GTest_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS} ${Log4plus_INCLUDE_DIRS} 
					${GMock_INCLUDE_DIRS} ${GTest_INCLUDE_DIRS} ${Protobuf_INCLUDE_DIRS})

add_library(Mocks STATIC ${Mocks_SOURCE_FILES})
set_target_properties(Mocks PROPERTIES LINKER_LANGUAGE CXX)
MY_LINK_THIRD_PARTY_LIBRARIES(Mocks ${Mocks_THIRD_PARTY_LIBS})
add_dependencies(Mocks GGMOCKTEST)
target_link_libraries(Mocks ${Mocks_CUSTOM_LIBS})

# if(TRENTINO_TESTING) 
   # install(TARGETS Mocks ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "Mocks")
# endif()
set_target_properties(Mocks PROPERTIES FOLDER "Tests")
