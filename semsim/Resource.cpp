# include "semsim/Resource.h"
# include "semsim/Component.h"

namespace semsim {

  URI Resource::getURI(const URI& base) const {
    if (!isLocal())
      return uri_;
    else
      return URI(base.withFrag(element_->getAnnotation().getMetaId()));
  }

  std::string Resource::humanize() const {
    if (element_)
      return "#"+element_->getAnnotation().getMetaId();
    else if (uri_ == "https://identifiers.org/GO:0005829")
      return "cytoplasm";
    else if (uri_ == "https://identifiers.org/CL:0000169")
      return "type B pancreatic cell";
    else if (uri_ == "http://identifiers.org/CHEBI:17234")
      return "glucose";
    else if (uri_ == "http://identifiers.org/opb/OPB_00425")
      return "chemical concentration";
    else if (uri_ == "http://identifiers.org/opb/OPB_00523")
      return "spatial volume";
    else
      throw std::runtime_error("Resource not recognized "+uri_.toString());
  }

}
