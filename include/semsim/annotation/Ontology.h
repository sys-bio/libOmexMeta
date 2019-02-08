#include "../definitions/ReferenceOntologies.h"
#include <string>
#include <vector>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace semsim { namespace definitions { class ReferenceOntologies; } }

namespace semsim
{
	namespace annotation
	{


		using ReferenceOntology = semsim::definitions::ReferenceOntologies::ReferenceOntology;

		/**
		 * Class representing identifier information about an ontology.
		 * This includes the ontology's full name, BioPortal namespace,
		 * textual description, etc.
		 */
		class Ontology
		{
		private:
			std::wstring fullname;
			std::wstring nickname;
			std::wstring bioportalnamespace;
			std::vector<std::wstring> namespaces = std::vector<std::wstring>();
			std::wstring description;

			/**
			 * @param name Full name of ontology
			 * @param abrev Nickname of ontology
			 * @param ns Array of namespaces used for this ontology
			 * @param desc Textual description of ontology
			 * @param bpns BioPortal namespace of the ontology
			 */
		public:
			Ontology(const std::wstring &name, const std::wstring &abrev, std::vector<std::wstring> &ns, const std::wstring &desc, const std::wstring &bpns);

			/**
			 * @param name Full name of ontology
			 * @param abrev Nickname of ontology
			 * @param ns Array of namespaces used for this ontology
			 * @param desc Textual description of ontology
			 */
			Ontology(const std::wstring &name, const std::wstring &abrev, std::vector<std::wstring> &ns, const std::wstring &desc);

			/**
			 * Constructor for creating an {@link Ontology} class
			 * from a {@link ReferenceOntology} class
			 * @param ro The {@link ReferenceOntology} that will have
			 * its information copied to this class.
			 */
			Ontology(ReferenceOntology ro);

			/**
			 * @param nspace Namespace to test for association with the ontology
			 * @return Whether the namespace is in the array of namespaces associated
			 * with this ontology
			 */
			virtual bool hasNamespace(const std::wstring &nspace);

			/**
			 * @return Full name of ontology
			 */
			virtual std::wstring getFullName();

			/**
			 * @return Nickname of ontology
			 */
			virtual std::wstring getNickName();

			/**
			 * @return The BioPortal namespace of the ontology
			 */
			virtual std::wstring getBioPortalNamespace();

			/**
			 * @return The set of namespaces associated with the ontology
			 */
			virtual std::vector<std::wstring> getNameSpaces();

			/**
			 * @return A free-text description of the ontology
			 */
			virtual std::wstring getDescription();
		};

	}
}