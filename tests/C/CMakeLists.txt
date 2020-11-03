# C API binary
set(target "OmexMetaCAPITests")

set(CAPI_TEST_SOURCES
        CAPITests.cpp
        ${OMEXMETA_TESTS_DIR}/OmexMetaTestUtils.h
        ${OMEXMETA_TESTS_DIR}/OmexMetaTestUtils.cpp
        )

add_executable(${target} ${CAPI_TEST_SOURCES})

target_link_libraries(
        ${target} PRIVATE
        OmexMetaCAPI
        gtest gtest_main
)
add_dependencies(OmexMetaCAPITests OmexMetaCAPI gtest gtest_main)


#includes
target_include_directories(
        ${target} PRIVATE
        $<BUILD_INTERFACE:${GOOGLETEST_SOURCE}/googletest/include>
        $<BUILD_INTERFACE:${INCLUDE_DIRECTORIES}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR} # for c export>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}
        $<BUILD_INTERFACE:${OMEXMETA_TESTS_DIR}>
        $<INSTALL_INTERFACE:include>
)

gtest_add_tests(TARGET ${target} SOURCES ${CAPI_TEST_SOURCES})


# links


# install
install(
        TARGETS ${target}
        EXPORT ${target}
        RUNTIME DESTINATION bin
)

