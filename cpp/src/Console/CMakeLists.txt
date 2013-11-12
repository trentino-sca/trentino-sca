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
FILE(GLOB Console_HEADER_FILES *.h *.inl)	  
FILE(GLOB Console_SOURCE_FILES *.cpp)	 

find_package (Threads)
 
set(Console_SOURCE_FILES ${Console_SOURCE_FILES} 
						 ../RuntimeService/TrentinoRuntimeServiceControl.cpp)

#libs
set( Console_THIRD_PARTY_LIBS 
     Boost_FILESYSTEM_LIBRARY
	 Boost_SYSTEM_LIBRARY
    Boost_THREAD_LIBRARY
    Boost_DATE_TIME_LIBRARY
	 ${loggingLib})


set( Console_CUSTOM_LIBS
     Utils)
	 
set( Console_SOURCE_FILES ${Console_SOURCE_FILES}
						  ${Console_HEADER_FILES})

include_directories(${Boost_INCLUDE_DIRS})

if(TRENTINO_LOGGING)
	include_directories(${Log4cplus_INCLUDE_DIRS})
endif()


add_executable(Console ${Console_SOURCE_FILES})
set_target_properties(Console PROPERTIES OUTPUT_NAME TrentinoConsole)
target_link_libraries(Console ${Console_CUSTOM_LIBS})
target_link_libraries (Console ${CMAKE_THREAD_LIBS_INIT})

if(CMAKE_COMPILER_IS_GNUCXX)
   set_target_properties(Console PROPERTIES INSTALL_RPATH "../lib")
   set_target_properties(Console PROPERTIES LINK_FLAGS "-ldl")
   target_link_libraries(Console ${DL_LIB})
endif()

MY_LINK_THIRD_PARTY_LIBRARIES(Console ${Console_THIRD_PARTY_LIBS} )
install(TARGETS Console DESTINATION ${TARGET_BIN_DIR} )

set_target_properties(Console PROPERTIES FOLDER "Executables")

if(CPPCHECK_GENERATE)
add_cppcheck(Console ${Console_SOURCE_FILES})                     
endif()

if(VERA_GENERATE)
add_vera(Console ${Console_SOURCE_FILES})                     
endif()