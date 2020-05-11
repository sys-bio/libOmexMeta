//
// Created by Ciaran on 5/8/2020.
//

#include "SemsimCApi.h"
#include <iostream>

semsim::RDF * rdf_new_ptr(){
    return new semsim::RDF();
}

void RDF_fromString(semsim::RDF *rdf_ptr, const char *str, const char *format) {
    semsim::RDF rdf = semsim::RDF::fromString(std::string(str), std::string(format));
    rdf_ptr = &rdf;
}


//int AFunctionCalledX() {
//    return 4;
//}