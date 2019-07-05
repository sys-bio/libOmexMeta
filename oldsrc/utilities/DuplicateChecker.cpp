// #include "DuplicateChecker.h"
//
// namespace semsim {
//     namespace utilities {
//         using SemSimTypes = semsim::definitions::SemSimTypes;
//         using SemSimModel = semsim::model::collection::SemSimModel;
//         using DataStructure = semsim::model::computational::datastructures::DataStructure;
//         using PhysicalEntity = semsim::model::physical::PhysicalEntity;
//         using PhysicalForce = semsim::model::physical::PhysicalForce;
//         using PhysicalProcess = semsim::model::physical::PhysicalProcess;
//         using CompositePhysicalEntity = semsim::model::physical::object::CompositePhysicalEntity;
//
//         void DuplicateChecker::removeDuplicatePhysicalEntities(SemSimModel* model1, SemSimModel* model2) {
//             std::unordered_set<PhysicalEntity*> pes;
//             for (auto pe2 : model2->getPhysicalEntities()) {
//                 PhysicalEntity* pe = pe2;
//                 for (auto pe1 : model1->getPhysicalEntities()) {
//                     if ((pe->hasPhysicalDefinitionAnnotation() || pe->getSemSimType().equals(SemSimTypes::COMPOSITE_PHYSICAL_ENTITY)) && pe1->equals(pe)) {
//                         pe = pe1;
//                     }
//                 }
//                 pes.insert(pe);
//             }
//             model2->setPhysicalEntities(pes);
//             for (auto ds : model2->getDataStructuresWithCompositesEntities()) {
//                 for (auto cpe : model2->getCompositePhysicalEntities()) {
//                     if (ds->getAssociatedPhysicalModelComponent()->equals(cpe)) {
//                         ds->setAssociatedPhysicalModelComponent(cpe);
//                         break;
//                     }
//                 }
//             }
//             for (auto proc : model2->getPhysicalProcesses()) {
//                 removeDuplicateProcessParticipants(proc, model2);
//             }
//             for (auto force : model2->getPhysicalForces()) {
//                 removeDuplicateForceParticipants(force,model2);
//             }
//         }
//
//         void DuplicateChecker::removeDuplicateProcessParticipants(PhysicalProcess* proc, SemSimModel* model) {
//             for (auto part : proc->getParticipants()) {
//                 for (auto proccpe : model->getCompositePhysicalEntities()) {
//                     if (part->equals(proccpe)) {
//                         proc->replaceParticipant(part, proccpe);
//                     }
//                 }
//             }
//         }
//
//         void DuplicateChecker::removeDuplicateForceParticipants(PhysicalForce* force, SemSimModel* model) {
//             for (auto part : force->getParticipants()) {
//                 for (auto proccpe : model->getCompositePhysicalEntities()) {
//                     if (part->equals(proccpe)) {
//                         force->replaceParticipant(part, proccpe);
//                     }
//                 }
//             }
//         }
//     }
// }
