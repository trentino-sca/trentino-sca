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

set ( ReflectionRuntime_COMMON_FILES
	  ReflectionRuntime/TrentinoReflectionDataRegistry.h	  
	  ReflectionRuntime/TrentinoReflectionDataRegistry.cpp
	  ReflectionRuntime/TrentinoReflectionReflectMethod.h	  
	  ReflectionRuntime/TrentinoReflectionReflectMethod.cpp
	  ReflectionRuntime/TrentinoReflectionReflectObject.h
	  ReflectionRuntime/TrentinoReflectionReflectObject.inl
	  ReflectionRuntime/TrentinoReflectionReflectObject.cpp		  
	  ReflectionRuntime/TrentinoReflectionRegistration.cpp )

set ( ReflectionRuntime_HELPER_FILES
	  ReflectionRuntime/TrentinoReflectionHelpersDefaultValue.h
	  ReflectionRuntime/TrentinoReflectionHelpersDefaultValue.inl
	  ReflectionRuntime/TrentinoReflectionHelpersDefaultValueVariant.h
	  ReflectionRuntime/TrentinoReflectionHelpersDefaultValueVariant.inl
	  ReflectionRuntime/TrentinoReflectionHelpersVariant.h
	  ReflectionRuntime/TrentinoReflectionHelpersVariant.inl
	  ReflectionRuntime/TrentinoReflectionHelpersVariant.cpp 
	  ReflectionRuntime/TrentinoReflectionHelpersListWrapper.h
	  ReflectionRuntime/TrentinoReflectionHelpersListWrapper.inl
	  ReflectionRuntime/TrentinoReflectionHelpersListType.h
	  ReflectionRuntime/TrentinoReflectionHelpersListType.inl)

set( ReflectionRuntime_DLLINTERFACE_FILES
	 ReflectionRuntime/TrentinoReflectionDataMethod.h
	 ReflectionRuntime/TrentinoReflectionDataObject.h	 
	 ReflectionRuntime/TrentinoReflectionIncludes.h
	 ReflectionRuntime/TrentinoReflectionRegistration.h) 

	  
#libs
set( ReflectionRuntime_THIRD_PARTY_LIBS 
     )
	 
set( ReflectionRuntime_CUSTOM_LIBS 
     )
	 
set( ReflectionRuntime_SOURCE_FILES ${ReflectionRuntime_SOURCE_FILES}
								    ${ReflectionRuntime_COMMON_FILES}
									${ReflectionRuntime_HELPER_FILES}
									${ReflectionRuntime_DLLINTERFACE_FILES})
if(MSVC_IDE)									
	source_group("ReflectionRuntime\\[Common]" FILES ${ReflectionRuntime_COMMON_FILES})
	source_group("ReflectionRuntime\\[Helpers]" FILES ${ReflectionRuntime_HELPER_FILES})
	source_group("ReflectionRuntime\\[Dll Interface]" FILES ${ReflectionRuntime_DLLINTERFACE_FILES})	
endif()

include_directories(${Boost_INCLUDE_DIRS})

if(WIN32)
	add_definitions(-DREFLECTIONRUNTIME_EXPORTS)
endif()


 