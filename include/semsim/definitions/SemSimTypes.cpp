#include "SemSimTypes.h"

namespace semsim
{
	namespace definitions
	{
		using org::semanticweb::owlapi::model::IRI;

SemSimTypes SemSimTypes::SEMSIM_COMPONENT(L"SEMSIM_COMPONENT", InnerEnum::SEMSIM_COMPONENT, L"SemSim Component", RDFNamespace::SEMSIM.getNamespaceAsString() + L"SemSim_component", L"", L"");
SemSimTypes SemSimTypes::MODEL(L"MODEL", InnerEnum::MODEL, L"SemSim Model", RDFNamespace::SEMSIM.getNamespaceAsString() + L"SemSim_Model", L"", L"SemSim:SemSim_Model");
SemSimTypes SemSimTypes::SUBMODEL(L"SUBMODEL", InnerEnum::SUBMODEL, L"Submodel", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Submodel", L"", L"SemSim:Submodel");
SemSimTypes SemSimTypes::PHYSICAL_MODEL_COMPONENT(L"PHYSICAL_MODEL_COMPONENT", InnerEnum::PHYSICAL_MODEL_COMPONENT, L"Physical Model Component", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Physical_model_component", L"", L"");
SemSimTypes SemSimTypes::PHYSICAL_PROPERTY(L"PHYSICAL_PROPERTY", InnerEnum::PHYSICAL_PROPERTY, L"Singular Physical Property", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Physical_property", L"A reference term that precisely defines a biophysical property simulated in the model.", L"SemSim:Physical_property");
SemSimTypes SemSimTypes::PHYSICAL_PROPERTY_IN_COMPOSITE(L"PHYSICAL_PROPERTY_IN_COMPOSITE", InnerEnum::PHYSICAL_PROPERTY_IN_COMPOSITE, L"Physical Property for a Composite", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Physical_property_in_composite", L"A reference term that defines the physical property component of a composite annotation.", L"");
SemSimTypes SemSimTypes::REFERENCE_PHYSICAL_ENTITY(L"REFERENCE_PHYSICAL_ENTITY", InnerEnum::REFERENCE_PHYSICAL_ENTITY, L"Reference Physical Entity", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Reference_physical_entity", L"A reference term that defines a physical entity represented in the model.", L"SemSim:Reference_physical_entity");
SemSimTypes SemSimTypes::PHYSICAL_DEPENDENCY(L"PHYSICAL_DEPENDENCY", InnerEnum::PHYSICAL_DEPENDENCY, L"Physical Dependency", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Physical_dependency", L"", L"");
SemSimTypes SemSimTypes::REFERENCE_PHYSICAL_DEPENDENCY(L"REFERENCE_PHYSICAL_DEPENDENCY", InnerEnum::REFERENCE_PHYSICAL_DEPENDENCY, L"Reference Physical Dependency", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Reference_physical_dependency", L"A reference term that defines a physical dependency represented in the model.", L"SemSim:Reference_physical_dependency");
SemSimTypes SemSimTypes::PHYSICAL_ENTITY(L"PHYSICAL_ENTITY", InnerEnum::PHYSICAL_ENTITY, L"Physical Entity", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Physical_entity", L"", L"");
SemSimTypes SemSimTypes::CUSTOM_PHYSICAL_ENTITY(L"CUSTOM_PHYSICAL_ENTITY", InnerEnum::CUSTOM_PHYSICAL_ENTITY, L"Custom Physical Entity", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Custom_physical_entity", L"A physical entity which is not defined against a reference term, but instead created and defined in an ad hoc manner within a model.", L"");
SemSimTypes SemSimTypes::COMPOSITE_PHYSICAL_ENTITY(L"COMPOSITE_PHYSICAL_ENTITY", InnerEnum::COMPOSITE_PHYSICAL_ENTITY, L"Composite Physical Entity", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Composite_physical_entity", L"A physical entity that is defined by a composition of multiple physical entity terms.", L"");
SemSimTypes SemSimTypes::CUSTOM_PHYSICAL_PROCESS(L"CUSTOM_PHYSICAL_PROCESS", InnerEnum::CUSTOM_PHYSICAL_PROCESS, L"Custom Physical Process", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Custom_physical_process", L"A physical process which is not defined against a reference term, but instead created and defined in an ad hoc manner within the model.", L"");
SemSimTypes SemSimTypes::REFERENCE_PHYSICAL_PROCESS(L"REFERENCE_PHYSICAL_PROCESS", InnerEnum::REFERENCE_PHYSICAL_PROCESS, L"Reference Physical Process", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Reference_physical_process", L"A reference term that defines a physical process simulated by the model.", L"semsim:Reference_physical_process");
SemSimTypes SemSimTypes::PHYSICAL_FORCE(L"PHYSICAL_FORCE", InnerEnum::PHYSICAL_FORCE, L"Physical Force", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Physical_force", L"", L"");
SemSimTypes SemSimTypes::CUSTOM_PHYSICAL_FORCE(L"CUSTOM_PHYSICAL_FORCE", InnerEnum::CUSTOM_PHYSICAL_FORCE, L"Custom Physical Force", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Custom_physical_force", L"A physical force which is not defined against a reference term, but instead created and defined in an ad hoc manner within the model.", L"");
SemSimTypes SemSimTypes::PHYSICAL_PROCESS(L"PHYSICAL_PROCESS", InnerEnum::PHYSICAL_PROCESS, L"Physical Process", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Physical_process",L"", L"");
SemSimTypes SemSimTypes::DATASTRUCTURE(L"DATASTRUCTURE", InnerEnum::DATASTRUCTURE, L"Data Structure", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Data_structure", L"", L"");
SemSimTypes SemSimTypes::DECIMAL(L"DECIMAL", InnerEnum::DECIMAL, L"Decimal", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Decimal", L"", L"semsim:Decimal");
SemSimTypes SemSimTypes::MMLCHOICE(L"MMLCHOICE", InnerEnum::MMLCHOICE, L"MML Model Choice", RDFNamespace::SEMSIM.getNamespaceAsString() + L"MMLchoice", L"", L"semsim:MMLchoice");
SemSimTypes SemSimTypes::INTEGER(L"INTEGER", InnerEnum::INTEGER, L"SemSim Integer", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Integer", L"", L"semsim:Integer");
SemSimTypes SemSimTypes::COMPUTATION(L"COMPUTATION", InnerEnum::COMPUTATION, L"Computation", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Computation", L"", L"semsim:Computation");
SemSimTypes SemSimTypes::SBML_FUNCTION_OUTPUT(L"SBML_FUNCTION_OUTPUT", InnerEnum::SBML_FUNCTION_OUTPUT, L"SBML Function Output", RDFNamespace::SEMSIM.getNamespaceAsString() + L"SBML_function_output", L"", L"semsim:SBML_function_output");
SemSimTypes SemSimTypes::RELATIONAL_CONSTRAINT(L"RELATIONAL_CONSTRAINT", InnerEnum::RELATIONAL_CONSTRAINT, L"Relational Constraint", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Relational_constraint", L"", L"semsim:Relational_constraint");
SemSimTypes SemSimTypes::EVENT(L"EVENT", InnerEnum::EVENT, L"Event", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Event", L"", L"semsim:Event");
SemSimTypes SemSimTypes::EVENT_ASSIGNMENT(L"EVENT_ASSIGNMENT", InnerEnum::EVENT_ASSIGNMENT, L"Event Assignment", RDFNamespace::SEMSIM.getNamespaceAsString() + L"EventAssignment", L"", L"semsim:EventAssignment");
SemSimTypes SemSimTypes::SBML_INITIAL_ASSIGNMENT(L"SBML_INITIAL_ASSIGNMENT", InnerEnum::SBML_INITIAL_ASSIGNMENT, L"SBML Initial Assignment", RDFNamespace::SEMSIM.getNamespaceAsString() + L"SBML_initial_assignment",L"",L"sesmsim:SBML_initial_assignment");
SemSimTypes SemSimTypes::UNIT_OF_MEASUREMENT(L"UNIT_OF_MEASUREMENT", InnerEnum::UNIT_OF_MEASUREMENT, L"Unit of Measurement", RDFNamespace::SEMSIM.getNamespaceAsString() + L"Unit_of_measurement", L"", L"semsim:Unit_of_measurement");

std::vector<SemSimTypes> SemSimTypes::valueList;

SemSimTypes::StaticConstructor::StaticConstructor()
{
	valueList.push_back(SEMSIM_COMPONENT);
	valueList.push_back(MODEL);
	valueList.push_back(SUBMODEL);
	valueList.push_back(PHYSICAL_MODEL_COMPONENT);
	valueList.push_back(PHYSICAL_PROPERTY);
	valueList.push_back(PHYSICAL_PROPERTY_IN_COMPOSITE);
	valueList.push_back(REFERENCE_PHYSICAL_ENTITY);
	valueList.push_back(PHYSICAL_DEPENDENCY);
	valueList.push_back(REFERENCE_PHYSICAL_DEPENDENCY);
	valueList.push_back(PHYSICAL_ENTITY);
	valueList.push_back(CUSTOM_PHYSICAL_ENTITY);
	valueList.push_back(COMPOSITE_PHYSICAL_ENTITY);
	valueList.push_back(CUSTOM_PHYSICAL_PROCESS);
	valueList.push_back(REFERENCE_PHYSICAL_PROCESS);
	valueList.push_back(PHYSICAL_FORCE);
	valueList.push_back(CUSTOM_PHYSICAL_FORCE);
	valueList.push_back(PHYSICAL_PROCESS);
	valueList.push_back(DATASTRUCTURE);
	valueList.push_back(DECIMAL);
	valueList.push_back(MMLCHOICE);
	valueList.push_back(INTEGER);
	valueList.push_back(COMPUTATION);
	valueList.push_back(SBML_FUNCTION_OUTPUT);
	valueList.push_back(RELATIONAL_CONSTRAINT);
	valueList.push_back(EVENT);
	valueList.push_back(EVENT_ASSIGNMENT);
	valueList.push_back(SBML_INITIAL_ASSIGNMENT);
	valueList.push_back(UNIT_OF_MEASUREMENT);
}

SemSimTypes::StaticConstructor SemSimTypes::staticConstructor;
int SemSimTypes::nextOrdinal = 0;

		SemSimTypes::SemSimTypes(const std::wstring &name, InnerEnum innerEnum, const std::wstring &name, const std::wstring &uri, const std::wstring &desc, const std::wstring &sparqlcode) : nameValue(name), ordinalValue(nextOrdinal++), innerEnumValue(innerEnum)
		{
			this->name = name;
			this->uri = uri;
			this->sparqlcode = sparqlcode;
		}

		std::wstring SemSimTypes::getName()
		{
			return name;
		}

		std::wstring SemSimTypes::getURIasString()
		{
			return uri;
		}

		java::net::URI *SemSimTypes::getURI()
		{
			return URI::create(uri);
		}

		org::semanticweb::owlapi::model::IRI *SemSimTypes::getIRI()
		{
			return IRI::create(uri);
		}

		std::wstring SemSimTypes::getSparqlCode()
		{
			return sparqlcode;
		}

		std::wstring SemSimTypes::getDescription()
		{
			return description;
		}

bool SemSimTypes::operator == (const SemSimTypes &other)
{
	return this->ordinalValue == other.ordinalValue;
}

bool SemSimTypes::operator != (const SemSimTypes &other)
{
	return this->ordinalValue != other.ordinalValue;
}

std::vector<SemSimTypes> SemSimTypes::values()
{
	return valueList;
}

int SemSimTypes::ordinal()
{
	return ordinalValue;
}

std::wstring SemSimTypes::toString()
{
	return nameValue;
}

SemSimTypes SemSimTypes::valueOf(const std::wstring &name)
{
	for (auto enumInstance : SemSimTypes::valueList)
	{
		if (enumInstance.nameValue == name)
		{
			return enumInstance;
		}
	}
}
	}
}