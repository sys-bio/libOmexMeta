//
// Created by Ciaran on 3/29/2020.
//

#ifndef LIBSEMGEN_CellMLFACTORY_H
#define LIBSEMGEN_CellMLFACTORY_H

#include <stdexcept>
#include <string>
#include <utility>


enum CellMLModelType {
    CELLML_TOY,
    CELLML_TOY_EXTENDED,
    CELLML_TOY_NO_METAIDS
};

/*
 * Abstract class implemented by all CellML models
 */
class CellMLModel {
public:
    CellMLModel() = default;

    virtual std::string str() = 0;
};

class CellMLToy : CellMLModel {
public:
    CellMLToy() = default;

    std::string str() override {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
               "<model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://bime.uw.edu/semsim/#\" xmlns:dc=\"https://dublincore.org/specifications/dublin-core/dcmi-terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">\n"
               "  <component name=\"main\">\n"
               "    <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />\n"
               "    <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />\n"
               "    <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />\n"
               "  </component>\n"
               "</model>";
    }
};

class CellMLToyNoMetaIds : CellMLModel {
public:
    CellMLToyNoMetaIds() = default;

    std::string str() override {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
               "<model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://bime.uw.edu/semsim/#\" xmlns:dc=\"https://dublincore.org/specifications/dublin-core/dcmi-terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">\n"
               "  <component name=\"main\">\n"
               "    <variable initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />\n"
               "    <variable initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />\n"
               "    <variable initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />\n"
               "  </component>\n"
               "</model>";
    }
};

class CellMLToyExtended : CellMLModel {
public:
    CellMLToyExtended() = default;

    std::string str() override {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
               "<model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://bime.uw.edu/semsim/#\" xmlns:dc=\"https://dublincore.org/specifications/dublin-core/dcmi-terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">\n"
               "  <component name=\"main\">\n"
               "    <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />\n"
               "    <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />\n"
               "    <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />\n"
               "    <variable cmeta:id=\"main.entity1\" initial_value=\"1\" name=\"entity1\" units=\"dimensionless\" />\n"
               "    <variable cmeta:id=\"main.entity2\" initial_value=\"1\" name=\"entity2\" units=\"dimensionless\" />\n"
               "    <variable cmeta:id=\"main.entity3\" initial_value=\"1\" name=\"entity3\" units=\"dimensionless\" />\n"
               "  </component>\n"
               "</model>";
    }
};


class CellMLFactory {
public:
    static std::string getCellML(CellMLModelType modelType) {
        if (modelType == CELLML_TOY)
            return CellMLToy().str();
        else if (modelType == CELLML_TOY_EXTENDED)
            return CellMLToyExtended().str();
        else if (modelType == CELLML_TOY_NO_METAIDS)
            return CellMLToyNoMetaIds().str();
        else {
            throw std::invalid_argument("CellMLFactory error: ModelType is not a valid argument.");
        }
    }
};


#endif//LIBSEMGEN_CellMLFACTORY_H
