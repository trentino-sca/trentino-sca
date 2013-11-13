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

FILE(GLOB PROJECT_HEADER_FILES *.h )
FILE(GLOB PROJECT_SOURCE_FILES *.cpp)

if(WIN32)
	add_definitions(-DTHRIFTBINDING_EXPORTS)
endif()

set(PROJECT_PUBLIC_FILES
)

#libs
set(PROJECT_THIRD_PARTY_LIBS
TrentinoRuntime TrentinoUtils)
	 
set(PROJECT_CUSTOM_LIBS 
     libthrift)
	 
set(PROJECT_SOURCE_FILES ${PROJECT_SOURCE_FILES}
							 ${PROJECT_HEADER_FILES})

include_directories( ${MYBoost_INCLUDE_DIRS}
					 ${THRIFT_INCLUDE_DIR}
					 ${TRENTINO_SOURCE_DIR})				 
link_directories (${TRENTINO_RUNTIME_DIR}/lib ${MYBoost_LIB_DIRS})
add_library(ThriftServer SHARED ${PROJECT_SOURCE_FILES})



set_target_properties(ThriftServer PROPERTIES OUTPUT_NAME TrentinoThriftServer)
target_link_libraries(ThriftServer ${PROJECT_CUSTOM_LIBS} ${PROJECT_THIRD_PARTY_LIBS})
set(S_TARGET_DLL_DIR ${TRENTINO_RUNTIME_DIR}/Bindings/Thrift/bin)
set(S_TARGET_LIB_DIR ${TRENTINO_RUNTIME_DIR}/Bindings/Thrift/lib)
set(S_TARGET_INCLUDE_DIR ${TRENTINO_RUNTIME_DIR}/Bindings/Thrift/include)

install( TARGETS ThriftServer
		 RUNTIME DESTINATION ${S_TARGET_DLL_DIR}
		 LIBRARY DESTINATION ${S_TARGET_LIB_DIR}
		 ARCHIVE DESTINATION ${S_TARGET_LIB_DIR})

install(FILES ThriftBindingImpl.componentType TrentinoThriftBinding.h TrentinoThriftBindingThriftBinding.h TrentinoThriftBindingThriftBindingImpl.h DESTINATION 	${S_TARGET_INCLUDE_DIR}/ThriftBinding)	 
foreach(filePath ${PROJECT_PUBLIC_FILES})
	get_filename_component(relativePath ${filePath} PATH)
	install(FILES ${filePath} DESTINATION ${S_TARGET_INCLUDE_DIR}/${relativePath})
endforeach()