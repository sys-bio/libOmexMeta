//
// Created by Ciaran on 4/15/2020.
//

#ifndef LIBSEMGEN_EDITOR_H
#define LIBSEMGEN_EDITOR_H


class XmlAssistant;

#include "semsim/XmlAssistant.h"
#include "semsim/Predicate.h"
#include "semsim/Resource.h"
#include "semsim/Triple.h"
#include "semsim/RDF.h"

namespace semsim {

    class RDF; // forward declaration

    class Editor {
    private:
        std::string xml_;
        std::vector<std::string> metaids_;
        TripleList triple_list_;
        librdf_world *world_;
        librdf_model *model_;

        // probably need to send our librdf model etc to the editor
    public:
        const TripleList &getTripleList() const;

    public:
        explicit Editor(const std::string &xml, XmlAssistantType type,
                librdf_world *world,
                librdf_model *model);

//        Editor(const Editor &editor);
//
//        Editor(const Editor &&editor) noexcept ;

//        Editor &operator=(const Editor &editor);
//
//        Editor &operator=(const Editor &&editor) noexcept;

        const std::string &getXml() const;

        const std::vector<std::string> &getMetaids() const;


        void addAnnotation(std::string metaid, Predicate predicate, const std::string &resource);

        void addAnnotation(std::string metaid, Predicate cvterm, Resource resource);

        void addAnnotation(Triple triple);

        void addAnnotation(TripleList tripleList);
        //overloaded

        void removeAnnotation() {

        }

        void toRDF(RDF &rdf);

        void checkValidMetaid(const std::string &metaid);


        //overloaded
        // singular signature
        // todo consider whether to change the name 'metaid' to 'about', for rdf:about.
        void addAnnotation(std::string metaid, PredicatePtr predicateptr, const std::string &resource);

        void addAnnotation(std::string metaid, Resource isVersionOf,
                std::string isPropertyOf, Resource is, Resource isPartOf);

        void addAnnotation(std::string metaid, std::string is_version_of_resource, std::string is_property_of_resource,
                           std::string is_resource, std::string is_part_of_resource);
    };


}

#endif //LIBSEMGEN_EDITOR_H
