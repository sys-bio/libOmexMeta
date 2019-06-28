# Find all the public headers
get_target_property(SEMSIM_PUBLIC_HEADER_DIR semsim INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE SEMSIM_PUBLIC_HEADERS ${SEMSIM_PUBLIC_HEADER_DIR}/*.h)
message(STATUS "SEMSIM_PUBLIC_HEADERS ${SEMSIM_PUBLIC_HEADERS}")

#This will be the main output of our command
set(DOXYGEN_INDEX_FILE ${CMAKE_CURRENT_SOURCE_DIR}/html/index.html)

add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${SEMSIM_PUBLIC_HEADERS}
                   COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   MAIN_DEPENDENCY Doxyfile
                   COMMENT "Generating docs")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
