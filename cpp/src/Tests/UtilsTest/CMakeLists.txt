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
FILE(GLOB UtilsTest_HEADER_FILES *.h *.inl)	  
FILE(GLOB UtilsTest_SOURCE_FILES *.cpp)	
FILE(GLOB UtilsTest_TESTDATA_FILES ./TestData/*)	
	  
#libs
set( UtilsTest_THIRD_PARTY_LIBS 
     GTest_LIBRARY
	 GMock_LIBRARY
	 ${loggingLib})
	 
set( UtilsTest_CUSTOM_LIBS 
     Utils)
	 
find_package (Threads)

if(MSVC_IDE)
	set(UtilsTest_SOURCE_FILES ${UtilsTest_SOURCE_FILES} ${UtilsTest_HEADER_FILES})
	source_group("TestData" FILES ${UtilsTest_TESTDATA_FILES})
endif()
	 
include_directories(BEFORE ${GTest_INCLUDE_DIRS} ${GMock_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

if(TRENTINO_LOGGING)
	include_directories(${Log4cplus_INCLUDE_DIRS})
endif()

if(WIN32)
	#turns out __declspecc(dllimport) inside of Utils.lib (because it's a static lib)
	add_definitions(-DUTILS_EXPORTS)
endif()

add_executable(UtilsTest ${UtilsTest_SOURCE_FILES} ${UtilsTest_TESTDATA_FILES})
MY_LINK_THIRD_PARTY_LIBRARIES(UtilsTest ${UtilsTest_THIRD_PARTY_LIBS})
target_link_libraries(UtilsTest ${UtilsTest_CUSTOM_LIBS})
target_link_libraries (UtilsTest ${CMAKE_THREAD_LIBS_INIT})

# if(TRENTINO_TESTING) 
   # install(TARGETS UtilsTest ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "UtilsTest")
# endif()
add_test(NAME UtilsTest COMMAND UtilsTest)

set_target_properties(UtilsTest PROPERTIES FOLDER "Tests")
 