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

macro(MY_FIND_LOG4CPLUS buildType)
	if(NOT DEFINED Log4cplus_FOUND)
		set(Log4cplus_FOUND TRUE)
	endif()
	
	if(${buildType} STREQUAL "debug")
		set(ext "D")
	else()
		set(ext "")
	endif()	
	
	string(TOUPPER ${buildType} suffix)	
	
	if(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR)
		find_file(TRENTINO_LOG4CPLUS_DIR log4cplus-1.1.0 PATHS ${TRENTINO_THIRD_PARTY_DIR} NO_DEFAULT_PATH)
		find_file(TRENTINO_LOG4CPLUS_LIB_DIR_${suffix} ${buildType} PATHS ${TRENTINO_LOG4CPLUS_DIR}/lib NO_DEFAULT_PATH)			
		find_file(Log4cplus_INCLUDE_DIRS include PATHS ${TRENTINO_LOG4CPLUS_DIR} NO_DEFAULT_PATH)	
		
		MY_FIND_LIBRARY(Log4cplus_LIBRARY_${suffix} log4cplusU${ext} ${TRENTINO_LOG4CPLUS_LIB_DIR_${suffix}})
	else()
		set(Log4cplus_LIBRARY_${suffix} "" CACHE FILEPATH "log4cplus library ${suffix} version")		
		set(Log4cplus_INCLUDE_DIRS "" CACHE PATH "log4cplus include dir")			
	endif()
	
	MAKE_DLL_NAME(${Log4cplus_LIBRARY_${suffix}} Log4cplus_LIBRARY_DLL_${suffix})	
	if( NOT(Log4cplus_LIBRARY_${suffix} AND Log4cplus_INCLUDE_DIRS)  )
		set(Log4cplus_FOUND FALSE)
	endif()		
endmacro(MY_FIND_LOG4CPLUS)