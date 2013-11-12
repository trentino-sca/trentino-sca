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

#source and header files

set(PName BindingCompactSoap)
set(SRC_PATH Binding/CompactSoap)
FILE(GLOB ${PName}_HEADER_FILES ${SRC_PATH}/*.h)
FILE(GLOB ${PName}_SOURCE_FILES ${SRC_PATH}/*.cpp)

FILE(GLOB ${PName}_PROTO_HEADER_FILES ${SRC_PATH}/*.pb.h)
#FILE(GLOB ${PName}_PROTO_SOURCE_FILES ${SRC_PATH}/*.pb.cc)

FILE(GLOB ${PName}_PROTO_MESSAGES_FILES Messages/*.proto)

set(${PName}_SOURCE_FILES ${${PName}_SOURCE_FILES} ${${PName}_PROTO_SOURCE_FILES})	
set(${PName}_HEADER_FILES ${${PName}_HEADER_FILES} ${${PName}_PROTO_HEADER_FILES})

set(${PName}_PUBLIC_FILES
${SRC_PATH}/BindingCompactSoapProtobufMessages.h
${SRC_PATH}/compact_soap.pb.h
${SRC_PATH}/ws_addressing.pb.h
${SRC_PATH}/BindingCompactSoapImportExport.h
${SRC_PATH}/TrentinoBindingCompactSoapUtil.h)

#libs
set( ${PName}_THIRD_PARTY_LIBS
     ${loggingLib}
	 Protobuf_LIBRARY
	 ZeroMq_LIBRARY)
	 
set( ${PName}_CUSTOM_LIBS )
	 
set( ${PName}_SOURCE_FILES ${${PName}_SOURCE_FILES}
								 ${${PName}_HEADER_FILES} ${${PName}_PROTO_MESSAGES_FILES})
								 
if(MSVC_IDE)
	set(${PName}_SOURCE_FILES ${${PName}_SOURCE_FILES} ${${PName}_HEADER_FILES})	
endif()

if(MSVC_IDE)									
	source_group("[Protobuf Sources]" FILES ${${PName}_PROTO_SOURCE_FILES})
    source_group("[Protobuf Headers]" FILES ${${PName}_PROTO_HEADER_FILES})
	source_group("[Protobuf Messages]" FILES ${${PName}_PROTO_MESSAGES_FILES})
endif()

set(compact_soap_dir Protobuf)
set(runtimedir ../)
include_directories( ${Protobuf_INCLUDE_DIRS}  ${ZeroMq_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})				 

add_library(${PName} SHARED ${${PName}_SOURCE_FILES})
set_target_properties(${PName} PROPERTIES OUTPUT_NAME Trentino${PName})
target_link_libraries(${PName} ${${PName}_CUSTOM_LIBS})
MY_LINK_THIRD_PARTY_LIBRARIES(${PName} ${${PName}_THIRD_PARTY_LIBS} )

install( TARGETS ${PName}
		 RUNTIME DESTINATION ${TARGET_DLL_DIR}
		 LIBRARY DESTINATION ${TARGET_LIB_DIR}
		 ARCHIVE DESTINATION ${TARGET_LIB_DIR})

foreach(filePath ${${PName}_PUBLIC_FILES})
	get_filename_component(relativePath ${filePath} PATH)
	install(FILES ${filePath} DESTINATION ${TARGET_INCLUDE_DIR}/${relativePath})
endforeach()

#install protobuf header files
install(DIRECTORY  ${Protobuf_INCLUDE_DIRS} DESTINATION ${TARGET_INCLUDE_DIR}/protobuf-2.4.1)

#install protobuf libraries

install(FILES ${Protobuf_LIBRARY_RELEASE} 
		DESTINATION ${TARGET_LIB_DIR}/protobuf-2.4.1
		CONFIGURATIONS Release RelWithDebInfo MinSizeRel)
install(FILES ${Protobuf_LIBRARY_DEBUG} 
		DESTINATION ${TARGET_LIB_DIR}/protobuf-2.4.1
		CONFIGURATIONS Debug)

if(WIN32)
	add_definitions(-DBINDINGCOMPACTSOAP_EXPORTS)
endif()

if(CPPCHECK_GENERATE)
add_cppcheck(BindingCompactSoap ${BindingCompactSoap_SOURCE_FILES})                     
endif()

if(VERA_GENERATE)
add_vera(BindingCompactSoap ${BindingCompactSoap_SOURCE_FILES})                     
endif()
