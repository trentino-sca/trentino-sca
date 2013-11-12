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
FILE(GLOB OpenSlpDeamon_HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ./slpd/*.h ./slpd/*.inl)	  
FILE(GLOB OpenSlpDeamon_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ./slpd/*.c ./slpd/*.cpp)	
FILE(GLOB OpenSlpDeamon_SOURCE_FILES_COMMON ./common/*.cpp ./common/*.c)
FILE(GLOB OpenSlpDeamon_HEADER_FILES_COMMON ./common/*.h)
FILE(GLOB OpenSlpDeamon_HEADER_FILES_LIBSLP ./libslp/*.h)
FILE(GLOB OpenSlpDeamon_HEADER_FILES_LIBSLPATTR ./libslpattr/*.h)
FILE(GLOB OpenSlpDeamon_SOURCE_FILES_LIBSLPATTR ./libslpattr/*.c)
#libs
set( OpenSlpDeamon_THIRD_PARTY_LIBS 
    OpenSlp_LIBRARY
	 )


set(OpenSlpDeamon_PUBLIC_FILES
slpd/slpddll.h
	)

	 
set( OpenSlpDeamon_CUSTOM_LIBS 
    )

if(MSVC_IDE)
	set(OpenSlpDeamon_SOURCE_FILES 
	${OpenSlpDeamon_SOURCE_FILES} 
	${OpenSlpDeamon_HEADER_FILES}
	${OpenSlpDeamon_SOURCE_FILES_COMMON}
	${OpenSlpDeamon_HEADER_FILES_COMMON} 
	${OpenSlpDeamon_HEADER_FILES_LIBSLP}
	${OpenSlpDeamon_HEADER_FILES_LIBSLPATTR}
   ${OpenSlpDeamon_SOURCE_FILES_LIBSLPATTR}
	)
	source_group("Source Files\\[Common]" FILES ${OpenSlpDeamon_SOURCE_FILES_COMMON} )
	source_group("Header Files\\[Common]" FILES ${OpenSlpDeamon_HEADER_FILES_COMMON} )
	source_group("Header Files\\[libslp]" FILES ${OpenSlpDeamon_HEADER_FILES_LIBSLP})
	source_group("Header Files\\[libslpattr]" FILES ${OpenSlpDeamon_HEADER_FILES_LIBSLPATTR} )
   source_group("Source Files\\[libslpattr]" FILES ${OpenSlpDeamon_SOURCE_FILES_LIBSLPATTR} )
endif()

set(commondir ./common)	
set(libslpdir libslp)	
set(libslpattrdir ./libslpattr)	

include_directories(${OpenSlp_INCLUDE_DIRS}
					${commondir}
					${libslpdir}
					${libslpattrdir}
               )

link_directories (${CMAKE_CURRENT_SOURCE_DIR}/icu)


#SET (SLP_VERSION ON CACHE BOOL "2.0.0" FORCE)			

if(WIN32)
	remove_definitions(/WX) #avoid treating warnings as errors
	remove_definitions(-DUNICODE -D_UNICODE) #with unicode char sets actual code is not compiling
	add_definitions(-DOPENSLPDEAMON_EXPORTS)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_definitions(-DSLP_VERSION="2.0.0") #Define SLP version as a preprocessor definition
   add_definitions(-DENABLE_SLPv1)
endif()


add_library(OpenSlpDeamon  SHARED ${OpenSlpDeamon_SOURCE_FILES} ${OpenSlpDeamon_SOURCE_FILES_COMMON} ${OpenSlpDeamon_SOURCE_FILES_LIBSLPATTR} )
set_target_properties(OpenSlpDeamon PROPERTIES OUTPUT_NAME OpenSlpDeamon) 

if(CMAKE_COMPILER_IS_GNUCXX)
set_target_properties(OpenSlpDeamon PROPERTIES LINK_FLAGS "-ldl")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl" CACHE STRING "Flag to Load Libdl" FORCE)
target_link_libraries(OpenSlpDeamon "-ldl")
endif()
target_link_libraries(OpenSlpDeamon "advapi32.lib")
#target_link_libraries(OpenSlpDeamon "icuuc.lib")
target_link_libraries(OpenSlpDeamon "ws2_32.lib")
MY_LINK_THIRD_PARTY_LIBRARIES(OpenSlpDeamon ${OpenSlpDeamon_THIRD_PARTY_LIBS} )

install( TARGETS OpenSlpDeamon 
		 RUNTIME DESTINATION ${TARGET_DLL_DIR}
		 LIBRARY DESTINATION ${TARGET_LIB_DIR}
		 ARCHIVE DESTINATION ${TARGET_LIB_DIR} )
install( FILES ${OpenSlpDeamon_PUBLIC_FILES} DESTINATION ${TARGET_INCLUDE_DIR}/OpenSlpDeamon)

set(target_location "")
set(target_path "")
get_target_property(target_location OpenSlpDeamon LOCATION)
get_filename_component(target_path ${target_location} PATH)
add_custom_command( TARGET OpenSlpDeamon POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/slp.conf ${target_path}/slp.conf)

install(FILES slp.conf DESTINATION ${TARGET_DLL_DIR})

# keep open slp deamon code out of cppcheck
#if(CPPPCHECK_GENERATE)
#add_cppcheck(OpenSlpDeamon ${OpenSlpDeamon_SOURCE_FILES})                     
#endif()

 