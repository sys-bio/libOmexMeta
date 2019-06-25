// #include <string>
// #include <map>
// #include <unordered_map>
// #include <unordered_set>
// #include <vector>
// #include <algorithm>
// #include <cctype>
// #include <optional>
// #include "stringhelper.h"
// #include "stringbuilder.h"
//
// namespace semsim {
//     namespace model {
//         namespace collection {
//             class SemSimModel;
//         }
//     }
// }
// namespace semsim {
//     namespace model {
//         namespace computational {
//             namespace datastructures {
//                 class DataStructure;
//             }
//         }
//     }
// }
// namespace semsim {
//     namespace model {
//         namespace physical {
//             namespace object {
//                 class CompositePhysicalEntity;
//             }
//         }
//     }
// }
// namespace semsim {
//     class SemSimLibrary;
// }
// namespace semsim {
//     namespace model {
//         namespace computational {
//             namespace units {
//                 class UnitFactor;
//             }
//         }
//     }
// }
// namespace semsim {
//     namespace model {
//         namespace computational {
//             namespace units {
//                 class UnitOfMeasurement;
//             }
//         }
//     }
// }
//
// namespace semsim {
//     using org::apache::commons::lang3::tuple::Pair;
//     using org::jdom::Element;
//
//     using SemSimLibrary = semsim::SemSimLibrary;
//     using SemSimModel = semsim::model::collection::SemSimModel;
//     using DataStructure = semsim::model::computational::datastructures::DataStructure;
//     using UnitFactor = semsim::model::computational::units::UnitFactor;
//     using UnitOfMeasurement = semsim::model::computational::units::UnitOfMeasurement;
//     using PhysicalModelComponent = semsim::model::physical::PhysicalModelComponent;
//     using CompositePhysicalEntity = semsim::model::physical::object::CompositePhysicalEntity;
//
//     /** A collection of utility methods for working with SemSim models */
//     class SemSimUtil {
//
//       public:
//         static const std::wstring mathMLelementStart;
//         static const std::wstring mathMLelementEnd;
//
//       public:
//         enum class regexQualifier {
//             GREEDY,
//             RELUCTANT,
//             POSSESSIVE,
//             NONE
//         };
//
//
//         /**
//          * Removes the FunctionalSubmodel structures within a model. Creates a "flattened"
//          * model where there are no MappableVariables. For merging a model that has a CellML component
//          * structure with one that does not.
//          * @param model The model to flatten
//          * @return Map of the changed data structure names
//          */
//       public:
//         static std::unordered_map<std::wstring, std::wstring> flattenModel(SemSimModel* model);
//
//         /**
//          * Replace all occurrences of a codeword in a model's equations with another
//          *  @param discardedds The {@link DataStructure} representing the codeword you want to replace
//          *  @param keptds The {@link DataStructure} representing the replacement codeword
//          *  @param modelfordiscardedds The model containing the discardedds parameter
//          *  @param oldtext The specific text you want to replace
//          *  @param replacementtext The replacement text
//          *  @param conversionfactor The multiplier needed to ensure unit balance between the replaced codeword
//          *  and the replacement
//          *  @return Whether the parameter "oldtext" is the name of a data structure that is used to compute its
//          *  own derivative
//          */
//         static std::optional<bool> replaceCodewordInAllEquations(DataStructure* discardedds, DataStructure* keptds, SemSimModel* modelfordiscardedds, const std::wstring& oldtext, const std::wstring& replacementtext, Pair<double, std::wstring>* conversionfactor);
//
//         /**
//          * Replace all occurrences of a sub-string within a mathematical expression. Uses greedy qualifier.
//          *  @param exp The expression that will be processed for replacement
//          *  @param kept The replacement string
//          *  @param discarded The string to be replaced
//          *  @return A string containing any replacements
//          */
//         static std::wstring replaceCodewordsInString(const std::wstring& exp, const std::wstring& kept, const std::wstring& discarded);
//
//
//         /**
//          * Replace all occurrences of a sub-string within a mathematical expression. Overloaded method for specifying regex qualifier type.
//          *  @param exp The expression that will be processed for replacement
//          *  @param kept The replacement string
//          *  @param discarded The string to be replaced
//          *  @param qual The type of regex qualifier to use
//          *  @return A string containing any replacements
//          */
//         static std::wstring replaceCodewordsInString(const std::wstring& exp, const std::wstring& kept, const std::wstring& discarded, regexQualifier qual);
//
//         /**
//          *  Collect all the variables in a block of MathML that are inputs for the mathematical expression
//          * @param semsimmodel The source SemSim model
//          * @param mathmlstring The MathML string to process for inputs
//          * @param nameprefixanddelimiter Optional prefix/delimiter pair to use for inputs that are local to a submodel
//          * @return All the variables in a block of MathML that are inputs for the MathML expression
//          */
//         static Set<DataStructure*>* getComputationalInputsFromMathML(SemSimModel* semsimmodel, const std::wstring& mathmlstring, Pair<std::wstring, std::wstring>* nameprefixanddelimiter);
//
//
//         /**
//          * Get names of terms used in a MathML string
//          * @param mathmlstring A MathML string
//          * @param nameprefixanddelimiter Optional prefix/delimiter pair for mapping an input name to a SemSim-formatted name
//          * @return Names of inputs used in MathML mapped to option prefixed names
//          */
//         static std::unordered_map<std::wstring, std::wstring> getInputNamesFromMathML(const std::wstring& mathmlstring, Pair<std::wstring, std::wstring>* nameprefixanddelimiter);
//
//         /**
//          * Set the computational inputs for a DataStructure based on its main MathML block and the MathML
//          * associated with any Event that effects the DataStructure's value.
//          * @param semsimmodel The model containing the DataStructure
//          * @param outputds The DataStructure that will have its computational inputs set
//          * @param prefixanddelimiter An optional prefix and delimiter pair to use for inputs that are local
//          *  to a submodel or function definition, etc.
//          */
//         static void setComputationInputsForDataStructure(SemSimModel* semsimmodel, DataStructure* outputds, Pair<std::wstring, std::wstring>* prefixanddelimiter);
//
//
//         /**
//          * Add the left-hand side of a MathML equation
//          * @param mathmlstring The right-hand side of a MathML equation
//          * @param varname The name of the solved variable
//          * @param isODE Whether the variable is solved with an ODE
//          * @param timedomainname Name of time domain to use in MathML
//          * @return The MathML equation containing both the left- and right-hand side
//          */
//         static std::wstring addLHStoMathML(const std::wstring& mathmlstring, const std::wstring& varname, bool isODE, const std::wstring& timedomainname);
//
//         /**
//          * Create the MathML left-hand side for a variable that is solved using an ODE
//          * @param varname Name of the variable
//          * @param timedomainname Name of the time domain to use when formulating the MathML
//          * @return Left-hand side of the MathML used for a variable that is solved using an ODE
//          */
//         static std::wstring makeLHSforStateVariable(const std::wstring& varname, const std::wstring& timedomainname);
//
//
//
//         /**
//          * Find the right hand side of the equation for a data structure from
//          * the MathML associated with the data structure's computation.
//          * @param mathmlstring The MathML string for the data structure's computation
//          * @param solvedvarlocalname The name of the data structure, stripped of all submodel prefixes
//          * @return A MathML string representing the right hand side of the equation used to compute
//          *  the data structure's value
//          */
//         static std::wstring getRHSofMathML(const std::wstring& mathmlstring, const std::wstring& solvedvarlocalname);
//
//
//         /**
//          * @param mathml Some MathML as a String
//          * @return Whether the MathML includes a left-hand side
//          */
//         static bool mathmlHasLHS(const std::wstring& mathml);
//
//         /**
//          * @param parentofdiffelement The immediate parent element of a <diff/> element
//          * @return The numerator variable of a differential expression (e.g. the "P" in dP/dt)
//          */
//       private:
//         static std::wstring getNumeratorOfDiffEq(Element* parentofdiffelement);
//
//
//         /**
//          * Determine if a given {@link CompositePhysicalEntity} is in the keyset of an input
//          * map that relates {@link PhysicalModelComponent}s to associated URIs
//          * @param cpe An input {@link CompositePhysicalEntity}
//          * @param map A Map that relates {@link PhysicalModelComponent}s to associated URIs
//          * @return The Map key that is equivalent to the input {@link CompositePhysicalEntity}, if present,
//          * otherwise the input {@link CompositePhysicalEntity}
//          */
//       public:
//         template<typename T1>
//         static CompositePhysicalEntity* getEquivalentCompositeEntityIfAlreadyInMap(CompositePhysicalEntity* cpe, std::unordered_map<T1> map);
//
//
//         /** Take collection of DataStructures and return an ArrayList sorted alphabetically
//          * @param collection A set of data structures
//          * @return Alphabetized list of data structures based on their names
//          */
//         static std::vector<DataStructure*> alphebetizeSemSimObjects(Collection<DataStructure*>* collection);
//
//
//         /**
//          * Replace all OPB physical properties with their equivalent in the list contained in the SemSimLibrary; thereby
//          * maintaining a single set of unique property instances
//          * @param model The model containing the properties to regularize
//          * @param lib A SemSimLibrary instance
//          * */
//         static void regularizePhysicalProperties(SemSimModel* model, SemSimLibrary* lib);
//
//         /**
//          * Given a SemSim model, recursively processes custom units and returns all of its units broken down into fundamental base units
//          * @param semsimmodel A SemSim model
//          * @param cfgpath Path to configuration folder
//          * @return HashMap of customUnit:(baseUnit1:exp1, baseUnit:exp2, ...)
//          */
//         static std::unordered_map<std::wstring, Set<UnitFactor*>*> getAllUnitsAsFundamentalBaseUnits(SemSimModel* semsimmodel, const std::wstring& cfgpath);
//
//         /**
//          * Used in tandem with method "getFundamentalBaseUnits" to decompose a unit into its fundamental elements
//          * @param uom Unit to decompose
//          * @param oldExp Exponent applied to the unit from its use as a unit factor in another "parent" unit
//          * @param sslib A SemSimLibrary instance
//          * @return Fundamental set of {@link UnitFactor}s comprising the unit
//          */
//         // TODO: should add a parameter here that allows the user to choose whether they want to decompose into
//         // CellML OR SBML base units
//         // TODO: This should also be rewritten so that for units with more than one
//         // unit factor, the multipliers on all factors for the units should be multiplied first,
//         // then compared. Otherwise, equivalent units might get flagged as unequivalent.
//         // Currently, multipliers are compared for each unit factor.
//         static Set<UnitFactor*>* recurseBaseUnits(UnitOfMeasurement* uom, std::optional<double>& oldExp, SemSimLibrary* sslib);
//
//         /**
//          * Create map of unit names that needed to be changed (i.e. given a valid name)
//          * when writing out a CellML or SBML model
//          * @param semsimmodel The SemSimModel that was written out
//          * @param map An old-to-new name map that will be appended by the method
//          * @return An old-to-new name map that includes mappings between old and new unit names
//          */
//         static std::unordered_map<std::wstring, std::wstring> createUnitNameMap(SemSimModel* semsimmodel, std::unordered_map<std::wstring, std::wstring>& map);
//
//         /**
//          * Create a CellML- and SBML-friendly unit name from an input name
//          * @param oldname An input unit name
//          * @return A CellML- and SBML-friendly unit name
//          */
//         static std::wstring makeValidUnitNameForCellMLorSBML(const std::wstring& oldname);
//     };
// }
