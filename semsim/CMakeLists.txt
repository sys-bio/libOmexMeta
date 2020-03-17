
set(SEMSIM_SOURCES
        omex/OmexOutput.h omex/OmexOutput.cpp
        omex/SBMLOmex.h omex/SBMLOmex.cpp
        ontologies/CHEBI.h
        ontologies/CL.h
        ontologies/GO.h
        ontologies/OPB.h
        ontologies/SBO.h
        query/Condition.h
        query/IdentityCondition.h
        query/Query.h
        query/QueryResults.h

        query/SelectQuery.h
        rdf/RDFReader.h rdf/RDFReader.cpp

        AnnotationBase.h
        BiomodelsQualifiers.h BiomodelsQualifiers.cpp
        Component.h
        CompositeAnnotation.h
        DescriptorTerm.h
        Entity.h
        EntityBase.h
        EntityDescriptor.h
        Mediator.h
        Model.h
        ontologies/Ontology.h
        Participant.h
        PhysicalProperty.h
        Preproc.h
        Process.h
        RaptorUtils.h
        Relation.h Relation.cpp
        Resource.h Resource.cpp
        SemSim.h SemSim.cpp
        SemSimQualifiers.h SemSimQualifiers.cpp
        SingularAnnotation.h SingularAnnotation.cpp
        Sink.h
        Source.h
        Term.h
        URI.h
        )

if (WITH_RASQAL)
    list(APPEND ${SOURCES}
            query/RasqalQuery.h query/RasqalQuery.cpp
            query/RasqalQueryResult.h query/RasqalQueryResult.cpp)
endif ()

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
    target_link_libraries(${l} PRIVATE ${LIBSBML_LIBRARY})
    #    target_link_libraries(${l} PRIVATE ${LIBSBML_STATIC_LIBRARY})

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
    target_link_libraries(${l} PRIVATE ${LIBCOMBINE_LIBRARY})
    #    target_link_libraries(${l} PRIVATE ${LIBCOMBINE_STATIC_LIB})

    # catch2
    #    target_include_directories(${l} PUBLIC ${CATCH2_INCLUDE_DIR})
    #    target_link_libraries(${l} PUBLIC ${CATCH2_LIB})

    #raptor2
    target_include_directories(${l} PRIVATE ${RAPTOR2_INCLUDE_DIR})
    target_link_libraries(${l} PRIVATE ${RAPTOR2_LIBRARY})

    # any extra libs
    message(STATUS "LIBSBML_DEPS_INSTALL_PREFIX ${LIBSBML_DEPS_INSTALL_PREFIX}")
    target_link_libraries(${l} PRIVATE ${LIBBZ2_LIBRARY})
    target_include_directories(${l} PRIVATE ${LIBBZ2_INCLUDE_DIR})

    target_link_libraries(${l} PRIVATE ${LIBBZ_LIBRARY})
    target_include_directories(${l} PRIVATE ${LIBBZ_INCLUDE_DIR})

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
        libCombine
        zipper
        libsbml-dependencies
        )


