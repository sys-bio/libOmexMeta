project(redland-combined)

##################################################################################
#       definitions, configuations
#

#definitions needed to compile librdf/rptor/rasqal
add_definitions(-DHAVE_CONFIG_H -DRASQAL_INTERNAL
        -DLIBRDF_INTERNAL -DREDLAND_MODULE_PATH
        -DPKGDATADIR ${PKGDATADIR}
        -DLIBRDFA_IN_RAPTOR -DRAPTOR_INTERNAL
        )

# files to configure - needed? possible source of non-portability
# since other systems will not be set up like mine
configure_file(raptor2-2.0.15/src/raptor_config_cmake.h.in raptor2-2.0.15/src/raptor_config.h @ONLY)
configure_file(raptor2-2.0.15/src/raptor2.h.in raptor2-2.0.15/src/raptor2.h @ONLY)
configure_file(rasqal-0.9.33/src/rasqal_config.h.in rasqal-0.9.33/src/rasqal_config.h)
configure_file(rasqal-0.9.33/rasqal-src-config.in rasqal-0.9.33/rasqal-src-config)

# set directory for librdf storage/cache. only used when not specified by user
set(PKGDATADIR $ENV{HOME}/.librdf)
file(MAKE_DIRECTORY ${PKGDATADIR})

##################################################################################
#       find some dependencies
#

find_library(LIBPQ_STATIC_LIBRARY
        NAMES pq.a libpq.a pq libpq
        )

if (NOT LIBPQ_STATIC_LIBRARY)
    message(WARNING "libpq not found so skipping these source files. Install with sudo apt install libpq-dev")
endif ()


find_path(LIBPQ_INCLUDE_DIR
        NAMES libpq-fe.h
        PATHS /usr/include/postgresql
        )

if (NOT LIBPQ_INCLUDE_DIR)
    message(WARNING "libpq-fe.h not found. Install with sudo apt install libpq-dev")
endif ()


##################################################################################
#       Sources
#

set(RAPTOR_SOURCES
        raptor2-2.0.15/src/raptor_parse.c
        raptor2-2.0.15/src/raptor_serialize.c
        raptor2-2.0.15/src/raptor_rfc2396.c
        raptor2-2.0.15/src/raptor_uri.c
        raptor2-2.0.15/src/raptor_log.c
        raptor2-2.0.15/src/raptor_locator.c
        raptor2-2.0.15/src/raptor_namespace.c
        raptor2-2.0.15/src/raptor_qname.c
        raptor2-2.0.15/src/raptor_option.c
        raptor2-2.0.15/src/raptor_general.c
        raptor2-2.0.15/src/raptor_unicode.c
        raptor2-2.0.15/src/raptor_www.c
        raptor2-2.0.15/src/raptor_statement.c
        raptor2-2.0.15/src/raptor_term.c
        raptor2-2.0.15/src/raptor_sequence.c
        raptor2-2.0.15/src/raptor_stringbuffer.c
        raptor2-2.0.15/src/raptor_iostream.c
        raptor2-2.0.15/src/raptor_xml.c
        raptor2-2.0.15/src/raptor_xml_writer.c
        raptor2-2.0.15/src/raptor_set.c
        raptor2-2.0.15/src/turtle_common.c
        raptor2-2.0.15/src/raptor_turtle_writer.c
        raptor2-2.0.15/src/raptor_avltree.c
        raptor2-2.0.15/src/snprintf.c
        raptor2-2.0.15/src/raptor_json_writer.c
        raptor2-2.0.15/src/raptor_memstr.c
        raptor2-2.0.15/src/raptor_concepts.c
        raptor2-2.0.15/src/raptor_syntax_description.c
        raptor2-2.0.15/src/raptor_sax2.c
        raptor2-2.0.15/src/raptor_escaped.c
        raptor2-2.0.15/src/raptor_ntriples.c
        raptor2-2.0.15/src/sort_r.c
        raptor2-2.0.15/src/sort_r.h
        raptor2-2.0.15/src/ssort.h
        raptor2-2.0.15/src/raptor_libxml.c
        raptor2-2.0.15/src/raptor_rdfxml.c
        raptor2-2.0.15/src/turtle_lexer.c
        raptor2-2.0.15/src/turtle_lexer.h
        raptor2-2.0.15/src/turtle_parser.c
        raptor2-2.0.15/src/turtle_parser.h
        raptor2-2.0.15/src/turtle_common.h
        raptor2-2.0.15/src/ntriples_parse.c
        raptor2-2.0.15/src/raptor_rss_common.c
        raptor2-2.0.15/src/raptor_rss.h
        raptor2-2.0.15/src/raptor_rss.c
        raptor2-2.0.15/src/raptor_grddl.c
        raptor2-2.0.15/src/raptor_guess.c
        raptor2-2.0.15/src/raptor_librdfa.c
        raptor2-2.0.15/src/raptor_json.c
        raptor2-2.0.15/src/raptor_serialize_rdfxml.c
        raptor2-2.0.15/src/raptor_serialize_ntriples.c
        raptor2-2.0.15/src/raptor_abbrev.c
        raptor2-2.0.15/src/raptor_serialize_rdfxmla.c
        raptor2-2.0.15/src/raptor_serialize_turtle.c
        raptor2-2.0.15/src/raptor_serialize_rss.c
        raptor2-2.0.15/src/raptor_serialize_dot.c
        raptor2-2.0.15/src/raptor_serialize_html.c
        raptor2-2.0.15/src/raptor_serialize_json.c
        raptor2-2.0.15/src/strcasecmp.c
        raptor2-2.0.15/src/parsedate.c
        )

set(RASQAL_SOURCES
        rasqal-0.9.33/src/rasqal_algebra.c
        rasqal-0.9.33/src/rasqal_expr.c
        rasqal-0.9.33/src/rasqal_expr_evaluate.c
        rasqal-0.9.33/src/rasqal_expr_datetimes.c
        rasqal-0.9.33/src/rasqal_expr_numerics.c
        rasqal-0.9.33/src/rasqal_expr_strings.c
        rasqal-0.9.33/src/rasqal_general.c
        rasqal-0.9.33/src/rasqal_query.c
        rasqal-0.9.33/src/rasqal_query_results.c
        rasqal-0.9.33/src/rasqal_engine.c
        rasqal-0.9.33/src/rasqal_raptor.c
        rasqal-0.9.33/src/rasqal_literal.c
        rasqal-0.9.33/src/rasqal_formula.c
        rasqal-0.9.33/src/rasqal_graph_pattern.c
        rasqal-0.9.33/src/rasqal_map.c
        rasqal-0.9.33/src/rasqal_feature.c
        rasqal-0.9.33/src/rasqal_result_formats.c
        rasqal-0.9.33/src/rasqal_xsd_datatypes.c
        rasqal-0.9.33/src/rasqal_decimal.c
        rasqal-0.9.33/src/rasqal_datetime.c
        rasqal-0.9.33/src/rasqal_rowsource.c
        rasqal-0.9.33/src/rasqal_format_sparql_xml.c
        rasqal-0.9.33/src/rasqal_variable.c
        rasqal-0.9.33/src/rasqal_rowsource_empty.c
        rasqal-0.9.33/src/rasqal_rowsource_union.c
        rasqal-0.9.33/src/rasqal_rowsource_rowsequence.c
        rasqal-0.9.33/src/rasqal_query_transform.c
        rasqal-0.9.33/src/rasqal_row.c
        rasqal-0.9.33/src/rasqal_engine_algebra.c
        rasqal-0.9.33/src/rasqal_triples_source.c
        rasqal-0.9.33/src/rasqal_rowsource_triples.c
        rasqal-0.9.33/src/rasqal_rowsource_filter.c
        rasqal-0.9.33/src/rasqal_rowsource_sort.c
        rasqal-0.9.33/src/rasqal_engine_sort.c
        rasqal-0.9.33/src/rasqal_rowsource_project.c
        rasqal-0.9.33/src/rasqal_rowsource_join.c
        rasqal-0.9.33/src/rasqal_rowsource_graph.c
        rasqal-0.9.33/src/rasqal_rowsource_distinct.c
        rasqal-0.9.33/src/rasqal_rowsource_groupby.c
        rasqal-0.9.33/src/rasqal_rowsource_aggregation.c
        rasqal-0.9.33/src/rasqal_rowsource_having.c
        rasqal-0.9.33/src/rasqal_rowsource_slice.c
        rasqal-0.9.33/src/rasqal_rowsource_bindings.c
        rasqal-0.9.33/src/rasqal_rowsource_service.c
        rasqal-0.9.33/src/rasqal_row_compatible.c
        rasqal-0.9.33/src/rasqal_format_table.c
        rasqal-0.9.33/src/rasqal_query_write.c
        rasqal-0.9.33/src/rasqal_format_json.c
        rasqal-0.9.33/src/rasqal_format_sv.c
        rasqal-0.9.33/src/rasqal_format_html.c
        rasqal-0.9.33/src/rasqal_format_rdf.c
        rasqal-0.9.33/src/rasqal_rowsource_assignment.c
        rasqal-0.9.33/src/rasqal_update.c
        rasqal-0.9.33/src/rasqal_triple.c
        rasqal-0.9.33/src/rasqal_data_graph.c
        rasqal-0.9.33/src/rasqal_prefix.c
        rasqal-0.9.33/src/rasqal_solution_modifier.c
        rasqal-0.9.33/src/rasqal_projection.c
        rasqal-0.9.33/src/rasqal_bindings.c
        rasqal-0.9.33/src/rasqal_service.c
        rasqal-0.9.33/src/rasqal_dataset.c
        rasqal-0.9.33/src/rasqal_random.c
        rasqal-0.9.33/src/rasqal_digest.c
        rasqal-0.9.33/src/rasqal_iostream.c
        rasqal-0.9.33/src/rasqal_regex.c
        rasqal-0.9.33/src/snprintf.c
        rasqal-0.9.33/src/rasqal_double.c
        rasqal-0.9.33/src/rasqal_ntriples.c
        rasqal-0.9.33/src/rasqal_results_compare.c
        rasqal-0.9.33/src/ssort.h
        rasqal-0.9.33/src/sparql_lexer.c
        rasqal-0.9.33/src/sparql_lexer.h
        rasqal-0.9.33/src/sparql_parser.c
        rasqal-0.9.33/src/sparql_parser.h
        rasqal-0.9.33/src/sparql_common.h
        rasqal-0.9.33/src/strcasecmp.c
        rasqal-0.9.33/src/timegm.c
        rasqal-0.9.33/src/gettimeofday.c
        rasqal-0.9.33/src/rasqal_sort.c
        rasqal-0.9.33/src/rasqal_digest_md5.c
        rasqal-0.9.33/src/rasqal_digest_sha1.c
        )


set(LIBRDF_SOURCES
        redland-1.0.17/src/rdf_init.c
        redland-1.0.17/src/rdf_raptor.c
        redland-1.0.17/src/rdf_uri.c
        redland-1.0.17/src/rdf_digest.c
        redland-1.0.17/src/rdf_hash.c
        redland-1.0.17/src/rdf_hash_cursor.c
        redland-1.0.17/src/rdf_hash_memory.c
        redland-1.0.17/src/rdf_model.c
        redland-1.0.17/src/rdf_model_storage.c
        redland-1.0.17/src/rdf_iterator.c
        redland-1.0.17/src/rdf_concepts.c
        redland-1.0.17/src/rdf_list.c
        redland-1.0.17/src/rdf_storage.c
        redland-1.0.17/src/rdf_storage_sql.c
        redland-1.0.17/src/rdf_stream.c
        redland-1.0.17/src/rdf_parser.c
        redland-1.0.17/src/rdf_parser_raptor.c
        redland-1.0.17/src/rdf_heuristics.c
        redland-1.0.17/src/rdf_files.c
        redland-1.0.17/src/rdf_utf8.c
        redland-1.0.17/src/rdf_query.c
        redland-1.0.17/src/rdf_query_results.c
        redland-1.0.17/src/rdf_query_rasqal.c
        redland-1.0.17/src/rdf_serializer.c
        redland-1.0.17/src/rdf_serializer_raptor.c
        redland-1.0.17/src/rdf_log.c
        redland-1.0.17/src/rdf_node_common.c
        redland-1.0.17/src/rdf_statement_common.c
        redland-1.0.17/src/rdf_node.c
        redland-1.0.17/src/rdf_statement.c
        redland-1.0.17/src/redland.h
        redland-1.0.17/src/rdf_internal.h
        redland-1.0.17/src/rdf_init.h
        redland-1.0.17/src/rdf_uri.h
        redland-1.0.17/src/rdf_node.h
        redland-1.0.17/src/rdf_statement.h
        redland-1.0.17/src/rdf_concepts.h
        redland-1.0.17/src/rdf_digest.h
        redland-1.0.17/src/rdf_hash.h
        redland-1.0.17/src/rdf_types.h
        redland-1.0.17/src/rdf_model.h
        redland-1.0.17/src/rdf_iterator.h
        redland-1.0.17/src/rdf_list.h
        redland-1.0.17/src/rdf_storage.h
        redland-1.0.17/src/rdf_stream.h
        redland-1.0.17/src/rdf_parser.h
        redland-1.0.17/src/rdf_heuristics.h
        redland-1.0.17/src/rdf_files.h
        redland-1.0.17/src/rdf_utf8.h
        redland-1.0.17/src/rdf_query.h
        redland-1.0.17/src/rdf_serializer.h
        redland-1.0.17/src/rdf_log.h
        redland-1.0.17/src/rdf_concepts_internal.h
        redland-1.0.17/src/rdf_digest_internal.h
        redland-1.0.17/src/rdf_hash_internal.h
        redland-1.0.17/src/rdf_init_internal.h
        redland-1.0.17/src/rdf_iterator_internal.h
        redland-1.0.17/src/rdf_list_internal.h
        redland-1.0.17/src/rdf_log_internal.h
        redland-1.0.17/src/rdf_model_internal.h
        redland-1.0.17/src/rdf_node_internal.h
        redland-1.0.17/src/rdf_parser_internal.h
        redland-1.0.17/src/rdf_query_internal.h
        redland-1.0.17/src/rdf_raptor_internal.h
        redland-1.0.17/src/rdf_serializer_internal.h
        redland-1.0.17/src/rdf_statement_internal.h
        redland-1.0.17/src/rdf_storage_internal.h
        redland-1.0.17/src/rdf_stream_internal.h
        redland-1.0.17/src/rdf_uri_internal.h
        redland-1.0.17/src/memcmp.c
        redland-1.0.17/src/rdf_storage_list.c
        redland-1.0.17/src/rdf_storage_hashes.c
        redland-1.0.17/src/rdf_storage_trees.c
        redland-1.0.17/src/rdf_storage_file.c
        # redland-1.0.17/src/rdf_storage_tstore.c // includes <rdfsql/rdfsql.h> which is un-locatable
        # redland-1.0.17/src/rdf_storage_mysql.c // no mysql setup yet. todo
        redland-1.0.17/src/rdf_storage_sqlite.c
        redland-1.0.17/src/rdf_storage_postgresql.c
        redland-1.0.17/src/rdf_storage_virtuoso.c
        redland-1.0.17/src/rdf_query_virtuoso.c
        redland-1.0.17/src/rdf_storage_virtuoso_internal.h
        )


set(WRAPPER_SOURCES
        RedlandAPIWrapper/src/LibrdfModel.cpp
        RedlandAPIWrapper/src/LibrdfModel.h
        RedlandAPIWrapper/src/LibrdfNode.cpp
        RedlandAPIWrapper/src/LibrdfNode.h
        RedlandAPIWrapper/src/LibrdfParser.cpp
        RedlandAPIWrapper/src/LibrdfParser.h
        RedlandAPIWrapper/src/LibrdfQuery.cpp
        RedlandAPIWrapper/src/LibrdfQuery.h
        RedlandAPIWrapper/src/LibrdfQueryResults.cpp
        RedlandAPIWrapper/src/LibrdfQueryResults.h
        RedlandAPIWrapper/src/LibrdfSerializer.cpp
        RedlandAPIWrapper/src/LibrdfSerializer.h
        RedlandAPIWrapper/src/LibrdfStatement.cpp
        RedlandAPIWrapper/src/LibrdfStatement.h
        RedlandAPIWrapper/src/LibrdfStorage.cpp
        RedlandAPIWrapper/src/LibrdfStorage.h
        RedlandAPIWrapper/src/LibrdfStream.cpp
        RedlandAPIWrapper/src/LibrdfStream.h
        RedlandAPIWrapper/src/LibrdfUri.cpp
        RedlandAPIWrapper/src/LibrdfUri.h
        RedlandAPIWrapper/src/RaptorIOStream.cpp
        RedlandAPIWrapper/src/RaptorIOStream.h
        RedlandAPIWrapper/src/RedlandAPIWrapper.h
        RedlandAPIWrapper/src/World.cpp
        RedlandAPIWrapper/src/World.h
        RedlandAPIWrapper/src/LibrdfException.h
        )


#######################################################
#   Build the library static
#
add_library(redland-combined STATIC
        ${RAPTOR_SOURCES}
        ${RASQAL_SOURCES}
        ${LIBRDF_SOURCES}
        ${WRAPPER_SOURCES}
        )

target_include_directories(redland-combined PUBLIC
        #raptor include dirs
        BEFORE raptor2-2.0.15/librdfa
        raptor2-2.0.15/src
        rasqal-0.9.33/src
        rasqal-0.9.33/libmtwist
        rasqal-0.9.33/libsv
        rasqal-0.9.33/getopt
        redland-1.0.17/src
        RedlandAPIWrapper

        ${LIBXML2_INCLUDE_DIR}
        ${LIBSBML_DEPS_INCLUDE_DIR}
        ${LIBSBML_INCLUDE_DIR}
        ${ZLIB_INCLUDE_DIR}
        ${ZIPPER_INCLUDE_DIR}
        ${LIBCOMBINE_INCLUDE_DIR}
        ${REDLAND_INCLUDE_DIR}
        ${RASQAL_INCLUDE_DIR}
        ${RAPTOR2_INCLUDE_DIR}
        ${RAPTOR2_INCLUDE_DIR}
        ${RASQAL_INCLUDE_DIR}
        ${LIBPQ_INCLUDE_DIR}
        )

target_link_libraries(redland-combined PUBLIC
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
        idn2
        ${CMAKE_DL_LIBS} # defines libdl libraries
        # additional rasqal libraries
        pcre
        mhash
        gcrypt
        uuid
        #        c
        ossp
        #        xml2
        mpfr
        #        m
        )


set_target_properties(redland-combined PROPERTIES PUBLIC_HEADER
        raptor2-2.0.15/src/raptor2.h
        rasqal-0.9.33/src/rasqal.h
        redland-1.0.17/src/librdf.h
        )

INSTALL(
        TARGETS redland-combined
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)


