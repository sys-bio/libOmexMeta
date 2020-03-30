add_executable(semsim-tests
#        SBMLImporterTests.cpp
#        LibSBMLTests.cpp
        ModelStrings.h
        RedlandLibrariesTests.cpp
        CreateSBMLModelTests.cpp SBMLTestModel.h)

message(STATUS "ZLIB_STATIC_LIBRARY ${ZLIB_STATIC_LIBRARY}")
message(STATUS "ZIPPER_STATIC_LIBRARY ${ZIPPER_STATIC_LIBRARY}")

target_link_libraries(semsim-tests PRIVATE
        $<TARGET_FILE:semsim-static>
        gtest gtest_main
        ${LIBSBML_STATIC_LIBRARY}
        ${LIBXML2_STATIC_LIBRARY}
        ${LIBBZ_STATIC_LIBRARY}
        ${ZLIB_STATIC_LIBRARY}
        ${ZIPPER_STATIC_LIBRARY}
        ${REDLAND_STATIC_LIBRARY}
        ${RASQAL_STATIC_LIBRARY}
        ${RAPTOR2_STATIC_LIBRARY}
        pcre
        pthread
        ltdl
        xml2
        curl
        xslt
        lzma
        m
        c
        )
message(STATUS "
LIBSBML_STATIC_LIBRARY      ${LIBSBML_STATIC_LIBRARY}
LIBXML2_STATIC_LIBRARY      ${LIBXML2_STATIC_LIBRARY}
LIBBZ_STATIC_LIBRARY        ${LIBBZ_STATIC_LIBRARY}
ZLIB_STATIC_LIBRARY         ${ZLIB_STATIC_LIBRARY}
ZIPPER_STATIC_LIBRARY       ${ZIPPER_STATIC_LIBRARY}
RAPTOR2_STATIC_LIBRARY      ${RAPTOR2_STATIC_LIBRARY}
RASQAL_STATIC_LIBRARY       ${RASQAL_STATIC_LIBRARY}
REDLAND_STATIC_LIBRARY      ${REDLAND_STATIC_LIBRARY}
")

get_target_property(X semsim-tests LINK_LIBRARIES )
MESSAGE(STATUS "X ${/usr/local/lib/librasqal.a}

-- X
/usr/local/lib/libxml2.a;
/mnt/d/libsemsim/third_party/libsbml-5.18.0/INSTALL/lib/libsbml-static.a;
/mnt/d/libsemsim/third_party/zipper/INSTALL/lib/libZipper-static.a;
/mnt/d/libsemsim/third_party/libCombine-0.2.3/INSTALL/lib/libcombine-static.a;
dl;
bz2;
z;
curl;
xslt

")



message(STATUS "REDLAND_INCLUDE_DIR ${REDLAND_INCLUDE_DIR}")
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

message(STATUS "
CMAKE_SOURCE_DIR          ${CMAKE_SOURCE_DIR}
GOOGLETEST_SOURCE         ${GOOGLETEST_SOURCE}
CMAKE_CURRENT_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}
LIBSBML_INCLUDE_DIR       ${LIBSBML_INCLUDE_DIR}
LIBXML2_INCLUDE_DIR       ${LIBXML2_INCLUDE_DIR}
LIBBZ_INCLUDE_DIR         ${LIBBZ_INCLUDE_DIR}
ZLIB_INCLUDE_DIR          ${ZLIB_INCLUDE_DIR}
ZIPPER_INCLUDE_DIR        ${ZIPPER_INCLUDE_DIR}
RAPTOR2_INCLUDE_DIR       ${RAPTOR2_INCLUDE_DIR}
RASQAL_INCLUDE_DIR        ${RASQAL_INCLUDE_DIR}
REDLAND_INCLUDE_DIR       ${REDLAND_INCLUDE_DIR}
")

add_dependencies(semsim-tests
        semsim-static

        )


















