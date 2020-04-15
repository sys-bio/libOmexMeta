//
// Created by Ciaran on 4/15/2020.
//

#ifndef LIBSEMGEN_EDITOR_H
#define LIBSEMGEN_EDITOR_H


class XmlAssistant;

#include "XmlAssistant.h"
#include "Predicate.h"
#include "Resource.h"
#include "Triple.h"

namespace semsim {

    class Editor {
    private:
        std::string xml_;
        std::vector<std::string> metaids_;

    public:
        const std::string &getXml() const;

        const std::vector<std::string> &getMetaids() const;

        explicit Editor(std::string xml, XmlAssistantType type);

        void addAnnotation(std::string metaid, Predicate cvterm, std::string resource) ;
        void addAnnotation(std::string metaid, Predicate cvterm, Resource resource) ;
        void addAnnotation(Triple triple);
        void addAnnotation(TripleList tripleList);
        //overloaded

        void removeAnnotation() {

        }
        //overloaded

    };


}

#endif //LIBSEMGEN_EDITOR_H
