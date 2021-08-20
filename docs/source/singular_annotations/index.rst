=====================
Singular Annotations
=====================

There's a little more to creating new annotations compared to
reading and writing them. There are a few additional classes that need
to be introduced: `Editor`, `SingleAnnotation`, `PersonalInformation`,
`PhysicalEntity`, `PhysicalProcess` and `EnergyDiff`. This document
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


Creating Single Annotations
===========================

A SingularAnnotation object is a typedef'd `omexmeta::Triple` object which is essentially
a wrapper around the `librdf_statement*` object from the Redland Libraries. In this example
we create a simple singular annotation for the top level `model` element of the sbml. We also
add this annotation to our RDF graph and serialize to Turtle syntax.

Simple example of creating a single annotation
----------------------------------------------

.. tabs::

    .. tab:: python

        .. literalinclude:: create_single_annotation_python.py
            :language: python
            :caption: Create a single annotation in Python

        .. literalinclude:: ../../ExampleOutputFiles/create_single_annotation_python.txt
            :caption: Output

    .. tab:: C++

        .. literalinclude:: create_single_annotation_cpp.CPP
            :language: C++
            :caption: Create a single annotation in C++

        .. literalinclude:: ../../ExampleOutputFiles/CreateSingleAnnotationCpp.txt
            :caption: Output

    .. tab:: C

        .. literalinclude:: create_single_annotation_c.CPP
            :language: C
            :caption: Create a single annotation in C

        Output:

        .. literalinclude:: ../../ExampleOutputFiles/CreateSingleAnnotationC.txt
            :caption: Output


The first thing to notice is that the sbml string only has a
single metaid called `ToyModel`, which is the metaid of the model element.
Metaids are essential for annotation, given that you cannot annotate an
element that does not have a metaid.

Using the `generate_new_metaids` argument
-----------------------------------------

If only some of your model elements have metaids,
you can use the third argument to `toEditor`  to automatically
create metaids

.. tabs::

    .. tab:: python

        .. literalinclude:: create_single_annotation_with_metaids_python.py
            :caption: Create a single annotation in Python and create metaids

        .. literalinclude:: ../../ExampleOutputFiles/create_single_annotation_with_metaids_python.txt
            :caption: Output


    .. tab:: C++

        .. literalinclude:: create_single_annotation_with_metaids_cpp.cpp
            :language: C++
            :caption: Create a single annotation in C++ and create metaids

        .. literalinclude:: ../../ExampleOutputFiles/CreateSingleAnnotationWithMetaidsCpp.txt
            :caption: Output

    .. tab:: C

        .. literalinclude:: create_single_annotation_with_metaids_c.cpp
            :language: C
            :caption: Create a single annotation in C and create metaids

        .. literalinclude:: ../../ExampleOutputFiles/CreateSingleAnnotationWithMetaidsC.txt
            :caption: Output

Creating and Serializing a Single Annotation without adding to the model
------------------------------------------------------------------------

In the previous examples, we added the singular annotation we had just constructed to the
RDF graph and then serialized the RDF graph to turtle syntax. It is also
possible to serialize a singular annotation (a typedef'd Triple) and a
set of annotations (a Triples class) without adding the annotations to the
RDF graph.

.. tabs::

    .. tab:: python

        .. literalinclude:: create_single_annotation_no_commit_python.py
            :language: python
            :caption: Create a single annotation in Python and serialize to turtle without commiting the triples to the current RDF graph

        .. literalinclude:: ../../ExampleOutputFiles/create_single_annotation_no_commit_python.txt
            :caption: Output

    .. tab:: C++

        .. literalinclude:: create_single_annotation_no_commit_cpp.CPP
            :language: C++
            :caption: Create a single annotation in C++ and serialize to turtle without commiting the triples to the current RDF graph


        .. literalinclude:: ../../ExampleOutputFiles/CreateSingleAnnotationNoCommitCpp.txt
            :caption: Output

    .. tab:: C

        .. literalinclude:: create_single_annotation_no_commit_c.cpp
            :language: C
            :caption: Create a single annotation in C and serialize to turtle without commiting the triples to the current RDF graph


        .. literalinclude:: ../../ExampleOutputFiles/CreateSingleAnnotationNoCommitC.txt
            :caption: Output

Subjects, Predicates and Resources
==================================

Singular annotations are Triples or RDF statements. Therefore  by definition
they are composed of three nodes (or terms): the subject, the predicate and the
resource. For a more detailed description of what these are, please
refer to the `RDF 1.1: Concepts and Abstract Syntax document <https://www.w3.org/TR/rdf11-concepts/>`_.
The RDF is a very general framework for storing information. In libOmexMeta
we have restricted this generality in accordance with the OmexMeta specification
1.1.

Subject
---------

A subject in libOmexMeta is the metaid of the element being element appended onto
the local namespace. In RDF, the subject is the value of the `about` attribute. To set
the subject of an annotation in libOmexMeta, use the `about()` method. Although
we focus on singular annotations here, this generalizes to the other
of annotations supported by libOmexMeta.

In this example, we have forced the generation of new metaids, which defaults
to `##OmexMetaId` followed by a 4 digit number. Hence the metaid `#OmexMetaId0002`
exists and is the metaid for the `Species` element with the name `"A"`
(see xml above).

.. warning::

    The following example is not a complete example. It will fail because
    a SingularAnnotation is only valid when all three of subject, predicate and
    resource are specified. For brevity, we assume `sbml` is the same as in the
    above examples.

.. tabs:

    .. tab: Python

        .. code-block:: Python
            :caption: Set the subject portion of the RDF triple in Python.

            rdf = RDF()

            with rdf.to_editor(sbml, generate_new_metaids=True) as editor:
                with editor.new_singular_annotation() as singular_annotation:
                    singular_annotation.about('#OmexMetaId0002')

        .. code-block:: C++
            :caption: Set the subject portion of the RDF triple in C++.

            RDF rdf;
            Editor editor = rdf.toEditor(sbml, "sbml", false);
            SingularAnnotation singular_annotation = editor.newSingularAnnotation();
            singular_annotation.about("species0000")

        .. code-block:: C
            :caption: Set the subject portion of the RDF triple in C.

            // create an empty RDF object
            RDF *rdf_ptr = RDF_new();

            // create editor object
            Editor *editor_ptr = RDF_toEditor(rdf_ptr, sbml, true, true);

            // create out annotation
            SingularAnnotation *singular_annotation = Editor_newSingularAnnotation(editor_ptr);
            SingularAnnotation_about(singular_annotation, "species0000");


However, leaving `generate_new_metaids=False` (the default) causes an error,
because the metaid `#OmexMetaId0002` was not found in your model.


.. tabs::

    .. tab:: Python

        .. code-block:: Python
            :caption: Raise error whilst setting the subject portion of the RDF triple in Python.

            rdf = RDF()

            with rdf.to_editor(sbml, generate_new_metaids=True) as editor:
                with editor.new_singular_annotation() as singular_annotation:
                    singular_annotation.about('#OmexMetaId0002')

    .. tab:: C++

        .. code-block:: C++
            :caption: Raise error whilst setting the subject portion of the RDF triple in C++.

            RDF rdf;
            Editor editor = rdf.toEditor(sbml, "sbml", false);
            SingularAnnotation singular_annotation = editor.newSingularAnnotation();
            singular_annotation.about("species0000")

    .. tab:: C

        .. code-block:: C
            :caption: Raise error whilst setting the subject portion of the RDF triple in C.

            // create an empty RDF object
            RDF *rdf_ptr = RDF_new();

            // create editor object
            Editor *editor_ptr = RDF_toEditor(rdf_ptr, sbml, OMEXMETA_TYPE_SBML, false);

            // create out annotation
            SingularAnnotation *singular_annotation = Editor_newSingularAnnotation(editor_ptr);
            SingularAnnotation_about(singular_annotation, "species0000");


Predicate
---------

Predicates in libOmexMeta are all subclasses of the Predicate class. Existing predicate
classes include `BiomodelsBiologyQualifier`, `BiomodelsBiologyQualifier`,
`DCTerm`, `SemSim` and `Foaf`. For convenience, these predicate classes
are only ever instantiated using a Factory method, which takes two string arguments:
the namespace and the term, i.e:

.. list-table:: Build in namespaces and prefixes for Predicates.
    :widths: 25 25
    :header-rows: 1

    * - Namespace
      - Prefix
    * - http://xmlns.cppom/foaf/0.1/
      - foaf
    * - http://purl.org/dc/terms/
      - dc
    * - http://biomodels.net/model-qualifiers/"
      - bqmodel
    * - http://biomodels.net/biology-qualifiers/"
      - bqbiol
    * - http://www.bhi.washington.edu/semsim#"
      - semsim

Each of these namespaces are referred to by their prefix. The term portion
of the predicates are by defined by the namespace you are using and can easily
be googled. An alternative strategy however, is simply to "get it wrong"
and run your program and you will be provided with a full list of available
terms for the prefix you are using.

.. warning::

    The following example will fail because the singular annotations
    built are not complete.


.. tabs::

    .. tab:: Python

        .. code-block:: Python
            :caption: Setting the Predicate portion of a singular annotation in Python

            rdf = RDF()

            with rdf.to_editor(sbml, generate_new_metaids=True) as editor:

                # build an annotation with bqbiol predicate
                with editor.new_singular_annotation() as bqbiol_singular_annotation:
                    bqbiol_singular_annotation.set_predicate('bqbiol', 'is')

                # build an annotation with bqmodel predicate
                with editor.new_singular_annotation() as bqmodel_singular_annotation:
                    bqmodel_singular_annotation.set_predicate('bqmodel', 'isDerivedFrom')

                # build an annotation with dcterm predicate
                with editor.new_singular_annotation() as dc_singular_annotation:
                    dc_singular_annotation.set_predicate('dc', 'date')


        .. code-block:: C++
            :caption: Setting the Predicate portion of a singular annotation in C++

            RDF rdf;
            Editor editor = rdf.toEditor(sbml, "sbml", false);

            SingularAnnotation bqbiol_singular_annotation = editor.newSingularAnnotation();
            bqbiol_singular_annotation.setPredicate("bqbiol", "is")

            SingularAnnotation bqmodel_singular_annotation = editor.newSingularAnnotation();
            bqmodel_singular_annotation.setPredicate("bqmodel", "isDerivedFrom")

            SingularAnnotation dc_singular_annotation = editor.newSingularAnnotation();
            dc_singular_annotation.setPredicate("dc", "date")

        .. code-block:: C
            :caption:  Setting the Predicate portion of a singular annotation in C

            // create an empty RDF object
            RDF *rdf_ptr = RDF_new();

            // create editor object
            Editor *editor_ptr = RDF_toEditor(rdf_ptr, sbml, OMEXMETA_TYPE_SBML, false);

            // create out annotation
            SingularAnnotation *bqbiol_singular_annotation = Editor_newSingularAnnotation(editor_ptr);
            SingularAnnotation_setPredicate(singular_annotation, "bqbiol", "is);

            SingularAnnotation *bqmodel_singular_annotation = Editor_newSingularAnnotation(editor_ptr);
            SingularAnnotation_setPredicate(singular_annotation, "bqmodel", "isDerivedFrom);

            SingularAnnotation *bqbiol_singular_annotation = Editor_newSingularAnnotation(editor_ptr);
            SingularAnnotation_setPredicate(singular_annotation, "dc", "date");



It should be noted that these Predicate subclasses in libOmexMeta are only
convenience structures to ease the collection of information from the user.
It is also possible and sometimes necessary to
manually give libOmexMeta the entire predicate string.  In C++, the setPredicate is overloaded
to accept a single string, which indicates that this is a full uri. In C and Python,
this is a different method call - see below.


.. tabs::

    .. tab:: python

        .. literalinclude:: create_single_annotation_predicate_from_uri_python.py
            :language: python
            :caption: Create a single annotation in Python using an arbitrary uri

        .. literalinclude:: ../../ExampleOutputFiles/create_single_annotation_predicate_from_uri_python.txt
            :caption: Output

    .. tab:: C++

        .. literalinclude:: create_single_annotation_predicate_from_uri_cpp.cpp
            :language: C++
            :caption: Create a single annotation in C++ using an arbitrary uri

        .. literalinclude:: ../../ExampleOutputFiles/CreateSingleAnnotationPredicateFromUriCpp.txt
            :caption: Output

    .. tab:: C

        .. literalinclude:: create_single_annotation_predicate_from_uri_c.cpp
            :language: C
            :caption: Create a single annotation in C using an arbitrary uri

        .. literalinclude:: ../../ExampleOutputFiles/CreateSingleAnnotationPredicateFromUriC.txt
            :caption: Output

Resources
----------

A resource node can be any of the three types of node: a literal, uri or a blank node. Separate
methods exist for each of these. In the next example we create a set of singular annotations
that demonstrate the various usages of Resource.


.. tabs::

    .. tab:: Python

        .. literalinclude:: create_single_annotation_resource_python.py
            :language: python
            :caption: Demonstration of options for the resource node in Python

        .. literalinclude:: ../../ExampleOutputFiles/create_single_annotation_resource_python.txt
            :caption: Output

    .. tab:: C++

        .. literalinclude:: create_single_annotation_resource_cpp.cpp
            :language: c++
            :caption: Demonstration of options for the resource node in C++

        .. literalinclude:: ../../ExampleOutputFiles/CreateSingleAnnotationResourceCpp.txt
            :caption: Output

    .. tab:: C

        .. literalinclude:: create_single_annotation_resource_c.cpp
            :language: C
            :caption: Demonstration of options for the resource node in C

        .. literalinclude:: ../../ExampleOutputFiles/CreateSingleAnnotationResourceC.txt
            :caption: Output




