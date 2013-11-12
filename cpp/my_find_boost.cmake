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

macro(MY_FIND_BOOST buildType)
	if(NOT DEFINED Boost_FOUND)
		set(Boost_FOUND TRUE)
	endif()	
	
	string(TOUPPER ${buildType} suffix)	
	if(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR)
		find_file(TRENTINO_BOOST_DIR boost_1_47 PATHS ${TRENTINO_THIRD_PARTY_DIR} NO_DEFAULT_PATH)		
		find_file(TRENTINO_BOOST_LIB_DIR_${suffix} ${buildType} PATHS ${TRENTINO_BOOST_DIR}/lib NO_DEFAULT_PATH)		
		find_file(Boost_INCLUDE_DIRS include PATHS ${TRENTINO_BOOST_DIR} NO_DEFAULT_PATH)		
		
		MY_FIND_BOOST_LIBRARY(Boost_DATE_TIME_LIBRARY_${suffix}   	    boost_date_time  	  ${buildType})							  
		MY_FIND_BOOST_LIBRARY(Boost_FILESYSTEM_LIBRARY_${suffix} 		boost_filesystem 	  ${buildType})
		MY_FIND_BOOST_LIBRARY(Boost_PROGRAM_OPTIONS_LIBRARY_${suffix} 	boost_program_options ${buildType})
		MY_FIND_BOOST_LIBRARY(Boost_REGEX_LIBRARY_${suffix} 			boost_regex	          ${buildType})
		MY_FIND_BOOST_LIBRARY(Boost_SYSTEM_LIBRARY_${suffix} 			boost_system		  ${buildType})
		MY_FIND_BOOST_LIBRARY(Boost_THREAD_LIBRARY_${suffix} 			boost_thread          ${buildType})
		MY_FIND_BOOST_LIBRARY(Boost_SIGNALS_LIBRARY_${suffix}			boost_signals		  ${buildType})
	else()
		set(Boost_DATE_TIME_LIBRARY_${suffix} "" CACHE FILEPATH "boost_filesystem library ${suffix} version")
		set(Boost_FILESYSTEM_LIBRARY_${suffix} "" CACHE FILEPATH "boost_filesystem library ${suffix} version")
		set(Boost_PROGRAM_OPTIONS_LIBRARY_${suffix} "" CACHE FILEPATH "boost_filesystem library ${suffix} version")
		set(Boost_REGEX_LIBRARY_${suffix} "" CACHE FILEPATH "boost_filesystem library ${suffix} version")
		set(Boost_SYSTEM_LIBRARY_${suffix} "" CACHE FILEPATH "boost_filesystem library ${suffix} version")
		set(Boost_THREAD_LIBRARY_${suffix} "" CACHE FILEPATH "boost_filesystem library ${suffix} version")		
		set(Boost_SIGNALS_LIBRARY_${suffix} "" CACHE FILEPATH "boost_signals library ${suffix} version")
		set(Boost_INCLUDE_DIRS "" CACHE PATH  "boost include dir")		
	endif()
		
	MAKE_DLL_NAME(${Boost_DATE_TIME_LIBRARY_${suffix}} Boost_DATE_TIME_LIBRARY_DLL_${suffix})	
	MAKE_DLL_NAME(${Boost_FILESYSTEM_LIBRARY_${suffix}} Boost_FILESYSTEM_LIBRARY_DLL_${suffix})
	MAKE_DLL_NAME(${Boost_PROGRAM_OPTIONS_LIBRARY_${suffix}} Boost_PROGRAM_OPTIONS_LIBRARY_DLL_${suffix})
	MAKE_DLL_NAME(${Boost_REGEX_LIBRARY_${suffix}} Boost_REGEX_LIBRARY_DLL_${suffix})
	MAKE_DLL_NAME(${Boost_SYSTEM_LIBRARY_${suffix}} Boost_SYSTEM_LIBRARY_DLL_${suffix})
	MAKE_DLL_NAME(${Boost_THREAD_LIBRARY_${suffix}} Boost_THREAD_LIBRARY_DLL_${suffix})
	MAKE_DLL_NAME(${Boost_SIGNALS_LIBRARY_${suffix}} Boost_SIGNALS_LIBRARY_DLL_${suffix})	
	
	if( NOT(Boost_DATE_TIME_LIBRARY_${suffix} 	    AND Boost_FILESYSTEM_LIBRARY_${suffix} AND 
			Boost_PROGRAM_OPTIONS_LIBRARY_${suffix} AND Boost_REGEX_LIBRARY_${suffix}      AND
			Boost_SYSTEM_LIBRARY_${suffix}          AND Boost_THREAD_LIBRARY_${suffix}     AND
			Boost_SIGNALS_LIBRARY_${suffix} 		AND Boost_INCLUDE_DIRS) )
		set(Boost_FOUND FALSE)
	endif()		
endmacro(MY_FIND_BOOST)


#---------------------------
# MY_FIND_BOOST_LIBRARY
#---------------------------
#Finds boost libraries in trentino's default 3rdParty directory.
#On Windows boost lib's file names are decorated. For example: 
#boost_date_time-vc90-mt-1_47 (release) or boost_date_time-vc90-mt-gd-1_47 (debug)
#Hence this macro expects and accepts only multithreaded variants for MSVC 2008
#with version 1.47 (=>TODO)
#---------------------------
macro(MY_FIND_BOOST_LIBRARY var baseLibName buildType)		 
	set(realLibName ${baseLibName})
	if(WIN32)		
		if(MSVC10)
			set(msvcVersion "100")
		elseif(MSVC90)
			set(msvcVersion "90")
		endif()
		set(realLibName ${realLibName}-vc${msvcVersion}-mt)
		if(${buildType} STREQUAL "debug")
			set(realLibName ${realLibName}-gd)
		endif()
		set(realLibName ${realLibName}-1_47)
	endif()
		
	if(${buildType} STREQUAL "debug")
		set(path ${TRENTINO_BOOST_LIB_DIR_DEBUG})
	else()
		set(path ${TRENTINO_BOOST_LIB_DIR_RELEASE})
	endif()	
	MY_FIND_LIBRARY(${var} ${realLibName} ${path})	
	#find_library(${var} ${realLibName} PATHS ${boostDir}/lib/${buildType} NO_DEFAULT_PATH)			
endmacro(MY_FIND_BOOST_LIBRARY)