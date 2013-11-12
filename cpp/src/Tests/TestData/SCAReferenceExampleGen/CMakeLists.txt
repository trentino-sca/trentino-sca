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

#header files
FILE(GLOB SCAReferenceExampleGen_HEADER_FILES *.h *.inl)	  

#source files
FILE(GLOB SCAReferenceExampleGen_SOURCE_FILES *.cpp)	  

set ( SCAReferenceExampleGen_SOURCE_FILES
	  ${SCAReferenceExampleGen_HEADER_FILES} ${SCAReferenceExampleGen_SOURCE_FILES})  


	  
#libs
set( SCAReferenceExampleGen_THIRD_PARTY_LIBS 
     )
	 
set( SCAReferenceExampleGen_CUSTOM_LIBS 
     Runtime
	 SCAReferenceExample
	 )

if (WIN32)
	add_definitions(-DSCAREFERENCEEXAMPLEGEN_EXPORTS)
endif()


include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)

add_library(SCAReferenceExampleGen SHARED ${SCAReferenceExampleGen_SOURCE_FILES})
set_target_properties(SCAReferenceExampleGen PROPERTIES OUTPUT_NAME sca-contribution)

set(target_location "")
set(target_path "")
#set(target_file_name "")
get_target_property(target_location SCAReferenceExampleGen LOCATION)
get_filename_component(target_path ${target_location} PATH)
set(new_path ${target_path}/SCAReferenceExampleGen/META-INF)
#get_filename_component(target_file_name ${target_location}
add_custom_command( TARGET SCAReferenceExampleGen POST_BUILD
					COMMAND  ${CMAKE_COMMAND} -E make_directory ${new_path}
					COMMAND ${CMAKE_COMMAND} -E copy ${target_location} ${new_path} 
					VERBATIM)

target_link_libraries(SCAReferenceExampleGen ${SCAReferenceExampleGen_CUSTOM_LIBS})
# install(TARGETS SCAReferenceExampleGen ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} 
#                                    ARCHIVE DESTINATION ${TARGET_LIB_DIR})

set_target_properties(SCAReferenceExampleGen PROPERTIES FOLDER "Tests/TestData")
