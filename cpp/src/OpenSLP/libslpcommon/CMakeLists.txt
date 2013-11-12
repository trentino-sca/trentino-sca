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
#l
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
FILE(GLOB libslpcommon_HEADER_FILES *.h *.inl)	  
FILE(GLOB libslpcommon_SOURCE_FILES *.c)	

if(MSVC_IDE)
    add_definitions(/wd4273)
endif()
	 
if(MSVC_IDE)
   set(libslpcommon_SOURCE_FILES ${libslpcommon_SOURCE_FILES} ${libslpcommon_HEADER_FILES} )
   source_group("Source Files" FILES ${libslpcommon_SOURCE_FILES}) 
   source_group("Header Files" FILES ${libslpcommon_HEADER_FILES} )
endif()

if(WIN32)
	remove_definitions(/WX) #avoid treating warnings as errors
	remove_definitions(-DUNICODE -D_UNICODE) #with unicode char sets actual code is not compiling
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_definitions(-DSLP_VERSION="2.0.0") #Define SLP version as a preprocessor definition
    add_definitions(-DENABLE_SLPv1)
endif()

add_library(libslpcommon ${libslpcommon_SOURCE_FILES} )
#MY_LINK_THIRD_PARTY_LIBRARIES(DiscoveryTest ${libslpcommon_THIRD_PARTY_LIBS})
set_target_properties(libslpcommon PROPERTIES FOLDER "OpenSLP")
 