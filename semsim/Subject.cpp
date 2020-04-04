//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Subject.h"

namespace semsim {
    std::string &Subject::getMetaId() {
        return metaId;
    }

    Uri &Subject::getUri() {
        return uri;
    }

    bool Subject::operator==(const Subject &rhs) const {
        return metaId == rhs.metaId &&
               uri == rhs.uri;
    }

    bool Subject::operator!=(const Subject &rhs) const {
        return !(rhs == *this);
    }

    std::ostream &operator<<(std::ostream &os, Subject &subject) {
        os << "Subject(metaId=" << subject.getMetaId() << ", uri=" << subject.getUri().str() << ")";
        return os;
    }


}