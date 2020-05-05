
find_package(SWIG REQUIRED)

include(${SWIG_USE_FILE})

set(LIBCOMBINE_CSHARP_BINDING_NATIVE_LIBRARY_NAME "libcombinecs" CACHE STRING
                       "The name of the native library file to generate. This can be changed to avoid conflicts with other applications using another version of the library.")
mark_as_advanced(LIBCOMBINE_CSHARP_BINDING_NATIVE_LIBRARY_NAME)

####################################################################
#
# determine local dependencies, so as to re-swig if one of them changed
#

file(GLOB SWIG_DEPENDENCIES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*.i
  ${CMAKE_CURRENT_SOURCE_DIR}/../swig/*.i
  ${CMAKE_CURRENT_SOURCE_DIR}/../swig/*.h
  )

####################################################################
#
# create correct assembly information file
#
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/AssemblyInfo.cs.in"
  "${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs"
  )

#
# Remove SWIG wrappers if requested
#
if (LIBCOMBINE_REMOVE_WRAPPERS)
  foreach(file
    ${CMAKE_CURRENT_BINARY_DIR}/libcombine_wrap.cpp
  )
    if (EXISTS ${file})
      FILE(REMOVE ${file})
    endif()
  endforeach()
endif(LIBCOMBINE_REMOVE_WRAPPERS)

####################################################################
#
# SWIG C# bindings
#

set(SWIG_EXTRA_FLAGS -DSWIGEXPORT -DLIBSBML_CPP_NAMESPACE_BEGIN -DLIBSBML_CPP_NAMESPACE_END -DLIBSBML_CPP_NAMESPACE_QUALIFIER -DLIBSBML_CPP_NAMESPACE_USE)
if(NOT UNIX)
  set(SWIG_EXTRA_FLAGS ${SWIG_EXTRA_FLAGS} -DSWIGWIN -DSWIG_CSHARP_NO_WSTRING_HELPER )
endif()



file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/csharp-files LIBCOMBINE_CS_FILES)

make_directory(${CMAKE_CURRENT_BINARY_DIR}/csharp-files)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/libcombine_wrap.cpp
         ${CMAKE_CURRENT_BINARY_DIR}/csharp-files/libcombine.cs
    COMMAND "${CMAKE_COMMAND}"
    ARGS  -E remove_directory "${LIBCOMBINE_CS_FILES}"
    COMMAND "${CMAKE_COMMAND}"
    ARGS  -E make_directory "${LIBCOMBINE_CS_FILES}"
    COMMAND "${SWIG_EXECUTABLE}"
    ARGS -I${SWIG_DIR}/csharp
         -I${SWIG_DIR}/std
         -I${CMAKE_CURRENT_SOURCE_DIR}/../swig/
         -I${CMAKE_CURRENT_SOURCE_DIR}/../../
         -I${CMAKE_CURRENT_BINARY_DIR}/../../
         -I${CMAKE_CURRENT_SOURCE_DIR}/../../sedml
         -I${CMAKE_CURRENT_SOURCE_DIR}
         -I${LIBSBML_INCLUDE_DIR}/
       -c++
       -csharp
       -namespace libcombinecs
       -dllimport ${LIBCOMBINE_CSHARP_BINDING_NATIVE_LIBRARY_NAME}
       ${SWIG_EXTRA_ARGS}
       ${SWIG_EXTRA_FLAGS}
         -outdir ${LIBCOMBINE_CS_FILES}
       -o ${CMAKE_CURRENT_BINARY_DIR}/libcombine_wrap.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/../swig/libcombine.i

    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/../swig/libcombine.i
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
            ${SWIG_DEPENDENCIES}
    COMMENT "Swig C# source")

add_custom_target(binding_csharp_swig ALL DEPENDS ${SWIG_DEPENDENCIES})

#
# Determine the csharp installation directory
#
set(CSHAPR_PACKAGE_INSTALL_DIR)
if (UNIX OR CYGWIN)
  set(CSHAPR_PACKAGE_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/mono/libcombinecsP)
else()
  set(CSHAPR_PACKAGE_INSTALL_DIR ${MISC_PREFIX}bindings/csharp)
endif()

####################################################################
#
# Build native library
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../swig)
include_directories(${LIBSBML_INCLUDE_DIR})
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/../../)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR}/../../)
add_definitions(-DLIBCOMBINE_STATIC)
add_library(binding_csharp_native_lib SHARED ${CMAKE_CURRENT_BINARY_DIR}/libcombine_wrap.cpp )
add_dependencies(binding_csharp_native_lib binding_csharp_swig)
if (UNIX)
# if name starts with 'lib' drop the prefix, otherwise we get 'liblibXXX'

set(UNIX_NATIVE_NAME "${LIBCOMBINE_CSHARP_BINDING_NATIVE_LIBRARY_NAME}")
string(LENGTH "${LIBCOMBINE_CSHARP_BINDING_NATIVE_LIBRARY_NAME}" length)
if (${length} GREATER 3)
   string(SUBSTRING "${LIBCOMBINE_CSHARP_BINDING_NATIVE_LIBRARY_NAME}" 0 3 result)
   if ("${result}" STREQUAL "lib")
       math(EXPR length_minus_three "${length} - 3")
       string(SUBSTRING "${LIBCOMBINE_CSHARP_BINDING_NATIVE_LIBRARY_NAME}" 3 ${length_minus_three} UNIX_NATIVE_NAME)
   endif()
endif()
set_target_properties (binding_csharp_native_lib PROPERTIES OUTPUT_NAME "${UNIX_NATIVE_NAME}")
else()
set_target_properties (binding_csharp_native_lib PROPERTIES OUTPUT_NAME ${LIBCOMBINE_CSHARP_BINDING_NATIVE_LIBRARY_NAME})
endif()
target_link_libraries(binding_csharp_native_lib ${LIBCOMBINE_LIBRARY}-static)
install(TARGETS binding_csharp_native_lib
        DESTINATION ${CSHAPR_PACKAGE_INSTALL_DIR}
  )

####################################################################
#
# build managed library
#

add_custom_command(
  OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/libcombinecsP.dll
    ${CMAKE_CURRENT_BINARY_DIR}/libcombinecsP.xml

  COMMAND "${CMAKE_COMMAND}"
  ARGS -DCSHARP_EXTRA_ARGS=\"${CSHARP_EXTRA_ARGS}\"
     -DCSHARP_COMPILER=\"${CSHARP_COMPILER}\"
     -DBIN_DIRECTORY=\"${CMAKE_CURRENT_BINARY_DIR}\"
     -DSRC_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}\"
     -P "${CMAKE_CURRENT_SOURCE_DIR}/compile-native-files.cmake"

  MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/../swig/libcombine.i"
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
      ${CMAKE_CURRENT_SOURCE_DIR}/compile-native-files.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/csharp-files/libcombine.cs
          ${CMAKE_CURRENT_BINARY_DIR}/libcombine_wrap.cpp
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    COMMENT "Build csharp files"
  )

add_custom_target(binding_csharp_managed_lib ALL DEPENDS libcombinecsP.dll)
add_dependencies(binding_csharp_managed_lib binding_csharp_swig)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libcombinecsP.dll DESTINATION ${CSHAPR_PACKAGE_INSTALL_DIR})
