#**********************************************************************************
# Trentino - A C++ based lightweight, non-invasive SCA runtime.
# Copyright 2012 by Siemens AG. All rights reserved.
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
#**********************************************************************************

#source and header files
FILE (GLOB LocalCallDataExchange_HEADER_FILES *.h META-INF/*.* *.componentType
	  services/*.h services/*.inl)

FILE (GLOB LocalCallDataExchange_SOURCE_FILES *.cpp)
	  
#libs
set( LocalCallDataExchange_THIRD_PARTY_LIBS 
     )
	 
set( LocalCallDataExchange_CUSTOM_LIBS 
     )
	 
set( LocalCallDataExchange_SOURCE_FILES ${LocalCallDataExchange_SOURCE_FILES}
						  ${LocalCallDataExchange_HEADER_FILES})

if (WIN32)
	add_definitions(-DLOCALDATACALLEXCHANGE_EXPORTS)
endif()

include_directories(${SCAAPI_INCLUDE_DIRS})
set(TrentinoLocalCallDataExchange_INSTALL_DIR ${TARGET_LIB_DIR}/../TestData/TrentinoLocalCallDataExchange)
add_library(LocalCallDataExchange SHARED ${LocalCallDataExchange_SOURCE_FILES})
set_target_properties(LocalCallDataExchange PROPERTIES OUTPUT_NAME TrentinoLocalCallDataExchange)
install(TARGETS LocalCallDataExchange ${DLL_TARGET_KIND} DESTINATION ${TrentinoLocalCallDataExchange_INSTALL_DIR})
install(DIRECTORY META-INF services DESTINATION ${TrentinoLocalCallDataExchange_INSTALL_DIR})
install(FILES TrentinoLocalCallDataExchangeServiceABImpl.h ServiceAImpl.componentType ServiceBImpl.componentType DESTINATION ${TrentinoLocalCallDataExchange_INSTALL_DIR})
set_target_properties(LocalCallDataExchange PROPERTIES FOLDER "Tests/TestData")