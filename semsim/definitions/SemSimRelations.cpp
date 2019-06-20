#include "SemSimRelations.h"

namespace semsim
{
	namespace definitions
	{
		using org::sbml::jsbml::CVTerm::Qualifier;
		using org::semanticweb::owlapi::model::IRI;
		using com::hp::hpl::jena::rdf::model::Property;
		using com::hp::hpl::jena::rdf::model::ResourceFactory;
		using Relation = semsim::annotation::Relation;

		Relation *SemSimRelations::getRelationFromBiologicalQualifier(Qualifier *q)
		{
			switch (q)
			{
			case BQB_ENCODES:
				return SemSimRelation::BQB_ENCODES;
			case BQB_HAS_PART:
				return StructuralRelation::HAS_PART; // Maybe this should be BQB_HAS_PART?
			case BQB_HAS_PROPERTY:
				return SemSimRelation::BQB_HAS_PROPERTY;
			case BQB_HAS_VERSION:
				return SemSimRelation::BQB_HAS_VERSION;
			case BQB_HAS_TAXON:
				return SemSimRelation::BQB_HAS_TAXON;
			case BQB_IS:
				return SemSimRelation::BQB_IS;
			case BQB_IS_DESCRIBED_BY:
				return SemSimRelation::BQB_IS_DESCRIBED_BY;
			case BQB_IS_ENCODED_BY:
				return SemSimRelation::BQB_IS_ENCODED_BY;
			case BQB_IS_HOMOLOG_TO:
				return SemSimRelation::BQB_IS_HOMOLOG_TO;
			case BQB_IS_PROPERTY_OF:
				return SemSimRelation::BQB_IS_PROPERTY_OF;
			case BQB_IS_VERSION_OF:
				return SemSimRelation::BQB_IS_VERSION_OF;
			case BQB_OCCURS_IN:
				return SemSimRelation::BQB_OCCURS_IN;
			case BQB_IS_PART_OF:
				return StructuralRelation::PART_OF; // Maybe this should be BQB_PART_OF?
			default:
				return nullptr;
			}
		}

		Qualifier *SemSimRelations::getBiologicalQualifierFromRelation(Relation *r)
		{

			if (r == SemSimRelation::BQB_IS || r == SemSimRelation::HAS_PHYSICAL_DEFINITION)
			{
				return Qualifier::BQB_IS;
			}

			else if (r == StructuralRelation::BQB_HAS_PART || r == StructuralRelation::HAS_PART)
			{
				return Qualifier::BQB_HAS_PART;
			}

			else if (r == StructuralRelation::BQB_IS_PART_OF || r == StructuralRelation::PART_OF)
			{
				return Qualifier::BQB_IS_PART_OF;
			}

			else if (r == SemSimRelation::BQB_IS_VERSION_OF)
			{
				return Qualifier::BQB_IS_VERSION_OF;
			}

			else if (r == SemSimRelation::BQB_OCCURS_IN)
			{
				return Qualifier::BQB_OCCURS_IN;
			}

			else if (r == SemSimRelation::BQB_IS_PROPERTY_OF || r == SemSimRelation::PHYSICAL_PROPERTY_OF)
			{
				return Qualifier::BQB_IS_PROPERTY_OF;
			}

			else if (r == SemSimRelation::BQB_HAS_TAXON)
			{
				return Qualifier::BQB_HAS_TAXON;
			}

			else if (r == SemSimRelation::BQB_HAS_PROPERTY)
			{
				return Qualifier::BQB_HAS_PROPERTY;
			}

			else if (r == SemSimRelation::BQB_ENCODES)
			{
				return Qualifier::BQB_ENCODES;
			}

			else if (r == SemSimRelation::BQB_IS_ENCODED_BY)
			{
				return Qualifier::BQB_IS_ENCODED_BY;
			}

			else if (r == SemSimRelation::BQB_HAS_VERSION)
			{
				return Qualifier::BQB_HAS_VERSION;
			}

			else if (r == SemSimRelation::BQB_IS_HOMOLOG_TO)
			{
				return Qualifier::BQB_IS_HOMOLOG_TO;
			}

			else if (r == SemSimRelation::BQB_IS_DESCRIBED_BY)
			{
				return Qualifier::BQB_IS_DESCRIBED_BY;
			}

			else if (r == SemSimRelation::BQB_OCCURS_IN)
			{
				return Qualifier::BQB_OCCURS_IN;
			}

			else
			{
				return nullptr;
			}

		}

		Relation *SemSimRelations::getRelationFromModelQualifier(Qualifier *id)
		{
			switch (id)
			{
			case BQM_IS:
				return SemSimRelation::BQM_IS;
			case BQM_IS_DESCRIBED_BY:
				return SemSimRelation::BQM_IS_DESCRIBED_BY;
			case BQM_IS_DERIVED_FROM:
				return SemSimRelation::BQM_IS_DERIVED_FROM;
			case BQM_IS_INSTANCE_OF:
				return SemSimRelation::BQM_IS_INSTANCE_OF;
			case BQM_HAS_INSTANCE:
				return SemSimRelation::BQM_HAS_INSTANCE;
			default:
				return nullptr;
			}
		}

		Qualifier *SemSimRelations::getModelQualifierFromRelation(Relation *r)
		{

			if (r == SemSimRelation::BQM_IS)
			{
				return Qualifier::BQM_IS;
			}

			else if (r == SemSimRelation::BQM_IS_DERIVED_FROM)
			{
				return Qualifier::BQM_IS_DERIVED_FROM;
			}

			else if (r == SemSimRelation::BQM_IS_DESCRIBED_BY)
			{
				return Qualifier::BQM_IS_DESCRIBED_BY;
			}

			else if (r == SemSimRelation::BQM_HAS_INSTANCE)
			{
				return Qualifier::BQM_HAS_INSTANCE;
			}

			else if (r == SemSimRelation::BQM_IS_INSTANCE_OF)
			{
				return Qualifier::BQM_IS_INSTANCE_OF;
			}

			else
			{
				return nullptr;
			}

		}

		SemSimRelations::StructuralRelation SemSimRelations::getInverseStructuralRelation(StructuralRelation rel) {
			switch (rel.innerEnumValue) {
				case semsim::definitions::SemSimRelations::StructuralRelation::InnerEnum::PART_OF:
					return StructuralRelation::HAS_PART;
				case semsim::definitions::SemSimRelations::StructuralRelation::InnerEnum::HAS_PART:
					return StructuralRelation::PART_OF;
				case semsim::definitions::SemSimRelations::StructuralRelation::InnerEnum::CONTAINED_IN:
					return StructuralRelation::CONTAINS;
				case semsim::definitions::SemSimRelations::StructuralRelation::InnerEnum::CONTAINS:
					return StructuralRelation::CONTAINED_IN;
				case semsim::definitions::SemSimRelations::StructuralRelation::InnerEnum::INDEX_ENTITY_FOR:
					return StructuralRelation::HAS_INDEX_ENTITY;
				case semsim::definitions::SemSimRelations::StructuralRelation::InnerEnum::HAS_INDEX_ENTITY:
					return StructuralRelation::INDEX_ENTITY_FOR;
				case semsim::definitions::SemSimRelations::StructuralRelation::InnerEnum::ADJACENT:
					return StructuralRelation::ADJACENT;
				case semsim::definitions::SemSimRelations::StructuralRelation::InnerEnum::BQB_IS_PART_OF:
					return StructuralRelation::BQB_HAS_PART;
				case semsim::definitions::SemSimRelations::StructuralRelation::InnerEnum::BQB_HAS_PART:
					return StructuralRelation::BQB_IS_PART_OF;
				case semsim::definitions::SemSimRelations::StructuralRelation::InnerEnum::MODEL_HAS_PART:
					return StructuralRelation::PART_OF;
			}
			return nullptr;
		}



