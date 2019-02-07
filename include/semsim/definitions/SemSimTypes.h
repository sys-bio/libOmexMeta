#include <string>
#include <vector>

namespace semsim
{
	namespace definitions
	{
		/**
		 * Enum and functions for the different types of objects used in SemSim models
		 *
		 *
		 */
		class SemSimTypes final
		{
public:
			static SemSimTypes SEMSIM_COMPONENT;
			static SemSimTypes MODEL;
			static SemSimTypes SUBMODEL;
			static SemSimTypes PHYSICAL_MODEL_COMPONENT;
			static SemSimTypes PHYSICAL_PROPERTY;
			static SemSimTypes PHYSICAL_PROPERTY_IN_COMPOSITE;
			static SemSimTypes REFERENCE_PHYSICAL_ENTITY;
			static SemSimTypes PHYSICAL_DEPENDENCY;
			static SemSimTypes REFERENCE_PHYSICAL_DEPENDENCY;
			static SemSimTypes PHYSICAL_ENTITY;
			static SemSimTypes CUSTOM_PHYSICAL_ENTITY;
			static SemSimTypes COMPOSITE_PHYSICAL_ENTITY;
			static SemSimTypes CUSTOM_PHYSICAL_PROCESS;
			static SemSimTypes REFERENCE_PHYSICAL_PROCESS;
			static SemSimTypes PHYSICAL_FORCE;
			static SemSimTypes CUSTOM_PHYSICAL_FORCE;
			static SemSimTypes PHYSICAL_PROCESS;
			static SemSimTypes DATASTRUCTURE;
			static SemSimTypes DECIMAL;
			static SemSimTypes MMLCHOICE;
			static SemSimTypes INTEGER;
			static SemSimTypes COMPUTATION;
			static SemSimTypes SBML_FUNCTION_OUTPUT;
			static SemSimTypes RELATIONAL_CONSTRAINT;
			static SemSimTypes EVENT;
			static SemSimTypes EVENT_ASSIGNMENT;
			static SemSimTypes SBML_INITIAL_ASSIGNMENT;
			static SemSimTypes UNIT_OF_MEASUREMENT;

private:
			static std::vector<SemSimTypes> valueList;

			class StaticConstructor
			{
			public:
				StaticConstructor();
			};

			static StaticConstructor staticConstructor;

public:
			enum class InnerEnum
			{
				SEMSIM_COMPONENT,
				MODEL,
				SUBMODEL,
				PHYSICAL_MODEL_COMPONENT,
				PHYSICAL_PROPERTY,
				PHYSICAL_PROPERTY_IN_COMPOSITE,
				REFERENCE_PHYSICAL_ENTITY,
				PHYSICAL_DEPENDENCY,
				REFERENCE_PHYSICAL_DEPENDENCY,
				PHYSICAL_ENTITY,
				CUSTOM_PHYSICAL_ENTITY,
				COMPOSITE_PHYSICAL_ENTITY,
				CUSTOM_PHYSICAL_PROCESS,
				REFERENCE_PHYSICAL_PROCESS,
				PHYSICAL_FORCE,
				CUSTOM_PHYSICAL_FORCE,
				PHYSICAL_PROCESS,
				DATASTRUCTURE,
				DECIMAL,
				MMLCHOICE,
				INTEGER,
				COMPUTATION,
				SBML_FUNCTION_OUTPUT,
				RELATIONAL_CONSTRAINT,
				EVENT,
				EVENT_ASSIGNMENT,
				SBML_INITIAL_ASSIGNMENT,
				UNIT_OF_MEASUREMENT
			};

			const InnerEnum innerEnumValue;
private:
			const std::wstring nameValue;
			const int ordinalValue;
			static int nextOrdinal;

		private:
			std::wstring name;
			std::wstring uri;
			std::wstring sparqlcode;
			std::wstring description;

		public:
			SemSimTypes(const std::wstring &name, InnerEnum innerEnum, const std::wstring &name, const std::wstring &uri, const std::wstring &desc, const std::wstring &sparqlcode);

			/** @return The name of the SemSimType */
			virtual std::wstring getName();

			/** @return The URI of the SemSimType as a string*/
			virtual std::wstring getURIasString();

			/** @return The URI of the SemSimType */
			virtual java::net::URI *getURI();

			/** @return The URI of the SemSimType cast as an IRI */
			virtual org::semanticweb::owlapi::model::IRI *getIRI();

			/** @return The SemSimType formatted for SPARQL queries */
			virtual std::wstring getSparqlCode();

			/** @return The description of the SemSimType */
			virtual std::wstring getDescription();

public:
			bool operator == (const SemSimTypes &other);

			bool operator != (const SemSimTypes &other);

			static std::vector<SemSimTypes> values();

			int ordinal();

			std::wstring toString();

			static SemSimTypes valueOf(const std::wstring &name);
		};

	}
}