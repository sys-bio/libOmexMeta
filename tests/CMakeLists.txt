add_executable(semsim-tests
        SBMLFactory.h
        UrlTests.cpp
        SubjectTests.cpp
        PredicateTests.cpp
        ResourceTests.cpp
        TripleTests.cpp
        ControlledVocabularyTests.cpp
        RaptorUtilsTests.cpp
        RDFTests.cpp
        WriterTests.cpp AnnotationSamples.h ReaderTests.cpp)


target_link_libraries(semsim-tests PRIVATE
        $<TARGET_FILE:semsim-static>
        gtest gtest_main
        ${LIBSBML_STATIC_LIBRARY}
        ${LIBXML2_STATIC_LIBRARY}
        ${LIBBZ_STATIC_LIBRARY}
        ${ZLIB_STATIC_LIBRARY}
        ${ZIPPER_STATIC_LIBRARY}
        ${LIBCOMBINE_STATIC_LIB}
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
        ${LIBCOMBINE_INCLUDE_DIR}
        )

add_dependencies(semsim-tests
        semsim-static
        )


















