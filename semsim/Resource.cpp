# include "semsim/Resource.h"
# include "semsim/Component.h"

namespace semsim {

URI Resource::getURI(const URI& base) const {
  if (!isLocal())
    return uri_;
  else
    return URI(base.withFrag(element_->getAnnotation().getMetaId()));
}

}
