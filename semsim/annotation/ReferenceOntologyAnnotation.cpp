// #include "ReferenceOntologyAnnotation.h"
// #include "Ontology.h"
// #include "../SemSimLibrary.h"
// #include "Relation.h"
//
// namespace semsim {
//     namespace annotation {
//         using SemSimLibrary = semsim::SemSimLibrary;
//
//         ReferenceOntologyAnnotation::ReferenceOntologyAnnotation(Relation* relation, URI* uri, const std::wstring& valueDescription, SemSimLibrary* lib) : Annotation(relation, uri) {
//             refontology = lib->getOntologyfromTermURI(uri->toString());
//             setReferenceURI(uri);
//             setValueDescription(valueDescription);
//         }
//
//         std::wstring ReferenceOntologyAnnotation::getBioPortalOntologyNamespace() {
//             return refontology->getBioPortalNamespace();
//         }
//
//         std::wstring ReferenceOntologyAnnotation::getValueDescription() {
//             if (valueDescription == L"") {
//                 if (getReferenceURI() != nullptr) {
//                     return getReferenceURI()->toString();
//                 } else {
//                     return L"?";
//                 }
//             } else {
//                 return valueDescription;
//             }
//         }
//
//         std::wstring ReferenceOntologyAnnotation::getReferenceOntologyName() {
//             return refontology->getFullName();
//         }
//
//         std::wstring ReferenceOntologyAnnotation::getNamewithOntologyAbreviation() {
//             return valueDescription + L" (" + getOntologyAbbreviation() + L")";
//         }
//
//         std::wstring ReferenceOntologyAnnotation::getOntologyAbbreviation() {
//             return refontology->getNickName();
//         }
//
//         void ReferenceOntologyAnnotation::setReferenceURI(URI* uri) {
//             this->referenceUri = uri;
//         }
//
//         URI* ReferenceOntologyAnnotation::getReferenceURI() {
//             return referenceUri;
//         }
//
//         std::wstring ReferenceOntologyAnnotation::getAltNumericalID() {
//             return altNumericalID;
//         }
//
//         void ReferenceOntologyAnnotation::setAltNumericalID(const std::wstring& ID) {
//             altNumericalID = ID;
//         }
//     }
// }
