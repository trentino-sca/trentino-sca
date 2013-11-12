# ***********************************************************************************
# Trentino - A C++ based lightweight, non-invasive SCA runtime.
# Copyright (C) Siemens AG, 2013
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

# add_kwstyle(target source1 [source2 ...])
#
# Takes a list of source files and generates a build target which can be used
# for checking the cpp style by KWStyle tool (http://public.kitware.com/KWStyle)
#
# Parameters:
#  - target: the name of the target to which the sources belong. You will get a
#            new build target named ${target}_cppcheck
#
#  - config: configuration file name
#  - source1 ... : a list of source files to be linted. Just pass the same list
#            as you passed for add_executable or add_library. Everything except
#            C and CPP files (*.c, *.cpp, *.cxx) will be filtered out.
#
# Example:
#  If you have a CMakeLists.txt which generates an executable like this:
#
#    set(MAIN_SOURCES main.c foo.c bar.c)
#    add_executable(main ${MAIN_SOURCES})
#
#  include this file
#
#    include(/path/to/my_add_kwstyle.cmake)
#
#  and add a line to generate the main_cppcheck target
#
#   if(COMMAND add_kwstyle)
#    add_kwstyle(main config.kws.xml ${MAIN_SOURCES})
#   endif(COMMAND add_kwstyle)
#

include(my_add_tool.cmake)

if(NOT DEFINED VERA_EXECUTABLE)

get_filename_component(TRENTINO_THIRD_PARTY_DIR_ABS ${TRENTINO_THIRD_PARTY_DIR} ABSOLUTE)
set(VERA_EXECUTABLE "${TRENTINO_THIRD_PARTY_DIR_ABS}/Vera++-1.1.1/bin/vera++.exe" CACHE STRING "full path to the KWStyle executable.")
set(VERA_HOME "${TRENTINO_THIRD_PARTY_DIR_ABS}/Vera++-1.1.1" CACHE STRING "full path to the KWStyle executable.")

endif()

list(APPEND vera_args -homefolder ${VERA_HOME})
list(APPEND vera_args -profile trentino)
list(APPEND vera_args -paramfile ${VERA_HOME}/trentino.param)

option(VERA_NOFAIL 	"do not fail even when finding rule violations" ON)
if(VERA_NOFAIL)
list(APPEND vera_args -nofail)
endif()

option(VERA_NODUP 	"do not duplicate messages if a single rule is violated many times in a single line of code" ON)
if(VERA_NODUP)
list(APPEND vera_args -nodup)
endif()

#-showrules         include rule name in each report
option(VERA_SHOWRULES 	"include rule name in each report" ON)
if(VERA_SHOWRULES)
list(APPEND vera_args -showrules)
endif()

function(add_vera target)


    #MESSAGE(STATUS "${target} ${config}")
    #MESSAGE(STATUS "${all_args}")
    add_tool( ${VERA_EXECUTABLE} "${vera_args}" _vera "Style Checks" ${target} \\.c$|\\.cxx$|\\.cpp$ ${ARGV})
    #add_custom_command(TARGET ${target}_kwstyle PRE_BUILD COMMAND set VERA_ROOT="c:\\Program Files\\Vera\\")
   
    
endfunction(add_vera)