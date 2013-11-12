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
FILE (GLOB NonExistentProxyReflectObject_HEADER_FILES *.h *.inl
	  services/*.h services/*.inl)
FILE (GLOB NonExistentProxyReflectObject_SCA_FILES *.xml  *.componentType META-INF/*.xml META-INF/*.composite)
FILE (GLOB NonExistentProxyReflectObject_SOURCE_FILES *.cpp)

#libs
set( NonExistentProxyReflectObject_THIRD_PARTY_LIBS 
     )
	 
set( NonExistentProxyReflectObject_CUSTOM_LIBS 
     )
	 
set( NonExistentProxyReflectObject_SOURCE_FILES ${NonExistentProxyReflectObject_SOURCE_FILES}
						  ${NonExistentProxyReflectObject_HEADER_FILES} 
						  ${NonExistentProxyReflectObject_SCA_FILES})

if (WIN32)
	add_definitions(-DBUILDER_EXPORTS)
endif()

if(MSVC_IDE)
	source_group("SCA Files" FILES ${NonExistentProxyReflectObject_SCA_FILES})
endif()

set(TARGET_CONTRIBUTION_DIR ${LIBRARY_OUTPUT_PATH}/TestData/NonExistentProxyReflectObject)

###################################################################################################
#										BUSINESS LOGIC                                            #
###################################################################################################
add_library(NonExistentProxyReflectObject SHARED ${NonExistentProxyReflectObject_SOURCE_FILES})
set_target_properties(NonExistentProxyReflectObject PROPERTIES 
	OUTPUT_NAME Builder
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}
	FOLDER "Tests/CoreTest/TestData" )
add_dependencies(CoreTest NonExistentProxyReflectObject)

###################################################################################################
#    										GENERATED                                             #
###################################################################################################
TRENGEN( ${CMAKE_CURRENT_SOURCE_DIR}  #in
		 ${CMAKE_CURRENT_BINARY_DIR}  #in
		 ${TARGET_CONTRIBUTION_DIR}   #in
		 generatedSourceFiles         #out
		 generatedConfigFile)         #out

set(generatedFileToModify TrentinoGenProxiesWrappers.cpp)
#modify the generated code to have no proxy reflection code for some services
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

add_library(NonExistentProxyReflectObjectGen SHARED ${generatedSourceFiles})
set_target_properties(NonExistentProxyReflectObjectGen PROPERTIES 
	OUTPUT_NAME sca-contribution
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TARGET_CONTRIBUTION_DIR}/META-INF
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TARGET_CONTRIBUTION_DIR}/META-INF
	INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}
	FOLDER "Tests/CoreTest/TestData")
target_link_libraries(NonExistentProxyReflectObjectGen Runtime Utils NonExistentProxyReflectObject)
include_directories(${CMAKE_SOURCE_DIR}/src)
add_dependencies(CoreTest NonExistentProxyReflectObjectGen)
	
