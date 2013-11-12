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

#header files
FILE(GLOB RuntimeModel_HEADER_FILES RuntimeModel/*.h RuntimeModel/*inl)

 
#source files
FILE(GLOB RuntimeModel_SOURCE_FILES RuntimeModel/*cpp)


if(MSVC_IDE)
	set(RuntimeModel_SOURCE_FILES ${RuntimeModel_SOURCE_FILES} ${RuntimeModel_HEADER_FILES})	
endif()

#libs
set( RuntimeModel_THIRD_PARTY_LIBS 
     )
	 
set( Utils_CUSTOM_LIBS 
     )

if(MSVC_IDE)									
	source_group("RuntimeModel" FILES ${RuntimeModel_SOURCE_FILES})		
endif()

include_directories(${Boost_INCLUDE_DIRS} ${SCAAPI_INCLUDE_DIRS})

if(WIN32)
	add_definitions(-DRUNTIMEMODEL_EXPORTS)
endif()



