
# Note: This file must be included after the Project command
# This content is abstracted into its own cmake file
# because it is needed twice, once for when HAVE_DEPENDECNIES=ON
# and again when HAVE_DEPENDENCIES=OFF
function(DeterminePlatform)

    message(STATUS "MINGW ${MINGW}")
    message(STATUS "CYGWIN ${CYGWIN}")
    message(STATUS "MSYS ${MSYS}")
    message(STATUS "UNIX ${UNIX}")
    message(STATUS "WIN32 ${WIN32}")
    message(STATUS "APPLE ${APPLE}")

    IF (UNIX)
        set(PLATFORM_ linux)
    elseif (WIN32)
        set(PLATFORM_ windows-msvc)
        if (${MINGW})
            set(PLATFORM_ windows-mingw)
        elseif (${CYGWIN})
            set(PLATFORM_ windows-cygwin)
        endif ()
    elseif (APPLE)
        set(PLATFORM_ macos)
    elseif (MINGW)
        set(PLATFORM_ windows-mingw)
    elseif (MSYS)
        set(PLATFORM_ windows-msys)
    elseif (CYGWIN)
        set(PLATFORM_ windows-cygwin)
    endif ()

    message(STATUS "PLATFORM_ ${PLATFORM_}")
    if (${PLATFORM_} STREQUAL "")
        message(FATAL_ERROR "PLATFORM_ not detected")
    endif ()

    SET(PLATFORM ${PLATFORM_} PARENT_SCOPE)

endfunction()

