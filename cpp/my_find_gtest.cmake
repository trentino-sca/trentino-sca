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

macro(MY_FIND_GTEST buildType)
	if(NOT DEFINED GTest_FOUND)
		set(GTest_FOUND TRUE)
	endif()	
	
	string(TOUPPER ${buildType} suffix)	
	
	if(TRENTINO_USE_DEFAULT_THIRD_PARTY_DIR)
		find_file(TRENTINO_GTEST_DIR gtest-1.6.0 PATHS ${TRENTINO_THIRD_PARTY_DIR} NO_DEFAULT_PATH)
		find_file(TRENTINO_GTEST_LIB_DIR_${suffix} ${buildType} PATHS ${TRENTINO_GTEST_DIR}/lib NO_DEFAULT_PATH)			
		find_file(GTest_INCLUDE_DIRS include PATHS ${TRENTINO_GTEST_DIR} NO_DEFAULT_PATH)	
			
		MY_FIND_LIBRARY(GTest_LIBRARY_${suffix} gtest ${TRENTINO_GTEST_LIB_DIR_${suffix}})
	else()
		set(GTest_LIBRARY_${suffix} "" CACHE FILEPATH "GTest library ${suffix} version")	
		set(GTest_INCLUDE_DIRS "" CACHE PATH "GTest include dir")			
	endif()
	
	if( NOT(GTest_LIBRARY_${suffix} AND GTest_INCLUDE_DIRS)  )
		set(GTest_FOUND FALSE)
	endif()		
endmacro(MY_FIND_GTEST)
