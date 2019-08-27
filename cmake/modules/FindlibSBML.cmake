# - Try to find libSBML
# Once done, this will define
#
#  libSBML_FOUND - system has libSBML
#  libSBML_INCLUDE_DIRS - the libSBML include directories
#  libSBML_LIBRARIES - link these to use libSBML

include(LibFindMacros)

find_package(sbml CONFIG)

if (sbml_FOUND)
  get_target_property(libSBML_LIBRARY sbml LOCATION)
  get_target_property(libSBML_INCLUDE_DIRS sbml INTERFACE_INCLUDE_DIRECTORIES)
  set(libSBML_FOUND TRUE)
else()
  find_package(PkgConfig REQUIRED)

  pkg_check_modules(libSBML_PC REQUIRED libsbml)
  message(STATUS "libSBML_PC_LIBRARY_DIRS ${libSBML_PC_LIBRARY_DIRS}")
  message(STATUS "libSBML_PC_LIBRARIES ${libSBML_PC_LIBRARIES}")

  foreach(lib ${libSBML_PC_LIBRARIES})
    message(STATUS "libsbml lib: libSBML_${lib}_LIBRARY")
    find_library(libSBML_${lib}_LIBRARY
      NAMES ${lib}
      PATHS ${libSBML_PC_LIBRARY_DIRS}
    )
    list(APPEND libSBML_LIBRARIES_LIST ${libSBML_${lib}_LIBRARY})
  endforeach()

  set(libSBML_PROCESS_INCLUDES libSBML_PC_INCLUDE_DIRS)
  set(libSBML_PROCESS_LIBS libSBML_LIBRARIES_LIST)
  libfind_process(libSBML)

  add_library(sbml SHARED IMPORTED)
  set_property(TARGET sbml PROPERTY IMPORTED_LOCATION ${libSBML_sbml_LIBRARY})
  set(libSBML_LIBRARY ${libSBML_sbml_LIBRARY})
endif()
