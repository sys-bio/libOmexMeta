//
// Created by Ciaran on 5/20/2020.
//

#include "_TripleWriter.h"

semsim::TripleWriter::TripleWriter(semsim::Triple triple, const std::string &base_uri, std::string format) {
    // when creating a writer from a Triple, we just create a locally scoped rdf model and storage
    LibrdfWorld world;
    LibrdfStorage storage = world.newStorage("memory", "triple_store");
    if (!storage) {
        throw LibRDFException("Writer::Writer: storage not created");
    }
    LibrdfModel model = world.newModel(storage);
    if (!model) {
        throw LibRDFException("Writer::Writer: model not created");
    }
    // add statements to the model
    model.addStatement(triple.toStatement());
    std::cout << triple.getResource().str() << std::endl;

    // initialize the writer
    init(world, model, base_uri, std::move(format));

    // determine whether we recognize the namespace and add it if we do.
    std::string ns = triple.getPredicatePtr()->getNamespace();
    if (triple.getPredicatePtr()->namespaceKnown(ns)) {
        registerNamespace(ns, Predicate::prefix_map()[ns]);
    }
}

semsim::TripleWriter::TripleWriter(semsim::Triples triples, const std::string &base_uri, std::string format) {
    // when creating a writer from a Triple, we just create a locally scoped rdf model and storage
    LibrdfWorld world;
    LibrdfStorage storage = world.newStorage("memory", "triple_store");
    if (!storage) {
        throw LibRDFException("Writer::Writer: storage not created");
    }
    LibrdfModel model = world.newModel(storage);
    if (!model) {
        throw LibRDFException("Writer::Writer: model not created");
    }

    init(world, model, base_uri, std::move(format));
    for (auto &triple : triples) {
        model.addStatement(triple.toStatement());
        std::string ns = triple.getPredicatePtr()->getNamespace();
        if (triple.getPredicatePtr()->namespaceKnown(ns)) {
            registerNamespace(ns, Predicate::prefix_map()[triple.getPredicatePtr()->getNamespace()]);
        }
    }
}
