

set(TEST_SOURCES
        SBMLFactory.h
        SubjectTests.cpp
        PredicateTests.cpp
        ResourceTests.cpp
        CurlGetTests.cpp
        TripleTests.cpp
        TripplesTests.cpp
        SemsimUtilsTests.cpp
        ReaderTests.cpp
        WriterTests.cpp
        RDFTests.cpp
        RDFReadAndWriteTests.cpp
        #        AnnotationSamples.h
        #        MetaIDTests.cpp
        #        XmlAssistantTests.cpp
        #        EditorTests.cpp
        #        ParticipantTests.cpp
        #        PhysicalPropertyTests.cpp
        #        PhysicalEntityTests.cpp
        #        PhysicalPhenomenonTests.cpp
        #        PhysicalProcessTests.cpp
        #        PhysicalForceTests.cpp
        #        SemsimCombineArchiveTests.cpp
        #        QueryTests.cpp
        #        CAPITests.cpp
        )

if (REDLAND_WRAPPER_TESTS)
    set(TEST_SOURCES ${TEST_SOURCES} ${REDLAND_WRAPPER_TEST_SOURCES})
endif ()

#add_executable(semsim-tests ${TEST_SOURCES})
#
#target_compile_options(semsim-tests PRIVATE -g)

#add_dependencies(semsim-tests semsim-static)

message(STATUS "LINK_LIBRARIES ${LINK_LIBRARIES}")
message(STATUS "REDLAND_LIBRARY ${REDLAND_LIBRARY}")

#target_link_libraries(semsim-tests PUBLIC
#        $<TARGET_FILE:semsim-static>
#        gtest gtest_main
#        ${LINK_LIBRARIES}
#        curl
#        xml2
#        dl
#        pthread
#        m
#        c
#        lzma
#        )

set(CMAKE_VERBOSE_MAKEFILE 1)
if (CLANG)
    message(STATUS "CLANG cmopiler")
    SET(ADDRESS_SANITIZER_FLAGS "-fsatize=address")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ADDRESS_SANITIZER_LINK_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDRESS_SANITIZER_FLAGS}")
ENDIF ()


MESSAGE(STATUS "INCLUDE_DIRS ${INCLUDE_DIRS}")
#target_include_directories(semsim-tests PRIVATE
#        ${CMAKE_SOURCE_DIR}
#        ${CMAKE_SOURCE_DIR}/src
#        ${CMAKE_SOURCE_DIR}/src/semsim
#        ${CMAKE_CURRENT_SOURCE_DIR}/RedlandAPITests
#        ${GOOGLETEST_SOURCE}/googletest/include
#        ${INCLUDE_DIRS}
#        )
#
#add_dependencies(semsim-tests
#        semsim-static
#        )
#install(
#        TARGETS semsim-tests
#        EXPORT semsim-tests.a
#        RUNTIME
#        DESTINATION bin
#)

















