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
  

#install boost header files
 install(FILES ${Boost_SYSTEM_LIBRARY_RELEASE} ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE} DESTINATION ${TARGET_LIB_DIR}/boost_1_44/release)
 install(FILES ${Boost_SYSTEM_LIBRARY_DEBUG} ${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG} DESTINATION ${TARGET_LIB_DIR}/boost_1_44/debug)


if(WIN32)
	add_definitions(-DBINDINGSCA_EXPORTS)
endif()