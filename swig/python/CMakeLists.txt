include(UseSWIG)
set(CMAKE_SWIG_FLAGS "")
set_source_files_properties(../semsim.i PROPERTIES CPLUSPLUS ON SWIG_MODULE_NAME semsim)

# Add swig module
swig_add_library(
  semsim_python
  LANGUAGE python
  OUTPUT_DIR python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages
  SOURCES ../semsim.i)
if (WIN32)
  swig_link_libraries(semsim_python semsim Python::Module)
else()
  if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set_target_properties(semsim_python PROPERTIES LINK_FLAGS "-Wl,--no-undefined")
  else()
    set_target_properties(semsim_python PROPERTIES LINK_FLAGS "-undefined dynamic_lookup" INSTALL_RPATH "@loader_path/../../lib;@loader_path/" INSTALL_NAME_DIR "@rpath")
  endif()
endif()

# Files to install with Python
set(PYTHON_INSTALL_FILES
        ${CMAKE_CURRENT_BINARY_DIR}/semgen.py
        ${CMAKE_CURRENT_BINARY_DIR}/_semgen.so)

# Configure setup.py and copy to output directory
set(SETUP_PY_IN ${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in)
set(SETUP_PY_OUT ${CMAKE_CURRENT_BINARY_DIR}/setup.py)
configure_file(${SETUP_PY_IN} ${SETUP_PY_OUT})

# Declare install target for python
#install(TARGETS swig_example
#        COMMAND "${PYTHON_EXECUTABLE} setup.py"
#        COMPONENT swig-python)

# Install target to call setup.py
# add_custom_target(install-python
#         DEPENDS _semgen
#         COMMAND python ${SETUP_PY_OUT} install)

install(TARGETS semsim_python
        DESTINATION python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages
        )
