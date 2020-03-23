add_executable(semsim-tests
        SBMLImporterTests.cpp
        LibSBMLTests.cpp
        ModelStrings.h Raptor2Test.cpp)

target_include_directories(semsim-tests PRIVATE
        ${CMAKE_SOURCE_DIR}/semsim
#        ${CMAKE_CURRENT_SOURCE_DIR}
        ${GOOGLETEST_SOURCE}/googletest/include
#        ${LIBSBML_INCLUDE_DIR}
#        ${LIBXML2_INCLUDE_DIR}
#        ${LIBBZ_INCLUDE_DIR}
        )



target_link_libraries(semsim-tests
        $<TARGET_FILE:semsim-static>
        gtest gtest_main
#        ${LIBSBML_LIBRARY}
#        ${LIBSBML_STATIC_LIBRARY}
#        ${RAPTOR2_LIBRARY}
#        ${LIBXML2_LIBRARY}
#        ${LIBBZ_LIBRARY}
#        ${LIBCOMBINE_LIBRARY}

        )

add_dependencies(semsim-tests
        semsim-static

        )

















