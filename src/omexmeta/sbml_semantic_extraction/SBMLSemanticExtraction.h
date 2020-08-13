//
// Created by Ciaran on 11/08/2020.
//

#ifndef LIBOMEXMETA_SBMLSEMANTICEXTRACTION_H
#define LIBOMEXMETA_SBMLSEMANTICEXTRACTION_H

#include "iostream"
#include "omexmeta/Editor.h"
#include "omexmeta/RDF.h"
#include "omexmeta/sbml_semantic_extraction/ElementExtractor.h"

namespace omexmeta {

    class RDF; // forward declaration

    class SBMLSemanticExtraction {

        RDF *rdf_;

        Editor editor_;

        std::string sbml_string_;
    public:
        SBMLSemanticExtraction(RDF* rdf, const std::string & sbml_string);

        SBMLSemanticExtraction(RDF rdf, const std::string & sbml_string);

        void extractSpeciesCompartmentSemantics();

        void extractProcessesFromReactions();
    };
}












#endif //LIBOMEXMETA_SBMLSEMANTICEXTRACTION_H
