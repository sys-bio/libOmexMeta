# include "semsim/SingularAnnotation.h"
# include "semsim/CompositeAnnotation.h"

namespace semsim {

    AnnotationPtr SingularAnnotation::makeComposite(PhysicalProperty &prop) {
        return AnnotationPtr(new CompositeAnnotation(*this, prop));
    }

}
