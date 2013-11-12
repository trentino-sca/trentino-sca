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
FILE (GLOB ValidContribution1_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)
FILE (GLOB ValidContribution1_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB ValidContribution1_SOURCE_FILES *.cpp)

#libs
set( ValidContribution1_THIRD_PARTY_LIBS 
     )
	 
set( ValidContribution1_CUSTOM_LIBS 
     )
	 
set( ValidContribution1_SOURCE_FILES ${ValidContribution1_SOURCE_FILES}
						  ${ValidContribution1_HEADER_FILES} 
						  ${ValidContribution1_SCA_FILES})

if (WIN32)
	add_definitions(-DVALIDCONTRIBUITION1_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${ValidContribution1_SCA_FILES})
endif()

set(TARGET_CONTRIBUTION_DIR ${LIBRARY_OUTPUT_PATH}/TestData/ValidContribution1)

###################################################################################################
#										BUSINESS LOGIC                                            #
###################################################################################################
add_library(ValidContribution1 SHARED ${ValidContribution1_SOURCE_FILES})
set_target_properties(ValidContribution1 PROPERTIES 
	OUTPUT_NAME BusinessLogic
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	FOLDER "Tests/CoreTest/TestData" )
add_dependencies(CoreTest ValidContribution1)
	
###################################################################################################
#    										GENERATED                                             #
###################################################################################################
TRENGEN( ${CMAKE_CURRENT_SOURCE_DIR}  #in
		 ${CMAKE_CURRENT_BINARY_DIR}  #in
		 ${TARGET_CONTRIBUTION_DIR}   #in
		 generatedSourceFiles         #out
		 generatedConfigFile)         #out

add_library(ValidContribution1Gen SHARED ${generatedSourceFiles})
set_target_properties(ValidContribution1Gen PROPERTIES 
	OUTPUT_NAME sca-contribution
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}
	FOLDER "Tests/CoreTest/TestData")
target_link_libraries(ValidContribution1Gen Runtime Utils ValidContribution1)
include_directories(${CMAKE_SOURCE_DIR}/src)
add_dependencies(CoreTest ValidContribution1Gen)
	
