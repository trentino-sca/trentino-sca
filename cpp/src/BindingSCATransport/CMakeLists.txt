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


SET(PN BindingSCATransport)
FILE(GLOB ${PN}_HEADER_FILES *.h)
FILE(GLOB ${PN}_SOURCE_FILES *.cpp)

set(${PN}_PUBLIC_FILES

)

#libs
set( ${PN}_THIRD_PARTY_LIBS
     ${loggingLib}
     Boost_SYSTEM_LIBRARY
	 Boost_THREAD_LIBRARY
     ZeroMq_LIBRARY	 
	 )
	 
set( ${PN}_CUSTOM_LIBS  Utils BindingCompactSoap)
	 
set( ${PN}_SOURCE_FILES ${${PN}_SOURCE_FILES}
								 ${${PN}_HEADER_FILES})
								 
if(MSVC_IDE)
	set(${PN}_SOURCE_FILES ${${PN}_SOURCE_FILES} ${${PN}_HEADER_FILES})	
endif()

set(compact_soap_dir ../BindingCompactSoap)
include_directories( ${Boost_INCLUDE_DIRS}
					 ${Log4cplus_INCLUDE_DIRS}
					 ${compact_soap_dir}
					 ${Protobuf_INCLUDE_DIRS}
					 ${ZeroMq_INCLUDE_DIRS})				 

#add_executable(${PN} ${${PN}_SOURCE_FILES})
add_library(${PN} SHARED ${${PN}_SOURCE_FILES})
set_target_properties(${PN} PROPERTIES OUTPUT_NAME Trentino${PN})
target_link_libraries(${PN} ${${PN}_CUSTOM_LIBS})
MY_LINK_THIRD_PARTY_LIBRARIES(${PN} ${${PN}_THIRD_PARTY_LIBS} )

install( TARGETS ${PN}
		 RUNTIME DESTINATION ${TARGET_DLL_DIR}
		 LIBRARY DESTINATION ${TARGET_LIB_DIR}
		 ARCHIVE DESTINATION ${TARGET_LIB_DIR})
		 

foreach(filePath ${${PN}_PUBLIC_FILES})
	get_filename_component(relativePath ${filePath} PATH)
	install(FILES ${filePath} DESTINATION ${TARGET_INCLUDE_DIR}/Binding/SCA/Transport/${relativePath})
endforeach()


if(WIN32)
	add_definitions(-DBINDINGSCATRANSPORT_EXPORTS)
endif()