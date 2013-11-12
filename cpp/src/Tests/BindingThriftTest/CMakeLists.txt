# *****************************************************************************
# Trentino - A C++ based lightweight, non-invasive SCA runtime.
# Copyright (C) Siemens AG, 2012
# All Rights Reserved
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# *****************************************************************************

set(PN BindingThriftTest)
FILE(GLOB ${PN}_HEADER_FILES *.h)
FILE(GLOB ${PN}_SOURCE_FILES *.cpp)

#header files
#set ( ${PN}_HEADER_FILES	  Trentino${PN}.h)
	  
#source files
#set ( ${PN}_SOURCE_FILES      main.cpp	  Trentino${PN}.cpp)
	  
#libs
set( ${PN}_THIRD_PARTY_LIBS 
	 GTest_LIBRARY
	 GMock_LIBRARY
	 Boost_THREAD_LIBRARY
	 )
	 
set(${PN}_CUSTOM_LIBS 
     BindingThrift Runtime)
	 
	 
if(MSVC_IDE)
	set(${PN}_SOURCE_FILES ${${PN}_SOURCE_FILES} ${${PN}_HEADER_FILES})	
endif()

	 
#include_directories(BEFORE ${CppUnit_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS} ${Log4plus_INCLUDE_DIRS} 
					${GMock_INCLUDE_DIRS} ${GTest_INCLUDE_DIRS} ${Protobuf_INCLUDE_DIRS} ../Mocks)

add_executable(${PN} ${${PN}_SOURCE_FILES} ${${PN}_TEST_BIN_FILES} ${${PN}_TEST_MESSAGES_FILES})
MY_LINK_THIRD_PARTY_LIBRARIES(${PN} ${${PN}_THIRD_PARTY_LIBS})
add_dependencies(${PN} GGMOCKTEST)
target_link_libraries(${PN} ${${PN}_CUSTOM_LIBS})

# if(TRENTINO_TESTING) 
   # install(TARGETS ${PN} ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "${PN}")
# endif()
add_test(${PN} ${EXECUTABLE_OUTPUT_PATH}/${PN})

set_target_properties(${PN} PROPERTIES FOLDER "Tests")
