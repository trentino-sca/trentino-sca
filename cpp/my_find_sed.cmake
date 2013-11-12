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

macro(MY_FIND_SED)		
	if(WIN32)
		if(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR)								
			find_program(SED_EXECUTABLE sed PATHS ${CMAKE_SOURCE_DIR}/${TRENTINO_THIRD_PARTY_DIR}/sed-4.2.1 NO_DEFAULT_PATH)		
		else()			
			set(SED_EXECUTABLE "" CACHE FILEPATH "sed executable")			
		endif()
	else()
		find_program(SED_EXECUTABLE sed)
	endif()
endmacro(MY_FIND_SED)