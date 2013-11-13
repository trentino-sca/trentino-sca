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
if(WIN32)
add_definitions(/DHAVE_CONFIG_H=1)
add_definitions(/DWIN32)
add_definitions(/D_LIB)
add_definitions(/DZc:forScope)
add_definitions(/DZc:wchar_t)
add_definitions(/D_MBCS)
endif()
SET(THRIFT_SOURCE_DIR ${TRENTINO_THIRD_PARTY_SRC_DIR}/thrift-0.9.1/lib/cpp/src/thrift)
FILE(GLOB TP_HEADER_FILES ${THRIFT_SOURCE_DIR}/*.h 
${THRIFT_SOURCE_DIR}/async/*.h 
${THRIFT_SOURCE_DIR}/concurrency/*.h 
${THRIFT_SOURCE_DIR}/processor/*.h 
${THRIFT_SOURCE_DIR}/protocol/*.h 
${THRIFT_SOURCE_DIR}/server/*.h 
${THRIFT_SOURCE_DIR}/transport/*.h
)

SET(TP_SOURCE_FILES ${THRIFT_SOURCE_DIR}/TApplicationException.cpp
${THRIFT_SOURCE_DIR}/Thrift.cpp
${THRIFT_SOURCE_DIR}/async/TAsyncChannel.cpp
${THRIFT_SOURCE_DIR}/concurrency/BoostMonitor.cpp
${THRIFT_SOURCE_DIR}/concurrency/BoostMutex.cpp
${THRIFT_SOURCE_DIR}/concurrency/BoostThreadFactory.cpp
${THRIFT_SOURCE_DIR}/concurrency/ThreadManager.cpp
${THRIFT_SOURCE_DIR}/concurrency/TimerManager.cpp
${THRIFT_SOURCE_DIR}/concurrency/Util.cpp
${THRIFT_SOURCE_DIR}/processor/PeekProcessor.cpp
${THRIFT_SOURCE_DIR}/protocol/TBase64Utils.cpp
${THRIFT_SOURCE_DIR}/protocol/TDebugProtocol.cpp
${THRIFT_SOURCE_DIR}/protocol/TBinaryProtocol.tcc
${THRIFT_SOURCE_DIR}/protocol/TDenseProtocol.cpp
${THRIFT_SOURCE_DIR}/protocol/TJSONProtocol.cpp
${THRIFT_SOURCE_DIR}/protocol/TMultiplexedProtocol.cpp
${THRIFT_SOURCE_DIR}/server/TSimpleServer.cpp
${THRIFT_SOURCE_DIR}/server/TThreadPoolServer.cpp
${THRIFT_SOURCE_DIR}/transport/TBufferTransports.cpp
${THRIFT_SOURCE_DIR}/transport/TFDTransport.cpp
${THRIFT_SOURCE_DIR}/transport/TFileTransport.cpp
${THRIFT_SOURCE_DIR}/transport/THttpClient.cpp
${THRIFT_SOURCE_DIR}/transport/THttpServer.cpp
${THRIFT_SOURCE_DIR}/transport/THttpTransport.cpp
${THRIFT_SOURCE_DIR}/transport/TPipe.cpp
${THRIFT_SOURCE_DIR}/transport/TPipeServer.cpp
${THRIFT_SOURCE_DIR}/transport/TServerSocket.cpp
${THRIFT_SOURCE_DIR}/transport/TSimpleFileTransport.cpp
${THRIFT_SOURCE_DIR}/transport/TSocket.cpp
#${THRIFT_SOURCE_DIR}/transport/TSSLSocket.cpp
${THRIFT_SOURCE_DIR}/transport/TTransportException.cpp
${THRIFT_SOURCE_DIR}/transport/TTransportUtils.cpp
)


FILE(GLOB TP_PUBLIC_FILES ${THRIFT_SOURCE_DIR}/*.h)

if(WIN32)
FILE(GLOB F_W32 ${THRIFT_SOURCE_DIR}/windows/*.h ${THRIFT_SOURCE_DIR}/windows/*.cpp)
set(TP_SOURCE_FILES ${TP_SOURCE_FILES} 
${THRIFT_SOURCE_DIR}/windows/config.h
${THRIFT_SOURCE_DIR}/windows/GetTimeOfDay.cpp
${THRIFT_SOURCE_DIR}/windows/GetTimeOfDay.h
${THRIFT_SOURCE_DIR}/windows/Operators.h
${THRIFT_SOURCE_DIR}/windows/SocketPair.cpp
${THRIFT_SOURCE_DIR}/windows/SocketPair.h
${THRIFT_SOURCE_DIR}/windows/TWinsockSingleton.cpp
${THRIFT_SOURCE_DIR}/windows/TWinsockSingleton.h
${THRIFT_SOURCE_DIR}/windows/WinFcntl.cpp
${THRIFT_SOURCE_DIR}/windows/WinFcntl.h 
)
endif()

#libs
set(TP_THIRD_PARTY_LIBS 
)
	 
set(TP_CUSTOM_LIBS 
     )
	 
set(TP_SOURCE_FILES ${TP_SOURCE_FILES}
							 ${TP_HEADER_FILES})


include_directories( ${MYBoost_INCLUDE_DIRS}
					 ${THRIFT_INCLUDE_DIR})				 
link_directories (${MYBoost_LIB_DIRS})
add_library(libthrift STATIC ${TP_SOURCE_FILES})
message(STATUS "Boost lib dir" ${MYBoost_LIB_DIRS})

set_target_properties(libthrift PROPERTIES OUTPUT_NAME libthrift)
target_link_libraries(libthrift ${TP_CUSTOM_LIBS} ${TP_THIRD_PARTY_LIBS})

set(T_TARGET_DLL_DIR ${TRENTINO_RUNTIME_DIR}/Bindings/Thrift/bin)
set(T_TARGET_LIB_DIR ${TRENTINO_RUNTIME_DIR}/Bindings/Thrift/lib)
set(T_TARGET_INCLUDE_DIR ${TRENTINO_RUNTIME_DIR}/Bindings/Thrift/include/thrift)
install( TARGETS libthrift
		 RUNTIME DESTINATION ${T_TARGET_DLL_DIR}
		 LIBRARY DESTINATION ${T_TARGET_LIB_DIR}
		 ARCHIVE DESTINATION ${T_TARGET_LIB_DIR})

foreach(filePath ${TP_PUBLIC_FILES})
	get_filename_component(relativePath ${filePath} NAME)
	install(FILES ${filePath} DESTINATION ${T_TARGET_INCLUDE_DIR})
endforeach()
  
if(WIN32)
	add_definitions(-DTHRIFT_EXPORTS)
endif()