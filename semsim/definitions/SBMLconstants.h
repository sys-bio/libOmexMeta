#include <string>
#include <unordered_map>
#include <unordered_set>

namespace semsim
{
	namespace definitions
	{
		/**
		 * Convenience sets and mappings for working with SBML models
		 *
		 *
		 */
		class SBMLconstants
		{

		public:
			static const std::unordered_map<std::wstring, std::wstring> SBML_LEVEL_2_RESERVED_UNITS_MAP;
			static Set<std::wstring> *const SBML_LEVEL_3_BASE_UNITS;
			static Set<std::wstring> *const SBML_LEVEL_2_VERSION_2_BASE_UNITS;
			static Set<std::wstring> *const SBML_LEVEL_2_VERSION_1_BASE_UNITS;

			static Set<URI*> *const OPB_PROPERTIES_FOR_COMPARTMENTS;
			static Set<URI*> *const OPB_PROPERTIES_FOR_SPECIES;
			static Set<URI*> *const OPB_PROPERTIES_FOR_REACTIONS;

				private:
					class StaticConstructor
					{
					public:
						StaticConstructor();
					};

				private:
					static SBMLconstants::StaticConstructor staticConstructor;

		};

	}
}