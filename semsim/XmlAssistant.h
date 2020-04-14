//
// Created by Ciaran on 4/14/2020.
//

#ifndef LIBSEMGEN_XMLASSISTANT_H
#define LIBSEMGEN_XMLASSISTANT_H


#include <vector>
#include "iostream"

namespace semsim {

    class XmlAssistant {
        std::vector<std::string> valid_elements_;
        std::string base_;

    public:
        XmlAssistant(std::string xml, std::string base = "MetaID");

        void addMetaIds();

        std::string getMetaIds();

    };

}
#endif //LIBSEMGEN_XMLASSISTANT_H
