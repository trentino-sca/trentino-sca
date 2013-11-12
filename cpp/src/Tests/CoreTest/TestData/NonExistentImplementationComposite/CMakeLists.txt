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
FILE (GLOB NonExistentImplementationComposite_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)
FILE (GLOB NonExistentImplementationComposite_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB NonExistentImplementationComposite_SOURCE_FILES *.cpp)

#libs
set( NonExistentImplementationComposite_THIRD_PARTY_LIBS 
     )
	 
set( NonExistentImplementationComposite_CUSTOM_LIBS 
     )
	 
set( NonExistentImplementationComposite_SOURCE_FILES ${NonExistentImplementationComposite_SOURCE_FILES}
						  ${NonExistentImplementationComposite_HEADER_FILES} 
						  ${NonExistentImplementationComposite_SCA_FILES})

if (WIN32)
	add_definitions(-DBUILDER_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${NonExistentImplementationComposite_SCA_FILES})
endif()

set(TARGET_CONTRIBUTION_DIR ${LIBRARY_OUTPUT_PATH}/TestData/NonExistentImplementationComposite)

###################################################################################################
#										BUSINESS LOGIC                                            #
###################################################################################################
add_library(NonExistentImplementationComposite SHARED ${NonExistentImplementationComposite_SOURCE_FILES})
set_target_properties(NonExistentImplementationComposite PROPERTIES 
	OUTPUT_NAME Builder
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	FOLDER "Tests/CoreTest/TestData" )
add_dependencies(CoreTest NonExistentImplementationComposite)
	
###################################################################################################
#    										GENERATED                                             #
###################################################################################################
TRENGEN( ${CMAKE_CURRENT_SOURCE_DIR}  #in
		 ${CMAKE_CURRENT_BINARY_DIR}  #in
		 ${TARGET_CONTRIBUTION_DIR}   #in
		 generatedSourceFiles         #out
		 generatedConfigFile)         #out

set(generatedFileToModify TrentinoGenModelLoader.cpp)
#modify the generated code to make <implemenation>/@composite refer to a non existent composite
add_custom_command(OUTPUT ${generatedSourceFiles} ${generatedConfigFile}
				   COMMAND ${SED_EXECUTABLE} 
						   -f ${CMAKE_CURRENT_SOURCE_DIR}/modify.sed ${CMAKE_CURRENT_BINARY_DIR}/${generatedFileToModify} 
						   >  ${CMAKE_CURRENT_BINARY_DIR}/${generatedFileToModify}.tmp				   
				   COMMAND ${CMAKE_COMMAND} -E copy 
							${CMAKE_CURRENT_BINARY_DIR}/${generatedFileToModify}.tmp
							${CMAKE_CURRENT_BINARY_DIR}/${generatedFileToModify}	
				   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/modify.sed
				   COMMENT "Executing SED"
				   APPEND)

add_library(NonExistentImplementationCompositeGen SHARED ${generatedSourceFiles})
set_target_properties(NonExistentImplementationCompositeGen PROPERTIES 
	OUTPUT_NAME sca-contribution
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}
	FOLDER "Tests/CoreTest/TestData")
target_link_libraries(NonExistentImplementationCompositeGen Runtime Utils NonExistentImplementationComposite)
include_directories(${CMAKE_SOURCE_DIR}/src)
add_dependencies(CoreTest NonExistentImplementationCompositeGen)

	
