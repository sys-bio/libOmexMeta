
set(SEMSIM_SOURCES
        CurlGet.cpp CurlGet.h
        RDFNode.cpp RDFNode.h
        Subject.h Subject.cpp
        Predicate.h Predicate.cpp
        Resource.cpp Resource.h
        Triple.h Triple.cpp
#        RaptorUtils.cpp RaptorUtils.h
#        SemsimCombineArchive.cpp SemsimCombineArchive.h

        SemsimUtils.cpp SemsimUtils.h
        MetaID.cpp MetaID.h
        XmlAssistant.cpp XmlAssistant.h
        Reader.h Reader.cpp
        Editor.h Editor.cpp
        Writer.h Writer.cpp
        RDF.cpp RDF.h
        SemSim.h
        Participant.cpp Participant.h CompositeAnnotation.cpp CompositeAnnotation.h PhysicalEntity.cpp PhysicalEntity.h PhysicalPhenomenon.cpp PhysicalPhenomenon.h PhysicalProcess.cpp PhysicalProcess.h PhysicalPropertyResource.cpp PhysicalPropertyResource.h AnnotationType.h PhysicalForce.cpp PhysicalForce.h Query.cpp Query.h)


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SEMSIM_STATIC_LIBRARY semsim-static)
set(SEMSIM_LIBRARY semsim)

# static library
add_library(${SEMSIM_STATIC_LIBRARY} STATIC ${SEMSIM_SOURCES})

# shared library
add_library(${SEMSIM_LIBRARY} SHARED ${SEMSIM_SOURCES})
if (UNIX)
    MESSAGE(STATUS "LINUX strS")
    #fPIC for linux shared library strs
    set_property(TARGET ${SEMSIM_LIBRARY} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif ()


list(APPEND LIBRARIES ${SEMSIM_STATIC_LIBRARY} ${SEMSIM_LIBRARY})


target_include_directories(${SEMSIM_STATIC_LIBRARY} PUBLIC # make public so include dirs propagate into test binaries
        ${CMAKE_SOURCE_DIR}
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
        ${LIBCOMBINE_STATIC_LIB}
        ${ZIPPER_STATIC_LIBRARY}
        ${ZLIB_STATIC_LIBRARY}
        ${LIBSBML_STATIC_LIB}
        ${LIBBZ_STATIC_LIBRARY}
        ${REDLAND_LIBRARY}
        ${RASQAL_LIBRARY}
        ${RAPTOR2_LIBRARY}
        ${LIBXML2_STATIC_LIBRARY}
        dl bz2 z curl xslt

        )


target_include_directories(${SEMSIM_LIBRARY} PUBLIC # make public so include dirs propagate into test binaries
        ${CMAKE_SOURCE_DIR}
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
        ${LIBCOMBINE_STATIC_LIB}
        ${LIBXML2_STATIC_LIBRARY}
        ${LIBSBML_STATIC_LIBRARY}
        #        ${ZLIB_STATIC_LIBRARY}
        ${ZIPPER_STATIC_LIBRARY}
        #        ${LIBBZ_STATIC_LIBRARY}
        ${RAPTOR2_LIBRARY}
        ${RASQAL_LIBRARY}
        ${REDLAND_LIBRARY}
        dl bz2 z curl xslt
        )

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


