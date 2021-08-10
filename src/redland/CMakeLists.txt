# Note: This is the only cmakelists.txt for the redland combined that is used
# in the libOmexMeta project. The individual redland packages do have their
# own cmake script, but these are for building each of the redland libraries alone. In this
# cmake script we pull the redland libraries into a single library along with some
# C++ wrapper code, which I wrote myself.
# todo: consider moving the wrapper code to the main repository.

project(redland-libraries-combined)

##################################################################################
#    set some variables
#

set(target redland-combined)

SET(RAPTOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/raptor2-2.0.15)
SET(RASQAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rasqal-0.9.33)
SET(LIBRDF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/redland-1.0.17)
SET(WRAPPER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/RedlandWrapper)

SET(RAPTOR_SOURCE_DIR ${RAPTOR_DIR}/src)
SET(RASQAL_SOURCE_DIR ${RASQAL_DIR}/src)
SET(LIBRDF_SOURCE_DIR ${LIBRDF_DIR}/src)
SET(WRAPPER_SOURCE_DIR ${WRAPPER_DIR}/src)

# directory of the wrapper tests
SET(WRAPPER_TEST_DIR ${WRAPPER_DIR}/test)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(RASQAL_DEBUGGING OFF CACHE BOOL "Turn on debugging for rasqal library. Only effective in debug mode")
    set(RAPTOR_DEBUGGING OFF CACHE BOOL "Turn on debugging for raptor library. Only effective in debug mode")
    set(LIBRDF_DEBUGGING OFF CACHE BOOL "Turn on debugging for librdf library. Only effective in debug mode")
endif ()

# set directory for librdf storage/cache. only used when not specified by user
#  which it is in the context of libomexmeta. I'm not sure about this.
set(PKGDATADIR $ENV{HOME}/.librdf_package_data_dir)
#file(MAKE_DIRECTORY ${PKGDATADIR})

# used by redland to store storage modules - still experimental
#  and not exactly sure how to use
set(REDLAND_MODULE_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
add_definitions(
        -DREDLAND_MODULE_PATH="${REDLAND_MODULE_PATH}"
        -DPKGDATADIR="${PKGDATADIR}"
)
# COMMENTED OUT FOR NOW
#file(MAKE_DIRECTORY ${PKGDATADIR})
#file(MAKE_DIRECTORY ${REDLAND_MODULE_PATH})


#definitions needed to compile librdf/rptor/rasqal
add_definitions(-DHAVE_CONFIG_H
        -DRASQAL_INTERNAL=1
        -DLIBRDF_INTERNAL=1
        -DLIBRDFA_IN_RAPTOR=1
        -DRAPTOR_INTERNAL=1
        #        -DRAPTOR_DEBUG=0 # sometimes useful. Comment out but don't delete.
        )

# files to configure - This overwrites the configuration generated from automate system
#  which I have modified manually. Do not uncomment but keep as a record of what was done.
#configure_file(${RAPTOR_DIR}/src/raptor_config_cmake.h.in raptor2-2.0.15/src/raptor_config.h @ONLY)
#configure_file(${RAPTOR_DIR}/src/raptor2.h.in ${RAPTOR_DIR}/src/raptor2.h @ONLY)
#configure_file(${RASQAL_DIR}/src/rasqal_config.h.in ${RASQAL_DIR}/src/rasqal_config.h)
#configure_file(${RASQAL_DIR}/rasqal-src-config.in ${RASQAL_DIR}/rasqal-src-config)


##################################################################################
#       Sources
#

# The redland libraries are highly modular. Sometimes there are redundancies
# in these modules. For instance, there are 3 libraries that can be used to implement
# integer types or 2 libraries that can be used for regexes.
# Sometimes I've commented out a feature in favour of one that does the same job.
# Best to leave these commented out incase we want to change later.


# I'm not sure whether these sources are actually used but they are
# not causing any harm where they are.
set(RAPTOR_LIBRDFA_SOURCES
        ${RAPTOR_DIR}/librdfa/context.c
        ${RAPTOR_DIR}/librdfa/config.h
        ${RAPTOR_DIR}/librdfa/curie.c
        ${RAPTOR_DIR}/librdfa/iri.c
        ${RAPTOR_DIR}/librdfa/language.c
        ${RAPTOR_DIR}/librdfa/lists.c
        ${RAPTOR_DIR}/librdfa/namespace.c
        ${RAPTOR_DIR}/librdfa/rdfa.c
        ${RAPTOR_DIR}/librdfa/rdfa.h
        ${RAPTOR_DIR}/librdfa/rdfa_utils.c
        ${RAPTOR_DIR}/librdfa/rdfa_utils.h
        ${RAPTOR_DIR}/librdfa/strtok_r.c
        ${RAPTOR_DIR}/librdfa/strtok_r.h
        ${RAPTOR_DIR}/librdfa/subject.c
        ${RAPTOR_DIR}/librdfa/triple.c
        )

# define raptor_sources
set(RAPTOR_SOURCES
        ${RAPTOR_LIBRDFA_SOURCES}
        ${RAPTOR_SOURCE_DIR}/raptor.h
        ${RAPTOR_SOURCE_DIR}/raptor2.h
        ${RAPTOR_SOURCE_DIR}/git-version.h
        ${RAPTOR_SOURCE_DIR}/ntriples_parse.c
        ${RAPTOR_SOURCE_DIR}/parsedate.c
        ${RAPTOR_SOURCE_DIR}/raptor_abbrev.c
        ${RAPTOR_SOURCE_DIR}/raptor_avltree.c
        ${RAPTOR_SOURCE_DIR}/raptor_concepts.c
        ${RAPTOR_SOURCE_DIR}/raptor_config.h
        ${RAPTOR_SOURCE_DIR}/raptor_config_linux.h
        ${RAPTOR_SOURCE_DIR}/raptor_config_windows.h
        #        ${RAPTOR_SOURCE_DIR}/raptor_win32.c // removed in favour of above
        ${RAPTOR_SOURCE_DIR}/raptor_escaped.c
        ${RAPTOR_SOURCE_DIR}/raptor_general.c
        ${RAPTOR_SOURCE_DIR}/raptor_grddl.c
        ${RAPTOR_SOURCE_DIR}/raptor_guess.c
        ${RAPTOR_SOURCE_DIR}/raptor_internal.h
        ${RAPTOR_SOURCE_DIR}/raptor_iostream.c
        ${RAPTOR_SOURCE_DIR}/raptor_json.c
        ${RAPTOR_SOURCE_DIR}/raptor_json_writer.c
        ${RAPTOR_SOURCE_DIR}/raptor_librdfa.c
        ${RAPTOR_SOURCE_DIR}/raptor_libxml.c
        ${RAPTOR_SOURCE_DIR}/raptor_locator.c
        ${RAPTOR_SOURCE_DIR}/raptor_log.c
        ${RAPTOR_SOURCE_DIR}/raptor_memstr.c
        ${RAPTOR_SOURCE_DIR}/raptor_namespace.c
        # commented out because it is never used and incurs icu as a dependency
        # ${RAPTOR_SOURCE_DIR}/raptor_nfc_icu.c
        ${RAPTOR_SOURCE_DIR}/raptor_ntriples.c
        ${RAPTOR_SOURCE_DIR}/raptor_option.c
        ${RAPTOR_SOURCE_DIR}/raptor_parse.c
        ${RAPTOR_SOURCE_DIR}/raptor_qname.c
        ${RAPTOR_SOURCE_DIR}/raptor_rdfxml.c
        ${RAPTOR_SOURCE_DIR}/raptor_rfc2396.c
        ${RAPTOR_SOURCE_DIR}/raptor_rss.c
        ${RAPTOR_SOURCE_DIR}/raptor_rss.h
        ${RAPTOR_SOURCE_DIR}/raptor_rss_common.c
        ${RAPTOR_SOURCE_DIR}/raptor_sax2.c
        ${RAPTOR_SOURCE_DIR}/raptor_sequence.c
        ${RAPTOR_SOURCE_DIR}/raptor_serialize.c
        ${RAPTOR_SOURCE_DIR}/raptor_serialize_dot.c
        ${RAPTOR_SOURCE_DIR}/raptor_serialize_html.c
        ${RAPTOR_SOURCE_DIR}/raptor_serialize_json.c
        ${RAPTOR_SOURCE_DIR}/raptor_serialize_ntriples.c
        ${RAPTOR_SOURCE_DIR}/raptor_serialize_rdfxml.c
        ${RAPTOR_SOURCE_DIR}/raptor_serialize_rdfxmla.c
        ${RAPTOR_SOURCE_DIR}/raptor_serialize_rss.c
        ${RAPTOR_SOURCE_DIR}/raptor_serialize_turtle.c
        ${RAPTOR_SOURCE_DIR}/raptor_set.c
        ${RAPTOR_SOURCE_DIR}/raptor_statement.c
        ${RAPTOR_SOURCE_DIR}/raptor_stringbuffer.c
        ${RAPTOR_SOURCE_DIR}/raptor_syntax_description.c
        ${RAPTOR_SOURCE_DIR}/raptor_term.c
        ${RAPTOR_SOURCE_DIR}/raptor_turtle_writer.c
        ${RAPTOR_SOURCE_DIR}/raptor_unicode.c
        ${RAPTOR_SOURCE_DIR}/raptor_uri.c
        #        ${RAPTOR_SOURCE_DIR}/raptor_win32.c
        ${RAPTOR_SOURCE_DIR}/raptor_www.c
        ${RAPTOR_SOURCE_DIR}/raptor_www_curl.c
        # since we use curl for www funcitonality, we do not need these
        #  sources. Note I've tried the libxml version and couldn't get it working.
        # ${RAPTOR_SOURCE_DIR}/raptor_www_libfetch.c
        # ${RAPTOR_SOURCE_DIR}/raptor_www_libxml.c
        ${RAPTOR_SOURCE_DIR}/raptor_xml.c
        ${RAPTOR_SOURCE_DIR}/raptor_xml_writer.c
        ${RAPTOR_SOURCE_DIR}/snprintf.c
        ${RAPTOR_SOURCE_DIR}/sort_r.c
        ${RAPTOR_SOURCE_DIR}/sort_r.h
        ${RAPTOR_SOURCE_DIR}/ssort.h
        ${RAPTOR_SOURCE_DIR}/strcasecmp.c
        ${RAPTOR_SOURCE_DIR}/turtle_common.c
        ${RAPTOR_SOURCE_DIR}/turtle_common.h
        ${RAPTOR_SOURCE_DIR}/turtle_lexer.c
        ${RAPTOR_SOURCE_DIR}/turtle_lexer.h
        ${RAPTOR_SOURCE_DIR}/turtle_parser.c
        ${RAPTOR_SOURCE_DIR}/turtle_parser.h
        )

#set(RASQAL_MTWIST_SOURCES
#        ${RASQAL_DIR}/libmtwist/mt.c
#        ${RASQAL_DIR}/libmtwist/mtwist.h
#        ${RASQAL_DIR}/libmtwist/mtwist_internal.h
#        ${RASQAL_DIR}/libmtwist/seed.c
#        )

set(RASQAL_LIBSV_SOURCES
        ${RASQAL_DIR}/libsv/sv.c
        ${RASQAL_DIR}/libsv/sv.h
        #        ${RASQAL_DIR}/libsv/sv2c.c # has a main function, so probs not wanted here
        )

set(RASQAL_SOURCES
        #        ${RASQAL_MTWIST_SOURCES}
        ${RASQAL_LIBSV_SOURCES}
        ${RASQAL_SOURCE_DIR}/rasqal_algebra.c
        ${RASQAL_SOURCE_DIR}/rasqal_expr.c
        ${RASQAL_SOURCE_DIR}/rasqal_expr_evaluate.c
        ${RASQAL_SOURCE_DIR}/rasqal_expr_datetimes.c
        ${RASQAL_SOURCE_DIR}/rasqal_expr_numerics.c
        ${RASQAL_SOURCE_DIR}/rasqal_expr_strings.c
        ${RASQAL_SOURCE_DIR}/rasqal_general.c
        ${RASQAL_SOURCE_DIR}/rasqal_query.c
        ${RASQAL_SOURCE_DIR}/rasqal_query_results.c
        ${RASQAL_SOURCE_DIR}/rasqal_engine.c
        ${RASQAL_SOURCE_DIR}/rasqal_raptor.c
        ${RASQAL_SOURCE_DIR}/rasqal_literal.c
        ${RASQAL_SOURCE_DIR}/rasqal_formula.c
        ${RASQAL_SOURCE_DIR}/rasqal_graph_pattern.c
        ${RASQAL_SOURCE_DIR}/rasqal_map.c
        ${RASQAL_SOURCE_DIR}/rasqal_feature.c
        ${RASQAL_SOURCE_DIR}/rasqal_result_formats.c
        ${RASQAL_SOURCE_DIR}/rasqal_xsd_datatypes.c
        ${RASQAL_SOURCE_DIR}/rasqal_decimal.c
        ${RASQAL_SOURCE_DIR}/rasqal_datetime.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource.c
        ${RASQAL_SOURCE_DIR}/rasqal_format_sparql_xml.c
        ${RASQAL_SOURCE_DIR}/rasqal_variable.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_empty.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_union.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_rowsequence.c
        ${RASQAL_SOURCE_DIR}/rasqal_query_transform.c
        ${RASQAL_SOURCE_DIR}/rasqal_row.c
        ${RASQAL_SOURCE_DIR}/rasqal_engine_algebra.c
        ${RASQAL_SOURCE_DIR}/rasqal_triples_source.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_triples.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_filter.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_sort.c
        ${RASQAL_SOURCE_DIR}/rasqal_engine_sort.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_project.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_join.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_graph.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_distinct.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_groupby.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_aggregation.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_having.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_slice.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_bindings.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_service.c
        ${RASQAL_SOURCE_DIR}/rasqal_row_compatible.c
        ${RASQAL_SOURCE_DIR}/rasqal_format_table.c
        ${RASQAL_SOURCE_DIR}/rasqal_query_write.c
        ${RASQAL_SOURCE_DIR}/rasqal_format_json.c
        ${RASQAL_SOURCE_DIR}/rasqal_format_sv.c
        ${RASQAL_SOURCE_DIR}/rasqal_format_html.c
        ${RASQAL_SOURCE_DIR}/rasqal_format_rdf.c
        ${RASQAL_SOURCE_DIR}/rasqal_rowsource_assignment.c
        ${RASQAL_SOURCE_DIR}/rasqal_update.c
        ${RASQAL_SOURCE_DIR}/rasqal_triple.c
        ${RASQAL_SOURCE_DIR}/rasqal_data_graph.c
        ${RASQAL_SOURCE_DIR}/rasqal_prefix.c
        ${RASQAL_SOURCE_DIR}/rasqal_solution_modifier.c
        ${RASQAL_SOURCE_DIR}/rasqal_projection.c
        ${RASQAL_SOURCE_DIR}/rasqal_bindings.c
        ${RASQAL_SOURCE_DIR}/rasqal_service.c
        ${RASQAL_SOURCE_DIR}/rasqal_dataset.c
        ${RASQAL_SOURCE_DIR}/rasqal_random.c
        ${RASQAL_SOURCE_DIR}/rasqal_digest.c
        ${RASQAL_SOURCE_DIR}/rasqal_iostream.c
        ${RASQAL_SOURCE_DIR}/rasqal_regex.c
        ${RASQAL_SOURCE_DIR}/snprintf.c
        ${RASQAL_SOURCE_DIR}/rasqal_double.c
        ${RASQAL_SOURCE_DIR}/rasqal_ntriples.c
        ${RASQAL_SOURCE_DIR}/rasqal_results_compare.c
        ${RASQAL_SOURCE_DIR}/ssort.h
        ${RASQAL_SOURCE_DIR}/sparql_lexer.c
        ${RASQAL_SOURCE_DIR}/sparql_lexer.h
        ${RASQAL_SOURCE_DIR}/sparql_parser.c
        ${RASQAL_SOURCE_DIR}/sparql_parser.h
        ${RASQAL_SOURCE_DIR}/sparql_common.h
        #        ${RASQAL_SOURCE_DIR}/strcasecmp.c
        ${RASQAL_SOURCE_DIR}/timegm.c
        ${RASQAL_SOURCE_DIR}/gettimeofday.c
        ${RASQAL_SOURCE_DIR}/rasqal_sort.c
        ${RASQAL_SOURCE_DIR}/rasqal_digest_md5.c
        ${RASQAL_SOURCE_DIR}/rasqal_digest_sha1.c
        ${RASQAL_SOURCE_DIR}/rasqal.h
        )

set(LIBRDF_SOURCES
        ${LIBRDF_SOURCE_DIR}/librdf.h
        ${LIBRDF_SOURCE_DIR}/memcmp.c
        ${LIBRDF_SOURCE_DIR}/rdf_concepts.c
        ${LIBRDF_SOURCE_DIR}/rdf_concepts.h
        ${LIBRDF_SOURCE_DIR}/rdf_concepts_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_config.h
        ${LIBRDF_SOURCE_DIR}/rdf_config_linux.h
        ${LIBRDF_SOURCE_DIR}/win32_rdf_config.h
        ${LIBRDF_SOURCE_DIR}/rdf_digest.c
        ${LIBRDF_SOURCE_DIR}/rdf_digest.h
        ${LIBRDF_SOURCE_DIR}/rdf_digest_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_digest_md5.c
        ${LIBRDF_SOURCE_DIR}/rdf_digest_sha1.c
        ${LIBRDF_SOURCE_DIR}/rdf_files.c
        ${LIBRDF_SOURCE_DIR}/rdf_files.h
        ${LIBRDF_SOURCE_DIR}/rdf_hash.c
        ${LIBRDF_SOURCE_DIR}/rdf_hash.h
        #    ${LIBRDF_SOURCE_DIR}/rdf_hash_bdb.c
        ${LIBRDF_SOURCE_DIR}/rdf_hash_cursor.c
        ${LIBRDF_SOURCE_DIR}/rdf_hash_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_hash_memory.c
        ${LIBRDF_SOURCE_DIR}/rdf_heuristics.c
        ${LIBRDF_SOURCE_DIR}/rdf_heuristics.h
        ${LIBRDF_SOURCE_DIR}/rdf_init.c
        ${LIBRDF_SOURCE_DIR}/rdf_init.h
        ${LIBRDF_SOURCE_DIR}/rdf_init_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_iterator.c
        ${LIBRDF_SOURCE_DIR}/rdf_iterator.h
        ${LIBRDF_SOURCE_DIR}/rdf_iterator_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_list.c
        ${LIBRDF_SOURCE_DIR}/rdf_list.h
        ${LIBRDF_SOURCE_DIR}/rdf_list_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_log.c
        ${LIBRDF_SOURCE_DIR}/rdf_log.h
        ${LIBRDF_SOURCE_DIR}/rdf_log_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_model.c
        ${LIBRDF_SOURCE_DIR}/rdf_model.h
        ${LIBRDF_SOURCE_DIR}/rdf_model_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_model_storage.c
        ${LIBRDF_SOURCE_DIR}/rdf_node.c
        ${LIBRDF_SOURCE_DIR}/rdf_node.h
        ${LIBRDF_SOURCE_DIR}/rdf_node_common.c
        ${LIBRDF_SOURCE_DIR}/rdf_node_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_parser.c
        ${LIBRDF_SOURCE_DIR}/rdf_parser.h
        ${LIBRDF_SOURCE_DIR}/rdf_parser_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_parser_raptor.c
        ${LIBRDF_SOURCE_DIR}/rdf_query.c
        ${LIBRDF_SOURCE_DIR}/rdf_query.h
        ${LIBRDF_SOURCE_DIR}/rdf_query_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_query_rasqal.c
        ${LIBRDF_SOURCE_DIR}/rdf_query_results.c
        #        ${LIBRDF_SOURCE_DIR}/rdf_query_virtuoso.c
        ${LIBRDF_SOURCE_DIR}/rdf_raptor.c
        ${LIBRDF_SOURCE_DIR}/rdf_raptor.h
        ${LIBRDF_SOURCE_DIR}/rdf_raptor_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_serializer.c
        ${LIBRDF_SOURCE_DIR}/rdf_serializer.h
        ${LIBRDF_SOURCE_DIR}/rdf_serializer_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_serializer_raptor.c
        ${LIBRDF_SOURCE_DIR}/rdf_statement.c
        ${LIBRDF_SOURCE_DIR}/rdf_statement.h
        ${LIBRDF_SOURCE_DIR}/rdf_statement_common.c
        ${LIBRDF_SOURCE_DIR}/rdf_statement_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_storage.c
        ${LIBRDF_SOURCE_DIR}/rdf_storage.h
        ${LIBRDF_SOURCE_DIR}/rdf_storage_file.c
        ${LIBRDF_SOURCE_DIR}/rdf_storage_hashes.c
        ${LIBRDF_SOURCE_DIR}/rdf_storage_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_storage_list.c
        ${LIBRDF_SOURCE_DIR}/rdf_storage_module.h
        #    ${LIBRDF_SOURCE_DIR}/rdf_storage_postgresql.c
        ${LIBRDF_SOURCE_DIR}/rdf_storage_sql.c
        ${LIBRDF_SOURCE_DIR}/rdf_storage_sqlite.c
        ${LIBRDF_SOURCE_DIR}/rdf_storage_trees.c
        #        ${LIBRDF_SOURCE_DIR}/rdf_storage_virtuoso.c
        #        ${LIBRDF_SOURCE_DIR}/rdf_storage_virtuoso_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_stream.c
        ${LIBRDF_SOURCE_DIR}/rdf_stream.h
        ${LIBRDF_SOURCE_DIR}/rdf_stream_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_types.h
        ${LIBRDF_SOURCE_DIR}/rdf_uri.c
        ${LIBRDF_SOURCE_DIR}/rdf_uri.h
        ${LIBRDF_SOURCE_DIR}/rdf_uri_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_utf8.c
        ${LIBRDF_SOURCE_DIR}/rdf_utf8.h
        ${LIBRDF_SOURCE_DIR}/redland.h
        #         ${LIBRDF_DIR}/src/rdf_storage_tstore.c // includes <rdfsql/rdfsql.h> which is un-locatable
        # ${LIBRDF_DIR}/src/rdf_storage_mysql.c // no mysql setup yet. todo
        )

SET(WRAPPER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/RedlandWrapper/src/include")
set(WRAPPER_SOURCES
        ${WRAPPER_SOURCE_DIR}/LibrdfModel.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfNode.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfParser.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfQuery.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfQueryResults.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfSerializer.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfStatement.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfStorage.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfUri.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfWorld.cpp
        ${WRAPPER_SOURCE_DIR}/Query.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfStream.cpp
        ${WRAPPER_SOURCE_DIR}/Logger.cpp

        ${WRAPPER_INCLUDE_DIR}/redland/RedlandAPI.h
        ${WRAPPER_INCLUDE_DIR}/redland/LibrdfWorld.h
        ${WRAPPER_INCLUDE_DIR}/redland/LibrdfModel.h
        ${WRAPPER_INCLUDE_DIR}/redland/LibrdfNode.h
        ${WRAPPER_INCLUDE_DIR}/redland/LibrdfParser.h
        ${WRAPPER_INCLUDE_DIR}/redland/LibrdfQuery.h
        ${WRAPPER_INCLUDE_DIR}/redland/LibrdfQueryResults.h
        ${WRAPPER_INCLUDE_DIR}/redland/LibrdfSerializer.h
        ${WRAPPER_INCLUDE_DIR}/redland/LibrdfStatement.h
        ${WRAPPER_INCLUDE_DIR}/redland/LibrdfStorage.h
        ${WRAPPER_INCLUDE_DIR}/redland/LibrdfUri.h
        ${WRAPPER_INCLUDE_DIR}/redland/LibrdfException.h
        ${WRAPPER_INCLUDE_DIR}/redland/Query.h
        ${WRAPPER_INCLUDE_DIR}/redland/RefCountedRedlandType.h
        ${WRAPPER_INCLUDE_DIR}/redland/RedlandType.h
        ${WRAPPER_INCLUDE_DIR}/redland/LibrdfStream.h
        ${WRAPPER_INCLUDE_DIR}/redland/Logger.h
        )


set(ALL_REDLAND_SOURCES
        ${RAPTOR_SOURCES}
        ${RASQAL_SOURCES}
        ${LIBRDF_SOURCES}
        ${WRAPPER_SOURCES}
        ${CMAKE_CURRENT_BINARY_DIR}/redland_export.h
        )


set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES}
        "${WRAPPER_INCLUDE_DIR}" "${WRAPPER_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} PARENT_SCOPE)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/raptor2-2.0.15/src/raptor2.h" "${CMAKE_CURRENT_SOURCE_DIR}/RedlandWrapper/src/include/redland" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/rasqal-0.9.33/src/rasqal.h" "${CMAKE_CURRENT_SOURCE_DIR}/RedlandWrapper/src/include/redland" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/redland-1.0.17/src/librdf.h" "${CMAKE_CURRENT_SOURCE_DIR}/RedlandWrapper/src/include/redland" COPYONLY)

#######################################################
#   Build the library static
#

add_library(${target}-static STATIC ${ALL_REDLAND_SOURCES})

target_compile_definitions(
        ${target}-static
        PUBLIC
        RAPTOR_STATIC
        RASQAL_STATIC
        LIBRDF_STATIC
        REDLAND_STATIC_DEFINE
        LIBXML_STATIC
        XML_STATIC
        LIBEXSLT_STATIC
        LIBXSLT_STATIC
        CURL_STATICLIB
        SQLITE_STATIC
        YAJL_STATIC
        LIBLAX_STATIC
        ZLIB_STATIC
)

if (WIN32)
    target_link_options(${target}-static PUBLIC /NODEFAULTLIB:library)
endif ()

# on linux we get errors when we run tests for c api
# because libgnutls cannot locate zlib.
# The easy way to solve this for now is to give it z lib shared

target_link_libraries(
        ${target}-static PUBLIC
        unofficial::sqlite3::sqlite3
        CURL::libcurl
        LibLZMA::LibLZMA
        LibXslt
        LibXml2
        ${YAJL_STATIC_LIBRARY}
        ${PCRE_STATIC_LIBRARY}
        spdlog
)


add_dependencies(${target}-static LibXml2 LibXslt)

message(STATUS "
LINK_FLAGS ${CMAKE_SHARED_LINKER_FLAGS}

")


add_custom_target(
        printIncl
        COMMAND ${CMAKE_COMMAND} -E echo "cmd here $<TARGET_FILE:LibXslt>"
)


target_include_directories(
        ${target}-static
        PUBLIC
        # raptor includes
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/raptor2-2.0.15/src>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/raptor2-2.0.15/utils>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/raptor2-2.0.15/librdfa>

        # rasqal includes
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/src>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/libmtwist>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/libsv>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/utils>

        # librdf includes
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/redland-1.0.17/src>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/redland-1.0.17/utils>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/redland-1.0.17/libltdl>

        # wrapper includes
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/RedlandWrapper/src>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/RedlandWrapper/src/include>

        # libomexmeta includes
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/include>

        # others
        $<BUILD_INTERFACE:${PCRE_INCLUDE_DIR}>

        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src/omexmeta>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src/omexmeta/C>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src/redland>
        $<BUILD_INTERFACE:${SPDLOG_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
        #        # dependency includes
        #        $<BUILD_INTERFACE:${LIBXML2_INCLUDE_DIR}>
        #        $<BUILD_INTERFACE:${LIBXSLT_INCLUDE_DIR}>
        #        $<BUILD_INTERFACE:${CURL_INCLUDE_DIR}>
        #        $<BUILD_INTERFACE:${SSL_INCLUDE_DIR}>
        #        $<BUILD_INTERFACE:${SSL_INCLUDE_DIR}>
        #        $<BUILD_INTERFACE:${YAJL_INCLUDE_DIR}>
        #        $<BUILD_INTERFACE:${LZMA_INCLUDE_DIR}>
        #        $<BUILD_INTERFACE:${ZLIB_INCLUDE_DIR}>
        #        $<BUILD_INTERFACE:${PCRE_INCLUDE_DIR}>
        #        $<BUILD_INTERFACE:${ICONV_INCLUDE_DIR}>

)


# install redland static target
install(
        TARGETS ${target}-static
        EXPORT ${target}-static
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/redland
)

# install the export info
install(
        EXPORT ${target}-static
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/omexmeta
        NAMESPACE OmexMeta::
        FILE RedlandCombinedStatic.cmake
)

if (PLATFORM STREQUAL "windows-msvc")
    foreach (lib ${LIBRARIES})
        add_custom_command(TARGET ${target}-static POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different "${lib}"
                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
        add_custom_command(TARGET ${target}-static POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${lib}" "${PYOMEXMETA_DIR}")
    endforeach ()
endif ()

add_custom_target(printx
        COMMAND ${CMAKE_COMMAND} -E echo "cmd: $<TARGET_PROPERTY:redland-combined-static,LINK_LIBRARIES>")


# add the shared library
add_library(${target} SHARED ${ALL_REDLAND_SOURCES})
target_compile_definitions(${target} PUBLIC $<TARGET_PROPERTY:redland-combined-static,COMPILE_DEFINITIONS>)
if (WIN32)
    target_link_options(${target} PUBLIC /NODEFAULTLIB:library)
endif ()

target_link_libraries(${target} PUBLIC $<TARGET_PROPERTY:redland-combined-static,LINK_LIBRARIES>)
target_include_directories(
        ${target} PRIVATE
        $<TARGET_PROPERTY:redland-combined-static,INCLUDE_DIRECTORIES>
        #        ${CMAKE_CURRENT_BINARY_DIR}
)
add_dependencies(${target} LibXml2 LibXslt)

get_target_property(v ${target} LINK_OPTIONS)
MESSAGE(STATUS "FLGS ${v}")

#unofficial::sqlite3::sqlite3;CURL::libcurl;LibLZMA::LibLZMA
#OpenSSL::SSL;OpenSSL::Crypto;ZLIB::ZLIB
#unofficial::pcre::pcre unofficial::pcre::pcre16 unofficial::pcre::pcre32 unofficial::pcre::pcrecpp
#get_target_property(var CURL::libcurl INTERFACE_LINK_LIBRARIES )
#MESSAGE(STATUS "var ${var}")
include(GenerateExportHeader)
generate_export_header(${target} BASE_NAME REDLAND)


# install shared library into standard locations.
install(TARGETS ${target}
        EXPORT ${target}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/redland
        )
# install the export info
install(
        EXPORT ${target}
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/omexmeta
        NAMESPACE OmexMeta::
        FILE RedlandCombined.cmake
)



