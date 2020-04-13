//
// Created by Ciaran on 4/8/2020.
//

#ifndef LIBSEMGEN_RDF_H
#define LIBSEMGEN_RDF_H

#include <unordered_map>
#include "librdf.h"
#include "Writer.h"

namespace semsim {
    class RDF {
    private:
        librdf_world *world_;
        librdf_storage *storage_;
        librdf_model *model_;
        raptor_world *raptor_world_ptr_;
        std::string name_ = "semsim"; // todo: Unused?
        librdf_uri *uri_; //todo needed?

        typedef std::tuple<librdf_world *, raptor_world *, librdf_storage *, librdf_model *> LibrdfObjectsTuple;

        std::unordered_map<std::string, std::string> namespaces_;

        //todo refactor makeWriter into the writer class only.
        semsim::Writer makeWriter(const std::string &format, const std::string &base_uri);

    public:

        static LibrdfObjectsTuple init();


        RDF();

        ~RDF();

        RDF(const RDF &libRdfModel);

        RDF(RDF &&libRdfModel) noexcept;

        RDF &operator=(const RDF &libRdfModel);

        RDF &operator=(RDF &&libRdfModel) noexcept;

        bool operator==(const RDF &rhs) const;

        bool operator!=(const RDF &rhs) const;

        void setNamespaces(const std::unordered_map<std::string, std::string> &namespaces);

        const std::unordered_map<std::string, std::string> &getNamespaces() const;

        static RDF fromUrl(std::string url);

        static semsim::RDF fromML(const std::string &filename, std::string format);

        static RDF fromRDF(std::string filename);

        static RDF fromOmex(std::string filename_or_url);

        std::string toString(std::string format, std::string base_uri = "./SemsimModel");

        void fromString(const std::string &str, std::string format = "guess");

        void toFile(std::string format);

        void addStatement(std::string subject, std::string predicate, std::string resource);

        static std::ostringstream listOptions();

        void setOption();

    };
}



//    + fromWWW() : static RDF
//    + fromML() : static RDF
//    + fromRDF() : static RDF
//    + fromModel() : static RDF
//    + load
//    + query() : RDF
//    + addStatement() : RDF
//    + removeStatement() : RDF
//    + replaceStatement() : RDF
//    + toString(std::string format) : std::string
//    + toFile(std::string format) : std::string


#endif //LIBSEMGEN_RDF_H
