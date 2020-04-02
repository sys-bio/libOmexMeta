# include "semsim/Resource.h"
# include "semsim/Component.h"

namespace semsim {

    Url Resource::getURI(Url base) const {
        if (!isLocal())
            return url_;
        else
            return Url(base.fragment(element_->getAnnotation().getMetaId()));
    }

    std::string Resource::humanize() const {
        if (element_)
            return "#" + element_->getAnnotation().getMetaId();
        else if (url_.str() == "https://identifiers.org/GO:0005829")
            return "GO:cytoplasm";
        else if (url_.str() == "https://identifiers.org/CL:0000169")
            return "CL:type B pancreatic cell";
        else if (url_.str() == "http://identifiers.org/CHEBI:17234")
            return "CHEBI:glucose";
        else if (url_.str() == "http://identifiers.org/opb/OPB_00425")
            return "OPB:chemical concentration";
        else if (url_.str() == "http://identifiers.org/opb/OPB_00523")
            return "OPB:spatial volume";
        else
            throw std::runtime_error("Resource not recognized " + url_.str());
    }

    std::ostream &operator<<(std::ostream &os, Resource &resource) {
        os << resource.url_.str();
        return os;
    }

}
