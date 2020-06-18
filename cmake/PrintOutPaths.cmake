
function(PrintOutPaths)

    message(STATUS "
#-------------------------------------------------------------------------------
#Configuration Summary
#-------------------------------------------------------------------------------
    Configured on host $ENV{COMPUTERNAME} ${HOSTNAME}
        host OS                   ${CMAKE_SYSTEM_NAME}
        host architecture         ${CMAKE_SYSTEM_PROCESSOR}
        Platform                  ${PLATFORM}
        CMAKE_MAKE_PROGRAM        ${CMAKE_MAKE_PROGRAM}
    General flags:
        CC                        ${CMAKE_C_COMPILER}
        CXX                       ${CMAKE_CXX_COMPILER}
        CPPFLAGS                  ${BUILD_DEFINITIONS}
        CFLAGS                    ${CMAKE_C_FLAGS}
        CXXFLAGS                  ${CMAKE_CXX_FLAGS}
        LDFLAGS                   ${CMAKE_EXE_LINKER_FLAGS}
    Installation prefix:          ${CMAKE_INSTALL_PREFIX}
    Options:
        HAVE_DEPENDENCIES         ${HAVE_DEPENDENCIES}
        BUILD_TESTS               ${BUILD_TESTS}
        BUILD_SHARED              ${BUILD_SHARED}
        BUILD_WRAPPER_TESTS       ${BUILD_WRAPPER_TESTS}
        BUILD_DOCS                ${BUILD_DOCS}
        WITH_ADDRESS_SANITIZER    ${WITH_ADDRESS_SANITIZER}

    Paths
    -----
    libsbml dependencies
        LIBSBML_DEPS_INCLUDE_DIR           ${LIBSBML_DEPS_INCLUDE_DIR}
        LIBSBML_DEPS_LIB_DIR               ${LIBSBML_DEPS_LIB_DIR}
        LIBSBML_DEPS_SOURCE_DIR            ${LIBSBML_DEPS_SOURCE_DIR}
        LIBSBML_DEPS_BINARY_DIR            ${LIBSBML_DEPS_BINARY_DIR}
        LIBSBML_DEPS_INSTALL_PREFIX        ${LIBSBML_DEPS_INSTALL_PREFIX}
    bzlib
        BZ2_INCLUDE_DIR                    ${BZ2_INCLUDE_DIR}
        BZ2_STATIC_LIBRARY                 ${BZ2_STATIC_LIBRARY}
    zlib
        ZLIB_SOURCE_DIR                    ${ZLIB_SOURCE_DIR}
        ZLIB_BUILD_DIR                     ${ZLIB_BUILD_DIR}
        ZLIB_INSTALL_PREFIX                ${ZLIB_INSTALL_PREFIX}
        ZLIB_INCLUDE_DIR                   ${ZLIB_INCLUDE_DIR}
        ZLIB_STATIC_LIBRARY                ${ZLIB_STATIC_LIBRARY}
    iconv
        ICONV_LIB_DIR                      ${ICONV_LIB_DIR}
        ICONV_INCLUDE_DIR                  ${ICONV_INCLUDE_DIR}
        ICONV_STATIC_LIBRARY               ${ICONV_STATIC_LIBRARY}
        ICONV_LIBRARY                      ${ICONV_LIBRARY}
    zipper
        ZIPPER_INCLUDE_DIR                 ${ZIPPER_INCLUDE_DIR}
        ZIPPER_STATIC_LIBRARY              ${ZIPPER_STATIC_LIBRARY}
        ZIPPER_SOURCE_DIR                  ${ZIPPER_SOURCE_DIR}
        ZIPPER_BINARY_DIR                  ${ZIPPER_BINARY_DIR}
        ZIPPER_INSTALL_PREFIX              ${ZIPPER_INSTALL_PREFIX}
        LIBSBML_DEPS_INSTALL_PREFIX        ${LIBSBML_DEPS_INSTALL_PREFIX}
    libxml2
        LIBXML2_INCLUDE_DIR                ${LIBXML2_INCLUDE_DIR}
        LIBXML2_STATIC_LIBRARY             ${LIBXML2_STATIC_LIBRARY}
        LIBXML2_SOURCE_DIR                 ${LIBXML2_SOURCE_DIR}
        LIBXML2_BINARY_DIR                 ${LIBXML2_BINARY_DIR}
        LIBXML2_INSTALL_PREFIX             ${LIBXML2_INSTALL_PREFIX}
    libsbml
        LIBSBML_INCLUDE_DIR                ${LIBSBML_INCLUDE_DIR}
        LIBSBML_STATIC_LIBRARY             ${LIBSBML_STATIC_LIBRARY}
        LIBSBML_SOURCE_DIR                 ${LIBSBML_SOURCE_DIR}
        LIBSBML_BINARY_DIR                 ${LIBSBML_BINARY_DIR}
        LIBSBML_INSTALL_PREFIX             ${LIBSBML_INSTALL_PREFIX}
    libcombine
        LIBCOMBINE_INCLUDE_DIR             ${LIBCOMBINE_INCLUDE_DIR}
        LIBCOMBINE_STATIC_LIBRARY          ${LIBCOMBINE_STATIC_LIBRARY}
        LIBCOMBINE_SOURCE_DIR              ${LIBCOMBINE_SOURCE_DIR}
        LIBCOMBINE_BINARY_DIR              ${LIBCOMBINE_BINARY_DIR}
        LIBCOMBINE_INSTALL_PREFIX          ${LIBCOMBINE_INSTALL_PREFIX}
    googletest
        GOOGLETEST_SOURCE                  ${GOOGLETEST_SOURCE}
    ")
endfunction()
