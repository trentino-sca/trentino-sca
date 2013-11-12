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

FILE(GLOB BindingSCATest_HEADER_FILES *.h)
FILE(GLOB BindingSCATest_SOURCE_FILES *.cpp *.cc)
FILE(GLOB BindingSCATest_TEST_BIN_FILES  BindingSCATestsTestData/*.bin)
FILE(GLOB BindingSCATest_TEST_MESSAGES_FILES  BindingSCATestsTestData/*.proto)

#header files
#set ( BindingSCATest_HEADER_FILES	  TrentinoBindingSCATest.h)
	  
#source files
#set ( BindingSCATest_SOURCE_FILES      main.cpp	  TrentinoBindingSCATest.cpp)
	  
#libs
set( BindingSCATest_THIRD_PARTY_LIBS 
	 Protobuf_LIBRARY
	 GTest_LIBRARY
	 GMock_LIBRARY
	 Boost_THREAD_LIBRARY
	 )
	 
set(BindingSCATest_CUSTOM_LIBS 
     BindingSCA Runtime BindingCompactSoap)
	 
	 
if(MSVC_IDE)
	set(BindingSCATest_SOURCE_FILES ${BindingSCATest_SOURCE_FILES} ${BindingSCATest_HEADER_FILES})	
endif()

if(MSVC_IDE)									
	source_group("[Testdata Binaries]" FILES ${BindingSCATest_TEST_BIN_FILES})
    source_group("[Testdata Message descriptions]" FILES  ${BindingSCATest_TEST_MESSAGES_FILES})
endif()

set(compact_soap_dir ../../BindingCompactSoap)	 

set(runtimedir ../../)
set(bindingsca_dir ../../BindingSCA)
include_directories(${Boost_INCLUDE_DIRS} 
                    ${Log4plus_INCLUDE_DIRS} 
					${GMock_INCLUDE_DIRS} 
					${GTest_INCLUDE_DIRS} 
					${Protobuf_INCLUDE_DIRS}
					${ZeroMq_INCLUDE_DIRS}
					../Mocks
					${compact_soap_dir}
					${runtimedir}
					${bindingsca_dir})

add_executable(BindingSCATest ${BindingSCATest_SOURCE_FILES} ${BindingSCATest_TEST_BIN_FILES} ${BindingSCATest_TEST_MESSAGES_FILES})
MY_LINK_THIRD_PARTY_LIBRARIES(BindingSCATest ${BindingSCATest_THIRD_PARTY_LIBS})
add_dependencies(BindingSCATest GGMOCKTEST)
target_link_libraries(BindingSCATest ${BindingSCATest_CUSTOM_LIBS})

# if(TRENTINO_TESTING) 
   # install(TARGETS BindingSCATest ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "BindingSCATest")
# endif()
add_test(NAME BindingSCATest COMMAND BindingSCATest)

set_target_properties(BindingSCATest PROPERTIES FOLDER "Tests")
