function(SetCrossPlatform name msvc_val linux_val macos_val)
    #macro(SetCrossPlatform VAR name MSVC msvc_val LINUX linux_val MACOS macos_val)

    MESSAGE(STATUS "PLATFORM ${PLATFORM}")
    MESSAGE(STATUS "name ${name}")
    MESSAGE(STATUS "msvc_val ${msvc_val}")

    if (PLATFORM STREQUAL "windows-msvc")
        set(name_ ${msvc_val})
    elseif (PLATFORM STREQUAL "linux")
        set(name_ ${linux_val})
    elseif (PLATFORM STREQUAL "macos")
        set(name_ ${macos_val})
    endif ()
    MESSAGE(STATUS "name ${name}")

    set(name ${name_} PARENT_SCOPE)

endfunction()