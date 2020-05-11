//
// Created by Ciaran on 5/8/2020.
//

#ifndef LIBSEMSIM_SEMSIMCAPI_H
#define LIBSEMSIM_SEMSIMCAPI_H

#include "RDF.h"

#ifdef __cplusplus
extern "C" {
#endif

semsim::RDF *RDF() ;

void RDF_fromString(semsim::RDF *rdf_ptr, const char *str, const char *format);


#ifdef __cplusplus
}
#endif




#endif //LIBSEMSIM_SEMSIMCAPI_H
