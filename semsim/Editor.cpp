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
            librdf_statement *stmt;
            if (tple.getResource().isLiteral()) {
                stmt = librdf_new_statement_from_nodes(world_,
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
                                                       librdf_new_node_from_literal(
                                                               world_,
                                                               (const unsigned char *) tple.getResource().str().c_str(),
                                                               nullptr, 0
                                                       )
                                                       //todo what is this xml_language argument? What difference does it make
                                                       // does it cause the rdf:Bag problem? What is id_wf_xml? How does this
                                                       // impact output?

                                                       // todo note: the is_wf_xml flag DOES make a different to
                                                       //  xml output.
                );
            } else {
                stmt = librdf_new_statement_from_nodes(world_,
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
                                                                       (const unsigned char *) tple.getResource().str().c_str()))
                );
            }
            librdf_model_add_statement(model_, stmt);
        }
    }

}

void semsim::Editor::addAnnotation(std::string metaid, std::string is_version_of_resource, std::string is_property_of_resource,
                                   std::string is_resource, std::string is_part_of_resource) {
    Triple triple1(metaid, BiomodelsQualifier("isVersionOf"), is_version_of_resource);
    // todo put some check in to ensure that the metaid is_resource in the model
    Triple triple2(metaid, BiomodelsQualifier("isPropertyOf"), is_property_of_resource);
    Triple triple3(is_property_of_resource, BiomodelsQualifier("is"), is_property_of_resource);
    Triple triple4(is_property_of_resource, BiomodelsQualifier("isPartOf"), is_part_of_resource);
    std::vector<Triple> triples = {triple1, triple2, triple3, triple4};
    TripleList list;
    list.push_back(triples);



}























