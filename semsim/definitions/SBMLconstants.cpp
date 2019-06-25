#include "SBMLconstants.h"

namespace semsim {
    namespace definitions {
        using SemSimLibrary = semsim::SemSimLibrary;
        const std::unordered_map<std::string, std::string> SBMLconstants::SBML_LEVEL_2_RESERVED_UNITS_MAP;
        java::util::Set<std::string>* const SBMLconstants::SBML_LEVEL_3_BASE_UNITS;
        java::util::Set<std::string>* const SBMLconstants::SBML_LEVEL_2_VERSION_2_BASE_UNITS;
        java::util::Set<std::string>* const SBMLconstants::SBML_LEVEL_2_VERSION_1_BASE_UNITS;
        java::util::Set<java::net::URI*>* const SBMLconstants::OPB_PROPERTIES_FOR_COMPARTMENTS;
        java::util::Set<java::net::URI*>* const SBMLconstants::OPB_PROPERTIES_FOR_SPECIES;
        java::util::Set<java::net::URI*>* const SBMLconstants::OPB_PROPERTIES_FOR_REACTIONS;

        SBMLconstants::StaticConstructor::StaticConstructor() {
            // Mapping between reserved units in SBML level 2 models and their default base units
            LinkedHashMap<std::string, std::string>* map0 = new LinkedHashMap<std::string, std::string>();
            map0->put(L"substance", L"mole");
            map0->put(L"volume", L"litre");
            map0->put(L"area", L"square metre");
            map0->put(L"length", L"metre");
            map0->put(L"time", L"second");
            SBML_LEVEL_2_RESERVED_UNITS_MAP = Collections::unmodifiableMap(map0);
            // SBML level 3 base unit set
            Set<std::string>* set0 = std::unordered_set<std::string>();
            set0->add(L"ampere");
            set0->add(L"farad");
            set0->add(L"joule");
            set0->add(L"lux");
            set0->add(L"radian");
            set0->add(L"volt");
            set0->add(L"avogadro");
            set0->add(L"gram");
            set0->add(L"katal");
            set0->add(L"metre");
            set0->add(L"second");
            set0->add(L"watt");
            set0->add(L"becquerel");
            set0->add(L"gray");
            set0->add(L"kelvin");
            set0->add(L"mole");
            set0->add(L"siemends");
            set0->add(L"weber");
            set0->add(L"candela");
            set0->add(L"henry");
            set0->add(L"kilogram");
            set0->add(L"newton");
            set0->add(L"sievert");
            set0->add(L"coulomb");
            set0->add(L"hertz");
            set0->add(L"litre");
            set0->add(L"ohm");
            set0->add(L"steradian");
            set0->add(L"dimensionless");
            set0->add(L"item");
            set0->add(L"lumen");
            set0->add(L"pascal");
            set0->add(L"tesla");
            SBML_LEVEL_3_BASE_UNITS = Collections::unmodifiableSet(set0);
            SBML_LEVEL_2_VERSION_2_BASE_UNITS = std::unordered_set<std::string>();
            SBML_LEVEL_2_VERSION_2_BASE_UNITS->addAll(SBML_LEVEL_3_BASE_UNITS);
            SBML_LEVEL_2_VERSION_2_BASE_UNITS->remove(L"avogadro");
            SBML_LEVEL_2_VERSION_1_BASE_UNITS = std::unordered_set<std::string>();
            SBML_LEVEL_2_VERSION_1_BASE_UNITS->addAll(SBML_LEVEL_2_VERSION_2_BASE_UNITS);
            SBML_LEVEL_2_VERSION_1_BASE_UNITS->add(L"Celsius");
            Set<URI*>* set1 = std::unordered_set<URI*>();
            set1->add(SemSimLibrary::OPB_FLUID_VOLUME_URI);
            set1->add(SemSimLibrary::OPB_AREA_OF_SPATIAL_ENTITY_URI);
            set1->add(SemSimLibrary::OPB_SPAN_OF_SPATIAL_ENTITY_URI);
            OPB_PROPERTIES_FOR_COMPARTMENTS = Collections::unmodifiableSet(set1);
            Set<URI*>* set2 = std::unordered_set<URI*>();
            set2->add(SemSimLibrary::OPB_CHEMICAL_CONCENTRATION_URI);
            set2->add(SemSimLibrary::OPB_CHEMICAL_MOLAR_AMOUNT_URI);
            set2->add(SemSimLibrary::OPB_PARTICLE_COUNT_URI);
            set2->add(SemSimLibrary::OPB_PARTICLE_CONCENTRATION_URI);
            set2->add(SemSimLibrary::OPB_MASS_OF_SOLID_ENTITY_URI);
            set2->add(SemSimLibrary::OPB_MASS_LINEAL_DENSITY_URI);
            set2->add(SemSimLibrary::OPB_MASS_AREAL_DENSITY_URI);
            set2->add(SemSimLibrary::OPB_MASS_VOLUMETRIC_DENSITY_URI);
            OPB_PROPERTIES_FOR_SPECIES = Collections::unmodifiableSet(set2);
            Set<URI*>* set3 = std::unordered_set<URI*>();
            set3->add(SemSimLibrary::OPB_CHEMICAL_MOLAR_FLOW_RATE_URI);
            set3->add(SemSimLibrary::OPB_MATERIAL_FLOW_RATE_URI);
            set3->add(SemSimLibrary::OPB_PARTICLE_FLOW_RATE_URI);
            OPB_PROPERTIES_FOR_REACTIONS = Collections::unmodifiableSet(set3);
        }

        SBMLconstants::StaticConstructor SBMLconstants::staticConstructor;
    }
}
