
set(SOURCES
        rdf_init.c
        rdf_raptor.c
        rdf_uri.c
        rdf_digest.c
        rdf_hash.c
        rdf_hash_cursor.c
        rdf_hash_memory.c
        rdf_model.c
        rdf_model_storage.c
        rdf_iterator.c
        rdf_concepts.c
        rdf_list.c
        rdf_storage.c
        rdf_storage_sql.c
        rdf_stream.c
        rdf_parser.c
        rdf_parser_raptor.c
        rdf_heuristics.c
        rdf_files.c
        rdf_utf8.c
        rdf_query.c
        rdf_query_results.c
        rdf_query_rasqal.c
        rdf_serializer.c
        rdf_serializer_raptor.c
        rdf_log.c
        rdf_node_common.c
        rdf_statement_common.c
        rdf_node.c
        rdf_statement.c
        redland.h
        rdf_internal.h
        rdf_init.h
        rdf_uri.h
        rdf_node.h
        rdf_statement.h
        rdf_concepts.h
        rdf_digest.h
        rdf_hash.h
        rdf_types.h
        rdf_model.h
        rdf_iterator.h
        rdf_list.h
        rdf_storage.h
        rdf_stream.h
        rdf_parser.h
        rdf_heuristics.h
        rdf_files.h
        rdf_utf8.h
        rdf_query.h
        rdf_serializer.h
        rdf_log.h
        rdf_concepts_internal.h
        rdf_digest_internal.h
        rdf_hash_internal.h
        rdf_init_internal.h
        rdf_iterator_internal.h
        rdf_list_internal.h
        rdf_log_internal.h
        rdf_model_internal.h
        rdf_node_internal.h
        rdf_parser_internal.h
        rdf_query_internal.h
        rdf_raptor_internal.h
        rdf_serializer_internal.h
        rdf_statement_internal.h
        rdf_storage_internal.h
        rdf_stream_internal.h
        rdf_uri_internal.h
        memcmp.c
        rdf_storage_list.c
        rdf_storage_hashes.c
        rdf_storage_trees.c
        rdf_storage_file.c
        #    rdf_storage_tstore.c // includes <rdfsql/rdfsql.h> which is un-locatable
#        rdf_storage_mysql.c // no mysql setup yet. todo
        rdf_storage_sqlite.c
        rdf_storage_postgresql.c
        rdf_storage_virtuoso.c
        rdf_query_virtuoso.c
        rdf_storage_virtuoso_internal.h
        )

add_library(librdf STATIC ${SOURCES})

target_include_directories(librdf PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${RAPTOR2_INCLUDE_DIR}
        ${RASQAL_INCLUDE_DIR}
        ${LIBPQ_INCLUDE_DIR}
        )

target_link_libraries(librdf PUBLIC
        ${RAPTOR2_STATIC_LIB}
        ${RASQAL_STATIC_LIB}
        ${LIBPQ_STATIC_LIBRARY}
        )
















