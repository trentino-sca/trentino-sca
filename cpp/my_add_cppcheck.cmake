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
#

# add_cppcheck(target source1 [source2 ...])
#
# Takes a list of source files and generates a build target which can be used
# for linting all files
#
# Parameters:
#  - target: the name of the target to which the sources belong. You will get a
#            new build target named ${target}_cppcheck
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
#    include(/path/to/my_add_cppcheck.cmake)
#
#  and add a line to generate the main_cppcheck target
#
#   if(COMMAND add_cppcheck)
#    add_cppcheck(main ${MAIN_SOURCES})
#   endif(COMMAND add_cppcheck)
#

# This file contains functions and configurations for generating cppcheck build
# targets for your CMake projects.

# --enable=<id>        Enable additional checks. The available ids are:
#                       * all
#                               Enable all checks
#                       * style
#                               Enable all coding style checks. All messages
#                               with the severities 'style', 'performance' and
#                               'portability' are enabled.
#                       * performance
#                               Enable performance messages
#                       * portability
#                               Enable portability messages
#                       * information
#                               Enable information messages
#                       * unusedFunction
#                               Check for unused functions
#                       * missingInclude
#                               Warn if there are missing includes. For
#                               detailed information, use '--check-config'.
#                      Several ids can be given if you separate them with
#                      commas. See also --std

include(my_add_tool.cmake)

if(NOT DEFINED CPPCHECK_EXECUTABLE)
set(CPPCHECK_EXECUTABLE "$ENV{PROGRAMFILES}/Cppcheck/cppcheck.exe" CACHE STRING "full path to the cppcheck executable.")
endif()

option(CPPCHECK_ADDITIONAL_ALL 	"Enable all checks" OFF)
option(CPPCHECK_ADDITIONAL_STYLE 	"Enable all coding style checks." ON)
option(CPPCHECK_ADDITIONAL_PERFORMANCE 	"Enable performance messages" OFF)
option(CPPCHECK_ADDITIONAL_PORTABILITY 	"Enable portability messages" OFF)
option(CPPCHECK_ADDITIONAL_INFORMATION 	"Enable information messages" ON)
option(CPPCHECK_ADDITIONAL_UNUSEDFUNC 	"Check for unused functions" OFF)
option(CPPCHECK_ADDITIONAL_MISSINGINCLUDE 	"Warn if there are missing includes." ON)

if (    CPPCHECK_ADDITIONAL_ALL OR
        CPPCHECK_ADDITIONAL_STYLE OR
        CPPCHECK_ADDITIONAL_PERFORMANCE OR
        CPPCHECK_ADDITIONAL_PORTABILITY OR
        CPPCHECK_ADDITIONAL_INFORMATION OR
        CPPCHECK_ADDITIONAL_UNUSEDFUNC OR
        CPPCHECK_ADDITIONAL_MISSINGINCLUDE)
        
        if(CPPCHECK_ADDITIONAL_ALL)
        list(APPEND enable_options all)
        else()
            if(CPPCHECK_ADDITIONAL_STYLE)
                list(APPEND enable_options " style ")
            else()
                if(CPPCHECK_ADDITIONAL_PERFORMANCE)
                list(APPEND enable_options " performance ")
                endif()
                if(CPPCHECK_ADDITIONAL_PORTABILITY)
                list(APPEND enable_options " portability ")
                endif()
            endif()
            if(CPPCHECK_ADDITIONAL_INFORMATION)
            list(APPEND enable_options " information ")
            endif()
            if(CPPCHECK_ADDITIONAL_UNUSEDFUNC)
            list(APPEND enable_options " unusedFunction ")
            endif()
            if(CPPCHECK_ADDITIONAL_MISSINGINCLUDE)
            list(APPEND enable_options " missingInclude ")
            endif()
        endif()
        string(STRIP "${enable_options}" enable_options_separated)
        STRING(REGEX REPLACE "[ ]+" "," enable_options_separated ${enable_options_separated} )
        #MESSAGE(STATUS ${enable_options} " -> " ${enable_options_separated})
        list(APPEND cppcheck_args "--enable=${enable_options_separated}")
endif()



#set(CPPCHECK_DEFAULT_ARGUMENTS "--template=vs --platform=win32W" CACHE STRING "cppcheck default command line arguments")
#if (NOT DEFINED CPP_CHECK_ARGUMENTS)
#set(CPP_CHECK_ARGUMENTS ${CPPCHECK_DEFAULT_ARGUMENTS} CACHE STRING "cppcheck command line arguments")
#endif()

option(CPPCHECK_INCONCLUSIVE 	"Allow that Cppcheck reports even though the analysis is inconclusive. There are false positives with this option." OFF)
if(CPPCHECK_INCONCLUSIVE)
list(APPEND cppcheck_args --inconclusive)
endif()

option(CPPCHECK_REPORT_PROGRESS 	"Report progress messages while checking a file." OFF)
if(CPPCHECK_REPORT_PROGRESS)
list(APPEND cppcheck_args --report-progress)
endif()


option(CPPCHECK_STD_POSIX 	"POSIX compatible code" OFF)
if(CPPCHECK_STD_POSIX)
list(APPEND cppcheck_args --std=posix)
endif()
option(CPPCHECK_STD_C89 	"C89 compatible code" OFF)
if(CPPCHECK_STD_C89)
list(APPEND cppcheck_args --std=c89)
endif()
option(CPPCHECK_STD_C99 	"C99 compatible code" OFF)
if(CPPCHECK_STD_C99)
list(APPEND cppcheck_args --std=c99)
endif()
option(CPPCHECK_STD_C11 	"C11 compatible code" OFF)
if(CPPCHECK_STD_C11)
list(APPEND cppcheck_args --std=c11)
endif()
option(CPPCHECK_STD_CPP03 	"c++03 compatible code" OFF)
if(CPPCHECK_STD_CPP03)
list(APPEND cppcheck_args --std=c++03)
endif()
option(CPPCHECK_STD_CPP11 	"c++11 compatible code" ON)
if(CPPCHECK_STD_CPP11)
list(APPEND cppcheck_args --std=c++11)
endif()

# -f, --force          Force checking of all configurations in files. If used
#                      together with '--max-configs=', the last option is the
#                      one that is effective.
option(CPPCHECK_FORCE 	"Force checking of all configurations in files." ON)
if(CPPCHECK_FORCE)
list(APPEND cppcheck_args -f)
endif()

option(CPPCHECK_VERBOSE 	"Output more detailed error information." OFF)
if(CPPCHECK_VERBOSE)
list(APPEND cppcheck_args -v)
endif()

# -q, --quiet          Only print error messages.
option(CPPCHECK_QUIET 	"Only print error messages." ON)
if(CPPCHECK_QUIET)
list(APPEND cppcheck_args -q)
endif()

option(CPPCHECK_INLINE_SUPPRESIONS 	"Enable inline warning suppressions." ON)
if(CPPCHECK_INLINE_SUPPRESIONS)
list(APPEND cppcheck_args --inline-suppr)
endif()

option(CPPCHECK_ANALYSE_INCLUDES "Analyse include files"   ON)
option(CPPCHECK_USE_DEFINES "Use pre-deined macros from project settings" OFF)
# Pattern for include directories filtering (meant to avoid analysis of third-party includes, e.g. boost)
set(CPPCHECK_INCLUDE_FILTER ".*3rdparty.*" CACHE STRING "Include directory filter")

#    --error-exitcode=<n> If errors are found, integer [n] is returned instead of
#                         the default '0'. '1' is returned
#                         if arguments are not valid or if no input files are
#                         provided. Note that your operating system can modify
#                         this value, e.g. '256' can become '0'.
set(CPPCHECK_ERROR_EXITCODE "0"  CACHE STRING "Error code to be returned if erros found")
string(COMPARE NOTEQUAL CPPCHECK_ERROR_EXITCODE "0" CPPCHECK_ERROR_EXITCODE_CHANGED)
if(CPPCHECK_ERROR_EXITCODE_CHANGED )
list(APPEND cppcheck_args --error-exitcode=${CPPCHECK_ERROR_EXITCODE})
endif()


if(WIN32)
list(APPEND cppcheck_args --platform=win32W)
else()
list(APPEND cppcheck_args --platform=unix32)
endif()

if(MSVC)
list(APPEND cppcheck_args --template=vs)
else()
list(APPEND cppcheck_args --template=gcc)
endif()

# a phony target which causes all available *_cppcheck targets to be executed
add_custom_target(ALL_CPPCHECK)


function(add_cppcheck target)
    get_directory_property(cppcheck_include_directories INCLUDE_DIRECTORIES)
    get_directory_property(cppcheck_defines COMPILE_DEFINITIONS)

    # let's get those elephants across the alps
    # prepend each include directory with "-I"; also quotes the directory
    set(cppcheck_include_directories_transformed)
    if(CPPCHECK_ANALYSE_INCLUDES)
    foreach(include_dir ${cppcheck_include_directories})
        if( NOT(include_dir MATCHES ${CPPCHECK_INCLUDE_FILTER}))
        #MESSAGE(STATUS "${include_dir} does not match ${CPPCHECK_INCLUDE_FILTER}")
        list(APPEND cppcheck_include_directories_transformed -I"${include_dir}")
        endif()
    endforeach(include_dir)
    endif()
    
    # prepend each definition with "-d"
    set(cppcheck_defines_transformed)
    if(CPPCHECK_USE_DEFINES)
    foreach(definition ${cppcheck_defines})
        list(APPEND cppcheck_defines_transformed -D${definition})
    endforeach(definition)
    endif()
    
     set( all_args  ${cppcheck_args} 
             ${cppcheck_include_directories_transformed} 
             ${cppcheck_defines_transformed} 
             )
    add_tool( ${CPPCHECK_EXECUTABLE} "${all_args}" _cppcheck "Static Analysis" ${target} \\.c$|\\.cxx$|\\.cpp$ ${ARGV})
   

endfunction(add_cppcheck)