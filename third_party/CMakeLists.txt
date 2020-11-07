#Note: googletest is added in the tests cmake lists.

add_subdirectory(zlib)
set(ZLIB_INCLUDE_DIR "$<TARGET_PROPERTY:zlib,INCLUDE_DIRECTORIES>" "${CMAKE_CURRENT_SOURCE_DIR}/zlib")

# iconv
add_subdirectory(iconv)
set(LIBICONV_INCLUDE_DIR "${LIBICONV_INCLUDE_DIR}")


add_subdirectory(libxml2)
add_dependencies(LibXml2 zlibstatic libiconv-static )

set_target_properties(LibXml2 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES)

set(LIBXML2_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libxml2/include")

add_subdirectory(libxslt)
add_dependencies(LibXslt LibXml2)
