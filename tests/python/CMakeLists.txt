find_package(Python COMPONENTS Interpreter)
get_filename_component(OMEXMETA_SOURCE_DIR ${PYOMEXMETA_DIR} DIRECTORY)
add_test(NAME
        pyomexmeta-api-tests
        COMMAND
        Python::Interpreter -m pytest ${CMAKE_BINARY_DIR}/site-packages/pyomexmeta/api_tests.py
        WORKING_DIRECTORY
        ${CMAKE_BINARY_DIR}/lib
        )
add_test(NAME
        pyomexmeta-tests
        COMMAND
        Python::Interpreter -m pytest ${CMAKE_BINARY_DIR}/site-packages/pyomexmeta/tests.py
        WORKING_DIRECTORY
        ${CMAKE_BINARY_DIR}/lib
        )

set(PYOMEXMETA_API_TESTS_PY "${CMAKE_CURRENT_SOURCE_DIR}/api_tests.py")
set(PYOMEXMETA_TESTS_PY "${CMAKE_CURRENT_SOURCE_DIR}/tests.py")

configure_file(${PYOMEXMETA_API_TESTS_PY} ${CMAKE_BINARY_DIR}/site-packages/pyomexmeta/api_tests.py COPYONLY)
configure_file(${PYOMEXMETA_TESTS_PY} ${CMAKE_BINARY_DIR}/site-packages/pyomexmeta/tests.py COPYONLY)


install(FILES
        ${PYOMEXMETA_API_TESTS_PY}
        ${PYOMEXMETA_TESTS_PY}
        DESTINATION
        site-packages/pyomexmeta
        )
