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

    virtual SBMLDocument *strModel() = 0;

};

class SBMLAnnotated : SBMLModel {
public:
    SBMLAnnotated() = default;

    SBMLDocument *strModel() override {
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

    SBMLDocument *strModel() override {
        SBMLDocument *doc;
        Model *sbml_model_ptr;
        std::string xml;

        doc = new SBMLDocument(3, 2);
        sbml_model_ptr = doc->createModel("TestModelNotAnnotated");

        // create a compartment to represent the cytosol
        Compartment *comp = sbml_model_ptr->createCompartment();
        comp->setId("cytosol");
        comp->setMetaId("cytosol");
        comp->setSize(1);
        comp->setConstant(true);

        // create molar unit
        UnitDefinition *unitdef = sbml_model_ptr->createUnitDefinition();
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

        Species *X = sbml_model_ptr->createSpecies();
        X->setCompartment("cytosol");
        X->setId("X");
        X->setMetaId("Meta00001");
        X->setInitialConcentration(10);
        X->setUnits("molar");
        X->setHasOnlySubstanceUnits(false);
        X->setConstant(false);
        X->setBoundaryCondition(false);

        Species *Y = sbml_model_ptr->createSpecies();
        Y->setCompartment("cytosol");
        Y->setId("Y");
        Y->setInitialConcentration(20);
        Y->setUnits("molar");
        Y->setHasOnlySubstanceUnits(false);
        Y->setConstant(false);
        Y->setBoundaryCondition(false);

        Species *Z = sbml_model_ptr->createSpecies();
        Z->setCompartment("cytosol");
        Z->setId("Y");
        Z->setInitialConcentration(15);
        Z->setUnits("molar");
        Z->setHasOnlySubstanceUnits(false);
        Z->setConstant(false);
        Z->setBoundaryCondition(false);

        Reaction *x2y = sbml_model_ptr->createReaction();
        x2y->setId("X2Y");
        x2y->setReversible(false);

        // add Y as product for reaction
        SpeciesReference *sr = x2y->createProduct();
        sr->setSpecies("Y");
        sr->setConstant(false);

        KineticLaw *k = x2y->createKineticLaw();
        Parameter *p = k->createParameter();
        p->setId("kx2y");
        p->setValue(1);
        k->setMath(SBML_parseL3FormulaWithModel("x*kx2y", sbml_model_ptr));

        Reaction *y2z = sbml_model_ptr->createReaction();
        y2z->setId("y2z");
        y2z->setReversible(false);

        // add Y as product for reaction
        SpeciesReference *sr2 = y2z->createProduct();
        sr2->setSpecies("Z");
        sr2->setConstant(false);

        KineticLaw *k2 = y2z->createKineticLaw();
        Parameter *p2 = k->createParameter();
        p2->setId("ky2z");
        p2->setValue(1);
        k2->setMath(SBML_parseL3FormulaWithModel("y*ky2z", sbml_model_ptr));
        return doc;
    }
};


class SBMLFactory {
public:

    static SBMLDocument *getSBMLDocument(ModelType modelType) {
        if (modelType == SBML_ANNOTATED)
            return SBMLAnnotated().strModel();
        else if (modelType == SBML_NOT_ANNOTATED)
            return SBMLNotAnnotated().strModel();
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
