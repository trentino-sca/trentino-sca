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
FILE(GLOB ReflectionRuntimeTest_HEADER_FILES *.h *.inl)	  

#source files
FILE(GLOB ReflectionRuntimeTest_SOURCE_FILES *.cpp)	  

set ( ReflectionRuntimeTest_SOURCE_FILES
	  ${ReflectionRuntimeTest_HEADER_FILES} ${ReflectionRuntimeTest_SOURCE_FILES})  

	  
#libs

find_package (Threads)

set( ReflectionRuntimeTest_THIRD_PARTY_LIBS 
      GTest_LIBRARY
	 GMock_LIBRARY)
	 
set( ReflectionRuntimeTest_CUSTOM_LIBS 
     Runtime)
	 
	 
if(MSVC_IDE)
	set(ReflectionRuntimeTest_SOURCE_FILES ${ReflectionRuntimeTest_SOURCE_FILES} ${ReflectionRuntimeTest_HEADER_FILES})	
endif()
	 
include_directories(BEFORE 	${GMock_INCLUDE_DIRS} ${GTest_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

if(WIN32)
	#turns out __declspecc(dllimport) inside of ReflectionRuntime.lib (because it's a static lib)
	add_definitions(-DREFLECTIONRUNTIME_EXPORTS)
endif()

add_executable(ReflectionRuntimeTest ${ReflectionRuntimeTest_SOURCE_FILES})
MY_LINK_THIRD_PARTY_LIBRARIES(ReflectionRuntimeTest ${ReflectionRuntimeTest_THIRD_PARTY_LIBS})
target_link_libraries (ReflectionRuntimeTest ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(ReflectionRuntimeTest ${ReflectionRuntimeTest_CUSTOM_LIBS})

# if(TRENTINO_TESTING) 
   # install(TARGETS ReflectionRuntimeTest ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "ReflectionRuntimeTest")
# endif()
add_test(NAME ReflectionRuntimeTest COMMAND ReflectionRuntimeTest)

set_target_properties(ReflectionRuntimeTest PROPERTIES FOLDER "Tests")
 