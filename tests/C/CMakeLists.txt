# C API binary

set(target "OmexMetaCAPITests")
set(CAPI_TEST_SOURCES ../cpp/CAPITests.cpp)

add_executable(${target} ${CAPI_TEST_SOURCES})

#includes
target_include_directories(${target} PRIVATE
        ${GOOGLETEST_SOURCE}/googletest/include
        ${INCLUDE_DIRECTORIES}
        ${WRAPPER_SOURCE_DIR}
        )

# links
target_link_libraries(${target} PRIVATE
        OmexMetaCAPI
        OmexMeta
        redland-combined
        ${LINK_LIBRARIES}
        ${RUNTIME}# best here so no clash with dynamic
        gtest gtest_main
        )


# install
install(TARGETS ${target}
        EXPORT  ${target}
        RUNTIME DESTINATION bin
        )

