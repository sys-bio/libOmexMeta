macro(SetCrossPlatform name msvc_val linux_val macos_val)

    if (${WIN32})
        set(${name} ${msvc_val})

    elseif (${UNIX})
        set(${name} ${linux_val})

    elseif (${APPLE})
        set(${name} ${macos_val})

    else ()
        message(FATAL_ERROR "Unknown operating system")
    endif ()

endmacro()