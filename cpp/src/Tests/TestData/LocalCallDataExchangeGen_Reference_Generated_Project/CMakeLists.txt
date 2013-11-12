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
FILE(GLOB LocalCallDataExchangeGen_HEADER_FILES *.h *.inl)	  

#source files
FILE(GLOB LocalCallDataExchangeGen_SOURCE_FILES *.cpp)	  

set ( LocalCallDataExchangeGen_SOURCE_FILES
	  ${LocalCallDataExchangeGen_HEADER_FILES} ${LocalCallDataExchangeGen_SOURCE_FILES})  


	  
#libs
set( LocalCallDataExchangeGen_THIRD_PARTY_LIBS 
     )
	 
set( LocalCallDataExchangeGen_CUSTOM_LIBS 
     Runtime
	 LocalCallDataExchange
	 )


if (WIN32)
	add_definitions(-DTRENTINOLOCALCALLDATAEXCHANGEGEN_EXPORTS)
endif()


include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src ../LocalCallDataExchange)

add_library(LocalCallDataExchangeGen SHARED ${LocalCallDataExchangeGen_SOURCE_FILES})
set_target_properties(LocalCallDataExchangeGen PROPERTIES OUTPUT_NAME sca-contribution)

set(target_location "")
set(target_path "")
#set(target_file_name "")
get_target_property(target_location LocalCallDataExchangeGen LOCATION)
get_filename_component(target_path ${target_location} PATH)
set(new_path ${target_path}/LocalCallDataExchangeGen/META-INF)
#get_filename_component(target_file_name ${target_location}
add_custom_command( TARGET LocalCallDataExchangeGen POST_BUILD
					COMMAND  ${CMAKE_COMMAND} -E make_directory ${new_path}
					COMMAND ${CMAKE_COMMAND} -E copy ${target_location} ${new_path} 
					VERBATIM)

target_link_libraries(LocalCallDataExchangeGen ${LocalCallDataExchangeGen_CUSTOM_LIBS})
#install(TARGETS LocalCallDataExchangeGen ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} 
#                                    ARCHIVE DESTINATION ${TARGET_LIB_DIR})

set_target_properties(LocalCallDataExchangeGen PROPERTIES FOLDER "Tests/TestData")