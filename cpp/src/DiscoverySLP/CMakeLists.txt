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
FILE(GLOB DiscoverySlp_HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.inl)	  
FILE(GLOB DiscoverySlp_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)	

if(NOT TRENTINO_LOGGING)
	list(REMOVE_ITEM DiscoverySlp_HEADER_FILES TrentinoUtilsLoggingLog4CPlus.h)
	list(REMOVE_ITEM DiscoverySlp_SOURCE_FILES TrentinoUtilsLoggingLog4CPlus.cpp)
endif()

set (DiscoverySLP_ADDITIONAL_FILES
     ../Runtime/Discovery/TrentinoDiscoveryTask.cpp
     ../Runtime/Discovery/TrentinoDiscoveryFoundService.cpp
	 ../Runtime/Discovery/TrentinoDiscoveryTaskFindSrv.cpp
    ../Runtime/Discovery/TrentinoDiscoveryTaskRegister.cpp
    ../Runtime/SCAModel/TrentinoSCAModelMetadata.h
	../Runtime/SCAModel/TrentinoSCAModelMetadata.inl
    ../Runtime/SCAModel/TrentinoSCAModelMetadataStringAttribute.h
    ../Runtime/SCAModel/TrentinoSCAModelMetadataStringAttribute.inl
     ) 

#libs
set( DiscoverySlp_THIRD_PARTY_LIBS 
    ${loggingLib}
    Boost_THREAD_LIBRARY
	 )


set(DiscoverySlp_PUBLIC_FILES

	)

	 
set( DiscoverySlp_CUSTOM_LIBS 
    slpd
	libslp
    Utils
    Runtime
    )

if(MSVC_IDE)
	set(DiscoverySlp_SOURCE_FILES 
	${DiscoverySlp_SOURCE_FILES} 
	${DiscoverySlp_HEADER_FILES}
	)

   source_group("Source Files\\[Additional]" FILES ${DiscoverySLP_ADDITIONAL_FILES}) 
endif()

include_directories(${Log4cplus_INCULDE_DIRS} )
   if(TRENTINO_LOGGING)
	   include_directories(${Log4cplus_INCLUDE_DIRS}
						${Boost_INCLUDE_DIRS})
   else()
	   include_directories(${Boost_INCLUDE_DIRS})
   endif()

if(WIN32)
	add_definitions(-DDISCOVERYSLP_EXPORTS)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif()


add_library(DiscoverySlp  SHARED ${DiscoverySlp_SOURCE_FILES} ${DiscoverySLP_ADDITIONAL_FILES})
set_target_properties(DiscoverySlp PROPERTIES OUTPUT_NAME DiscoverySlp) 

if(CMAKE_COMPILER_IS_GNUCXX)
   set_target_properties(DiscoverySlp PROPERTIES LINK_FLAGS "-ldl")
   SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl" CACHE STRING "Flag to Load Libdl" FORCE)
   target_link_libraries(DiscoverySlp "-ldl")
endif()

MY_LINK_THIRD_PARTY_LIBRARIES(DiscoverySlp ${DiscoverySlp_THIRD_PARTY_LIBS})
target_link_libraries(DiscoverySlp ${DiscoverySlp_CUSTOM_LIBS})

install( TARGETS DiscoverySlp 
		 RUNTIME DESTINATION ${TARGET_DLL_DIR}
		 LIBRARY DESTINATION ${TARGET_LIB_DIR}
		 ARCHIVE DESTINATION ${TARGET_LIB_DIR} )

install( FILES ${DiscoverySlp_PUBLIC_FILES} DESTINATION ${TARGET_INCLUDE_DIR}/DiscoverySlp)

if(CPPCHECK_GENERATE)
   add_cppcheck(DiscoverySlp ${DiscoverySlp_SOURCE_FILES})                     
endif()

if(VERA_GENERATE)
   add_vera(DiscoverySLP ${DiscoverySlp_SOURCE_FILES})                     
endif()

 