//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFWORLD_H
#define LIBSEMSIM_LIBRDFWORLD_H

#include "librdf.h"

#include <iostream>
#include <memory>
#include <regex>
#include <semsim/Predicate.h>

#include "LibrdfStorage.h"
#include "semsim/SemsimUtils.h"

#include "RaptorWorld.h"
#include "LibrdfModel.h"
#include "LibrdfStorage.h"
#include "LibrdfNode.h"
#include "LibrdfUri.h"

#include "semsim/Subject.h"
#include "semsim/Predicate.h"


namespace semsim {

    class Predicate;


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
                                 const std::string &options_string = std::string());

        LibrdfModel newModel(const LibrdfStorage &storage, const std::string &options_string = std::string());

        LibrdfNode newNodeUriString(const std::string &string);

        LibrdfNode newNodeUri(const LibrdfUri &raptorUri);

        LibrdfNode newNodeBlank(const std::string &identifier);

        LibrdfNode
        newNodeLiteral(const std::string &literal, const char *xml_language = nullptr, bool is_wf_xml = false);

        LibrdfNode newNodeTypedLiteral(
                const std::string &literal,
                const std::string &datatypeUri = "http://www.w3.org/2001/XMLSchema#string",
                const char *xml_language = nullptr);

        LibrdfUri newUri(const std::string &uri_string);

        Subject newSubjectUri(const std::string &subject_value);

        Subject newSubjectBlank(const std::string &subject_value);

        PredicatePtr newPredicate(std::string namespace_, const std::string &term);

    };

}

#endif //LIBSEMSIM_LIBRDFWORLD_H


















