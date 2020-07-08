//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBOMEXMETA_ANNOTATIONTYPE_H
#define LIBOMEXMETA_ANNOTATIONTYPE_H

/*
 * AnnotationType enum for indicating the type of annotation.
 * For developers: Possibly not needed.
 */
namespace omexmeta {
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


#endif //LIBOMEXMETA_ANNOTATIONTYPE_H
