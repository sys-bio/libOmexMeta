#include <string>
#include <vector>

namespace semsim
{
	namespace definitions
	{


		/**
		 * Enumeration of various RDF namespaces used in biosimulation modeling formats.
		 *
		 */
		class RDFNamespace final
		{
public:
			static RDFNamespace PKB;
			static RDFNamespace SEMSIM;
			static RDFNamespace OPB;
			static RDFNamespace RO;
			static RDFNamespace BQB;
			static RDFNamespace BQM;
			static RDFNamespace RDF;
			static RDFNamespace DCTERMS;
			static RDFNamespace DCTERMS11;
			static RDFNamespace MATHML;
			static RDFNamespace XLINK;
			static RDFNamespace CELLML1_0;
			static RDFNamespace CELLML1_1;
			static RDFNamespace BQS;
			static RDFNamespace CMETA;
			static RDFNamespace DOC;
			static RDFNamespace VCARD;

private:
			static std::vector<RDFNamespace> valueList;

			class StaticConstructor
			{
			public:
				StaticConstructor();
			};

			static StaticConstructor staticConstructor;

public:
			enum class InnerEnum
			{
				PKB,
				SEMSIM,
				OPB,
				RO,
				BQB,
				BQM,
				RDF,
				DCTERMS,
				DCTERMS11,
				MATHML,
				XLINK,
				CELLML1_0,
				CELLML1_1,
				BQS,
				CMETA,
				DOC,
				VCARD
			};

			const InnerEnum innerEnumValue;
private:
			const std::wstring nameValue;
			const int ordinalValue;
			static int nextOrdinal;

		private:
			std::wstring namespace_Renamed;
			std::wstring owlid;

		public:
			RDFNamespace(const std::wstring &name, InnerEnum innerEnum, const std::wstring &namespace_Renamed, const std::wstring &id);

			/**
			 * @return The RDF namespace as a string (e.g. http://www.w3.org/1998/Math/MathML)
			 */
			virtual std::wstring getNamespaceAsString();

			/**
			 * @return A prefix for the namespace
			 */
			virtual std::wstring getOWLid();

			/**
			 * @return The namespace as a JDom Namespace object
			 */
			virtual org::jdom::Namespace *createJdomNamespace();

public:
			bool operator == (const RDFNamespace &other);

			bool operator != (const RDFNamespace &other);

			static std::vector<RDFNamespace> values();

			int ordinal();

			std::wstring toString();

			static RDFNamespace valueOf(const std::wstring &name);
		};

	}
}