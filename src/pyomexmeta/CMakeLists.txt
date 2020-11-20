########################################################################
#   We create a build tree python package and an
#   install tree python package for pyomexmeta
#
# build tree site-packages dir
set(BUILD_TREE_SITE_PACKAGES ${CMAKE_BINARY_DIR}/site-packages)

# configure the python __init.py
set(PYTHON_INIT_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py")
set(PYTHON_INIT_FILE "${BUILD_TREE_SITE_PACKAGES}/pyomexmeta/__init__.py")
configure_file(${PYTHON_INIT_CONFIG_FILE} ${PYTHON_INIT_FILE} COPYONLY)

# configure the python pyomexmeta_api.py.in
set(PYTHON_API_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/pyomexmeta_api.py")
set(PYTHON_API_FILE "${BUILD_TREE_SITE_PACKAGES}/pyomexmeta/pyomexmeta_api.py")
configure_file(${PYTHON_API_CONFIG_FILE} ${PYTHON_API_FILE} COPYONLY)
configure_file(VERSION.txt "${BUILD_TREE_SITE_PACKAGES}/pyomexmeta/VERSION.txt")

set(PYOMEXMETA_PY "${CMAKE_CURRENT_SOURCE_DIR}/pyomexmeta.py")
configure_file(${PYOMEXMETA_PY} ${BUILD_TREE_SITE_PACKAGES}/pyomexmeta/pyomexmeta.py COPYONLY)


install(FILES ${PYTHON_SETUP_FILE} DESTINATION .)
install(
        FILES
        ${PYTHON_INIT_FILE}
        ${PYTHON_API_FILE}
        ${PYOMEXMETA_PY}
        "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt"
        "$<TARGET_FILE:OmexMetaCAPI>"
        DESTINATION
        site-packages/pyomexmeta
)
