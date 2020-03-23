
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
        RDFReader.h RDFReader.cpp

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
        Error.h)

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

# includes and linking
foreach (l ${LIBRARIES})

    target_include_directories(${l} PUBLIC
            ${CMAKE_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CYG_INCLUDE_DIR}
            ${LIBXML2_INCLUDE_DIR}
            ${LIBSBML_DEPS_INCLUDE_DIR}
            ${LIBSBML_INCLUDE_DIR}
            ${ZLIB_INCLUDE_DIR}
            ${ZIPPER_INCLUDE_DIR}
            ${LIBCOMBINE_INCLUDE_DIR}
            ${LIBBZ2_INCLUDE_DIR}
            ${LIBBZ_INCLUDE_DIR}
            ${RAPTOR2_INCLUDE_DIR}
            ${RASQAL_INCLUDE_DIR}
            ${REDLAND_INCLUDE_DIR}
            )

    target_link_libraries(${l} PUBLIC
            ${LIBXML2_LIBRARIES}
            ${LIBSBML_LIBRARY}
            ${ZLIB_LIBRARY}
            ${ZIPPER_LIBRARY}
            ${LIBCOMBINE_LIBRARY}
            ${LIBBZ2_LIBRARY}
            ${LIBBZ_LIBRARY}
            ${RAPTOR2_LIBRARY}
            ${RASQAL_LIBRARY}
            ${REDLAND_LIBRARY}
            )


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


