
#######################################################################
# configure files
#
configure_file(rasqal-config.in rasqal-config)
configure_file(rasqal.h.in rasqal.h)


set(RASQAL_SOURCES
        rasqal_algebra.c
        rasqal_expr.c
        rasqal_expr_evaluate.c
        rasqal_expr_datetimes.c
        rasqal_expr_numerics.c
        rasqal_expr_strings.c
        rasqal_general.c
        rasqal_query.c
        rasqal_query_results.c
        rasqal_engine.c
        rasqal_raptor.c
        rasqal_literal.c
        rasqal_formula.c
        rasqal_graph_pattern.c
        rasqal_map.c
        rasqal_feature.c
        rasqal_result_formats.c
        rasqal_xsd_datatypes.c
        rasqal_decimal.c
        rasqal_datetime.c
        rasqal_rowsource.c
        rasqal_format_sparql_xml.c
        rasqal_variable.c
        rasqal_rowsource_empty.c
        rasqal_rowsource_union.c
        rasqal_rowsource_rowsequence.c
        rasqal_query_transform.c
        rasqal_row.c
        rasqal_engine_algebra.c
        rasqal_triples_source.c
        rasqal_rowsource_triples.c
        rasqal_rowsource_filter.c
        rasqal_rowsource_sort.c
        rasqal_engine_sort.c
        rasqal_rowsource_project.c
        rasqal_rowsource_join.c
        rasqal_rowsource_graph.c
        rasqal_rowsource_distinct.c
        rasqal_rowsource_groupby.c
        rasqal_rowsource_aggregation.c
        rasqal_rowsource_having.c
        rasqal_rowsource_slice.c
        rasqal_rowsource_bindings.c
        rasqal_rowsource_service.c
        rasqal_row_compatible.c
        rasqal_format_table.c
        rasqal_query_write.c
        rasqal_format_json.c
        rasqal_format_sv.c
        rasqal_format_html.c
        rasqal_format_rdf.c
        rasqal_rowsource_assignment.c
        rasqal_update.c
        rasqal_triple.c
        rasqal_data_graph.c
        rasqal_prefix.c
        rasqal_solution_modifier.c
        rasqal_projection.c
        rasqal_bindings.c
        rasqal_service.c
        rasqal_dataset.c
        rasqal_random.c
        rasqal_digest.c
        rasqal_iostream.c
        rasqal_regex.c
        snprintf.c
        rasqal_double.c
        rasqal_ntriples.c
        rasqal_results_compare.c
        ssort.h
        sparql_lexer.c
        sparql_lexer.h
        sparql_parser.c
        sparql_parser.h
        sparql_common.h
        strcasecmp.c
        timegm.c
        gettimeofday.c
        rasqal_sort.c
        rasqal_digest_md5.c
        rasqal_digest_sha1.c
        )

add_library(rasqal STATIC ${RASQAL_SOURCES})

message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(rasqal PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        #        ${RAPTOR2_INCLUDE_DIR}
        /mnt/d/redland/raptor2-2.0.15/install-ubuntu/include
        ${LIBSV_DIR}
        ${LIBMTWIST_DIR}
        ${GETOPT_DIR}
        )


target_link_libraries(rasqal PUBLIC
        ${RAPTOR2_STATIC_LIB}
        pcre
        mhash
        gcrypt
        uuid
        c
        ossp
        xml2
        mpfr
        m
        )

set_target_properties(rasqal PROPERTIES PUBLIC_HEADER "rasqal.h")



INSTALL(
        TARGETS rasqal
#        EXPORT Rasqal2Config
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

#INSTALL(EXPORT Rasqal2Config DESTINATION lib/cmake)







