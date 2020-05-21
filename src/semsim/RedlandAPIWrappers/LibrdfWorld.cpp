//
// Created by Ciaran on 5/17/2020.
//


#include "LibrdfWorld.h"

namespace semsim {
    typedef std::shared_ptr<librdf_world> world_ptr;

    LibrdfWorld::LibrdfWorld() {
        world_ = world_ptr(librdf_new_world(), librdf_free_world);
        librdf_world_open(world_.get());
    }

    bool LibrdfWorld::operator==(const LibrdfWorld &rhs) const {
        return world_.get() == rhs.world_.get();
    }

    bool LibrdfWorld::operator!=(const LibrdfWorld &rhs) const {
        return !(rhs == *this);
    }

    const librdf_world_ptr &LibrdfWorld::getWorld() const {
        return world_;
    }

    RaptorWorld LibrdfWorld::getRaptor() {
        return RaptorWorld(librdf_world_get_raptor(world_.get()));
    }

    LibrdfStorage LibrdfWorld::newStorage(const std::string &storage_name, const std::string &name,
                                          const char *options_string) {

        //todo fill these in and write verification statements for them.
        std::vector<std::string> valid_storage_names;
        std::vector<std::string> valid_storage;
        std::vector<std::string> valid_options;

        return LibrdfStorage(
                librdf_new_storage(
                        world_.get(), storage_name.c_str(), name.c_str(), options_string)
        );
    }

    LibrdfModel LibrdfWorld::newModel(LibrdfStorage storage, const char *options_string) {
        librdf_model *m = librdf_new_model(world_.get(), storage.get(), options_string);
        LibrdfModel model = LibrdfModel(m);
        return model;
    }

    LibrdfNode LibrdfWorld::newNodeUriString(const std::string &string) {
        std::string identifier_dot_org = "https://identifiers.org/";
        std::regex identifiers_regex(identifier_dot_org);
        std::regex http_regex("^https://");
        std::regex identifiers_org_form1("^(?!file://)(?!https://)(?!http://)([A-Za-z0-9]+)[/:]{1}(\\S*)");
        std::regex file_regex("^file://");

        std::smatch m;
        std::string x;
        // if we find identifiers.org form 1
        if (std::regex_search(string, m, identifiers_org_form1)) {
            x = identifier_dot_org + std::string(m[1]) + "/" + std::string(m[2]);
        } else {
            x = string;
        }
        return LibrdfNode(librdf_new_node_from_uri_string(
                world_.get(), (const unsigned char *) x.c_str()));
    }

    LibrdfNode LibrdfWorld::newNodeUri(LibrdfUri raptorUri) const {
        return LibrdfNode(
                librdf_new_node_from_uri(world_.get(), raptorUri.get())
        );
    }

    LibrdfNode LibrdfWorld::newNodeLiteral(
            const std::string &literal, const char *xml_language, bool is_wf_xml) const {
        return LibrdfNode(librdf_new_node_from_literal(
                world_.get(), (const unsigned char *) literal.c_str(), xml_language, (int) is_wf_xml)
        );
    }

    LibrdfNode LibrdfWorld::newNodeTypedLiteral(
            const std::string &literal,
            const std::string &datatypeUri,
            const char *xml_language) const {
        std::string prefix = "http://www.w3.org/2001/XMLSchema#";
        std::string data_type_url_tmp = std::string();
        if (datatypeUri.rfind(prefix, 0) == 0) {
            data_type_url_tmp = datatypeUri;
        } else {
            data_type_url_tmp = prefix + datatypeUri;
        }

        LibrdfUri uri = newUri(data_type_url_tmp);
        return LibrdfNode(librdf_new_node_from_typed_literal(
                world_.get(),
                (const unsigned char *)
                        literal.c_str(), xml_language, uri.get())
        );
    }

    LibrdfNode LibrdfWorld::newNodeBlank(const std::string &identifier) const {
        return LibrdfNode(
                librdf_new_node_from_blank_identifier(world_.get(), (const unsigned char *) identifier.c_str()));
    }


    LibrdfUri LibrdfWorld::newUri(std::string uri_string) const {
        return LibrdfUri(librdf_new_uri(world_.get(), (const unsigned char *) uri_string.c_str()));
    }

    LibrdfStatement
    LibrdfWorld::newStatementFromNodes(LibrdfNode subject, LibrdfNode predicate, LibrdfNode object) const {
        return LibrdfStatement(librdf_new_statement_from_nodes(
                world_.get(), subject.getNode().get(), predicate.getNode().get(), object.getNode().get())
        );
    }

    librdf_world *LibrdfWorld::get() {
        return world_.get();
    }

//    Subject LibrdfWorld::newSubjectUri(const std::string &subject_value) {
//        return Subject(RDFURINode(newNodeUriString(subject_value)));
//    }
//
//    Subject LibrdfWorld::newSubjectBlank(const std::string &subject_value) {
//        return Subject(RDFURINode(newNodeBlank(subject_value)));
//    }
//
//    PredicatePtr LibrdfWorld::newPredicate(std::string namespace_, const std::string &term) {
//        return PredicateFactory(*this, namespace_, term);
//    }


}












