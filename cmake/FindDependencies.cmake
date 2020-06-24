macro(FindDependencies)
    set(DEFAULT_LINUX_LOCATIONS
            "/usr/local/lib"
            "/mnt/d/usr/local/lib"
            "/mnt/c/usr/local/lib"
            "/usr/lib/x86_64-linux-gnu"
            "mnt/d/usr/lib/x86_64-linux-gnu"
            "mnt/c/usr/lib/x86_64-linux-gnu"
            # include dirs
            "/usr/local/include"
            "/mnt/d/usr/local/include"
            "/mnt/c/usr/local/include"
            "/usr/include/x86_64-linux-gnu"
            "/mnt/d/usr/include/x86_64-linux-gnu"
            "/mnt/c/usr/include/x86_64-linux-gnu"
            )

    # libxml2
    find_library(LIBXML2_STATIC_LIBRARY
            NAMES libxml2.lib libxml2.a
            PATHS ${VCPKG_X64_LIB_DIR}
            NO_DEFAULT_PATH
            )

    find_file(LIBXML2_LIBRARY
            NAMES libxml2.dll libxml2.so xml2 xml2.dll libxml2
            PATHS ${VCPKG_X64_BIN_DIR}
            ${DEFAULT_LINUX_LOCATIONS}
            NO_DEFAULT_PATH
            )

    find_path(LIBXML2_INCLUDE_DIR
            NAMES libxml/parser.h
            PATHS ${VCPKG_X64_INCLUDE_DIR}
            NO_DEFAULT_PATH
            )

    # libxslt
    # Note vcpkg port broken on x64-linux. I've reported
    # the issue and we'll build in support for it when they
    # have fixed it. For now, on linux, we can use the apt version.
    #    find_library(LIBXSLT_STATIC_LIBRARY
    #            NAMES libxslt.lib libxslt.a
    #            PATHS ${VCPKG_X64_LIB_DIR}
    #            /usr/local/lib
    #            mnt/d/usr/local/lib
    #            mnt/c/usr/local/lib
    #            NO_DEFAULT_PATH
    #            )

    find_file(LIBXSLT_LIBRARY
            NAMES libxslt.dll libxslt.so
            PATHS ${VCPKG_X64_BIN_DIR}
            ${DEFAULT_LINUX_LOCATIONS}
            NO_DEFAULT_PATH
            )

    find_path(LIBXSLT_INCLUDE_DIR
            NAMES libxslt/libxslt.h libxslt/xsltconfig.h
            PATHS ${VCPKG_X64_INCLUDE_DIR}
            ${DEFAULT_LINUX_LOCATIONS}
            NO_DEFAULT_PATH
            )

    # curl
    find_library(CURL_STATIC_LIBRARY
            NAMES libcurl.lib libcurl.a
            PATHS ${VCPKG_X64_LIB_DIR}
            NO_DEFAULT_PATH
            )

    find_file(CURL_LIBRARY
            NAMES libcurl.dll curl.dll libcurl.so
            PATHS ${VCPKG_X64_BIN_DIR}
            ${DEFAULT_LINUX_LOCATIONS}
            NO_DEFAULT_PATH
            REQUIRED
            )

    find_path(CURL_INCLUDE_DIR
            NAMES curl/curl.h
            PATHS ${VCPKG_X64_INCLUDE_DIR}
            NO_DEFAULT_PATH
            )

    # libcharset (from libiconv)
    if (PLATFORM STREQUAL "windows-msvc")
        find_library(LIBCHARSET_STATIC_LIBRARY
                NAMES libcharset.lib libcharset.a
                PATHS ${VCPKG_X64_LIB_DIR}
                ${LINUX_DEFAULT_LOCATIONS}
                NO_DEFAULT_PATH
                )
    endif ()

    find_file(LIBCHARSET_LIBRARY
            NAMES libcharset.dll libcharset.so
            PATHS ${VCPKG_X64_BIN_DIR}
            ${DEFAULT_LINUX_LOCATIONS}
            NO_DEFAULT_PATH
            REQUIRED
            )
    #       POSSIBLY NOT NEEDED
    #        find_path(LIBCHARSETL_INCLUDE_DIR
    #                NAMES curl/curl.h
    #                PATHS ${VCPKG_X64_INCLUDE_DIR}
    #                )


    # openssl
    find_library(SSL_STATIC_LIBRARY
            NAMES libssl.lib libssl.a
            PATHS ${VCPKG_X64_LIB_DIR}
            NO_DEFAULT_PATH
            )

    find_file(SSL_LIBRARY
            NAMES libssl.dll libssl-1_1-x64.dll libssl.so
            PATHS ${VCPKG_X64_BIN_DIR}
            ${DEFAULT_LINUX_LOCATIONS}
            NO_DEFAULT_PATH
            REQUIRED
            )
    find_path(SSL_INCLUDE_DIR
            NAMES openssl/ssl2.h openssl/ssl3.h
            PATHS ${VCPKG_X64_INCLUDE_DIR}
            NO_DEFAULT_PATH
            )

    # libcrypto
    find_library(CRYPTO_STATIC_LIBRARY
            NAMES libcrypto.lib libcrypto.a
            PATHS ${VCPKG_X64_LIB_DIR}
            NO_DEFAULT_PATH
            )

    find_file(CRYPTO_LIBRARY
            NAMES libcrypto.dll libcrypto-1_1-x64.dll libcrypto.so
            PATHS ${VCPKG_X64_BIN_DIR}
            ${DEFAULT_LINUX_LOCATIONS}
            NO_DEFAULT_PATH
            REQUIRED
            )
    find_path(SSL_INCLUDE_DIR
            NAMES openssl/crypto.h
            PATHS ${VCPKG_X64_INCLUDE_DIR}
            NO_DEFAULT_PATH
            )

    # yajl
    find_library(YAJL_STATIC_LIBRARY
            NAMES yajl.lib libyajl_s.a
            PATHS ${VCPKG_X64_LIB_DIR}
            ${LINUX_DEFAULT_LOCATIONS}
            NO_DEFAULT_PATH
            )

    find_file(YAJL_LIBRARY
            NAMES yajl.dll libyajl.so
            PATHS ${VCPKG_X64_BIN_DIR}
            ${DEFAULT_LINUX_LOCATIONS}
            NO_DEFAULT_PATH
            REQUIRED
            )

    find_path(YAJL_INCLUDE_DIR
            NAMES yajl/yajl_parse.h
            PATHS ${VCPKG_X64_INCLUDE_DIR}
            NO_DEFAULT_PATH
            )

    # lzma
    find_library(LZMA_STATIC_LIBRARY
            NAMES lzma.lib lzma.a liblzma.a
            PATHS ${VCPKG_X64_LIB_DIR}
            ${DEFAULT_LINUX_LOCATIONS}
            NO_DEFAULT_PATH
            )

    find_file(LZMA_LIBRARY
            NAMES lzma.dll liblzma.so
            PATHS ${VCPKG_X64_BIN_DIR}
            ${DEFAULT_LINUX_LOCATIONS}
            NO_DEFAULT_PATH
            REQUIRED
            )

    find_path(LZMA_INCLUDE_DIR
            NAMES lzma/lzma12.h
            PATHS ${VCPKG_X64_INCLUDE_DIR}
            NO_DEFAULT_PATH
            )

    # zlib
    find_library(ZLIB_STATIC_LIBRARY
            NAMES zlib.lib zlib libz libz.lib libz.a
            PATHS ${VCPKG_X64_LIB_DIR}
            NO_DEFAULT_PATH
            REQUIRED
            )

    find_file(ZLIB_LIBRARY
            NAMES zlib1.dll zlib libz libz.so
            PATHS
            "${VCPKG_X64_BIN_DIR}"
            "/usr/local/lib"
            "/mnt/d/usr/local/lib"
            "/mnt/c/usr/local/lib"
            "/usr/lib/x86_64-linux-gnu"
            "mnt/d/usr/lib/x86_64-linux-gnu"
            "mnt/c/usr/lib/x86_64-linux-gnu"
            NO_DEFAULT_PATH
            REQUIRED
            )

    find_path(ZLIB_INCLUDE_DIR
            NAMES zlib.h
            PATHS ${VCPKG_X64_INCLUDE_DIR}
            NO_DEFAULT_PATH
            )


    # pcre
    find_library(PCRE_STATIC_LIBRARY
            NAMES pcre.lib libpcre.a
            PATHS ${VCPKG_X64_LIB_DIR}
            ${LINUDEFAULT_LINUX_LOCATIONS}
            NO_DEFAULT_PATH
            REQUIRED
            )

    find_file(PCRE_LIBRARY
            NAMES pcre.so pcre.dll pcre.so libpcre.so
            PATHS ${VCPKG_X64_BIN_DIR}
            ${DEFAULT_LINUX_LOCATIONS}
            NO_DEFAULT_PATH
            REQUIRED)

    find_path(PCRE_INCLUDE_DIR
            NAMES pcre.h
            PATHS
            ${VCPKG_X64_INCLUDE_DIR}
            NO_DEFAULT_PATH
            )


    # ICONV
    find_library(ICONV_STATIC_LIBRARY
            NAMES libiconv.lib libiconv.a
            PATHS
            ${VCPKG_X64_LIB_DIR}
            ${DEFAULT_LINUX_LOCATIONS}
            NO_DEFAULT_PATH
            )

    find_file(ICONV_LIBRARY
            NAMES libiconv.dll libiconv.so libiconv.so.2
            PATHS ${VCPKG_X64_BIN_DIR}
            ${DEFAULT_LINUX_LOCATIONS}
            REQUIRED
            )

    find_path(ICONV_INCLUDE_DIR
            NAMES iconv.h
            PATHS ${VCPKG_X64_INCLUDE_DIR}
            /usr/local/include # linux
            /mnt/d/usr/local/include # wsl
            /mnt/c/usr/local/include # wsl
            NO_DEFAULT_PATH
            )

    # Note: on windows these are note actually static libraries,
    # but the *.lib files which contain stubs that need filling with dll
    # at runtime.

    SET(STATIC_LIBRARIES
            "${LIBXML2_STATIC_LIBRARY}"
            #            "${LIBXSLT_STATIC_LIBRARY}"
            "${CURL_STATIC_LIBRARY}"
            "${LIBCHARSET_STATIC_LIBRARY}"
            "${SSL_STATIC_LIBRARY}"
            "${CRYPTO_STATIC_LIBRARY}"
            "${YAJL_STATIC_LIBRARY}"
            "${LZMA_STATIC_LIBRARY}"
            "${ZLIB_STATIC_LIBRARY}"
            "${ICONV_STATIC_LIBRARY}"
            "${PCRE_STATIC_LIBRARY}"
            )
    SET(LIBRARIES
            "${ZLIB_LIBRARY}"
            "${LIBXML2_LIBRARY}"
            "${LIBXSLT_LIBRARY}"
            "${CURL_LIBRARY}"
            "${LIBCHARSET_LIBRARY}"
            "${SSL_LIBRARY}"
            "${CRYPTO_LIBRARY}"
            "${YAJL_LIBRARY}"
            "${LZMA_LIBRARY}"
            "${ICONV_LIBRARY}"
            "${PCRE_LIBRARY}"
            )

    set(INCLUDES
            "${LIBXML2_INCLUDE_DIR}"
            "${LIBXSLT_INCLUDE_DIR}"
            "${CURL_INCLUDE_DIR}"
            "${SSL_INCLUDE_DIR}"
            "${SSL_INCLUDE_DIR}"
            "${YAJL_INCLUDE_DIR}"
            "${LZMA_INCLUDE_DIR}"
            "${ZLIB_INCLUDE_DIR}"
            "${PCRE_INCLUDE_DIR}"
            "${ICONV_INCLUDE_DIR}"
            )

    if (DEBUG_DEPENDENCIES)
        # validation
        foreach (_lib ${LIBRARIES})
            message(STATUS "Shared library: ${_lib} found")
            if (NOT EXISTS "${_lib}")
                message(FATAL_ERROR "${_lib} not found")
            endif ()
        endforeach ()

        message(STATUS " ")

        foreach (_slib ${STATIC_LIBRARIES})
            message(STATUS "Static library: ${_slib} found")
            if (NOT EXISTS "${_slib}")
                message(FATAL_ERROR "${_slib} not found")
            endif ()
        endforeach ()


        message(STATUS " ")

        foreach (_inc ${INCLUDES})
            message(STATUS "Include path: ${_inc} found")
            if (NOT EXISTS "${_inc}")
                message(FATAL_ERROR "${_inc} not found")
            endif ()
        endforeach ()

    endif ()
endmacro()