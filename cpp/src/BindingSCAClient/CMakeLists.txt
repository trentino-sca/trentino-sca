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


SET(PN BindingSCAClient)
set(SRC_PATH Binding/SCA/Client)
FILE(GLOB ${PN}_HEADER_FILES ${SRC_PATH}/*.h)
FILE(GLOB ${PN}_SOURCE_FILES ${SRC_PATH}/*.cpp)

set(${PN}_PUBLIC_FILES
${SRC_PATH}/TrentinoBindingSCAClientProxyDelegate.h
${SRC_PATH}/TrentinoBindingSCAClientImportExport.h
${SRC_PATH}/TrentinoBindingSCAClientDefs.h
)

#libs
set( ${PN}_THIRD_PARTY_LIBS
     ${loggingLib}
     Boost_SYSTEM_LIBRARY
	 Boost_THREAD_LIBRARY 
    Boost_FILESYSTEM_LIBRARY
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
	install(FILES ${filePath} DESTINATION ${TARGET_INCLUDE_DIR}/${relativePath})
endforeach()
  

#if(WIN32)
	install(FILES ${Boost_SYSTEM_LIBRARY_RELEASE} 				  
		    DESTINATION ${TARGET_LIB_DIR}/boost_1_47 
			CONFIGURATIONS Release RelWithDebInfo MinSizeRel)
	install(FILES ${Boost_SYSTEM_LIBRARY_DEBUG} 				   
			DESTINATION ${TARGET_LIB_DIR}/boost_1_47 
			CONFIGURATIONS Debug)
#endif()


if(WIN32)
	add_definitions(-DBINDINGSCACLIENT_EXPORTS)
endif()

if(CPPCHECK_GENERATE)
add_cppcheck(BindingSCAClient ${BindingSCAClient_SOURCE_FILES})                     
endif()

if(VERA_GENERATE)
add_vera(BindingSCAClient ${BindingSCAClient_SOURCE_FILES})                     
endif()