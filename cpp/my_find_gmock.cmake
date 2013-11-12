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

macro(MY_FIND_GMOCK buildType)
	if(NOT DEFINED GMock_FOUND)
		set(GMock_FOUND TRUE)
	endif()	
	
	string(TOUPPER ${buildType} suffix)	
	
	if(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR)
		find_file(TRENTINO_GMOCK_DIR gmock-1.6.0 PATHS ${TRENTINO_THIRD_PARTY_DIR} NO_DEFAULT_PATH)
		find_file(TRENTINO_GMOCK_LIB_DIR_${suffix} ${buildType} PATHS ${TRENTINO_GMOCK_DIR}/lib NO_DEFAULT_PATH)			
		find_file(GMock_INCLUDE_DIRS include PATHS ${TRENTINO_GMOCK_DIR} NO_DEFAULT_PATH)	
			
		MY_FIND_LIBRARY(GMock_LIBRARY_${suffix} gmock ${TRENTINO_GMOCK_LIB_DIR_${suffix}})
	else()
		set(GMock_LIBRARY_${suffix} "" CACHE FILEPATH "GMock library ${suffix} version")	
		set(GMock_INCLUDE_DIRS "" CACHE PATH "GMock include dir")			
	endif()
	
	if( NOT(GMock_LIBRARY_${suffix} AND GMock_INCLUDE_DIRS)  )
		set(GMock_FOUND FALSE)
	endif()		
endmacro(MY_FIND_GMOCK)
