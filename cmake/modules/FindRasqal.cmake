# - Try to find the Rasqal RDF parsing library (http://librdf.org/rasqal/)
# Once done this will define
#
#  Rasqal_FOUND       - System has Rasqal
#  Rasqal_LIBRARIES   - Rasqal and dependencies
#  Rasqal_INCLUDE_DIR - Include directory for using Rasqal
#  Rasqal_DEFINITIONS - Compiler switches required for using Rasqal
#
#  Capabilities
#       RASQAL_HAVE_TRIG   - Set if rasqal has TRIG

# (c) 2014 J Kyle Medley
# (c) 2007-2011 Sebastian Trueg <trueg@kde.org>
# (c) 2011 Artem Serebriyskiy <v.for.vandal@gmail.com>
# (c) 2011 Michael Jansen <kde@michael-jansen.biz>
#
# Based on FindFontconfig Copyright (c) 2006,2007 Laurent Montel, <montel@kde.org>
#
# Redistribution and use is allowed according to the terms of the BSD license.


include(LibFindMacros)

if ( NOT( RASQAL_INCLUDE_DIR AND RASQAL_LIBRARIES ) OR NOT RASQAL_FOUND )

  include(FindLibraryWithDebug)
  include(MacroEnsureVersion)
  find_package(PkgConfig)

  if ( NOT WIN32 )
    pkg_check_modules(PC_RASQAL QUIET rasqal)
    if ( PC_RASQAL_FOUND )
      set(VRASQAL_FOUND TRUE)
      set(RASQAL_LIBS "")
      set(RASQAL_INCLUDES "")
      foreach(lib ${PC_RASQAL_LIBRARIES})
        message(STATUS "lib ${lib}")
        find_library(RASQAL_LIBRARY_${lib} NAMES ${lib}
          HINTS ${PC_RASQAL_LIBDIR} ${PC_RASQAL_LIBRARY_DIRS})
        message(STATUS "lib2 ${RASQAL_LIBRARY_${lib}}")
        list(APPEND RASQAL_LIBS ${RASQAL_LIBRARY_${lib}})
        if (NOT RASQAL_LIBRARY_${lib}_FOUND)
          set(VRASQAL_FOUND FALSE)
        endif()
      endforeach()
      foreach(path ${PC_RASQAL_INCLUDE_DIRS})
        list(APPEND RASQAL_INCLUDES ${path})
      endforeach()
    else()
      message(SEND_ERROR "No pkg-config info for rasqal")
    endif ()
  endif ()

  mark_as_advanced(RASQAL_INCLUDE_DIR RASQAL_LIBRARIES)

endif () # Check for cached values

mark_as_advanced(RASQAL_VERSION)

set(Rasqal_PROCESS_INCLUDES RASQAL_INCLUDES)
set(Rasqal_PROCESS_LIBS RASQAL_LIBS)
libfind_process(Rasqal)
