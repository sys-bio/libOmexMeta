/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * rdf_storage.h - RDF Storage Factory and Storage interfaces and definitions
 *
 * Copyright (C) 2000-2008, David Beckett http://www.dajobe.org/
 * Copyright (C) 2000-2005, University of Bristol, UK http://www.bristol.ac.uk/
 * 
 * This package is Free Software and part of Redland http://librdf.org/
 * 
 * It is licensed under the following three licenses as alternatives:
 *   1. GNU Lesser General Public License (LGPL) V2.1 or any newer version
 *   2. GNU General Public License (GPL) V2 or any newer version
 *   3. Apache License, V2.0 or any newer version
 * 
 * You may not use this file except in compliance with at least one of
 * the above three licenses.
 * 
 * See LICENSE.html or LICENSE.txt at the top of this package for the
 * complete terms and further detail along with the license texts for
 * the licenses in COPYING.LIB, COPYING and LICENSE-2.0.txt respectively.
 * 
 * 
 */


#ifndef LIBRDF_STORAGE_H
#define LIBRDF_STORAGE_H

#include "rdf_config.h"
#include "rdf_storage_module.h"

/*
 * Commented out by ciaran welsh on 17/06/2020
 */
#ifdef LIBRDF_INTERNAL
#include <rdf_storage_internal.h>
#endif
/*
 * if favour of this instead, in order to try and get the database
 * storages working.
 */
//#include <rdf_storage_internal.h>

#ifdef __cplusplus
extern "C" {
#endif


/** A storage object */
struct librdf_storage_s {
    librdf_world *world;

    /* usage count of this instance
     * Used by other redland classes such as model, iterator, stream
     * via  librdf_storage_add_reference librdf_storage_remove_reference
     * The usage count of storage after construction is 1.
     */
    int usage;

    librdf_model *model;
    void *instance;
    int index_contexts;
    struct librdf_storage_factory_s *factory;
};

/* class methods */
REDLAND_EXPORT
int librdf_storage_register_factory(librdf_world *world, const char *name, const char *label,
                                    void (*factory)(librdf_storage_factory *));

REDLAND_EXPORT
int librdf_storage_enumerate(librdf_world *world, const unsigned int counter, const char **name, const char **label);


/* constructor */
REDLAND_EXPORT
librdf_storage *
librdf_new_storage(librdf_world *world, const char *storage_name, const char *name, const char *options_string);
REDLAND_EXPORT
librdf_storage *
librdf_new_storage_with_options(librdf_world *world, const char *storage_name, const char *name, librdf_hash *options);
REDLAND_EXPORT
librdf_storage *librdf_new_storage_from_storage(librdf_storage *old_storage);
REDLAND_EXPORT
librdf_storage *librdf_new_storage_from_factory(librdf_world *world, librdf_storage_factory *factory, const char *name,
                                                librdf_hash *options);

/* destructor */
REDLAND_EXPORT
void librdf_free_storage(librdf_storage *storage);


/* methods */
REDLAND_EXPORT
void librdf_storage_add_reference(librdf_storage *storage);
REDLAND_EXPORT
void librdf_storage_remove_reference(librdf_storage *storage);

REDLAND_EXPORT
void librdf_storage_set_instance(librdf_storage *storage, librdf_storage_instance instance);
REDLAND_EXPORT
librdf_storage_instance librdf_storage_get_instance(librdf_storage *storage);

REDLAND_EXPORT
librdf_world *librdf_storage_get_world(librdf_storage *storage);

REDLAND_EXPORT
int librdf_storage_open(librdf_storage *storage, librdf_model *model);
REDLAND_EXPORT
int librdf_storage_close(librdf_storage *storage);

REDLAND_EXPORT
int librdf_storage_size(librdf_storage *storage);

REDLAND_EXPORT
int librdf_storage_add_statement(librdf_storage *storage, librdf_statement *statement);
REDLAND_EXPORT
int librdf_storage_add_statements(librdf_storage *storage, librdf_stream *statement_stream);
REDLAND_EXPORT
int librdf_storage_remove_statement(librdf_storage *storage, librdf_statement *statement);
REDLAND_EXPORT
int librdf_storage_contains_statement(librdf_storage *storage, librdf_statement *statement);
REDLAND_EXPORT
librdf_stream *librdf_storage_serialise(librdf_storage *storage);
REDLAND_EXPORT
librdf_stream *librdf_storage_find_statements(librdf_storage *storage, librdf_statement *statement);
REDLAND_EXPORT
librdf_stream *librdf_storage_find_statements_with_options(librdf_storage *storage, librdf_statement *statement,
                                                           librdf_node *context_node, librdf_hash *options);
REDLAND_EXPORT
librdf_iterator *librdf_storage_get_sources(librdf_storage *storage, librdf_node *arc, librdf_node *target);
REDLAND_EXPORT
librdf_iterator *librdf_storage_get_arcs(librdf_storage *storage, librdf_node *source, librdf_node *target);
REDLAND_EXPORT
librdf_iterator *librdf_storage_get_targets(librdf_storage *storage, librdf_node *source, librdf_node *arc);


/* return list of properties to/from a node */
REDLAND_EXPORT
librdf_iterator *librdf_storage_get_arcs_in(librdf_storage *storage, librdf_node *node);
REDLAND_EXPORT
librdf_iterator *librdf_storage_get_arcs_out(librdf_storage *storage, librdf_node *node);

/* check for [node, property, ?] */
REDLAND_EXPORT
int librdf_storage_has_arc_in(librdf_storage *storage, librdf_node *node, librdf_node *property);
/* check for [?, property, node] */
REDLAND_EXPORT
int librdf_storage_has_arc_out(librdf_storage *storage, librdf_node *node, librdf_node *property);

/* context methods */
REDLAND_EXPORT
int librdf_storage_context_add_statement(librdf_storage *storage, librdf_node *context, librdf_statement *statement);
REDLAND_EXPORT
int librdf_storage_context_add_statements(librdf_storage *storage, librdf_node *context, librdf_stream *stream);
REDLAND_EXPORT
int librdf_storage_context_remove_statement(librdf_storage *storage, librdf_node *context, librdf_statement *statement);
REDLAND_EXPORT
int librdf_storage_context_remove_statements(librdf_storage *storage, librdf_node *context);
REDLAND_EXPORT
librdf_stream *librdf_storage_context_as_stream(librdf_storage *storage, librdf_node *context);
REDLAND_EXPORT REDLAND_DEPRECATED
librdf_stream *librdf_storage_context_serialise(librdf_storage *storage, librdf_node *context);

/* querying methods */
REDLAND_EXPORT
int librdf_storage_supports_query(librdf_storage *storage, librdf_query *query);
REDLAND_EXPORT
librdf_query_results *librdf_storage_query_execute(librdf_storage *storage, librdf_query *query);

/* synchronise a storage to the backing store */
REDLAND_EXPORT
int librdf_storage_sync(librdf_storage *storage);

/* find statements in a given context */
REDLAND_EXPORT
librdf_stream *librdf_storage_find_statements_in_context(librdf_storage *storage, librdf_statement *statement,
                                                         librdf_node *context_node);

REDLAND_EXPORT
librdf_iterator *librdf_storage_get_contexts(librdf_storage *storage);

/* features */
REDLAND_EXPORT
librdf_node *librdf_storage_get_feature(librdf_storage *storage, librdf_uri *feature);
REDLAND_EXPORT
int librdf_storage_set_feature(librdf_storage *storage, librdf_uri *feature, librdf_node *value);

REDLAND_EXPORT
int librdf_storage_transaction_start(librdf_storage *storage);
REDLAND_EXPORT
int librdf_storage_transaction_start_with_handle(librdf_storage *storage, void *handle);
REDLAND_EXPORT
int librdf_storage_transaction_commit(librdf_storage *storage);
REDLAND_EXPORT
int librdf_storage_transaction_rollback(librdf_storage *storage);
REDLAND_EXPORT
void *librdf_storage_transaction_get_handle(librdf_storage *storage);

#ifdef __cplusplus
}
#endif

#endif
