#include "SemSimTypes.h"

namespace semsim {
    // SemSimTypes SemSimTypes::SEMSIM_COMPONENT("SEMSIM_COMPONENT", InnerEnum::SEMSIM_COMPONENT, "SemSim Component", RDFNamespace::SEMSIM.getNamespaceAsString() + "SemSim_component", "", "");
    // SemSimTypes SemSimTypes::MODEL("MODE", InnerEnum::MODEL, "SemSim Mode", RDFNamespace::SEMSIM.getNamespaceAsString() + "SemSim_Mode", "", "SemSim:SemSim_Mode");
    // SemSimTypes SemSimTypes::SUBMODEL("SUBMODE", InnerEnum::SUBMODEL, "Submode", RDFNamespace::SEMSIM.getNamespaceAsString() + "Submode", "", "SemSim:Submode");
    // SemSimTypes SemSimTypes::PHYSICAL_MODEL_COMPONENT("PHYSICAL_MODEL_COMPONENT", InnerEnum::PHYSICAL_MODEL_COMPONENT, "Physical Model Component", RDFNamespace::SEMSIM.getNamespaceAsString() + "Physical_model_component", "", "");
    // SemSimTypes SemSimTypes::PHYSICAL_PROPERTY("PHYSICAL_PROPERTY", InnerEnum::PHYSICAL_PROPERTY, "Singular Physical Property", RDFNamespace::SEMSIM.getNamespaceAsString() + "Physical_property", "A reference term that precisely defines a biophysical property simulated in the model.", "SemSim:Physical_property");
    // SemSimTypes SemSimTypes::PHYSICAL_PROPERTY_IN_COMPOSITE("PHYSICAL_PROPERTY_IN_COMPOSITE", InnerEnum::PHYSICAL_PROPERTY_IN_COMPOSITE, "Physical Property for a Composite", RDFNamespace::SEMSIM.getNamespaceAsString() + "Physical_property_in_composite", "A reference term that defines the physical property component of a composite annotation.", "");
    // SemSimTypes SemSimTypes::REFERENCE_PHYSICAL_ENTITY("REFERENCE_PHYSICAL_ENTITY", InnerEnum::REFERENCE_PHYSICAL_ENTITY, "Reference Physical Entity", RDFNamespace::SEMSIM.getNamespaceAsString() + "Reference_physical_entity", "A reference term that defines a physical entity represented in the model.", "SemSim:Reference_physical_entity");
    // SemSimTypes SemSimTypes::PHYSICAL_DEPENDENCY("PHYSICAL_DEPENDENCY", InnerEnum::PHYSICAL_DEPENDENCY, "Physical Dependency", RDFNamespace::SEMSIM.getNamespaceAsString() + "Physical_dependency", "", "");
    // SemSimTypes SemSimTypes::REFERENCE_PHYSICAL_DEPENDENCY("REFERENCE_PHYSICAL_DEPENDENCY", InnerEnum::REFERENCE_PHYSICAL_DEPENDENCY, "Reference Physical Dependency", RDFNamespace::SEMSIM.getNamespaceAsString() + "Reference_physical_dependency", "A reference term that defines a physical dependency represented in the model.", "SemSim:Reference_physical_dependency");
    // SemSimTypes SemSimTypes::PHYSICAL_ENTITY("PHYSICAL_ENTITY", InnerEnum::PHYSICAL_ENTITY, "Physical Entity", RDFNamespace::SEMSIM.getNamespaceAsString() + "Physical_entity", "", "");
    // SemSimTypes SemSimTypes::CUSTOM_PHYSICAL_ENTITY("CUSTOM_PHYSICAL_ENTITY", InnerEnum::CUSTOM_PHYSICAL_ENTITY, "Custom Physical Entity", RDFNamespace::SEMSIM.getNamespaceAsString() + "Custom_physical_entity", "A physical entity which is not defined against a reference term, but instead created and defined in an ad hoc manner within a model.", "");
    // SemSimTypes SemSimTypes::COMPOSITE_PHYSICAL_ENTITY("COMPOSITE_PHYSICAL_ENTITY", InnerEnum::COMPOSITE_PHYSICAL_ENTITY, "Composite Physical Entity", RDFNamespace::SEMSIM.getNamespaceAsString() + "Composite_physical_entity", "A physical entity that is defined by a composition of multiple physical entity terms.", "");
    // SemSimTypes SemSimTypes::CUSTOM_PHYSICAL_PROCESS("CUSTOM_PHYSICAL_PROCESS", InnerEnum::CUSTOM_PHYSICAL_PROCESS, "Custom Physical Process", RDFNamespace::SEMSIM.getNamespaceAsString() + "Custom_physical_process", "A physical process which is not defined against a reference term, but instead created and defined in an ad hoc manner within the model.", "");
    // SemSimTypes SemSimTypes::REFERENCE_PHYSICAL_PROCESS("REFERENCE_PHYSICAL_PROCESS", InnerEnum::REFERENCE_PHYSICAL_PROCESS, "Reference Physical Process", RDFNamespace::SEMSIM.getNamespaceAsString() + "Reference_physical_process", "A reference term that defines a physical process simulated by the model.", "semsim:Reference_physical_process");
    // SemSimTypes SemSimTypes::PHYSICAL_FORCE("PHYSICAL_FORCE", InnerEnum::PHYSICAL_FORCE, "Physical Force", RDFNamespace::SEMSIM.getNamespaceAsString() + "Physical_force", "", "");
    // SemSimTypes SemSimTypes::CUSTOM_PHYSICAL_FORCE("CUSTOM_PHYSICAL_FORCE", InnerEnum::CUSTOM_PHYSICAL_FORCE, "Custom Physical Force", RDFNamespace::SEMSIM.getNamespaceAsString() + "Custom_physical_force", "A physical force which is not defined against a reference term, but instead created and defined in an ad hoc manner within the model.", "");
    // SemSimTypes SemSimTypes::PHYSICAL_PROCESS("PHYSICAL_PROCESS", InnerEnum::PHYSICAL_PROCESS, "Physical Process", RDFNamespace::SEMSIM.getNamespaceAsString() + "Physical_process","", "");
    // SemSimTypes SemSimTypes::DATASTRUCTURE("DATASTRUCTURE", InnerEnum::DATASTRUCTURE, "Data Structure", RDFNamespace::SEMSIM.getNamespaceAsString() + "Data_structure", "", "");
    // SemSimTypes SemSimTypes::DECIMAL("DECIMA", InnerEnum::DECIMAL, "Decima", RDFNamespace::SEMSIM.getNamespaceAsString() + "Decima", "", "semsim:Decima");
    // SemSimTypes SemSimTypes::MMLCHOICE("MMLCHOICE", InnerEnum::MMLCHOICE, "MML Model Choice", RDFNamespace::SEMSIM.getNamespaceAsString() + "MMLchoice", "", "semsim:MMLchoice");
    // SemSimTypes SemSimTypes::INTEGER("INTEGER", InnerEnum::INTEGER, "SemSim Integer", RDFNamespace::SEMSIM.getNamespaceAsString() + "Integer", "", "semsim:Integer");
    // SemSimTypes SemSimTypes::COMPUTATION("COMPUTATION", InnerEnum::COMPUTATION, "Computation", RDFNamespace::SEMSIM.getNamespaceAsString() + "Computation", "", "semsim:Computation");
    // SemSimTypes SemSimTypes::SBML_FUNCTION_OUTPUT("SBML_FUNCTION_OUTPUT", InnerEnum::SBML_FUNCTION_OUTPUT, "SBML Function Output", RDFNamespace::SEMSIM.getNamespaceAsString() + "SBML_function_output", "", "semsim:SBML_function_output");
    // SemSimTypes SemSimTypes::RELATIONAL_CONSTRAINT("RELATIONAL_CONSTRAINT", InnerEnum::RELATIONAL_CONSTRAINT, "Relational Constraint", RDFNamespace::SEMSIM.getNamespaceAsString() + "Relational_constraint", "", "semsim:Relational_constraint");
    // SemSimTypes SemSimTypes::EVENT("EVENT", InnerEnum::EVENT, "Event", RDFNamespace::SEMSIM.getNamespaceAsString() + "Event", "", "semsim:Event");
    // SemSimTypes SemSimTypes::EVENT_ASSIGNMENT("EVENT_ASSIGNMENT", InnerEnum::EVENT_ASSIGNMENT, "Event Assignment", RDFNamespace::SEMSIM.getNamespaceAsString() + "EventAssignment", "", "semsim:EventAssignment");
    // SemSimTypes SemSimTypes::SBML_INITIAL_ASSIGNMENT("SBML_INITIAL_ASSIGNMENT", InnerEnum::SBML_INITIAL_ASSIGNMENT, "SBML Initial Assignment", RDFNamespace::SEMSIM.getNamespaceAsString() + "SBML_initial_assignment","","sesmsim:SBML_initial_assignment");
    // SemSimTypes SemSimTypes::UNIT_OF_MEASUREMENT("UNIT_OF_MEASUREMENT", InnerEnum::UNIT_OF_MEASUREMENT, "Unit of Measurement", RDFNamespace::SEMSIM.getNamespaceAsString() + "Unit_of_measurement", "", "semsim:Unit_of_measurement");
    //
    // std::vector<SemSimTypes> SemSimTypes::valueList;
    //
    // SemSimTypes::StaticConstructor::StaticConstructor() {
    //     valueList.push_back(SEMSIM_COMPONENT);
    //     valueList.push_back(MODEL);
    //     valueList.push_back(SUBMODEL);
    //     valueList.push_back(PHYSICAL_MODEL_COMPONENT);
    //     valueList.push_back(PHYSICAL_PROPERTY);
    //     valueList.push_back(PHYSICAL_PROPERTY_IN_COMPOSITE);
    //     valueList.push_back(REFERENCE_PHYSICAL_ENTITY);
    //     valueList.push_back(PHYSICAL_DEPENDENCY);
    //     valueList.push_back(REFERENCE_PHYSICAL_DEPENDENCY);
    //     valueList.push_back(PHYSICAL_ENTITY);
    //     valueList.push_back(CUSTOM_PHYSICAL_ENTITY);
    //     valueList.push_back(COMPOSITE_PHYSICAL_ENTITY);
    //     valueList.push_back(CUSTOM_PHYSICAL_PROCESS);
    //     valueList.push_back(REFERENCE_PHYSICAL_PROCESS);
    //     valueList.push_back(PHYSICAL_FORCE);
    //     valueList.push_back(CUSTOM_PHYSICAL_FORCE);
    //     valueList.push_back(PHYSICAL_PROCESS);
    //     valueList.push_back(DATASTRUCTURE);
    //     valueList.push_back(DECIMAL);
    //     valueList.push_back(MMLCHOICE);
    //     valueList.push_back(INTEGER);
    //     valueList.push_back(COMPUTATION);
    //     valueList.push_back(SBML_FUNCTION_OUTPUT);
    //     valueList.push_back(RELATIONAL_CONSTRAINT);
    //     valueList.push_back(EVENT);
    //     valueList.push_back(EVENT_ASSIGNMENT);
    //     valueList.push_back(SBML_INITIAL_ASSIGNMENT);
    //     valueList.push_back(UNIT_OF_MEASUREMENT);
    // }
    //
    // SemSimTypes::StaticConstructor SemSimTypes::staticConstructor;
    // int SemSimTypes::nextOrdinal = 0;
    //
    // SemSimTypes::SemSimTypes(const std::wstring& name, InnerEnum innerEnum, const std::wstring& name, const std::wstring& uri, const std::wstring& desc, const std::wstring& sparqlcode) : nameValue(name), ordinalValue(nextOrdinal++), innerEnumValue(innerEnum) {
    //     this->name = name;
    //     this->uri = uri;
    //     this->sparqlcode = sparqlcode;
    // }
    //
    // std::wstring SemSimTypes::getName() {
    //     return name;
    // }
    //
    // std::wstring SemSimTypes::getURIasString() {
    //     return uri;
    // }
    //
    // java::net::URI* SemSimTypes::getURI() {
    //     return URI::create(uri);
    // }
    //
    // org::semanticweb::owlapi::model::IRI* SemSimTypes::getIRI() {
    //     return IRI::create(uri);
    // }
    //
    // std::wstring SemSimTypes::getSparqlCode() {
    //     return sparqlcode;
    // }
    //
    // std::wstring SemSimTypes::getDescription() {
    //     return description;
    // }
    //
    // bool SemSimTypes::operator == (const SemSimTypes& other) {
    //     return this->ordinalValue == other.ordinalValue;
    // }
    //
    // bool SemSimTypes::operator != (const SemSimTypes& other) {
    //     return this->ordinalValue != other.ordinalValue;
    // }
    //
    // std::vector<SemSimTypes> SemSimTypes::values() {
    //     return valueList;
    // }
    //
    // int SemSimTypes::ordinal() {
    //     return ordinalValue;
    // }
    //
    // std::wstring SemSimTypes::toString() {
    //     return nameValue;
    // }
    //
    // SemSimTypes SemSimTypes::valueOf(const std::wstring& name) {
    //     for (auto enumInstance : SemSimTypes::valueList) {
    //         if (enumInstance.nameValue == name) {
    //             return enumInstance;
    //         }
    //     }
    // }
}
