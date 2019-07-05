// #include "Annotation.h"
// #include <string>
// namespace semsim {
//     namespace annotation {
//         class Ontology;
//     }
// }
// namespace semsim {
//     class SemSimLibrary;
// }
// namespace semsim {
//     namespace annotation {
//         class Relation;
//     }
// }
//
// namespace semsim {
//     namespace annotation {
//
//
//         using SemSimLibrary = semsim::SemSimLibrary;
//
//         /**
//          * A type of Annotation where the annotation value is a URI
//          * from a reference ontology or other controlled knowledge base.
//          */
//         class ReferenceOntologyAnnotation : public Annotation {
//           private:
//             Ontology* refontology;
//             URI* referenceUri;
//             std::wstring altNumericalID;
//
//             /**
//              * Constructor for annotation
//              * @param relation The relationship between the object being annotated and the knowledge base URI
//              * @param uri The URI annotation value
//              * @param valueDescription A free-text description of the resource corresponding to the URI
//              * @param lib A SemSimLibrary instance
//              */
//           public:
//             virtual ~ReferenceOntologyAnnotation() {
//                 delete refontology;
//                 delete referenceUri;
//             }
//
//             ReferenceOntologyAnnotation(Relation* relation, URI* uri, const std::wstring& valueDescription, SemSimLibrary* lib);
//
//             /**
//              * @return The BioPortal Ontology namespace of the knowledge base that contains the URI annotation value
//              */
//             virtual std::wstring getBioPortalOntologyNamespace();
//
//             /**
//              * @return The free-text description of the resource corresponding to the URI
//              */
//             std::wstring getValueDescription() override;
//
//             /**
//              * @return The name of the knowledge base that contains the URI used as the annotation value
//              */
//             virtual std::wstring getReferenceOntologyName();
//
//             /**
//              * @return The name of the knowledge base that contains the URI used as the annotation value
//              */
//             virtual std::wstring getNamewithOntologyAbreviation();
//
//             /**
//              * @return The abbreviation of the knowledge base containing the URI used for the annotation value
//              */
//             virtual std::wstring getOntologyAbbreviation();
//
//             /**
//              * Set the URI annotation value
//              * @param uri The URI to reference
//              */
//             virtual void setReferenceURI(URI* uri);
//
//             /**
//              * @return The URI used as the annotation value
//              */
//             virtual URI* getReferenceURI();
//
//             /**
//              * @return A numerical ID for the reference concept (only used to
//              * map Foundational Model of Anatomy URIs to their numerical FMA IDs.
//              */
//             virtual std::wstring getAltNumericalID();
//
//             /**
//              * @param ID The numerical ID of the reference term (only used for
//              * the Foundational Model of Anatomy)
//              */
//             virtual void setAltNumericalID(const std::wstring& ID);
//         };
//
//     }
// }
