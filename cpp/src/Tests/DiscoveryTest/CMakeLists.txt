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
FILE(GLOB DiscoveryTest_HEADER_FILES *.h *.inl)	  
FILE(GLOB DiscoveryTest_SOURCE_FILES *.cpp)	
FILE(GLOB DiscoveryTest_SOURCE_FILES_MOCK_FAKE ./MocksFakes/*Fake.cpp ./MocksFakes/*Mock.cpp)
FILE(GLOB DiscoveryTest_HEADER_FILES_MOCK_FAKE ./MocksFakes/*Fake.h ./MocksFakes/*Mock.h)
FILE(GLOB DiscoveryTest_TESTDATA_FILES ./TestData/*)	

if(MSVC_IDE)
    add_definitions(/wd4273)
endif()

set ( DiscoveryTest_ADDITIONAL_FILES
     ../../Runtime/Discovery/TrentinoDiscoveryFactory.cpp
     ../../Runtime/Discovery/TrentinoDiscoveryFactory2.cpp
     ../../Runtime/Discovery/TrentinoDiscoveryInterface.h
     ../../Runtime/Discovery/TrentinoDiscoveryImpl.cpp
     ../../Runtime/Discovery/TrentinoDiscoveryTask.cpp
     ../../Runtime/Discovery/TrentinoDiscoveryTaskQueue.cpp
     ../../Runtime/Discovery/TrentinoDiscoveryTaskFindSrv.cpp
     ../../Runtime/Discovery/TrentinoDiscoveryTaskStop.cpp
     ../../Runtime/Discovery/TrentinoDiscoveryTaskStart.cpp
     ../../Runtime/Discovery/TrentinoDiscoveryTaskRegister.cpp
     ../../Runtime/Discovery/TrentinoDiscoveryFoundService.cpp
     ../../Runtime/Discovery/TrentinoDiscoveryTaskDeregister.cpp
     ../../Runtime/SCAModel/TrentinoSCAModelMetadata.h
	 ../../Runtime/SCAModel/TrentinoSCAModelMetadata.inl
    ../../Runtime/SCAModel/TrentinoSCAModel.cpp
    ../../Runtime/XML/TrentinoXMLSchemaQName.h
    ../../Runtime/XML/TrentinoXMLSchemaQName.cpp
    ../../Runtime/XML/TrentinoXMLSchema.h
    ../../Runtime/SCAModel/TrentinoSCAModel.cpp
../../Runtime/Discovery/TrentinoDiscoveryUtil.h
../../Runtime/Discovery/TrentinoDiscoveryUtil.cpp) 
#libs

find_package (Threads)

set( DiscoveryTest_THIRD_PARTY_LIBS 
   GTest_LIBRARY
   GMock_LIBRARY
   ${loggingLib}
   Boost_THREAD_LIBRARY
	Boost_DATE_TIME_LIBRARY
)
	 
set( DiscoveryTest_CUSTOM_LIBS
Utils
 )
	 
if(MSVC_IDE)
	set(DiscoveryTest_SOURCE_FILES ${DiscoveryTest_SOURCE_FILES} ${DiscoveryTest_HEADER_FILES} ${DiscoveryTest_SOURCE_FILES_MOCK_FAKE} ${DiscoveryTest_HEADER_FILES_MOCK_FAKE})
	source_group("TestData" FILES ${DiscoveryTest_TESTDATA_FILES})
   source_group("Source Files\\[Additional]" FILES ${DiscoveryTest_ADDITIONAL_FILES}) 
   source_group("Source Files\\[MocksFakes]" FILES ${DiscoveryTest_SOURCE_FILES_MOCK_FAKE} )
   source_group("Header Files\\[MocksFakes]" FILES ${DiscoveryTest_HEADER_FILES_MOCK_FAKE} )
endif()

set(discoverydir ../../Discovery)	 

include_directories(${GTest_INCLUDE_DIRS} 
                  ${GMock_INCLUDE_DIRS} 
                  ${Boost_INCLUDE_DIRS}
                  ${discoverydir}
                  ${OpenSlp_INCLUDE_DIRS})


if(TRENTINO_LOGGING)
	include_directories(${Log4cplus_INCLUDE_DIRS})
endif()



add_executable(DiscoveryTest ${DiscoveryTest_SOURCE_FILES} ${DiscoveryTest_SOURCE_FILES_MOCK_FAKE} ${DiscoveryTest_TESTDATA_FILES} ${DiscoveryTest_ADDITIONAL_FILES})
MY_LINK_THIRD_PARTY_LIBRARIES(DiscoveryTest ${DiscoveryTest_THIRD_PARTY_LIBS})
target_link_libraries(DiscoveryTest ${DiscoveryTest_CUSTOM_LIBS})
target_link_libraries (DiscoveryTest ${CMAKE_THREAD_LIBS_INIT})

# if(TRENTINO_TESTING) 
   # install(TARGETS DiscoveryTest ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "DiscoveryTest")
# endif()
add_test(NAME DiscoveryTest COMMAND DiscoveryTest)

set_target_properties(DiscoveryTest PROPERTIES FOLDER "Tests")
 