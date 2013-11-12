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

set(PROXIES_WRAPPER_PATH ../SystemTestData/ProxiesAndWrappers)
set(LOCAL_DATA_EXCHANGE_PATH ../SystemTestData/LocalCallDataExchange_Source)
set(BASIC_CALCULATOR_PATH ../SystemTestData/BasicCalculator_Source)
set(SCAAPI_INCLUDE_DIRS ../../../3rdparty/sca_api)

#header files
FILE(GLOB RuntimeTest_HEADER_FILES *.h *.inl ${PROXIES_WRAPPER_PATH}/LocalCallDataExchangeGen_*.h ${PROXIES_WRAPPER_PATH}/BasicCalculatorGen_*.h)	  

#source files 
FILE(GLOB RuntimeTest_SOURCE_FILES *.cpp ${LOCAL_DATA_EXCHANGE_PATH}/*.cpp ${BASIC_CALCULATOR_PATH}/*.cpp ${PROXIES_WRAPPER_PATH}/LocalCallDataExchangeGen_*.cpp ${PROXIES_WRAPPER_PATH}/BasicCalculatorGen_*.cpp)  

set ( RuntimeTest_SOURCE_FILES
	  ${RuntimeTest_HEADER_FILES} ${RuntimeTest_SOURCE_FILES})  
  
#libs
set( RuntimeTest_THIRD_PARTY_LIBS 
     GTest_LIBRARY
	 GMock_LIBRARY
	 Log4cplus_LIBRARY)
	 
set( RuntimeTest_CUSTOM_LIBS 
     Runtime )
	 


if(WIN32)
endif()	 
	
include_directories(${GMock_INCLUDE_DIRS} ${GTest_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS}
					${Log4plus_INCLUDE_DIRS})

include_directories(${LOCAL_DATA_EXCHANGE_PATH} ${LOCAL_DATA_EXCHANGE_PATH}/services)
include_directories(${BASIC_CALCULATOR_PATH} ${BASIC_CALCULATOR_PATH}/services)
include_directories(../../)
include_directories(${SCAAPI_INCLUDE_DIRS})
include_directories(../Mocks)

if (WIN32)
	add_definitions(-DBASICCALCULATOR_EXPORTS)
	add_definitions(-DLOCALDATACALLEXCHANGE_EXPORTS)
endif()

add_executable(RuntimeTest ${RuntimeTest_SOURCE_FILES})
MY_LINK_THIRD_PARTY_LIBRARIES(RuntimeTest ${RuntimeTest_THIRD_PARTY_LIBS})
target_link_libraries(RuntimeTest ${RuntimeTest_CUSTOM_LIBS})
add_dependencies(RuntimeTest BasicCalculatorGen)
# if(TRENTINO_TESTING) 
   # install(TARGETS RuntimeTest ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "RuntimeTest")
# endif()
add_test(NAME RuntimeTest COMMAND RuntimeTest)

set_target_properties(RuntimeTest PROPERTIES FOLDER "Tests")
