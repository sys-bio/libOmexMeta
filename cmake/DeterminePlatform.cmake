
# Note: This file must be included after the Project command
# This content is abstracted into its own cmake file
# because it is needed twice, once for when HAVE_DEPENDECNIES=ON
# and again when HAVE_DEPENDENCIES=OFF
set(PLATFORM)

#message(STATUS "MINGW ${MINGW}")
#message(STATUS "CYGWIN ${CYGWIN}")
#message(STATUS "MSYS ${MSYS}")
#message(STATUS "UNIX ${UNIX}")
#message(STATUS "WIN32 ${WIN32}")
#message(STATUS "APPLE ${APPLE}")

IF (UNIX)
    set(PLATFORM linux)
elseif (WIN32)
    set(PLATFORM windows-msvc)
    if (${MINGW})
        set(PLATFORM windows-mingw)
    elseif (${CYGWIN})
        set(PLATFORM windows-cygwin)
    endif ()
elseif (APPLE)
    set(PLATFORM macos)
elseif (MINGW)
    set(PLATFORM windows-mingw)
elseif (MSYS)
    set(PLATFORM windows-msys)
elseif (CYGWIN)
    set(PLATFORM windows-cygwin)
endif ()

#message(STATUS "PLATFORM ${PLATFORM}")
if(${PLATFORM} STREQUAL "")
    message(FATAL_ERROR "Platform not detected")
endif()