find_package(PythonInterp)
add_test (NAME pyomexmeta-tests
  COMMAND ${PYTHON_EXECUTABLE} -m pytest ${CMAKE_CURRENT_SOURCE_DIR}
  WORKING_DIRECTORY ${PYOMEXMETA_DIR}
)