//
// Created by Ciaran on 28/10/2020.
//

#ifndef LIBOMEXMETA_OMEXMETATESTUTILS_H
#define LIBOMEXMETA_OMEXMETATESTUTILS_H


#include "omexmeta/RDF.h"

using namespace omexmeta;

class OmexMetaTestUtils {
public:
    static bool equals(RDF *actual, const std::string &expected, const std::string& format = "turtle");

    static bool equals(const Triple &actual, const std::string &expected, const std::string& format = "turtle");

    static bool equals(const Triples &actual, const std::string &expected, const std::string& format = "turtle");

    static bool equals(RDF *actual, RDF *expected, const std::string& format = "turtle");

    bool equals(const std::string &first, const std::string &second, const std::string &first_format="turtle", const std::string &second_format="turtle");
};


#endif//LIBOMEXMETA_OMEXMETATESTUTILS_H
