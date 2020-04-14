//
// Created by Ciaran on 3/29/2020.
//

#ifndef LIBSEMGEN_SBMLFACTORY_H
#define LIBSEMGEN_SBMLFACTORY_H

#include <utility>

#include "sbml/SBMLTypes.h"
#include "semsim/SemSim.h"

using namespace libsbml;


enum ModelType {
    SBML_ANNOTATED,
    SBML_NOT_ANNOTATED,
    SBML_BIOMD0000000695
};

/*
 * Abstract class implemented by all SBML models
 */
class SBMLModel {
public:
    SBMLModel() = default;

    virtual SBMLDocument *buildModel() = 0;

};

class SBMLAnnotated : SBMLModel {
public:
    SBMLAnnotated() = default;

    SBMLDocument *buildModel() override {
        SBMLDocument *doc;
        Model *m;
        std::string xml;

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
//            cv_cytosol->addResource(semsim::GO::get(5829).getURI().str());
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
//            cv_glucose->addResource(semsim::CHEBI::get(17234).getURI().str());
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
        return doc;
    }
};

class SBMLNotAnnotated : SBMLModel {
public:
    SBMLNotAnnotated() = default;

    SBMLDocument *buildModel() override {
        SBMLDocument *doc;
        Model *m;
        std::string xml;

        doc = new SBMLDocument(3, 2);
        m = doc->createModel("beta_cell_model");

        // create a compartment to represent the cytosol
        Compartment *comp = m->createCompartment();
        comp->setId("cytosol");
        comp->setMetaId("cytosol");
        comp->setSize(1);
        comp->setConstant(true);

        // create molar unit
        UnitDefinition *unitdef = m->createUnitDefinition();
        unitdef->setId("molar");
        Unit *unit = unitdef->createUnit();
        unit->setKind(UNIT_KIND_MOLE);
        unit->setExponent(1);
        unit->setMultiplier(1);
        unit->setScale(1);

        // create litre unit
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
        s->setInitialConcentration(10);
        s->setUnits("molar");
        s->setHasOnlySubstanceUnits(false);
        s->setConstant(false);
        s->setBoundaryCondition(false);

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
        return doc;
    }
};


class SBMLFactory {
public:

    static SBMLDocument *getSBMLDocument(ModelType modelType) {
        if (modelType == SBML_ANNOTATED)
            return SBMLAnnotated().buildModel();
        else if (modelType == SBML_NOT_ANNOTATED)
            return SBMLNotAnnotated().buildModel();
//            else if (modelType == SBML_BIOMD0000000695)
            //Download https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000695.3?filename=BIOMD0000000695_url.xml
//                SBMLModel::curlGet();
        else {
            throw std::invalid_argument("ModelType is not a valid argument.");
        }
    }

    static std::string getModelStr(ModelType modelType) {
        SBMLWriter writer;
        SBMLDocument *doc = getSBMLDocument(modelType);
        return writer.writeSBMLToString(doc);
    }
};


#endif //LIBSEMGEN_SBMLFACTORY_H
