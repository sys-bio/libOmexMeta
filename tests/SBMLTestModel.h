//
// Created by Ciaran on 3/29/2020.
//

#ifndef LIBSEMGEN_SBMLTESTMODEL_H
#define LIBSEMGEN_SBMLTESTMODEL_H

#include <utility>

#include "sbml/SBMLTypes.h"
#include "semsim/SemSim.h"


/*
 * We could pass in as parameters things like number of reactions, species
 * events, existing annotations and we could include a random component to this as well.
 * This is overkill just for a set of models for testing libsemsim with, but might be useful
 * in the broader context
 */




using namespace libsbml;

class ITestModel {
public:
    ITestModel() = default;

    virtual std::string getModelString() = 0;
};

class SBMLAnnotated : ITestModel {
public:
    SBMLAnnotated() = default;

    std::string getModelString() override {
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
        cv_cytosol->addResource(semsim::GO::get(5829).getURI().encode());
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
        cv_glucose->addResource(semsim::CHEBI::get(17234).getURI().encode());
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
        return xml;
    }
};

class SBMLNotAnnotated : ITestModel {
public:
    SBMLNotAnnotated() = default;

    std::string getModelString() override {
        return "";
    }

};

class CellMLNotAnnotated : ITestModel {
public:
    CellMLNotAnnotated() = default;

    std::string getModelString() {
        return "";

    }


};

class CellMLAnnotated : ITestModel {
public:
    CellMLAnnotated() = default;

    std::string getModelString() override {
        return "";

    }

};

class ModelFactory {
private:
    std::string modelType;
public:
    explicit ModelFactory(std::string modelType) : modelType(std::move(modelType)) {};

    std::string getModel() {
        if (modelType == "sbml_annotated")
            return SBMLAnnotated().getModelString();
        else if (modelType == "sbml_not_annotated")
            return SBMLNotAnnotated().getModelString();
        else if (modelType == "cellml_annotated")
            return CellMLAnnotated().getModelString();
        else if (modelType == "cellml_not_annotated")
            return CellMLNotAnnotated().getModelString();
        else {
            throw std::invalid_argument("\"" + modelType + "\" is not a valid argument.");
        }
    }
};



#endif //LIBSEMGEN_SBMLTESTMODEL_H
