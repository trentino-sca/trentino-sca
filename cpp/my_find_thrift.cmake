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

macro(MY_FIND_THRIFT buildType)	
	if(NOT DEFINED Thrift_FOUND)
		set(Thrift_FOUND TRUE)
	endif()	
	
	string(TOUPPER ${buildType} suffix)	
	
	if(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR)
		find_file(TRENTINO_THRIFT_DIR thrift-0.8.0 PATHS ${TRENTINO_THIRD_PARTY_DIR} NO_DEFAULT_PATH)
		find_file(TRENTINO_THRIFT_LIB_DIR_${suffix} ${buildType} PATHS ${TRENTINO_THRIFT_DIR}/lib NO_DEFAULT_PATH)			
		find_file(Thrift_INCLUDE_DIRS include PATHS ${TRENTINO_THRIFT_DIR} NO_DEFAULT_PATH)	
		
		if(WIN32)
			set(libName "libthrift")
		else()
			set(libName "thrift")
		endif()
		
		MY_FIND_LIBRARY(Thrift_LIBRARY_${suffix} ${libName} ${TRENTINO_THRIFT_LIB_DIR_${suffix}})
	else()
		set(Thrift_LIBRARY_${suffix} "" CACHE FILEPATH "thrift library ${suffix} version")	
		set(Thrift_INCLUDE_DIRS "" CACHE PATH "thrift include dir")
	endif()
		
	if( NOT(Thrift_LIBRARY_${suffix} AND Thrift_INCLUDE_DIRS) )		    
		set(Thrift_FOUND FALSE)
	endif()		
endmacro(MY_FIND_THRIFT)