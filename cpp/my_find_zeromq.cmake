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

macro(MY_FIND_ZEROMQ buildType)	
	if(NOT DEFINED ZeroMq_FOUND)
		set(ZeroMq_FOUND TRUE)
	endif()	
	
	string(TOUPPER ${buildType} suffix)	
	
	if(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR)
		find_file(TRENTINO_ZEROMQ_DIR zeromq-3.2.1 PATHS ${TRENTINO_THIRD_PARTY_DIR} NO_DEFAULT_PATH)
		find_file(TRENTINO_ZEROMQ_LIB_DIR_${suffix} ${buildType} PATHS ${TRENTINO_ZEROMQ_DIR}/lib NO_DEFAULT_PATH)			
		find_file(ZeroMq_INCLUDE_DIRS include PATHS ${TRENTINO_ZEROMQ_DIR} NO_DEFAULT_PATH)	
		
		if(WIN32)
			set(realLibName "libzmq")
		else()
			set(realLibName "zmq")
		endif()
		
		if(${buildType} STREQUAL "debug" AND WIN32)
			set(realLibName ${realLibName}_d)
		endif()
		MY_FIND_LIBRARY(ZeroMq_LIBRARY_${suffix} ${realLibName} ${TRENTINO_ZEROMQ_LIB_DIR_${suffix}})
	else()
		set(ZeroMq_LIBRARY_${suffix} "" CACHE FILEPATH "zeromq library ${suffix} version")	
		set(ZeroMq_INCLUDE_DIRS "" CACHE PATH "zeromq include dir")
	endif()
	
		MAKE_DLL_NAME(${ZeroMq_LIBRARY_${suffix}} ZeroMq_LIBRARY_DLL_${suffix})	
	if( NOT(ZeroMq_LIBRARY_${suffix} AND ZeroMq_INCLUDE_DIRS) )		    
		set(ZeroMq_FOUND FALSE)
	endif()		
endmacro(MY_FIND_ZEROMQ)