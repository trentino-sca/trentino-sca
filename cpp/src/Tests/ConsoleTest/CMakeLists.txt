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
FILE(GLOB ConsoleTest_COMMON_FILES *.h *.cpp *.inl)	  

set ( ConsoleTest_ADDITIONAL_FILES
	  ../../Console/TrentinoConsole.cpp
	  ../../Console/TrentinoConsoleParser.cpp
	  ../../Console/TrentinoConsoleCommand.cpp	  .
	  ../../Console/TrentinoConsoleCommandBoot.cpp
	  ../../Console/TrentinoConsoleCommandShutdown.cpp	  
	  ../../Console/TrentinoConsoleCommandSetProperty.cpp
	  ../../Console/TrentinoConsoleCommandRewire.cpp
	  ../../Console/TrentinoConsoleCommandRemove.cpp
	  ../../Console/TrentinoConsoleCommandQuit.cpp	 
	  ../../Console/TrentinoConsoleCommandInstall.cpp
	  ../../Console/TrentinoConsoleCommandUpdateh.cpp
	  ../../Console/TrentinoConsoleCommandInfo.cpp
	  ../../Console/TrentinoConsoleContext.cpp
	  ../../Console/TrentinoConsoleContextAccessingCommand.cpp
	  ../../Console/TrentinoConsoleContextManagingCommand.cpp)

	set ( ConsoleTest_ServiceCtrl_FILES
			  ../../Console/TrentinoConsoleCommandService.cpp
			  ../../Console/TrentinoConsoleCommandService.h
			  ../../RuntimeService/TrentinoRuntimeServiceControl.cpp)
		  
#libs

find_package (Threads)

set( ConsoleTest_THIRD_PARTY_LIBS 
     GTest_LIBRARY
	 GMock_LIBRARY
	 Boost_FILESYSTEM_LIBRARY
	 Boost_SYSTEM_LIBRARY
    Boost_THREAD_LIBRARY)

set( ConsoleTest_CUSTOM_LIBS
	 Utils )

if(MSVC_IDE)
	source_group("Source Files" FILES ${ConsoleTest_COMMON_FILES})
	source_group("Source Files\\[Additional]" FILES ${ConsoleTest_ADDITIONAL_FILES} ${ConsoleTest_ServiceCtrl_FILES})
endif()
	
include_directories(BEFORE ${Boost_INCLUDE_DIRS} ${GMock_INCLUDE_DIRS} ${GTest_INCLUDE_DIRS})

add_executable(ConsoleTest ${ConsoleTest_COMMON_FILES} ${ConsoleTest_ADDITIONAL_FILES} ${ConsoleTest_ServiceCtrl_FILES})
MY_LINK_THIRD_PARTY_LIBRARIES(ConsoleTest ${ConsoleTest_THIRD_PARTY_LIBS})
target_link_libraries(ConsoleTest ${ConsoleTest_CUSTOM_LIBS})
target_link_libraries (ConsoleTest ${CMAKE_THREAD_LIBS_INIT})
# if(TRENTINO_TESTING) 
   # install(TARGETS ConsoleTest ${DLL_TARGET_KIND} DESTINATION ${TARGET_LIB_DIR} COMPONENT "ConsoleTest")
# endif()
add_test(NAME ConsoleTest COMMAND ConsoleTest)

set_target_properties(ConsoleTest PROPERTIES FOLDER "Tests")

 
