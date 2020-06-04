//
// Created by Ciaran on 6/4/2020.
//

#include <iostream>
#include "librdf.h"

std::string str(const std::string &format, const std::string &base) {
    librdf_world *world = librdf_new_world();
    librdf_storage *storage = librdf_new_storage(world, "memory", "SemsimMemoryStore", nullptr);
    librdf_model *model = librdf_new_model(world, storage, nullptr);

    librdf_node *subject = librdf_new_node_from_uri_string(world, (const unsigned char *) "https://subject.com");
    librdf_node *predicate = librdf_new_node_from_uri_string(world, (const unsigned char *) "https://predicate.com#apredicate");
    librdf_node *resource = librdf_new_node_from_uri_string(world, (const unsigned char *) "https://resource.com");
    librdf_statement *statement = librdf_new_statement_from_nodes(world, subject, predicate, resource);

    librdf_model_add_statement(model, statement);
    librdf_serializer *serializer = librdf_new_serializer(world, format.c_str(), nullptr, nullptr);

    // deal with namespaces
    librdf_uri* ns_uri = librdf_new_uri(world, (const unsigned char*)"https://predicate.com#");
    librdf_serializer_set_namespace(serializer, ns_uri, "pred");
    librdf_free_uri(ns_uri);

    // do the serializing
    librdf_uri *base_uri = librdf_new_uri(world, (const unsigned char *) base.c_str());
    unsigned char *string = librdf_serializer_serialize_model_to_string(serializer, base_uri, model);
    std::string str = (const char *) string;

    // free up resources
    free(string);
    librdf_free_statement(statement);
    librdf_free_serializer(serializer);
    librdf_free_uri(base_uri);
    librdf_free_model(model);
    librdf_free_storage(storage);
    librdf_free_world(world);
    return str;

}

void test_rdfxml(){
    // valgrind doesn't complain
    std::string rdfxml = str("rdfxml", "rdfxml_example_base");
    std::cout << rdfxml << std::endl;
}

void test_dot(){
    // valgrind doesn't complain
    std::string dot = str("dot", "dot_example_base");
    std::cout << dot << std::endl;}

int main() {
//    test_rdfxml()
    test_dot();
}
