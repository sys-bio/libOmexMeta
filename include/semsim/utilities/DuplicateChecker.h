#include <unordered_set>

namespace semsim { namespace model { namespace collection { class SemSimModel; } } }
namespace semsim { namespace model { namespace physical { class PhysicalProcess; } } }
namespace semsim { namespace model { namespace physical { class PhysicalForce; } } }

namespace semsim
{
	namespace utilities
	{


		using SemSimModel = semsim::model::collection::SemSimModel;
		using PhysicalForce = semsim::model::physical::PhysicalForce;
		using PhysicalProcess = semsim::model::physical::PhysicalProcess;

		/**
		 * Utility class for finding and removing duplicate instances of the same annotation in two models
		 * The duplicate instance is replaced with the instance in the first model
		 * This allows for much faster comparisons during the mapping phase of a merge
		 * **/
		class DuplicateChecker
		{

		public:
			static void removeDuplicatePhysicalEntities(SemSimModel *model1, SemSimModel *model2);


			/**
			 * Make sure that process participants are not duplicates of {@link CompositePhysicalEntity}s
			 * already in the model
			 * @param proc A {@link PhysicalProcess} object
			 * @param model The {@link SemSimModel} containing the process
			 */
		private:
			static void removeDuplicateProcessParticipants(PhysicalProcess *proc, SemSimModel *model);

			/**
			 * Make sure that force participants are not duplicates of {@link CompositePhysicalEntity}s
			 * already in the model
			 * @param force A {@link PhysicalForce} object
			 * @param model The {@link SemSimModel} containing the force
			 */
			static void removeDuplicateForceParticipants(PhysicalForce *force, SemSimModel *model);

		};

	}
}