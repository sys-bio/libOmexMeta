#include "Annotation.h"
#include "Relation.h"

namespace semsim {

    Annotation::Annotation(const Relation& relation, const Resource& resource)
        : relation_(relation), resource_(resource) {}

    Annotation::Annotation(const Relation& relation,
                           const Resource& resource,
                           const std::string& valueDescription)
        : relation_(relation), resource_(resource), valueDescription_(valueDescription) {}

    // Annotation::Annotation(const Annotation& other)
    //     : relation_(other.reltaion),
    //       resource_(other.resource),
    //       valueDescription_(other.valueDescription) {}

    void Annotation::setValueDescription(const std::string& valueDescription) {
        valueDescription_ = valueDescription;
    }

    const std::string& Annotation::getValueDescription() const {
        return valueDescription_;
    }

    void Annotation::setRelation(const Relation& relation) {
        relation_ = relation;
    }

    const Relation& Annotation::getRelation() const {
        return relation_;
    }

    void Annotation::setResource(const Resource& resource) {
        resource_ = resource;
    }

    const Resource& Annotation::getResource() const {
        return resource_;
    }

    // use equality operator instead
    // bool Annotation::equals(std::any obj) {
    //     if (!(dynamic_cast<Annotation*>(obj) != nullptr)) {
    //         return false;
    //     }
    //     if (obj == this) {
    //         return true;
    //     }
    //     // Annotation* rhs = std::any_cast<Annotation*>(obj);
    //     // EqualsBuilder tempVar();
    //     // return (&tempVar)->append(relation, rhs->relation)->append(valueDescription, rhs->valueDescription)->append(value, rhs->value).isEquals();
    //     return
    // }
}
