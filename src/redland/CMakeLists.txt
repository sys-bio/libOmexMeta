project(redland-combined)

message(STATUS "Building redland-combind")

##################################################################################
#       definitions, configuations
#

SET(RAPTOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/raptor2-2.0.15)
SET(RASQAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rasqal-0.9.33)
SET(LIBRDF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/redland-1.0.17)

SET(RAPTOR_SOURCE_DIR ${RAPTOR_DIR}/src)
SET(RASQAL_SOURCE_DIR ${RASQAL_DIR}/src)
SET(LIBRDF_SOURCE_DIR ${LIBRDF_DIR}/src)

SET(WRAPPER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/RedlandAPIWrapper)
SET(WRAPPER_SOURCE_DIR ${WRAPPER_DIR}/src)
SET(WRAPPER_TEST_DIR ${WRAPPER_DIR}/test)

# set directory for librdf storage/cache. only used when not specified by user
#  which it is in the context of libsemsim
set(PKGDATADIR $ENV{HOME}/.librdf)
file(MAKE_DIRECTORY ${PKGDATADIR})

#definitions needed to compile librdf/rptor/rasqal
add_definitions(-DHAVE_CONFIG_H
        -DRASQAL_INTERNAL=1
        -DLIBRDF_INTERNAL=1
        -DREDLAND_MODULE_PATH="${CMAKE_CURRENT_BINARY_DIR}"
        -DPKGDATADIR="${PKGDATADIR}"
        -DLIBRDFA_IN_RAPTOR=1
        -DRAPTOR_INTERNAL=1
        #        -DRAPTOR_DEBUG=0
        )

# files to configure - This overwrites the configuration generated from automate system
#  with null values, since I haven't found the cmake equivalent
#note: the copasi-dependencies configures a cmake script to do this. Kind of.
#configure_file(${RAPTOR_DIR}/src/raptor_config_cmake.h.in raptor2-2.0.15/src/raptor_config.h @ONLY)
#configure_file(${RAPTOR_DIR}/src/raptor2.h.in ${RAPTOR_DIR}/src/raptor2.h @ONLY)
#configure_file(${RASQAL_DIR}/src/rasqal_config.h.in ${RASQAL_DIR}/src/rasqal_config.h)
#configure_file(${RASQAL_DIR}/rasqal-src-config.in ${RASQAL_DIR}/rasqal-src-config)


##################################################################################
#       find some dependencies
#


##################################################################################
#       Sources
#
set(RAPTOR_LIBRDFA_SOURCES
        ${RAPTOR_DIR}/librdfa/config.h
        ${RAPTOR_DIR}/librdfa/context.c
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

set(RAPTOR_SOURCES
        ${RAPTOR_LIBRDFA_SOURCES}
        ${RAPTOR_SOURCE_DIR}/git-version.h
        ${RAPTOR_SOURCE_DIR}/ntriples_parse.c
        ${RAPTOR_SOURCE_DIR}/parsedate.c
        ${RAPTOR_SOURCE_DIR}/raptor.h
        ${RAPTOR_SOURCE_DIR}/raptor2.h
        ${RAPTOR_SOURCE_DIR}/raptor_abbrev.c
        ${RAPTOR_SOURCE_DIR}/raptor_avltree.c
        ${RAPTOR_SOURCE_DIR}/raptor_concepts.c
        ${RAPTOR_SOURCE_DIR}/raptor_config.h
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
        ${RASQAL_SOURCE_DIR}/strcasecmp.c
        ${RASQAL_SOURCE_DIR}/timegm.c
        ${RASQAL_SOURCE_DIR}/gettimeofday.c
        ${RASQAL_SOURCE_DIR}/rasqal_sort.c
        ${RASQAL_SOURCE_DIR}/rasqal_digest_md5.c
        ${RASQAL_SOURCE_DIR}/rasqal_digest_sha1.c
        )

set(LIBRDF_SOURCES
        ${LIBRDF_SOURCE_DIR}/librdf.h
        ${LIBRDF_SOURCE_DIR}/memcmp.c
        ${LIBRDF_SOURCE_DIR}/rdf_concepts.c
        ${LIBRDF_SOURCE_DIR}/rdf_concepts.h
        ${LIBRDF_SOURCE_DIR}/rdf_concepts_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_config.h
        ${LIBRDF_SOURCE_DIR}/rdf_digest.c
        ${LIBRDF_SOURCE_DIR}/rdf_digest.h
        ${LIBRDF_SOURCE_DIR}/rdf_digest_internal.h
        ${LIBRDF_SOURCE_DIR}/rdf_digest_md5.c
        ${LIBRDF_SOURCE_DIR}/rdf_digest_sha1.c
        ${LIBRDF_SOURCE_DIR}/rdf_files.c
        ${LIBRDF_SOURCE_DIR}/rdf_files.h
        ${LIBRDF_SOURCE_DIR}/rdf_hash.c
        ${LIBRDF_SOURCE_DIR}/rdf_hash.h
        #        ${LIBRDF_SOURCE_DIR}/rdf_hash_bdb.c
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
        #        ${LIBRDF_SOURCE_DIR}/rdf_storage_postgresql.c
        ${LIBRDF_SOURCE_DIR}/rdf_storage_sql.c
#        ${LIBRDF_SOURCE_DIR}/rdf_storage_sqlite.c
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


set(WRAPPER_SOURCES
        ${WRAPPER_SOURCE_DIR}/LibrdfModel.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfModel.h
        ${WRAPPER_SOURCE_DIR}/LibrdfNode.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfNode.h
        ${WRAPPER_SOURCE_DIR}/LibrdfParser.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfParser.h
        ${WRAPPER_SOURCE_DIR}/LibrdfQuery.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfQuery.h
        ${WRAPPER_SOURCE_DIR}/LibrdfQueryResults.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfQueryResults.h
        ${WRAPPER_SOURCE_DIR}/LibrdfSerializer.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfSerializer.h
        ${WRAPPER_SOURCE_DIR}/LibrdfStatement.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfStatement.h
        ${WRAPPER_SOURCE_DIR}/LibrdfStorage.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfStorage.h
        ${WRAPPER_SOURCE_DIR}/LibrdfStream.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfStream.h
        ${WRAPPER_SOURCE_DIR}/LibrdfUri.cpp
        ${WRAPPER_SOURCE_DIR}/LibrdfUri.h
        ${WRAPPER_SOURCE_DIR}/RaptorIOStream.cpp
        ${WRAPPER_SOURCE_DIR}/RaptorIOStream.h
        ${WRAPPER_SOURCE_DIR}/RedlandAPIWrapper.h
        ${WRAPPER_SOURCE_DIR}/World.cpp
        ${WRAPPER_SOURCE_DIR}/World.h
        ${WRAPPER_SOURCE_DIR}/LibrdfException.h
        )


#######################################################
#   Build the library static
#
message(STATUS "before adding the library")
add_library(redland-combined STATIC
        ${RAPTOR_SOURCES}
        ${RASQAL_SOURCES}
        ${LIBRDF_SOURCES}
        ${WRAPPER_SOURCES}
        )
set_target_properties(redland-combined PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(redland-combined PUBLIC
        ${INCLUDE_DIRECTORIES}
        D:/vcpkg/installed/x64-windows/include
        )

target_link_libraries(redland-combined PUBLIC
        ${LINK_LIBRARIES}

        )


set_target_properties(redland-combined PROPERTIES PUBLIC_HEADER
        ${RAPTOR_DIR}/src/raptor2.h
        ${RASQAL_DIR}/src/rasqal.h
        ${LIBRDF_DIR}/src/librdf.h
        )

INSTALL(
        TARGETS redland-combined
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

option(BUILD_WRAPPER_TESTS "Build the tests for the redland api wrapper" OFF)

message(STATUS "BUILD_WRAPPER_TESTS ${BUILD_WRAPPER_TESTS}")
if (${BUILD_WRAPPER_TESTS})
    add_subdirectory(RedlandAPIWrapper/test)
endif ()