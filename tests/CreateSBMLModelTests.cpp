//
// Created by Ciaran on 3/28/2020.
//

# include "gtest/gtest.h"
# include <semsim/SemSim.h>
# include "sbml/SBMLTypes.h"
# include <iostream>

using namespace semsim;
using namespace libsbml;

class SBMLImporterTests : public ::testing::Test {
protected:
    SBMLDocument *doc;
    Model *m;
    std::string xml;

    void SetUp() override {

        doc = new SBMLDocument(3, 2);
        m = doc->createModel("beta_cell_model");

        // create a compartment to represent the cytosol
        Compartment *comp = m->createCompartment();
        comp->setId("cytosol");
        comp->setMetaId("cytosol");
        comp->setSize(1);
        comp->setConstant(true);

        // add a CV term for the cytosol
        auto *cv_cytosol = new CVTerm();
        cv_cytosol->setQualifierType(BIOLOGICAL_QUALIFIER);
        cv_cytosol->setBiologicalQualifierType(BQB_IS);
        cv_cytosol->addResource(GO::get(5829).getURI().encode());
        comp->addCVTerm(cv_cytosol);

        UnitDefinition *unitdef = m->createUnitDefinition();
        unitdef->setId("molar");

        Unit *unit = unitdef->createUnit();
        unit->setKind(UNIT_KIND_MOLE);
        unit->setExponent(1);
        unit->setMultiplier(1);
        unit->setScale(1);

        unit = unitdef->createUnit();
        unit->setKind(UNIT_KIND_LITRE);
        unit->setExponent(-1);
        unit->setMultiplier(1);
        unit->setScale(1);

        // create the species for glucose
        Species *s = m->createSpecies();
        s->setCompartment("cytosol");
        s->setId("glucose");
        s->setMetaId("glucose");
        s->setInitialConcentration(0);
        s->setUnits("molar");
        s->setHasOnlySubstanceUnits(false);
        s->setConstant(false);
        s->setBoundaryCondition(false);

        // add a CV term to glucose
        auto *cv_glucose = new CVTerm();
        cv_glucose->setQualifierType(BIOLOGICAL_QUALIFIER);
        cv_glucose->setBiologicalQualifierType(BQB_IS);
        cv_glucose->addResource(CHEBI::get(17234).getURI().encode());
        s->addCVTerm(cv_glucose);

        // create import reaction for glucose
        Reaction *reaction = m->createReaction();
        reaction->setId("glucose_import");
        reaction->setReversible(false);

        SpeciesReference *sr = reaction->createProduct();
        sr->setSpecies("glucose");
        sr->setConstant(false);
        KineticLaw *k = reaction->createKineticLaw();
        Parameter *p = k->createParameter();
        p->setId("glucose_import_rate");
        p->setValue(1);
        k->setMath(SBML_parseL3FormulaWithModel("glucose_import_rate", m));
        SBMLWriter sbml_writer;
        xml = sbml_writer.writeSBMLToString(doc);
    }

//    void TearDown() override {
//        delete doc;
//        delete m;
//    }
};


TEST_F(SBMLImporterTests, test1) {
    // create SBML model
//     importing the model into libSemSim will automatically
//     add metaids for any annotatable SBML elements that lack them
    SBMLImporter importer(doc);
    SBMLModel &model = importer.getSBMLModel();
    std::string rdf = model.getRDF("./mymodel.xml", "turtle");
    const char* actual = rdf.c_str();
    const char* expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
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
//
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