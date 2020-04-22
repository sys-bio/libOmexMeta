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

void semsim::Editor::toRDF() {
    for (auto &annot : triple_list_) {
        for (auto &triple : annot) {
            librdf_statement *stmt = triple.toStatement();
            librdf_model_add_statement(model_, stmt);
        }
    }

}


void
semsim::Editor::addSingleAnnotation(semsim::Subject subject, semsim::PredicatePtr predicate_ptr,
                                    semsim::Resource resource) {
    checkValidMetaid(subject.str());
    Triple triple(world_, std::move(subject), std::move(predicate_ptr), std::move(resource));
    std::vector<Triple> vec = {triple};
    triple_list_.push_back(vec);
}

void semsim::Editor::addSingleAnnotation(Triple triple) {
    std::vector<Triple> vec = {triple};
    triple_list_.push_back(vec);
}

void semsim::Editor::addAnnotation(TripleList tripleList) {
    for (auto &inner_triple_vec: tripleList) {
        triple_list_.push_back(inner_triple_vec);
    }
}

void semsim::Editor::addAnnotation(std::vector<Triple> triples) {
    triple_list_.push_back(triples);
}

std::vector<semsim::Triple> semsim::Editor::connectionTriple(
        const std::string &subject, std::string isVersionOf, std::string isPropertyOf) {
    Triple triple1(
            world_,
            Subject(world_, RDFURINode(world_, subject)),
            std::make_shared<BiomodelsQualifier>(BiomodelsQualifier(world_, "isVersionOf")),
            Resource(world_, RDFURINode(world_, std::move(isVersionOf)))
    );
    Triple triple2(
            world_,
            Subject(world_, RDFURINode(world_, subject)),
            std::make_shared<BiomodelsQualifier>(BiomodelsQualifier(world_, "isPropertyOf")),
            Resource(world_, RDFURINode(world_, std::move(isPropertyOf)))
    );
    return std::vector<Triple>({triple1, triple2});
}

std::vector<semsim::Triple> semsim::Editor::connectionTriple(
        const std::string &subject, std::string isVersionOf, std::vector<std::string> isPropertyOf) {
    std::vector<Triple> triples;
    triples.push_back(
            Triple(
                    world_,
                    Subject(world_, RDFURINode(world_, subject)),
                    std::make_shared<BiomodelsQualifier>(BiomodelsQualifier(world_, "isVersionOf")),
                    Resource(world_, RDFURINode(world_, std::move(isVersionOf)))
            )
    );
    for (auto &it : isPropertyOf) {
        triples.push_back(
                Triple(world_,
                       Subject(world_, RDFURINode(world_, subject)),
                       std::make_shared<BiomodelsQualifier>(BiomodelsQualifier(world_, "isPropertyOf")),
                       Resource(world_, RDFURINode(world_, std::move(it)))
                )
        );
    }
    return triples;
}

void semsim::Editor::addPhysicalEntityAnnotation(const std::string &subject, std::string isVersionOf,
                                                 const std::string &isPropertyOf,
                                                 semsim::Resource is, semsim::Resource isPartOf) {

    std::vector<Triple> triples = connectionTriple(subject, std::move(isVersionOf), isPropertyOf);
    Triple triple3(
            world_,
            Subject(world_, RDFURINode(world_, isPropertyOf)),
            std::make_shared<BiomodelsQualifier>(BiomodelsQualifier(world_, "is")),
            std::move(is)
    );
    Triple triple4(
            world_,
            Subject(world_, RDFURINode(world_, isPropertyOf)),
            std::make_shared<BiomodelsQualifier>(BiomodelsQualifier(world_, "isPartOf")),
            std::move(isPartOf)
    );
    triples.push_back(triple3);
    triples.push_back(triple4);
    triple_list_.push_back(triples);
}

void semsim::Editor::addPhysicalProcessAnnotation(
        std::string subject, std::string isVersionOf, std::string isPropertyOf,
        std::vector<ParticipantPtr> participants) {
    std::vector<Triple> triples = connectionTriple(subject, isVersionOf, isPropertyOf);
    for (auto &participant : participants) {
        for (auto &triple : participant->toTriples()) {
            triples.push_back(triple);
        }
    }
    triple_list_.push_back(triples);
}
























