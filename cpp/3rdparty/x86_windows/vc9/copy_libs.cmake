if(NOT DEFINED type)
	set(type release)
endif()

if(NOT DEFINED target_path OR NOT(type STREQUAL "debug" OR type STREQUAL "release"))
	message(FATAL_ERROR "Usage: cmake -D target_path=<directory_path> [-D type=(debug|release)]")
endif()

file(MAKE_DIRECTORY ${target_path})

#BOOST
file(GLOB files ${CMAKE_CURRENT_SOURCE_DIR}/boost_1_44/lib/${type}/*.dll)
foreach(f ${files})	
	execute_process(COMMAND "${CMAKE_COMMAND}" -E copy ${f} ${target_path})
endforeach()

#LOG4CXX
# file(GLOB files ${CMAKE_CURRENT_SOURCE_DIR}/log4cxx-0.10.0/lib/${type}/*.dll)
# foreach(f ${files})	
	# execute_process(COMMAND "${CMAKE_COMMAND}" -E copy ${f} ${target_path})
# endforeach()

#CPPUNIT
file(GLOB files ${CMAKE_CURRENT_SOURCE_DIR}/cppunit-1.12.1/lib/${type}/*.dll)
foreach(f ${files})	
	execute_process(COMMAND "${CMAKE_COMMAND}" -E copy ${f} ${target_path})
endforeach()


