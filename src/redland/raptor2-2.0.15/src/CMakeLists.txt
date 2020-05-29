# raptor/src/CMakeLists.txt
#
# Original listfile by Daniel Richard G. <skunk@iSKUNK.ORG>
# This file is in the public domain.
#


##################################################################################
# set source variables
#

# rdfa
if (RAPTOR_PARSER_RDFA)
    include_directories(BEFORE ${CMAKE_SOURCE_DIR}/librdfa)
endif (RAPTOR_PARSER_RDFA)

# rdf/xml
if (RAPTOR_PARSER_RDFXML)
    set(raptor_parser_rdfxml_sources raptor_rdfxml.c)
    set(raptor_libxml_libs ${LIBXML2_STATIC_LIBRARY})
endif (RAPTOR_PARSER_RDFXML)

# ntripples
if (RAPTOR_PARSER_NTRIPLES OR RAPTOR_PARSER_NQUADS)
    set(raptor_parser_ntriples_nquads_sources ntriples_parse.c)
endif (RAPTOR_PARSER_NTRIPLES OR RAPTOR_PARSER_NQUADS)

# turtle
if (RAPTOR_PARSER_TURTLE OR RAPTOR_PARSER_TRIG)
    set(raptor_parser_turtle_trig_sources
            turtle_common.h
            turtle_lexer.c
            turtle_lexer.h
            turtle_parser.c
            turtle_parser.h
            )
endif (RAPTOR_PARSER_TURTLE OR RAPTOR_PARSER_TRIG)

# rss
if (RAPTOR_PARSER_RSS OR RAPTOR_SERIALIZER_RSS_1_0)
    set(raptor_rss_common_sources raptor_rss_common.c raptor_rss.h)
endif (RAPTOR_PARSER_RSS OR RAPTOR_SERIALIZER_RSS_1_0)

if (RAPTOR_PARSER_RSS)
    set(raptor_parser_rss_sources raptor_rss.c)
    set(raptor_libxml_libs ${LIBXML2_STATIC_LIBRARY})
endif (RAPTOR_PARSER_RSS)

# GRDL
if (RAPTOR_PARSER_GRDDL)
    set(raptor_parser_grddl_sources raptor_grddl.c)
    set(raptor_libxml_libs ${LIBXML2_STATIC_LIBRARY})
    set(raptor_libxslt_libs ${LIBXSLT_STATIC_LIBRARY})
endif (RAPTOR_PARSER_GRDDL)

# parser guess
if (RAPTOR_PARSER_GUESS)
    set(raptor_parser_guess_sources raptor_guess.c)
endif (RAPTOR_PARSER_GUESS)

# parser rdfa
if (RAPTOR_PARSER_RDFA)
    set(raptor_parser_rdfa_sources raptor_librdfa.c)
endif (RAPTOR_PARSER_RDFA)

# json
if (RAPTOR_PARSER_JSON)
    set(raptor_parser_json_sources raptor_json.c)
endif (RAPTOR_PARSER_JSON)

# rdf/xml serializer
if (RAPTOR_SERIALIZER_RDFXML)
    set(raptor_serializer_rdfxml_sources raptor_serialize_rdfxml.c)
endif (RAPTOR_SERIALIZER_RDFXML)

# ntriples serialiser
if (RAPTOR_SERIALIZER_NTRIPLES OR RAPTOR_SERIALIZER_NQUADS)
    set(raptor_serializer_ntriples_nquads_sources raptor_serialize_ntriples.c)
endif (RAPTOR_SERIALIZER_NTRIPLES OR RAPTOR_SERIALIZER_NQUADS)


if (RAPTOR_SERIALIZER_RDFXML_ABBREV OR RAPTOR_SERIALIZER_TURTLE)
    set(raptor_serializer_abbrev_sources raptor_abbrev.c)
endif (RAPTOR_SERIALIZER_RDFXML_ABBREV OR RAPTOR_SERIALIZER_TURTLE)


if (RAPTOR_SERIALIZER_RDFXML_ABBREV)
    set(raptor_serializer_rdfxml_abbrev_sources raptor_serialize_rdfxmla.c)
endif (RAPTOR_SERIALIZER_RDFXML_ABBREV)


if (RAPTOR_SERIALIZER_TURTLE)
    set(raptor_serializer_turtle_sources raptor_serialize_turtle.c)
endif (RAPTOR_SERIALIZER_TURTLE)


if (RAPTOR_SERIALIZER_RSS_1_0)
    set(raptor_serializer_rss_1_0_sources raptor_serialize_rss.c)
endif (RAPTOR_SERIALIZER_RSS_1_0)


if (RAPTOR_SERIALIZER_DOT)
    set(raptor_serializer_dot_sources raptor_serialize_dot.c)
endif (RAPTOR_SERIALIZER_DOT)


if (RAPTOR_SERIALIZER_HTML)
    set(raptor_serializer_html_sources raptor_serialize_html.c)
endif (RAPTOR_SERIALIZER_HTML)


if (RAPTOR_SERIALIZER_JSON)
    set(raptor_serializer_json_sources raptor_serialize_json.c)
    set(raptor_yajl_libs ${YAJL_LIBRARIES})
endif (RAPTOR_SERIALIZER_JSON)


if (RAPTOR_WWW STREQUAL "curl")
    set(raptor_www_sources raptor_www_curl.c)
    set(raptor_www_libs ${CURL_STATIC_LIBRARY})
elseif (RAPTOR_WWW STREQUAL "fetch")
    set(raptor_www_sources raptor_www_libfetch.c)
    #set(raptor_www_libs ${FETCH_LIBRARIES})
elseif (RAPTOR_WWW STREQUAL "xml")
    set(raptor_www_sources raptor_www_libxml.c)
    set(raptor_www_libs ${LIBXML2_STATIC_LIBRARY})
endif (RAPTOR_WWW STREQUAL "curl")

if (RAPTOR_XML STREQUAL "libxml")
    set(raptor_libxml_sources raptor_libxml.c)
    set(raptor_libxml_libs ${LIBXML2_STATIC_LIBRARY})
endif (RAPTOR_XML STREQUAL "libxml")

if (RAPTOR_PARSER_RDFA)
    set(raptor_librdfa_sources
            ${CMAKE_SOURCE_DIR}/librdfa/context.c
            ${CMAKE_SOURCE_DIR}/librdfa/curie.c
            ${CMAKE_SOURCE_DIR}/librdfa/iri.c
            ${CMAKE_SOURCE_DIR}/librdfa/language.c
            ${CMAKE_SOURCE_DIR}/librdfa/lists.c
            ${CMAKE_SOURCE_DIR}/librdfa/namespace.c
            ${CMAKE_SOURCE_DIR}/librdfa/rdfa.c
            ${CMAKE_SOURCE_DIR}/librdfa/rdfa_utils.c
            ${CMAKE_SOURCE_DIR}/librdfa/strtok_r.c
            ${CMAKE_SOURCE_DIR}/librdfa/subject.c
            ${CMAKE_SOURCE_DIR}/librdfa/triple.c
            ${CMAKE_SOURCE_DIR}/librdfa/rdfa.h
            ${CMAKE_SOURCE_DIR}/librdfa/rdfa_utils.h
            ${CMAKE_SOURCE_DIR}/librdfa/strtok_r.h
            )
endif (RAPTOR_PARSER_RDFA)

if (NOT HAVE_STRCASECMP AND NOT HAVE_STRICMP)
    set(raptor_strcasecmp_sources strcasecmp.c)
endif (NOT HAVE_STRCASECMP AND NOT HAVE_STRICMP)

if (RAPTOR_PARSEDATE)
    set(raptor_parsedate_sources parsedate.c)
endif (RAPTOR_PARSEDATE)

#######################################################################################
# Build the raptor2 target
#

# configure the *.in files

configure_file(raptor_config_cmake.h.in raptor_config.h @ONLY)

add_definitions(-DHAVE_CONFIG_H)

configure_file(raptor2.h.in raptor2.h @ONLY)

add_library(raptor2
        raptor_avltree.c
        raptor_concepts.c
        raptor_general.c
        raptor_iostream.c
        raptor_json_writer.c
        raptor_locator.c
        raptor_log.c
        raptor_memstr.c
        raptor_namespace.c
        raptor_option.c
        raptor_parse.c
        raptor_qname.c
        raptor_rfc2396.c
        raptor_sax2.c
        raptor_sequence.c
        raptor_serialize.c
        raptor_set.c
        raptor_statement.c
        raptor_stringbuffer.c
        raptor_syntax_description.c
        raptor_term.c
        raptor_turtle_writer.c
        raptor_unicode.c
        raptor_uri.c
        raptor_www.c
        raptor_xml.c
        raptor_xml_writer.c
        snprintf.c
        turtle_common.c

        # added by ciaran welsh
        # todo figure out whether these sources are actually needed?
        #  siince I added them myself
        #        raptor2.h
        sort_r.c
        sort_r.h
        ssort.h
        raptor_ntriples.c
        raptor_escaped.c
        raptor_www_libxml.c
        raptor_www_curl.c

        ${raptor_parser_rdfxml_sources}
        ${raptor_parser_ntriples_nquads_sources}
        ${raptor_parser_turtle_trig_sources}
        ${raptor_rss_common_sources}
        ${raptor_parser_rss_sources}
        ${raptor_parser_grddl_sources}
        ${raptor_parser_guess_sources}
        ${raptor_parser_rdfa_sources}
        ${raptor_parser_json_sources}
        ${raptor_serializer_rdfxml_sources}
        ${raptor_serializer_ntriples_nquads_sources}
        ${raptor_serializer_abbrev_sources}
        ${raptor_serializer_rdfxml_abbrev_sources}
        ${raptor_serializer_turtle_sources}
        ${raptor_serializer_rss_1_0_sources}
        ${raptor_serializer_dot_sources}
        ${raptor_serializer_html_sources}
        ${raptor_serializer_json_sources}
        ${raptor_www_sources}
        ${raptor_libxml_sources}
        ${raptor_librdfa_sources}
        ${raptor_strcasecmp_sources}
        ${raptor_parsedate_sources}
        )

target_link_libraries(raptor2 PUBLIC
        ${raptor_libxslt_libs}
        ${raptor_libxml_libs}
        ${raptor_yajl_libs}
        ${raptor_www_libs}
        iconv
        xml2
        xslt
        z
        lzma
        c
        pthread
        gss
        m
        yajl
        # These and others are needed for WWW support. These are hard to find/install so skip
        #        curl
        #        ssl
        #        crypto
        #        dl
        idn2
        #        nghttp2

        #        -lbcrypt -lcrypt32 -lcrypto \ # from https://github.com/curl/curl/issues/2516
        #-lcurl -lgdi32 -lnghttp2 -lssh2 -lssl -lwldap32 -lws2_32 -lz
        ${CMAKE_DL_LIBS} # defines libdl libraries
        )

set(LIBXML2_STATIC_LIBRARY ${LIBXML2_STATIC_LIBRARY})
set(LIBXML2_INCLUDE_DIRS ${LIBXML2_INCLUDE_DIRS})
target_include_directories(raptor2 PUBLIC ${LIBXML2_INCLUDE_DIRS})

set_target_properties(
        raptor2 PROPERTIES COMPILE_DEFINITIONS "LIBRDFA_IN_RAPTOR;RAPTOR_INTERNAL;${LIBXML2_DEFINITIONS};${LIBXSLT_DEFINITIONS}"
)
set_target_properties(raptor2 PROPERTIES PUBLIC_HEADER "raptor2.h")

#######################################################################################
# Build some raptor2 tests to ensure each part of raptor builds
#


#turtle_lexer_test
add_executable(turtle_lexer_test turtle_lexer.c)
add_dependencies(turtle_lexer_test raptor2)
target_link_libraries(turtle_lexer_test PRIVATE raptor2)
add_dependencies(turtle_lexer_test raptor2)


# This currently cannot be built on Windows with DLL linkage

#turtle_parser_test
add_executable(turtle_parser_test turtle_parser.c)
add_dependencies(turtle_parser_test raptor2)
target_link_libraries(turtle_parser_test PRIVATE raptor2)
set_target_properties(
        turtle_parser_test
        PROPERTIES
        COMPILE_DEFINITIONS "RAPTOR_INTERNAL;STANDALONE"
)


#raptor_parse_test
add_executable(raptor_parse_test raptor_parse.c)
add_dependencies(raptor_parse_test raptor2)
target_link_libraries(raptor_parse_test PRIVATE
        raptor2
        ${LIBM_STATIC_LIBRARY}
        lzma
        )
target_include_directories(raptor_parse_test PRIVATE raptor2
        ${MATH_INCLUDE_DIRS}
        )
add_test(raptor_parse_test raptor_parse_test)


#raptor_rfc2396_test
add_executable(raptor_rfc2396_test raptor_rfc2396.c)
add_dependencies(raptor_rfc2396_test raptor2)
target_link_libraries(raptor_rfc2396_test PRIVATE raptor2)
add_test(raptor_rfc2396_test raptor_rfc2396_test)


#raptor_uri_test
add_executable(raptor_uri_test raptor_uri.c)
add_dependencies(raptor_uri_test raptor2)
target_link_libraries(raptor_uri_test PRIVATE
        raptor2
        ${LIBXML2_STATIC_LIBRARY}
        m
        )
target_include_directories(raptor_uri_test PRIVATE
        ${LIBXML2_INCLUDE_DIRS}
        )
add_test(raptor_uri_test raptor_uri_test)


#raptor_namespace_test
add_executable(raptor_namespace_test raptor_namespace.c)
add_dependencies(raptor_namespace_test raptor2)
target_link_libraries(raptor_namespace_test PRIVATE raptor2)
target_include_directories(raptor_namespace_test PRIVATE raptor2)

add_test(raptor_namespace_test raptor_namespace_test)


#strcasecmp_test
add_executable(strcasecmp_test strcasecmp.c)
add_dependencies(strcasecmp_test raptor2)
target_link_libraries(strcasecmp_test PRIVATE raptor2)
add_test(strcasecmp_test strcasecmp_test)


#raptor_www_test
add_executable(raptor_www_test raptor_www_test.c)
add_dependencies(raptor_www_test raptor2)
target_link_libraries(raptor_www_test PRIVATE raptor2)
add_test(raptor_www_test raptor_www_test)


#raptor_sequence_test
add_executable(raptor_sequence_test raptor_sequence.c)
add_dependencies(raptor_sequence_test raptor2)
target_link_libraries(raptor_sequence_test PRIVATE raptor2)
add_test(raptor_sequence_test raptor_sequence_test)


#raptor_stringbuffer_test
add_executable(raptor_stringbuffer_test raptor_stringbuffer.c)
add_dependencies(raptor_stringbuffer_test raptor2)
target_link_libraries(raptor_stringbuffer_test PRIVATE raptor2)
add_test(raptor_stringbuffer_test raptor_stringbuffer_test)


#raptor_iostream_test
add_executable(raptor_iostream_test raptor_iostream.c)
add_dependencies(raptor_iostream_test raptor2)
target_link_libraries(raptor_iostream_test PRIVATE raptor2)
add_test(raptor_iostream_test raptor_iostream_test)


#raptor_xml_writer_test
add_executable(raptor_xml_writer_test raptor_xml_writer.c)
add_dependencies(raptor_xml_writer_test raptor2)
target_link_libraries(raptor_xml_writer_test PRIVATE raptor2)
target_include_directories(raptor_xml_writer_test PRIVATE)
add_test(raptor_xml_writer_test raptor_xml_writer_test)


#raptor_turtle_writer_test
add_executable(raptor_turtle_writer_test raptor_turtle_writer.c)
add_dependencies(raptor_turtle_writer_test raptor2)
target_link_libraries(raptor_turtle_writer_test PRIVATE raptor2)
add_test(raptor_turtle_writer_test raptor_turtle_writer_test)


#raptor_avltree_test
add_executable(raptor_avltree_test raptor_avltree.c)
add_dependencies(raptor_avltree_test raptor2)
target_link_libraries(raptor_avltree_test PRIVATE raptor2)
add_test(raptor_avltree_test raptor_avltree_test)


#raptor_term_test
add_executable(raptor_term_test raptor_term.c)
add_dependencies(raptor_term_test raptor2)
target_link_libraries(raptor_term_test PRIVATE raptor2)
add_test(raptor_term_test raptor_term_test)


#raptor_permute_test
add_executable(raptor_permute_test raptor_permute_test.c)
add_dependencies(raptor_permute_test raptor2)
target_link_libraries(raptor_permute_test PRIVATE raptor2)
add_test(raptor_permute_test raptor_permute_test)

set_target_properties(
        turtle_lexer_test
        #        turtle_parser_test
        raptor_parse_test
        raptor_rfc2396_test
        raptor_uri_test
        raptor_namespace_test
        strcasecmp_test
        raptor_www_test
        raptor_sequence_test
        raptor_stringbuffer_test
        raptor_iostream_test
        raptor_xml_writer_test
        raptor_turtle_writer_test
        raptor_avltree_test
        raptor_term_test
        raptor_permute_test
        PROPERTIES
        COMPILE_DEFINITIONS "RAPTOR_INTERNAL;STANDALONE"
)

if (RAPTOR_PARSER_RDFXML)

    #raptor_set_test
    add_executable(raptor_set_test raptor_set.c)
    add_dependencies(raptor_set_test raptor2)
    target_link_libraries(raptor_set_test PRIVATE raptor2
            ${ZLIB_STATIC_LIBRARY}
            )
    target_include_directories(raptor_set_test PRIVATE
            ${ZLIB_INCLUDE_DIRS}
            )
    add_test(raptor_set_test raptor_set_test)


    #raptor_xml_test
    add_executable(raptor_xml_test raptor_xml.c)
    add_dependencies(raptor_xml_test raptor2)
    target_link_libraries(raptor_xml_test PRIVATE raptor2)
    add_test(raptor_xml_test raptor_xml_test)

    set_target_properties(
            raptor_set_test
            raptor_xml_test
            PROPERTIES
            COMPILE_DEFINITIONS "RAPTOR_INTERNAL;STANDALONE"
    )
endif (RAPTOR_PARSER_RDFXML)

# Generate pkg-config metadata file
#
FILE(WRITE ${CMAKE_CURRENT_BINARY_DIR}/raptor2.pc
        "prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=\${prefix}
libdir=\${exec_prefix}/lib
includedir=\${prefix}/include/raptor2

Name: Raptor RDF Parsing Library
Description: RDF Parser Toolkit Library
Version: ${VERSION}
Libs: -L\${libdir} -lraptor2
Libs.private: ${raptor_libxslt_libs} ${raptor_libxml_libs}
Cflags: -I\${includedir}
")


INSTALL(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/raptor2.pc
        DESTINATION lib/pkgconfig
        )

INSTALL(
        TARGETS raptor2
        EXPORT Raptor2Config
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

INSTALL(EXPORT Raptor2Config DESTINATION lib/cmake)

# end raptor/src/CMakeLists.txt


message(STATUS "

    Raptor Variables
        raptor_parser_rdfxml_sources                ${raptor_parser_rdfxml_sources}
        raptor_libxml_libs                          ${raptor_libxml_libs}
        raptor_parser_ntriples_nquads_sources       ${raptor_parser_ntriples_nquads_sources}
        raptor_parser_turtle_trig_sources           ${raptor_parser_turtle_trig_sources}
        raptor_rss_common_sources                   ${raptor_rss_common_sources}
        raptor_parser_rss_sources                   ${raptor_parser_rss_sources}
        raptor_libxml_libs                          ${raptor_libxml_libs}
        raptor_parser_grddl_sources                 ${raptor_parser_grddl_sources}
        raptor_libxml_libs                          ${raptor_libxml_libs}
        raptor_libxslt_libs                         ${raptor_libxslt_libs}
        raptor_parser_guess_sources                 ${raptor_parser_guess_sources}
        raptor_parser_rdfa_sources                  ${raptor_parser_rdfa_sources}
        raptor_parser_json_sources                  ${raptor_parser_json_sources}
        raptor_serializer_rdfxml_sources            ${raptor_serializer_rdfxml_sources}
        raptor_serializer_ntriples_nquads_sources   ${raptor_serializer_ntriples_nquads_sources}
        raptor_serializer_abbrev_sources            ${raptor_serializer_abbrev_sources}
        raptor_serializer_rdfxml_abbrev_sources     ${raptor_serializer_rdfxml_abbrev_sources}
        raptor_serializer_turtle_sources            ${raptor_serializer_turtle_sources}
        raptor_serializer_rss_1_0_sources           ${raptor_serializer_rss_1_0_sources}
        raptor_serializer_dot_sources               ${raptor_serializer_dot_sources}
        raptor_serializer_html_sources              ${raptor_serializer_html_sources}
        raptor_serializer_json_sources              ${raptor_serializer_json_sources}
        raptor_yajl_libs                            ${raptor_yajl_libs}
        raptor_www_sources                          ${raptor_www_sources}
        raptor_www_libs                             ${raptor_www_libs}
        RAPTOR_WWW                                  ${RAPTOR_WWW}
        raptor_www_sources                          ${raptor_www_sources}
        RAPTOR_WWW                                  ${RAPTOR_WWW}
        raptor_www_sources                          ${raptor_www_sources}
        raptor_libxml_sources                       ${raptor_libxml_sources}
        raptor_libxml_libs                          ${raptor_libxml_libs}
        raptor_librdfa_sources                      ${raptor_librdfa_sources}

        LIBXML2_DEFINITIONS                         ${LIBXML2_DEFINITIONS}
        LIBXSLT_DEFINITIONS                         ${LIBXSLT_DEFINITIONS}
")
