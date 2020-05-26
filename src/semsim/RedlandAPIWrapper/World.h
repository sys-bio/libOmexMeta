//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_WORLD_H
#define LIBSEMSIM_WORLD_H

#include "librdf.h"

#include <iostream>
#include <memory>
#include <regex>

//#include "LibrdfStorage.h"
//#include "RaptorWorld.h"
//#include "LibrdfModel.h"
//#include "LibrdfNode.h"
//#include "LibrdfUri.h"
//#include "LibrdfSerializer.h"
//#include "LibrdfParser.h"
//#include "LibrdfQuery.h"


//#include "semsim/SemsimUtils.h"
//#include "semsim/Subject.h"
//#include "semsim/Predicate.h"

/*
 * A useful comment made by a stackoverflow wizard in a question
 * I asked:
 *  https://stackoverflow.com/questions/61972493/how-to-generalize-this-c-wrapper-around-a-c-class?noredirect=1#comment109609206_61972493
 *
 * A thunk is a small function used to basically call another
 * function and pass along the parameters as arguments to the
 * actual implementation function. It's a glue function.
 * The approach you're taking will help with object ownership
 * and life-cycle management and allow for RAII (so the destructor
 * can do the clean up), which I like. I've wrapped C libraries
 * before, it starts out a bother, but gets easier as you go.
 */

namespace semsim {

    typedef std::shared_ptr<librdf_world> librdf_world_ptr;

    /*
     * @brief C++ wrapper around librdf_world.
     *
     * World is a singleton
     * class. Other classes can use the World
     * by call to World::getWorld(). To implement
     * the singleton, librdf_world* is allocated statically
     * and therefore does not need to be destructed in the
     * way that the other wrapper classes need to be
     * (i.e. stack not heap)
     */
    class World {

        static librdf_world *world_;

        /*
         * Private constructor prevents instancing
         */
        World();

    public:

        static librdf_world *getWorld();

        static raptor_world *getRaptor();

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

#endif //LIBSEMSIM_WORLD_H


















