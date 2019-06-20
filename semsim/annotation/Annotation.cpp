#include "Annotation.h"
#include "Relation.h"

namespace semsim {
    using namespace org::apache::commons::lang3::builder;

    Annotation::Annotation(Relation* relation, std::any value) {
        this->relation = relation;
        this->setValue(value);
    }

    Annotation::Annotation(Relation* relation, std::any value, const std::wstring& valueDescription) {
        this->relation = relation;
        setValue(value);
        setValueDescription(valueDescription);
    }

    Annotation::Annotation(const Annotation& tocopy) {
        if (tocopy->valueDescription != L"") {
            valueDescription = std::wstring(tocopy->valueDescription);
        }
        relation = tocopy->relation;
        value = tocopy->value;
    }

    void Annotation::setValueDescription(const std::wstring& valueDescription) {
        this->valueDescription = valueDescription;
    }

    std::wstring Annotation::getValueDescription() {
        return valueDescription;
    }

    void Annotation::setRelation(Relation* relation) {
        this->relation = relation;
    }

    Relation* Annotation::getRelation() {
        return relation;
    }

    void Annotation::setValue(std::any value) {
        this->value = value;
    }

    std::any Annotation::getValue() {
        return value;
    }

    Annotation* Annotation::clone() throw(CloneNotSupportedException) {
        return static_cast<Annotation*>(__super::clone());
    }

    int Annotation::hashCode() {
        return value.hashCode();
    }

    bool Annotation::equals(std::any obj) {
        if (!(dynamic_cast<Annotation*>(obj) != nullptr)) {
            return false;
        }
        if (obj == this) {
            return true;
        }
        Annotation* rhs = std::any_cast<Annotation*>(obj);
        EqualsBuilder tempVar();
        return (&tempVar)->append(relation, rhs->relation)->append(valueDescription, rhs->valueDescription)->append(value, rhs->value).isEquals();
    }
}
