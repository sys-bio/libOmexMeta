# We add some variables before including CPath
set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An annotation library for models in systems biology")
set(CPACK_PACKAGE_VENDOR "Prof. Herbert Sauro's Lab")

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_MICRO})

set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set(CPACK_VERBATIM_VARIABLES TRUE)
set(CPACK_PACKAGE_DESCRIPTION_FILE ../README.md)
set(CPACK_RESOURCE_FILE_WELCOME ../banner.txt)
set(CPACK_RESOURCE_FILE_LICENSE ../LICENCE.txt)
set(CPACK_RESOURCE_FILE_README ../README.md)

set(CPACK_DEBIAN_PACKAGE_NAME ${CPACK_PACKAGE_NAME})

include(CPack)

if (WIN32)
    set(CPACK_GENERATOR ZIP)
elseif (APPLE)
    set(CPACK_GENERATOR TGZ)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CPACK_GENERATOR TGZ RPM)
else ()
    set(CPACK_GENERATOR TGZ)
endif ()


if (WIN32)
    add_custom_target(
            PackageOmexMeta
            COMMENT "Create a zip binary distribution"
            COMMAND ${CMAKE_CPACK_COMMAND} -G ZIP ${CMAKE_BINARY_DIR}/CPackConfig.cmake
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            VERBATIM
    )
else ()
    add_custom_target(
            PackageOmexMeta
            COMMENT "Create a tarball binary distribution"
            COMMAND ${CMAKE_CPACK_COMMAND} -G TGZ "${CMAKE_BINARY_DIR}/CPackConfig.cmake"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            VERBATIM
    )
endif ()



add_custom_target(
        libOmexMetaInstall
        COMMAND "${CMAKE_COMMAND}" --build . --target install
        #    COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_LIST_DIR}/InstallWindowsRedistrib.cmake"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)
set(all_targets
    OmexMeta-static
    OmexMeta
    OmexMetaCAPI
    redland-combined-static
    redland-combined
    OmexMetaTests
    redland-wrapper-tests
    gtest gtest_main
    )

# add all targets as dependencies to ensure packaging is done last in all scenarios
add_dependencies(PackageOmexMeta ${all_targets})
if (BUILD_PYTHON)
    # in order to build the python package you must
    # build the PackageOmexMetaPython target sucessfully
    # on both windows and linux. The first will fail
    # due to not having the binaries it needs inthe python
    # source but then the other will fill in these gaps.
    add_custom_target(
            PackageOmexMetaPython
            COMMENT "create a pip wheel"
            COMMAND ${PYTHON_EXECUTABLE} ${PYTHON_SETUP_FILE} sdist bdist_wheel
            DEPENDS libOmexMetaInstall
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    add_dependencies(PackageOmexMetaPython ${all_targets})
endif ()
