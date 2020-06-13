cmake_minimum_required(VERSION 3.15)
project(rasqal)


######################################################################################3
#   dependencies
#
if (NOT EXISTS ${RAPTOR2_INCLUDE_DIR})
    message(FATAL_ERROR "Raptor not found at \"${RAPTOR2_INCLUDE_DIR}\". Please give path to raptor2 include directory")
endif ()

if (NOT EXISTS ${RAPTOR2_STATIC_LIB})
    message(FATAL_ERROR "Raptor static library not found at \"${RAPTOR2_STATIC_LIB}\". Please give path to raptor2 include directory")
endif ()

set(RASQAL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
#FLEX_MIN_VERSION=2.5.19
#FLEX_REC_VERSION=2.5.36

SET(RASQAL_VERSION_MAJOR version_major 0)
SET(RASQAL_VERSION_MINOR version_minor 9)
SET(RASQAL_VERSION_RELEASE version_release 0.9.33)
SET(RASQAL_VERSION_DECIMAL version_decimal 33)

set(LIBSV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libsv)
set(LIBMTWIST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libmtwist)
set(GETOPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/getopt)


######################################################################################3
#   validate some files in rasqal exist
#

if (NOT EXISTS ${RASQAL_SOURCE_DIR}/rasqal_general.c)
    message(FATAL_ERROR "sanity check failed. ${RASQAL_SOURCE_DIR}/rasqal_general.c not found.")
endif ()

add_definitions(-DRASQAL_INTERNAL -DHAVE_CONFIG_H)

######################################################################################3
#   configure files
#

configure_file(src/rasqal_config.h.in src/rasqal_config.h)
configure_file(rasqal-src-config.in rasqal-src-config)
configure_file(rasqal.pc.in rasqal.pc)
configure_file(rasqal.spec.in rasqal.spec)
configure_file(rasqal.rdf.in rasqal.rdf)


######################################################################################3
#   Build rasqal
#


add_subdirectory(src)


######################################################################################3
#   Configuration report
#

message(STATUS "

    RAPTOR2_INCLUDE_DIR         ${RAPTOR2_INCLUDE_DIR}
    RAPTOR2_STATIC_LIB          ${RAPTOR2_STATIC_LIB}
")





























