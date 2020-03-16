add_executable(semsim-tests
        sbml_tests.cpp
        )

target_include_directories(semsim-tests PRIVATE ${GOOGLETEST_SOURCE}/googletest/include)

target_link_libraries(semsim-tests
        ${SEMSIM_STATIC_LIBRARY}
        gtest gtest_main
        )

add_test(sbml_tests sbml_tests)


















