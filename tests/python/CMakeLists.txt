find_package(Python3 COMPONENTS Interpreter)
if (Python3_Interpreter_FOUND)
    get_filename_component(OMEXMETA_SOURCE_DIR ${PYOMEXMETA_DIR} DIRECTORY)
    add_test(NAME pyomexmeta-api-tests
            COMMAND Python3::Interpreter -m pytest ${CMAKE_CURRENT_SOURCE_DIR}/api_tests.py
            WORKING_DIRECTORY ${OMEXMETA_SOURCE_DIR})
    add_test(NAME pyomexmeta-tests
            COMMAND Python3::Interpreter -m pytest ${CMAKE_CURRENT_SOURCE_DIR}/tests.py
            WORKING_DIRECTORY ${OMEXMETA_SOURCE_DIR})
endif ()

