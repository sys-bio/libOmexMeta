
set(SEMSIM_SOURCES
        uri.h uri.cpp
        Subject.h Subject.cpp
        Resource.cpp Resource.h
        Triple.h Triple.cpp
        semsim.h
        IRDF.h
        Predicate.cpp Predicate.h
        RaptorUtils.cpp RaptorUtils.h
        RDF.cpp RDF.h
        Writer.h Writer.cpp
        Reader.h Reader.cpp SemsimCombineArchive.cpp SemsimCombineArchive.h CurlGet.cpp CurlGet.h SemsimUtils.cpp SemsimUtils.h XmlAssistant.cpp XmlAssistant.h MetaID.cpp MetaID.h Editor.h Editor.cpp TripleList.cpp TripleList.h)


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SEMSIM_STATIC_LIBRARY semsim-static)
set(SEMSIM_LIBRARY semsim)

# static library
add_library(${SEMSIM_STATIC_LIBRARY} STATIC ${SEMSIM_SOURCES})

# shared library
add_library(${SEMSIM_LIBRARY} SHARED ${SEMSIM_SOURCES})
if (UNIX)
    MESSAGE(STATUS "LINUX BUILDS")
    #fPIC for linux shared library builds
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


