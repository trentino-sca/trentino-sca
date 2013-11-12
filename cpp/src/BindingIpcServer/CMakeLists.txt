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


FILE(GLOB BindingIpcServer_HEADER_FILES *.h )
FILE(GLOB BindingIpcServer_SOURCE_FILES *.cpp)


set(BindingIpcServer_PUBLIC_FILES
TrentinoBindingIPCImportExport.h
TrentinoBindingIPCBindingHelper.h
TrentinoBindingIPCFaultDetailBuilder.h
TrentinoBindingIpcSoapMsg.h
TrentinoBindingIpcMemoryMapObj.h)



#libs
set( BindingIpcServer_THIRD_PARTY_LIBS
     ${loggingLib}
     )
	 
set( BindingIpcServer_CUSTOM_LIBS 
	Utils 
	Runtime 
	)
	 
set( BindingIpcServer_SOURCE_FILES 
	${BindingIpcServer_SOURCE_FILES}
	${BindingIpcServer_HEADER_FILES})
								 
if(MSVC_IDE)
	set(BindingIpcServer_SOURCE_FILES 
	${BindingIpcServer_SOURCE_FILES} 
	${BindingIpcServer_HEADER_FILES})	
endif()

set(TRENTINO_RUNTIME_INSTALLATION_DIR $ENV{TRENTINO_HOME})
set(runtimedir ../)
include_directories( ${Boost_INCLUDE_DIRS}
					 ${Log4cplus_INCLUDE_DIRS}
					  ${runtimedir}
                 ${TRENTINO_RUNTIME_INSTALLATION_DIR}
					 ./)				 

add_library(BindingIpcServer SHARED ${BindingIpcServer_SOURCE_FILES})
set_target_properties(BindingIpcServer PROPERTIES OUTPUT_NAME TrentinoBindingIpcServer)
target_link_libraries(BindingIpcServer ${BindingIpcServer_CUSTOM_LIBS})
MY_LINK_THIRD_PARTY_LIBRARIES(BindingIpcServer ${BindingIpcServer_THIRD_PARTY_LIBS} )

install( TARGETS BindingIpcServer
		 RUNTIME DESTINATION ${TARGET_DLL_DIR}
		 LIBRARY DESTINATION ${TARGET_LIB_DIR}
		 ARCHIVE DESTINATION ${TARGET_LIB_DIR})

foreach(filePath ${BindingIpcServer_PUBLIC_FILES})
	get_filename_component(relativePath ${filePath} PATH)
	install(FILES ${filePath} DESTINATION ${TARGET_INCLUDE_DIR}/Binding/IPC/${relativePath})
endforeach()
  
#install boost import libraries (*.lib) for windows
if(WIN32)
	install(FILES ${Boost_SYSTEM_LIBRARY_RELEASE} 				 
		    DESTINATION ${TARGET_LIB_DIR}/boost_1_47 
			CONFIGURATIONS Release RelWithDebInfo MinSizeRel)
	install(FILES ${Boost_SYSTEM_LIBRARY_DEBUG} 
				  ${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG} 
			DESTINATION ${TARGET_LIB_DIR}/boost_1_47 
			CONFIGURATIONS Debug)
endif()

if(WIN32)
	add_definitions(-DBINDINGIPCSERVER_EXPORTS)
endif()

if(CPPCHECK_GENERATE)
add_cppcheck(BindingIpcServer ${BindingIpcServer_SOURCE_FILES})                     
endif()

if(VERA_GENERATE)
add_vera(BindingIpcServer ${BindingIpcServer_SOURCE_FILES})                     
endif()
