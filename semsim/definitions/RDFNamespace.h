# ifndef SEMSIM_RDF_NAMESPACE_H_
# define SEMSIM_RDF_NAMESPACE_H_

# include <string>
# include <vector>

namespace semsim {
    /**
     * Enumeration of various RDF namespaces used in biosimulation modeling formats.
     *
     */
    class RDFNamespace {
      public:
        static RDFNamespace PKB;
        static RDFNamespace SEMSIM;
        static RDFNamespace OPB;
        static RDFNamespace RO;
        static RDFNamespace BQB;
        static RDFNamespace BQM;
        static RDFNamespace RDF;
        static RDFNamespace DCTERMS;
        static RDFNamespace DCTERMS11;
        static RDFNamespace MATHML;
        static RDFNamespace XLINK;
        static RDFNamespace CELLML1_0;
        static RDFNamespace CELLML1_1;
        static RDFNamespace BQS;
        static RDFNamespace CMETA;
        static RDFNamespace DOC;
        static RDFNamespace VCARD;

      private:
        // static std::vector<RDFNamespace> valueList;

      public:
        // enum class InnerEnum {
        //     PKB,
        //     SEMSIM,
        //     OPB,
        //     RO,
        //     BQB,
        //     BQM,
        //     RDF,
        //     DCTERMS,
        //     DCTERMS11,
        //     MATHML,
        //     XLINK,
        //     CELLML1_0,
        //     CELLML1_1,
        //     BQS,
        //     CMETA,
        //     DOC,
        //     VCARD
        // };

        // const InnerEnum innerEnumValue;
      private:
        const std::string nameValue;
        // const int ordinalValue;
        // static int nextOrdinal;

      private:
        std::string namespace_Renamed;
        std::string owlid;

      public:
        // RDFNamespace(const std::string& name, InnerEnum innerEnum, const std::string& namespace_Renamed, const std::string& id);

        /**
         * @return The RDF namespace as a string (e.g. http://www.w3.org/1998/Math/MathML)
         */
        std::string getNamespaceAsString();

        /**
         * @return A prefix for the namespace
         */
        std::string getOWLid();

        /**
         * @return The namespace as a JDom Namespace object
         */
        // org::jdom::Namespace* createJdomNamespace();

      public:
        // bool operator == (const RDFNamespace& other);

        // bool operator != (const RDFNamespace& other);

        // static std::vector<RDFNamespace> values();

        // int ordinal();

        // std::string toString();

        // static RDFNamespace valueOf(const std::string& name);
    };
}

# endif
