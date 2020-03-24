add_executable(semsim-tests
        SBMLImporterTests.cpp
        LibSBMLTests.cpp
        ModelStrings.h Raptor2Test.cpp)

message(STATUS "ZLIB_STATIC_LIBRARY ${ZLIB_STATIC_LIBRARY}")
message(STATUS "ZIPPER_STATIC_LIBRARY ${ZIPPER_STATIC_LIBRARY}")

target_link_libraries(semsim-tests PRIVATE
        $<TARGET_FILE:semsim-static>
        gtest gtest_main
        ${LIBSBML_LIBRARY}
        ${LIBSBML_STATIC_LIBRARY}
        ${LIBXML2_STATIC_LIBRARY}
        ${LIBBZ_STATIC_LIBRARY}
        ${ZLIB_STATIC_LIBRARY}
        ${ZIPPER_STATIC_LIBRARY}
        ${LIBCOMBINE_STATIC_LIBRARY}
        ${RAPTOR2_STATIC_LIBRARY}
        ${RASQAL_STATIC_LIBRARY}
        ${REDLAND_STATIC_LIBRARY}
        lzma
        m
        pthread
        c
        )


target_include_directories(semsim-tests PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${GOOGLETEST_SOURCE}/googletest/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${LIBSBML_INCLUDE_DIR}
        ${LIBXML2_INCLUDE_DIR}
        ${LIBBZ_INCLUDE_DIR}
        ${ZLIB_INCLUDE_DIR}
        ${ZIPPER_INCLUDE_DIR}
        ${RAPTOR2_INCLUDE_DIR}
        ${RASQAL_INCLUDE_DIR}
        ${REDLAND_INCLUDE_DIR}
        )


add_dependencies(semsim-tests
        semsim-static
        )

















