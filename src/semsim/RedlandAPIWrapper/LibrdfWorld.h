//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFWORLD_H
#define LIBSEMSIM_LIBRDFWORLD_H

#include "librdf.h"

#include <iostream>
#include <memory>
#include <regex>

#include "LibrdfStorage.h"
#include "RaptorWorld.h"
#include "LibrdfModel.h"
#include "LibrdfNode.h"
#include "LibrdfUri.h"
#include "LibrdfSerializer.h"
#include "LibrdfParser.h"
#include "LibrdfQuery.h"


//#include "semsim/SemsimUtils.h"
//#include "semsim/Subject.h"
//#include "semsim/Predicate.h"


namespace semsim {

    typedef std::shared_ptr<librdf_world> librdf_world_ptr;
    /*
     * @brief C++ wrapper around librdf_world.
     *
     * LibrdfWorld is a singleton
     * class. Other classes can use the LibrdfWorld
     * by call to LibrdfWorld::getWorld(). To implement
     * the singleton, LibrdfWorld is allocated statically
     * and therefore does not need to be destructed in the
     * way that the other wrapper classes need to be.
     */
    class LibrdfWorld {

        static LibrdfWorld *world_;

        /*
         * @brief Constructor for
         */
        LibrdfWorld();

    public:

        static LibrdfWorld *getWorld();

//        RaptorWorld getRaptor();

//        LibrdfStorage newStorage(const std::string &storage_name = "memory", const std::string &name = "SemsimStorage",
//                                 const char *options_string = nullptr);
//
//        LibrdfModel newModel(LibrdfStorage storage, const char *options_string = nullptr);
//
//        LibrdfNode newNodeUriString(const std::string &string);
//
//        LibrdfNode newNodeUri(LibrdfUri raptorUri) const;
//
//        LibrdfNode newNodeBlank(const std::string &identifier) const;
//
//        LibrdfNode
//        newNodeLiteral(const std::string &literal, const char *xml_language = nullptr, bool is_wf_xml = false) const;
//
//        LibrdfNode newNodeTypedLiteral(
//                const std::string &literal,
//                const std::string &datatypeUri = "http://www.w3.org/2001/XMLSchema#string",
//                const char *xml_language = nullptr) const;
//
//        LibrdfUri newUri(std::string uri_string) const;
//
//        LibrdfStatement newStatementFromNodes(LibrdfNode subject, LibrdfNode predicate, LibrdfNode object) const;
//
//        LibrdfStatement newStatement() const;
//
//        librdf_world *get();
//
//        LibrdfParser newParser(const char *name, std::string mime_type = std::string(),
//                               std::string uri_type = std::string());
//
//
//        LibrdfSerializer newSerializer(const char *name,
//                                       std::string mime_type = std::string(),
//                                       std::string uri_type = std::string());
//
//        LibrdfQuery newQuery(std::string query,
//                             std::string query_language_name = "sparql",
//                             std::string uri = std::string(),
//                             std::string base_uri = std::string());
//
    };


//        LibrdfSerializer newSerializer(std::string name);

//        Subject newSubjectUri(const std::string &subject_value);
//
//        Subject newSubjectBlank(const std::string &subject_value);
//
//        PredicatePtr newPredicate(std::string namespace_, const std::string &term);
}

#endif //LIBSEMSIM_LIBRDFWORLD_H


















