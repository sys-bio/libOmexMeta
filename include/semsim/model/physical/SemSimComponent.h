#include <string>
#include <optional>

namespace semsim { namespace model { namespace collection { class SemSimModel; } } }

namespace semsim
{
	namespace model
	{

		using SemSimObject = semsim::SemSimObject;
		using SemSimTypes = semsim::definitions::SemSimTypes;
		using SemSimModel = semsim::model::collection::SemSimModel;

		/**
		 * A SemSimComponent is a {@link SemSimObject} that represents a computational 
		 * or physical model element
		 */
		class SemSimComponent : public SemSimObject
		{

		protected:
			URI *referenceuri = URI::create(std::wstring(L""));

		public:
			virtual ~SemSimComponent()
			{
				delete referenceuri;
			}

			SemSimComponent(SemSimTypes type);

			/**
			 * Copy constructor
			 * @param ssctocopy The SemSimComponent to copy
			 */
			SemSimComponent(const SemSimComponent &ssctocopy);

			/** @return Whether the component's physical meaning is defined with an annotation */
			virtual std::optional<bool> hasPhysicalDefinitionAnnotation();

			/** @return Whether the component is a physical component. Method 
			 * is overriden by subclasses. */
			virtual std::optional<bool> isPhysicalComponent();

			/**
			 * Add the component to a specified {@link SemSimModel}
			 * @param model The specified {@link SemSimModel}
			 * @return The SemSimComponent added to the model
			 */
			virtual SemSimComponent *addToModel(SemSimModel *model) = 0;
		};

	}
}