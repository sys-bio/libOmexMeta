Composite Annotations: SBML Examples
====================================


Annotations on a Physical Entity
-----------------------------------------------

In this case we build a new model using tellurium and antimony in Python.
For simplicity, the string was copied from Python and stored as a string
for the C++ and C examples.

In the example we create a PhysicalEntity type annotation of A, which
has the metid `SpeciesA`. Our annotation states that we are
simulating the chemical concetration (OPB:OPB_00340) of Smad3 (`uniprot/P84022') in the
dermal fibroblasts `fma/FMA:63877` of the dermal papilla `fma:FMA:70737` in the
skin `FMA_7163` of the surface or the arm `FMA:24178`.

.. note::

    You can add an arbitrary number of anatomical locations, but the order you
    add them is meaningful. The first anatomical location you add will be at
    the smallest level of biological organization which increases when you
    add more locations.


.. tabs::

    .. tab:: Python

        .. literalinclude:: sbml_create_physical_entity_python.py
            :language: python
            :caption: Demonstrate the creation of a physical entity composite annotation in Python

        .. literalinclude:: ../../ExampleOutputFiles/sbml_create_physical_entity_python.txt
            :caption: Output

    .. tab:: C++

        .. literalinclude:: sbml_create_physical_entity_cpp.cpp
            :language: C++
            :caption: Demonstrate the creation of a physical entity composite annotation in C++

        .. literalinclude:: ../../ExampleOutputFiles/SBMLCreatePhysicalEntityCpp.txt
            :caption: Output

    .. tab:: C

        .. literalinclude:: sbml_create_physical_entity_c.cpp
            :language: C
            :caption: Demonstrate the creation of a physical entity composite annotation in C

        .. literalinclude:: ../../ExampleOutputFiles/SBMLCreatePhysicalEntityC.txt
            :caption: Output


Annotations on a Physical Process
-----------------------------------------------

.. tabs::

    .. tab:: Python

        .. literalinclude:: sbml_create_physical_process_python.py
            :language: python
            :caption: Demonstrate the creation of a physical process composite annotation in Python

        .. literalinclude:: ../../ExampleOutputFiles/sbml_create_physical_process_python.txt
            :caption: Output

    .. tab:: C++

        .. literalinclude:: sbml_create_physical_process_cpp.cpp
            :language: C++
            :caption: Demonstrate the creation of a physical process composite annotation in C++

        .. literalinclude:: ../../ExampleOutputFiles/SBMLCreatePhysicalProcessCpp.txt
            :caption: Output

    .. tab:: C

        .. literalinclude:: sbml_create_physical_process_c.cpp
            :language: C
            :caption: Demonstrate the creation of a physical process composite annotation in C

        .. literalinclude:: ../../ExampleOutputFiles/SBMLCreatePhysicalProcessC.txt
            :caption: Output



Annotations on an energy differential
-----------------------------------------------

.. tabs::

    .. tab:: Python

        .. literalinclude:: sbml_create_energy_diff_python.py
            :language: python
            :caption: Demonstrate the creation of a energy differential composite annotation in Python

        .. literalinclude:: ../../ExampleOutputFiles/sbml_create_energy_diff_python.txt
            :caption: Output

    .. tab:: C++

        .. literalinclude:: sbml_create_energy_diff_cpp.cpp
            :language: C++
            :caption: Demonstrate the creation of a energy differential composite annotation in C++

        .. literalinclude:: ../../ExampleOutputFiles/SBMLCreateEnergyDiffCpp.txt
            :caption: Output

    .. tab:: C

        .. literalinclude:: sbml_create_energy_diff_c.cpp
            :language: C
            :caption: Demonstrate the creation of a energy differential composite annotation in C

        .. literalinclude:: ../../ExampleOutputFiles/SBMLCreateEnergyDiffC.txt
            :caption: Output

Composite Annotations: CellML Examples
=======================================

Annotations on a Physical Entity
-----------------------------------------------


.. tabs::

    .. tab:: Python

        .. literalinclude:: cellml_create_physical_entity_python.py
            :language: python
            :caption: Demonstrate the creation of a physical entity composite annotation in Python

        .. literalinclude:: ../../ExampleOutputFiles/cellml_create_physical_entity_python.txt
            :caption: Output

    .. tab:: C++

        .. literalinclude:: cellml_create_physical_entity_cpp.cpp
            :language: C++
            :caption: Demonstrate the creation of a physical entity composite annotation in C++

        .. literalinclude:: ../../ExampleOutputFiles/CellMLCreatePhysicalEntityCpp.txt
            :caption: Output

    .. tab:: C

        .. literalinclude:: cellml_create_physical_entity_c.cpp
            :language: C
            :caption: Demonstrate the creation of a physical entity composite annotation in C

        .. literalinclude:: ../../ExampleOutputFiles/CellMLCreatePhysicalEntityC.txt
            :caption: Output


Annotations on a Physical Process
-----------------------------------------------

.. tabs::

    .. tab:: Python

        .. literalinclude:: cellml_create_physical_process_python.py
            :language: python
            :caption: Demonstrate the creation of a physical process composite annotation in Python

        .. literalinclude:: ../../ExampleOutputFiles/cellml_create_physical_process_python.txt
            :caption: Output

    .. tab:: C++

        .. literalinclude:: cellml_create_physical_process_cpp.cpp
            :language: C++
            :caption: Demonstrate the creation of a physical process composite annotation in C++

        .. literalinclude:: ../../ExampleOutputFiles/CellMLCreatePhysicalProcessCpp.txt
            :caption: Output

    .. tab:: C

        .. literalinclude:: cellml_create_physical_process_c.cpp
            :language: C
            :caption: Demonstrate the creation of a physical process composite annotation in C

        .. literalinclude:: ../../ExampleOutputFiles/CellMLCreatePhysicalProcessC.txt
            :caption: Output



Annotations on an energy differential
-----------------------------------------------

.. tabs::

    .. tab:: Python

        .. literalinclude:: cellml_create_energy_diff_python.py
            :language: python
            :caption: Demonstrate the creation of a energy differential composite annotation in Python

        .. literalinclude:: ../../ExampleOutputFiles/cellml_create_energy_diff_python.txt
            :caption: Output

    .. tab:: C++

        .. literalinclude:: cellml_create_energy_diff_cpp.cpp
            :language: C++
            :caption: Demonstrate the creation of a energy differential composite annotation in C++

        .. literalinclude:: ../../ExampleOutputFiles/CellMLCreateEnergyDiffCpp.txt
            :caption: Output

    .. tab:: C

        .. literalinclude:: cellml_create_energy_diff_c.cpp
            :language: C
            :caption: Demonstrate the creation of a energy differential composite annotation in C

        .. literalinclude:: ../../ExampleOutputFiles/CellMLCreateEnergyDiffC.txt
            :caption: Output
















