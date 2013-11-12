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

configure_file(TrentinoTestsEnvironmentInfo.h.in ${CMAKE_CURRENT_SOURCE_DIR}/TrentinoTestsEnvironmentInfo.h)

include (${CMAKE_SOURCE_DIR}/my_find_sed.cmake)
MY_FIND_SED()

macro(TRENGEN srcContributionDir #in
			  generatedFilesOutDir #in
			  targetContributionDir #in				  
			  generatedSourceFiles #out
			  generatedConfFile) #out
	#add_custom_command ( OUTPUT AtificialNonExistentDependencyToMakeTheCustomBuiltStepBeExecutedEveryTime
	#					 COMMAND ${CMAKE_COMMAND} -E echo "" )					 

	set(generatedSourceFileNames TrentinoGenModelLoader.cpp 
								 TrentinoGenReflx.cpp 
								 TrentinoGenProxiesWrappers.cpp
								 TrentinoGenProxiesWrappers.h 
								 TrentinoGenContributionInfo.h
								 TrentinoGenContributionInfo.cpp)
	set(generatedConfFileName sca-contribution.conf)
	
	set(${generatedSourceFiles} "" )
	foreach(fileName ${generatedSourceFileNames})
		set(${generatedSourceFiles} ${${generatedSourceFiles}} ${generatedFilesOutDir}/${fileName})
	endforeach()	
	
	set(${generatedConfFile} ${generatedFilesOutDir}/${generatedConfFileName})
	
	add_custom_command( OUTPUT ${${generatedSourceFiles}} ${${generatedConfFile}}								
						#DEPENDS AtificialNonExistentDependencyToMakeTheCustomBuiltStepBeExecutedEveryTime
						COMMAND Trengen -cont ${srcContributionDir} -outdir ${generatedFilesOutDir}
						COMMAND ${CMAKE_COMMAND} -E copy ${${generatedConfFile}}
														  ${targetContributionDir}/META-INF/${generatedConfFileName}						 								  
						VERBATIM )	
endmacro(TRENGEN)

#------------------------------------------------------------------------------
# MY_CREATE_VALIDATE_GENERATE_INSTALL_TARGET
# project_name is the name of the project e.g HelloWorld for HelloWorld_Source
# and BasicCalculator for BasicCalculator_Source
# it corresponds to a folder name in the directoy specified by the project path
# project_path is the path to the parent directory that contains the project
#project_rel_path path of the rpoject relative to system test data
#-------------------------------------------------------------------------------
macro(MY_COMPILE_SYSTEM_TEST_DATA project_path config_file  project_rel_path project_name custom_target)

if (WIN32)
	set(GEN_INSTALL_COMMAND msbuild INSTALL.vcxproj)
	set(SET_TRENTINO_HOME call SET TRENTINO_HOME=${DEFAULT_INSTALL_PATH}/${TARGET_TRENTINO_DIR})
	# we suppose that this is valid for all windows system. starting from XP
	set(SET_MSVC_ENV  )
	SET(MY_CMAKE_COMMAND_OPTIONS -G "Visual Studio 10")
else()
	set(GEN_INSTALL_COMMAND make install)
	set(SET_TRENTINO_HOME export TRENTINO_HOME=${DEFAULT_INSTALL_PATH}/${TARGET_TRENTINO_DIR})
	set(SET_MSVC_ENV )
	SET(MY_CMAKE_COMMAND_OPTIONS )
endif()
add_custom_target([${custom_target}]
#set vidual studio command line promt
COMMAND ${SET_MSVC_ENV}
#set trentino home
COMMAND ${SET_TRENTINO_HOME}
#create build directoty
COMMAND ${CMAKE_COMMAND} -E remove_directory ${project_name}_Build
COMMAND ${CMAKE_COMMAND} -E remove_directory ${project_name}Gen_Build
COMMAND ${CMAKE_COMMAND} -E make_directory ${project_name}_Build
#install the application first

#run cmake
COMMAND ${CMAKE_COMMAND} -E chdir ${project_name}_Build cmake ${MY_CMAKE_COMMAND_OPTIONS}  ${project_path}/${project_name}_Source
#run install target
COMMAND ${CMAKE_COMMAND} -E chdir ${project_name}_Build ${GEN_INSTALL_COMMAND}
#generate validate and generate with trengen
COMMAND Trengen	-cf ${config_file} -DROOT=${CMAKE_CURRENT_SOURCE_DIR}/../../../../ -DPROJECT=${project_rel_path}
#create a build folder for the generated code
COMMAND ${CMAKE_COMMAND} -E make_directory ${project_name}Gen_Build
#build the project using cmake
COMMAND ${CMAKE_COMMAND} -E chdir ${project_name}Gen_Build cmake ${MY_CMAKE_COMMAND_OPTIONS} ../${project_name}Gen
#And now install
COMMAND ${CMAKE_COMMAND} -E chdir ${project_name}Gen_Build ${GEN_INSTALL_COMMAND}
WORKING_DIRECTORY ${project_path}
VERBATIM
)
set_target_properties([${project_name}] PROPERTIES FOLDER "Tests/SystemTestData/TestData")
endmacro(MY_COMPILE_SYSTEM_TEST_DATA)

add_subdirectory(ConsoleTest)
if(TRENTINO_BUILD_CORETESTS)
	add_subdirectory(CoreTest)
endif()
add_subdirectory(ReflectionRuntimeTest)
add_subdirectory(UtilsTest)
add_subdirectory(RuntimeAPITest)
add_subdirectory(XMLTest)
#add_subdirectory(BindingSCAClientTest)
add_subdirectory(BindingSCATest)
add_subdirectory(SCAReferenceExampleTest)
add_subdirectory(TrentinoTest)
add_subdirectory(Mocks)
#add_subdirectory(DiscoveryTest)
#add_subdirectory(BindingIpcTest)

# the next line is for not to fail in tests
configure_file(../../res/slp.conf ${CMAKE_BINARY_DIR}/src/Tests/cfg/slp.conf COPYONLY)

## Integration level test. Will build if inputs data from SystemTestData can also build
if(TRENTINO_INTEGRATION_TESTING)
    add_subdirectory(RuntimeTest)
	add_subdirectory(BasicCalculatorReturnVoidTest)
endif()

set(SystemTestDataFolder ${CMAKE_CURRENT_SOURCE_DIR}/SystemTestData)
set(HOME_VAL $ENV{TRENTINO_HOME})
get_filename_component(HOME_VAL ${HOME_VAL} REALPATH)
#STRING(REGEX REPLACE "/" "\\\\" HOME_VAL ${HOME_VAL} )
set (REMOTE_INCLUDES ${HOME_VAL}/include/protobuf-2.4.1/include)
set(REMOTE_LIB_DIR ${HOME_VAL}/lib/protobuf-2.4.1)
set(CF_REM ${CMAKE_CURRENT_SOURCE_DIR}/SystemTestData/trengen_config_remote.conf)
set(CF_LOC ${CMAKE_CURRENT_SOURCE_DIR}/SystemTestData/trengen_config_local.conf)

MY_COMPILE_SYSTEM_TEST_DATA(${SystemTestDataFolder}/BasicCalculatorWithLifeCycle_Test ${CF_LOC} BasicCalculatorWithLifeCycle_Test/BasicCalculatorWithLifeCycle BasicCalculatorWithLifeCycle BasicCalculatorWithLifeCycle)
MY_COMPILE_SYSTEM_TEST_DATA(${SystemTestDataFolder}/HelloWorldRemote ${CF_REM} HelloWorldRemote/HelloWorldRemote HelloWorldRemote HelloWorldRemote)
MY_COMPILE_SYSTEM_TEST_DATA(${SystemTestDataFolder}/HelloWorldRemote ${CF_REM} HelloWorldRemote/HelloWorldRemoteClient HelloWorldRemoteClient HelloWorldRemoteClient)
MY_COMPILE_SYSTEM_TEST_DATA(${SystemTestDataFolder} ${CF_REM} BasicCalculatorRemoteClient BasicCalculatorRemoteClient BasicCalculatorRemoteClient)
MY_COMPILE_SYSTEM_TEST_DATA(${SystemTestDataFolder} ${CF_REM} BasicCalculatorRemote BasicCalculatorRemote BasicCalculatorRemote)
MY_COMPILE_SYSTEM_TEST_DATA(${SystemTestDataFolder} ${CF_LOC} BasicCalculator BasicCalculator BasicCalculator)
MY_COMPILE_SYSTEM_TEST_DATA(${SystemTestDataFolder} ${CF_REM} BasicCalculatorRemoteNotEnclosedTypes BasicCalculatorRemoteNotEnclosedTypes BasicCalculatorRemoteNotEnclosedTypes)
MY_COMPILE_SYSTEM_TEST_DATA(${SystemTestDataFolder} ${CF_REM} BasicPrinter BasicPrinter BasicPrinter)
MY_COMPILE_SYSTEM_TEST_DATA(${SystemTestDataFolder} ${CF_REM} BasicPrinterClient BasicPrinterClient BasicPrinterClient)
MY_COMPILE_SYSTEM_TEST_DATA(${SystemTestDataFolder} ${CF_LOC} LocalCallDataExchange LocalCallDataExchange LocalCallDataExchange)
MY_COMPILE_SYSTEM_TEST_DATA(${SystemTestDataFolder}/PerformanceTest_BasicCalculator ${CF_REM}  PerformanceTest_BasicCalculator/BasicCalculatorRemote BasicCalculatorRemote BasicCalculatorRemotePerf)
MY_COMPILE_SYSTEM_TEST_DATA(${SystemTestDataFolder}/PerformanceTest_BasicCalculator ${CF_REM}  PerformanceTest_BasicCalculator/BasicCalculatorRemoteClient BasicCalculatorRemoteClient BasicCalculatorRemotePerfClient)
add_custom_target([Build_System_Test_Data]
WORKING_DIRECTORY ${SystemTestDataFolder}
VERBATIM
)

add_dependencies([Build_System_Test_Data] [BasicCalculatorWithLifeCycle] 
                                          [HelloWorldRemote] 
                                          [HelloWorldRemoteClient] 
										  [BasicCalculatorRemoteClient] 
										  [BasicCalculatorRemote] 
										  [BasicCalculator]
										  [BasicCalculatorRemoteNotEnclosedTypes]
										  [BasicPrinter]
										  [BasicPrinterClient]
										  [LocalCallDataExchange]
										  )

set_target_properties([Build_System_Test_Data] PROPERTIES FOLDER "Tests/SystemTestData")

add_custom_target([Build_Performance_Test_Data]
WORKING_DIRECTORY ${SystemTestDataFolder}
VERBATIM
)

add_dependencies([Build_Performance_Test_Data] [BasicCalculatorRemotePerf] 
                                          [BasicCalculatorRemotePerfClient]
										  )
set_target_properties([Build_Performance_Test_Data] PROPERTIES FOLDER "Tests/SystemTestData")