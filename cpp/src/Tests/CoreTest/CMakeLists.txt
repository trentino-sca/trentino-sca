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
FILE(GLOB CoreTest_HEADER_FILES ./*.h ./*.inl)	  
FILE(GLOB CoreTest_SOURCE_FILES ./*.cpp)	  

#libs
set( CoreTest_THIRD_PARTY_LIBS 
      GTest_LIBRARY
	 ${loggingLib})
	 
set( CoreTest_CUSTOM_LIBS 
     Runtime)
	 
	 
if(MSVC_IDE)
	set(CoreTest_SOURCE_FILES ${CoreTest_SOURCE_FILES} ${CoreTest_HEADER_FILES})	
endif()
	 
include_directories(BEFORE ${GTest_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

add_executable(CoreTest ${CoreTest_SOURCE_FILES})
MY_LINK_THIRD_PARTY_LIBRARIES(CoreTest ${CoreTest_THIRD_PARTY_LIBS})
target_link_libraries(CoreTest ${CoreTest_CUSTOM_LIBS})

# if(TRENTINO_TESTING) 
   # install(TARGETS CoreTest ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "CoreTest")
# endif()
add_test(NAME CoreTest COMMAND CoreTest)

set_target_properties(CoreTest PROPERTIES FOLDER "Tests/CoreTest")

add_subdirectory(TestData)
 