# ***********************************************************************************
# Trentino - A C++ based lightweight, non-invasive SCA runtime.
# Copyright (C) Siemens AG, 2012
# All Rights Copy
# http://trentino.sourceforge.net/TARGET_TRENTINO_DIR
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; opensl
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

cmake_minimum_required(VERSION 2.8.4)
project(Trentino)

##############################################################################
#                                Project Include
##############################################################################
Include(CheckIncludeFiles)
Include(CheckLibraryExists)


##############################################################################
#                                CMAKE OPTIONS                               #
##############################################################################
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

##############################################################################
#                               CUSTOM OPTIONS                               #
##############################################################################

option(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR 
		"use trentino's default 3rdParty directory provided in TRENTINO_THIRD_PARTY_DIR" ON)

option(TRENTINO_BUILD_TRENGEN 
		"enable or disable trengen build" ON)

option(TRENTINO_BUILD_CORETESTS 
		"enable or disable trengen build" OFF)

set (DEFAULT_INSTALL_PATH ${PROJECT_SOURCE_DIR}/../../Binaries)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
   set (CMAKE_INSTALL_PREFIX ${DEFAULT_INSTALL_PATH} CACHE STRING "Install path" FORCE)
endif()
		
if(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR)
	
	if(MSVC90)
		set(3rdpartyDirSuffix x86_windows/vc9)
	elseif(MSVC10)
		set(3rdpartyDirSuffix x86_windows/vc10)
	elseif(CYGWIN)
		set(3rdpartyDirSuffix x86_cygwin)
		execute_process(COMMAND chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party.sh)
		execute_process(COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party.sh ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR})
	else(NOT WIN32)
		set(3rdpartyDirSuffix x86_linux)
		execute_process(COMMAND chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party.sh)
		execute_process(COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party.sh ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR})
	endif()
	
	set(TRENTINO_THIRD_PARTY_DIR ./3rdparty/${3rdpartyDirSuffix} CACHE PATH  
			"path to the directory containing third party artifacts" )
endif()

#set(CMAKE_SYSTEM_PROCESSOR "x86" CACHE STRING "target architecture: x86 or arm")
if(WIN32)
	set(TRENTINO_WIN32_WINNT "0x0502" CACHE STRING 
		"possible values: 0x0500 (Win 2000), 0x0501 (Win XP), 0x0600 (Win Vista), 0x0502 (Win Server 2003), 0x0601 (Win 7)")
endif()
option(TRENTINO_LOGGING "turns logging on/off" ON)
option(TRENTINO_DEV "determines whether the project is configured mainly for development or distribution" ON)

if(CYGWIN)
	option(TRENTINO_TESTING "build test projects?" OFF)
else()
	option(TRENTINO_TESTING "build test projects?" ON)
endif()

option(TRENTINO_INTEGRATION_TESTING "build test projects?" OFF)
option(TRENTINO_DEBUG_OUTPUT "enable debug output?" OFF)

#Enable CTests testing
if(TRENTINO_TESTING)
    ENABLE_TESTING()
endif()

#global logginglib variable
if(TRENTINO_LOGGING)
	set(loggingLib Log4cplus_LIBRARY)
endif()

##############################################################################
# 								COMPILER OPTIONS  							 #
##############################################################################
if(MSVC)
	add_definitions(/W4)
	add_definitions(/WX)
	add_definitions(/wd4251)
	add_definitions(/wd4275)
else()
	add_definitions(-Wall -pedantic -Wno-variadic-macros -Wno-unknown-pragmas -Wno-long-long)
endif()

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DBOOST_ALL_DYN_LINK)


##############################################################################
# 							   OUTPUT CONFIGURATION						     #
##############################################################################
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}${CMAKE_SYSTEM_NAME})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}${CMAKE_SYSTEM_NAME})

#if(MSVC_IDE)
#	#make CMake put all xml-files in the "Resource Files"-tab in Visual Studio's solution explorer
#	source_group("Resource Files" REGULAR_EXPRESSION  ".*\\.xml")	
#endif()

##############################################################################
# 							PREPROCESSOR DEFINITIONS						 #
##############################################################################
if(WIN32)
	#disable boost's autolink feature
	add_definitions(-DBOOST_ALL_NO_LIB -D_WIN32_WINNT=${TRENTINO_WIN32_WINNT}
	-D_WINVER=${TRENTINO_WIN32_WINNT})
endif()
if(TRENTINO_LOGGING)
	add_definitions(-DTRENTINO_LOGGING)
endif()
if(TRENTINO_DEBUG_OUTPUT)
	add_definitions(-DTRENTINO_DEBUG_OUTPUT)
endif()



##############################################################################
# 							LIBDL CHECK UNIX 				                 #
##############################################################################
if(NOT MSVC)
 Check_Library_Exists(dl dlopen "" TRENTINO_LIBDL_EXISTS)
  if(NOT TRENTINO_LIBDL_EXISTS)
    message(SEND_ERROR "libdl was not found in your system")
  else()
   FIND_LIBRARY(DL_LIB NAMES dl )
   MESSAGE( STATUS "using dl library: ${DL_LIB}" )
  endif()
endif()
##############################################################################
# 							VARS FOR BUILD TYPES							 #
##############################################################################
set(IS_BUILD_TYPE_DEBUG TRUE)
set(IS_BUILD_TYPE_RELEASE TRUE)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

if(MSVC_IDE)
	list(FIND CMAKE_CONFIGURATION_TYPES Debug CONF_TYPE)
	if(CONF_TYPE EQUAL -1)
		set(IS_BUILD_TYPE_DEBUG FALSE)
	endif()

	list(FIND CMAKE_CONFIGURATION_TYPES Release CONF_TYPE)
	list(FIND CMAKE_CONFIGURATION_TYPES RelWithDebInfo CONF_TYPE2)
	list(FIND CMAKE_CONFIGURATION_TYPES MinSizeRel CONF_TYPE3)
	if(CONF_TYPE EQUAL -1 AND CONF_TYPE2 EQUAL -1 AND CONF_TYPE3 EQUAL -1  )
		set(IS_BUILD_TYPE_RELEASE FALSE)
	endif()
else()
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(IS_BUILD_TYPE_RELEASE FALSE)
	else()
		set(IS_BUILD_TYPE_DEBUG FALSE)
	endif()
endif(MSVC_IDE)

##############################################################################
# 									MACROS									 #
##############################################################################

#----------------------------------
# MY_LINK_THIRD_PARTY_LIBRARIES 
#----------------------------------
#The libs to be linked to are expected to be passed as additional arguments after 'target'.
#This arguments have to be uncomplete variable names representing the libs
#The macro will append '_DEBUG' respectively '_RELEASE' to the passed arguments
#in order to produce real variable names that are expected to contain the real lib names.
#EXAMPLE: 
#The call MY_LINK_THIRD_PARTY_LIBRARIES(main Boost_FILESYSTEM_LIBRARY) expects the variables
#'Boost_FILESYSTEM_LIBRARY_DEBUG' (if build type is debug) respectively 
#'Boost_FILESYSTEM_LIBRARY_RELEASE' (if build type is release) to be defined
#----------------------------
macro(MY_LINK_THIRD_PARTY_LIBRARIES target)
	foreach(lib ${ARGN})
		if(IS_BUILD_TYPE_DEBUG)			
			target_link_libraries(${target} debug  ${${lib}_DEBUG})
		endif()
		if(IS_BUILD_TYPE_RELEASE)			
			target_link_libraries(${target} optimized ${${lib}_RELEASE})
		endif()		
	endforeach()	
endmacro(MY_LINK_THIRD_PARTY_LIBRARIES)

#----------------------------------
# MY_FIND_LIBRARY
#----------------------------------
#Searches a library in the specified path and prints an error message on failure
#used by MY_FIND_* macros contained in the corresponding my_find_*.cmake files
#---------------------------
macro(MY_FIND_LIBRARY var lib path)
	find_library(${var} ${lib} PATHS ${path} NO_DEFAULT_PATH)	
	if(NOT ${var})		
		message(SEND_ERROR "Library ${var} ${lib} ${path} not found")
	endif()
endmacro(MY_FIND_LIBRARY)

#----------------------------------
# MAKE_DLL_NAME
#----------------------------------
#Replaces the file extension of the given library file path with
#the os specific shared/dynamic library extension
#---------------------------------
macro(MAKE_DLL_NAME libraryFilePath dllFilePath)
	get_filename_component(libraryPath ${libraryFilePath} PATH)
	get_filename_component(libraryFileName ${libraryFilePath} NAME_WE)	
	set(${dllFilePath} ${libraryPath}/${libraryFileName}${CMAKE_SHARED_LIBRARY_SUFFIX} CACHE PATH "")		
endmacro(MAKE_DLL_NAME)


#----------------------------------
# MY_ADD_CUSTOM_COMMAND_PROTOC 
#----------------------------------
macro(MY_ADD_CUSTOM_COMMAND_PROTOC sourceFile)
	#replace the source file extension by 'pb.cpp', 'pb.cc' and 'pb.h'
	string(REGEX REPLACE "(.*)\\..*$" "\\1.pb.cpp" targetCppFile ${sourceFile})	
	string(REGEX REPLACE "(.*)\\..*$" "\\1.pb.cc" intermCcFile ${sourceFile})	
	string(REGEX REPLACE "(.*)\\..*$" "\\1.pb.h" targetHFile ${sourceFile})	
	
	if(WIN32)
		set(ld_library_path_settings "")
	else()
		if(IS_BUILD_TYPE_DEBUG)
			set(suffix "DEBUG")
		else()
			set(suffix "RELEASE")
		endif()	
		set(ld_library_path_settings "LD_LIBRARY_PATH=${TRENTINO_PROTOBUF_LIB_DIR_${suffix}}")	
	endif()

	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${targetCppFile} ${CMAKE_CURRENT_SOURCE_DIR}/${targetHFile}
		COMMAND ${ld_library_path_settings} ${Protobuf_EXECUTABLE_PROTOC} -I=${CMAKE_CURRENT_SOURCE_DIR} 
												--cpp_out=${CMAKE_CURRENT_SOURCE_DIR}
												${CMAKE_CURRENT_SOURCE_DIR}/${sourceFile}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${intermCcFile}
										${CMAKE_CURRENT_SOURCE_DIR}/${targetCppFile}
		COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_CURRENT_SOURCE_DIR}/${intermCcFile}
		MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${sourceFile}
		VERBATIM)
endmacro(MY_ADD_CUSTOM_COMMAND_PROTOC)

##############################################################################
#                        THIRD PARTY LIB CONFIGURATION                       #
##############################################################################

#TODO: refactor: write a finder or make otherwise sure that the correct 3rdparty
#      directory is used (see TRENTINO_THIRD_PARTY_DIR) 
#set(SCAAPI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/sca_api)
set(RUNTIME_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/Runtime)
set(GLOBAL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/Global)


include(my_find_boost.cmake)
include(my_find_protobuf.cmake)
include(my_find_zeromq.cmake)
#include(my_find_openslp.cmake)
if(TRENTINO_LOGGING)
	include(my_find_log4cplus.cmake)
endif()
if(TRENTINO_TESTING)
	include(my_find_gtest.cmake)
    include(my_find_gmock.cmake)
endif()

option(OpenSlpEnable "Enable/disable OpenSlp build: temporary option before openSlp is fully checked in" ON)

if(IS_BUILD_TYPE_DEBUG)
	MY_FIND_BOOST(debug)	
	MY_FIND_PROTOBUF(debug)
	MY_FIND_ZEROMQ(debug)
if(OpenSlpEnable)   
	#MY_FIND_OPENSLP(debug)
endif()    
	if(TRENTINO_LOGGING)
		MY_FIND_LOG4CPLUS(debug)
	endif()
	if(TRENTINO_TESTING)
		MY_FIND_GTEST(debug)
		MY_FIND_GMOCK(debug)
	endif()
endif()
if(IS_BUILD_TYPE_RELEASE)
	MY_FIND_BOOST(release)
	MY_FIND_PROTOBUF(release)
	MY_FIND_ZEROMQ(release)
if(OpenSlpEnable)   
	#MY_FIND_OPENSLP(release)
endif()    
	if(TRENTINO_LOGGING)
		MY_FIND_LOG4CPLUS(release)
	endif()
	if(TRENTINO_TESTING)
		MY_FIND_GTEST(release)
		MY_FIND_GMOCK(release)
	endif()
endif()

if (NOT OpenSlpEnable) 
 set(OpenSlp_INCLUDE_DIRS " ")
endif()

set(libList Boost Protobuf)
if(TRENTINO_LOGGING) 
	set(libList ${libList} Log4cplus) 	
endif()

foreach(i ${libList})
	if(NOT ${i}_FOUND) 
		message(SEND_ERROR "${i} library not found!")
	endif()	
endforeach()

##############################################################################
#                       THIRD PARTY BIN CONFIGURATION                        #
##############################################################################
include(my_find_protobuf_protoc.cmake)
MY_FIND_PROTOBUF_PROTOC()

if(NOT Protobuf_EXECUTABLE_PROTOC)
	message(SEND_ERROR "protoc not found!")
endif()
if(NOT WIN32 AND NOT Protobuf_LIBRARY_PROTOC)
	message(SEND_ERROR "protoc library not found!")
endif()

##############################################################################
#                                    INSTALL                                 #
##############################################################################
if(WIN32)
	set(DLL_TARGET_KIND RUNTIME) #used by subordinate CMakeLists.txt files
else()
	set(DLL_TARGET_KIND LIBRARY) #used by subordinate CMakeLists.txt files
endif()

include(trentino_version.cmake)
set(TARGET_TRENTINO_DIR trentino_${TRENTINO_FULL_VERSION_STRING})
set(TARGET_BIN_DIR ${TARGET_TRENTINO_DIR}/bin)
set(CTEST_BINARY_DIRECTORY ${TARGET_BIN_DIR} CACHE STRING "CTest path" FORCE)
set(TARGET_LIB_DIR ${TARGET_TRENTINO_DIR}/lib)
if(WIN32)
	set(TARGET_DLL_DIR ${TARGET_TRENTINO_DIR}/bin)
else()
	set(TARGET_DLL_DIR ${TARGET_TRENTINO_DIR}/lib)
endif()

set(TARGET_CFG_DIR ${TARGET_TRENTINO_DIR}/cfg)
set(TARGET_INCLUDE_DIR ${TARGET_TRENTINO_DIR}/include)
#set(TARGET_EXAMPLES_DIR ${TARGET_TRENTINO_DIR}/examples)
#set(TARGET_DOC_DIR ${TARGET_TRENTINO_DIR}/doc)


#The rules for the installation of ordinary targets are defined in 
#CMakeLists.txt files contained in the corresponding project subdirectories.
#The rules defined below are meant for files that aren't expressed as cmake targets

#install( DIRECTORY ../examples/
#		 DESTINATION ${TARGET_EXAMPLES_DIR})

if(MSVC)	
	set(TRENTINO_CONSOLE_CONF_STANDARD_RUNTIME_PATH ./)		
else()
	set(TRENTINO_CONSOLE_CONF_STANDARD_RUNTIME_PATH ../lib)		
endif()
 
install( FILES LICENSE ..\\NOTICE
		 DESTINATION ${TARGET_TRENTINO_DIR})

configure_file(res/Console.conf.in ${CMAKE_BINARY_DIR}/res/Console.conf)
install( FILES ${CMAKE_BINARY_DIR}/res/Console.conf DESTINATION ${TARGET_CFG_DIR})
install( FILES res/Runtime.conf DESTINATION ${TARGET_CFG_DIR})
install( FILES res/Binding.conf DESTINATION ${TARGET_CFG_DIR})
install( FILES src/Global/TrentinoGlobal.h DESTINATION ${TARGET_INCLUDE_DIR}/Global)

if(TRENTINO_LOGGING)
    install( FILES res/log4cplus.properties DESTINATION ${TARGET_CFG_DIR})        
endif()
		
# if(WIN32)
	# set(dll_pattern "*.dll")
# else()
	# set(dll_pattern "*.so*")
# endif()


if(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR)			
	#--------------------------- BOOST -----------------------------------
	set(TARGET_BOOST_INCLUDE_DIR ${TARGET_INCLUDE_DIR}/boost)			

	if(NOT WIN32)
		file(GLOB Boost_SHARED_LIBS_DEBUG
				"${Boost_SYSTEM_LIBRARY_DLL_DEBUG}.*"
				"${Boost_PROGRAM_OPTIONS_LIBRARY_DLL_DEBUG}.*"
				"${Boost_THREAD_LIBRARY_DLL_DEBUG}.*"
				"${Boost_FILESYSTEM_LIBRARY_DLL_DEBUG}.*"
				"${Boost_DATE_TIME_LIBRARY_DLL_DEBUG}.*" )
		file(GLOB Boost_SHARED_LIBS_RELEASE
				"${Boost_SYSTEM_LIBRARY_DLL_RELEASE}.*"
				"${Boost_PROGRAM_OPTIONS_LIBRARY_DLL_RELEASE}.*"
				"${Boost_THREAD_LIBRARY_DLL_RELEASE}.*"
				"${Boost_FILESYSTEM_LIBRARY_DLL_RELEASE}.*"
				"${Boost_DATE_TIME_LIBRARY_DLL_RELEASE}.*" )
	endif()	

	install(FILES ${Boost_FILESYSTEM_LIBRARY_DLL_DEBUG}
				  ${Boost_SYSTEM_LIBRARY_DLL_DEBUG}
				  ${Boost_PROGRAM_OPTIONS_LIBRARY_DLL_DEBUG}
				  ${Boost_THREAD_LIBRARY_DLL_DEBUG}
				  ${Boost_DATE_TIME_LIBRARY_DLL_DEBUG}
				  ${Boost_SHARED_LIBS_DEBUG}
			DESTINATION ${TARGET_DLL_DIR}
			CONFIGURATIONS Debug )
	install(FILES ${Boost_FILESYSTEM_LIBRARY_DLL_RELEASE}
				  ${Boost_SYSTEM_LIBRARY_DLL_RELEASE}
				  ${Boost_PROGRAM_OPTIONS_LIBRARY_DLL_RELEASE}
				  ${Boost_THREAD_LIBRARY_DLL_RELEASE}
				  ${Boost_DATE_TIME_LIBRARY_DLL_RELEASE}
				  ${Boost_SHARED_LIBS_RELEASE}
			DESTINATION ${TARGET_DLL_DIR}
			CONFIGURATIONS Release RelWithDebInfo MinSizeRel )
	install(FILES ${Boost_INCLUDE_DIRS}/boost/shared_ptr.hpp
	              ${Boost_INCLUDE_DIRS}/boost/scoped_ptr.hpp
				  ${Boost_INCLUDE_DIRS}/boost/intrusive_ptr.hpp
				  ${Boost_INCLUDE_DIRS}/boost/foreach.hpp
				  ${Boost_INCLUDE_DIRS}/boost/config.hpp
				  ${Boost_INCLUDE_DIRS}/boost/foreach_fwd.hpp
				  ${Boost_INCLUDE_DIRS}/boost/noncopyable.hpp
				  ${Boost_INCLUDE_DIRS}/boost/aligned_storage.hpp
				  ${Boost_INCLUDE_DIRS}/boost/assert.hpp
				  ${Boost_INCLUDE_DIRS}/boost/checked_delete.hpp
				  ${Boost_INCLUDE_DIRS}/boost/throw_exception.hpp
				  ${Boost_INCLUDE_DIRS}/boost/memory_order.hpp
				  ${Boost_INCLUDE_DIRS}/boost/current_function.hpp
				  ${Boost_INCLUDE_DIRS}/boost/integer_fwd.hpp
				  ${Boost_INCLUDE_DIRS}/boost/integer_traits.hpp
				  ${Boost_INCLUDE_DIRS}/boost/ref.hpp
				  ${Boost_INCLUDE_DIRS}/boost/function_equal.hpp
				  ${Boost_INCLUDE_DIRS}/boost/mem_fn.hpp
				  ${Boost_INCLUDE_DIRS}/boost/get_pointer.hpp
				  ${Boost_INCLUDE_DIRS}/boost/call_traits.hpp
				  ${Boost_INCLUDE_DIRS}/boost/function.hpp
				  ${Boost_INCLUDE_DIRS}/boost/iterator.hpp
				  ${Boost_INCLUDE_DIRS}/boost/utility.hpp
				  ${Boost_INCLUDE_DIRS}/boost/next_prior.hpp
				  ${Boost_INCLUDE_DIRS}/boost/static_assert.hpp
				  ${Boost_INCLUDE_DIRS}/boost/implicit_cast.hpp
				  ${Boost_INCLUDE_DIRS}/boost/weak_ptr.hpp
				  ${Boost_INCLUDE_DIRS}/boost/enable_shared_from_this.hpp
				  ${Boost_INCLUDE_DIRS}/boost/version.hpp
				  ${Boost_INCLUDE_DIRS}/boost/cstdint.hpp
				  ${Boost_INCLUDE_DIRS}/boost/operators.hpp
				  ${Boost_INCLUDE_DIRS}/boost/limits.hpp
				  ${Boost_INCLUDE_DIRS}/boost/cerrno.hpp
				  ${Boost_INCLUDE_DIRS}/boost/exception_ptr.hpp
				  ${Boost_INCLUDE_DIRS}/boost/cstdint.hpp
				  ${Boost_INCLUDE_DIRS}/boost/program_options.hpp
				  ${Boost_INCLUDE_DIRS}/boost/any.hpp
				  ${Boost_INCLUDE_DIRS}/boost/lexical_cast.hpp
				  ${Boost_INCLUDE_DIRS}/boost/shared_array.hpp
				  ${Boost_INCLUDE_DIRS}/boost/integer.hpp
              ${Boost_INCLUDE_DIRS}/boost/pointer_cast.hpp
              ${Boost_INCLUDE_DIRS}/boost/pointer_to_other.hpp
			DESTINATION ${TARGET_BOOST_INCLUDE_DIR})
	install(DIRECTORY ${Boost_INCLUDE_DIRS}/boost/detail
					  ${Boost_INCLUDE_DIRS}/boost/bind
					  ${Boost_INCLUDE_DIRS}/boost/mpl
					  ${Boost_INCLUDE_DIRS}/boost/range
					  ${Boost_INCLUDE_DIRS}/boost/type_traits
					  ${Boost_INCLUDE_DIRS}/boost/iterator
					  ${Boost_INCLUDE_DIRS}/boost/utility
					  ${Boost_INCLUDE_DIRS}/boost/smart_ptr
					  ${Boost_INCLUDE_DIRS}/boost/config
					  ${Boost_INCLUDE_DIRS}/boost/exception
					  ${Boost_INCLUDE_DIRS}/boost/preprocessor
					  ${Boost_INCLUDE_DIRS}/boost/thread
					  ${Boost_INCLUDE_DIRS}/boost/date_time
					  ${Boost_INCLUDE_DIRS}/boost/system
					  ${Boost_INCLUDE_DIRS}/boost/units
					  ${Boost_INCLUDE_DIRS}/boost/program_options
					  ${Boost_INCLUDE_DIRS}/boost/function
                 ${Boost_INCLUDE_DIRS}/boost/interprocess
                 ${Boost_INCLUDE_DIRS}/boost/intrusive
			DESTINATION ${TARGET_BOOST_INCLUDE_DIR})
	
	#--------------------------- LOG4CPLUS--------------------------------
	if(NOT WIN32)
		file(GLOB Log4cplus_SHARED_LIBS_DEBUG
			"${TRENTINO_LOG4CPLUS_LIB_DIR_DEBUG}/liblog4cplus-*" )
		file(GLOB Log4cplus_SHARED_LIBS_RELEASE
			"${TRENTINO_LOG4CPLUS_LIB_DIR_RELEASE}/liblog4cplus-*" )
	endif()

	install(FILES ${Log4cplus_LIBRARY_DLL_DEBUG}
			      ${Log4cplus_SHARED_LIBS_DEBUG}
			DESTINATION ${TARGET_DLL_DIR}
			CONFIGURATIONS Debug )
	install(FILES ${Log4cplus_LIBRARY_DLL_RELEASE}
			      ${Log4cplus_SHARED_LIBS_RELEASE}
			DESTINATION ${TARGET_DLL_DIR}			
			CONFIGURATIONS Release RelWithDebInfo MinSizeRel )
		
	#--------------------------- ZEROMQ--------------------------------
	if(NOT WIN32)
		file(GLOB ZeroMq_SHARED_LIBS_DEBUG "${ZeroMq_LIBRARY_DEBUG}.*")
		file(GLOB ZeroMq_SHARED_LIBS_RELEASE "${ZeroMq_LIBRARY_RELEASE}.*")		
	endif()	
	
	install(FILES ${ZeroMq_LIBRARY_DLL_DEBUG}
			      ${ZeroMq_SHARED_LIBS_DEBUG}
			DESTINATION ${TARGET_DLL_DIR}
			CONFIGURATIONS Debug )
	install(FILES ${ZeroMq_LIBRARY_DLL_RELEASE}
			      ${ZeroMq_SHARED_LIBS_RELEASE}
			DESTINATION ${TARGET_DLL_DIR}			
			CONFIGURATIONS Release RelWithDebInfo MinSizeRel )
	#--------------------------- OPENSLP--------------------------------
#if(OpenSlpEnable) 
#	if(NOT WIN32)
#		file(GLOB OpenSlp_SHARED_LIBS_DEBUG "${OpenSlp_LIBRARY_DEBUG}.*")
#		file(GLOB OpenSlp_SHARED_LIBS_RELEASE "${OpenSlp_LIBRARY_RELEASE}.*")		
#	endif()	
	
#	install(FILES ${OpenSlp_LIBRARY_DLL_DEBUG}
#			      ${OpenSlp_SHARED_LIBS_DEBUG}
#			DESTINATION ${TARGET_DLL_DIR}
#			CONFIGURATIONS Debug )
#	install(FILES ${OpenSlp_LIBRARY_DLL_RELEASE}
#			      ${OpenSlp_SHARED_LIBS_RELEASE}
#			DESTINATION ${TARGET_DLL_DIR}			
#			CONFIGURATIONS Release RelWithDebInfo MinSizeRel )
#endif()	
endif(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR)


##############################################################################
#                                 CONFIGURE                                 #
##############################################################################
if(TRENTINO_DEV)
	if(MSVC)	
	    set(TRENTINO_CONSOLE_CONF_STANDARD_RUNTIME_PATH ./)
		configure_file(res/Runtime.conf ${EXECUTABLE_OUTPUT_PATH}/cfg/Runtime.conf COPYONLY)
		configure_file(res/Console.conf.in ${EXECUTABLE_OUTPUT_PATH}/cfg/Console.conf)
		configure_file(res/Binding.conf ${EXECUTABLE_OUTPUT_PATH}/cfg/Binding.conf COPYONLY)
		configure_file(res/log4cplus.properties ${EXECUTABLE_OUTPUT_PATH}/cfg/log4cplus.properties COPYONLY)
		configure_file(res/slp.conf ${EXECUTABLE_OUTPUT_PATH}/cfg/slp.conf COPYONLY)

		add_custom_target(  [Copy3rdPartyLibs]  
							COMMAND ${CMAKE_COMMAND} -D target_path=${EXECUTABLE_OUTPUT_PATH}/$(Configuration) 
													 -D type=$(Configuration) 
												     -D third_party_dir=${CMAKE_SOURCE_DIR}/${TRENTINO_THIRD_PARTY_DIR}
													 -P ${CMAKE_SOURCE_DIR}/${TRENTINO_THIRD_PARTY_DIR}/copy_libs.cmake
							VERBATIM)
	else()
		set(TRENTINO_CONSOLE_CONF_STANDARD_RUNTIME_PATH ../lib)
		configure_file(res/Runtime.conf ${EXECUTABLE_OUTPUT_PATH}/../cfg/Runtime.conf COPYONLY)	
		configure_file(res/Console.conf.in ${EXECUTABLE_OUTPUT_PATH}/../cfg/Console.conf)
		configure_file(res/log4cplus.properties ${EXECUTABLE_OUTPUT_PATH}/../cfg/log4cplus.properties COPYONLY)	
		configure_file(res/slp.conf ${EXECUTABLE_OUTPUT_PATH}/../cfg/slp.conf COPYONLY)		
	endif()
endif()


##############################################################################
#                           CPPCHECK STATIC ANALYZER                         #
##############################################################################

option(CPPCHECK_GENERATE "Generate targets for static analysis" ON)
if(CPPCHECK_GENERATE)
include(my_add_cppcheck.cmake)
endif()

##############################################################################
#                           VERA++ STYLE CHECKER                            #
##############################################################################

option(VERA_GENERATE "Generate targets for style check" ON)
if(VERA_GENERATE)
include(my_add_vera.cmake)
endif()


##############################################################################
#                           PROJECT SUBDIRECTORIES                           #
##############################################################################




add_subdirectory(src/Utils)
add_subdirectory(src/Console)
add_subdirectory(src/RuntimeService)
add_subdirectory(src/Runtime)
#add_subdirectory(src/CommonService  [EXCLUDE_FROM_ALL])
add_subdirectory(src/BindingSCA)
add_subdirectory(src/BindingSCAClient)
add_subdirectory(src/BindingCompactSoap)
add_subdirectory(src/BindingIpcClient)
add_subdirectory(src/BindingIpcServer)
add_subdirectory(src/TrengenExecutable)
if(OpenSlpEnable)
if(WIN32)
add_subdirectory(src/DiscoverySLP)
#add_subdirectory(src/OpenSlpDeamon)
add_subdirectory(src/OpenSLP)
endif()
endif()
add_subdirectory(src/Public)

#Does not work!
#set(ALL_PUBLIC_FILES
#	${CMAKE_CURRENT_SOURCE_DIR}/src/Utils/TrentinoUtilsTypeName.h
#	${CMAKE_CURRENT_SOURCE_DIR}/src/Utils/TrentinoUtilsTypeName.inl
#	${CMAKE_CURRENT_SOURCE_DIR}/src/Utils/TrentinoUtilsTypeNameBase.h
#	${CMAKE_CURRENT_SOURCE_DIR}/src/Utils/TrentinoUtilsTypeNameBase.inl
# ...
#	)
#source_group("[Public Files]" FILES ${ALL_PUBLIC_FILES})


if(TRENTINO_TESTING)
	add_subdirectory(src/Tests)	
endif()
add_subdirectory(doc) #source code documentation


##############################################################################
#                           CUSTOM TARGET FOR CI BUILD                       #
##############################################################################
IF(TRENTINO_BUILD_TRENGEN)
IF(WIN32)
SET(CALL_COMMAND call)
endif()
add_custom_target([Trengen_jar] 
COMMAND ${CALL_COMMAND}	mvn -f ../../doc/pom.xml clean install
COMMAND ${CALL_COMMAND} mvn -f ${CMAKE_SOURCE_DIR}/../java/org.trentino.trengen.tools/pom.xml assembly:single
COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../java/org.trentino.trengen.tools/target/Trengen.jar ${CMAKE_SOURCE_DIR}/../java/dist
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/../java/org.trentino.trengen.parent
VERBATIM
)
ENDIF()

##############################################################################
#                           CUSTOM TARGET FOR DOCUMENTATION BUILD            #
##############################################################################
SET(LATEST_DOC_DIR  ${DEFAULT_INSTALL_PATH}/${TARGET_TRENTINO_DIR}/doc CACHE STRING "Install path for doc")

IF(WIN32)
SET(CALL_COMMAND call)
endif()
add_custom_target(maindoc 
COMMAND ${CALL_COMMAND}	mvn site
COMMAND ${CMAKE_COMMAND} -E make_directory ${LATEST_DOC_DIR}
COMMAND ${CMAKE_COMMAND} -E remove_directory "${LATEST_DOC_DIR}/site"
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/../doc/target/site" "${LATEST_DOC_DIR}/site"
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/../doc
VERBATIM
)

#include(${CMAKE_CURRENT_SOURCE_DIR}/src/CommonService/CMakeLists.txt)
##############################################################################
#                           CUSTOM TARGET FOR COMMON SERVICE INSTALL         #
##############################################################################

set(TARGET_COMMONSERVICE_DIR ${TARGET_TRENTINO_DIR}/CommonService/)
set(TARGET_INCLUDE_DIR ${TARGET_TRENTINO_DIR}/include)
#add_custom_target(  [INSTALL_COMMON_SERVICES]  
#                     COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/src/CommonService/PreferenceService" ${TARGET_COMMONSERVICE_DIR} 
#							VERBATIM)

add_custom_target(  [BUILD_COMMON_SERVICES]  
					COMMAND ${CMAKE_COMMAND} -D common_service_dir=${CMAKE_SOURCE_DIR}/src/CommonService -D TRENTINO_INSTALL_DIR=${CMAKE_INSTALL_PREFIX}/${TARGET_TRENTINO_DIR}
               -P ${CMAKE_SOURCE_DIR}/src/CommonService/CmakeLists.txt 
					VERBATIM)

add_custom_target( [INSTALL_COMMON_SERVICES]  
					COMMAND ${CMAKE_COMMAND} -D trentino_home=${CMAKE_INSTALL_PREFIX}/${TARGET_TRENTINO_DIR}
												-D common_service_dir=${CMAKE_SOURCE_DIR}/src/CommonService
												-P ${CMAKE_SOURCE_DIR}/src/CommonService/InstallCommonServices.cmake
					VERBATIM)


