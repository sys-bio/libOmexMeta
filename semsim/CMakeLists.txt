
set(SEMSIM_SOURCES
        omex/OmexOutput.h omex/OmexOutput.cpp
        omex/SBMLOmex.h omex/SBMLOmex.cpp
#        ontologies/CHEBI.h
#        ontologies/CL.h
#        ontologies/GO.h
#        ontologies/OPB.h
#        ontologies/SBO.h
#        query/Condition.h
#        query/IdentityCondition.h
#        query/Query.h
#        query/QueryResults.h
#
#        BiomodelsQualifiers.h BiomodelsQualifiers.cpp
#
#        query/RasqalQuery.h query/RasqalQuery.cpp
#        query/RasqalQueryResult.h query/RasqalQueryResult.cpp
#        query/SelectQuery.h

#        sbml/Accessor.h
#        sbml/Annotation.h
#        sbml/MetaID.h
#        sbml/SBMLImporter.h
#        sbml/SBMLModel.h
#        RDFReader.h RDFReader.cpp
#
#        AnnotationBase.h
#        BiomodelsQualifiers.h BiomodelsQualifiers.cpp
#        Component.h
#        CompositeAnnotation.h
#        DescriptorTerm.h
#        Entity.h
#        EntityBase.h
#        EntityDescriptor.h
#        Mediator.h
#        Model.h
#        ontologies/Ontology.h
#        Participant.h
#        PhysicalProperty.h
#        Preproc.h
#        Process.h
#        RaptorUtils.h
#        Relation.h Relation.cpp
#        Resource.h Resource.cpp
#        SemSim.h SemSim.cpp
#        SemSimQualifiers.h SemSimQualifiers.cpp
#        SingularAnnotation.h SingularAnnotation.cpp
#        Sink.h
#        Source.h
#        Term.h
#        URI.h
#        Error.h
        sbmlTest.h
        )


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SEMSIM_STATIC_LIBRARY semsim-static)
set(SEMSIM_LIBRARY semsim)

# static library
add_library(${SEMSIM_STATIC_LIBRARY} STATIC ${SEMSIM_SOURCES})

# shared library
add_library(${SEMSIM_LIBRARY} SHARED ${SEMSIM_SOURCES} sbmlTest.h)

list(APPEND LIBRARIES ${SEMSIM_STATIC_LIBRARY} ${SEMSIM_LIBRARY})

# includes and linking
foreach (l ${LIBRARIES})

    target_include_directories(${l} PUBLIC # make public so include dirs propagate into test binaries
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

    target_link_libraries(${l} PUBLIC # make public so libraries propagate into test binaries
            ${LIBBZ_STATIC_LIBRARY}
            ${ZLIB_STATIC_LIBRARY}
            ${ZIPPER_STATIC_LIBRARY}
            ${LIBXML2_STATIC_LIBRARY}
            ${LIBSBML_STATIC_LIBRARY}
#            /mnt/d/libsemsim/third_party/libsbml/INSTALL/lib/libsbml.so

            ${LIBCOMBINE_STATIC_LIB}
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


