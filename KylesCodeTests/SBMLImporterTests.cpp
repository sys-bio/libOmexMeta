//
// Created by Ciaran on 3/28/2020.
//

#include "gtest/gtest.h"
#include <semsim/SemSim.h>
#include "sbml/SBMLTypes.h"
#include <iostream>

#include "SBMLFactory.h"


class NotAnnotatedSBMLImporterTests : public ::testing::Test {
protected:
    SBMLDocument *doc;

    NotAnnotatedSBMLImporterTests()  {
        doc = semsim_test::SBMLFactory::getSBMLDocument(semsim_test::SBML_NOT_ANNOTATED);
    };
};

class AnnotatedSBMLImporterTests : public ::testing::Test {
protected:
    SBMLDocument *doc;

    AnnotatedSBMLImporterTests()  {
        doc = semsim_test::SBMLFactory::getSBMLDocument(semsim_test::SBML_ANNOTATED);
    };
};

TEST_F(NotAnnotatedSBMLImporterTests, test1){
    semsim::SBMLImporter importer(doc);

}

/*
 * importing the model into libSemSim will automatically
 * add metaids for any annotatable SBML elements that lack them
 *
 */
TEST_F(AnnotatedSBMLImporterTests, TestRDFGeneration) {
    semsim::SBMLImporter importer(doc);
    semsim::SemSimSBMLModel &model = importer.getSemSimSBMLModel();
    semsim::Url modelpath("./mymodel.xml");
    std::string rdf = model.getRDF(modelpath, "turtle");
    const char *actual = rdf.c_str();
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqb: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/SemSim#> .\n"
                           "\n"
                           "<#glucose>\n"
                           "    bqb:is <https://identifiers.org/CHEBI:17234> ;\n"
                           "    bqb:occursIn <./mymodel.xml#cytosol> .\n"
                           "\n"
                           "<#sink0>\n"
                           "    semsim:hasMultiplier \"1\" ;\n"
                           "    semsim:hasPhysicalEntityReference <./mymodel.xml#glucose> .\n"
                           "\n"
                           "<./mymodel.xml#cytosol>\n"
                           "    bqb:is <https://identifiers.org/GO:0005829> .\n"
                           "\n"
                           "<./mymodel.xml#glucose_property>\n"
                           "    bqb:isPropertyOf <#glucose> ;\n"
                           "    bqb:isVersionOf <https://identifiers.org/opb/OPB_00425> .\n"
                           "\n"
                           "<./mymodel.xml#reaction0>\n"
                           "    semsim:hasSinkParticipant <#sink0> .\n\n";
    ASSERT_STREQ(expected, actual);
}

TEST_F(AnnotatedSBMLImporterTests, TestRDFGeneration2) {
    semsim::SBMLImporter importer(doc);
    semsim::SemSimSBMLModel &model = importer.getSemSimSBMLModel();
}

//    // this isn't bad - the RDF already contains a composite annotation
//    // telling is that the species "glucose" is inside the "cytosol"
//    // we currently have "cytosolic glucose"
//    // however - what we want is "cytosolic glucose in a pancreatic beta cell"
//    // to describe this, we need to annotate the compartment (not the species!)
//    // and describe the cell type it is part of
//
//    // the compartment currently has a *singular annotation*, which can't
//    // represent membership in a "pancreatic beta cell", so we change this to
//    // a composite annotation
//    Component *c = model.getComponentForId("cytosol");
//    c->setAnnotation(c->getAnnotation().makeComposite(OPB::get(523))); // 523 is spatial volume
//    // now add a descriptor term specifying that the cytoplasm
//    // is part of a pancreatic beta cell (CL:0000169)
//    c->getCompositeAnnotation().addTerm(
//            bqb::isPartOf, // the relation (the cytoplasm *is part of* ...)
//            CL::get(169)   // the resource (pancreatic beta cell)
//    );
//
//    std::cout << "**********************************************************\n";
//    std::cout << "RDF serialization with cell type annotation:\n";
//    std::cout << "**********************************************************\n\n";
//    std::cout << model.getRDF("./mymodel.xml", "turtle") << "\n";
//    std::cout << "**********************************************************\n";
//    std::cout << "Humanized version of the annotation information\n";
//    std::cout << "(ontology terms replaced by human-readable names):\n";
//    std::cout << "**********************************************************\n\n";
//    std::cout << model.humanize() << "\n";

//    exportToOmex(model, "/tmp/combine.omex");
//};