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

#expetcs TRENTINO_PROTOBUF_DIR to be defined if TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR is set to TRUE
#expectx TRENTINO_PROTOBUF_LIB_DIR_RELEASE/DEBUG to be defined if NOT WIN32 and TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR is set to TRUE
macro(MY_FIND_PROTOBUF_PROTOC)		
	if(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR)
		find_file(TRENTINO_PROTOBUF_BIN_DIR bin PATHS ${TRENTINO_PROTOBUF_DIR} NO_DEFAULT_PATH)
		find_program(Protobuf_EXECUTABLE_PROTOC protoc PATHS ${TRENTINO_PROTOBUF_BIN_DIR} NO_DEFAULT_PATH)		
		
		if(NOT WIN32)	
			if(IS_BUILD_TYPE_DEBUG)
				set(suffix "DEBUG")
			else()
				set(suffix "RELEASE")
			endif()
			MY_FIND_LIBRARY(Protobuf_LIBRARY_PROTOC protoc ${TRENTINO_PROTOBUF_LIB_DIR_${suffix}})
		endif()		
	else()
		set(Protobuf_EXECUTABLE_PROTOC "" CACHE FILEPATH "protobuf tool protoc")			
		set(Protobuf_LIBRARY_PROTOC "" CACHE FILEPATH "protobuf protoc library needed for the protoc executable")
	endif()
endmacro(MY_FIND_PROTOBUF_PROTOC)
