macro(ConfigurationSummary)
    message(STATUS "
########################################################
# Build Summary for LibOmexMeta ${LIBOMEXMETA_VERSION} #
########################################################

CMake variables and options
---------------------------
    PLATFORM                           ${PLATFORM}
    LIBOMEXMETA_VERSION                ${LIBOMEXMETA_VERSION}
    CMAKE_CXX_STANDARD                 ${CMAKE_CXX_STANDARD}
    CMAKE_POSITION_INDEPENDENT_CODE    ${CMAKE_POSITION_INDEPENDENT_CODE}
    CMAKE_INSTALL_RPATH                ${CMAKE_INSTALL_RPATH}
    CMAKE_INSTALL_PREFIX               ${CMAKE_INSTALL_PREFIX}
    CMAKE_VERBOSE_MAKEFILE             ${CMAKE_VERBOSE_MAKEFILE}
    CMAKE_BUILD_TYPE                   ${CMAKE_BUILD_TYPE}
    CMAKE_RUNTIME_OUTPUT_DIRECTORY     ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    CMAKE_LIBRARY_OUTPUT_DIRECTORY     ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    CMAKE_ARCHIVE_OUTPUT_DIRECTORY     ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
    MSVC_RUNTIME_LIBRARY               ${MSVC_RUNTIME_LIBRARY}

    WITH_SANITIZER                     ${WITH_SANITIZER}
    BUILD_SHARED_LIBS                  ${BUILD_SHARED_LIBS}
    BUILD_DOCS                         ${BUILD_DOCS}
    BUILD_TESTS                        ${BUILD_TESTS}
    N                                  ${N}

VCPKG config
------------
    VCPKG_ROOT                          ${VCPKG_ROOT}
    CMAKE_TOOLCHAIN_FILE                ${CMAKE_TOOLCHAIN_FILE}
    VCPKG_ARCH                          ${VCPKG_ARCH}
    VCPKG_X64_INSTALLED_PACKAGES        ${VCPKG_X64_INSTALLED_PACKAGES}
    VCPKG_X64_STATIC_INSTALLED_PACKAGES ${VCPKG_X64_STATIC_INSTALLED_PACKAGES}
    VCPKG_X64_STATIC_LIB_DIR            ${VCPKG_X64_STATIC_LIB_DIR}
    VCPKG_X64_LIB_DIR                   ${VCPKG_X64_LIB_DIR}
    VCPKG_X64_BIN_DIR                   ${VCPKG_X64_BIN_DIR}
    VCPKG_X64_INCLUDE_DIR               ${VCPKG_X64_INCLUDE_DIR}

Dependencies
------------
    PYOMEXMETA_DIR                      ${PYOMEXMETA_DIR}
    GOOGLETEST_SOURCE                   ${GOOGLETEST_SOURCE}
    LIBXML2
        LIBXML2_STATIC_LIBRARY              ${LIBXML2_STATIC_LIBRARY}
        LIBXML2_LIBRARY                     ${LIBXML2_LIBRARY}
        LIBXML2_INCLUDE_DIR                 ${LIBXML2_INCLUDE_DIR}
    Libxslt
        LIBXSLT_STATIC_LIBRARY              ${LIBXSLT_STATIC_LIBRARY}
        LIBXSLT_LIBRARY                     ${LIBXSLT_LIBRARY}
        LIBXSLT_INCLUDE_DIR                 ${LIBXSLT_INCLUDE_DIR}
    libcurl
        CURL_STATIC_LIBRARY                 ${CURL_STATIC_LIBRARY}
        CURL_LIBRARY                        ${CURL_LIBRARY}
        CURL_INCLUDE_DIR                    ${CURL_INCLUDE_DIR}
    libcharset
        LIBCHARSET_STATIC_LIBRARY           ${LIBCHARSET_STATIC_LIBRARY}
        LIBCHARSET_LIBRARY                  ${LIBCHARSET_LIBRARY}
    ssl
        SSL_STATIC_LIBRARY                  ${SSL_STATIC_LIBRARY}
        SSL_LIBRARY                         ${SSL_LIBRARY}
        SSL_INCLUDE_DIR                     ${SSL_INCLUDE_DIR}
    crypto
        CRYPTO_STATIC_LIBRARY               ${CRYPTO_STATIC_LIBRARY}
        CRYPTO_LIBRARY                      ${CRYPTO_LIBRARY}
        CRYPTO_INCLUDE_DIR                  ${CRYPTO_INCLUDE_DIR}
    YAJL
        YAJL_STATIC_LIBRARY                 ${YAJL_STATIC_LIBRARY}
        YAJL_LIBRARY                        ${YAJL_LIBRARY}
        YAJL_INCLUDE_DIR                    ${YAJL_INCLUDE_DIR}
    LZMA
        LZMA_STATIC_LIBRARY                 ${LZMA_STATIC_LIBRARY}
        LZMA_LIBRARY                        ${LZMA_LIBRARY}
        LZMA_INCLUDE_DIR                    ${LZMA_INCLUDE_DIR}
    ZLIB
        ZLIB_STATIC_LIBRARY                 ${ZLIB_STATIC_LIBRARY}
        ZLIB_LIBRARY                        ${ZLIB_LIBRARY}
        ZLIB_INCLUDE_DIR                    ${ZLIB_INCLUDE_DIR}
    PCRE
        PCRE_STATIC_LIBRARY                 ${PCRE_STATIC_LIBRARY}
        PCRE_LIBRARY                        ${PCRE_LIBRARY}
        PCRE_INCLUDE_DIR                    ${PCRE_INCLUDE_DIR}
    ICONV
        ICONV_STATIC_LIBRARY                ${ICONV_STATIC_LIBRARY}
        ICONV_LIBRARY                       ${ICONV_LIBRARY}
        ICONV_INCLUDE_DIR                   ${ICONV_INCLUDE_DIR}
    SQLITE
        SQLITE3_STATIC_LIBRARY              ${SQLITE3_STATIC_LIBRARY}
        SQLITE3_LIBRARY                     ${SQLITE3_LIBRARY}
        SQLITE3_INCLUDE_DIR                 ${SQLITE3_INCLUDE_DIR}
    Berkerly
        BERKELY_STATIC_LIBRARY              ${BERKELY_STATIC_LIBRARY}
        BERKELY_lIBRARY                     ${BERKELY_LIBRARY}
        BERKELY_INCLUDE_DIR                 ${BERKELY_INCLUDE_DIR}
    All Static Libraries
        STATIC_LIBRARIES                    ${STATIC_LIBRARIES}
    All Libraries
        LIBRARIES                           ${LIBRARIES}

Build variables
---------------
    INCLUDE_DIRECTORIES                      ${INCLUDE_DIRECTORIES}
    LINK_LIBRARIES                           ${LINK_LIBRARIES}

End Summary
########################################################################################
")
endmacro()
