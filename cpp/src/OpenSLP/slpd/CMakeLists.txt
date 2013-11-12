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
FILE(GLOB OpenSlpDeamon_HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.inl)	  
FILE(GLOB OpenSlpDeamon_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c *.cpp)	

set(OpenSlpDeamon_PUBLIC_FILES
slpddll.h
	)

if(MSVC_IDE)
	set(OpenSlpDeamon_SOURCE_FILES 
	${OpenSlpDeamon_SOURCE_FILES} 
	${OpenSlpDeamon_HEADER_FILES}
	)
	source_group("Source Files" FILES ${OpenSlpDeamon_SOURCE_FILES} )
	source_group("Header Files" FILES ${OpenSlpDeamon_HEADER_FILES} )
endif()

set(commondir ../slpdcommon)	
set(libslpattrdir ../libslpattr)	

include_directories(${commondir}
					${libslpattrdir}
               )

link_directories (../icu)

if(WIN32)
	remove_definitions(/WX) #avoid treating warnings as errors
	remove_definitions(-DUNICODE -D_UNICODE) #with unicode char sets actual code is not compiling
	add_definitions(-DOPENSLPDEAMON_EXPORTS)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_definitions(-DSLP_VERSION="2.0.0") #Define SLP version as a preprocessor definition
   add_definitions(-DENABLE_SLPv1)
endif()

add_library(slpd  SHARED ${OpenSlpDeamon_SOURCE_FILES})
set_target_properties(slpd PROPERTIES OUTPUT_NAME slpd) 

if(CMAKE_COMPILER_IS_GNUCXX)
set_target_properties(slpd PROPERTIES LINK_FLAGS "-ldl")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl" CACHE STRING "Flag to Load Libdl" FORCE)
target_link_libraries(slpd "-ldl")
endif()
target_link_libraries(slpd "advapi32.lib")
#target_link_libraries(slpd "icuuc.lib")
target_link_libraries(slpd "ws2_32.lib")
target_link_libraries(slpd libslpattr)
target_link_libraries(slpd slpdcommon)

install( TARGETS slpd 
		 RUNTIME DESTINATION ${TARGET_DLL_DIR}
		 LIBRARY DESTINATION ${TARGET_LIB_DIR}
		 ARCHIVE DESTINATION ${TARGET_LIB_DIR} )
install( FILES ${OpenSlpDeamon_PUBLIC_FILES} DESTINATION ${TARGET_INCLUDE_DIR}/slpd)

set(target_location "")
set(target_path "")
get_target_property(target_location slpd LOCATION)
get_filename_component(target_path ${target_location} PATH)

set_target_properties(slpd PROPERTIES FOLDER "OpenSLP")
 