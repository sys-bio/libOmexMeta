add_subdirectory(redland)
add_subdirectory(omexmeta)

# ensure changes to ${INCLUDE_DIR} are propagated to top level cmake script
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} PARENT_SCOPE)