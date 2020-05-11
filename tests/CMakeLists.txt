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

add_dependencies(semsim-tests semsim-static)

message(STATUS "LINK_LIBRARIES ${LINK_LIBRARIES}")
message(STATUS "REDLAND_LIBRARY ${REDLAND_LIBRARY}")

target_link_libraries(semsim-tests PUBLIC
        $<TARGET_FILE:semsim-static>
        gtest gtest_main
        ${LINK_LIBRARIES}
        curl
        xml2
        dl
        pthread
        m
        c
        lzma
#        "${LIBCOMBINE_STATIC_LIBRARY}"
#        "${LIBSBML_STATIC_LIBRARY}"
#        "${ZIPPER_STATIC_LIBRARY}"
        #        "${ZLIB_STATIC_LIBRARY}"
#        z
#        "iconv"
#        "lzma"
#        "${BZ2_STATIC_LIBRARY}"
#        "${REDLAND_STATIC_LIBRARY}"
#        "${RASQAL_STATIC_LIBRARY}"
#        "${RAPTOR2_STATIC_LIBRARY}"
        #                "${LIBXML2_STATIC_LIBRARY}"
#        "rdf"
#        "rasqal"
#        "raptor"
#        "xml2"
#        "xslt"
#        "dl"
#        "curl"
#        "pthread"
#        "pcre"
#        "ltdl"
        #        ${LINK_LIBRARIES}
        #                z
        #                ${REDLAND_STATIC_LIBRARY}
        #                ${RASQAL_STATIC_LIBRARY}
        #                ${RAPTOR2_STATIC_LIBRARY}
        #
        #                ${LIBCOMBINE_STATIC_LIBRARY}
        #                ${ZIPPER_STATIC_LIBRARY}
        #
        #                ${LIBSBML_STATIC_LIBRARY}
        #                ${LIBXML2_STATIC_LIBRARY}
        #                ${ZLIB_STATIC_LIBRARY}
        #                ${BZ2_STATIC_LIBRARY}
        #                xslt
        #
        #                pcre
        #                pthread
        #                curl
        #                lzma
        #                m
        #                c
        )
get_target_property(y semsim-tests LINK_LIBRARIES)
MESSAGE(STATUS "Y ${y}")


MESSAGE(STATUS "INCLUDE_DIRS ${INCLUDE_DIRS}")
target_include_directories(semsim-tests PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${GOOGLETEST_SOURCE}/googletest/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${INCLUDE_DIRS}
        #        ${LIBSBML_INCLUDE_DIR}
        #        ${LIBXML2_INCLUDE_DIR}
        #        ${BZ_INCLUDE_DIR}
        #        ${ZLIB_INCLUDE_DIR}
        #        ${ZIPPER_INCLUDE_DIR}
        #        ${RAPTOR2_INCLUDE_DIR}
        #        ${RASQAL_INCLUDE_DIR}
        #        ${REDLAND_INCLUDE_DIR}
        #        ${LIBCOMBINE_INCLUDE_DIR}
        )

add_dependencies(semsim-tests
        semsim-static
        )
install(
        TARGETS semsim-tests
        EXPORT semsim-tests.a
        RUNTIME
        DESTINATION bin
)

















