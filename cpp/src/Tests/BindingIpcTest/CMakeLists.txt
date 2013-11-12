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
FILE(GLOB BindingIpcTest_HEADER_FILES *.h *.inl)	  
FILE(GLOB BindingIpcTest_SOURCE_FILES *.cpp)	
FILE(GLOB BindingIpcTest_SOURCE_FILES_MOCK_FAKE ./MocksFakes/*Fake.cpp ./MocksFakes/*Mock.cpp)
FILE(GLOB BindingIpcTest_HEADER_FILES_MOCK_FAKE ./MocksFakes/*Fake.h ./MocksFakes/*Mock.h)
FILE(GLOB BindingIpcTest_TESTDATA_FILES ./TestData/*)	

if(MSVC_IDE)
    add_definitions(/wd4273)
endif()

set ( BindingIpcTest_ADDITIONAL_FILES
 #../../BindingIpcServer/TrentinoBindingIpcDataHandler.cpp
 #../../BindingIpcServer/TrentinoBindingIpcDataHandler.h
 #../../BindingIpcServer/TrentinoBindingIpcMemoryChecker.cpp
 #../../BindingIpcServer/TrentinoBindingIpcMemoryChecker.h
 #../../BindingIpcServer/TrentinoBindingIpcInvokerProxy.cpp
 #../../BindingIpcServer/TrentinoBindingIpcServiceInfoReaderFromIpcSoap.cpp
	) 
#libs

find_package (Threads)

set( BindingIpcTest_THIRD_PARTY_LIBS 
   GTest_LIBRARY
   GMock_LIBRARY
   ${loggingLib}
   Boost_THREAD_LIBRARY
	Boost_DATE_TIME_LIBRARY
)
	 
set( BindingIpcTest_CUSTOM_LIBS
Utils
Runtime 
BindingIpcServer
BindingIpcClient
 )
	 
if(MSVC_IDE)
	set(BindingIpcTest_SOURCE_FILES ${BindingIpcTest_SOURCE_FILES} ${BindingIpcTest_HEADER_FILES} ${BindingIpcTest_SOURCE_FILES_MOCK_FAKE} ${BindingIpcTest_HEADER_FILES_MOCK_FAKE})
	source_group("TestData" FILES ${BindingIpcTest_TESTDATA_FILES})
   source_group("Source Files\\[Additional]" FILES ${BindingIpcTest_ADDITIONAL_FILES}) 
   source_group("Source Files\\[MocksFakes]" FILES ${BindingIpcTest_SOURCE_FILES_MOCK_FAKE} )
   source_group("Header Files\\[MocksFakes]" FILES ${BindingIpcTest_HEADER_FILES_MOCK_FAKE} )
endif()

set(runtimedir ../../) 
set(TrentinoInstallationDir $ENV{TRENTINO_HOME})
include_directories(${GTest_INCLUDE_DIRS} 
                  ${GMock_INCLUDE_DIRS} 
                  ${Boost_INCLUDE_DIRS}
                  ${runtimedir}
                  ${TrentinoInstallationDir}/include
                  )


if(TRENTINO_LOGGING)
	include_directories(${Log4cplus_INCLUDE_DIRS})
endif()



add_executable(BindingIpcTest ${BindingIpcTest_SOURCE_FILES} ${BindingIpcTest_SOURCE_FILES_MOCK_FAKE} ${BindingIpcTest_TESTDATA_FILES} ${BindingIpcTest_ADDITIONAL_FILES})
MY_LINK_THIRD_PARTY_LIBRARIES(BindingIpcTest ${BindingIpcTest_THIRD_PARTY_LIBS})
target_link_libraries(BindingIpcTest ${BindingIpcTest_CUSTOM_LIBS})
target_link_libraries (BindingIpcTest ${CMAKE_THREAD_LIBS_INIT})

# if(TRENTINO_TESTING) 
   # install(TARGETS BindingIpcTest ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "BindingIpcTest")
# endif()
add_test(NAME BindingIpcTest COMMAND BindingIpcTest)

set_target_properties(BindingIpcTest PROPERTIES FOLDER "Tests")
 