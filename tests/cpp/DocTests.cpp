//
// Created by Ciaran on 17/07/2020.
//

#include "gtest/gtest.h"
#include "omexmeta/OmexMeta.h"
#include "omexmeta/OmexMetaCApi.h"

using namespace omexmeta;

TEST(DocTests, TestEditorCreateSingleAnnotationCPP) {
    std::string sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                       "<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->\n"
                       "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                       "  <model metaid=\"ToyModel\" id=\"ToyModel\">\n"
                       "    <listOfCompartments>\n"
                       "      <compartment id=\"cytosol\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                       "    </listOfCompartments>\n"
                       "    <listOfSpecies>\n"
                       "      <species id=\"A\" compartment=\"cytosol\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "      <species id=\"B\" compartment=\"cytosol\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "    </listOfSpecies>\n"
                       "    <listOfParameters>\n"
                       "      <parameter id=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
                       "    </listOfParameters>\n"
                       "    <listOfReactions>\n"
                       "      <reaction id=\"r1\" reversible=\"false\" fast=\"false\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw>\n"
                       "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                       "            <apply>\n"
                       "              <times/>\n"
                       "              <ci> k2 </ci>\n"
                       "              <ci> B </ci>\n"
                       "            </apply>\n"
                       "          </math>\n"
                       "        </kineticLaw>\n"
                       "      </reaction>\n"
                       "    </listOfReactions>\n"
                       "  </model>\n"
                       "</sbml>\n";

    // create an empty RDF object
    RDF rdf = RDF();

    // create editor object
    Editor editor = rdf.toEditor(sbml, OMEXMETA_TYPE_SBML);

    // Print out metaids to console
    std::vector<std::string> metaids = editor.getMetaids();
    for (auto &id: metaids) {
        std::cout << id << ", ";
    }
    std::cout << std::endl;

    // create out annotation
    SingularAnnotation singular_annotation = editor.newSingularAnnotation();
    singular_annotation
            .setAbout("ToyModel")
            .setPredicate("dc", "description")
            .setResourceLiteral("This is a toy model for demonstration purposes");

    // in C/C++ we need to manually add the annotation to the editor
    editor.addSingleAnnotation(singular_annotation);

    // The Singular annotation object contains a dynamically allocated
    // librdf_statement* from the redland libraries which must be freed
    // by the caller. Now we've use the singular_annotation object
    // we can release the used memory.
    singular_annotation.freeTriple();

    std::cout << rdf.toString("turtle") << std::endl;
}

TEST(DocTests, TestEditorCreateSingleAnnotationC) {
    const char *sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                       "<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->\n"
                       "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                       "  <model metaid=\"ToyModel\" id=\"ToyModel\">\n"
                       "    <listOfCompartments>\n"
                       "      <compartment id=\"cytosol\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                       "    </listOfCompartments>\n"
                       "    <listOfSpecies>\n"
                       "      <species id=\"A\" compartment=\"cytosol\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "      <species id=\"B\" compartment=\"cytosol\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "    </listOfSpecies>\n"
                       "    <listOfParameters>\n"
                       "      <parameter id=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
                       "    </listOfParameters>\n"
                       "    <listOfReactions>\n"
                       "      <reaction id=\"r1\" reversible=\"false\" fast=\"false\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw>\n"
                       "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                       "            <apply>\n"
                       "              <times/>\n"
                       "              <ci> k2 </ci>\n"
                       "              <ci> B </ci>\n"
                       "            </apply>\n"
                       "          </math>\n"
                       "        </kineticLaw>\n"
                       "      </reaction>\n"
                       "    </listOfReactions>\n"
                       "  </model>\n"
                       "</sbml>\n";

    // create an empty RDF object
    RDF *rdf_ptr = RDF_new();

    // create editor object
    Editor *editor_ptr = RDF_toEditor(rdf_ptr, sbml, OMEXMETA_TYPE_SBML);

    // Print out metaids to console
    int number_of_metaids = Editor_getNumMetaIds(editor_ptr);
    for (int i = 0; i < number_of_metaids; i++) {
        printf("%s", Editor_getMetaId(editor_ptr, i));
    }

    // create out annotation
    SingularAnnotation *singular_annotation = SingularAnnotation_new(editor_ptr);
    SingularAnnotation_setAbout(singular_annotation, "ToyModel");
    SingularAnnotation_setPredicate(singular_annotation, "dc", "description");
    SingularAnnotation_setResourceLiteral(singular_annotation, "This is a toy model for demonstration purposes");

    // in C/C++ we need to manually add the annotation to the editor
    Editor_addSingleAnnotation(editor_ptr, singular_annotation);

    // generate the string
    const char *single_annotation_string = RDF_toString(rdf_ptr, "turtle", "base_uri");
    printf("%s", single_annotation_string);

    free((void *) single_annotation_string);
    SingularAnnotation_delete(singular_annotation);
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);

}

TEST(DocTests, QuickExampleOfRedlandAPI) {
    librdf_world *world = librdf_new_world();
    librdf_storage *storage = librdf_new_storage(world, "memory", "SemsimMemoryStore", nullptr);
    librdf_model *model = librdf_new_model(world, storage, nullptr);

    librdf_statement *statement = librdf_new_statement_from_nodes(
            world,
            librdf_new_node_from_uri_string(
                    world, (const unsigned char *) "https://subject.com"),
            librdf_new_node_from_uri_string(
                    world,
                    (const unsigned char *) "https://predicate.com"),
            librdf_new_node_from_uri_string(
                    world,
                    (const unsigned char *) "https://resource.com")
    );

    librdf_model_add_statement(model, statement);
    librdf_free_statement(statement);
    librdf_free_storage(storage);
    librdf_free_model(model);
    librdf_free_world(world);
}


TEST(DocTests, QuickExampleOfHowIveChangedIt) {
    LibrdfStorage storage;
    LibrdfModel model(storage.get());
    LibrdfStatement statement = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromUriString("https//subject.com").get(),
            LibrdfNode::fromUriString("https//predicate.com").get(),
            LibrdfNode::fromUriString("https//resource.com").get()
    );
    model.addStatement(statement);
    statement.freeStatement();
    model.freeModel();
    storage.freeStorage();
}


TEST(DocTests, SingularAnnotationWithMetaIdsC) {
    const char *sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                   "<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->\n"
                   "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                   "  <model metaid=\"ToyModel\" id=\"ToyModel\">\n"
                   "    <listOfCompartments>\n"
                   "      <compartment id=\"cytosol\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                   "    </listOfCompartments>\n"
                   "    <listOfSpecies>\n"
                   "      <species id=\"A\" compartment=\"cytosol\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                   "      <species id=\"B\" compartment=\"cytosol\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                   "    </listOfSpecies>\n"
                   "    <listOfParameters>\n"
                   "      <parameter id=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
                   "      <parameter id=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
                   "    </listOfParameters>\n"
                   "    <listOfReactions>\n"
                   "      <reaction id=\"r1\" reversible=\"false\" fast=\"false\">\n"
                   "        <listOfReactants>\n"
                   "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                   "        </listOfReactants>\n"
                   "        <listOfProducts>\n"
                   "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                   "        </listOfProducts>\n"
                   "        <kineticLaw>\n"
                   "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                   "            <apply>\n"
                   "              <times/>\n"
                   "              <ci> k2 </ci>\n"
                   "              <ci> B </ci>\n"
                   "            </apply>\n"
                   "          </math>\n"
                   "        </kineticLaw>\n"
                   "      </reaction>\n"
                   "    </listOfReactions>\n"
                   "  </model>\n"
                   "</sbml>\n";

    // create an empty RDF object
    RDF *rdf_ptr = RDF_new();

    // create editor object
    Editor *editor_ptr = RDF_toEditor(rdf_ptr, sbml, OMEXMETA_TYPE_SBML, true);

    // Print out metaids to console
    const char* xml_with_metaids = Editor_getXml(editor_ptr);
    printf("%s\n", xml_with_metaids);

    // create out annotation
    SingularAnnotation *singular_annotation = SingularAnnotation_new(editor_ptr);
    SingularAnnotation_setAbout(singular_annotation, "#OmexMetaId0001");
    SingularAnnotation_setPredicate(singular_annotation, "bqbiol", "is");
    SingularAnnotation_setResourceUri(singular_annotation, "uniprot/P01137");

    // in C/C++ we need to manually add the annotation to the editor
    Editor_addSingleAnnotation(editor_ptr, singular_annotation);

    // generate the string
    const char* single_annotation_string = RDF_toString(rdf_ptr, "turtle", "base_uri");
    printf("%s", single_annotation_string);

    free((void *) single_annotation_string);
    SingularAnnotation_delete(singular_annotation);
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);
}

TEST(DocTests, SingularAnnotationWithMetaIdsCpp) {

    std::string sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                       "<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->\n"
                       "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                       "  <model metaid=\"ToyModel\" id=\"ToyModel\">\n"
                       "    <listOfCompartments>\n"
                       "      <compartment id=\"cytosol\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                       "    </listOfCompartments>\n"
                       "    <listOfSpecies>\n"
                       "      <species id=\"A\" compartment=\"cytosol\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "      <species id=\"B\" compartment=\"cytosol\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "    </listOfSpecies>\n"
                       "    <listOfParameters>\n"
                       "      <parameter id=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
                       "    </listOfParameters>\n"
                       "    <listOfReactions>\n"
                       "      <reaction id=\"r1\" reversible=\"false\" fast=\"false\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw>\n"
                       "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                       "            <apply>\n"
                       "              <times/>\n"
                       "              <ci> k2 </ci>\n"
                       "              <ci> B </ci>\n"
                       "            </apply>\n"
                       "          </math>\n"
                       "        </kineticLaw>\n"
                       "      </reaction>\n"
                       "    </listOfReactions>\n"
                       "  </model>\n"
                       "</sbml>\n";

    // create an empty RDF object
    RDF rdf = RDF();

    // create editor object
    Editor editor = rdf.toEditor(sbml, OMEXMETA_TYPE_SBML, true);

    // Print out metaids to console
    std::string xml_with_metids = editor.getXml();
    std::cout << xml_with_metids << std::endl;

    // create out annotation
    SingularAnnotation singular_annotation = editor.newSingularAnnotation();
    singular_annotation
        .setAbout("#OmexMetaId0001")
        .setPredicate("bqbiol", "is")
        .setResourceUri("uniprot/P01137");

    // in C/C++ we need to manually add the annotation to the editor
    editor.addSingleAnnotation(singular_annotation);

    // The Singular annotation object contains a dynamically allocated
    // librdf_statement* from the redland libraries which must be freed
    // by the caller. Now we've use the singular_annotation object
    // we can release the used memory.
    singular_annotation.freeTriple();

    std::cout << rdf.toString("turtle") << std::endl;
}


TEST(DocTests, SingularAnnotationSerializeWithoutCommitingC) {
    const char *sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                   "<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->\n"
                   "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                   "  <model metaid=\"ToyModel\" id=\"ToyModel\">\n"
                   "    <listOfCompartments>\n"
                   "      <compartment id=\"cytosol\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                   "    </listOfCompartments>\n"
                   "    <listOfSpecies>\n"
                   "      <species id=\"A\" compartment=\"cytosol\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                   "      <species id=\"B\" compartment=\"cytosol\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                   "    </listOfSpecies>\n"
                   "    <listOfParameters>\n"
                   "      <parameter id=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
                   "      <parameter id=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
                   "    </listOfParameters>\n"
                   "    <listOfReactions>\n"
                   "      <reaction id=\"r1\" reversible=\"false\" fast=\"false\">\n"
                   "        <listOfReactants>\n"
                   "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                   "        </listOfReactants>\n"
                   "        <listOfProducts>\n"
                   "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                   "        </listOfProducts>\n"
                   "        <kineticLaw>\n"
                   "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                   "            <apply>\n"
                   "              <times/>\n"
                   "              <ci> k2 </ci>\n"
                   "              <ci> B </ci>\n"
                   "            </apply>\n"
                   "          </math>\n"
                   "        </kineticLaw>\n"
                   "      </reaction>\n"
                   "    </listOfReactions>\n"
                   "  </model>\n"
                   "</sbml>\n";

    // create an empty RDF object
    RDF *rdf_ptr = RDF_new();

    // create editor object
    Editor *editor_ptr = RDF_toEditor(rdf_ptr, sbml, OMEXMETA_TYPE_SBML, true);

    // create out annotation
    SingularAnnotation *singular_annotation = SingularAnnotation_new(editor_ptr);
    SingularAnnotation_setAbout(singular_annotation, "#OmexMetaId0002");
    SingularAnnotation_setPredicate(singular_annotation, "bqbiol", "is");
    SingularAnnotation_setResourceUri(singular_annotation, "uniprot/P01137");

    // generate the string
    const char* single_annotation_string = SingularAnnotation_str(singular_annotation, "turtle", "base_uri");
    printf("%s", single_annotation_string);

    free((void *) single_annotation_string);
    SingularAnnotation_delete(singular_annotation);
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);
}

TEST(DocTests, SingularAnnotationSerializeWithoutCommitingCpp) {

    std::string sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                       "<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->\n"
                       "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                       "  <model metaid=\"ToyModel\" id=\"ToyModel\">\n"
                       "    <listOfCompartments>\n"
                       "      <compartment id=\"cytosol\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                       "    </listOfCompartments>\n"
                       "    <listOfSpecies>\n"
                       "      <species id=\"A\" compartment=\"cytosol\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "      <species id=\"B\" compartment=\"cytosol\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "    </listOfSpecies>\n"
                       "    <listOfParameters>\n"
                       "      <parameter id=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
                       "    </listOfParameters>\n"
                       "    <listOfReactions>\n"
                       "      <reaction id=\"r1\" reversible=\"false\" fast=\"false\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw>\n"
                       "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                       "            <apply>\n"
                       "              <times/>\n"
                       "              <ci> k2 </ci>\n"
                       "              <ci> B </ci>\n"
                       "            </apply>\n"
                       "          </math>\n"
                       "        </kineticLaw>\n"
                       "      </reaction>\n"
                       "    </listOfReactions>\n"
                       "  </model>\n"
                       "</sbml>\n";

    // create an empty RDF object
    RDF rdf = RDF();

    // create editor object
    Editor editor = rdf.toEditor(sbml, OMEXMETA_TYPE_SBML, true);

    // create out annotation
    SingularAnnotation singular_annotation = editor.newSingularAnnotation();
    singular_annotation
        .setAbout("#OmexMetaId0001")
        .setPredicate("bqbiol", "is")
        .setResourceUri("uniprot/P01137");

    std::string singular_annotation_string = singular_annotation.str("turtle");
    std::cout << singular_annotation_string<< std::endl;
    singular_annotation.freeTriple();
}




TEST(DocTests, SingularAnnotationArbitraryPredicateUriC) {
    const char *sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                   "<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->\n"
                   "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                   "  <model metaid=\"ToyModel\" id=\"ToyModel\">\n"
                   "    <listOfCompartments>\n"
                   "      <compartment id=\"cytosol\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                   "    </listOfCompartments>\n"
                   "    <listOfSpecies>\n"
                   "      <species id=\"A\" compartment=\"cytosol\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                   "      <species id=\"B\" compartment=\"cytosol\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                   "    </listOfSpecies>\n"
                   "    <listOfParameters>\n"
                   "      <parameter id=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
                   "      <parameter id=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
                   "    </listOfParameters>\n"
                   "    <listOfReactions>\n"
                   "      <reaction id=\"r1\" reversible=\"false\" fast=\"false\">\n"
                   "        <listOfReactants>\n"
                   "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                   "        </listOfReactants>\n"
                   "        <listOfProducts>\n"
                   "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                   "        </listOfProducts>\n"
                   "        <kineticLaw>\n"
                   "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                   "            <apply>\n"
                   "              <times/>\n"
                   "              <ci> k2 </ci>\n"
                   "              <ci> B </ci>\n"
                   "            </apply>\n"
                   "          </math>\n"
                   "        </kineticLaw>\n"
                   "      </reaction>\n"
                   "    </listOfReactions>\n"
                   "  </model>\n"
                   "</sbml>\n";

    // create an empty RDF object
    RDF *rdf_ptr = RDF_new();

    // create editor object
    Editor *editor_ptr = RDF_toEditor(rdf_ptr, sbml, OMEXMETA_TYPE_SBML, true);

    // create out annotation
    SingularAnnotation *singular_annotation = SingularAnnotation_new(editor_ptr);
    SingularAnnotation_setAbout(singular_annotation, "#OmexMetaId0001");
    SingularAnnotation_setPredicateFromUri(singular_annotation, "https://predicate.com/linker");
    SingularAnnotation_setResourceLiteral(singular_annotation, "New predicate demonstration");

    // in C/C++ we need to manually add the annotation to the editor
    Editor_addSingleAnnotation(editor_ptr, singular_annotation);

    // generate the string
    const char* single_annotation_string = RDF_toString(rdf_ptr, "turtle", "base_uri");
    printf("%s", single_annotation_string);

    free((void *) single_annotation_string);
    SingularAnnotation_delete(singular_annotation);
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);
}

TEST(DocTests, SingularAnnotationArbitraryPredicateUriCpp) {

    std::string sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                       "<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->\n"
                       "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                       "  <model metaid=\"ToyModel\" id=\"ToyModel\">\n"
                       "    <listOfCompartments>\n"
                       "      <compartment id=\"cytosol\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                       "    </listOfCompartments>\n"
                       "    <listOfSpecies>\n"
                       "      <species id=\"A\" compartment=\"cytosol\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "      <species id=\"B\" compartment=\"cytosol\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "    </listOfSpecies>\n"
                       "    <listOfParameters>\n"
                       "      <parameter id=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
                       "    </listOfParameters>\n"
                       "    <listOfReactions>\n"
                       "      <reaction id=\"r1\" reversible=\"false\" fast=\"false\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw>\n"
                       "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                       "            <apply>\n"
                       "              <times/>\n"
                       "              <ci> k2 </ci>\n"
                       "              <ci> B </ci>\n"
                       "            </apply>\n"
                       "          </math>\n"
                       "        </kineticLaw>\n"
                       "      </reaction>\n"
                       "    </listOfReactions>\n"
                       "  </model>\n"
                       "</sbml>\n";

    // create an empty RDF object
    RDF rdf = RDF();

    // create editor object
    Editor editor = rdf.toEditor(sbml, OMEXMETA_TYPE_SBML, true);

    // create out annotation
    SingularAnnotation singular_annotation = editor.newSingularAnnotation();
    singular_annotation
        .setAbout("#OmexMetaId0001")
        .setPredicate("https://predicate.com/linker")
        .setResourceLiteral("New predicate demonstration");

    editor.addSingleAnnotation(singular_annotation);
    singular_annotation.freeTriple();
    std::cout << rdf.toString("turtle") << std::endl;
}
