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
FILE (GLOB NonExistentComponentType_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)
FILE (GLOB NonExistentComponentType_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB NonExistentComponentType_SOURCE_FILES *.cpp)

#libs
set( NonExistentComponentType_THIRD_PARTY_LIBS 
     )
	 
set( NonExistentComponentType_CUSTOM_LIBS 
     )
	 
set( NonExistentComponentType_SOURCE_FILES ${NonExistentComponentType_SOURCE_FILES}
						  ${NonExistentComponentType_HEADER_FILES} 
						  ${NonExistentComponentType_SCA_FILES})

if (WIN32)
	add_definitions(-DBUILDER_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${NonExistentComponentType_SCA_FILES})
endif()

set(TARGET_CONTRIBUTION_DIR ${LIBRARY_OUTPUT_PATH}/TestData/NonExistentComponentType)

###################################################################################################
#										BUSINESS LOGIC                                            #
###################################################################################################
add_library(NonExistentComponentType SHARED ${NonExistentComponentType_SOURCE_FILES})
set_target_properties(NonExistentComponentType PROPERTIES 
	OUTPUT_NAME Builder
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	FOLDER "Tests/CoreTest/TestData" )	
add_dependencies(CoreTest NonExistentComponentType) 

###################################################################################################
#    										GENERATED                                             #
###################################################################################################
TRENGEN( ${CMAKE_CURRENT_SOURCE_DIR}  #in
		 ${CMAKE_CURRENT_BINARY_DIR}  #in
		 ${TARGET_CONTRIBUTION_DIR}   #in
		 generatedSourceFiles         #out
		 generatedConfigFile)         #out
set(generatedFileToModify TrentinoGenModelLoader.cpp)
#modify the generated code to have some components with no associated component types 
add_custom_command( OUTPUT ${generatedSourceFiles} ${generatedConfigFile}
				    COMMAND ${SED_EXECUTABLE} 
						    -f ${CMAKE_CURRENT_SOURCE_DIR}/modify.sed ${CMAKE_CURRENT_BINARY_DIR}/${generatedFileToModify} 
						    >  ${CMAKE_CURRENT_BINARY_DIR}/${generatedFileToModify}.tmp				   
				    COMMAND ${CMAKE_COMMAND} -E copy 
							${CMAKE_CURRENT_BINARY_DIR}/${generatedFileToModify}.tmp
							${CMAKE_CURRENT_BINARY_DIR}/${generatedFileToModify}	
				    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/modify.sed
				    COMMENT "Executing SED"
				    APPEND)

add_library(NonExistentComponentTypeGen SHARED ${generatedSourceFiles})
set_target_properties(NonExistentComponentTypeGen PROPERTIES 
	OUTPUT_NAME sca-contribution
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}
	FOLDER "Tests/CoreTest/TestData")
target_link_libraries(NonExistentComponentTypeGen Runtime Utils NonExistentComponentType)
include_directories(${CMAKE_SOURCE_DIR}/src)
add_dependencies(CoreTest NonExistentComponentTypeGen) 

	
