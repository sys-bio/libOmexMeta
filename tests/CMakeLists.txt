add_executable(semsim-tests
        SBMLImporterTests.cpp)

target_include_directories(semsim-tests PRIVATE
        ${CMAKE_SOURCE_DIR}/semsim
        ${GOOGLETEST_SOURCE}/googletest/include
        ${LIBSBML_INCLUDE_DIR}
        )

message(STATUS "${GOOGLETEST_SOURCE}/googletest/include")
message(STATUS "LIBSBML_LIBRARY ${LIBSBML_LIBRARY}")
message(STATUS "LIBSBML_STATIC_LIBRARY ${LIBSBML_STATIC_LIBRARY}")


target_link_libraries(semsim-tests
        $<TARGET_FILE:semsim-static>
        gtest gtest_main
        ${LIBSBML_LIBRARY}
#        ${LIBSBML_STATIC_LIBRARY}
        ${RAPTOR2_LIBRARY}
#        ${LIBCOMBINE_LIBRARY}

        )

add_dependencies(semsim-tests
        semsim-static

        )

















