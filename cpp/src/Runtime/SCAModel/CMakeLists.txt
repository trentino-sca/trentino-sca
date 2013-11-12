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
FILE(GLOB SCAModel_HEADER_FILES SCAModel/*.h SCAModel/*.inl)
#source files
FILE(GLOB SCAModel_SOURCE_FILES SCAModel/*.cpp)   

	  
#libs
set( SCAModel_THIRD_PARTY_LIBS 
     )
	 
set( SCAModel_CUSTOM_LIBS 
     )

if(MSVC_IDE)
	set(SCAModel_SOURCE_FILES ${SCAModel_SOURCE_FILES} ${SCAModel_HEADER_FILES})
endif()

if(MSVC_IDE)									
	source_group("SCAModel" FILES ${SCAModel_SOURCE_FILES})		
endif()

include_directories(${Boost_INCLUDE_DIRS})

if(WIN32)
	add_definitions(-DSCAMODEL_EXPORTS)
endif()