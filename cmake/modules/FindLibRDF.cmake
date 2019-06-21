# - Try to find the LibRDF RDF parsing library (http://librdf.org/librdf/)
# Once done this will define
#
#  LibRDF_FOUND       - System has LibRDF
#  LibRDF_LIBRARIES   - LibRDF and dependencies
#  LibRDF_INCLUDE_DIR - Include directory for using LibRDF
#  LibRDF_DEFINITIONS - Compiler switches required for using LibRDF
#
#  Capabilities
#       LIBRDF_HAVE_TRIG   - Set if librdf has TRIG

# (c) 2014 J Kyle Medley
# (c) 2007-2011 Sebastian Trueg <trueg@kde.org>
# (c) 2011 Artem Serebriyskiy <v.for.vandal@gmail.com>
# (c) 2011 Michael Jansen <kde@michael-jansen.biz>
#
# Based on FindFontconfig Copyright (c) 2006,2007 Laurent Montel, <montel@kde.org>
#
# Redistribution and use is allowed according to the terms of the BSD license.


include(LibFindMacros)

if ( NOT( LIBRDF_INCLUDE_DIR AND LIBRDF_LIBRARIES ) OR NOT LIBRDF_FOUND )

  include(FindLibraryWithDebug)
  include(MacroEnsureVersion)
  find_package(PkgConfig)

  if ( NOT WIN32 )
    pkg_check_modules(PC_LIBRDF QUIET redland)
    if ( PC_LIBRDF_FOUND )
      set(VLIBRDF_FOUND TRUE)
      set(LIBRDF_LIBS "")
      set(LIBRDF_INCLUDES "")
      foreach(lib ${PC_LIBRDF_LIBRARIES})
        find_library(LIBRDF_LIBRARY_${lib} NAMES ${lib}
          HINTS ${PC_LIBRDF_LIBDIR} ${PC_LIBRDF_LIBRARY_DIRS})
        list(APPEND LIBRDF_LIBS ${LIBRDF_LIBRARY_${lib}})
        if (NOT LIBRDF_LIBRARY_${lib}_FOUND)
          set(VLIBRDF_FOUND FALSE)
        endif()
      endforeach()
      foreach(path ${PC_LIBRDF_INCLUDE_DIRS})
        list(APPEND LIBRDF_INCLUDES ${path})
      endforeach()
    else()
      message(SEND_ERROR "No pkg-config info for librdf")
    endif ()
  endif ()

  mark_as_advanced(LIBRDF_INCLUDE_DIR LIBRDF_LIBRARIES)

endif () # Check for cached values

mark_as_advanced(LIBRDF_VERSION)

set(LibRDF_PROCESS_INCLUDES LIBRDF_INCLUDES)
set(LibRDF_PROCESS_LIBS LIBRDF_LIBS)
libfind_process(LibRDF)
