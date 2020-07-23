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


############################################################
# Build the documentation examples
#

if (BUILD_DOCS_EXAMPLES)

    # I've automated this as much as possible. The idea is that
    # I write the examples and compile the programs. Then I capture the
    # output and save those to file as well. Then, we can easily include
    # both code and output into sphinx using the `.. literalinclude` directive.
    # This can be done using pure cmake, and I asked how here:
    #   https://stackoverflow.com/questions/62978989/running-multiple-executables-with-a-single-command-in-cmake-and-collecting-the-r
    # But instead I opted to write a python script that will run the examples.
    #
    # So, its cmakes job to build these examples. And its Pythons job to
    # run the examples and write output to a known location. Then its
    # sphinx's job to pickup both code and output and include them in
    # the documentation.

    add_executable(FromStringC source/reading_rdf/from_string_c.cpp)
    add_executable(FromStringCpp source/reading_rdf/from_string_cpp.cpp)
    add_executable(FromUriC source/reading_rdf/from_uri_c.cpp)
    add_executable(FromUriCpp source/reading_rdf/from_uri_cpp.cpp)
    add_executable(FromFileC source/reading_rdf/from_file_c.cpp)
    add_executable(FromFileCpp source/reading_rdf/from_file_cpp.cpp)
    add_executable(AddFromStringC source/reading_rdf/add_from_string_c.cpp)
    add_executable(AddFromStringCpp source/reading_rdf/add_from_string_cpp.cpp)
    add_executable(AddFromFileC source/reading_rdf/add_from_uri_c.cpp)
    add_executable(AddFromFileCpp source/reading_rdf/add_from_file_cpp.cpp)
    add_executable(AddFromUriC source/reading_rdf/add_from_uri_cpp.cpp)
    add_executable(AddFromUriCpp source/reading_rdf/add_from_uri_cpp.cpp)

    add_executable(CreateSingleAnnotationC source/editing_rdf/create_single_annotation_c.cpp)
    add_executable(CreateSingleAnnotationCpp source/editing_rdf/create_single_annotation_cpp.cpp)
    add_executable(CreateSingleAnnotationNoCommitC source/editing_rdf/create_single_annotation_no_commit_c.cpp)
    add_executable(CreateSingleAnnotationNoCommitCpp source/editing_rdf/create_single_annotation_no_commit_cpp.cpp)
    add_executable(CreateSingleAnnotationPredicateFromUriC source/editing_rdf/create_single_annotation_predicate_from_uri_c.cpp)
    add_executable(CreateSingleAnnotationPredicateFromUriCpp source/editing_rdf/create_single_annotation_predicate_from_uri_cpp.cpp)
    add_executable(CreateSingleAnnotationResourceC source/editing_rdf/create_single_annotation_resource_c.cpp)
    add_executable(CreateSingleAnnotationResourceCpp source/editing_rdf/create_single_annotation_resource_cpp.cpp)
    add_executable(CreateSingleAnnotationWithMetaidsC source/editing_rdf/create_single_annotation_with_metaids_c.cpp)
    add_executable(CreateSingleAnnotationWithMetaidsCpp source/editing_rdf/create_single_annotation_with_metaids_cpp.cpp)

    add_executable(CreatePhysicalEntityC source/editing_rdf/create_physical_entity_c.cpp)
    add_executable(CreatePhysicalEntityCpp source/editing_rdf/create_physical_entity_cpp.cpp)
    add_executable(CreatePhysicalProcessC source/editing_rdf/create_physical_process_c.cpp)
    add_executable(CreatePhysicalProcessCpp source/editing_rdf/create_physical_process_cpp.cpp)
    add_executable(CreatePhysicalForceC source/editing_rdf/create_physical_force_c.cpp)
    add_executable(CreatePhysicalForceCpp source/editing_rdf/create_physical_force_cpp.cpp)

    add_executable(WritingToStringC source/writing_rdf/writing_to_string_c.cpp)
    add_executable(WritingToStringCpp source/writing_rdf/writing_to_string_cpp.cpp)

    add_executable(QueryingRdfGraphC source/querying_rdf/querying_rdf_c.cpp)
    add_executable(QueryingRdfGraphCpp source/querying_rdf/querying_rdf_cpp.cpp)

    set(EXAMPLE_EXECUTABLES_TARGETS
            "FromStringC"
            "FromStringCpp"
            "FromUriC"
            "FromUriCpp"
            "FromFileC"
            "FromFileCpp"
            "AddFromStringC"
            "AddFromStringCpp"
            "AddFromFileC"
            "AddFromFileCpp"
            "AddFromUriC"
            "AddFromUriCpp"

            "WritingToStringC"
            "WritingToStringCpp"

            "CreateSingleAnnotationC"
            "CreateSingleAnnotationCpp"
            "CreateSingleAnnotationNoCommitC"
            "CreateSingleAnnotationNoCommitCpp"
            "CreateSingleAnnotationPredicateFromUriC"
            "CreateSingleAnnotationPredicateFromUriCpp"
            "CreateSingleAnnotationResourceC"
            "CreateSingleAnnotationResourceCpp"
            "CreateSingleAnnotationWithMetaidsC"
            "CreateSingleAnnotationWithMetaidsCpp"

            "CreatePhysicalEntityC"
            "CreatePhysicalEntityCpp"
            "CreatePhysicalProcessC"
            "CreatePhysicalProcessCpp"
            "CreatePhysicalForceC"
            "CreatePhysicalForceCpp"

            "QueryingRdfGraphC"
            "QueryingRdfGraphCpp"
            )

    set_target_properties(${EXAMPLE_EXECUTABLES_TARGETS} PROPERTIES
            INCLUDE_DIRECTORIES "${INCLUDE_DIRECTORIES}"
            LINK_LIBRARIES "$<TARGET_FILE:OmexMeta-static>;$<TARGET_FILE:redland-combined-static>;${LINK_LIBRARIES};pthread"
            LINKER_LANGUAGE "CXX"
            CXX_STANDARD 17
            )

    add_custom_target(AllDocExamples
            DEPENDS ${EXAMPLE_EXECUTABLES_TARGETS}
            )

    add_dependencies(AllDocExamples OmexMeta OmexMeta-static)

    # We now create a target that runs the Python script which runs the
    # executables.
    set(DOC_EXAMPLE_RUNNER "${CMAKE_CURRENT_SOURCE_DIR}/build_doc_examples.py")
    if (NOT EXISTS ${DOC_EXAMPLE_RUNNER})
        message(FATAL_ERROR "No Python script found where \"build_doc_examples.pu\" should be")
    endif ()

    message(STATUS "PYTHON_EXECUTABLE ${PYTHON_EXECUTABLE}")
    # later we'll set the build docs target to depend on this
    add_custom_target(RunDocExamplesAndGenerateOutput
            COMMAND ${PYTHON_EXECUTABLE} ${DOC_EXAMPLE_RUNNER} --python-interpretor ${PYTHON_EXECUTABLE}
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

#Look for an executable called sphinx-docs-build
#find_program(SPHINX_EXECUTABLE
#        NAMES sphinx-build
#        PATHS
#        /home/ciaran/miniconda3/bin
#        /home/ciaran/miniconda3/envs/py37/bin/
#        D:/miniconda3/bin
#        C:/miniconda3/bin
#        /mnt/d/miniconda3/bin
#        /mnt/c/miniconda3/bin
#        /root/miniconda3/bin
#        DOC "Path to sphinx-build executable bin directory"
#        )
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


add_custom_target(libomexmeta-docs-sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})

# when were building the docs examples, we add the dependency so the
# examples get built when we run build the libomexmeta-dpcs-sphinx target
if (BUILD_DOCS_EXAMPLES)
    add_dependencies(libomexmeta-docs-sphinx RunDocExamplesAndGenerateOutput)
endif ()

# Add an install target to install the docs
include(GNUInstallDirs)
install(DIRECTORY ${SPHINX_BUILD}
        DESTINATION ${CMAKE_INSTALL_DOCDIR})



