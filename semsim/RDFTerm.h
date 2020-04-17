//
// Created by Ciaran on 4/17/2020.
//

#ifndef LIBSEMGEN_RDFTERM_H
#define LIBSEMGEN_RDFTERM_H

#include <string>
#include <memory>
#include <librdf.h>

namespace semsim {
    enum TermType {
        SEMSIM_TERM_URI,
        SEMSIM_TERM_RELATIVE_URI,
        SEMSIM_TERM_IDENTIFIERS_URI,
        SEMSIM_TERM_LITERAL,
        SEMSIM_TERM_BLANK,
        SEMSIM_TERM_NONE,
    };

    class RDFTerm {
        TermType termType = SEMSIM_TERM_NONE;
        librdf_model* model;

    public:
        virtual std::string str() const;

        virtual RDFTerm *clone() const;

        virtual ~RDFTerm() = default;

        virtual librdf_node* toNode() ;
    };

    class URITerm : public RDFTerm {
        TermType termType = SEMSIM_TERM_URI;

        //optional but must be resolvable against the base_iri
        std::string fragment_ = "";

        std::string uri_;
    public:
        const std::string &getUri() const;

        explicit URITerm(std::string uri);

        explicit URITerm(std::string uri, std::string fragment);

        std::string str() const override;

        URITerm *clone() const override;

    };

    class IdentifiersURITerm : public URITerm {
        TermType termType = SEMSIM_TERM_IDENTIFIERS_URI;
        std::string identifiers_uri_ = "https://identifiers/.org";

    public:
        std::string str() const override;

        IdentifiersURITerm *clone() const override;

        explicit IdentifiersURITerm(std::string resource);

    };


    class RelativeURITerm : public URITerm {
        // if relative, iri must be resolvable against base_iri
        TermType termType = SEMSIM_TERM_RELATIVE_URI;
        std::string identifiers_uri_ = "https://identifiers/.org";

    public:
        std::string str() const override;

        RelativeURITerm *clone() const override;

        explicit RelativeURITerm(std::string resource);

    };

    class LiteralTerm : public RDFTerm {
        TermType termType = SEMSIM_TERM_LITERAL;

        std::string literal_;
        // default datatype is string
        std::string datatype_ = "http://www.w3.org/2001/XMLSchema#string";

        // if datatype == language_datatype_str, we must define a language tag
        std::string language_datatype_str_ = "http://www.w3.org/1999/02/22-rdf-syntax-ns#langString";
        std::string language_tag_;

    public:
        std::string str() const override;

        explicit LiteralTerm(std::string literal);

        LiteralTerm(std::string literal, std::string language_tag);

        LiteralTerm *clone() const override;


    };

    class BlankTerm : public RDFTerm {
        TermType termType = SEMSIM_TERM_BLANK;
        std::string term_;

    public:
        std::string str() const override;

        explicit BlankTerm(std::string term);

        BlankTerm *clone() const override;


    };

}

#endif //LIBSEMGEN_RDFTERM_H
