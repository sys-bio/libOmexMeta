//
// Created by Ciaran on 5/17/2020.
//

#include <iostream>
#include <memory>
#include "LibrdfWorld.h"
#include "LibrdfStorage.h"
#include "semsim/SemsimUtils.h"

namespace semsim {

    LibrdfWorld::LibrdfWorld() {
        librdf_world *world_tmp = librdf_new_world();
        librdf_world_open(world_tmp);
        world_ = std::make_shared<librdf_world *>(world_tmp);
    }

    LibrdfWorld::~LibrdfWorld() {
        if (world_.use_count() == 1) {
            librdf_free_world(*world_);
        }
    };

    LibrdfWorld::LibrdfWorld(const LibrdfWorld &librdfWorld) {
        if (world_) {
            librdf_free_world(*world_); // get rid of whats alreday there before we copy librdfWorld.world_
        }
        world_ = librdfWorld.world_;
    }

    LibrdfWorld::LibrdfWorld(LibrdfWorld &&librdfWorld) noexcept {
        if (world_)
            librdf_free_world(*world_);
        world_ = std::move(librdfWorld.world_);
    }

    LibrdfWorld &LibrdfWorld::operator=(const LibrdfWorld &librdfWorld) {
        if (this != &librdfWorld) {
            if (world_)
                librdf_free_world(*world_);
            this->world_ = librdfWorld.world_;
        }
        return *this;
    }

    LibrdfWorld &LibrdfWorld::operator=(LibrdfWorld &&librdfWorld) noexcept {
        if (this != &librdfWorld) {
            if (world_)
                librdf_free_world(*world_);
            this->world_ = std::move(librdfWorld.world_);
        }
        return *this;
    }

    RaptorWorld LibrdfWorld::getRaptor() {
        raptor_world *raptor_world_ptr = librdf_world_get_raptor(*world_);
        RaptorWorld raptorWorld(raptor_world_ptr);
        return raptorWorld;
    }

    std::shared_ptr<LibrdfWorld> LibrdfWorld::getWorld() const {
        return world_;
    }

    bool LibrdfWorld::operator==(const LibrdfWorld &rhs) const {
        return getWorld() == rhs.getWorld();
    }

    bool LibrdfWorld::operator!=(const LibrdfWorld &rhs) const {
        return !(rhs == *this);
    }

    LibrdfStorage LibrdfWorld::newStorage(const std::string &storage_name, const std::string &name,
                                          const std::string &options_string) {

        //todo fill these in and write verification statements for them.
        std::vector<std::string> valid_storage_names;
        std::vector<std::string> valid_storage;
        std::vector<std::string> valid_options;

        LibrdfStorage storage = librdf_new_storage(
                *world_, storage_name.c_str(), name.c_str(), options_string.c_str());
        LibrdfStorage librdfStorage(storage);
        return librdfStorage;
    }

    LibrdfModel LibrdfWorld::newModel(const LibrdfStorage &storage, const std::string &options_string) {
        LibrdfModel model = librdf_new_model(*world_, *storage.getStorage(), options_string.c_str());
        LibrdfModel librdfModel(model);
        return librdfModel;
    }

    LibrdfNode LibrdfWorld::newNodeUriString(const std::string &string) {
        LibrdfNode node = librdf_new_node_from_uri_string(*world_, (const unsigned char *) string.c_str());
        return LibrdfNode(node);
    }

    LibrdfNode LibrdfWorld::newNodeUri(const LibrdfUri &raptorUri) {
        LibrdfNode node = librdf_new_node_from_uri(*world_, *raptorUri.getRaptorUri());
        return LibrdfNode(node);
    }

    LibrdfNode LibrdfWorld::newNodeLiteral(
            const std::string &literal, const char *xml_language, bool is_wf_xml) {
        LibrdfNode node = librdf_new_node_from_literal(
                *world_, (const unsigned char *) literal.c_str(), xml_language, (int) is_wf_xml);
        return LibrdfNode(node);
    }

    LibrdfNode LibrdfWorld::newNodeTypedLiteral(
            const std::string &literal,
            const std::string &datatypeUri,
            const char *xml_language) {
        std::string prefix = "http://www.w3.org/2001/XMLSchema#";
        std::string data_type_url_tmp = std::string();
        if (datatypeUri.rfind(prefix, 0) == 0) {
            data_type_url_tmp = datatypeUri;
        } else {
            data_type_url_tmp = prefix + datatypeUri;
        }

        LibrdfUri uri = newUri(data_type_url_tmp);
        LibrdfNode node = librdf_new_node_from_typed_literal(
                *world_, (const unsigned char *) literal.c_str(), xml_language, *uri.getRaptorUri());
        return LibrdfNode(node);
    }

    LibrdfNode LibrdfWorld::newNodeBlank(const std::string &identifier) {
        LibrdfNode node = librdf_new_node_from_blank_identifier(*world_, (const unsigned char *) identifier.c_str());
        return LibrdfNode(node);
    }


    LibrdfUri LibrdfWorld::newUri(const std::string &uri_string) {
        raptor_uri *uri = librdf_new_uri(*world_, (const unsigned char *) uri_string.c_str());
        return LibrdfUri(uri);
    }


}












