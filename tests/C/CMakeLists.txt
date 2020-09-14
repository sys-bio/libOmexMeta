# C API binary

set(target "OmexMetaCAPITests")
set(CAPI_TEST_SOURCES CAPITests.cpp)

add_executable(${target} ${CAPI_TEST_SOURCES})

#includes
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_BINARY_DIR} DIRECTORY)
target_include_directories(
        ${target} PRIVATE
        ${GOOGLETEST_SOURCE}/googletest/include
        ${INCLUDE_DIRECTORIES}
        ${WRAPPER_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR} # for c export
)

target_compile_definitions(
        ${target} PRIVATE
        OMEXMETA_STATIC_DEFINE
        REDLAND_STATIC_DEFINE
)

gtest_discover_tests(${target})


# links
target_link_libraries(
        ${target} PRIVATE
        OmexMetaCAPI
        OmexMeta-static
        ${RUNTIME}# best here so no clash with dynamic
        gtest gtest_main
)


# install
install(
        TARGETS ${target}
        EXPORT ${target}
        RUNTIME DESTINATION bin
)

