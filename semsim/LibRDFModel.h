//
// Created by Ciaran on 4/8/2020.
//

#ifndef LIBSEMGEN_LIBRDFMODEL_H
#define LIBSEMGEN_LIBRDFMODEL_H

#include "librdf.h"

namespace semsim {
    class LibRDFModel {
    private:
        librdf_world *world;
        librdf_storage *storage;
        librdf_parser *parser;
        librdf_serializer *serializer;
        librdf_model *model;
        raptor_world *raptor_world_ptr;
        std::string name = "semsim";
        librdf_uri *uri;


    public:

        LibRDFModel();

        ~LibRDFModel();

        LibRDFModel(const LibRDFModel &libRdfModel);

        LibRDFModel(LibRDFModel &&libRdfModel) noexcept;

        LibRDFModel &operator=(const LibRDFModel &libRdfModel);

        LibRDFModel &operator=(LibRDFModel &&libRdfModel) noexcept;

        bool operator==(const LibRDFModel &rhs) const;

        bool operator!=(const LibRDFModel &rhs) const;

        static LibRDFModel fromUrl(std::string url);

        static LibRDFModel fromML(std::string filename);

        static LibRDFModel fromRDF(std::string filename);

        void fromString(std::string str);

        void toString(std::string format);

        void toFile(std::string format);


//    + fromWWW() : static LibRDFModel
//    + fromML() : static LibRDFModel
//    + fromRDF() : static LibRDFModel
//    + fromString() : static LibRDFModel
//    + query() : LibRDFModel
//    + addStatement() : LibRDFModel
//    + removeStatement() : LibRDFModel
//    + replaceStatement() : LibRDFModel
//    + toString(std::string format) : std::string
//    + toFile(std::string format) : std::string

    };
}

#endif //LIBSEMGEN_LIBRDFMODEL_H
