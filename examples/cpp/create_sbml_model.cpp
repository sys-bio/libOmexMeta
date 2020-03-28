# include <semsim/SemSim.h>

# include "sbml/SBMLTypes.h"

# include <iostream>
# include "combine/combinearchive.h"

using namespace semsim;

int main() {
    CombineArchive::CombineArchive archive;

    // create SBML model
//    libsbml::SBMLDocument *d =
//            new libsbml::SBMLDocument(3, 2);
//    libsbml::Model *m = d->createModel();
//    m->setId("beta_cell_model");
//
//    // create a compartment to represent the cytosol
//    libsbml::Compartment *comp = m->createCompartment();
//    comp->setId("cytosol");
//    comp->setMetaId("cytosol");
//    comp->setSize(1);
//    comp->setConstant(true);
//
//    // add a CV term for the cytosol
//    libsbml::CVTerm *cv_cytosol = new libsbml::CVTerm();
//    cv_cytosol->setQualifierType(libsbml::BIOLOGICAL_QUALIFIER);
//    cv_cytosol->setBiologicalQualifierType(libsbml::BQB_IS);
//    cv_cytosol->addResource(GO::get(5829).getURI().encode());
//    comp->addCVTerm(cv_cytosol);
//
//    libsbml::UnitDefinition *unitdef = m->createUnitDefinition();
//    unitdef->setId("molar");
//
//    libsbml::Unit *unit = unitdef->createUnit();
//    unit->setKind(libsbml::UNIT_KIND_MOLE);
//    unit->setExponent(1);
//    unit->setMultiplier(1);
//    unit->setScale(1);
//
//    unit = unitdef->createUnit();
//    unit->setKind(libsbml::UNIT_KIND_LITRE);
//    unit->setExponent(-1);
//    unit->setMultiplier(1);
//    unit->setScale(1);
//
//    // create the species for glucose
//    libsbml::Species *s = m->createSpecies();
//    s->setCompartment("cytosol");
//    s->setId("glucose");
//    s->setMetaId("glucose");
//    s->setInitialConcentration(0);
//    s->setUnits("molar");
//    s->setHasOnlySubstanceUnits(false);
//    s->setConstant(false);
//    s->setBoundaryCondition(false);
//
//    // add a CV term to glucose
//    libsbml::CVTerm *cv_glucose = new libsbml::CVTerm();
//    cv_glucose->setQualifierType(libsbml::BIOLOGICAL_QUALIFIER);
//    cv_glucose->setBiologicalQualifierType(libsbml::BQB_IS);
//    cv_glucose->addResource(CHEBI::get(17234).getURI().encode());
//    s->addCVTerm(cv_glucose);
//
//    // create import reaction for glucose
//    libsbml::Reaction *reaction = m->createReaction();
//    reaction->setId("glucose_import");
//    reaction->setReversible(false);
//
//    libsbml::SpeciesReference *sr = reaction->createProduct();
//    sr->setSpecies("glucose");
//    sr->setConstant(false);
//    libsbml::KineticLaw *k = reaction->createKineticLaw();
//    libsbml::Parameter *p = k->createParameter();
//    p->setId("glucose_import_rate");
//    p->setValue(1);
//    k->setMath(libsbml::SBML_parseL3FormulaWithModel("glucose_import_rate", m));
//    // alternate way to set formula
//    // libsbml:: ASTNode* a =
//    //   new libsbml:: ASTNode(libsbml:: AST_NAME);
//    // a->setName("glucose_import_rate");
//    // k->setMath(a);
//
//    libsbml::SBMLWriter sbml_writer;
//
//    std::cerr << "**********************************************************\n";
//    std::cerr << "SBML output:\n";
//    std::cerr << "**********************************************************\n\n";
//
//    std::cerr << sbml_writer.writeSBMLToString(d) << "\n";
//
//    // importing the model into libSemSim will automatically
//    // add metaids for any annotatable SBML elements that lack them
//    SBMLImporter importer(d);
//    SBMLModel &model = importer.getSBMLModel();
//
//    std::cerr << "**********************************************************\n";
//
//    std::cerr << "RDF serialization of annotations:\n";
//    std::cerr << "**********************************************************\n\n";
//
//    std::cerr << model.getRDF("./mymodel.xml", "turtle") << "\n";
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
//    std::cerr << "**********************************************************\n";
//    std::cerr << "RDF serialization with cell type annotation:\n";
//    std::cerr << "**********************************************************\n\n";
//
//    std::cerr << model.getRDF("./mymodel.xml", "turtle") << "\n";
//
//    std::cerr << "**********************************************************\n";
//    std::cerr << "Humanized version of the annotation information\n";
//    std::cerr << "(ontology terms replaced by human-readable names):\n";
//    std::cerr << "**********************************************************\n\n";
//
//    std::cerr << model.humanize() << "\n";
//
//    exportToOmex(model, "/tmp/combine.omex");

    return 0;
}
