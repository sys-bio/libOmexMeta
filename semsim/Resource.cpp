# include "semsim/Resource.h"
# include "semsim/Component.h"

namespace semsim {

    Url Resource::getURI(Url base) const {
        if (!isLocal())
            return url_;
        else
            return Url(base.fragment(element_->getAnnotation().getMetaId()));
    }

    /*
     * todo: work out Why are these special Url strings hard coded?
     */
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

    Resource::Resource(Resource &resource) {
        this->url_ = resource.url_;
        this->element_ = resource.element_;
    }

    Resource &Resource::operator=(const Resource &resource) {
        if (this != &resource) {
            this->url_ = resource.url_;
            this->element_ = resource.element_;
        }
        return (*this);
    }

    Resource::Resource(Resource &&resource) noexcept {
        if (this != &resource) {
            this->url_ = resource.url_;
            this->element_ = resource.element_;

            resource.url_ = "";
            resource.element_ = nullptr;
        }
    }

    Resource &Resource::operator=(Resource &&resource) noexcept {
        if (this != &resource) {
            this->url_ = resource.url_;
            this->element_ = resource.element_;

            resource.url_ = "";
            resource.element_ = nullptr;
        }
        return (*this);
    }

    bool Resource::operator==(const Resource &rhs) const {
        return url_ == rhs.url_ &&
               element_ == rhs.element_;
    }

    bool Resource::operator!=(const Resource &rhs) const {
        return !(rhs == *this);
    }

}
