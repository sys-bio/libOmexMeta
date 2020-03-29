
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
        query/RasqalQuery.h query/RasqalQuery.cpp
        query/RasqalQueryResult.h query/RasqalQueryResult.cpp
        query/SelectQuery.h

        Accessor.h
        Annotation.h
        MetaID.h
        SBMLImporter.h
        SBMLModel.h
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
        SBMLModel.h
        ontologies/Ontology.h
        Participant.h
        PhysicalProperty.h
#        Preproc.h
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
        Error.h
        sbmlTest.h
        )


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SEMSIM_STATIC_LIBRARY semsim-static)
set(SEMSIM_LIBRARY semsim)

# static library
add_library(${SEMSIM_STATIC_LIBRARY} STATIC ${SEMSIM_SOURCES})

# shared library
add_library(${SEMSIM_LIBRARY} SHARED ${SEMSIM_SOURCES} sbmlTest.h)
if (UNIX)
    MESSAGE(STATUS "LINUX BUILDS")
    #fPIC for linux shared library builds
    set_property(TARGET ${SEMSIM_LIBRARY} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif ()


list(APPEND LIBRARIES ${SEMSIM_STATIC_LIBRARY} ${SEMSIM_LIBRARY})


target_include_directories(${SEMSIM_STATIC_LIBRARY} PUBLIC # make public so include dirs propagate into test binaries
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CYG_INCLUDE_DIR}

        ${LIBXML2_INCLUDE_DIR}
        ${LIBSBML_DEPS_INCLUDE_DIR}
        ${LIBSBML_INCLUDE_DIR}
        ${ZLIB_INCLUDE_DIR}
        ${ZIPPER_INCLUDE_DIR}
        ${LIBCOMBINE_INCLUDE_DIR}
        ${LIBBZ_INCLUDE_DIR}

        ${REDLAND_INCLUDE_DIR}
        ${RASQAL_INCLUDE_DIR}
        ${RAPTOR2_INCLUDE_DIR}

        )

target_link_libraries(${SEMSIM_STATIC_LIBRARY} PUBLIC # make public so libraries propagate into test binaries
        ${LIBXML2_STATIC_LIBRARY}
        ${ZLIB_STATIC_LIBRARY}
        ${ZIPPER_STATIC_LIBRARY}
        ${LIBBZ_STATIC_LIBRARY}
        ${LIBSBML_STATIC_LIBRARY}
        ${LIBCOMBINE_STATIC_LIB}
        ${REDLAND_LIBRARY}
        ${RASQAL_LIBRARY}
        ${RAPTOR2_LIBRARY}
        )

get_target_property(Y ${SEMSIM_STATIC_LIBRARY} LINK_LIBRARIES)
MESSAGE(STATUS "Y
/usr/local/lib/libxml2.a;
/mnt/d/libsemsim/third_party/libsbml-5.18.0/INSTALL/lib/libsbml-static.a;
/usr/lib/x86_64-linux-gnu/libz.a;
/mnt/d/libsemsim/third_party/zipper/INSTALL/lib/libZipper-static.a;
/mnt/d/libsemsim/third_party/libCombine-0.2.3/INSTALL/lib/libcombine-static.a;
/usr/local/lib/libbz2.a
"
)

target_include_directories(${SEMSIM_LIBRARY} PUBLIC # make public so include dirs propagate into test binaries
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CYG_INCLUDE_DIR}

        ${LIBXML2_INCLUDE_DIR}
        ${LIBSBML_DEPS_INCLUDE_DIR}
        ${LIBSBML_INCLUDE_DIR}
        ${ZLIB_INCLUDE_DIR}
        ${ZIPPER_INCLUDE_DIR}
        ${LIBCOMBINE_INCLUDE_DIR}
        ${LIBBZ_INCLUDE_DIR}
        ${RAPTOR2_INCLUDE_DIR}
        ${RASQAL_INCLUDE_DIR}
        ${REDLAND_INCLUDE_DIR}
        )

target_link_libraries(${SEMSIM_LIBRARY} PUBLIC # make public so libraries propagate into test binaries
        ${LIBXML2_STATIC_LIBRARY}
        ${LIBSBML_STATIC_LIBRARY}
#        ${ZLIB_STATIC_LIBRARY}
        ${ZIPPER_STATIC_LIBRARY}
        ${LIBCOMBINE_STATIC_LIB}
#        ${LIBBZ_STATIC_LIBRARY}
        ${RAPTOR2_LIBRARY}
        ${RASQAL_LIBRARY}
        ${REDLAND_LIBRARY}
        dl bz2 z curl xslt
        )

get_target_property(X ${SEMSIM_LIBRARY} LINK_LIBRARIES)


MESSAGE(STATUS "X ${X}")
install(TARGETS ${SEMSIM_STATIC_LIBRARY} ${SEMSIM_LIBRARY}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)


add_dependencies(semsim
        libsbml
        libCombine
        zipper
        libsbml-dependencies
        )


