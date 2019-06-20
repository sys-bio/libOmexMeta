#include "SemSimComponent.h"

namespace semsim
{
	namespace model
	{
		using SemSimObject = semsim::SemSimObject;
		using SemSimTypes = semsim::definitions::SemSimTypes;
		using SemSimModel = semsim::model::collection::SemSimModel;

		SemSimComponent::SemSimComponent(SemSimTypes type) : semsim::SemSimObject(type)
		{
		}

		SemSimComponent::SemSimComponent(const SemSimComponent &ssctocopy) : semsim::SemSimObject(ssctocopy)
		{
			referenceuri = ssctocopy->referenceuri;
		}

		std::optional<bool> SemSimComponent::hasPhysicalDefinitionAnnotation()
		{
			return !referenceuri->toString()->isEmpty();
		}

		std::optional<bool> SemSimComponent::isPhysicalComponent()
		{
			return false;
		}
	}
}