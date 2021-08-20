#Note: googletest is added in the tests cmake lists.

add_subdirectory(zlib)
set(ZLIB_INCLUDE_DIR "$<TARGET_PROPERTY:zlib,INCLUDE_DIRECTORIES>" "${CMAKE_CURRENT_SOURCE_DIR}/zlib")

# iconv
add_subdirectory(iconv)
set(LIBICONV_INCLUDE_DIR "${LIBICONV_INCLUDE_DIR}") # alias for xml2
set(ICONV_INCLUDE_DIR "${LIBICONV_INCLUDE_DIR}") # Alias for iconv


add_subdirectory(libxml2)
add_dependencies(LibXml2 zlibstatic libiconv-static )

set_target_properties(LibXml2 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
#        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libxml2/include>"
        "$<BUILD_INTERFACE:/home/ciaranwelsh/Documents/libOmexMeta/third_party/libxml2/include>"
        )

set(
        LIBXML2_INCLUDE_DIR
        "${CMAKE_CURRENT_SOURCE_DIR}/libxml2/include"
        "${CMAKE_CURRENT_BINARY_DIR}/libxml2/include"
        "${CMAKE_BINARY_DIR}/third_party/libxml2"
)

add_subdirectory(libxslt)
add_dependencies(LibXslt LibXml2)

add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE
        $<BUILD_INTERFACE:${SPDLOG_INCLUDE_DIR}>
        )

install(
        TARGETS spdlog
        EXPORT spdlog
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(
        EXPORT spdlog
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/spdlog"
        NAMESPACE spdlog::
        FILE spdlog.cmake
)