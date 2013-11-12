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
FILE(GLOB RuntimeAPITest_HEADER_FILES *.h *.inl)	  
FILE(GLOB RuntimeAPITest_SOURCE_FILES *.cpp)	
	  
#libs
find_package (Threads)

set( RuntimeAPITest_THIRD_PARTY_LIBS 
     Boost_FILESYSTEM_LIBRARY
	 Boost_SYSTEM_LIBRARY
	 GTest_LIBRARY
	 ${loggingLib})
	 
set( RuntimeAPITest_CUSTOM_LIBS 
     Runtime)
	 
if(MSVC_IDE)
	set(RuntimeAPITest_SOURCE_FILES ${RuntimeAPITest_SOURCE_FILES} ${RuntimeAPITest_HEADER_FILES})
endif()
	 
include_directories(BEFORE ${GTest_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

if(TRENTINO_LOGGING)
	include_directories(
	${Log4cplus_INCLUDE_DIRS}
	)
else()
	include_directories(
	${SCAAPI_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/src
	)
endif()

include_directories(
${CMAKE_SOURCE_DIR}/src
)
add_executable(RuntimeAPITest ${RuntimeAPITest_SOURCE_FILES})
MY_LINK_THIRD_PARTY_LIBRARIES(RuntimeAPITest ${RuntimeAPITest_THIRD_PARTY_LIBS})
target_link_libraries(RuntimeAPITest ${RuntimeAPITest_CUSTOM_LIBS})
target_link_libraries (RuntimeAPITest ${CMAKE_THREAD_LIBS_INIT})

# if(TRENTINO_TESTING) 
   # install(TARGETS RuntimeAPITest ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "RuntimeAPITest")
# endif()
add_test(NAME RuntimeAPITest COMMAND RuntimeAPITest)

set_target_properties(RuntimeAPITest PROPERTIES FOLDER "Tests")
 