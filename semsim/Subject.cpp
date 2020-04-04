//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Subject.h"

namespace semsim {


    bool Subject::operator==(const Subject &rhs) const {
        return metaId == rhs.metaId;
    }

    bool Subject::operator!=(const Subject &rhs) const {
        return !(rhs == *this);
    }

    std::ostream &operator<<(std::ostream &os, const Subject &subject) {
        os << "Subject(metaId=" << subject.getMetaId() << ")";
        return os;
    }

    const std::string &Subject::getMetaId() const {
        return metaId;
    }


}