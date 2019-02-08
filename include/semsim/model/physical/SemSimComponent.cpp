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
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
			return !referenceuri->toString()->isEmpty();
		}

		std::optional<bool> SemSimComponent::isPhysicalComponent()
		{
			return false;
		}
	}
}