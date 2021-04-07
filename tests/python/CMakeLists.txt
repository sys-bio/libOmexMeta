find_package(Python COMPONENTS Interpreter Development REQUIRED)

message(STATUS "Found Python:
Python_VERSION      ${Python_VERSION}
Python_EXECUTABLE   ${Python_EXECUTABLE}
Python_ROOT_DIR     ${Python_ROOT_DIR}
Python_INCLUDE_DIR  ${Python_INCLUDE_DIR}
Python_LIBRARY      ${Python_LIBRARY}
")

if (NOT Python_ROOT_DIR)
    message(WARNING "-DPython_ROOT_DIR variable is empty. Is is possible that you
are using a version of Python that you are not intending to use. Please set Python_ROOT_DIR
as per the docs: https://cmake.org/cmake/help/git-stage/module/FindPython.html")
endif ()

add_test(NAME
        pyomexmeta-api-tests
        COMMAND
        Python::Interpreter -m pytest ${CMAKE_BINARY_DIR}/site-packages/pyomexmeta/api_tests.py
        WORKING_DIRECTORY
        "${CMAKE_BINARY_DIR}/site-packages/pyomexmeta"
        )
add_test(NAME
        pyomexmeta-tests
        COMMAND
        Python::Interpreter -m pytest ${CMAKE_BINARY_DIR}/site-packages/pyomexmeta/pyomexmeta_tests.py
        WORKING_DIRECTORY
        "${CMAKE_BINARY_DIR}/site-packages/pyomexmeta"
        )

set(PYOMEXMETA_API_TESTS_PY "${CMAKE_CURRENT_SOURCE_DIR}/api_tests.py")
set(PYOMEXMETA_TESTS_PY "${CMAKE_CURRENT_SOURCE_DIR}/pyomexmeta_tests.py")
set(PYOMEXMETA_TEST_STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/test_strings.py")

configure_file(${PYOMEXMETA_API_TESTS_PY} ${CMAKE_BINARY_DIR}/site-packages/pyomexmeta/api_tests.py COPYONLY)
configure_file(${PYOMEXMETA_TESTS_PY} ${CMAKE_BINARY_DIR}/site-packages/pyomexmeta/pyomexmeta_tests.py COPYONLY)
configure_file(${PYOMEXMETA_TEST_STRINGS} ${CMAKE_BINARY_DIR}/site-packages/pyomexmeta/test_strings.py COPYONLY)


install(FILES
        ${PYOMEXMETA_API_TESTS_PY}
        ${PYOMEXMETA_TESTS_PY}
        ${PYOMEXMETA_TEST_STRINGS}
        DESTINATION
        site-packages/pyomexmeta
        )
