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


FILE(GLOB BindingSCA_HEADER_FILES *.h )
FILE(GLOB BindingSCA_SOURCE_FILES *.cpp)


set(BindingSCA_PUBLIC_FILES
TrentinoBindingSCAImportExport.h
TrentinoBindingSCASCABindingHelper.h
TrentinoBindingSCAFaultDetailBuilder.h)

#libs
set( BindingSCA_THIRD_PARTY_LIBS
     ${loggingLib}
	 ZeroMq_LIBRARY
     Boost_SYSTEM_LIBRARY)
	 
set( BindingSCA_CUSTOM_LIBS 
     Utils Runtime BindingCompactSoap)
	 
set( BindingSCA_SOURCE_FILES ${BindingSCA_SOURCE_FILES}
							 ${BindingSCA_HEADER_FILES})
								 
if(MSVC_IDE)
	set(BindingSCA_SOURCE_FILES ${BindingSCA_SOURCE_FILES} ${BindingSCA_HEADER_FILES})	
endif()

set(compact_soap_dir ../BindingCompactSoap)
set(runtimedir ../)
include_directories( ${Boost_INCLUDE_DIRS}
					 ${Log4cplus_INCLUDE_DIRS}
					 ${compact_soap_dir}
					 ${runtimedir}
					 ${Protobuf_INCLUDE_DIRS}
					 ${ZeroMq_INCLUDE_DIRS}
					 ./)				 

add_library(BindingSCA SHARED ${BindingSCA_SOURCE_FILES})
set_target_properties(BindingSCA PROPERTIES OUTPUT_NAME TrentinoBindingSCA)
target_link_libraries(BindingSCA ${BindingSCA_CUSTOM_LIBS})
MY_LINK_THIRD_PARTY_LIBRARIES(BindingSCA ${BindingSCA_THIRD_PARTY_LIBS} )

install( TARGETS BindingSCA
		 RUNTIME DESTINATION ${TARGET_DLL_DIR}
		 LIBRARY DESTINATION ${TARGET_LIB_DIR}
		 ARCHIVE DESTINATION ${TARGET_LIB_DIR})

foreach(filePath ${BindingSCA_PUBLIC_FILES})
	get_filename_component(relativePath ${filePath} PATH)
	install(FILES ${filePath} DESTINATION ${TARGET_INCLUDE_DIR}/Binding/SCA/${relativePath})
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
	add_definitions(-DBINDINGSCA_EXPORTS)
endif()

if(CPPCHECK_GENERATE)
add_cppcheck(BindingSCA ${BindingSCA_SOURCE_FILES})                     
endif()

if(VERA_GENERATE)
add_vera(BindingSCA ${BindingSCA_SOURCE_FILES})                     
endif()
