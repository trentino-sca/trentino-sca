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

#"constants"
set(TRENTINO_VERSION_STATUS_PREALPHA "pa")
set(TRENTINO_VERSION_STATUS_ALPHA "a")
set(TRENTINO_VERSION_STATUS_BETA "b")
set(TRENTINO_VERSION_STATUS_RC "rc")
set(TRENTINO_VERSION_STATUS_RELEASE "r")

#variables describing the version
set(TRENTINO_VERSION_MAJOR 0)
set(TRENTINO_VERSION_MINOR 8)
set(TRENTINO_VERSION_REVISION 0)
set(TRENTINO_VERSION_STATUS ${TRENTINO_VERSION_STATUS_RELEASE})
set(TRENTINO_VERSION_STATUS_NUMBER 0)

macro(MAKE_VERSION_STRING versionString)
	set(${versionString} "${TRENTINO_VERSION_MAJOR}.${TRENTINO_VERSION_MINOR}")
	if(NOT ${TRENTINO_VERSION_REVISION} EQUAL 0)
		set(${versionString} "${${versionString}}.${TRENTINO_VERSION_REVISION}")
	endif()	
	set(${versionString} "${${versionString}}-${TRENTINO_VERSION_STATUS}" CACHE STRING "Trentino Version")	
	if(NOT ${TRENTINO_VERSION_STATUS_NUMBER} EQUAL 0)
		set(${versionString} "${${versionString}}${TRENTINO_VERSION_STATUS_NUMBER}")
	endif()
endmacro(MAKE_VERSION_STRING)

MAKE_VERSION_STRING(TRENTINO_VERSION_STRING)

macro (MAKE_FULL_VERSION_STRING fullVersionString)	
	string(TOLOWER ${CMAKE_SYSTEM_NAME} system_name)
	set( ${fullVersionString} "${CMAKE_SYSTEM_PROCESSOR}_${system_name}_${TRENTINO_VERSION_STRING}"
	     CACHE STRING "Trentino Full Version")
endmacro(MAKE_FULL_VERSION_STRING)

MAKE_FULL_VERSION_STRING(TRENTINO_FULL_VERSION_STRING)
