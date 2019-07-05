#include "SemSimComponent.h"

namespace semsim {
    // SemSimComponent::SemSimComponent(SemSimTypes type) : semsim::SemSimObject(type) {
    // }

    // SemSimComponent::SemSimComponent(const SemSimComponent& other) : semsim::SemSimObject(other) {
    //     referenceuri = other.referenceuri;
    // }

    bool SemSimComponent::hasDefinitionAnnotation() {
        return referenceuri.toString().size();
    }

    // bool SemSimComponent::isPhysicalComponent() {
    //     return false;
    // }
}
