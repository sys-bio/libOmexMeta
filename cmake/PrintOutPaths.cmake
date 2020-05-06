
function(PrintOutPaths)

    message(STATUS "
    ###################################################################
    #   Library and Include Directory Summary
    #
    libsbml dependencies
        LIBSBML_DEPS_INCLUDE_DIR           ${LIBSBML_DEPS_INCLUDE_DIR}
        LIBSBML_DEPS_LIB_DIR               ${LIBSBML_DEPS_LIB_DIR}
    bzlib
        LIBBZ_INCLUDE_DIR                  ${LIBBZ_INCLUDE_DIR}
        LIBBZ_STATIC_LIBRARY               ${LIBBZ_STATIC_LIBRARY}
    zlib
        ZLIB_INCLUDE_DIR                   ${ZLIB_INCLUDE_DIR}
        ZLIB_STATIC_LIBRARY                ${ZLIB_STATIC_LIBRARY}
    zipper
        ZIPPER_INCLUDE_DIR                 ${ZIPPER_INCLUDE_DIR}
        ZIPPER_STATIC_LIBRARY              ${ZIPPER_STATIC_LIBRARY}
    libxml2
        LIBXML2_INCLUDE_DIR                ${LIBXML2_INCLUDE_DIR}
        LIBXML2_STATIC_LIBRARY             ${LIBXML2_STATIC_LIBRARY}
    libsbml
        LIBSBML_INCLUDE_DIR                ${LIBSBML_INCLUDE_DIR}
        LIBSBML_STATIC_LIBRARY             ${LIBSBML_STATIC_LIBRARY}
    libcombine
        LIBCOMBINE_INCLUDE_DIR             ${LIBCOMBINE_INCLUDE_DIR}
        LIBCOMBINE_LIBRARY                 ${LIBCOMBINE_LIBRARY}
        LIBCOMBINE_STATIC_LIB              ${LIBCOMBINE_STATIC_LIB}
    Redland libraries
        REDLAND_ROOT                       ${REDLAND_ROOT}
        raptor
            RAPTOR2_INCLUDE_DIR            ${RAPTOR2_INCLUDE_DIR}
            RAPTOR2_STATIC_LIBRARY         ${RAPTOR2_STATIC_LIBRARY}
        rasqal
            RASQAL_INCLUDE_DIR             ${RASQAL_INCLUDE_DIR}
            RASQAL_STATIC_LIBRARY          ${RASQAL_STATIC_LIBRARY}
        librdf
            REDLAND_INCLUDE_DIR             ${REDLAND_INCLUDE_DIR}
            REDLAND_STATIC_LIBRARY          ${REDLAND_STATIC_LIBRARY}
    googletest
        GOOGLETEST_SOURCE                  ${GOOGLETEST_SOURCE}
    ")
    endfunction()
