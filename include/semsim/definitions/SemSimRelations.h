#include <string>
#include <vector>

namespace semsim { namespace annotation { class Relation; } }

namespace semsim
{
	namespace definitions
	{


		using org::sbml::jsbml::CVTerm::Qualifier;


		using Relation = semsim::annotation::Relation;

		/**
		 * Constants and functions for working with relations (AKA predicates or qualifiers)
		 * in SemSim models
		 * @author mneal
		 *
		 */
		class SemSimRelations
		{

			/**
			 * @param q A BioModels.net biological qualifier
			 * @return The {@link Relation} corresponding to the qualifier
			 */
		public:
			static Relation *getRelationFromBiologicalQualifier(Qualifier *q);


			/**
			 * @param r A {@link Relation}
			 * @return The BioModels.net biological qualifier corresponding to the relation
			 */
			static Qualifier *getBiologicalQualifierFromRelation(Relation *r);

			/**
			 * @param id A BioModels.net model qualifier ID
			 * @return The {@link Relation} corresponding to the qualifier
			 */
			static Relation *getRelationFromModelQualifier(Qualifier *id);


			/**
			 * @param r A {@link Relation}
			 * @return The BioModels.net model qualifier corresponding to the relation
			 */
			static Qualifier *getModelQualifierFromRelation(Relation *r);




			/**
			 * @param rel A {@link StructuralRelation}
			 * @return The logical inverse of the StructuralRelation
			 */
			static StructuralRelation getInverseStructuralRelation(StructuralRelation rel);


			/**
			 * Look up which relation to use for an ontology-level annotation in a SemSim OWL file.
			 * This is needed because the same OWL property can't be used in statements on classes
			 * and in ontology-level annotations.
			 * @param rel The Relation that we'd like to use for the ontology-level annotation
			 * @return The synonymous relation to use for the ontology-level annotation
			 */
			static Relation *getSynonymousModelLevelRelationForSemSimOWLwriting(Relation *rel);


			/**
			 * Look up which relation to use for a model-level annotation in a SemSim model.
			 * This is needed because the same OWL property can't be used in statements on classes
			 * and in ontology-level annotations.
			 * @param rel The Relation that we'd like to use for the model-level annotation that comes from a SemSim OWL file
			 * @return The synonymous relation to use for the model-level annotation
			 */
			static Relation *getSynonymousModelLevelRelationForSemSimOWLreading(Relation *rel);


			/**
			 * Look up a URI's corresponding {@link SemSimRelation}
			 * 
			 * @param uri The URI key
			 * @return The SemSimRelation value for the URI key or else null if not found
			 */
			static Relation *getRelationFromURI(URI *uri);

		public:
			class SemSimRelation final : public Relation
			{
				//Model level Relations

				// Separate relation for model-level metadata ID needed b/c OWL Annotation properties used to annotate the ontology as a whole are disjoint 
				// from Datatype properties used to annotate, say, a data structure in a model
public:
				static SemSimRelation MODEL_METADATA_ID;
				static SemSimRelation MODEL_NAME;
				static SemSimRelation MODEL_DESCRIPTION;
				static SemSimRelation MODEL_IS_VERSION_OF; // needed b/c BQB:isVersionOf can be used on class statements but not for ontology-level annotation
				static SemSimRelation MODEL_ENCODES; // needed b/c BQB:encodes could potentially be used on class statements but not for ontology-level annotation
				static SemSimRelation MODEL_IS_ENCODED_BY; // needed b/c BQB:isEncodedBy could potentially be used on class statements but not for ontology-level annotation

				static SemSimRelation HAS_NAME;
				static SemSimRelation KEY_TERM;

				//CellML Specific Relations:
				static SemSimRelation CELLML_COMPONENT_SUBSUMPTION_TYPE;
				static SemSimRelation CELLML_RDF_MARKUP;
				static SemSimRelation CELLML_DOCUMENTATION;
				static SemSimRelation CELLML_COMPONENT_PRIVATE_INTERFACE;
				static SemSimRelation CELLML_COMPONENT_PUBLIC_INTERFACE;
				static SemSimRelation MAPPED_FROM;
				static SemSimRelation MAPPED_TO;
				static SemSimRelation CELLML_INITIAL_VALUE;

				//Collection Relations
				static SemSimRelation INCLUDES_SUBMODEL;
				static SemSimRelation ENCAPSULATES;

				//Computational Relations
				static SemSimRelation HAS_COMPUTATIONAL_COMPONENT;
				static SemSimRelation IS_COMPUTATIONAL_COMPONENT_FOR;
				static SemSimRelation COMPUTATIONAL_REPRESENTATION_OF;
				static SemSimRelation HAS_MATHML;
				static SemSimRelation HAS_COMPUTATIONAL_CODE;
				static SemSimRelation IS_OUTPUT_FOR;
				static SemSimRelation IS_INPUT_FOR;
				static SemSimRelation HAS_ASSOCIATED_DATA_STRUCTURE;
				static SemSimRelation HAS_TRIGGER_MATHML;
				static SemSimRelation HAS_EVENT;
				static SemSimRelation HAS_EVENT_ASSIGNMENT;
				static SemSimRelation HAS_PRIORITY_MATHML;
				static SemSimRelation HAS_DELAY_MATHML;
				static SemSimRelation HAS_TIME_UNIT;
				static SemSimRelation HAS_INPUT;
				static SemSimRelation IS_DECLARED;
				static SemSimRelation IS_DETERMINED_BY;
				static SemSimRelation IS_DISCRETE;
				static SemSimRelation IS_FUNDAMENTAL_UNIT;
				static SemSimRelation IS_SOLUTION_DOMAIN;
				static SemSimRelation HAS_SOLUTION_DOMAIN;
				static SemSimRelation HAS_START_VALUE;
				static SemSimRelation HAS_OUTPUT;
				static SemSimRelation HAS_UNIT_FACTOR;
				static SemSimRelation UNIT_FACTOR_EXPONENT;
				static SemSimRelation UNIT_FACTOR_FOR;
				static SemSimRelation UNIT_FACTOR_PREFIX;
				static SemSimRelation UNIT_FACTOR_MULTIPLIER;

				//Process participant relations0
				static SemSimRelation HAS_SOURCE;
				static SemSimRelation HAS_SINK;
				static SemSimRelation HAS_MEDIATOR;
				static SemSimRelation HAS_SOURCE_PARTICIPANT;
				static SemSimRelation HAS_SINK_PARTICIPANT;
				static SemSimRelation HAS_MEDIATOR_PARTICIPANT;
				static SemSimRelation HAS_MULTIPLIER;

				static SemSimRelation DETERMINES;

				static SemSimRelation HREF_VALUE_OF_IMPORT;
				static SemSimRelation IMPORTED_FROM;
				static SemSimRelation REFERENCE_NAME_OF_IMPORT;
				static SemSimRelation METADATA_ID;

				static SemSimRelation HAS_PHYSICAL_DEFINITION;
				static SemSimRelation HAS_PHYSICAL_ENTITY_REFERENCE;
				static SemSimRelation HAS_PHYSICAL_PROPERTY;
				static SemSimRelation PHYSICAL_PROPERTY_OF;
				static SemSimRelation HAS_UNIT;
				static SemSimRelation UNIT_FOR;

				//BioModels qualifiers
				static SemSimRelation BQB_ENCODES;
				static SemSimRelation BQB_HAS_PROPERTY;
				static SemSimRelation BQB_HAS_VERSION;
				static SemSimRelation BQB_IS;
				static SemSimRelation BQB_IS_DESCRIBED_BY;
				static SemSimRelation BQB_IS_ENCODED_BY;
				static SemSimRelation BQB_IS_HOMOLOG_TO;
				static SemSimRelation BQB_IS_PROPERTY_OF;
				static SemSimRelation BQB_IS_VERSION_OF;
				static SemSimRelation BQB_HAS_TAXON;
				static SemSimRelation BQB_OCCURS_IN;

				static SemSimRelation BQM_IS;
				static SemSimRelation BQM_IS_DESCRIBED_BY;
				static SemSimRelation BQM_IS_DERIVED_FROM;
				static SemSimRelation BQM_HAS_INSTANCE;
				static SemSimRelation BQM_IS_INSTANCE_OF;

				static SemSimRelation UNKNOWN;

