//
// Created by Ciaran on 4/15/2020.
//

#include "omexmeta/Editor.h"

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

    int Editor::size() const {
        return model_.size();
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


    void Editor::extractNamespacesFromTriplesVector(Triples &triples) {
        /*
         * Note: if this oesn't work, move the logic of this function
         * into where its needed. Since its only used once, we
         * do not need a specialized function
         */
        for (int i = 0; i < triples.size(); i++) {
            // create new reference to triple at i
            Triple triple = triples[i];
            addNamespaceFromAnnotation(triple.getPredicateStr());
            // remember to free the new reference (should still exist but
            // internal raptor reference count will decrease)
            triple.freeStatement();
        }
    }

    void Editor::extractNamespacesFromTriplesVector(PhysicalPhenomenon* pp) {
        // here we create our own localized Triples object
        // and deplete it during the while loop. This
        // is preferable to passing in a Triples object
        // as argument because that would take copies and
        // mess with cleaning up the triples later.
        Triples triples = pp->toTriples();
        while(!triples.isEmpty()){
            Triple triple = triples.pop_front();
            addNamespaceFromAnnotation(triple.getPredicateStr());
            triple.freeStatement();
        }
    }


    void Editor::addNamespace(const std::string &ns, std::string prefix) {
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
        model_.addStatement(triple);
        triple.freeStatement();
        namespaces_[predicate_ptr->getNamespace()] = predicate_ptr->getPrefix();
    }

    void Editor::addSingleAnnotation(SingularAnnotation &singularAnnotation) {
        checkValidMetaid(singularAnnotation.getSubjectStr());
        addNamespaceFromAnnotation(singularAnnotation.getPredicateStr());
        model_.addStatement(singularAnnotation);
//        singularAnnotation.freeStatement();
    }

    void Editor::addNamespaceFromAnnotation(const std::string &predicate_string) {
        // store namespaces for later
        std::string ns = SemsimUtils::getNamespaceFromUri(predicate_string);
        if (Predicate::namespaceKnown(ns)) {
            namespaces_[ns] = Predicate::namespaceMap()[ns];
        };
    }

    void Editor::addCompositeAnnotation(PhysicalPhenomenon *phenomenonPtr) {
//        extractNamespacesFromTriplesVector(phenomenonPtr);
        Triples triples = phenomenonPtr->toTriples();
        while (!triples.isEmpty()) {
            // remove a Triple off the front of triples
            Triple triple = triples.pop_front();
            // collect the namespace from the triple
            addNamespaceFromAnnotation(triple.getPredicateStr());
            // add to the model
            model_.addStatement(triple.getStatement());
            // remember to free it.
            triple.freeStatement();
        }

    }

    void Editor::addPhysicalEntity(PhysicalEntity &physicalEntity) {
        if (physicalEntity.getAbout().empty()) {
            throw NullPointerException(
                    "NullPointerException: Editor::addPhysicalEntity() physicalEntity::subject_ (i.e. about) node is empty");
        }
        checkValidMetaid(physicalEntity.getAbout());
        addCompositeAnnotation(&physicalEntity);
    }

    void Editor::addPhysicalProcess(const PhysicalProcess &physicalProcess) {
        if (physicalProcess.getAbout().empty()) {
            throw NullPointerException(
                    "NullPointerException: Editor::addPhysicalProcess() PhysicalProcess::subject_ (i.e. about) node is empty");
        }
        checkValidMetaid(physicalProcess.getAbout());
        /*
         * object slicing???
         */
        addCompositeAnnotation((PhysicalPhenomenon *) &physicalProcess);

    }

    void Editor::addPhysicalForce(const PhysicalForce &physicalForce) {
        if (physicalForce.getAbout().empty()) {
            throw NullPointerException(
                    "NullPointerException: Editor::addPhysicalForce() PhysicalForce::subject_ (i.e. about) node is empty");
        }
        checkValidMetaid(physicalForce.getAbout());
        addCompositeAnnotation((PhysicalPhenomenon *) &physicalForce);

    }


    void Editor::removeSingleAnnotation(const SingularAnnotation &singularAnnotation) const {
        librdf_statement *stmt = singularAnnotation.getStatement();
        model_.removeStatement(stmt);
    }

    void Editor::removePhysicalEntity(PhysicalEntity &physicalEntity) {
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

        Triples triples = physicalEntity.toTriples();

        while (!triples.isEmpty()) {
            Triple triple = triples.pop();
//            std::cout << triples[i].str("ntriples") << std::endl;
            model_.removeStatement(triple.getStatement());
//            triple.freeStatement();

        }
//        triples.freeTriples(); // seg fault
    }

//
//    void Editor::removePhysicalProcess(PhysicalProcess physicalProcess) {
//        for (auto &it: physicalProcess.toTriples()) {
//            model_.removeStatement(it.getStatement());
//        }
//    }
//
    void Editor::removePhysicalForce(PhysicalForce &physicalForce) const {
        /*
         * Can I manipulate the count to get this done? ? ?
         *  - No, if a uri is used elsewhere, we need to keep it.
         * Where is the statement being copied? ? ?
         */
        int count = 0;
        for (auto &it: physicalForce.toTriples()) {
            std::cout << "count: " << count << ": " << it.str("ntriples", "base")
            << ", usage count: " << it.get()->usage
            << ", Subject usage: " << it.getSubject()->usage
            << ", Predicate usage: " << it.getPredicate()->usage
            << ", resource usage: " << it.getResource()->usage
            << "\n" << std::endl;
            librdf_statement* triple = it.getStatement();
            model_.removeStatement(triple);
            count++;
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









