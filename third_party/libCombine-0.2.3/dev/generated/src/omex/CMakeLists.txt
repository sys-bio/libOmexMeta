###############################################################################
#
# Description       : CMake build script for libCombine
# 
###############################################################################


include(CheckLibraryExists)
check_library_exists(m sqrt "" HAVE_LIBM)

# generate configuration for this system
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/common/libcombine-config-common.h.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/common/libcombine-config-common.h"
  )

# Replace: @PACKAGE_VERSION@ and @LIBCOMBINE_VERSION_NUMERIC@
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/common/libcombine-version.h.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/common/libcombine-version.h"
  )

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/common/libcombine-namespace.h.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/common/libcombine-namespace.h"
  )
  

###############################################################################
#
# mark header files for installation
#
foreach(dir annotation common compress conversion extension math units util validator xml  )

  file(GLOB header_files "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.h")
  install(FILES ${header_files} DESTINATION include/omex/${dir})

endforeach(dir)

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${files} DESTINATION include/omex)

# install generated headers
install(FILES 
       "${CMAKE_CURRENT_BINARY_DIR}/common/libcombine-version.h"
       "${CMAKE_CURRENT_BINARY_DIR}/common/libcombine-config-common.h"
       "${CMAKE_CURRENT_BINARY_DIR}/common/libcombine-namespace.h"
        DESTINATION include/omex/common)

###############################################################################
#
# specify include directories
#
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(BEFORE ${LIBSBML_INCLUDE_DIR})
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR}/..)

if (EXTRA_DEFS)
add_definitions(${EXTRA_DEFS})
endif()

###############################################################################
#
# Find all sources
#

foreach (directory common omex )

  set(dir ${directory})

  if ("${directory}" STREQUAL "omex")
    set(dir ".")
  endif()


  file(GLOB temp
      ${dir}/*.cpp
      ${dir}/*.c
      ${dir}/*.h)

  # create source group for IDEs
  source_group(${directory} FILES ${temp})

  # add to libcombine sources
  set(LIBCOMBINE_SOURCES ${LIBCOMBINE_SOURCES} ${temp})

endforeach()

###############################################################################
#
# this is a directory level operation!
#
if (MSVC)
if (WITH_STATIC_RUNTIME)
  foreach(flag_var
    CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
    CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
    CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
    CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)

    if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif(${flag_var} MATCHES "/MD")


  endforeach(flag_var)
  add_definitions( -D_MT)
endif(WITH_STATIC_RUNTIME)
endif(MSVC)

###############################################################################
#
# Build library
#

if (NOT LIBCOMBINE_SKIP_SHARED_LIBRARY)

add_library (${LIBCOMBINE_LIBRARY} SHARED ${LIBCOMBINE_SOURCES} )

if (LIBCOMBINE_SHARED_VERSION)
  set_target_properties(${LIBCOMBINE_LIBRARY} PROPERTIES COMPILE_DEFINITIONS "LIBCOMBINE_EXPORTS=1")
  set_target_properties(${LIBCOMBINE_LIBRARY} PROPERTIES
                      SOVERSION ${LIBCOMBINE_VERSION_MAJOR}
                      VERSION ${LIBCOMBINE_VERSION_MAJOR}.${LIBCOMBINE_VERSION_MINOR}.${LIBCOMBINE_VERSION_PATCH})
endif()

target_link_libraries(${LIBCOMBINE_LIBRARY} ${LIBSBML_LIBRARY}  ${EXTRA_LIBS})

INSTALL(TARGETS ${LIBCOMBINE_LIBRARY}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

endif()

add_library (${LIBCOMBINE_LIBRARY}-static STATIC ${LIBCOMBINE_SOURCES} )
if (WIN32 AND NOT CYGWIN)
  # don't decorate static library 
  set_target_properties(${LIBCOMBINE_LIBRARY}-static PROPERTIES COMPILE_DEFINITIONS "LIBCOMBINE_STATIC=1")
endif(WIN32 AND NOT CYGWIN)

target_link_libraries(${LIBCOMBINE_LIBRARY}-static ${LIBSBML_LIBRARY}  ${EXTRA_LIBS})

INSTALL(TARGETS ${LIBCOMBINE_LIBRARY}-static
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
