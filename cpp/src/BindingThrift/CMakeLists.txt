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

#source and header files


SET(PN BindingThrift)
FILE(GLOB ${PN}_HEADER_FILES *.h)
FILE(GLOB ${PN}_SOURCE_FILES *.cpp)


FILE(GLOB ${PN}_PROTO_MESSAGES_FILES Protobuf/Messages/*.proto)

set(${PN}_SOURCE_FILES ${${PN}_SOURCE_FILES})	
set(${PN}_HEADER_FILES ${${PN}_HEADER_FILES})

#libs
set( ${PN}_THIRD_PARTY_LIBS
     ${loggingLib}
     Boost_SYSTEM_LIBRARY
	 Thrift_LIBRARY
	 )
	 
set( ${PN}_CUSTOM_LIBS 
     Utils Runtime)
	 
set( ${PN}_SOURCE_FILES ${${PN}_SOURCE_FILES}
								 ${${PN}_HEADER_FILES} ${${PN}_PROTO_MESSAGES_FILES})
								 
if(MSVC_IDE)
	set(${PN}_SOURCE_FILES ${${PN}_SOURCE_FILES} ${${PN}_HEADER_FILES})	
endif()


include_directories( ${Boost_INCLUDE_DIRS}
					 ${Log4cplus_INCLUDE_DIRS} 
					 ${Thrift_INCLUDE_DIRS})				 

add_library(${PN} SHARED ${${PN}_SOURCE_FILES})
set_target_properties(${PN} PROPERTIES OUTPUT_NAME Trentino${PN})
target_link_libraries(${PN} ${${PN}_CUSTOM_LIBS})
MY_LINK_THIRD_PARTY_LIBRARIES(${PN} ${${PN}_THIRD_PARTY_LIBS} )

#install(TARGETS ${PN} ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} 
#ARCHIVE DESTINATION ${TARGET_LIB_DIR})
if(WIN32)
	add_definitions(-DBINDINGTHRIFT_EXPORTS)
endif()