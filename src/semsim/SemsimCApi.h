//
// Created by Ciaran on 5/8/2020.
//

#ifndef LIBSEMSIM_SEMSIMCAPI_H
#define LIBSEMSIM_SEMSIMCAPI_H

#include "semsim/RDF.h"
#include "semsim/Editor.h"
#include "semsim/XmlAssistant.h"

namespace semsim {

#ifdef __cplusplus
    extern "C" {
#endif

/***************************************************
 * RDF class methods
 */

    semsim::RDF *RDF_new_ptr();

    void RDF_free(semsim::RDF *rdf_ptr);

    char *RDF_getBaseUri(semsim::RDF *rdf_ptr);

    void RDF_setBaseUri(semsim::RDF *rdf_ptr, const char *uri);

    const char *RDF_toString(semsim::RDF *rdf_ptr, const char *format, const char *base_uri);

    void RDF_fromString(semsim::RDF *rdf_ptr, const char *str, const char *format);

    const char *RDF_queryResultsAsStr(semsim::RDF *rdf_ptr, const char *query_str, const char *results_format);

    int RDF_size(semsim::RDF *rdf_ptr);

    Editor *RDF_toEditor(semsim::RDF *rdf_ptr, const char *xml, semsim::XmlAssistantType type);

//RDF_toFile(semsim::RDF* rdf_ptr, );
//RDF_listOptions(semsim::RDF* rdf_ptr, );
//RDF_setNamespaces(semsim::RDF* rdf_ptr, );
//RDF_getNamespaces(semsim::RDF* rdf_ptr, );
//semsim::RDF* RDF_fromUrl(semsim::RDF* rdf_ptr, const char* url, const char* filename, const char* format);
//semsim::RDF* RDF_fromXML(semsim::RDF* rdf_ptr, const char* filename, const char* format);
//semsim::RDF* RDF_fromFile(semsim::RDF* rdf_ptr, const char* filename, const char* format);
//semsim::RDF* RDF_fromOmex(semsim::RDF* rdf_ptr, const char* filename_or_uri, const char* format);

/*********************************************
 *  Editor class
 */


#ifdef __cplusplus
    }
#endif
}

#endif //LIBSEMSIM_SEMSIMCAPI_H

























