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

macro(MY_FIND_OPENSLP buildType)	
	if(NOT DEFINED OpenSlp_FOUND)
		set(OpenSlp_FOUND TRUE)
	endif()	
	
	string(TOUPPER ${buildType} suffix)	
	
	if(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR)
		find_file(TRENTINO_OPENSLP_DIR openslp PATHS ${TRENTINO_THIRD_PARTY_DIR} NO_DEFAULT_PATH)
		find_file(TRENTINO_OPENSLP_LIB_DIR_${suffix} ${buildType} PATHS ${TRENTINO_OPENSLP_DIR}/lib NO_DEFAULT_PATH)			
		find_file(OpenSlp_INCLUDE_DIRS include PATHS ${TRENTINO_OPENSLP_DIR} NO_DEFAULT_PATH)	
		
		if(WIN32)
			set(realLibNameSlp "slp")
		else()
			set(realLibNameSlp "slp")
		endif()
		
		MY_FIND_LIBRARY(OpenSlp_LIBRARY_${suffix} ${realLibNameSlp} ${TRENTINO_OPENSLP_LIB_DIR_${suffix}})
	else()
		set(OpenSlp_LIBRARY_${suffix} "" CACHE FILEPATH "OpenSlp library ${suffix} version")	
		set(OpenSlp_INCLUDE_DIRS "" CACHE PATH "OpenSlp include dir")
	endif()
	
		MAKE_DLL_NAME(${OpenSlp_LIBRARY_${suffix}} OpenSlp_LIBRARY_DLL_${suffix})	
	if( NOT(OpenSlp_LIBRARY_${suffix} AND OpenSlp_INCLUDE_DIRS) )		    
		set(OpenSlp_FOUND FALSE)
	endif()		
endmacro(MY_FIND_OPENSLP)