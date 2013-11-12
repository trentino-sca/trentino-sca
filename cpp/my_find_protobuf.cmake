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

macro(MY_FIND_PROTOBUF buildType)	
	if(NOT DEFINED Protobuf_FOUND)
		set(Protobuf_FOUND TRUE)
	endif()	
	
	string(TOUPPER ${buildType} suffix)	
	
	if(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR)
		find_file(TRENTINO_PROTOBUF_DIR protobuf-2.4.1 PATHS ${TRENTINO_THIRD_PARTY_DIR} NO_DEFAULT_PATH)
		find_file(TRENTINO_PROTOBUF_LIB_DIR_${suffix} ${buildType} PATHS ${TRENTINO_PROTOBUF_DIR}/lib NO_DEFAULT_PATH)			
		find_file(Protobuf_INCLUDE_DIRS include PATHS ${TRENTINO_PROTOBUF_DIR} NO_DEFAULT_PATH)	
		
		if(WIN32)
			set(libName "libprotobuf-lite")
		else()
			set(libName "protobuf-lite")
		endif()
		
		MY_FIND_LIBRARY(Protobuf_LIBRARY_${suffix} ${libName} ${TRENTINO_PROTOBUF_LIB_DIR_${suffix}})
	else()
		set(Protobuf_LIBRARY_${suffix} "" CACHE FILEPATH "protobuf library ${suffix} version")	
		set(Protobuf_INCLUDE_DIRS "" CACHE PATH "protobuf include dir")
	endif()
		
	if( NOT(Protobuf_LIBRARY_${suffix} AND Protobuf_INCLUDE_DIRS) )		    
		set(Protobuf_FOUND FALSE)
	endif()		
endmacro(MY_FIND_PROTOBUF)