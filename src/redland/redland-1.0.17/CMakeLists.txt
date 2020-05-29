cmake_minimum_required(VERSION 3.15)
project(librdf)


set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIBLTDL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libltdl)

if (NOT EXISTS ${RAPTOR2_INCLUDE_DIR})
    message(WARNING "RAPTOR2_INCLUDE_DIR not found ${RAPTOR2_INCLUDE_DIR}")
endif ()

if (NOT EXISTS ${RAPTOR2_STATIC_LIB})
    message(WARNING "RAPTOR2_STATIC_LIB not found ${RAPTOR2_STATIC_LIB}")
endif ()

if (NOT EXISTS ${RASQAL_INCLUDE_DIR})
    message(WARNING "RASQAL_INCLUDE_DIR not found ${RASQAL_INCLUDE_DIR}")
endif ()

if (NOT EXISTS ${RASQAL_STATIC_LIB})
    message(WARNING "RASQAL_STATIC_LIB not found ${RASQAL_STATIC_LIB}")
endif ()

set(PKGDATADIR $ENV{HOME}/.librdf)
file(MAKE_DIRECTORY ${PKGDATADIR})


find_library(LIBPQ_STATIC_LIBRARY
        NAMES pq.a libpq.a pq libpq
        )

if (NOT LIBPQ_STATIC_LIBRARY)
    message(WARNING "libpq not found so skipping these source files. Install with sudo apt install libpq-dev")
endif ()


find_path(LIBPQ_INCLUDE_DIR
        NAMES libpq-fe.h
        PATHS /usr/include/postgresql
        )

if (NOT LIBPQ_INCLUDE_DIR)
    message(WARNING "libpq-fe.h not found. Install with sudo apt install libpq-dev")
endif ()






message(STATUS ${LIBPQ_STATIC_LIBRARY})

add_definitions(-DHAVE_CONFIG_H -DLIBRDF_INTERNAL
        -DREDLAND_MODULE_PATH
        #        -DPKGDATADIR
        -DPKGDATADIR ${PKGDATADIR}
        )

add_subdirectory(src)


message(STATUS "
##############################################################
# configuration summary                                      #
##############################################################

    CMAKE_CURRENT_SOURCE_DIR          ${CMAKE_CURRENT_SOURCE_DIR}
    RAPTOR2_INCLUDE_DIR               ${RAPTOR2_INCLUDE_DIR}
    RAPTOR2_STATIC_LIB                ${RAPTOR2_STATIC_LIB}
    RASQAL_INCLUDE_DIR                ${RASQAL_INCLUDE_DIR}
    RASQAL_STATIC_LIB                 ${RASQAL_STATIC_LIB}
    PKGDATADIR                        ${PKGDATADIR}
    LIBPQ_STATIC_LIBRARY              ${LIBPQ_STATIC_LIBRARY}
    LIBPQ_INCLUDE_DIR                 ${LIBPQ_INCLUDE_DIR}

")



































