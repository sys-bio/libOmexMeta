
set(SEMSIM_SOURCES
        # annotation/Annotatable.cpp
        # annotation/Annotation.cpp
        # annotation/AnnotationCopier.cpp
        # annotation/Ontology.cpp
        # annotation/ReferenceOntologyAnnotation.cpp
        # annotation/ReferenceTerm.cpp
        # annotation/Relation.cpp
        # definitions/OtherKBconstants.cpp
        # definitions/PropertyType.cpp
        # definitions/RDFNamespace.cpp
        # definitions/SBMLconstants.cpp
        # definitions/SemSimRelations.cpp
        # definitions/SemSimTypes.cpp
        # model/physical/SemSimComponent.cpp
        # utilities/CaseInsensitiveComparator.cpp
        # utilities/DuplicateChecker.cpp
        # utilities/ErrorEntry.cpp
        # utilities/ErrorLog.cpp
        # utilities/SemSimComponentComparator.cpp
        # SemSimObject.cpp
        BiomodelsQualifiers.cpp
        Relation.cpp
        Resource.cpp
        SingularAnnotation.cpp
        SemSim.cpp
        SemSimQualifiers.cpp
        omex/OmexOutput.cpp
        omex/SBMLOmex.cpp
        rdf/RDFReader.cpp
        )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# static library
add_library(semsim-static STATIC ${SEMSIM_SOURCES})

# shared library
add_library(semsim SHARED ${SEMSIM_SOURCES})


set(SEMSIM_STATIC_LIBRARY semsim-static)
set(SEMSIM_LIBRARY semsim)
list(APPEND LIBRARIES semsim-static semsim)
message(STATUS "LIBRARIES: ${LIBRARIES}")

# includes and linking
foreach (l ${LIBRARIES})
    message(STATUS "l ${l}")

    target_include_directories(${l} PRIVATE ${CYG_INCLUDE_DIR})
    target_include_directories(${l} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    # libxml
    if (LIBXML2_LIB_DIR_FOUND)
        target_include_directories(${l} PRIVATE ${LIBXML2_INCLUDE_DIR})
        target_link_libraries(${l} PRIVATE ${LIBXML2_LIBRARIES})
    endif ()

    #    target_link_libraries(${l} PUBLIC )

    # libsbml dependency package
    target_include_directories(${l} PRIVATE ${LIBSBML_DEPS_INCLUDE_DIR})

    # libsbml
    target_include_directories(${l} PRIVATE ${LIBSBML_INCLUDE_DIR})
    target_link_libraries(${l} PRIVATE ${LIBSBML_STATIC_LIB})

    # zlib
    target_include_directories(${l} PRIVATE ${ZLIB_INCLUDE_DIR})
    target_link_libraries(${l} PRIVATE ${ZLIB_LIBRARY})

    # zipper
    message(STATUS "ZIPPER_INCLUDE_DIR ${ZIPPER_INCLUDE_DIR}")
    message(STATUS "ZIPPER_LIBRARY ${ZIPPER_LIBRARY}")
    target_include_directories(${l} PRIVATE ${ZIPPER_INCLUDE_DIR})
    target_link_libraries(${l} PRIVATE ${ZIPPER_LIBRARY})

    # libcombine
    target_include_directories(${l} PRIVATE ${LIBCOMBINE_INCLUDE_DIR})
    target_link_libraries(${l} PRIVATE D:/libsemsim/third_party/libCombine/INSTALL/lib/libCombine.dll.a)
#    target_link_libraries(${l} PRIVATE ${LIBCOMBINE_STATIC_LIB})

    # catch2
    #    target_include_directories(${l} PUBLIC ${CATCH2_INCLUDE_DIR})
    #    target_link_libraries(${l} PUBLIC ${CATCH2_LIB})

    #raptor2
    target_include_directories(${l} PRIVATE ${RAPTOR2_INCLUDE_DIR})
    target_link_libraries(${l} PRIVATE ${RAPTOR2_LIBRARY})

    # any extra libs
    target_link_libraries(${l} PRIVATE D:/libsemsim/third_party/libSBML-dependencies/INSTALL/lib/libbz2.a)
    target_link_libraries(${l} PRIVATE C:/cygwin64/lib/libxml2.dll.a)
    target_link_libraries(${l} PRIVATE D:/libsemsim/third_party/libSBML-dependencies/INSTALL/lib/libzlib.a)
#    target_link_libraries(${l} PRIVATE ${EXTRA_LIBS})

    # not sure what this is for
    if (CYGWIN)
        target_link_libraries(${l} PRIVATE uuid)
    endif ()


    install(TARGETS ${l}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            PUBLIC_HEADER DESTINATION include)
endforeach ()


add_dependencies(semsim
        libsbml
        raptor2
        libCombine
        zipper
        libsbml-dependencies
        )


