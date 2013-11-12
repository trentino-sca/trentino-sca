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

#source and header files

FILE(GLOB Invocation_HEADER_FILES Invocation/*.h Invocation/*.inl)	  

FILE(GLOB Invocation_SOURCE_FILES Invocation/*.cpp)	  

set ( Invocation_SOURCE_FILES
	  ${Invocation_HEADER_FILES} ${Invocation_SOURCE_FILES})  
	  
#libs
set( Invocation_THIRD_PARTY_LIBS 
     )
	 
set( Invocation_CUSTOM_LIBS 
     )

include_directories(${Boost_INCLUDE_DIRS} ${SCAAPI_INCLUDE_DIRS})

if(MSVC_IDE)										
	source_group("Invocation" FILES ${Invocation_SOURCE_FILES})
endif()

if(WIN32)
	add_definitions(-DINVOCATION_EXPORTS)
endif()
