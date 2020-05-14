//
// Created by Ciaran on 4/15/2020.
//

#include "Editor.h"
#include "RDF.h"
#include "librdf.h"

#include <utility>
#include "SemsimUtils.h"

semsim::Editor::Editor(const std::string &xml, XmlAssistantType type,
                       librdf_world *world, librdf_model *model, NamespaceMap &nsmap)
        : world_(world), model_(model), namespaces_(nsmap) {
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

const std::unordered_map<std::string, std::string> &semsim::Editor::getNamespaces() const {
    return namespaces_;
}

void semsim::Editor::setNamespaces(const std::unordered_map<std::string, std::string> &namespaces) {
    namespaces_ = namespaces;
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


const semsim::NestedTriples &semsim::Editor::getTripleList() const {
    return triple_list_;
}

void semsim::Editor::extractNamespacesFromTriplesVector(Triples triples) {
    for (auto &triple: triples) {
        namespaces_[triple.getPredicatePtr()->getNamespace()] = triple.getPredicatePtr()->getPrefix();
    }
}


void semsim::Editor::toRDF() {
    for (auto &annot : triple_list_) {
        for (auto &triple : annot) {
            librdf_statement *stmt = triple.toStatement();
            //todo add get namespace to triple
            librdf_model_add_statement(model_, stmt);
        }
    }
}


void semsim::Editor::addNamespace(std::string ns, std::string prefix) {
    namespaces_[ns] = prefix;
}


void semsim::Editor::addSingleAnnotation(
        semsim::Subject subject, semsim::PredicatePtr predicate_ptr,
        semsim::Resource resource) {
    if (!predicate_ptr){
        std::ostringstream err;
        err << __FILE__<<":"<<__LINE__<<":PredicatePtr argument is null"<<std::endl;
        throw NullPointerException(err.str());
    }
    checkValidMetaid(subject.str());
    Triple triple(world_, std::move(subject), predicate_ptr, std::move(resource));
    Triples vec = {triple};
    triple_list_.push_back(vec);
    for (auto &it : namespaces_){
        std::cout << "ns: " << it.first << ": " << it.second << std::endl;
    }
    namespaces_[predicate_ptr->getNamespace()] = predicate_ptr->getPrefix();
}

void semsim::Editor::addSingleAnnotation(semsim::SingularAnnotation singularAnnotation) {
    Triples vec = {singularAnnotation};
    triple_list_.push_back(vec);
    namespaces_[singularAnnotation.getPredicatePtr()->getNamespace()] = singularAnnotation.getPredicatePtr()->getPrefix();

}

void semsim::Editor::addAnnotationFromNestedTriples(NestedTriples tripleList) {
    for (auto &inner_triple_vec: tripleList) {
        extractNamespacesFromTriplesVector(inner_triple_vec);
        triple_list_.push_back(inner_triple_vec);
    }
}

void semsim::Editor::addAnnotationFromTriples(Triples triples) {
    extractNamespacesFromTriplesVector(triples);
    triple_list_.push_back(triples);

}


void semsim::Editor::addCompositeAnnotation(semsim::PhysicalPhenomenonPtr phenomenonPtr) {
    Triples triples = phenomenonPtr->toTriples();
    extractNamespacesFromTriplesVector(triples);
    for (auto &triple : triples ) {
        librdf_model_add_statement(model_, triple.toStatement());
    }
}
























