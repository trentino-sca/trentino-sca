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
FILE(GLOB SCAReferenceExampleTest_HEADER_FILES *.h *.inl)	  

#source files
FILE(GLOB SCAReferenceExampleTest_SOURCE_FILES *.cpp)	  

set ( SCAReferenceExampleTest_SOURCE_FILES
	  ${SCAReferenceExampleTest_HEADER_FILES} ${SCAReferenceExampleTest_SOURCE_FILES})  
  
#libs
find_package (Threads)

set( SCAReferenceExampleTest_THIRD_PARTY_LIBS 
	 GTest_LIBRARY
	 GMock_LIBRARY
	 ${loggingLib})
	 
set( SCAReferenceExampleTest_CUSTOM_LIBS 
     Runtime )
	 


if(WIN32)
endif()	 
	 
include_directories(BEFORE 	${GMock_INCLUDE_DIRS} 
					${GTest_INCLUDE_DIRS} )
include_directories(${Boost_INCLUDE_DIRS}
					${Log4plus_INCLUDE_DIRS})

add_executable(SCAReferenceExampleTest ${SCAReferenceExampleTest_SOURCE_FILES})
MY_LINK_THIRD_PARTY_LIBRARIES(SCAReferenceExampleTest ${SCAReferenceExampleTest_THIRD_PARTY_LIBS})
target_link_libraries(SCAReferenceExampleTest ${SCAReferenceExampleTest_CUSTOM_LIBS})
target_link_libraries (SCAReferenceExampleTest ${CMAKE_THREAD_LIBS_INIT})
add_dependencies(SCAReferenceExampleTest SCAReferenceExampleGen)
# if(TRENTINO_TESTING) 
   # install(TARGETS SCAReferenceExampleTest ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "SCAReferenceExampleTest")
# endif()
add_test(NAME SCAReferenceExampleTest COMMAND SCAReferenceExampleTest)

set_target_properties(SCAReferenceExampleTest PROPERTIES FOLDER "Tests")
