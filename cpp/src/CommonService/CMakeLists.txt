# ***********************************************************************************
# Trentino - A C++ based lightweight, non-invasive SCA runtime.
# Copyright (C) Siemens AG, 2012
# All Rights Reserved
# http://trentino.ho.net/
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


if (WIN32)
	set(GEN_INSTALL_COMMAND msbuild INSTALL.vcxproj)
	# we suppose that this is valid for all windows system. starting from XP
	set(SET_MSVC_ENV  )
	SET(MY_CMAKE_COMMAND_OPTIONS -G "Visual Studio 10")
else()
	set(GEN_INSTALL_COMMAND make install)
	set(SET_MSVC_ENV )
	SET(MY_CMAKE_COMMAND_OPTIONS )
endif()
#############################################Build PreferenceService########################3
set(project_name PreferenceService)

#clean up already existing directories
execute_process(COMMAND  ${CMAKE_COMMAND} -E remove_directory ${common_service_dir}/${project_name}_Build)
execute_process(COMMAND  ${CMAKE_COMMAND} -E remove_directory ${common_service_dir}/${project_name})
execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${common_service_dir}/${project_name}Gen_Build)
execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${common_service_dir}/${project_name}Gen)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${common_service_dir}/${project_name}_Build)

#run cmake
execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${common_service_dir}/${project_name}_Build cmake ${MY_CMAKE_COMMAND_OPTIONS}  ${common_service_dir}/${project_name}_Source)

#run install target
execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${common_service_dir}/${project_name}_Build ${GEN_INSTALL_COMMAND})

#generate validate and generate with trengen
set(config_file ${common_service_dir}/trengen_config_local.conf)
#how about remote conf???set(CF_LOC ${CMAKE_CURRENT_SOURCE_DIR}/trengen_config_remote.conf)
execute_process(COMMAND ${TRENTINO_INSTALL_DIR}/bin/Trengen	-cf ${config_file}  -DROOT=${common_service_dir}/../../../  -DPROJECT=${project_name} -DTRENTINO_INSTALLATION=${TRENTINO_INSTALL_DIR} -d )


#create a build folder for the generated code
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${common_service_dir}/${project_name}Gen_Build)

#build the project using cmake
set(ENV{TRENTINO_HOME} ${TRENTINO_INSTALL_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${common_service_dir}/${project_name}Gen_Build cmake ${MY_CMAKE_COMMAND_OPTIONS} ../${project_name}Gen)

#And now install
execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${common_service_dir}/${project_name}Gen_Build ${GEN_INSTALL_COMMAND})


