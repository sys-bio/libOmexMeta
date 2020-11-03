//
// Created by Ciaran on 28/10/2020.
//

#include "OmexMetaTestUtils.h"

bool OmexMetaTestUtils::equals(RDF* actual, RDF* expected, const std::string& format) {
    bool equal = *expected == *actual;
    if (!equal){
        std::cout << "Expected does not equal actual: " << std::endl;
        std::cout << "Expected:" <<std::endl;
        std::cout << expected->toString(format) << std::endl;
        std::cout << "Actual : " << std::endl;
        std::cout << actual->toString(format) << std::endl;
    }
    return equal;
}
bool OmexMetaTestUtils::equals(RDF* actual, const std::string& expected_string, const std::string& format) {
    RDF expected = RDF::fromString(expected_string, format);
    bool equal = expected == *actual;
    if (!equal){
        std::cout << "Expected does not equal actual: " << std::endl;
        std::cout << "Expected:" <<std::endl;
        std::cout << expected.toString(format) << std::endl;
        std::cout << "Actual : " << std::endl;
        std::cout << actual->toString(format) << std::endl;
    }
    return equal;
}

bool OmexMetaTestUtils::equals(const Triple& actual, const std::string& expected_string, const std::string& format) {
    RDF actual_rdf;
    actual_rdf.addTriple(actual);

    RDF expected_rdf = RDF::fromString(expected_string);
    bool equal = expected_rdf == actual_rdf;
    if (!equal){
        std::cout << "Expected does not equal actual: " << std::endl;
        std::cout << "Expected:" <<std::endl;
        std::cout << expected_rdf.toString(format) << std::endl;
        std::cout << "Actual : " << std::endl;
        std::cout << actual_rdf.toString(format) << std::endl;
    }
    return equal;
}

bool OmexMetaTestUtils::equals(const Triples& actual, const std::string& expected_string, const std::string& format) {
    RDF actual_rdf;
    actual_rdf.addTriples(actual);

    RDF expected_rdf = RDF::fromString(expected_string);
    bool equal = expected_rdf == actual_rdf;
    if (!equal){
        std::cout << "Expected does not equal actual: " << std::endl;
        std::cout << "Expected:" <<std::endl;
        std::cout << expected_rdf.toString(format) << std::endl;
        std::cout << "Actual : " << std::endl;
        std::cout << actual_rdf.toString(format) << std::endl;
    }
    return equal;
}

bool OmexMetaTestUtils::equals(const std::string& first, const std::string& second, const std::string& first_format, const std::string& second_format) {
    RDF first_rdf = RDF::fromString(first, first_format);
    RDF second_rdf = RDF::fromString(second, second_format);
    bool equal = first_format == second_format;
    if (!equal){
        std::cout << "First rdf string does not equal second rdf string: " << std::endl;
        std::cout << "first:" <<std::endl;
        std::cout << first_rdf.toString("turtle") << std::endl;
        std::cout << "Actual : " << std::endl;
        std::cout << second_rdf.toString("turtle") << std::endl;
    }
    return equal;
}
