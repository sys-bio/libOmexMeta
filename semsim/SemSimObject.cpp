# include "SemSimObject.h"

namespace semsim {
    SemSimObject::SemSimObject(SemSimTypes type)
      : semsimtype(type) {}

    // SemSimObject::SemSimObject(const SemSimObject& other)
    //   : semsimtype(other.semsimtype),
    //     name(objtocopy.name),
    //     description(other.description),
    //     metadataID(other.metadataID) {}

    const std::string& SemSimObject::getDescription() const {
        return description;
    }

    const std::string& SemSimObject::getName() const {
        return name;
    }

    bool SemSimObject::hasName() const {
        return (name != "" && name != "");
    }

    bool SemSimObject::hasDescription() const {
        if (description != "" && description != "") {
            return true;
        } else {
            return false;
        }
    }

    bool SemSimObject::hasMetadataID() const {
        return (metadataID != "" && metadataID != "");
    }

    void SemSimObject::setName(const std::string& name) {
        this->name = name;
    }

    void SemSimObject::setDescription(const std::string& description) {
        this->description = description;
    }

    void SemSimObject::copyDescription(const SemSimObject& other) {
        setDescription(other.getDescription());
    }

    void SemSimObject::setMetadataID(const std::string& metadataID) {
        if (metadataID != "") {
            this->metadataID = metadataID;
        }
    }

    const std::string& SemSimObject::getMetadataID() const {
        return metadataID;
    }

    // SemSimTypes SemSimObject::getSemSimType() const {
    //     return semsimtype;
    // }

    // URI SemSimObject::getSemSimClassURI() {
    //     return semsimtype.getURI();
    // }
    //
    // bool SemSimObject::isType(SemSimTypes type) {
    //     return type == semsimtype;
    // }
}
