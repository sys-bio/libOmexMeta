add_subdirectory(zlib)
set(ZLIB_INCLUDE_DIR "$<TARGET_PROPERTY:zlib,INCLUDE_DIRECTORIES>" "${CMAKE_CURRENT_SOURCE_DIR}/zlib")

# iconv
add_subdirectory(iconv)
set(LIBICONV_INCLUDE_DIR "${LIBICONV_INCLUDE_DIR}" "$<TARGET_PROPERTY:libiconv-static,INCLUDE_DIRECTORIES>")


add_subdirectory(libxml2)

add_subdirectory(libxslt)