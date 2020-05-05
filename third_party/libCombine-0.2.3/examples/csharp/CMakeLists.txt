## @file    CMakeLists.txt
## @brief   CMake build script for example .net programs
## @author  Frank T. Bergmann
##
file(GLOB cs_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cs")

foreach(filename 
		${cs_files}
		)
	get_filename_component(example ${filename} NAME_WE)
	ADD_CUSTOM_COMMAND(	
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${example}.exe
		COMMAND "${CSHARP_COMPILER}"
		ARGS -r:${CMAKE_CURRENT_BINARY_DIR}/../../src/bindings/csharp/libcombinecsP.dll
			-target:exe
			-out:${example}.exe
			${CSHARP_EXTRA_ARGS}
			${filename}
		MAIN_DEPENDENCY ${filename}
		COMMENT "Build C# example: ${example}") 
	
	add_custom_target(example_cs_${example} ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${example}.exe)
	add_dependencies(example_cs_${example} binding_csharp_managed_lib)
endforeach()
