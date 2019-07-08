add_executable(sbml_tests sbml_tests.cpp)
target_link_libraries(sbml_tests ${SEMSIM_LIBRARY} Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(sbml_tests)
