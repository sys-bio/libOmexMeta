#include <string>

namespace semsim
{
	namespace annotation
	{

		using com::hp::hpl::jena::rdf::model::Property;
		using org::semanticweb::owlapi::model::IRI;


		/**
		 * Interface that provides methods for getting information about
		 * relations (AKA predicates, AKA qualifiers) used in annotations.
		 */
		class Relation
		{
		public:
			virtual std::wstring getName() = 0;

			/** @return The URI of the relation */
			virtual URI *getURI() = 0;

			/** @return The URI of the relation as a string*/
			virtual std::wstring getURIasString() = 0;

			/** @return The free-text description of the relation*/
			virtual std::wstring getDescription() = 0;

			/** @return The relation encoded for SPARQL queries*/
			virtual std::wstring getSPARQLCode() = 0;

			/** @return The IRI of the relation*/
			virtual IRI *getIRI() = 0;

			/** @return The relation instantiated as an RDF property*/
			virtual Property *getRDFproperty() = 0;
		};

	}
}