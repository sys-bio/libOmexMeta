add_subdirectory(redland)
add_subdirectory(omexmeta)

if (${BUILD_PYTHON})
    add_subdirectory(pyomexmeta)
endif (${BUILD_PYTHON})

# ensure changes to ${INCLUDE_DIR} are propagated to top level cmake script
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} PARENT_SCOPE)