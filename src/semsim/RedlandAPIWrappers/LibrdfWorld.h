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


//#include "semsim/SemsimUtils.h"
//#include "semsim/Subject.h"
//#include "semsim/Predicate.h"


namespace semsim {

    class LibrdfWorld {
        std::shared_ptr<librdf_world *> world_;

    public:
        LibrdfWorld();

        ~LibrdfWorld();

        LibrdfWorld(const LibrdfWorld &librdfWorld);

        LibrdfWorld(LibrdfWorld &&librdfWorld) noexcept;

        LibrdfWorld &operator=(const LibrdfWorld &librdfWorld);

        LibrdfWorld &operator=(LibrdfWorld &&librdfWorld) noexcept;

        std::shared_ptr<librdf_world *> getWorld() const;

        bool operator==(const LibrdfWorld &rhs) const;

        bool operator!=(const LibrdfWorld &rhs) const;

        bool operator!() const;

        RaptorWorld getRaptor();

        LibrdfStorage newStorage(const std::string &storage_name, const std::string &name,
                                 const char *options_string = nullptr);

        LibrdfModel newModel(const LibrdfStorage &storage, const char *options_string = nullptr);

        LibrdfNode newNodeUriString(const std::string &string) const;

        LibrdfNode newNodeUri(const LibrdfUri &raptorUri) const;

        LibrdfNode newNodeBlank(const std::string &identifier) const;

        LibrdfNode
        newNodeLiteral(const std::string &literal, const char *xml_language = nullptr, bool is_wf_xml = false) const;

        LibrdfNode newNodeTypedLiteral(
                const std::string &literal,
                const std::string &datatypeUri = "http://www.w3.org/2001/XMLSchema#string",
                const char *xml_language = nullptr) const;

        LibrdfUri newUri(std::string uri_string) const;

        LibrdfStatement newStatementFromNodes(LibrdfNode subject, LibrdfNode predicate, LibrdfNode object);

//        LibrdfSerializer newSerializer(std::string name);

//        Subject newSubjectUri(const std::string &subject_value);
//
//        Subject newSubjectBlank(const std::string &subject_value);
//
//        PredicatePtr newPredicate(std::string namespace_, const std::string &term);

    };

}

#endif //LIBSEMSIM_LIBRDFWORLD_H


















