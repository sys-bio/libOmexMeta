Creating, removing and editing annotations
============================================

There's a little more to creating new annotations compared to
reading and writing them. There are a few additional classes that need
to be introduced: `Editor`, `SingleAnnotation`, `PersonalInformation`,
`PhysicalEntity`, `PhysicalProcess` and `PhysicalForce`. This document
assumes background knowledge in what these different types of annotations are.

To demonstrate libOmexMeta we first generate a sbml document using
tellurium and antimony.

.. code-block:: python

    import tellurium as te
    ant = """
    model ToyModel
        compartment cytosol = 1.0;
        A in cytosol;
        B in cytosol
        A = 10;
        B = 0;
        k1 = 0.1;
        k2 = 0.1;
        r1: A => B; k1*A
        r1: B => A; k2*B
    end"""
    sbml = te.antimonyToSBML(ant)
    print(sbml)

Which produces:

.. code-block:: xml

    <?xml version="1.0" encoding="UTF-8"?>
    <!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->
    <sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
      <model metaid="ToyModel" id="ToyModel">
        <listOfCompartments>
          <compartment id="cytosol" spatialDimensions="3" size="1" constant="true"/>
        </listOfCompartments>
        <listOfSpecies>
          <species id="A" compartment="cytosol" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
          <species id="B" compartment="cytosol" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
        </listOfSpecies>
        <listOfParameters>
          <parameter id="k1" value="0.1" constant="true"/>
          <parameter id="k2" value="0.1" constant="true"/>
        </listOfParameters>
        <listOfReactions>
          <reaction id="r1" reversible="false" fast="false">
            <listOfReactants>
              <speciesReference species="B" stoichiometry="1" constant="true"/>
            </listOfReactants>
            <listOfProducts>
              <speciesReference species="A" stoichiometry="1" constant="true"/>
            </listOfProducts>
            <kineticLaw>
              <math xmlns="http://www.w3.org/1998/Math/MathML">
                <apply>
                  <times/>
                  <ci> k2 </ci>
                  <ci> B </ci>
                </apply>
              </math>
            </kineticLaw>
          </reaction>
        </listOfReactions>
      </model>
    </sbml>


Creating a single annotation
----------------------------

A SingularAnnotation object is a typedef'd `omexmeta::Triple` object which is essentially
a wrapper around the `librdf_statement*` object from the Redland Libraries. In this example
we create a simple singular annotation for the top level `model` element of the sbml. We also
add this annotation to our RDF graph and serialize to Turtle syntax.

.. tabs::

    .. tab:: python

        .. literalinclude:: create_single_annotation_python.py
            :linenos:
            :language: python
            :caption: Create a single annotation in Python

        Output:

        .. code-block::

            ['ToyModel']
            @prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
            @prefix dcterms: <http://purl.org/dc/terms/> .
            @prefix myOMEXlib: <http://omex-library.org/> .
            @prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
            @prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

            local:ToyModel
                dcterms:description "This is a toy model for demonstration purposes"^^rdf:string .

    .. tab:: C++

        .. literalinclude:: create_single_annotation_cpp.cpp
            :linenos:
            :language: C++
            :caption: Create a single annotation in C++

        Output:

        .. code-block::

            ToyModel,
            @prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
            @prefix dcterms: <http://purl.org/dc/terms/> .
            @prefix myOMEXlib: <http://omex-library.org/> .
            @prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
            @prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

            <http://omex-library.org/NewOmex.omex/NewModel.xml#ToyModel>
                dcterms:description "This is a toy model for demonstration purposes"^^rdf:string .

    .. tab:: C

        .. literalinclude:: create_single_annotation_c.c
            :linenos:
            :language: C
            :caption: Create a single annotation in C

        Output:

        .. code-block::

            ToyModel,
            @prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
            @prefix dcterms: <http://purl.org/dc/terms/> .
            @prefix myOMEXlib: <http://omex-library.org/> .
            @prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
            @prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

            <http://omex-library.org/NewOmex.omex/NewModel.xml#ToyModel>
                dcterms:description "This is a toy model for demonstration purposes"^^rdf:string .


The first thing to notice is that the sbml string only has a
single metaid called `ToyModel`, which is the metaid of the model element.
Metaids are essential for annotation, given that you cannot annotate an
element that does not have a metaid. If only some of your model elements have metaids,
you can use the third argument to `toEditor` which defaults



.. tabs::

    .. tab:: python

        .. literalinclude:: create_single_annotation_with_metaids_python.py
            :linenos:
            :language: python
            :caption: Create a single annotation in Python and create metaids

        Output:

        .. code-block::

            <?xml version="1.0" encoding="UTF-8"?>
            <!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->
            <sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
              <model metaid="ToyModel" id="ToyModel">
                <listOfCompartments>
                  <compartment id="cytosol" spatialDimensions="3" size="1" constant="true" metaid="#OmexMetaId0000"/>
                </listOfCompartments>
                <listOfSpecies>
                  <species id="A" compartment="cytosol" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0001"/>
                  <species id="B" compartment="cytosol" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0002"/>
                </listOfSpecies>
                <listOfParameters>
                  <parameter id="k1" value="0.1" constant="true"/>
                  <parameter id="k2" value="0.1" constant="true"/>
                </listOfParameters>
                <listOfReactions>
                  <reaction id="r1" reversible="false" fast="false" metaid="#OmexMetaId0003">
                    <listOfReactants>
                      <speciesReference species="B" stoichiometry="1" constant="true"/>
                    </listOfReactants>
                    <listOfProducts>
                      <speciesReference species="A" stoichiometry="1" constant="true"/>
                    </listOfProducts>
                    <kineticLaw metaid="#OmexMetaId0004">
                      <math xmlns="http://www.w3.org/1998/Math/MathML">
                        <apply>
                          <times/>
                          <ci> k2 </ci>
                          <ci> B </ci>
                        </apply>
                      </math>
                    </kineticLaw>
                  </reaction>
                </listOfReactions>
              </model>
            </sbml>

            @prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
            @prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
            @prefix myOMEXlib: <http://omex-library.org/> .
            @prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
            @prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

            local:OmexMetaId0001
                bqbiol:is <https://identifiers.org/uniprot/P01137> .


    .. tab:: C++

        .. literalinclude:: create_single_annotation_with_metaids_cpp.cpp
            :linenos:
            :language: C++
            :caption: Create a single annotation in C++ and create metaids

        Output:

        .. code-block::

            <?xml version="1.0" encoding="UTF-8"?>
            <!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->
            <sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
              <model metaid="ToyModel" id="ToyModel">
                <listOfCompartments>
                  <compartment id="cytosol" spatialDimensions="3" size="1" constant="true" metaid="#OmexMetaId0000"/>
                </listOfCompartments>
                <listOfSpecies>
                  <species id="A" compartment="cytosol" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0001"/>
                  <species id="B" compartment="cytosol" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0002"/>
                </listOfSpecies>
                <listOfParameters>
                  <parameter id="k1" value="0.1" constant="true"/>
                  <parameter id="k2" value="0.1" constant="true"/>
                </listOfParameters>
                <listOfReactions>
                  <reaction id="r1" reversible="false" fast="false" metaid="#OmexMetaId0003">
                    <listOfReactants>
                      <speciesReference species="B" stoichiometry="1" constant="true"/>
                    </listOfReactants>
                    <listOfProducts>
                      <speciesReference species="A" stoichiometry="1" constant="true"/>
                    </listOfProducts>
                    <kineticLaw metaid="#OmexMetaId0004">
                      <math xmlns="http://www.w3.org/1998/Math/MathML">
                        <apply>
                          <times/>
                          <ci> k2 </ci>
                          <ci> B </ci>
                        </apply>
                      </math>
                    </kineticLaw>
                  </reaction>
                </listOfReactions>
              </model>
            </sbml>

            @prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
            @prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
            @prefix myOMEXlib: <http://omex-library.org/> .
            @prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
            @prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

            <http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0001>
                bqbiol:is <https://identifiers.org/uniprot/P01137> .

    .. tab:: C

        .. literalinclude:: create_single_annotation_with_metaids_c.c
            :linenos:
            :language: C
            :caption: Create a single annotation in C and create metaids

        Output:

        .. code-block::

            <?xml version="1.0" encoding="UTF-8"?>
            <!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->
            <sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
              <model metaid="ToyModel" id="ToyModel">
                <listOfCompartments>
                  <compartment id="cytosol" spatialDimensions="3" size="1" constant="true" metaid="#OmexMetaId0000"/>
                </listOfCompartments>
                <listOfSpecies>
                  <species id="A" compartment="cytosol" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0001"/>
                  <species id="B" compartment="cytosol" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0002"/>
                </listOfSpecies>
                <listOfParameters>
                  <parameter id="k1" value="0.1" constant="true"/>
                  <parameter id="k2" value="0.1" constant="true"/>
                </listOfParameters>
                <listOfReactions>
                  <reaction id="r1" reversible="false" fast="false" metaid="#OmexMetaId0003">
                    <listOfReactants>
                      <speciesReference species="B" stoichiometry="1" constant="true"/>
                    </listOfReactants>
                    <listOfProducts>
                      <speciesReference species="A" stoichiometry="1" constant="true"/>
                    </listOfProducts>
                    <kineticLaw metaid="#OmexMetaId0004">
                      <math xmlns="http://www.w3.org/1998/Math/MathML">
                        <apply>
                          <times/>
                          <ci> k2 </ci>
                          <ci> B </ci>
                        </apply>
                      </math>
                    </kineticLaw>
                  </reaction>
                </listOfReactions>
              </model>
            </sbml>

            @prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
            @prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
            @prefix myOMEXlib: <http://omex-library.org/> .
            @prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
            @prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

            local:OmexMetaId0001
                bqbiol:is <https://identifiers.org/uniprot/P01137> .


In the previous examples, we added the singular annotation we had just constructed to the
RDF graph and then serialized the RDF graph to turtle syntax. It is also
possible to serialize a singular annotation (a typedef'd Triple) and a
set of annotations (a Triples class) without adding the annotations to the
RDF graph.


.. tabs::

    .. tab:: python

        .. literalinclude:: create_single_annotation_no_commit_to_rdf_python.py
            :linenos:
            :language: python
            :caption: Create a single annotation in Python and serialize to turtle without commiting the triples to the current RDF graph

        Output:

        .. code-block::


    .. tab:: C++

        .. literalinclude:: create_single_annotation_no_commit_to_rdf_cpp.cpp
            :linenos:
            :language: C++
            :caption: Create a single annotation in C++ and serialize to turtle without commiting the triples to the current RDF graph

        Output:

        .. code-block::


    .. tab:: C

        .. literalinclude:: create_single_annotation_no_commit_to_rdf_c.c
            :linenos:
            :language: C
            :caption: Create a single annotation in C and serialize to turtle without commiting the triples to the current RDF graph

        Output:

        .. code-block::

And printing the triple before commiting it to the model.

And talk about how the subject, predicate and resource objects work.




