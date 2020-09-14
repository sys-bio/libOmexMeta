#include "librdf.h"


int main(){
    librdf_world *world = librdf_new_world();
    librdf_storage *storage = librdf_new_storage(world, "memory", "SemsimMemoryStore", nullptr);
    librdf_model *model = librdf_new_model(world, storage, nullptr);

    librdf_statement *statement = librdf_new_statement_from_nodes(
            world,
            librdf_new_node_from_uri_string(
                    world, (const unsigned char *) "https://subject.com"),
            librdf_new_node_from_uri_string(
                    world,
                    (const unsigned char *) "https://predicate.com"),
            librdf_new_node_from_uri_string(
                    world,
                    (const unsigned char *) "https://resource.com")
    );

    librdf_model_add_statement(model, statement);
    librdf_free_statement(statement);
    librdf_free_storage(storage);
    librdf_free_model(model);
    librdf_free_world(world);
    return 0;
}