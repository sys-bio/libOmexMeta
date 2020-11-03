
set(OMEXMETA_TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/omexmeta")
set(OMEXMETA_TESTS_DIR ${OMEXMETA_TESTS_DIR} PARENT_SCOPE) # for C API to have access to sample annotations
set(REDLAND_WRAPPER_TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/RedlandWrapper")

add_subdirectory(${OMEXMETA_TESTS_DIR})
add_subdirectory(${REDLAND_WRAPPER_TESTS_DIR})