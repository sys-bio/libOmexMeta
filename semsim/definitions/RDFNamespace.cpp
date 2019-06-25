#include "RDFNamespace.h"

namespace semsim {
    namespace definitions {
        using org::jdom::Namespace;

        RDFNamespace RDFNamespace::PKB("PKB", InnerEnum::PKB, "http://www.virtualrat.edu/physkb/", "physkb");
        RDFNamespace RDFNamespace::SEMSIM("SEMSIM", InnerEnum::SEMSIM, "http://www.bhi.washington.edu/SemSim#", "semsim");
        RDFNamespace RDFNamespace::OPB("OPB", InnerEnum::OPB, "http://bhi.washington.edu/OPB#", "opb");
        RDFNamespace RDFNamespace::RO("RO", InnerEnum::RO, "http://www.obofoundry.org/ro/ro.owl#", "ro");
        RDFNamespace RDFNamespace::BQB("BQB", InnerEnum::BQB, "http://biomodels.net/biology-qualifiers/", "bqbiol");
        RDFNamespace RDFNamespace::BQM("BQM", InnerEnum::BQM, "http://biomodels.net/model-qualifiers/", "bqm");
        RDFNamespace RDFNamespace::RDF("RDF", InnerEnum::RDF, "http://www.w3.org/1999/02/22-rdf-syntax-ns#", "rdf");
        RDFNamespace RDFNamespace::DCTERMS("DCTERMS", InnerEnum::DCTERMS, "http://purl.org/dc/terms/", "dcterms");
        RDFNamespace RDFNamespace::DCTERMS11("DCTERMS11", InnerEnum::DCTERMS11, "http://purl.org/dc/elements/1.1/", "dcterms11");
        RDFNamespace RDFNamespace::MATHML("MATHML", InnerEnum::MATHML, "http://www.w3.org/1998/Math/MathML", "mathml");
        RDFNamespace RDFNamespace::XLINK("XLINK", InnerEnum::XLINK, "http://www.w3.org/1999/xlink", "xlink");
        RDFNamespace RDFNamespace::CELLML1_0("CELLML1_0", InnerEnum::CELLML1_0, "http://www.cellml.org/cellml/1.0#", "cellml");
        RDFNamespace RDFNamespace::CELLML1_1("CELLML1_1", InnerEnum::CELLML1_1, "http://www.cellml.org/cellml/1.1#", "cellml");
        RDFNamespace RDFNamespace::BQS("BQS", InnerEnum::BQS, L"http://www.cellml.org/bqs/1.0#", "bqs");
        RDFNamespace RDFNamespace::CMETA("CMETA", InnerEnum::CMETA, L"http://www.cellml.org/metadata/1.0#", "cmeta");
        RDFNamespace RDFNamespace::DOC("DOC", InnerEnum::DOC, L"http://cellml.org/tmp-documentation", "doc");
        RDFNamespace RDFNamespace::VCARD("VCARD", InnerEnum::VCARD, L"http://www.w3.org/2001/vcard-rdf/3.0#","vCard");

        std::vector<RDFNamespace> RDFNamespace::valueList;

        RDFNamespace::StaticConstructor::StaticConstructor() {
            valueList.push_back(PKB);
            valueList.push_back(SEMSIM);
            valueList.push_back(OPB);
            valueList.push_back(RO);
            valueList.push_back(BQB);
            valueList.push_back(BQM);
            valueList.push_back(RDF);
            valueList.push_back(DCTERMS);
            valueList.push_back(DCTERMS11);
            valueList.push_back(MATHML);
            valueList.push_back(XLINK);
            valueList.push_back(CELLML1_0);
            valueList.push_back(CELLML1_1);
            valueList.push_back(BQS);
            valueList.push_back(CMETA);
            valueList.push_back(DOC);
            valueList.push_back(VCARD);
        }

        RDFNamespace::StaticConstructor RDFNamespace::staticConstructor;
        int RDFNamespace::nextOrdinal = 0;

        RDFNamespace::RDFNamespace(const std::string& name, InnerEnum innerEnum, const std::string& namespace_Renamed, const std::string& id) : nameValue(name), ordinalValue(nextOrdinal++), innerEnumValue(innerEnum) {
            this->namespace_Renamed = namespace_Renamed;
            owlid = id;
        }

        std::string RDFNamespace::getNamespaceAsString() {
            return namespace_Renamed;
        }

        std::string RDFNamespace::getOWLid() {
            return owlid;
        }

        org::jdom::Namespace* RDFNamespace::createJdomNamespace() {
            return Namespace::getNamespace(getOWLid(), getNamespaceAsString());
        }

        bool RDFNamespace::operator == (const RDFNamespace& other) {
            return this->ordinalValue == other.ordinalValue;
        }

        bool RDFNamespace::operator != (const RDFNamespace& other) {
            return this->ordinalValue != other.ordinalValue;
        }

        std::vector<RDFNamespace> RDFNamespace::values() {
            return valueList;
        }

        int RDFNamespace::ordinal() {
            return ordinalValue;
        }

        std::string RDFNamespace::toString() {
            return nameValue;
        }

        RDFNamespace RDFNamespace::valueOf(const std::string& name) {
            for (auto enumInstance : RDFNamespace::valueList) {
                if (enumInstance.nameValue == name) {
                    return enumInstance;
                }
            }
        }
    }
}
