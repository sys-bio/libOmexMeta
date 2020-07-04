##########################################################################
#   Set libOmexMeta sources
#
set(OMEXMETA_HEADERS
        "SemsimUtils.h"
        "CurlGet.h"
        "RDF.h"
        "SemsimXmlAssistant.h"

        "Subject.h"
        "Resource.h"
        "Query.h"
        "Predicate.h"
        "Triple.h"
        "Triples.h"
        "MetaID.h"
        "PhysicalProperty.h"
        "Participant.h"

        "PhysicalPhenomenon.h"
        "PhysicalEntity.h"
        "PhysicalProcess.h"
        "PhysicalForce.h"
        "AnnotationType.h"
        "Editor.h"
        "SemsimCApi.h"
        )

set(OMEXMETA_SOURCES
        "SemsimUtils.cpp"
        "RDF.cpp"
        "Query.cpp"
        "CurlGet.cpp"
        "SemsimXmlAssistant.cpp"
        "Subject.cpp"
        "Resource.cpp"
        "Predicate.cpp"
        "Triple.cpp"
        "Triples.cpp"
        "PhysicalProperty.cpp"
        "MetaID.cpp"
        "Participant.cpp"

        "PhysicalEntity.cpp"
        "PhysicalPhenomenon.cpp"
        "Editor.cpp"
        "PhysicalProcess.cpp"
        "PhysicalForce.cpp"
        "SemsimCApi.cpp"
        )


#####################################################################3
#
#

# static library
add_library(OmexMeta-static STATIC ${OMEXMETA_HEADERS} ${OMEXMETA_SOURCES})

# set runtime static for windows (ignored on other systems)
set_target_properties(OmexMeta-static PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")

# add redland-combined as dependency
add_dependencies(OmexMeta-static redland-combined-static)

#includes
target_include_directories(OmexMeta-static PRIVATE
        ${INCLUDE_DIRECTORIES}
        )

# links
target_link_libraries(OmexMeta-static PRIVATE
        $<TARGET_FILE:redland-combined-static>
        ${LINK_LIBRARIES}
        )

# install
install(TARGETS OmexMeta-static
        EXPORT OmexMeta-static
        LIBRARY
        DESTINATION lib
        PUBLIC_HEADER DESTINATION include/omexmeta
        )


if (${BUILD_SHARED_LIBS})

    # FIXME some redundancy here.
    # RPATH: on linux determines where shared libraries look for other shared library dependencies.
    #    set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)
    #    set(CMAKE_INSTALL_RPATH "")
    #    set(CMAKE_INSTALL_RPATH ".")
    #    set(CMAKE_BUILD_RPATH "$ORIGIN:1")
    #    set(CMAKE_INSTALL_RPATH "$ORIGIN:2")


    # shared library
    add_library(OmexMeta SHARED "${OMEXMETA_HEADERS}" "${OMEXMETA_SOURCES}" Preproc.h)

    # configure RPATH
    set_target_properties(OmexMeta PROPERTIES INSTALL_RPATH ${RPATH})#:$ORIGIN:/home/ciaran/vcpkg/installed/x64-linux/lib")
    set_target_properties(OmexMeta PROPERTIES BUILD_RPATH ${RPATH})
    #    set_target_properties(OmexMeta PROPERTIES BUILD_RPATH_USE_ORIGIN TRUE)
    GET_TARGET_PROPERTY(V OmexMeta INSTALL_RPATH)
    MESSAGE(V ${V})

    # set runtime shared for windows (ignored on other systems)
    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set_property(TARGET OmexMeta PROPERTY
                MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    elseif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set_property(TARGET OmexMeta PROPERTY
                MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    endif ()

    # includes
    target_include_directories(OmexMeta PUBLIC
            ${INCLUDE_DIRECTORIES}
            )

    # msvc, linux, macos values
    # On msvc this is the lib file counterpart to the redland-combined dll
    # on linux simply the .a file
    # only for shared lib
    SetCrossPlatform(REDLAND_LINK_LIBRARY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/redland-combined.lib $<TARGET_FILE:redland-combined-static> $<TARGET_FILE:redland-combined-static>)

    # links
    target_link_libraries(OmexMeta PUBLIC
            ${REDLAND_LINK_LIBRARY}
            ${LINK_LIBRARIES}
            )

    # Technically linux version depends on static version and windows depends on the dynamic library
    add_dependencies(OmexMeta redland-combined redland-combined-static)

    # install target
    install(TARGETS OmexMeta
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            PUBLIC_HEADER DESTINATION include/OmexMeta
            )

    # for automatically installing to folder containing python api
    install(TARGETS OmexMeta
            LIBRARY DESTINATION ${PYOMEXMETA_DIR}
            )


    # install the shared library dependencies
    if (PLATFORM STREQUAL "linux")

        # On linux we only need a few dynamic libraries due to static linking the rest.
        install(FILES $<TARGET_FILE:OmexMeta> DESTINATION ${PYOMEXMETA_DIR})

        # I had issues installing a few of the dynamic libraries, namely:
        #       - ${LIBXML2_LIBRARY}
        #       - ${LIBXSLT_LIBRARY}
        #       - ${SQLITE3_LIBRARY}
        #       - ${BERKELY_LIBRARY}
        #       - ${POSTGRESQL_LIBRARY}
        # Checkout the LINK_LIBRARIES variable for details on which were statically
        # and which were dynamically linked. I later realized that in order to use these at run time you need both a smbolic
        # link link libx.so.1 which points to the actual library libx.so.1.0.15. Both
        # need to be copied into the pyomexmeta src directory which will then be incorporated
        # into the python build.
        # This is a viable strategy, and should probably be implemented soon so users do not
        # need to manually install packages from apt. However, for now, we rely on users
        # installing these dependencies manually.

        # The exception is the libstdc++ library. Since ive build
        # using a later version than is easily obtainably
        # using apt-get, I just distribute along with python
#        install(FILES ${LIBSTDCXX6_LIBRARY} DESTINATION ${PYOMEXMETA_DIR})


        # curl was statically linked in the end
        #        install(FILES "${CURL_LIBRARY}" DESTINATION ${PYOMEXMETA_DIR} RENAME libsqlite.so.0)

    elseif (PLATFORM STREQUAL "windows-msvc")
        # Just take all of them on windows, since we've linked dynamically to everything
        install(FILES ${LIBRARIES} DESTINATION bin)

        # Remember to copy dependency dlls to pyomexmeta directory
        install(FILES ${LIBRARIES} DESTINATION ${PYOMEXMETA_DIR})
        install(FILES $<TARGET_FILE:redland-combined> DESTINATION ${PYOMEXMETA_DIR})

    elseif (PLATFORM STREQUAL "macos")
        message(STATUS "macos == sad face =[")
    endif ()


endif ()
















#Install the project...
#/home/travis/cmake-3.15.7-Linux-x86_64/bin/cmake -P cmake_install.cmake
#-- Install configuration: ""
#-- Installing: /home/travis/install/include/redland/raptor2.h
#-- Installing: /home/travis/install/include/redland/rasqal.h
#-- Installing: /home/travis/install/include/redland/librdf.h
#-- Installing: /home/travis/install/lib/libredland-combined-static.a
#-- Installing: /home/travis/install/bin/redland-wrapper-tests
#-- Set runtime path of "/home/travis/install/bin/redland-wrapper-tests" to "$ORIGIN:$ORIGIN/../lib"
#-- Installing: /home/travis/install/lib/libOmexMeta-static.a
#-- Up-to-date: /home/travis/install/include
#-- Installing: /home/travis/install/include/gmock
#-- Installing: /home/travis/install/include/gmock/gmock-more-actions.h
#-- Installing: /home/travis/install/include/gmock/gmock-matchers.h
#-- Installing: /home/travis/install/include/gmock/gmock-cardinalities.h
#-- Installing: /home/travis/install/include/gmock/gmock.h
#-- Installing: /home/travis/install/include/gmock/gmock-generated-actions.h.pump
#-- Installing: /home/travis/install/include/gmock/gmock-nice-strict.h
#-- Installing: /home/travis/install/include/gmock/gmock-function-mocker.h
#-- Installing: /home/travis/install/include/gmock/internal
#-- Installing: /home/travis/install/include/gmock/internal/gmock-pp.h
#-- Installing: /home/travis/install/include/gmock/internal/gmock-port.h
#-- Installing: /home/travis/install/include/gmock/internal/gmock-internal-utils.h
#-- Installing: /home/travis/install/include/gmock/internal/custom
#-- Installing: /home/travis/install/include/gmock/internal/custom/gmock-port.h
#-- Installing: /home/travis/install/include/gmock/internal/custom/gmock-matchers.h
#-- Installing: /home/travis/install/include/gmock/internal/custom/gmock-generated-actions.h.pump
#-- Installing: /home/travis/install/include/gmock/internal/custom/README.md
#-- Installing: /home/travis/install/include/gmock/internal/custom/gmock-generated-actions.h
#-- Installing: /home/travis/install/include/gmock/gmock-generated-actions.h
#-- Installing: /home/travis/install/include/gmock/gmock-actions.h
#-- Installing: /home/travis/install/include/gmock/gmock-spec-builders.h
#-- Installing: /home/travis/install/include/gmock/gmock-more-matchers.h
#-- Installing: /home/travis/install/lib/libgmock.a
#-- Installing: /home/travis/install/lib/libgmock_main.a
#-- Installing: /home/travis/install/lib/pkgconfig/gmock.pc
#-- Installing: /home/travis/install/lib/pkgconfig/gmock_main.pc
#-- Installing: /home/travis/install/lib/cmake/GTest/GTestTargets.cmake
#-- Installing: /home/travis/install/lib/cmake/GTest/GTestTargets-noconfig.cmake
#-- Installing: /home/travis/install/lib/cmake/GTest/GTestConfigVersion.cmake
#-- Installing: /home/travis/install/lib/cmake/GTest/GTestConfig.cmake
#-- Up-to-date: /home/travis/install/include
#-- Installing: /home/travis/install/include/gtest
#-- Installing: /home/travis/install/include/gtest/gtest-test-part.h
#-- Installing: /home/travis/install/include/gtest/gtest.h
#-- Installing: /home/travis/install/include/gtest/gtest-message.h
#-- Installing: /home/travis/install/include/gtest/gtest-param-test.h
#-- Installing: /home/travis/install/include/gtest/gtest_prod.h
#-- Installing: /home/travis/install/include/gtest/gtest-spi.h
#-- Installing: /home/travis/install/include/gtest/gtest-typed-test.h
#-- Installing: /home/travis/install/include/gtest/gtest-printers.h
#-- Installing: /home/travis/install/include/gtest/gtest_pred_impl.h
#-- Installing: /home/travis/install/include/gtest/gtest-matchers.h
#-- Installing: /home/travis/install/include/gtest/internal
#-- Installing: /home/travis/install/include/gtest/internal/gtest-internal.h
#-- Installing: /home/travis/install/include/gtest/internal/gtest-string.h
#-- Installing: /home/travis/install/include/gtest/internal/gtest-type-util.h
#-- Installing: /home/travis/install/include/gtest/internal/gtest-port.h
#-- Installing: /home/travis/install/include/gtest/internal/gtest-death-test-internal.h
#-- Installing: /home/travis/install/include/gtest/internal/gtest-filepath.h
#-- Installing: /home/travis/install/include/gtest/internal/custom
#-- Installing: /home/travis/install/include/gtest/internal/custom/gtest.h
#-- Installing: /home/travis/install/include/gtest/internal/custom/gtest-port.h
#-- Installing: /home/travis/install/include/gtest/internal/custom/gtest-printers.h
#-- Installing: /home/travis/install/include/gtest/internal/custom/README.md
#-- Installing: /home/travis/install/include/gtest/internal/gtest-port-arch.h
#-- Installing: /home/travis/install/include/gtest/internal/gtest-param-util.h
#-- Installing: /home/travis/install/include/gtest/gtest-death-test.h
#-- Installing: /home/travis/install/lib/libgtest.a
#-- Installing: /home/travis/install/lib/libgtest_main.a
#-- Installing: /home/travis/install/lib/pkgconfig/gtest.pc
#-- Installing: /home/travis/install/lib/pkgconfig/gtest_main.pc
#-- Installing: /home/travis/install/bin/OmexMetaTests
#-- Set runtime path of "/home/travis/install/bin/OmexMetaTests" to "$ORIGIN:$ORIGIN/../lib"









