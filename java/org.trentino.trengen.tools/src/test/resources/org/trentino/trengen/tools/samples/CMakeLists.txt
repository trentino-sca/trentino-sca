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

cmake_minimum_required(VERSION 2.8)

get_filename_component(P_DIR ${SRC} PATH)
get_filename_component(FN ${SRC} NAME)
get_filename_component(DEFINCL "../../../../../../../../../cpp/CMakeList.txt" ABSOLUTE)
get_filename_component(DEFINCL "${DEFINCL}" PATH)
set(DEFINCL "${DEFINCL}/3rdparty/x86_windows/vc10")
try_compile( RESULT_VAR ${P_DIR} ${P_DIR}/${FN}
             CMAKE_FLAGS "-DINCLUDE_DIRECTORIES:STRING=${DEFINCL}/protobuf-2.4.1/include;${DEFINCL}/boost_1_47/include;${INCL}"
			 COMPILE_DEFINITIONS "/c /w"
			 OUTPUT_VARIABLE OUTVAR)
			 
 if(${RESULT_VAR} STREQUAL "FALSE")
   message(SEND_ERROR ${OUTVAR})
  endif()