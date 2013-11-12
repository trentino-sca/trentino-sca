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
#header files
FILE(GLOB SCAReferenceExample_HEADER_FILES *.h *.inl services/*.h)	  

#source files
FILE(GLOB SCAReferenceExample_SOURCE_FILES *.cpp)	  

set ( SCAReferenceExample_SOURCE_FILES
	  ${SCAReferenceExample_HEADER_FILES} ${SCAReferenceExample_SOURCE_FILES})  
	  
#libs
set( SCAReferenceExample_THIRD_PARTY_LIBS 
     )
	 
set( SCAReferenceExample_CUSTOM_LIBS 
     )
	 

if (WIN32)
	add_definitions(-DSCAREFERENCEEXAMPLE_EXPORTS)
endif()

include_directories(${SCAAPI_INCLUDE_DIRS})

add_library(SCAReferenceExample SHARED ${SCAReferenceExample_SOURCE_FILES})
set_target_properties(SCAReferenceExample PROPERTIES OUTPUT_NAME SCAReferenceExample)
# install(TARGETS SCAReferenceExample ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} 
#                                    ARCHIVE DESTINATION ${TARGET_LIB_DIR})

set_target_properties(SCAReferenceExample PROPERTIES FOLDER "Tests/TestData")

