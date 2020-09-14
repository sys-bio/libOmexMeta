find_package(Python3 COMPONENTS Interpreter)
if(Python3_Interpreter_FOUND)
add_test (NAME pyomexmeta-api-tests
  COMMAND Python3::Interpreter -m pytest ${CMAKE_CURRENT_SOURCE_DIR}/api_tests.py
  WORKING_DIRECTORY ${PYOMEXMETA_DIR})
add_test (NAME pyomexmeta-tests
  COMMAND Python3::Interpreter -m pytest ${CMAKE_CURRENT_SOURCE_DIR}/tests.py
  WORKING_DIRECTORY ${PYOMEXMETA_DIR})
endif()

