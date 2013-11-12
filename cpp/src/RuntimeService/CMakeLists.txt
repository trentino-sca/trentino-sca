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
if(WIN32)
set ( RuntimeService_HEADER_FILES
	  TrentinoRuntimeService.h)
endif()

if(WIN32)
set ( RuntimeService_SOURCE_FILES
	  Main.cpp
	  TrentinoRuntimeService.cpp)
else()
set ( RuntimeService_SOURCE_FILES
	  TrentinoRuntimeDaemon.cpp)
endif()

#libs
set( RuntimeService_THIRD_PARTY_LIBS 
     )
	 
set( RuntimeService_CUSTOM_LIBS 
     )
	 
set( RuntimeService_SOURCE_FILES ${RuntimeService_SOURCE_FILES}
								 ${RuntimeService_HEADER_FILES})

add_executable(RuntimeService ${RuntimeService_SOURCE_FILES})
set_target_properties(RuntimeService PROPERTIES OUTPUT_NAME TrentinoRuntimeService)
#install(TARGETS RuntimeService ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "RuntimeService")

set_target_properties(RuntimeService PROPERTIES FOLDER "Executables")

if(CPPCHECK_GENERATE)
add_cppcheck(RuntimeService ${RuntimeService_SOURCE_FILES})                     
endif()

if(VERA_GENERATE)
add_vera(RuntimeService ${RuntimeService_SOURCE_FILES})                     
endif()