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


# Function creates a build target calling the specified tool
# Arguments:
# tool_executable: reference to the tool executable file
# tool_args: list of the tool arguments
# tool_suffix: suffix to be added to the new build target
# folder_name: name of the older new target shall be added to, leave blanc for none
# target: name of the base target
# source_file_filter: a regex to which the source file name from the base target shall match to be added to the new target, specify .* for all files
# then goes a list of source files
function(add_tool tool_executable tool_args tool_suffix folder_name target source_file_filter source_files)

    set(tool_commands)
    
    foreach(sourcefile ${ARGN})
        # only include c and cpp files
        #MESSAGE(STATUS ${sourcefile})
        if( sourcefile MATCHES ${source_file_filter} )
            # make filename absolute
            get_filename_component(sourcefile_abs ${sourcefile} ABSOLUTE)
            # create command line for checking one source file and add it to the list of commands
            list(APPEND tool_commands
                COMMAND ${tool_executable} 
                ${tool_args} 
                ${sourcefile_abs}
                )
        endif()
    endforeach(sourcefile)

    set(new_target ${target}${tool_suffix})
    # add a custom target consisting of all the commands generated above
    add_custom_target(${new_target} ${tool_commands} VERBATIM)
    # Assign a folder
    set_target_properties(${new_target} PROPERTIES FOLDER  ${folder_name})
    # make the ALL_LINT target depend on each and every *_LINT target
#    add_dependencies(ALL_CPPCHECK ${target}_cppcheck)

endfunction(add_tool)