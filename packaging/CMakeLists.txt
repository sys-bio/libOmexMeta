# when WITH_SANTIZER=ON we must not package anything
if (WITH_SANITIZER)
    message(FATAL_ERROR "You cannot package libOmexMeta when the WITH_SANITIZER option set to ON")
endif ()
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
set(CPACK_CMAKE_GENERATOR Ninja)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libxml2;libxml2-dev;libxslt1-dev;libpq-dev")

# debian specific variables
set(CPACK_DEBIAN_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_PACKAGE_CONTACT "cwelsh2@uw.edu")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Ciaran Welsh")

include(CPack)


# In order to have the packaging targets depend on
# first installing libomexmeta we need to create a target
# that does the install.
add_custom_target(
        libOmexMetaInstall
        COMMAND "${CMAKE_COMMAND}" --build . --target install
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
    add_dependencies(
            packaging packaging-zip
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


if (${BUILD_PYTHON})
    # in order to build the python package you must
    # build the PackageOmexMetaPython target sucessfully
    # on both windows and linux.
    #
    # We only present this target to used on windows if libOmexMeta.so
    # is found in ${PYOMEXMETA_DIR} or on linux if OmexMeta.dll is found
    # at the same place.
    if (${WIN32})
        message(STATUS "BUILDIN pyokna")
        find_program(
                LINUX_LIBRARIES_FOUND
                NAMES ${PYOMEXMETA_DIR}/libOmexMeta.so.${LIBOMEXMETA_VERSION}
                NO_DEFAULT_PATH
        )

        message(STATUS "LINUX_LIBRARIES_FOUND ${LINUX_LIBRARIES_FOUND}")

        if (LINUX_LIBRARIES_FOUND)
            add_custom_target(
                    PackageOmexMetaPython
                    COMMENT "create a pip wheel"
                    COMMAND ${PYTHON_EXECUTABLE} ${PYTHON_SETUP_FILE} sdist bdist_wheel
#                    DEPENDS libOmexMetaInstall
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            )
#            add_dependencies(packaging PackageOmexMetaPython)
        else (LINUX_LIBRARIES_FOUND)
            message(WARNING "You are packaging libOmexMeta but will not be able \
to build the Python package because you have not yet built and installed the \
linux version. Both linux and windows are required to build a pip Wheel.")
        endif (LINUX_LIBRARIES_FOUND)
    elseif (UNIX)
        find_program(
                WINDOWS_LIBRARIES_FOUND
                NAMES ${PYOMEXMETA_DIR}/OmexMeta.dll
                NO_DEFAULT_PATH
        )

        if (WINDOWS_LIBRARIES_FOUND)
            add_custom_target(
                    PackageOmexMetaPython
                    COMMENT "create a pip wheel"
                    COMMAND ${PYTHON_EXECUTABLE} ${PYTHON_SETUP_FILE} sdist bdist_wheel
#                    DEPENDS libOmexMetaInstall
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            )
#            add_dependencies(packaging PackageOmexMetaPython)
        else ()
            message(WARNING "You are packaging libOmexMeta but will not be able \
to build the Python package because you have not yet built and installed the \
windows version. Both linux and windows are required to build a pip Wheel.")
        endif ()

    endif ()

endif ()
