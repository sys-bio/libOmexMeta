#include "PropertyType.h"

namespace semsim {
    PropertyType PropertyType::PropertyOfPhysicalEntity("PropertyOfPhysicalEntity", InnerEnum::PropertyOfPhysicalEntity, "State");
    PropertyType PropertyType::PropertyOfPhysicalProcess("PropertyOfPhysicalProcess", InnerEnum::PropertyOfPhysicalProcess, "Rate");
    PropertyType PropertyType::PropertyOfPhysicalForce("PropertyOfPhysicalForce", InnerEnum::PropertyOfPhysicalForce, "Force");
    PropertyType PropertyType::Unknown("Unknown", InnerEnum::Unknown, "Constitutive");

    std::vector<PropertyType> PropertyType::valueList;

    PropertyType::StaticConstructor::StaticConstructor() {
        valueList.push_back(PropertyOfPhysicalEntity);
        valueList.push_back(PropertyOfPhysicalProcess);
        valueList.push_back(PropertyOfPhysicalForce);
        valueList.push_back(Unknown);
    }

    PropertyType::StaticConstructor PropertyType::staticConstructor;
    int PropertyType::nextOrdinal = 0;

    PropertyType::PropertyType(const std::wstring& name, InnerEnum innerEnum, const std::wstring& name) : nameValue(name), ordinalValue(nextOrdinal++), innerEnumValue(innerEnum) {
        _name = name;
    }

    std::wstring PropertyType::ToString() {
        return _name;
    }

    bool PropertyType::operator == (const PropertyType& other) {
        return this->ordinalValue == other.ordinalValue;
    }

    bool PropertyType::operator != (const PropertyType& other) {
        return this->ordinalValue != other.ordinalValue;
    }

    std::vector<PropertyType> PropertyType::values() {
        return valueList;
    }

    int PropertyType::ordinal() {
        return ordinalValue;
    }

    PropertyType PropertyType::valueOf(const std::wstring& name) {
        for (auto enumInstance : PropertyType::valueList) {
            if (enumInstance.nameValue == name) {
                return enumInstance;
            }
        }
    }
}
