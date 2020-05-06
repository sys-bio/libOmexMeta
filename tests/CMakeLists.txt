add_executable(semsim-tests
        SemsimUtilsTests.cpp
        SBMLFactory.h
        RDFNodeTests.cpp
        SubjectTests.cpp
        PredicateTests.cpp
        ResourceTests.cpp
        TripleTests.cpp
        AnnotationSamples.h
        CurlGetTests.cpp
        MetaIDTests.cpp
        XmlAssistantTests.cpp
        ReaderTests.cpp
        WriterTests.cpp
        EditorTests.cpp
        RDFTests.cpp
        ParticipantTests.cpp
        PhysicalPropertyTests.cpp
        PhysicalEntityTests.cpp
        PhysicalPhenomenonTests.cpp
        PhysicalProcessTests.cpp
        PhysicalForceTests.cpp
        SemsimCombineArchiveTests.cpp
        QueryTests.cpp TripplesTests.cpp RDFReadAndWriteTests.cpp)


target_link_libraries(semsim-tests PRIVATE
        $<TARGET_FILE:semsim-static>
        gtest gtest_main
        ${LIBCOMBINE_STATIC_LIB}
        ${ZIPPER_STATIC_LIBRARY}

        ${LIBSBML_STATIC_LIBRARY}
        ${ZLIB_STATIC_LIBRARY}
        ${LIBBZ_STATIC_LIBRARY}
        ${LIBXML2_STATIC_LIBRARY}

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
install(TARGETS semsim-tests
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    )

















