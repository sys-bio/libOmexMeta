//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMSIM_ANNOTATIONTYPE_H
#define LIBSEMSIM_ANNOTATIONTYPE_H
/*
 * AnnotationType enum is on its own to
 * protect against circular dependecies.
 */
namespace semsim {
    /*
     * Denotes the type of composite annotation in use.
     */
    enum AnnotationType {
        PHYSICAL_ENTITY,
        PHYSICAL_PROCESS,
        PHYSICAL_FORCE,
        SINGULAR,
        UNKNOWN
    };
}


#endif //LIBSEMSIM_ANNOTATIONTYPE_H
