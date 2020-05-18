//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFWORLD_H
#define LIBSEMSIM_LIBRDFWORLD_H

#include "librdf.h"
#include "CWrapper.h"
#include "RaptorWorld.h"
#include "LibrdfModel.h"
#include "LibrdfStorage.h"


namespace semsim {

    class LibrdfWorld : public CWrapper {
        librdf_world *world_;

    public:
        LibrdfWorld();

        ~LibrdfWorld();

        LibrdfWorld(LibrdfWorld &librdfWorld);

        LibrdfWorld &operator=(LibrdfWorld &librdfWorld);

        LibrdfWorld(LibrdfWorld &&librdfWorld) noexcept;

        LibrdfWorld &operator=(LibrdfWorld &&librdfWorld) noexcept;

        librdf_world *getWorld() const;

        bool operator==(const LibrdfWorld &rhs) const;

        bool operator!=(const LibrdfWorld &rhs) const;

        RaptorWorld getRaptor();

//        LibrdfModel newModel(LibrdfStorage librdfStorage);

        LibrdfStorage newStorage(const std::string& storage_name, const std::string& name, const std::string& options_string="");

        LibrdfModel newModel(const LibrdfStorage& storage, const std::string& options_string);
    };
}

#endif //LIBSEMSIM_LIBRDFWORLD_H
