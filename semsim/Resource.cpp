# include "semsim/Resource.h"
# include "semsim/Component.h"

namespace semsim {

URI Resource::getURI() const {
  if (!isLocal())
    return uri_;
  else
    return URI("#"+element_->getAnnotation().getMetaId());
}

}
