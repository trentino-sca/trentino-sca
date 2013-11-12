#**********************************************************************************
# Trentino - A C++ based lightweight, non-invasive SCA runtime.
# Copyright 2012 by Siemens AG. All rights reserved.
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
#**********************************************************************************

#source and header files
FILE (GLOB SeparateWires_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)
FILE (GLOB SeparateWires_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB SeparateWires_SOURCE_FILES *.cpp)

#libs
set( SeparateWires_THIRD_PARTY_LIBS 
     )
	 
set( SeparateWires_CUSTOM_LIBS 
     )
	 
set( SeparateWires_SOURCE_FILES ${SeparateWires_SOURCE_FILES}
						  ${SeparateWires_HEADER_FILES} 
						  ${SeparateWires_SCA_FILES})

if (WIN32)
	add_definitions(-DSEPARATEWIRES_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${SeparateWires_SCA_FILES})
endif()

set(TARGET_CONTRIBUTION_DIR ${LIBRARY_OUTPUT_PATH}/TestData/SeparateWires)

###################################################################################################
#										BUSINESS LOGIC                                            #
###################################################################################################
add_library(SeparateWires SHARED ${SeparateWires_SOURCE_FILES})
set_target_properties(SeparateWires PROPERTIES 
	OUTPUT_NAME BusinessLogic
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	FOLDER "Tests/CoreTest/TestData" )
add_dependencies(CoreTest SeparateWires)
	
###################################################################################################
#    										GENERATED                                             #
###################################################################################################
TRENGEN( ${CMAKE_CURRENT_SOURCE_DIR}  #in
		 ${CMAKE_CURRENT_BINARY_DIR}  #in
		 ${TARGET_CONTRIBUTION_DIR}   #in
		 generatedSourceFiles         #out
		 generatedConfigFile)         #out

add_library(SeparateWiresGen SHARED ${generatedSourceFiles})

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/SeparateWires_ContributionInfo.cpp PROPERTIES GENERATED TRUE) 
set_target_properties(SeparateWiresGen PROPERTIES 
	OUTPUT_NAME sca-contribution
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}
	FOLDER "Tests/CoreTest/TestData")
target_link_libraries(SeparateWiresGen Runtime Utils SeparateWires)
include_directories(${CMAKE_SOURCE_DIR}/src)
add_dependencies(CoreTest SeparateWiresGen)
	
