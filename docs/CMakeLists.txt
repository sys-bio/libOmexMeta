##################################################################
# Usage
# -----
# Build the libomexmeta-docs-sphinx.
#
# setup
# ------
# To setup, you first need to tell cmake which sphinx-build you are using.
# do this with -DSPHINX_EXECUTABLE="/path/to/sphinx-build"
# Be careful with conda environments, since its possible that
# the target will find the python interpreter that you do not want to use.
# You will need to:
#   pip install sphinx breathe sphinxcontrib-bibtex sphinx-tabs sphinx_rtd_theme
# you will also need to ensure doxygen is installed and findable.
#
#

############################################################
# Build the documentation examples
#

set(EXAMPLE_EXECUTABLES_TARGETS)

macro(add_doc_example BINARY_NAME)

    # binary for testing Editor's ability to extract information from sbml
    add_executable(${BINARY_NAME} ${ARGN})
    set(EXAMPLE_EXECUTABLES_TARGETS ${EXAMPLE_EXECUTABLES_TARGETS} "${BINARY_NAME}")

    target_compile_definitions(
            ${BINARY_NAME} PRIVATE RR_STATIC
    )
    # add test so it can be run with $ctest or $make test
    add_test(
            NAME ${BINARY_NAME}
            COMMAND $<TARGET_FILE:${BINARY_NAME}>
    )

    set_tests_properties(${BINARY_NAME} PROPERTIES DEPENDS roadrunner-static)
    add_dependencies(${BINARY_NAME} roadrunner-static roadrunner_c_api)

    # links
    target_link_libraries(${BINARY_NAME} PRIVATE
                          $<TARGET_FILE:roadrunner-static> # for C examples
                          $<TARGET_FILE:roadrunner_c_api> # for c++ examples
                          )
endmacro()




if (BUILD_DOCS_EXAMPLES)

    # I've automated this as much as possible. The idea is that
    # we write examples and compile them as self contained programs. Then we capture
    # the output and save those to file as well (in ../ExampleOutputFiles). Then, we can easily include
    # both code and output into sphinx using the `.. literalinclude` directive.
    # The python script called build_doc_examples.py does all of this.
    #
    # Its cmakes job to build these examples. And its Pythons job to
    # run the examples and write output to a known location. Then its
    # sphinx's job to pickup both code and output and include them in
    # the documentation.

    # todo populate with examples here:
    add_doc_example(AddFromFileC                                  source/reading_rdf/add_from_file_c.cpp)

    add_custom_target(AllDocExamples
            DEPENDS ${EXAMPLE_EXECUTABLES_TARGETS}
            )

    add_dependencies(AllDocExamples roadrunner-static roadrunner_c_api)

    # We now create a target that runs the Python script which runs the
    # executables.
    set(DOC_EXAMPLE_RUNNER "${CMAKE_CURRENT_SOURCE_DIR}/build_doc_examples.py")
    if (NOT EXISTS ${DOC_EXAMPLE_RUNNER})
        message(FATAL_ERROR "No Python script found where \"build_doc_examples.pY\" should be")
    endif ()


    # we do not want to use the "CMAKE_BINARY_DIR" variable as invalid in embedded projects
    # so we just take parent of current binary dir
    get_filename_component(PARENT_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} DIRECTORY)
    # later we'll set the build docs target to depend on this
    add_custom_target(RunDocExamplesAndGenerateOutput
            COMMAND ${PYTHON_EXECUTABLE} ${DOC_EXAMPLE_RUNNER} --python-interpretor ${PYTHON_EXECUTABLE} --build-dir ${PARENT_CURRENT_BINARY_DIR} --pyomexmeta-source-dir ${PYOMEXMETA_DIR}
            DEPENDS AllDocExamples
            )
endif ()


############################################################
#   doxygen
#


# https://devblogs.microsoft.com/cppblog/clear-functional-c-documentation-with-sphinx-breathe-doxygen-cmake/
find_package(Doxygen REQUIRED)

set(DOXYGEN_INPUT_DIR1 "${CMAKE_SOURCE_DIR}/src/omexmeta")
set(DOXYGEN_INPUT_DIR2 "${CMAKE_SOURCE_DIR}/src/redland/RedlandWrapper/src")
set(DOXYGEN_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/docs/doxygen-output")
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

set(SPHINX_EXECUTABLE "/home/ciaran/miniconda3/bin/sphinx-build" CACHE FILEPATH
        "absolute path to the sphinx-build executable. If you do not have sphinx-build
you will need to install it. In your conda environment do: $conda activate <env>;
pip install breathe sphinx sphinxcontrib-bibtex sphinx-tabs sphinx_rtd_theme; which sphinx-build. Then copy the value of which sphinx-build into
-DSPHINX_EXECUTABLE")

message(STATUS "SPHINX_EXECUTABLE ${SPHINX_EXECUTABLE}")
set(SPHINX_SOURCE ${CMAKE_SOURCE_DIR}/docs/source)
set(SPHINX_BUILD ${CMAKE_SOURCE_DIR}/docs/docs-build)
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


add_custom_target(libomexmeta-docs-sphinx DEPENDS ${SPHINX_INDEX_FILE})

# when were building the docs examples, we add the dependency so the
# examples get built when we run build the libomexmeta-dpcs-sphinx target
if (BUILD_DOCS_EXAMPLES)
    add_dependencies(libomexmeta-docs-sphinx RunDocExamplesAndGenerateOutput)
endif ()

# Add an install target to install the docs
include(GNUInstallDirs)
install(DIRECTORY ${SPHINX_BUILD}
        DESTINATION ${CMAKE_INSTALL_DOCDIR})



