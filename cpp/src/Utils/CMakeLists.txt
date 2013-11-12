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
FILE(GLOB Utils_HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.inl)	  
FILE(GLOB Utils_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)	

if(NOT TRENTINO_LOGGING)
	list(REMOVE_ITEM Utils_HEADER_FILES TrentinoUtilsLoggingLog4CPlus.h)
	list(REMOVE_ITEM Utils_SOURCE_FILES TrentinoUtilsLoggingLog4CPlus.cpp)
endif()

#libs
set( Utils_THIRD_PARTY_LIBS 
	 Boost_PROGRAM_OPTIONS_LIBRARY ${loggingLib}
	 )


set(Utils_PUBLIC_FILES
	TrentinoUtilsTypeName.h
	TrentinoUtilsTypeName.inl
	TrentinoUtilsTypeNameBase.h
	TrentinoUtilsTypeNameBase.inl
	)

	 
set( Utils_CUSTOM_LIBS 
     )

if(MSVC_IDE)
	set(Utils_SOURCE_FILES 
	${Utils_SOURCE_FILES} 
	${Utils_HEADER_FILES}
	)

	#source_group("[Public]" FILES ${Utils_PUBLIC_FILES})
endif()

include_directories(${Log4cplus_INCULDE_DIRS} ${Log4cplus_INCULDE_DIRS})
if(TRENTINO_LOGGING)
	include_directories(${Log4cplus_INCLUDE_DIRS}
						${Boost_INCLUDE_DIRS})
else()
	include_directories(${Boost_INCLUDE_DIRS})
endif()

if(WIN32)
	add_definitions(-DUTILS_EXPORTS)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif()


add_library(Utils  SHARED ${Utils_SOURCE_FILES})
set_target_properties(Utils PROPERTIES OUTPUT_NAME TrentinoUtils) 

if(CMAKE_COMPILER_IS_GNUCXX)
set_target_properties(Utils PROPERTIES LINK_FLAGS "-ldl")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl" CACHE STRING "Flag to Load Libdl" FORCE)
target_link_libraries(Utils "-ldl")
endif()

MY_LINK_THIRD_PARTY_LIBRARIES(Utils ${Utils_THIRD_PARTY_LIBS})
install( TARGETS Utils 
		 RUNTIME DESTINATION ${TARGET_DLL_DIR}
		 LIBRARY DESTINATION ${TARGET_LIB_DIR}
		 ARCHIVE DESTINATION ${TARGET_LIB_DIR} )
install( FILES ${Utils_PUBLIC_FILES} DESTINATION ${TARGET_INCLUDE_DIR}/Utils)

if(CPPCHECK_GENERATE)
add_cppcheck(Utils ${Utils_SOURCE_FILES})                     
endif()

if(VERA_GENERATE)
add_vera(Utils ${Utils_SOURCE_FILES})                     
endif()