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


const semsim::TripleList &semsim::Editor::getTripleList() const {
    return triple_list_;
}

void semsim::Editor::toRDF(RDF &rdf) {
    for (auto &annot : triple_list_) {
        for (auto &triple : annot) {
            librdf_statement *stmt = triple.toStatement();
            librdf_model_add_statement(model_, stmt);
        }
    }

}


//void semsim::Editor::addAnnotation(std::string metaid, semsim::PredicatePtr predicateptr, const std::string &resource) {
//    checkValidMetaid(metaid);
//    Triple triple(world_, std::move(metaid), *predicateptr, resource);
//    std::vector<Triple> vec = {triple};
//    triple_list_.push_back(vec);
//}
//
//void semsim::Editor::addAnnotation(const std::string &metaid, const std::string &is_version_of_resource,
//                                   const std::string &is_property_of_resource,
//                                   const std::string &is_resource, const std::string &is_part_of_resource) {
//    Triple triple1(metaid, BiomodelsQualifier("isVersionOf"), is_version_of_resource, world_);
//    // todo put some check in to ensure that the metaid is_resource in the model
//    Triple triple2(metaid, BiomodelsQualifier("isPropertyOf"), is_property_of_resource, world_);
//    Triple triple3(is_property_of_resource, BiomodelsQualifier("is"), is_resource, world_);
//    Triple triple4(is_property_of_resource, BiomodelsQualifier("isPartOf"), is_part_of_resource, world_);
//    std::vector<Triple> triples = {triple1, triple2, triple3, triple4};
//    triple_list_.push_back(triples);
//}
//
//





















