find_package(PythonInterp)
add_test(
        NAME pyomexmeta-tests
        COMMAND ${PYTHON_EXECUTABLE} -m pytest # Or just COMMAND pytest
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
set_tests_properties(
        pyomexmeta-tests
        PROPERTIES ENVIRONMENT "PYTHONPATH=${PYOMEXMETA_DIR}:$ENV{PYTHONPATH}"
)
