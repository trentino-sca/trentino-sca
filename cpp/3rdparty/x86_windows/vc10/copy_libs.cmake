if(NOT DEFINED type)
	set(type_lower release)
endif()

if(NOT DEFINED third_party_dir)
	set(third_party_dir ${CMAKE_CURRENT_SOURCE_DIR})
endif()

string(TOLOWER ${type} type_lower)

if(NOT DEFINED target_path)
	message(FATAL_ERROR "Usage: cmake -D target_path=<directory_path> [-D type=(debug|release)] [-D third_party_dir=<directory_path>]")
endif()

if(NOT type_lower STREQUAL "debug")
	set(type_lower "release")
endif()

file(MAKE_DIRECTORY ${target_path})

#BOOST
file(GLOB files ${third_party_dir}/boost_1_47/lib/${type_lower}/*.dll)
foreach(f ${files})	
	message("copying ${f} to ${target_path}")
	execute_process(COMMAND "${CMAKE_COMMAND}" -E copy ${f} ${target_path})
endforeach()

#LOG4CPLUS
file(GLOB files ${third_party_dir}/log4cplus-1.1.0/lib/${type_lower}/*.dll)
foreach(f ${files})	
	message("copying ${f} to ${target_path}")
	execute_process(COMMAND "${CMAKE_COMMAND}" -E copy ${f} ${target_path})
endforeach()

#CPPUNIT
file(GLOB files ${third_party_dir}/cppunit-1.12.1/lib/${type_lower}/*.dll)
foreach(f ${files})	
	message("copying ${f} to ${target_path}")
	execute_process(COMMAND "${CMAKE_COMMAND}" -E copy ${f} ${target_path})
endforeach()

#ZEROMQ
file(GLOB files ${third_party_dir}/zeromq-3.2.1/lib/${type_lower}/*.dll)
foreach(f ${files})	
	message("copying ${f} to ${target_path}")
	execute_process(COMMAND "${CMAKE_COMMAND}" -E copy ${f} ${target_path})
endforeach()

#OPENSLP
file(GLOB files ${third_party_dir}/openslp/lib/${type_lower}/*.dll)
foreach(f ${files})	
	message("copying ${f} to ${target_path}")
	execute_process(COMMAND "${CMAKE_COMMAND}" -E copy ${f} ${target_path})
endforeach()