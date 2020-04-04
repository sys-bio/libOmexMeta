//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Subject.h"

namespace semsim {


    bool Subject::operator==(const Subject &rhs) const {
        return metaId == rhs.metaId &&
               uri == rhs.uri;
    }

    bool Subject::operator!=(const Subject &rhs) const {
        return !(rhs == *this);
    }

    std::ostream &operator<<(std::ostream &os, const Subject &subject) {
        os << "Subject(metaId=" << subject.getMetaId() << ", uri=" << subject.getUri().str() << ")";
        return os;
    }

    const std::string &Subject::getMetaId() const {
        return metaId;
    }

    const Uri &Subject::getUri() const {
        return uri;
    }


}