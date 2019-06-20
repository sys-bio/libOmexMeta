#include <unordered_set>

namespace semsim { namespace model { namespace computational { namespace datastructures { class DataStructure; } } } }
namespace semsim { namespace annotation { class SemSimTermLibrary; } }
namespace semsim { class SemSimLibrary; }
namespace semsim { namespace model { namespace computational { namespace datastructures { class MappableVariable; } } } }

namespace semsim
{
	namespace annotation
	{



		using SemSimLibrary = semsim::SemSimLibrary;
		using DataStructure = semsim::model::computational::datastructures::DataStructure;
		using MappableVariable = semsim::model::computational::datastructures::MappableVariable;

		class AnnotationCopier
		{

			/**
			 * Composite annotation copy between data structures
			 * @param sourceds The {@link DataStructure} containing the composite annotation to copy
			 * @param targetds The {@link DataStructure} to which the composite annotation will be copied
			 */
		public:
			static void copyCompositeAnnotation(DataStructure *sourceds, DataStructure *targetds);

			/**
			 * Composite annotation copy using a SemSimTermLibrary instance
			 * @param lib A SemSimTermLibrary
			 * @param sourceds The {@link DataStructure} containing the composite annotation to copy
			 * @param targetds The {@link DataStructure} to which the composite annotation will be copied
			 */
			static void copyCompositeAnnotation(SemSimTermLibrary *lib, DataStructure *targetds, DataStructure *sourceds);

			static Set<MappableVariable*> *copyAllAnnotationsToMappedVariables(MappableVariable *ds, SemSimLibrary *semsimlib);

			static Set<MappableVariable*> *copyCompositeAnnotationsToMappedVariables(MappableVariable *ds);

			static Set<MappableVariable*> *copyAllAnnotationsToLocallyMappedVariables(MappableVariable *ds, SemSimLibrary *semsimlib);

		private:
			static void copyAllAnnotations(MappableVariable *sourceds, Set<MappableVariable*> *targetdsset, SemSimLibrary *semsimlib);

		public:
			static Set<MappableVariable*> *getAllMappedVariables(MappableVariable *rootds, MappableVariable *ds, Set<MappableVariable*> *runningset);

			static Set<MappableVariable*> *getAllLocallyMappedVariables(MappableVariable *rootds, MappableVariable *ds, Set<MappableVariable*> *runningset);
		};

	}
}