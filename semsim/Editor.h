//
// Created by Ciaran on 4/15/2020.
//

#ifndef LIBSEMGEN_EDITOR_H
#define LIBSEMGEN_EDITOR_H


class XmlAssistant;

#include "XmlAssistant.h"

namespace semsim {

    template<class T>
    class Editor {
    private:
        std::string xml_;
//        XmlAssistantPtr assistantPtr_;

    public:
        std::string addMetaIds() {
            T xmlAssistant(xml_);
            return xmlAssistant.addMetaIds();
        }


        explicit Editor(std::string xml) :
                xml_(std::move(xml)) {
        }

        std::string getMetaIds() {
            return std::__cxx11::string();
        }

        void addAnnotation() {

        }
        //overloaded

        void removeAnnotation() {

        }
        //overloaded

    };


}

#endif //LIBSEMGEN_EDITOR_H
