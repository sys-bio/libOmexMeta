//
// Created by Ciaran on 4/15/2020.
//

#include "semsim/Editor.h"

#include <utility>

namespace semsim {
    Editor::Editor(const std::string &xml, SemsimXmlType type,
                   const LibrdfModel &model, NamespaceMap &nsmap)
            : model_(model), namespaces_(nsmap) {
        XmlAssistantPtr xmlAssistantPtr = SemsimXmlAssistantFactory::generate(xml, type);
        std::pair<std::string, std::vector<std::string>> xml_and_metaids = xmlAssistantPtr->addMetaIds();
        xml_ = xml_and_metaids.first;
        //todo create a structure mapping metaids to more useful information for the user.
        metaids_ = xml_and_metaids.second;
    }

    const std::string &Editor::getXml() const {
        return xml_;
    }

    const std::vector<std::string> &Editor::getMetaids() const {
        return metaids_;
    }

    const std::unordered_map<std::string, std::string> &Editor::getNamespaces() const {
        return namespaces_;
    }

    void Editor::setNamespaces(const std::unordered_map<std::string, std::string> &namespaces) {
        namespaces_ = namespaces;
    }

    librdf_model *Editor::getModel() const {
        return model_.get();
    }

    void Editor::checkValidMetaid(const std::string &metaid) {
        if (std::find(metaids_.begin(), metaids_.end(), metaid) == metaids_.end()) {
            std::ostringstream err;
            err << "std::invalid_argument(): metaid \"" << metaid << "\" not found. ";
            err << "These are your available metaids: ";
            for (auto &it: metaids_) {
                err << it << ", ";
            }
            throw std::invalid_argument(err.str());
        }
    }


    const NestedTriples &Editor::getTripleList() const {
        return triple_list_;
    }

    void Editor::extractNamespacesFromTriplesVector(Triples triples) {
        for (auto &triple: triples) {
            addNamespaceFromAnnotation(triple.getPredicateStr());
        }
    }


    void Editor::toRDF() {
        for (auto &annot : triple_list_) {
            for (auto &triple : annot) {
                //todo add get namespace to triple
                model_.addStatement(triple.getStatement());
            }
        }
    }


    void Editor::addNamespace(const std::string& ns, std::string prefix) {
        namespaces_[ns] = std::move(prefix);
    }


    void Editor::addSingleAnnotation(
            Subject subject, PredicatePtr predicate_ptr,
            Resource resource) {
        if (!predicate_ptr) {
            std::ostringstream err;
            err << __FILE__ << ":" << __LINE__ << ":PredicatePtr argument is null" << std::endl;
            throw NullPointerException(err.str());
        }
        checkValidMetaid(subject.str());
        Triple triple(subject, predicate_ptr, resource);
        Triples vec;
        vec.push_back(triple);
        triple_list_.push_back(vec);
        for (auto &it : namespaces_) {
            std::cout << "ns: " << it.first << ": " << it.second << std::endl;
        }
        namespaces_[predicate_ptr->getNamespace()] = predicate_ptr->getPrefix();
    }

    void Editor::addSingleAnnotation(SingularAnnotation &singularAnnotation) {
        checkValidMetaid(singularAnnotation.getSubjectStr());
        Triples vec;
        vec.push_back(singularAnnotation);
        triple_list_.push_back(vec);
        addNamespaceFromAnnotation(singularAnnotation.getPredicateStr());

    }

    void Editor::addNamespaceFromAnnotation(const std::string &predicate_string) {
        // store namespaces for later
        std::string ns = SemsimUtils::getNamespaceFromUri(predicate_string);
        if (Predicate::namespaceKnown(ns)) {
            namespaces_[ns] = Predicate::namespaceMap()[ns];
        };
    }

    void Editor::addAnnotationFromNestedTriples(const NestedTriples &tripleList) {
        for (auto &inner_triple_vec: tripleList) {
            extractNamespacesFromTriplesVector(inner_triple_vec);
            triple_list_.push_back(inner_triple_vec);
        }
    }

    void Editor::addAnnotationFromTriples(const Triples &triples) {
        extractNamespacesFromTriplesVector(triples);
        triple_list_.push_back(triples);
    }


    void Editor::addCompositeAnnotation(const PhysicalPhenomenonPtr& phenomenonPtr) {
        Triples triples = phenomenonPtr->toTriples();
        extractNamespacesFromTriplesVector(triples);
        for (auto &triple : triples) {
            model_.addStatement(triple.getStatement());
        }
        /*
         * Should I remove the triples here?
         */
        triples.freeTriples();
    }

    void Editor::addPhysicalEntity(const PhysicalEntity &physicalEntity) {
        if (!physicalEntity.getAbout().getNode()) {
            throw NullPointerException(
                    "NullPointerException: Editor::addPhysicalEntity() physicalEntity::subject_ (i.e. about) node is empty");
        }
        checkValidMetaid(physicalEntity.getAbout().str());
        addCompositeAnnotation(
                std::make_shared<PhysicalEntity>(physicalEntity)
        );
    }

    void Editor::addPhysicalProcess(const PhysicalProcess &physicalProcess) {
        if (!physicalProcess.getAbout().getNode()) {
            throw NullPointerException(
                    "NullPointerException: Editor::addPhysicalProcess() PhysicalProcess::subject_ (i.e. about) node is empty");
        }
        checkValidMetaid(physicalProcess.getAbout().str());
        addCompositeAnnotation(
                std::make_shared<PhysicalProcess>(physicalProcess)
        );

    }

    void Editor::addPhysicalForce(const PhysicalForce &physicalForce) {
        if (!physicalForce.getAbout().getNode()) {
            throw NullPointerException(
                    "NullPointerException: Editor::addPhysicalForce() PhysicalForce::subject_ (i.e. about) node is empty");
        }
        checkValidMetaid(physicalForce.getAbout().str());
        addCompositeAnnotation(
                std::make_shared<PhysicalForce>(physicalForce)
        );

    }


    void Editor::removeSingleAnnotation(const SingularAnnotation &singularAnnotation) const {
        model_.removeStatement(singularAnnotation.getStatement());
    }

    void Editor::removePhysicalEntity(PhysicalEntity physicalEntity) const {
        /*
         * This strategy causes a seg sault because toTriples
         * passes ownership of the nodes inside statement to the Triples
         * object which has its own destructor while removeStatement also
         * calls the destructor for librdf_stement.
         *
         * 1) make LibrdfStatement free up resources itself,
         * rather than having a destructor.
         *
         * 2) do not use the toTriples here. Instead try to reconstruct
         * the physical entity.
         *
         * option 1 is probably better
         */

        const Triples& triples = physicalEntity.toTriples();
        for (int i=0; i< triples.size(); i++) {
//            std::cout << triples[i].str("ntriples") << std::endl;
            model_.removeStatement(triples[i].getStatement());
        }
    }

    void Editor::removePhysicalProcess(PhysicalProcess physicalProcess) {
        for (auto &it: physicalProcess.toTriples()) {
            model_.removeStatement(it.getStatement());
        }
    }

    void Editor::removePhysicalForce(PhysicalForce physicalForce) {
        for (auto &it: physicalForce.toTriples()) {
            model_.removeStatement(it.getStatement());
        }
    }

    PhysicalEntity Editor::createPhysicalEntity() {
        return PhysicalEntity(model_.get());
    }

    PhysicalForce Editor::createPhysicalForce() {
        return PhysicalForce(model_.get());
    }

    PhysicalProcess Editor::createPhysicalProcess() {
        return PhysicalProcess(model_.get());
    }


}









