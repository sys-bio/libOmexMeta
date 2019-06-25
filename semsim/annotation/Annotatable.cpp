# include "semsim/annotation/Annotatable.h"

namespace semsim {
    const Annotatable::Annotations& Annotatable::getAnnotations() const {
      return annotations_;
    }

    Annotatable::Annotations& Annotatable::getAnnotations() {
      return annotations_;
    }
}
