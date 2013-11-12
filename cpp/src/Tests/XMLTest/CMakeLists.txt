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
set ( XMLTest_HEADER_FILES
	  TrentinoTestsXMLSchemaQNameTest.h)
	  
#source files
set ( XMLTest_SOURCE_FILES
	  main.cpp
	  TrentinoTestsXMLSchemaQNameTest.cpp)
	  
#libs
find_package (Threads)

set( XMLTest_THIRD_PARTY_LIBS 
     GTest_LIBRARY
	 GMock_LIBRARY)
	 
set( XMLTest_CUSTOM_LIBS 
     Runtime)
	 
if(MSVC_IDE)
	set(XMLTest_SOURCE_FILES ${XMLTest_SOURCE_FILES} ${XMLTest_HEADER_FILES})
endif()
	 
include_directories(BEFORE ${GTest_INCLUDE_DIRS} ${GMock_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(XMLTest ${XMLTest_SOURCE_FILES})
MY_LINK_THIRD_PARTY_LIBRARIES(XMLTest ${XMLTest_THIRD_PARTY_LIBS})
target_link_libraries(XMLTest ${XMLTest_CUSTOM_LIBS})
target_link_libraries (XMLTest ${CMAKE_THREAD_LIBS_INIT})

# if(TRENTINO_TESTING) 
   # install(TARGETS XMLTest ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "XMLTest")
# endif()
add_test(NAME XMLTest COMMAND XMLTest)

set_target_properties(XMLTest PROPERTIES FOLDER "Tests")
 