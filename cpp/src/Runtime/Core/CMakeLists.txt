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

#header files
FILE(GLOB Core_HEADER_FILES Core/*.h Core/*.inl)	  
FILE(GLOB Core_ContributionLoading_HEADER_FILES Core/*ContributionLoading*.h Core/*ContributionLoading*.inl)

#source files
FILE(GLOB Core_SOURCE_FILES Core/*.cpp)	  
FILE(GLOB Core_ContributionLoading_SOURCE_FILES Core/*ContributionLoading*.cpp)

set ( Core_SOURCE_FILES
	  ${Core_HEADER_FILES} ${Core_SOURCE_FILES})  
set ( Core_ContributionLoading_SOURCE_FILES
	  ${Core_ContributionLoading_SOURCE_FILES} ${Core_ContributionLoading_HEADER_FILES})

#libs
set( Core_THIRD_PARTY_LIBS 
     )
	 
set( Core_CUSTOM_LIBS 
     Utils)

include_directories(${Boost_INCLUDE_DIRS})
if(MSVC_IDE)	
	set(OnlyCoreGroup ${Core_SOURCE_FILES})
	list(REMOVE_ITEM OnlyCoreGroup ${Core_ContributionLoading_SOURCE_FILES})
	source_group("Core" FILES ${OnlyCoreGroup})	
	source_group("Core\\ContribuitonLoading" FILES ${Core_ContributionLoading_SOURCE_FILES})	
endif()

if(WIN32)
	add_definitions(-DCORE_EXPORTS)
endif()


