//
// Created by Ciaran on 5/17/2020.
//


#include "World.h"

namespace semsim {

    void World::deleter::operator()(librdf_world *world) {
        if (world)
            librdf_free_world(world);
    }

    librdf_world *World::world_ = nullptr;

    librdf_world *World::getWorld() {
        if (world_ == nullptr) {
            world_ = librdf_new_world();
            librdf_world_open(world_);
        }
        return world_;
    }

    raptor_world *World::getRaptor() {
        return librdf_world_get_raptor(World::getWorld());
    }

    World::World() = default;


//    bool World::operator==(const World &rhs) const {
//        return world_.get() == rhs.world_.get();
//    }
//
//    bool World::operator!=(const World &rhs) const {
//        return !(rhs == *this);
//    }
//
//    const librdf_world_ptr &World::getWorld() const {
//        return world_;
//    }
//
//    RaptorWorld World::getRaptor() {
//        return RaptorWorld(librdf_world_get_raptor(world_.get()));
//    }
//
//    LibrdfStorage World::newStorage(const std::string &storage_name, const std::string &name,
//                                          const char *options_string) {
//
//        //todo fill these in and write verification statements for them.
//        std::vector<std::string> valid_storage_names;
//        std::vector<std::string> valid_storage;
//        std::vector<std::string> valid_options;
//
//        return LibrdfStorage(
//                librdf_new_storage(
//                        world_.get(), storage_name.c_str(), name.c_str(), options_string)
//        );
//    }
//
//    LibrdfModel World::newModel(LibrdfStorage storage, const char *options_string) {
//        librdf_model *m = librdf_new_model(world_.get(), storage.get(), options_string);
//        LibrdfModel model = LibrdfModel(m);
//        return model;
//    }
//
//    LibrdfNode World::newNodeUriString(const std::string &string) {
//        std::string identifier_dot_org = "https://identifiers.org/";
//        std::regex identifiers_regex(identifier_dot_org);
//        std::regex http_regex("^https://");
//        std::regex identifiers_org_form1("^(?!file://)(?!https://)(?!http://)([A-Za-z0-9]+)[/:]{1}(\\S*)");
//        std::regex file_regex("^file://");
//
//        std::smatch m;
//        std::string x;
//        // if we find identifiers.org form 1
//        if (std::regex_search(string, m, identifiers_org_form1)) {
//            x = identifier_dot_org + std::string(m[1]) + "/" + std::string(m[2]);
//        } else {
//            x = string;
//        }
//        return LibrdfNode(librdf_new_node_from_uri_string(
//                world_.get(), (const unsigned char *) x.c_str()));
//    }
//
//    LibrdfNode World::newNodeUri(LibrdfUri raptorUri) const {
//        return LibrdfNode(
//                librdf_new_node_from_uri(world_.get(), raptorUri.get())
//        );
//    }
//
//    LibrdfNode World::newNodeLiteral(
//            const std::string &literal, const char *xml_language, bool is_wf_xml) const {
//        return LibrdfNode(librdf_new_node_from_literal(
//                world_.get(), (const unsigned char *) literal.c_str(), xml_language, (int) is_wf_xml)
//        );
//    }
//
//    LibrdfNode World::newNodeTypedLiteral(
//            const std::string &literal,
//            const std::string &datatypeUri,
//            const char *xml_language) const {
//        std::string prefix = "http://www.w3.org/2001/XMLSchema#";
//        std::string data_type_url_tmp = std::string();
//        if (datatypeUri.rfind(prefix, 0) == 0) {
//            data_type_url_tmp = datatypeUri;
//        } else {
//            data_type_url_tmp = prefix + datatypeUri;
//        }
//
//        LibrdfUri uri = newUri(data_type_url_tmp);
//        return LibrdfNode(librdf_new_node_from_typed_literal(
//                world_.get(),
//                (const unsigned char *)
//                        literal.c_str(), xml_language, uri.get())
//        );
//    }
//
//    LibrdfNode World::newNodeBlank(const std::string &identifier) const {
//        return LibrdfNode(
//                librdf_new_node_from_blank_identifier(world_.get(), (const unsigned char *) identifier.c_str()));
//    }
//
//
//    LibrdfUri World::newUri(std::string uri_string) const {
//        return LibrdfUri(librdf_new_uri(world_.get(), (const unsigned char *) uri_string.c_str()));
//    }
//
//    LibrdfStatement
//    World::newStatementFromNodes(LibrdfNode subject, LibrdfNode predicate, LibrdfNode object) const {
//        return LibrdfStatement(librdf_new_statement_from_nodes(
//                world_.get(), subject.getNode().get(), predicate.getNode().get(), object.getNode().get())
//        );
//    }
//
//    LibrdfStatement World::newStatement() const {
//        return LibrdfStatement(librdf_new_statement(world_.get()));
//    }
//
//    librdf_world *World::get() const {
//        return world_.get();
//    }
//
//    LibrdfParser World::newParser(const char *name, std::string mime_type, std::string uri_type) {
//        librdf_uri *uri_type_;
//        const char *mime_type_;
//        if (!uri_type.empty()) {
//            uri_type_ = librdf_new_uri(world_.get(), (const unsigned char *) uri_type.c_str());
//        } else {
//            uri_type_ = nullptr;
//        }
//        if (!mime_type.empty()) {
//            mime_type_ = mime_type.c_str();
//        } else {
//            mime_type_ = nullptr;
//        }
//        librdf_parser *parser = librdf_new_parser(world_.get(), name, mime_type_, uri_type_);
//        return LibrdfParser(parser);
//    }
//
//    LibrdfSerializer World::newSerializer(const char *name, std::string mime_type, std::string uri_type) {
//        librdf_uri *uri_type_;
//        const char *mime_type_;
//        if (!uri_type.empty()) {
//            uri_type_ = librdf_new_uri(world_.get(), (const unsigned char *) uri_type.c_str());
//        } else {
//            uri_type_ = nullptr;
//        }
//        if (!mime_type.empty()) {
//            mime_type_ = mime_type.c_str();
//        } else {
//            mime_type_ = nullptr;
//        }
//        librdf_serializer *serializer = librdf_new_serializer(world_.get(), name, mime_type_, uri_type_);
//        return LibrdfSerializer(serializer);
//    }
//
//    LibrdfQuery
//    World::newQuery(std::string query, std::string query_language_name, std::string uri, std::string base_uri) {
//        const char *query_language_name_ = query_language_name.c_str();
//        auto query_ = (const unsigned char *) query.c_str();
//        librdf_uri *uri_;
//        librdf_uri *base_uri_;
//        const char *mime_type_;
//        if (!uri.empty()) {
//            uri_ = librdf_new_uri(world_.get(), (const unsigned char *) uri.c_str());
//        } else {
//            uri_ = nullptr;
//        }
//        if (!base_uri.empty()) {
//            base_uri_ = librdf_new_uri(world_.get(), (const unsigned char *) base_uri.c_str());
//        } else {
//            base_uri_ = nullptr;
//        }
//        return LibrdfQuery(librdf_new_query(world_.get(), query_language_name_, uri_, query_, base_uri_));
//    }



//    Subject World::newSubjectUri(const std::string &subject_value) {
//        return Subject(RDFURINode(newNodeUriString(subject_value)));
//    }
//
//    Subject World::newSubjectBlank(const std::string &subject_value) {
//        return Subject(RDFURINode(newNodeBlank(subject_value)));
//    }
//
//    PredicatePtr World::newPredicate(std::string namespace_, const std::string &term) {
//        return PredicateFactory(*this, namespace_, term);
//    }



}












