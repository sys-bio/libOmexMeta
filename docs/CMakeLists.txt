
############################################################
#   doxygen
#

# https://devblogs.microsoft.com/cppblog/clear-functional-c-documentation-with-sphinx-breathe-doxygen-cmake/
find_package(Doxygen REQUIRED)

set(DOXYGEN_INPUT_DIR1 "${CMAKE_SOURCE_DIR}/src/semsim")
set(DOXYGEN_INPUT_DIR2 "${CMAKE_SOURCE_DIR}/src/redland/RedlandAPIWrapper/src")
set(DOXYGEN_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/docs/cpp")
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.xml)
set(DOXYFILE_IN ${CMAKE_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

# Doxygen won't create this for us
file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

# Only regenerate Doxygen when the Doxyfile or public headers change
add_custom_command(
        OUTPUT ${DOXYGEN_INDEX_FILE}
        DEPENDS ${SEMSIM_HEADERS}
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
        COMMENT "Generating docs"
        VERBATIM
)

add_custom_target(libomexmeta-docs-doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})

############################################################
#   Sphinx
#

#Look for an executable called sphinx-build
find_program(SPHINX_EXECUTABLE
        NAMES sphinx-build
        PATHS
        /home/ciaran/miniconda3/envs/py37/bin/
        D:/miniconda3/bin
        C:/miniconda3/bin
        /mnt/d/miniconda3/bin
        /mnt/c/miniconda3/bin
        /root/miniconda3/bin
        DOC "Path to sphinx-build executable bin directory"
        )

set(SPHINX_SOURCE ${CMAKE_SOURCE_DIR}/docs/source)
set(SPHINX_BUILD ${CMAKE_SOURCE_DIR}/docs/build)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

# Only regenerate Sphinx when:
# - Doxygen has rerun
# - Our doc files have been updated
# - The Sphinx config has been updated
add_custom_command(
        OUTPUT ${SPHINX_INDEX_FILE}
        COMMAND
        # Tell Breathe where to find the Doxygen output
        ${SPHINX_EXECUTABLE} -b html -Dbreathe_projects.libomexmeta=${DOXYGEN_OUTPUT_DIR}/xml
        ${SPHINX_SOURCE} ${SPHINX_BUILD}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS
        # Other docs files you want to track should go here (or in some variable)
        ${SPHINX_SOURCE}/index.rst
        ${DOXYGEN_INDEX_FILE}
        MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
        COMMENT "Generating documentation with Sphinx")



add_custom_target(libomexmeta-docs-sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})


# Add an install target to install the docs
include(GNUInstallDirs)
install(DIRECTORY ${SPHINX_BUILD}
DESTINATION ${CMAKE_INSTALL_DOCDIR})






