//
// Created by Ciaran on 4/15/2020.
//

#include "Editor.h"
#include "RDF.h"
#include "librdf.h"

#include <utility>

semsim::Editor::Editor(const std::string &xml, XmlAssistantType type, librdf_world *world, librdf_model *model)
        : world_(world), model_(model) {
    semsim::XmlAssistantPtr xmlAssistantPtr = XmlAssistantFactory::generate(xml, type);
    std::pair<std::string, std::vector<std::string>> xml_and_metaids = xmlAssistantPtr->addMetaIds();
    xml_ = xml_and_metaids.first;
    //todo create a structure mapping metaids to more useful information for the user.
    metaids_ = xml_and_metaids.second;
}

const std::string &semsim::Editor::getXml() const {
    return xml_;
}

const std::vector<std::string> &semsim::Editor::getMetaids() const {
    return metaids_;
}

void semsim::Editor::checkValidMetaid(const std::string &metaid) {
    if (std::find(metaids_.begin(), metaids_.end(), metaid) == metaids_.end()) {
        std::ostringstream err;
        err << __FILE__ << ":" << __LINE__ << ": metaid \"" << metaid << "\" not found. ";
        err << "These are your available metaids: ";
        for (auto &it: metaids_) {
            err << it << ", ";
        }
        throw std::invalid_argument(err.str());
    }
}

void semsim::Editor::addAnnotation(std::string metaid, semsim::PredicatePtr predicateptr, const std::string &resource) {
    checkValidMetaid(metaid);
    Triple triple(std::move(metaid), *predicateptr, resource);
    std::vector<Triple> vec = {triple};
    triple_list_.push_back(vec);
}

const semsim::TripleList &semsim::Editor::getTripleList() const {
    return triple_list_;
}

void semsim::Editor::toRDF(RDF &rdf) {
    for (auto &annot : triple_list_) {
        for (auto &tple : annot) {
            librdf_statement *stmt = librdf_new_statement_from_nodes(world_,
                                                                     librdf_new_node_from_uri(
                                                                             world_,
                                                                             librdf_new_uri(
                                                                                     world_,
                                                                                     (const unsigned char *) tple.getSubject().getMetaId().c_str())),
                                                                     librdf_new_node_from_uri(
                                                                             world_,
                                                                             librdf_new_uri(
                                                                                     world_,
                                                                                     (const unsigned char *) tple.getPredicate()->getUri().str().c_str())),
                                                                     librdf_new_node_from_uri(
                                                                             world_,
                                                                             librdf_new_uri(
                                                                                     world_,
                                                                                     (const unsigned char *) tple.getResource().build().c_str()))
            );
            librdf_model_add_statement(model_, stmt);
        }
    }

}























