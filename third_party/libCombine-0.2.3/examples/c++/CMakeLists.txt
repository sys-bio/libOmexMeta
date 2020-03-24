## @file    CMakeLists.txt
## @brief   CMake build script for C++ example programs
## @author  Frank T. Bergmann
##

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(BEFORE ${LIBCOMBINE_ROOT_SOURCE_DIR}/src)
include_directories(${LIBCOMBINE_ROOT_SOURCE_DIR}/include)
include_directories(BEFORE ${LIBCOMBINE_ROOT_BINARY_DIR}/src)


if (EXTRA_INCLUDE_DIRS) 
include_directories(${EXTRA_INCLUDE_DIRS})
endif(EXTRA_INCLUDE_DIRS)

file(GLOB cpp_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(filename 
		${cpp_files}
		)
	get_filename_component(example ${filename} NAME_WE)
	add_executable(example_cpp_${example} ${filename})
	set_target_properties(example_cpp_${example} PROPERTIES  OUTPUT_NAME ${example})
	target_link_libraries(example_cpp_${example} ${LIBCOMBINE_LIBRARY}-static ${ZIPPER_LIBRARY} ${LIBZ_LIBRARY} ${LIBSBML_LIBRARY} ${EXTRA_LIBS})

endforeach()
