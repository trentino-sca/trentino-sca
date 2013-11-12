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

cmake_minimum_required(VERSION 2.6)
project (Trengen)
#source files
set ( Trengen_SOURCE_FILES
      Trengen.cpp)

#libs
set( Trengen_THIRD_PARTY_LIBS 
     Boost_FILESYSTEM_LIBRARY
	 Boost_SYSTEM_LIBRARY)

set(Trengen_CUSTOM_LIBS 
    Utils)

find_package (Threads)

include_directories(${Boost_INCLUDE_DIRS})
	  
if(MSVC_IDE)
	set(CMAKE_MFC_FLAG 2)
	set(Trengen_SOURCE_FILES ${Trengen_SOURCE_FILES} )	
endif()


if(CMAKE_COMPILER_IS_GNUCXX)
	set(Trengen_SOURCE_FILES ${Trengen_SOURCE_FILES} )	
endif()


add_executable(Trengen ${Trengen_SOURCE_FILES})

#######section-begin:  to copy the jar in dist folder to the buidl path
set(target_location "")
set(target_path "")
get_target_property(target_location Trengen LOCATION)
get_filename_component(target_path ${target_location} PATH)
get_filename_component(source_path ../../../java/dist/Trengen.jar PATH)
add_custom_command( TARGET Trengen POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../../../java/dist/Trengen.jar ${target_path}/Trengen.jar)
add_custom_command( TARGET Trengen POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../../../java/org.trentino.trengen.cpp.parser.eclipse/lib/org.eclipse.cdt.core_5.3.1.201109151620.jar ${target_path}/org.eclipse.cdt.core_5.3.1.201109151620.jar)
add_custom_command( TARGET Trengen POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../../../java/org.trentino.trengen.cpp.parser.eclipse/lib/org.eclipse.core.resources_3.7.100.v20110510-0712.jar ${target_path}/org.eclipse.core.resources_3.7.100.v20110510-0712.jar)
add_custom_command( TARGET Trengen POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../../../java/org.trentino.trengen.cpp.parser.eclipse/lib/org.eclipse.equinox.common_3.6.0.v20110523.jar ${target_path}/org.eclipse.equinox.common_3.6.0.v20110523.jar)
add_custom_command( TARGET Trengen POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../../../java/org.trentino.trengen.tools/protoc.exe ${target_path}/protoc.exe)
######section-end:  to copy the jar in dist folder to the buidl path

install(TARGETS Trengen DESTINATION ${TARGET_BIN_DIR})
install(FILES ../../../java/dist/Trengen.jar DESTINATION ${TARGET_BIN_DIR})
install(FILES ../../../java/org.trentino.trengen.cpp.parser.eclipse/lib/org.eclipse.cdt.core_5.3.1.201109151620.jar DESTINATION ${TARGET_BIN_DIR})
install(FILES ../../../java/org.trentino.trengen.cpp.parser.eclipse/lib/org.eclipse.core.resources_3.7.100.v20110510-0712.jar DESTINATION ${TARGET_BIN_DIR})
install(FILES ../../../java/org.trentino.trengen.cpp.parser.eclipse/lib/org.eclipse.equinox.common_3.6.0.v20110523.jar DESTINATION ${TARGET_BIN_DIR})
install(FILES ../../../java/org.trentino.trengen.tools/protoc.exe DESTINATION ${TARGET_BIN_DIR})
install(FILES ../../../java/dist/trengen.config DESTINATION ${TARGET_CFG_DIR})

set_target_properties(Trengen PROPERTIES FOLDER "Executables")
set_target_properties(Trengen PROPERTIES OUTPUT_NAME "trengen")

if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(Trengen PROPERTIES INSTALL_RPATH "../lib")
endif()

target_link_libraries(Trengen ${Trengen_CUSTOM_LIBS}) 
target_link_libraries (Trengen ${CMAKE_THREAD_LIBS_INIT})
MY_LINK_THIRD_PARTY_LIBRARIES(Trengen ${Trengen_THIRD_PARTY_LIBS} )

if(CPPCHECK_GENERATE)
add_cppcheck(Trengen ${Trengen_SOURCE_FILES})                     
endif()

if(VERA_GENERATE)
add_vera(Trengen ${Trengen_SOURCE_FILES})                     
endif()