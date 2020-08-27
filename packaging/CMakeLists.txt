
# We need a list of targets to ensure the install target defined below
# gets built last
set(
        all_targets
        OmexMeta-static
        OmexMeta
        OmexMetaCAPI
        redland-combined-static
        redland-combined
        OmexMetaTests
        redland-wrapper-tests
        gtest gtest_main
)

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

# debian specific variables
set(CPACK_DEBIAN_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_PACKAGE_CONTACT "cwelsh2@uw.edi")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Ciaran Welsh")

# ensure the WIX generator doesn't think we want components
set(CPACK_MONOLITHIC_INSTALL TRUE)
set(CPACK_WIX_PRODUCT_GUID "B70BA590-2913-4A45-89BB-B1ADBED699C1")
set(CPACK_WIX_UPGRADE_GUID "B70BA590-2913-4A45-89BB-B1ADBED699C1")

# ensures WIX installer works
set(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION OFF)
include(CPack)


# In order to have the packaging targets depend on
# first installing libomexmeta we need to create a target
# that does the install.
add_custom_target(
        libOmexMetaInstall
        COMMAND "${CMAKE_COMMAND}" --build . --target install
        #    COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_LIST_DIR}/InstallWindowsRedistrib.cmake"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# add all targets as dependencies to ensure packaging is done last in all scenarios
add_dependencies(libOmexMetaInstall ${all_targets})

# mickey mouse target for collecting packaging targets
add_custom_target(packaging)
add_dependencies(packaging libOmexMetaInstall)

if (WIN32)
    add_custom_target(
            packaging-zip
            COMMENT "Create a zip binary distribution"
            COMMAND ${CMAKE_CPACK_COMMAND} -G ZIP ${CMAKE_BINARY_DIR}/CPackConfig.cmake
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            VERBATIM
    )
    add_custom_target(
            packaging-wix
            COMMENT "Create a wix binary distribution, i.e. a msi"
            COMMAND ${CMAKE_CPACK_COMMAND} -G WIX ${CMAKE_BINARY_DIR}/CPackConfig.cmake
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            VERBATIM
    )
    add_dependencies(
            packaging packaging-zip packaging-wix
    )

else ()
    add_custom_target(
            packaging-deb
            COMMENT "Create a debian binary distribution"
            COMMAND ${CMAKE_CPACK_COMMAND} -G DEB "${CMAKE_BINARY_DIR}/CPackConfig.cmake"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            VERBATIM
    )
    add_custom_target(
            packaging-tar
            COMMENT "Create a tarball binary distribution"
            COMMAND ${CMAKE_CPACK_COMMAND} -G TGZ "${CMAKE_BINARY_DIR}/CPackConfig.cmake"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            VERBATIM
    )
    add_dependencies(
            packaging packaging-deb packaging-tar
    )

endif ()



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
    add_dependencies(packaging PackageOmexMetaPython)
endif ()
